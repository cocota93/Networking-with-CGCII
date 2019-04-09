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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CNoManage
 @brief		아무런 멤버 관리를 하지 않는 그룹 클래스이다.
 @todo		
 @ref		
 @details	\n
 가장 간단한 그룹으로 아무런 멤버에 대한 관리를 하지 않는다.
 멤버가 입장할 때 혹은 퇴장할때 OnMemberEntered와 같은 훅함수들만 호출된다.
 멤버의 입장과 퇴장 기능만 제공하고 그 왜에 모든 기능은 자체적으로 구현하고자 할때 많이 사용된다.

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
	//! @brief 입장에 락을 건다.
			void				LockEnter()								{ ICGReferenceable::AddRef(); m_csEnter.lock();}
	//! @brief 입장에 언락한다.
			void				UnlockEnter()							{	m_csEnter.unlock(); ICGReferenceable::Release();}
	//! @brief 입장 락을 얻는다.
			LOCKABLE<>&			GetEnterLock()							{	return m_csEnter;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief 입장을 허용했을 때 호출되는 함수
	virtual	void				OnEnableEnter()							{}
	//! @brief 입장이 금지했을 때 호출되는 함수
	virtual	void				OnDisableEnter()						{}

	//! @brief 새로운 멤버가 입장하기 직전 호출되는 함수 @param _pMember 입장할 '멤버 객체' @param _Msg 입장시 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 입장 성공 @return !eOBJECT_RESULT::SUCCESS 입장 실패
	virtual	eOBJECT_RESULT		OnMemberEntering(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/){ return eOBJECT_RESULT::SUCCESS;}
	//! @brief 새로운 멤버가 입장된 후 호출되는 함수 @param _pMember 입장한 '멤버 객체' @param _Msg 입장시 전달할 메시지
	virtual	void				OnMemberEntered(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/) {}

	//! @brief 멤버가 퇴장되기 직전에 호출되는 함수 @param _pMember 퇴장할 '멤버 객체' @return 전달할 값
	virtual	uintptr_t			OnMemberLeaving(TMEMBER* /*_pMember*/)	{ return 0;}
	//! @brief 멤버가 퇴장된 후 호출되는 함수 @param _pMember 퇴장한 '멤버 객체' @param _Result OnMemberLeaving()의 리턴 함수
	virtual	void				OnMemberLeaved(TMEMBER* /*_pMember*/, _In_ uintptr_t /*_Result*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief 입장 가능 여부를 설정하는 과정을 정의한다. @param _pEnable 입장 가능 여부 @return true 성공 @return false 실패
	virtual	bool				ProcessEnableEnter(bool _bEnable) override;

	//! @brief '멤버 객체'를 입장시킨다. @param _pMember 입장할 '멤버 객체' @param _Msg 입장할 때 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
	virtual	eOBJECT_RESULT		ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) override;

	//! @brief 그룹에서 멤버가 퇴장하는 처리를 정의한다. @param _pMember 퇴장할 '멤버 객체'
	virtual	void				ProcessLeaveMember(TMEMBERBASE* _pMember) override;

private:
	// 1) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);

private:
	// 2) Member의 Enter에 대한 Lock
			bool				m_bEnableEnter;
			LOCKABLE<>			m_csEnter;
};


}

#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupNoManage.inl"
