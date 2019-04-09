//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// ----------------------------------------------------------------------------
//
// NCGServerService
//
// 1. Service는 Server를 동작시키기 위한 서비스를 객체화한 것이다.
//    1) Service의 가장 기본적인 사항을 제작해 놓은 Service 클래스이다.
//    2) 
//
//
// ----------------------------------------------------------------------------
class CCGServerService : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NCGServerService						//     CGServerService
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CCGServerService(_In_opt_z_ const _CHAR* _strName);
			CCGServerService(_In_opt_z_ const _CHAR_SUB* _strName = nullptr);
	virtual ~CCGServerService();


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
	//! @brief 설정 값을 설정하기 위한 함수
	virtual	void				OnServiceSetting(CGMSG_CONTEXT& /*_Msg*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Status가 변경되었을 때 호출되는 함수.
	virtual	void				ProcessStateChanged(eOBJECT_STATE _eStatus) override;

	// 2) Init/Destroy
	virtual	void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	virtual	void				_ProcessDestroying() override;

	//! @brief 자식 노드의 시작 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;

	// 3) Open/Close
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg) override;
	virtual	void				ProcessStop() override;
	virtual	void				ProcessPause() override;
	virtual	void				ProcessContinue() override;

protected:
	// 4) Admin System을 위한 Socket들
			CGPTR<CGServerAdmin::CSocketToHostAgent>	m_psocketHostAgent;
};
