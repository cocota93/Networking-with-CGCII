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

template <class _TSTATE, class _TEVENT=int>
class NControl: 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGFSMControl<_TSTATE, _TEVENT>			//     FSM Control
{
	// ****************************************************************************
	// Definitnion)
	// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE														TSTATE;
	typedef	typename ICGFSMControl<_TSTATE, _TEVENT>::TSTATE_ID			TSTATE_ID;
	typedef	_TEVENT														TEVENT;
	typedef	typename ICGFSMControl<_TSTATE, _TEVENT>::TRANSITION_TABLE	TRANSITION_TABLE;


	// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NControl()			{}
	virtual	~NControl()			{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	virtual	bool				NotifyEvent(const TEVENT& p_rEvent) override;

			void				SetTransitionTable(TRANSITION_TABLE* p_pTransitionTable);
			CGPTR<TRANSITION_TABLE>	GetTransitionTable()	{	return m_pTransitionTable;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			CGPTR<TRANSITION_TABLE>	m_pTransitionTable;
};

template <class _TSTATE, class _TEVENT>
void NControl<_TSTATE, _TEVENT>::SetTransitionTable(TRANSITION_TABLE* p_pTransitionTable)
{
	LOCK(ICGStateable<_TSTATE>::m_csState)
	{
		m_pTransitionTable	 = p_pTransitionTable;
	}
}

template <class _TSTATE, class _TEVENT>
bool NControl<_TSTATE, _TEVENT>::NotifyEvent(const TEVENT& p_rEvent)
{
	LOCK(ICGStateable<_TSTATE>::m_csState)
	{
		// Check) 
		CGASSERT_ERROR(m_pTransitionTable.exist());

		// Check) State Table이 없으면 Exception을 던진다.
		ERROR_THROW_IF(m_pTransitionTable.empty(), CGException::CThrow_NoInitialized(), );

		// 1) 현재 State를 얻는다.
		CGPTR<TSTATE>	pstateNow	 = this->GetState();

		// Check) 현재 State가 없으면 false를 리턴한다.
		ERROR_RETURN_IF(pstateNow.empty(), false, );

		// Check) 다음 State가 없으면 근야 Return한다.
		RETURN_IF(m_pTransitionTable->HasNextState(pstateNow->GetStateID(), p_rEvent)==false, false);

		// 2) 다음 State로 변경한다.
		this->ChangeState(m_pTransitionTable->GetNextState(pstateNow->GetStateID(), p_rEvent));
	}

	// Return) 
	return	true;
}


}