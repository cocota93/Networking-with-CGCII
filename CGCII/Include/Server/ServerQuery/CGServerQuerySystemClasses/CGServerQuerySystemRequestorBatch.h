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

class NRequestorBatch :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CRequestor							//     Reference Count
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NRequestorBatch()	{}
	virtual ~NRequestorBatch()	{}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	// 1) Queue/Cancel Query
			bool				QueueQuery(ICGServerQuerier* _pQuerier, ICGServerQueryExecutable* _pQuery);
	virtual	bool				CancelQuery(ICGServerQuerier* /*_pQuerier*/) override	{ CGASSERT_ERROR(false); return 0;}
	virtual	bool				CancelQuery(ICGServerQuery* _pQuery) override;
	virtual	bool				CancelQuery() override;

			bool				CancelQueryIf(uint32_t _dwAttribute);


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Process Request Query
	virtual	bool				ProcessBeginQuery();

	// 2) Process Complete Query
	virtual	void				ProcessNotifyCompleteQuery(ICGServerQuery* _pQuery);

	// 3) ProcessCompleteExecution
	virtual	void				ProcessCompleteQuery() override			{}
};

inline bool CGServerQuery::DBSystem::NRequestorBatch::CancelQuery(ICGServerQuery* _pQuery)
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

inline bool CGServerQuery::DBSystem::NRequestorBatch::CancelQuery()
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

inline bool CGServerQuery::DBSystem::NRequestorBatch::CancelQueryIf(uint32_t _Attribute)
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

inline bool CGServerQuery::DBSystem::NRequestorBatch::ProcessBeginQuery()
{
	// Declare) 
	REQUEST_QUERY	bQueuedRequest;

	// 1) Queued된 Request를 얻어온다.(Queue에서는 빼지 않는다. 완료후 뺀다.)
	LOCK(m_queueQuery)
	{
		if (m_queueQuery.empty() == false)
		{
			bQueuedRequest	 = m_queueQuery.front();
		}
	}

	// 2) Qeueud Request가 있으면 Query를 건다. 아니면 바로 완료 처리를 한다.
	if(bQueuedRequest.pQuerier.exist())
	{
		// Check)
		CGASSERT_ERROR(bQueuedRequest.pQuery.exist());

		// - 바로 Request Query를 수행한다.
		bQueuedRequest.pQuerier->ProcessPostRequestQuery(bQueuedRequest.pQuery);
	}
	else
	{
		// - 바로 완료 처리
		ProcessCompleteQuery();
	}

	// Return)
	return	true;
}

inline void CGServerQuery::DBSystem::NRequestorBatch::ProcessNotifyCompleteQuery(ICGServerQuery* /*_pQuery*/)
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