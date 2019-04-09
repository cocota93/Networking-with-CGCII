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
// CGFSM::State::CMessageMember
//
// 1. CGFSM::State::CMessageMember�̶�...?
//    1) Class Member �Լ��� State�� �Լ���� ����ϴ� State�̴�.
//    2) �̰��� ����ϰ� �Ǹ� �޸𸮸� 256kbyte�� ����ϹǷ� Packet�� ������
//       ���� �ʿ��� ����ϴ� ���� ����.
//    3) Packet�� ������ �ش� Packet�� ���� �� ȣ��� �Լ��� �������ָ�...
//       Table���� ���ٷ� Pointing�ؼ� �ش��ϴ� �Լ��� ȣ���ϵ��� �Ǿ� �ִ�.
//
//
//-----------------------------------------------------------------------------
namespace CGState
{

template <class _TCLASS, class _TSTATE_ID=_STRING>
class CUpdatableMessagableMember :
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						CUpdatableMember<_TCLASS, _TSTATE_ID>,
	virtual public				ICGMessageable							// (I) ICGMessageable
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TCLASS														TCLASS;
	typedef	_TSTATE_ID													TSTATE_ID;
	typedef	typename CUpdatableMember<_TCLASS, _TSTATE_ID>::FEXECUTE	FEXECUTE;
	typedef	typename CUpdatableMember<_TCLASS, _TSTATE_ID>::FONENTER	FONENTER;
	typedef	typename CUpdatableMember<_TCLASS, _TSTATE_ID>::FONLEAVE	FONLEAVE;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CUpdatableMessagableMember()								{}
			CUpdatableMessagableMember(const TSTATE_ID& _idState) : CUpdatableMember<_TCLASS, _TSTATE_ID>(_idState)	{}
			CUpdatableMessagableMember(	const TSTATE_ID& _idState,	// - State ID
							FEXECUTE	p_fMessageable,			// - Messageable function
							FONENTER	p_fOnEnter=nullptr,		// - OnStateEnter function
							FONLEAVE	p_fOnLeave=nullptr,		// - OnClose function
							FEXECUTE	p_fUpdate=nullptr)		// - OnUpdate function
							: CUpdatableMember<TSTATE_ID>(_idState, p_fOnEnter, p_fOnLeave, p_fUpdate), m_fMessageable(p_fMessageable)	{}
	virtual	~CUpdatableMessagableMember()								{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Update & Messageable
	virtual	int					ProcessMessage(CGMSG& _Msg)				{	RETURN_IF(m_fMessageable==nullptr, 0); return (CUpdatableMember<_TCLASS, _TSTATE_ID>::m_this->*m_fMessageable)(_Msg);}

	// 2) Functions
			void				SetMessageableFunction(FEXECUTE _pFunction) {	m_fMessageable=_pFunction;}
			void				ResetMessageableFunction()				{	SetMessageableFunction(nullptr);}

			void				SetFunctions( FEXECUTE p_fMessageable, FONENTER p_fOnEnter, FONLEAVE p_fOnLeave, FEXECUTE p_fUpdate)
								{
									CUpdatableMember<_TCLASS, _TSTATE_ID>::SetFunctions(p_fOnEnter, p_fOnLeave, p_fUpdate);
									SetMessageableFunction(p_fMessageable);
								}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 2) Message function
			FEXECUTE			m_fMessageable;
};


}


// ----------------------------------------------------------------------------
// DEFINE
// ----------------------------------------------------------------------------
// 1) For Network Message
#define	CGNETSTATE	CGState::CUpdatableMessagableMember

// 2) Declare Manager
#define	DECLARE_CGNETSTATE_CONTROL(body, manager)						CGOBJ<CCGStateable<CGNETSTATE<body>>>	manager;

// 3) Define State
#define	DEFINE_CGNETSTATE(body, state)									CGOBJ<CGNETSTATE<body>>	state;

// 4) Set State
#define	SET_CGNETSTATE(body, manager, message, open, close, process)	CGOBJ<CGFSM::CStateNetwork<body>> body::manager(message, open, close, process);


// ----------------------------------------------------------------------------
// PROCESS_STATEMESSAGE
// ----------------------------------------------------------------------------
#define	PROCESS_STATE_CGMESSAGE(manager, msg)							\
{																		\
	auto	pState	 = manager.GetState();								\
	if(pState.exist())													\
	{																	\
		auto	iResult	 = pState->ProcessMessage(msg);					\
		RETURN_IF(iResult!=0, iResult);									\
	}																	\
}
