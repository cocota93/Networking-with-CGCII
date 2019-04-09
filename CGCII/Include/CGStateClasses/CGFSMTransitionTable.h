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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGFSM::CManager
//
// 1. CGFSM::CManager란?
//    Event를 받으면 Transition Table에 따라 State들을 변경해주는 Manager이다.
// 
// 2. 구성
//    크게 State와 어떤 State에서 어떤 Event받으면 어떤 State로 전이하는가의 정보를
//    들고 있는 Transition Table로 구성되어 있다.
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

	// 3) Event를 전달하는 함수
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
		// 1) Key를 만듬.
		TRANSITION	tempTransition(p_idStateNow, p_rEvent);

		// 2) 먼저 같은 것이 있는지 확인한다.
		auto	iterFind	 = m_mapTransition.find(tempTransition);

		// Check) 이미 같은 것이 있다면 false를 리턴한다.
		ERROR_RETURN_IF(iterFind!=m_mapTransition.end(), false, );

		// 3) 아니면 추가한다.
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
		// 1) Key를 만듬.
		TRANSITION	tempTransition(p_idStateNow, p_rEvent);

		// 1) 먼저 같은 것이 있는지 확인한다.
		auto	iterFind	 = m_mapTransition.find(tempTransition);

		// Check) 해당하는 State가 없다면 그냥 끝낸다.
		ERROR_RETURN_IF(iterFind==m_mapTransition.end(), false, );

		// 2) 찾았으면 지운다.
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
		// 1) Key를 만듬.
		TRANSITION	tempTransition(p_idStateNow, p_rEvent);

		// 2) 같은 것이 있으면 true
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
		// 1) Key를 만듬.
		TRANSITION	tempTransition(p_idStateNow, p_rEvent);

		// 1) 먼저 같은 것이 있는지 확인한다.
		auto	iterFind	 = m_mapTransition.find(tempTransition);

		// Check) 해당하는 State가 없다면 그냥 끝낸다.
		ERROR_RETURN_IF(iterFind==m_mapTransition.end(), sidEmpty, );

		// Return) 
		return	iterFind->second;
	}
}


}
