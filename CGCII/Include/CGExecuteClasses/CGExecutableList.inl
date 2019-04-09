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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGExecutable::CList
//
// 1. CGExecutable::CList�� Ư¡!
//    1) �������� Executable�� list���·� ������ ������ ����� �� �ڽ��� ����
//       Executable�� ProcessExecute()�� ȣ�����ش�.
//
//-----------------------------------------------------------------------------
namespace CGExecutable
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
CList<TEXECUTABLE>::CList()
{
	SetObjectType(eOBJECT_TYPE::EXECUTABLE_LIST);

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
		// 1) ��� �Ҵ��������ش�.(�̰� �Ҹ��ڿ��� �ݵ�� ����� �Ѵ�. �ƴϸ� �Ҹ��� ���� ������ ���� �� �ִ�.)
		LOCK(m_listExecutable)
		{
			m_listExecutable.clear();
		}
	}
	NO_EXCEPTION_END
}

template <class TEXECUTABLE>
bool CList<TEXECUTABLE>::RegisterExecutable(_In_ TEXECUTABLE* _pExecutable)
{
	LOCK(m_listExecutable)
	{
		// 1) �ش� ��ü�� ã�´�.
		auto	iterEnd	 = m_listExecutable.end();
		auto	iter	 = std::find(m_listExecutable.begin(), iterEnd, _pExecutable);

		// Check) ��ã������ ������.
		RETURN_IF(iter!=iterEnd, false);

		// 2) �߰��Ѵ�.
		m_listExecutable.push_back(_pExecutable);

		// 3) ...
		if(m_iterNow==iterEnd)
		{
			m_iterNow	 = m_listExecutable.end();
		}
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("Prg) Executable is registered[%p] ") _CGFUNCTION, _pExecutable);
	
	// Return) ����~
	return	true;
}

template <class TEXECUTABLE>
bool CList<TEXECUTABLE>::UnregisterExecutable(_In_ TEXECUTABLE* _pExecutable)
{
	LOCK(m_listExecutable)
	{
		// 1) �ش� ��ü�� ã�´�.
		auto iter	 = std::find(m_listExecutable.begin(), m_listExecutable.end(), _pExecutable);

		// Check) ��ã������ ������.
		RETURN_IF(iter==m_listExecutable.end(), false);

		// 2) ���� Iter���� ���̶�� ����..
		if(m_iterNow==iter)
		{
			++m_iterNow;
		}

		// 3) �����.
		m_listExecutable.erase(iter);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("Prg) Executable is unregistered[%p] ") _CGFUNCTION, _pExecutable);

	// Return) ����!!!
	return	true;
}

template <class TEXECUTABLE>
void CList<TEXECUTABLE>::DetachAllExecutable()
{
	// Declare) 
	CONTAINER	listExecutable;

	// 1) Swap�Ѵ�.
	LOCK(m_listExecutable)
	{
		listExecutable.swap(m_listExecutable);
	}

	// 2) ��� �����Ѵ�.
	for(const auto& iter:listExecutable)
	{
		// Trace) 
		CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGExecute: Executable is unregistered[%p] ") _CGFUNCTION, iter->get());
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
		// 1) begin()�� end()�� �̸� �޾� ���´�.
		m_iterNow	 = m_listExecutable.begin();

		// 2) ��ȸ�ϸ� �����Ѵ�.
		while(m_iterNow!=m_listExecutable.end())
		{
			auto	iterNow	 = m_iterNow++;

			(*iterNow)->ProcessExecute(_Return, _Param);
		}
	}

	// Return) Success
	return	intptr_t(0);
}


}
