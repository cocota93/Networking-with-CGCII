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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
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
				// - ���� �� �� ���� Querier�� �ɷ��ִ� Query��� ���� Querier�� Query�� Cancel�� �õ��ϰ� �����ϸ� ���� Query�� �Ǵ�.
				if(iter==iterBegin)
				{
					// Declare) 
					bool	bResult;

					// - Query�� Cancel�Ѵ�.
					bResult	 = iter->pQuerier->CancelQuery(iter->pQuery);

					// Check) ���ſ� ���������� false�� �����Ѵ�.
					RETURN_IF(bResult!=true, false);

					// - Requestor�� ����...
					(*iter).pQuery->ResetRequestor();

					// - ���������� Cancel�� �Ǿ��ٸ� iterator�� �������� �ű��.
					m_queueQuery.erase(iter++);

					// - ���� ���� �ƴ϶�� 
					if(iter!=iterEnd)
					{
						// Declare) 
						REQUEST_QUERY	tempQuery	 = *iter;

						// Critical Section Leave)
						LOCK_LEAVE(cs);

						// - Query�� �Ǵ�.
						tempQuery.pQuerier->ProcessPostRequestQuery(tempQuery.pQuery);
					}
					// - ���̶�� ProcessCompleteQuery�� ȣ���Ѵ�.
					else
					{
						// Critical Section Leave)
						LOCK_LEAVE(cs);

						ProcessCompleteQuery();
					}
				}
				else
				{
					// - Requestor�� ����...
					(*iter).pQuery->ResetRequestor();

					// - �����.
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

		// 1) ���� ���� Query�� ��´�.
		REQUEST_QUERY	queryRequest	 = m_queueQuery.front();

		// Declare) 
		bool	bResult;

		// 2) Query�� Cancel�Ѵ�.
		bResult	 = queryRequest.pQuerier->CancelQuery(queryRequest.pQuery);

		// 3) ���ſ� ���������� ó�� �͸� ���� ��� Cancel�Ѵ�.
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

		// 4) ���ſ� ���������� ��� �����Ѵ�.
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

		// 1) ���� ���� Query�� ��´�.
		RETURN_IF(m_queueQuery.front().pQuery->GetAttribute()!=_Attribute, false);

		// 2) Query�� ����Ѵ�.
		return	CancelQuery();
	}
}

inline bool CGServerQuery::DBSystem::NRequestorBatch::ProcessBeginQuery()
{
	// Declare) 
	REQUEST_QUERY	bQueuedRequest;

	// 1) Queued�� Request�� ���´�.(Queue������ ���� �ʴ´�. �Ϸ��� ����.)
	LOCK(m_queueQuery)
	{
		if (m_queueQuery.empty() == false)
		{
			bQueuedRequest	 = m_queueQuery.front();
		}
	}

	// 2) Qeueud Request�� ������ Query�� �Ǵ�. �ƴϸ� �ٷ� �Ϸ� ó���� �Ѵ�.
	if(bQueuedRequest.pQuerier.exist())
	{
		// Check)
		CGASSERT_ERROR(bQueuedRequest.pQuery.exist());

		// - �ٷ� Request Query�� �����Ѵ�.
		bQueuedRequest.pQuerier->ProcessPostRequestQuery(bQueuedRequest.pQuery);
	}
	else
	{
		// - �ٷ� �Ϸ� ó��
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
		// Check) ������ �׳� ������.
		CGASSERT_ERROR(!m_queueQuery.empty());

		// 1) �ϴ� ���� �տ� �� ����
		m_queueQuery.pop_front();

		// 2) ���� ���� Query�� �ϳ� ������.
		if(!m_queueQuery.empty())
		{
			tempQuery	 = m_queueQuery.front();
		}
	}

	// 2-1) ���ο� Query�� �Ǵ�.
	if(tempQuery.pQuery.exist())
	{
		tempQuery.pQuerier->ProcessPostRequestQuery(tempQuery.pQuery);
	}
	// 2-2) Query�� ������ �������� ��...
	else
	{
		ProcessCompleteQuery();
	}
}


}
}