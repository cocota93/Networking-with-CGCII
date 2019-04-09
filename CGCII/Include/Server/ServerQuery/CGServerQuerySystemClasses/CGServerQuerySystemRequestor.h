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

class CRequestor : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGServerQueryRequestor				//     Reference Count
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CRequestor()	{}
	virtual ~CRequestor()	{	CancelQuery();}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Request Query
			bool				RequestQuery()							{ return ProcessBeginQuery(); }

	// 2) Add Query/Cancel Query
			bool				AddQuery(ICGServerQuerier* _pQuerier, ICGServerQueryExecutable* _pQuery);
	virtual	bool				CancelQuery(ICGServerQuerier* _pQuerier);
	virtual	bool				CancelQuery(ICGServerQuery* /*_pQuery*/){ CGASSERT_ERROR(false); return 0;}
	virtual	bool				CancelQuery();


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
		CGPTR<ICGServerQuerier>	pQuerier;
		CGPTR<ICGServerQueryExecutable>	pQuery;
	};

	virtual	bool				ProcessBeginQuery() PURE;
	virtual	void				ProcessCompleteQuery() PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
		LOCKABLE<circular_list<REQUEST_QUERY>>	m_queueQuery;
};

inline bool CGServerQuery::DBSystem::CRequestor::AddQuery(ICGServerQuerier* _pQuerier, ICGServerQueryExecutable* _pQuery)
{
	// Check)
	ERROR_RETURN_IF(_pQuerier == nullptr, false, );

	// Check)
	ERROR_RETURN_IF(_pQuery == nullptr, false, );

	// 1) Requestor를 this로 설정한다.
	_pQuery->SetRequestor(this);

	try
	{
		LOCK(m_queueQuery)
		{
			// 2) Queue에 집어 넣는다.
			m_queueQuery.push_back(REQUEST_QUERY(_pQuerier, _pQuery));
		}
	}
	catch (...)
	{
		// - Reset...
		_pQuery->ResetRequestor();

		// Reraise) 
		throw;
	}

	// Return)
	return	true;
}

inline bool CGServerQuery::DBSystem::CRequestor::CancelQuery(ICGServerQuerier* _pQuerier)
{
	LOCK(m_queueQuery)
	{
		auto	iter	 = m_queueQuery.begin();
		auto	iterEnd	 = m_queueQuery.end();

		for(; iter!=iterEnd; )
		{
			if((*iter).pQuerier==_pQuerier)
			{
				m_queueQuery.erase(iter++);
				continue;
			}

			++iter;
		}
	}

	// Return)
	return	true;
}

inline bool CGServerQuery::DBSystem::CRequestor::CancelQuery()
{
	LOCK(m_queueQuery)
	{
		for(auto& iter:m_queueQuery)
		{
			iter.pQuery->ResetRequestor();
		}

		m_queueQuery.clear();
	}

	// Return)
	return	true;
}


}
}