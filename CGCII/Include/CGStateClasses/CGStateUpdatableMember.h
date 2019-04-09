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
// CGState::CProcess<TSTATE, TEVENT>
//
// 1. CGState::CProcess<TSTATE, TEVENT>��!
//    1) Grouble ��ü  ���� ���� ��� �����ϴ� ���� Group class�̴�.
//       �� Group Class�� �� Interface Class�� �ش��ϴ� ������ ����� ���� �� 
//       �����Ͽ� ����Ͽ��� �Ѵ�.
//
// 2. CGState::CProcess<TSTATE, TEVENT>�� �ٽ�! Function�� ��� ����.
//    1) Process()
//       Group���� Member ��ü�� ������ �Լ��̴�. �� �Լ��� abstract�Լ���
//      ��ӹ��� Group�� �ݵ�� ������ �� �־�� �Ѵ�.
//      �� �Լ��� virtual�� ������ ������ �� Group���� �ٸ� Group���� �Űܰ���
//      �ڵ����� Group���� ������ ���� ó���ϱ� ���ؼ��̴�.
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