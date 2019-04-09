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

		// Check) State Table�� ������ Exception�� ������.
		ERROR_THROW_IF(m_pTransitionTable.empty(), CGException::CThrow_NoInitialized(), );

		// 1) ���� State�� ��´�.
		CGPTR<TSTATE>	pstateNow	 = this->GetState();

		// Check) ���� State�� ������ false�� �����Ѵ�.
		ERROR_RETURN_IF(pstateNow.empty(), false, );

		// Check) ���� State�� ������ �پ� Return�Ѵ�.
		RETURN_IF(m_pTransitionTable->HasNextState(pstateNow->GetStateID(), p_rEvent)==false, false);

		// 2) ���� State�� �����Ѵ�.
		this->ChangeState(m_pTransitionTable->GetNextState(pstateNow->GetStateID(), p_rEvent));
	}

	// Return) 
	return	true;
}


}