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
template <class _TSTATE_ID, class _TEVENT=int>
class ICGFSMTransitionTable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						//
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE_ID	TSTATE_ID;
	typedef	_TEVENT		TEVENT;

	struct TRANSITION
	{
	public:
		TSTATE_ID	idState;
		TEVENT		idEvent;

	public:
			TRANSITION()	{}
			TRANSITION(const TRANSITION& _Rhs) : idState(_Rhs.idState), idEvent(_Rhs.idEvent)	{}
			TRANSITION(const TRANSITION&& _Rhs) : idState(std::move(_Rhs.idState)), idEvent(std::move(_Rhs.idEvent))	{}
			TRANSITION(const TSTATE_ID& p_ridState, const TEVENT& p_idEvent) : idState(p_ridState), idEvent(p_idEvent)	{}

	public:
			TRANSITION&	operator=(const TRANSITION& _Rhs)			{ idState=_Rhs.idState; idEvent=_Rhs.idEvent; return *this;}
			TRANSITION&	operator=(const TRANSITION&& _Rhs)			{ idState=std::move(_Rhs.idState); idEvent=std::move(_Rhs.idEvent); return *this;}

			bool		operator!=(const TRANSITION& _Rhs) const	{ return (idEvent!=_Rhs.idEvent) || (idState!=_Rhs.idState);}
			bool		operator==(const TRANSITION& _Rhs) const	{ return (idEvent==_Rhs.idEvent) && (idState==_Rhs.idState);}
			bool		operator< (const TRANSITION& _Rhs) const	{ return (idEvent< _Rhs.idEvent) ? true : (idEvent==_Rhs.idEvent) ? (idState< _Rhs.idState) : false;}
			bool		operator<=(const TRANSITION& _Rhs) const	{ return (idEvent<=_Rhs.idEvent) ? (idEvent==_Rhs.idEvent) ? (idState<= _Rhs.idState) : false : false;}
			bool		operator> (const TRANSITION& _Rhs) const	{ return (idEvent> _Rhs.idEvent) ? true : (idEvent==_Rhs.idEvent) ? (idState> _Rhs.idState) : false;}
			bool		operator>=(const TRANSITION& _Rhs) const	{ return (idEvent>=_Rhs.idEvent) ? (idEvent==_Rhs.idEvent) ? (idState>= _Rhs.idState) : false : false;}
	};


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Transition Info
	virtual	bool				RegisterTransition(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_rEvent, _In_ const TSTATE_ID& p_idStateNext) PURE;
	virtual	bool				UnregisterTransition(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_rEvent) PURE;

	// 3) Event�� �����ϴ� �Լ�
	virtual	bool				HasNextState(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_Event) PURE;
	virtual	const TSTATE_ID&	GetNextState(_In_ const TSTATE_ID& p_idStateNow, _In_ const TEVENT& p_Event) PURE;
};


