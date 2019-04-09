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
class NCGServerService : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGServerService,
	public						CGNameable::NString,
	public						NCGObjectState,
	public						NCGStartable,
	public						NCGInitializable,
	public						NCGPausable,
	public						CGNet::IO::Messageable::NBase,
	virtual public				NCGDispatchable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NCGServerService(_In_opt_z_ const _CHAR* _strName);
			NCGServerService(_In_opt_z_ const _CHAR_SUB* _strName = nullptr);
	virtual ~NCGServerService();


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 설정 값을 설정하기 위한 함수
	virtual	void				OnServiceSetting(CGMSG_CONTEXT& /*_Msg*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 초기화 절차를 정의한다. @param _MSg 초기활 할 때 전달된 메시지
	virtual	void				ProcessInitialize(CGMSG_CONTEXT& _Msg) override;
	//! @brief 파괴 절차를 정의한다.
	virtual	void				ProcessDestroy() override;
	//! @brief 시작시 처리해야할 내용을 정의한다. @param _Msg 시작시 전달할 인자
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg) override;
	//! @brief 중지시 처리해야할 내용을 정의한다.
	virtual	void				ProcessStop() override;
	//! @brief 잠시 중지할 때 처리해야할 내용을 정의한다. @param _Msg 전달할 인자
	virtual	void				ProcessPause() override;
	//! @brief 중지를 해제할 때 처리해야할 내용을 정의한다.
	virtual	void				ProcessContinue() override;


	//! @brief 자식 노드의 초기화 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	//! @brief 자식 노드의 시작 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;

	//! @brief 상태가 바뀌었을 때의 처리 @param _eStatus 바꿀 새로운 상태
	virtual	void				ProcessStateChanged(eOBJECT_STATE _eStatus) override;
};
