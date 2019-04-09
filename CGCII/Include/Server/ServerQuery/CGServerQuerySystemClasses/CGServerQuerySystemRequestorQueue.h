//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                         Server DB System Classes                          *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGServerQuery::DBSystem::IEntity
//
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DBSystem
{

class CRequestorQueue :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGServerQueryRequestor				//     Reference Count
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CRequestorQueue()	{}
	virtual ~CRequestorQueue()	{}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	// 1) Request Query
			void				RequestQuery(ICGServerQuerier* _pQuerier, ICGServerQueryExecutable* _pQuery) { ProcessRequestQuery(_pQuerier, _pQuery); }

	// 2) Cancel Query
	virtual	bool				CancelQuery(ICGServerQuery* _pQuery);
	virtual	bool				CancelQuery();

			bool				CancelQueryIf(uint32_t _Attribute);


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// Definitions) 
	struct REQUEST_QUERY
	{
	public:
		REQUEST_QUERY()	{}
		REQUEST_QUERY(ICGServerQuerier* _pQuerier, ICGServerQueryExecutable* _pQuery) : pQuerier(_pQuerier), pQuery(_pQuery)	{}

	public:
		CGPTR<ICGServerQuerier>			pQuerier;
		CGPTR<ICGServerQueryExecutable>	pQuery;
	};


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Process Request Query
	virtual	void				ProcessRequestQuery(ICGServerQuerier* _pQuerier, ICGServerQueryExecutable* _pQuery);

	// 2) Process Complete Query
	virtual	void				ProcessNotifyCompleteQuery(ICGServerQuery* _pQuery) override;

	// 3) ProcessCompleteExecution
	virtual	void				ProcessCompleteQuery()					{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	LOCKABLE<circular_list<REQUEST_QUERY>>	m_queueQuery;
};


inline void CRequestorQueue::ProcessRequestQuery(ICGServerQuerier* _pQuerier, ICGServerQueryExecutable* _pQuery)
{
	// 1) Requestor를 this로 설정한다.
	_pQuery->SetRequestor(this);

	LOCK(m_queueQuery)
	{
		// 2) Queue에 집어 넣는다.
		m_queueQuery.push_back(REQUEST_QUERY(_pQuerier, _pQuery));

		// Check) Queuing된 수가 1개 이상이면 그냥 끝넨다.
		RETURN_IF(m_queueQuery.size()>1, );
	}

	// 3) 바로 Request Query를 수행한다.
	_pQuerier->ProcessPostRequestQuery(_pQuery);
}

inline bool CRequestorQueue::CancelQuery(ICGServerQuery* _pQuery)
{
	LOCK_NAMED(m_queueQuery, cs)
	{
		auto	iterBegin= m_queueQuery.begin();
		auto	iterEnd	 = m_queueQuery.end();

		for(auto iter=iterBegin; iter!=iterEnd; ++iter)
		{
			if((*iter).pQuery==_pQuery)
			{
				// - 제일 앞 즉 현재 Querier에 걸려있는 Query라면 먼저 Querier에 Query의 Cancel을 시도하고 성공하면 다음 Query를 건다.
				if(iter==iterBegin)
				{
					// Declare) 
					bool	bResult;

					// - Query를 Cancel한다.
					bResult	 = iter->pQuerier->CancelQuery(iter->pQuery);

					// Check) 제거에 실패했으면 false를 리턴한다.
					RETURN_IF(bResult!=true, false);

					// - Requestor를 제거...
					(*iter).pQuery->ResetRequestor();

					// - 성공적으로 Cancel이 되었다면 iterator를 다음으로 옮긴다.
					m_queueQuery.erase(iter++);

					// - 제일 끝이 아니라면 
					if(iter!=iterEnd)
					{
						// Declare) 
						REQUEST_QUERY	tempQuery	 = *iter;

						// Critical Section Leave)
						LOCK_LEAVE(cs);

						// - Query를 건다.
						tempQuery.pQuerier->ProcessPostRequestQuery(tempQuery.pQuery);
					}
					// - 끝이라면 ProcessCompleteQuery를 호출한다.
					else
					{
						// Critical Section Leave)
						LOCK_LEAVE(cs);

						ProcessCompleteQuery();
					}
				}
				else
				{
					// - Requestor를 제거...
					(*iter).pQuery->ResetRequestor();

					// - 지운다.
					m_queueQuery.erase(iter);
				}

				// Break)
				break;
			}
		}
	}

	// Return)
	return	true;
}

inline bool CRequestorQueue::CancelQuery()
{
	LOCK(m_queueQuery)
	{
		// Check) 
		RETURN_IF(m_queueQuery.empty(), true);

		// 1) 제일 앞의 Query를 얻는다.
		REQUEST_QUERY	queryRequest	 = m_queueQuery.front();

		// Declare) 
		bool	bResult;

		// 2) Query를 Cancel한다.
		bResult	 = queryRequest.pQuerier->CancelQuery(queryRequest.pQuery);

		// 3) 제거에 실패했으면 처음 것만 빼고 모두 Cancel한다.
		if(bResult!=true)
		{
			auto	iterBegin	 = ++m_queueQuery.begin();
			auto	iterEnd		 = m_queueQuery.end();

			for(auto iter=iterBegin; iter!=iterEnd; ++iter)
			{
				(*iter).pQuery->ResetRequestor();
			}
			m_queueQuery.erase(iterBegin, iterEnd);

			// Return) 
			return	false;
		}

		// 4) 제거에 성공했으면 모두 제거한다.
		for(auto& iter:m_queueQuery)
		{
			iter.pQuery->ResetRequestor();
		}
		m_queueQuery.clear();
	}

	// 5) ProcessCompleteQuery
	ProcessCompleteQuery();

	// Return) 
	return	true;
}

inline bool CRequestorQueue::CancelQueryIf(uint32_t _Attribute)
{
	LOCK(m_queueQuery)
	{
		// Check) 
		RETURN_IF(m_queueQuery.empty(), false);

		// 1) 제일 앞의 Query를 얻는다.
		RETURN_IF(m_queueQuery.front().pQuery->GetAttribute()!=_Attribute, false);

		// 2) Query를 취소한다.
		return	CancelQuery();
	}
}

inline void CRequestorQueue::ProcessNotifyCompleteQuery(ICGServerQuery* /*_pQuery*/)
{
	// Declare) 
	REQUEST_QUERY	tempQuery;

	LOCK(m_queueQuery)
	{
		// Check) 없으면 그냥 끝낸다.
		CGASSERT_ERROR(!m_queueQuery.empty());

		// 1) 일단 제일 앞에 것 제거
		m_queueQuery.pop_front();

		// 2) 제일 앞의 Query를 하나 꺼낸다.
		if(!m_queueQuery.empty())
		{
			tempQuery	 = m_queueQuery.front();
		}
	}

	// 2-1) 새로운 Query를 건다.
	if(tempQuery.pQuery.exist())
	{
		tempQuery.pQuerier->ProcessPostRequestQuery(tempQuery.pQuery);
	}
	// 2-2) Query를 완전히 종료했을 때...
	else
	{
		ProcessCompleteQuery();
	}
}


}
}