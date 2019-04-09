//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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
// CGExecutor::CList
//
// 1. CGExecutor::CList은~
//    1) 여러 개의 Executor를 일정시간마다 실행시켜주는 Executor의 Executor이다.
//    
// 2. 주요함수.
//    1) bool RegisterExecutor(TEXECUTOR* _pExecutor);
//       - 실행할 TEXECUTOR을 붙이는 함수이다.
//
//    2) bool UnregisterExecutor(TEXECUTOR* _pExecutor);
//       - 붙혀진 TEXECUTOR을 떼어낸다.
//
//-----------------------------------------------------------------------------
namespace CGExecutor
{

template <class TEXECUTOR>
class CList<TEXECUTOR>::ITERATOR
{
public:
	ITERATOR(const LOCKABLE<CONTAINER>& pContainer) : m_csLock(pContainer), m_iter(pContainer.begin()), m_iterEnd(pContainer.end())	{}

public:
	bool			IsContinue() const	{	return m_iter!=m_iterEnd;}
	bool			IsEnded() const		{	return m_iter==m_iterEnd;}
	bool			MoveNext()			{	if(m_iter==m_iterEnd) return false; ++m_iter; return true;}
				
	void			operator++()		{	++m_iter;}
	TEXECUTOR*		operator->()		{	return *m_iter;}
	TEXECUTOR*		operator*()			{	return *m_iter;}

public:
			CGD::lock_guard			m_csLock;
	typename CONTAINER::iterator	m_iter;
	typename CONTAINER::iterator	m_iterEnd;
};

template <class TEXECUTOR>
CList<TEXECUTOR>::CList()
{
	SetObjectType(eOBJECT_TYPE::EXECUTOR_LIST);
}

template <class TEXECUTOR>
CList<TEXECUTOR>::~CList()
{
	NO_EXCEPTION_BEGIN
	{
		LOCK(m_listExecutor)
		{
			m_listExecutor.clear();
		}
	}
	NO_EXCEPTION_END
}

template <class TEXECUTOR>
bool CList<TEXECUTOR>::Stop()
{
	// 1) 모두 할당해제해준다.(이건 소멸자에서 반드시 해줘야 한다. 아니면 소멸의 순서 때문에 뻑날 수 있다.)
	LOCK(m_listExecutor)
	{
		m_listExecutor.clear();
	}

	// Return)
	return	true;
}

template <class TEXECUTOR>
bool CList<TEXECUTOR>::ProcessAttach(_In_ TEXECUTOR* _pExecutor)
{
	LOCK(m_listExecutor)
	{
		// 1) 해당 객체를 찾는다.
		auto	iterEnd	 = m_listExecutor.end();
		auto	iter	 = std::find(m_listExecutor.begin(), iterEnd, _pExecutor);

		// Check) 이미 추가되어 있으면 끝낸다.
		RETURN_IF(iter!=iterEnd, false);

		// 2) 추가한다.
		m_listExecutor.push_back(_pExecutor);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGExecute: Executor is attached[%p] ") _CGFUNCTION, _pExecutor);
	
	// Return) 성공~
	return	true;
}

template <class TEXECUTOR>
int CList<TEXECUTOR>::ProcessDetach(_In_opt_ TEXECUTOR* _pExecutor)
{
	LOCK(m_listExecutor)
	{
		// Check) nullptr이면 모든 객체를 떼낸다.
		if(_pExecutor==nullptr)
		{
			return	UnregisterAllExecutor();
		}

		// 1) 해당 객체를 찾는다.
		auto	iterEnd	 = m_listExecutor.end();
		auto	iter	 = std::find(m_listExecutor.begin(), iterEnd, _pExecutor);

		// Check) 못찾았으면 끝낸다.
		RETURN_IF(iter==iterEnd, 0);

		// 2) 지운다.
		m_listExecutor.erase(iter);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGExecute: Executor is detached[%p] ") _CGFUNCTION, _pExecutor);

	// Return) 성공!!!
	return	1;
}

template <class TEXECUTOR>
int CList<TEXECUTOR>::UnregisterAllExecutor()
{
	int	iCount;

	LOCK(m_listExecutor)
	{
		// 1) Excutor의 갯수를 저장해 놓는다.
		iCount	 = static_cast<int>(m_listExecutor.size());

		// 2) 모두 제거
		m_listExecutor.clear();
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGExecute: All Executors is unregistered ") _CGFUNCTION);

	// Return)
	return	iCount;
}

template <class TEXECUTOR>
typename CList<TEXECUTOR>::ITERATOR CList<TEXECUTOR>::GetIterator()
{
	LOCK(m_listExecutor)
	{
		return	ITERATOR(m_listExecutor);
	}
}

// Definitions) 
template <class TREF>
class CGATOMIC_REF
{
public:
	CGATOMIC_REF(ATOMIC<TREF>& _rRef) noexcept : m_rRef(_rRef) { value=_rRef.fetch_add(1)+1; }
	~CGATOMIC_REF() noexcept { m_rRef.fetch_sub(1); }

private:
	ATOMIC<TREF>&		m_rRef;
public:
	TREF				value;
};

template <class TEXECUTOR>
bool CList<TEXECUTOR>::ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Param)
{
	//// Check) _pExecutable가 nullptr이면 그냥 끝낸다.
	//RETURN_IF(_pExecutable==nullptr, false);

	//// Declare) 
	//CGATOMIC_REF<size_t>	rExecutable(_pExecutable->m_countConcurrentExecuting);

	//// Check) 현재 실행수가 MAX치보다 크면 1을 줄이고 끝낸다.
	//RETURN_IF(rExecutable.value>_pExecutable->GetMaxConcurrentExecutingCount(), false);

	//// 1) 바로 실행한다.
	//_pExecutable->ProcessExecute(0, _Param);

	// Return)
	return	true;
}

template <class TEXECUTOR>
bool CList<TEXECUTOR>::Execute(_In_ TICK::duration _tickdiff)
{
	// Declare) 
	vector<CGPTR<TEXECUTOR>>	vectorExecutor;

	LOCK(m_listExecutor)
	{
		// 1) Resserve
		for(const auto& iter:m_listExecutor)
		{
			vectorExecutor.push_back(iter);
		}
	}

	// 4) 돌면서 Execute한다.
	for(auto& iter:vectorExecutor)
	{
		iter->Execute(_tickdiff);
	}

	// Return)
	return	true;
}

template <class TEXECUTOR>
size_t CList<TEXECUTOR>::GetExecutorCount() const
{
	LOCK(m_listExecutor)
	{
		return	m_listExecutor.size();
	}
}

template <class TEXECUTOR>
bool CList<TEXECUTOR>::IsEmpty() const
{
	return GetExecutorCount()==0;
}

template <class TEXECUTOR>
bool CList<TEXECUTOR>::IsExist() const
{
	return GetExecutorCount()!=0;
}


}