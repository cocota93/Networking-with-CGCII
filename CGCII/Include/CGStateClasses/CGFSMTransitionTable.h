//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               State Classes                               *
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
// CGFSM::CManager
//
// 1. CGFSM::CManager��?
//    Event�� ������ Transition Table�� ���� State���� �������ִ� Manager�̴�.
// 
// 2. ����
//    ũ�� State�� � State���� � Event������ � State�� �����ϴ°��� ������
//    ��� �ִ� Transition Table�� �����Ǿ� �ִ�.
// 
//
//-----------------------------------------------------------------------------
namespace CGFSM
{

template <class _TSTATE_ID, class _TEVENT=int>
class CTransitionTable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGFSMTransitionTable<_TSTATE_ID, _TEVENT>//
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE_ID		TSTATE_ID;
	typedef	_TEVENT			TEVENT;
	typedef typename ICGFSMTransitionTable<_TSTATE_ID, _TEVENT>::TRANSITION	TRANSITION;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CTransitionTable()	{}
	virtual	~CTransitionTable()	{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Transition Info
	virtual	bool				RegisterTransition(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_rEvent, _In_ const TSTATE_ID& p_idStateNext);
	virtual	bool				UnregisterTransition(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_rEvent);

	// 3) Event�� �����ϴ� �Լ�
	virtual	bool				HasNextState(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_Event);
	virtual	const TSTATE_ID&	GetNextState(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_Event);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 2) State Container
			LOCKABLE<std::map<TRANSITION, TSTATE_ID>>	m_mapTransition;
};

template <class _TSTATE, class _TEVENT>
bool CTransitionTable<_TSTATE, _TEVENT>::RegisterTransition(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_rEvent, _In_ const TSTATE_ID& p_idStateNext)
{
	LOCK(m_mapTransition)
	{
		// 1) Key�� ����.
		TRANSITION	tempTransition(p_idStateNow, p_rEvent);

		// 2) ���� ���� ���� �ִ��� Ȯ���Ѵ�.
		auto	iterFind	 = m_mapTransition.find(tempTransition);

		// Check) �̹� ���� ���� �ִٸ� false�� �����Ѵ�.
		ERROR_RETURN_IF(iterFind!=m_mapTransition.end(), false, );

		// 3) �ƴϸ� �߰��Ѵ�.
		m_mapTransition.insert(std::make_pair(tempTransition, p_idStateNext));
	}

	// Return) 
	return	true;
}

template <class _TSTATE, class _TEVENT>
bool CTransitionTable<_TSTATE, _TEVENT>::UnregisterTransition(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_rEvent)
{
	LOCK(m_mapTransition)
	{
		// 1) Key�� ����.
		TRANSITION	tempTransition(p_idStateNow, p_rEvent);

		// 1) ���� ���� ���� �ִ��� Ȯ���Ѵ�.
		auto	iterFind	 = m_mapTransition.find(tempTransition);

		// Check) �ش��ϴ� State�� ���ٸ� �׳� ������.
		ERROR_RETURN_IF(iterFind==m_mapTransition.end(), false, );

		// 2) ã������ �����.
		m_mapTransition.erase(iterFind);
	}

	// Return) 
	return	true;
}

template <class _TSTATE, class _TEVENT>
bool CTransitionTable<_TSTATE, _TEVENT>::HasNextState(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_rEvent)
{
	LOCK(m_mapTransition)
	{
		// 1) Key�� ����.
		TRANSITION	tempTransition(p_idStateNow, p_rEvent);

		// 2) ���� ���� ������ true
		return	m_mapTransition.find(tempTransition)!=m_mapTransition.end();
	}
}

template <class _TSTATE, class _TEVENT>
const typename CTransitionTable<_TSTATE, _TEVENT>::TSTATE_ID& CTransitionTable<_TSTATE, _TEVENT>::GetNextState(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_rEvent)
{
	// Declare)
	static	TSTATE_ID	sidEmpty;

	LOCK(m_mapTransition)
	{
		// 1) Key�� ����.
		TRANSITION	tempTransition(p_idStateNow, p_rEvent);

		// 1) ���� ���� ���� �ִ��� Ȯ���Ѵ�.
		auto	iterFind	 = m_mapTransition.find(tempTransition);

		// Check) �ش��ϴ� State�� ���ٸ� �׳� ������.
		ERROR_RETURN_IF(iterFind==m_mapTransition.end(), sidEmpty, );

		// Return) 
		return	iterFind->second;
	}
}


}
