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
// CGExecutor::Executable::CList
//
// 1. CGExecutor::Executable::CList의 특징!
//    1) 여러 개의 TEXECUTABLE을 붙여서 일정시간마다 실행하는 Executor이다.
//    2) 
//       같은 함수가 동시에 여러 개가 호출되어질 수가 있다. 하지만 이 클래스는 오직
//       하나의 객체에 하나만이 동시에 동작하도록 해준다.
//
//-----------------------------------------------------------------------------
namespace CGSchedulable
{
namespace Executable
{

template <class TEXECUTABLE>
class CList<TEXECUTABLE>::ITERATOR
{
public:
	ITERATOR(const CGD::lockable& cs, const typename CONTAINER::iterator& p_iterBegin, const typename CONTAINER::iterator& p_iterEnd) : m_csLock(cs), m_iter(p_iterBegin), m_iterEnd(p_iterEnd)	{}

public:
	bool			IsContinue() const	{	return m_iter!=m_iterEnd;}
	bool			IsEnded() const		{	return m_iter==m_iterEnd;}
	bool			MoveNext()			{	if(m_iter==m_iterEnd) return false; ++m_iter; return true;}
				
	void			operator++()		{	++m_iter;}
	TEXECUTABLE*	operator->()		{	return *m_iter;}
	TEXECUTABLE*	operator*()			{	return *m_iter;}

public:
			CGD::lock_guard			m_csLock;
	typename CONTAINER::iterator	m_iter;
	typename CONTAINER::iterator	m_iterEnd;
};

template <class TEXECUTABLE>
CList<TEXECUTABLE>::CList(uint32_t _tickGap) : 
	NExecutable(_tickGap)
{
	LOCK(m_listExecutable)
	{
		m_iterNow	 = m_listExecutable.end();
	}
}

template <class TEXECUTABLE>
CList<TEXECUTABLE>::~CList()	
{
	NO_EXCEPTION_BEGIN
	{
		// 1) 모두 할당해제해준다.(이건 소멸자에서 반드시 해줘야 한다. 아니면 소멸의 순서 때문에 뻑날 수 있다.)
		LOCK(m_listExecutable)
		{
			m_listExecutable.clear();
		}
	}
	NO_EXCEPTION_END

	NO_EXCEPTION_BEGIN
	{
		// 2) 완료될 때까지 기다린다.(최대 1초간 기다린다.)
		int i=1000;
		while(GetConcurrentExecutingCount()!=0)
		{
			// - 1ms만큼 대기한다.
			Sleep(1);

			// - 카운트~
			--i;

			// Check) 최대 1000번 이상 Loop가 돌때까지 끝나지 않는다면 그냥 끝낸다.
			ERROR_BREAK_IF(i<=0, )
		}
	}
	NO_EXCEPTION_END
}

template <class TEXECUTABLE>
bool CList<TEXECUTABLE>::RegisterExecutable(_In_ TEXECUTABLE* _pExecutable)
{
	LOCK(m_listExecutable)
	{
		// 1) 해당 객체를 찾는다.
		auto	iterEnd	 = m_listExecutable.end();
		auto	iter	 = std::find(m_listExecutable.begin(), iterEnd, _pExecutable);

		// Check) 못찾았으면 끝낸다.
		RETURN_IF(iter!=iterEnd, false);

		// 2) 추가한다.
		m_listExecutable.push_back(_pExecutable);

		// 3) ...
		if(m_iterNow==iterEnd)
		{
			m_iterNow	 = m_listExecutable.end();
		}
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGExecute: Executable is registered[%p] ") _CGFUNCTION, _pExecutable);
	
	// Return) 성공~
	return	true;
}

template <class TEXECUTABLE>
bool CList<TEXECUTABLE>::UnregisterExecutable(_In_ TEXECUTABLE* _pExecutable)
{
	LOCK(m_listExecutable)
	{
		// 1) 해당 객체를 찾는다.
		auto iter	 = std::find(m_listExecutable.begin(), m_listExecutable.end(), _pExecutable);

		// Check) 못찾았으면 끝낸다.
		RETURN_IF(iter==m_listExecutable.end(), false);

		// 2) 지금 Iter중인 것이라면 다음..
		if(m_iterNow==iter)
		{
			++m_iterNow;
		}

		// 3) 지운다.
		m_listExecutable.erase(iter);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGExecute: Executable is unregistered[%p] ") _CGFUNCTION, _pExecutable);

	// Return) 성공!!!
	return	true;
}

template <class TEXECUTABLE>
void CList<TEXECUTABLE>::UnregisterAllExecutable()
{
	// Declare) 
	CONTAINER	listExecutable;

	// 1) Swap한다.
	LOCK(m_listExecutable)
	{
		listExecutable.swap(m_listExecutable);
	}

	// 2) 모두 제거한다.
	for(const auto& iter:listExecutable)
	{
		// Trace) 
		CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGExecute: All Executables are unregistered[%p] ") _CGFUNCTION, pExecutable->get());
	}
}

template <class TEXECUTABLE>
typename CList<TEXECUTABLE>::ITERATOR CList<TEXECUTABLE>::GetIterator()
{
	LOCK(m_listExecutable)
	{
		return	ITERATOR(m_listExecutable, m_listExecutable.begin(), m_listExecutable.end());
	}
}

template <class TEXECUTABLE>
size_t CList<TEXECUTABLE>::GetExecutableCount() const
{
	LOCK(m_listExecutable)
	{
		return	m_listExecutable.size();
	}
}

template <class TEXECUTABLE>
bool CList<TEXECUTABLE>::IsEmpty() const
{
	return GetExecutableCount()==0;
}

template <class TEXECUTABLE>
bool CList<TEXECUTABLE>::IsExist() const
{
	return GetExecutableCount()!=0;
}

template <class TEXECUTABLE>
intptr_t CList<TEXECUTABLE>::ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param)
{
	LOCK(m_listExecutable)
	{
		// 1) begin()과 end()를 미리 받아 놓는다.
		m_iterNow	 = m_listExecutable.begin();

		// 2) 순회하며 실행한다.
		while(m_iterNow!=m_listExecutable.end())
		{
			typename CONTAINER::iterator	iterNow	 = m_iterNow++;

			(*iterNow)->ProcessExecute(_Return, _Param);
		}
	}

	// Return) 
	return	intptr_t(0);
}


}
}