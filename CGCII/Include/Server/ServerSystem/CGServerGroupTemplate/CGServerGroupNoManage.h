//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Group Template Classes                           *
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

namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CNoManage
 @brief		�ƹ��� ��� ������ ���� �ʴ� �׷� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ���� ������ �׷����� �ƹ��� ����� ���� ������ ���� �ʴ´�.
 ����� ������ �� Ȥ�� �����Ҷ� OnMemberEntered�� ���� ���Լ��鸸 ȣ��ȴ�.
 ����� ����� ���� ��ɸ� �����ϰ� �� �ֿ� ��� ����� ��ü������ �����ϰ��� �Ҷ� ���� ���ȴ�.

*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBERBASE=_TMEMBER>
class CNoManage : 
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				ICGServerGroup<_TMEMBERBASE>			//     Group Base
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TMEMBER			TMEMBER;
	typedef	_TMEMBERBASE		TMEMBERBASE;


// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			CNoManage();
	virtual	~CNoManage();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief ���忡 ���� �Ǵ�.
			void				LockEnter()								{ ICGReferenceable::AddRef(); m_csEnter.lock();}
	//! @brief ���忡 ����Ѵ�.
			void				UnlockEnter()							{	m_csEnter.unlock(); ICGReferenceable::Release();}
	//! @brief ���� ���� ��´�.
			LOCKABLE<>&			GetEnterLock()							{	return m_csEnter;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief ������ ������� �� ȣ��Ǵ� �Լ�
	virtual	void				OnEnableEnter()							{}
	//! @brief ������ �������� �� ȣ��Ǵ� �Լ�
	virtual	void				OnDisableEnter()						{}

	//! @brief ���ο� ����� �����ϱ� ���� ȣ��Ǵ� �Լ� @param _pMember ������ '��� ��ü' @param _Msg ����� ������ �޽��� @return eOBJECT_RESULT::SUCCESS ���� ���� @return !eOBJECT_RESULT::SUCCESS ���� ����
	virtual	eOBJECT_RESULT		OnMemberEntering(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/){ return eOBJECT_RESULT::SUCCESS;}
	//! @brief ���ο� ����� ����� �� ȣ��Ǵ� �Լ� @param _pMember ������ '��� ��ü' @param _Msg ����� ������ �޽���
	virtual	void				OnMemberEntered(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/) {}

	//! @brief ����� ����Ǳ� ������ ȣ��Ǵ� �Լ� @param _pMember ������ '��� ��ü' @return ������ ��
	virtual	uintptr_t			OnMemberLeaving(TMEMBER* /*_pMember*/)	{ return 0;}
	//! @brief ����� ����� �� ȣ��Ǵ� �Լ� @param _pMember ������ '��� ��ü' @param _Result OnMemberLeaving()�� ���� �Լ�
	virtual	void				OnMemberLeaved(TMEMBER* /*_pMember*/, _In_ uintptr_t /*_Result*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief ���� ���� ���θ� �����ϴ� ������ �����Ѵ�. @param _pEnable ���� ���� ���� @return true ���� @return false ����
	virtual	bool				ProcessEnableEnter(bool _bEnable) override;

	//! @brief '��� ��ü'�� �����Ų��. @param _pMember ������ '��� ��ü' @param _Msg ������ �� ������ �޽��� @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
	virtual	eOBJECT_RESULT		ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) override;

	//! @brief �׷쿡�� ����� �����ϴ� ó���� �����Ѵ�. @param _pMember ������ '��� ��ü'
	virtual	void				ProcessLeaveMember(TMEMBERBASE* _pMember) override;

private:
	// 1) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);

private:
	// 2) Member�� Enter�� ���� Lock
			bool				m_bEnableEnter;
			LOCKABLE<>			m_csEnter;
};


}

#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupNoManage.inl"
