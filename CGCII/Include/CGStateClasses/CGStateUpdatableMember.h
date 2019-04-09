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
// CGState::CProcess<TSTATE, TEVENT>
//
// 1. CGState::CProcess<TSTATE, TEVENT>란!
//    1) Grouble 객체  여러 개를 묶어서 관리하는 것이 Group class이다.
//       이 Group Class는 는 Interface Class에 해당하는 것으로 상속을 받은 후 
//       정의하여 사용하여야 한다.
//
// 2. CGState::CProcess<TSTATE, TEVENT>의 핵심! Function의 기능 설명.
//    1) Process()
//       Group에서 Member 객체를 떼내는 함수이다. 이 함수는 abstract함수로
//      상속받은 Group은 반드시 재정의 해 주어야 한다.
//      이 함수만 virtual로 선언한 이유는 한 Group에서 다른 Group으로 옮겨갈시
//      자동으로 Group에서 떼내는 것을 처리하기 위해서이다.
//
//
//-----------------------------------------------------------------------------
namespace CGState
{

template <class _TCLASS, class _TSTATE_ID=_STRING>
class CUpdatableMember :
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						CUpdatable<_TSTATE_ID>				// (I) IState
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TCLASS				TCLASS;
	typedef	_TSTATE_ID			TSTATE_ID;


// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
	typedef	int			(TCLASS::*FEXECUTE)(CGMSG&);
	typedef	void		(TCLASS::*FONENTER)();
	typedef	void		(TCLASS::*FONLEAVE)();


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CUpdatableMember()											{}
			CUpdatableMember(const TSTATE_ID& _idState) : CUpdatable<TSTATE_ID>(_idState)	{}
			CUpdatableMember(const TSTATE_ID& _idState,					// - State ID
							FONENTER		p_fOnEnter,					// - OnStateEnter function
							FONLEAVE		p_fOnLeave,					// - OnClose function
							FEXECUTE		p_fUpdateable)				// - OnUpdateable function
							: CUpdatable<TSTATE_ID>(_idState), m_fOnEnter(p_fOnEnter), m_fOnLeave(p_fOnLeave), m_fUpdatable(p_fUpdateable)	{}
	virtual	~CUpdatableMember()											{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Updateable & ProcessMessage
	virtual	int					ProcessUpdate(CGMSG& _Msg)				{	RETURN_IF(m_fUpdatable==nullptr, FALSE); return (m_this->*m_fUpdatable)(_Msg); }

	// 2) Functions
			void				SetThis(TCLASS* p_pThis)				{	m_this=p_pThis;}
			void				ResetThis()								{	SetThis(nullptr);}

			void				SetEnterFunction(FONENTER p_fOnEnter)	{	m_fOnEnter=p_fOnEnter;}
			void				ResetEnterFunction()					{	SetEnterFunction(nullptr);}

			void				SetLeaveFunction(FONLEAVE p_fOnLeave)	{	m_fOnLeave=p_fOnLeave;}
			void				ResetLeaveFunction()					{	SetLeaveFunction(nullptr);}

			void				SetUpdateableFunction(FEXECUTE p_fProcess){	m_fUpdatable=p_fProcess;}
			void				ResetUpdateableFunction()				{	SetUpdateableFunction(nullptr);}

			void				SetFunctions(FONENTER p_fOnEnter, FONLEAVE p_fOnLeave, FEXECUTE p_fUpdateable)
								{
									SetEnterFunction(p_fOnEnter);
									SetLeaveFunction(p_fOnLeave);
									SetUpdateableFunction(p_fUpdateable);
								}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	virtual	void				ProcessStateEnter()						{	RETURN_IF(m_fOnEnter==nullptr,); (m_this->*m_fOnEnter)();}
	virtual	void				ProcessStateLeave()						{	RETURN_IF(m_fOnLeave==nullptr,); (m_this->*m_fOnLeave)();}

protected:
	// 1) Body
			TCLASS*				m_this;

	// 2) Message function
			#pragma pack(push, 16)
			FONENTER			m_fOnEnter;
			FONLEAVE			m_fOnLeave;
			FEXECUTE			m_fUpdatable;
			#pragma pack(pop)
};


}