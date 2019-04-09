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
//-----------------------------------------------------------------------------
//
// CGServerService::NApplication
//
// 1. CGServerService::NApplication란!
//    1) CGCII Admin Server Application 제작을 위해 정의된 Class
//
//
//-----------------------------------------------------------------------------
namespace CGServerService
{

class NApplication :
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
protected:
			NApplication();
	virtual	~NApplication();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Start/Stop/Pause/Continue
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override;
	virtual	bool				Stop() override;
	virtual	bool				Pause() override;
	virtual	bool				Continue() override;

	// 2) Status
	virtual	eOBJECT_STATE		GetObjectState() const override ;
	virtual	eOBJECT_STATE		SetObjectState(_In_ eOBJECT_STATE _eStatus) NOEXCEPT override;
	virtual	bool				SetObjectStateIf(_In_ eOBJECT_STATE _eStatusCompare, _In_ eOBJECT_STATE _eStatus) NOEXCEPT  override;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	// 1) Setting
	virtual	void				OnServiceSetting(CGMSG_CONTEXT& /*_Msg*/)	{}

	// 2) Init/Destroy (from NCGInitializable)
	virtual	void				OnInitializing(CGMSG_CONTEXT& /*_Msg*/) override{}
	virtual	void				OnInitialize(CGMSG_CONTEXT& /*_Msg*/) override	{}
	virtual	void				OnDestroying() override					{}
	virtual	void				OnDestroy() override					{}

	// 3) Start/Stop (from NCGStartable)
	virtual	void				OnStarting(CGMSG_CONTEXT& /*_Msg*/) override	{}
	virtual	void				OnStart(CGMSG_CONTEXT& /*_Msg*/) override		{}
	virtual	void				OnStopping() override					{}
	virtual	void				OnStop() override						{}

	// 4) Pause/Continue (from NCGPausable)
	virtual	void				OnPausing() override					{}
	virtual	void				OnPause() override						{}
	virtual	void				OnContinuing() override					{}
	virtual	void				OnContinue() override					{}

	// 5) Service Control
	virtual	void				OnProcessInterrogate			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessShutdown				(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessParamChange			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessNetBindAdd				(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessNetBindRemove			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessNetBindEnable			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessNetBindDisable			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessDeviceEvent			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessHardwareProfileChage	(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessPowerEvent				(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessSessionChange			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessPreShutdown			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessTimeChange				(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}
	virtual	void				OnProcessTriggerEvent			(uint32_t /*_dwEventType*/, void* /*_lpEventData*/, void* /*_lpContext*/)	{}

	// 6) Message...
	virtual int					OnMessage(CGMSG& /*_Msg*/)				{	return 0;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 초기화 절차를 정의한다. @param _MSg 초기활 할 때 전달된 메시지
	virtual	void				ProcessInitialize(CGMSG_CONTEXT& _Msg);
	//! @brief 파괴 절차를 정의한다.
	virtual	void				ProcessDestroy();
	//! @brief 시작시 처리해야할 내용을 정의한다. @param _Msg 시작시 전달할 인자
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg);
	//! @brief 중지시 처리해야할 내용을 정의한다.
	virtual	void				ProcessStop();

	//! @brief 자식 노드의 초기화 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	//! @brief 자식 노드의 시작 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;

protected:
	// 1) Service Control
	virtual	void				ProcessInterrogate				(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessShutdown					(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessParamChange				(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessNetBindAdd				(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessNetBindRemove			(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessNetBindEnable			(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessNetBindDisable			(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessDeviceEvent				(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessHardwareProfileChage		(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessPowerEvent				(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessSessionChange			(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessPreShutdown				(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessTimeChange				(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessTriggerEvent				(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);

	// 2) Service Process
	virtual	uint32_t			ProcessService_Main				(int _argc, _CHAR** _pargv, _In_ __callback LPHANDLER_FUNCTION_EX _lpHandlerProc);
	virtual	uint32_t			ProcessService_Handler			(uint32_t _dwControl, uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessService_Start			(CGMSG_CONTEXT& _Msg);
	virtual	void				ProcessService_Stop				();
	virtual	void				ProcessService_Pause			(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessService_Continue			(uint32_t _dwEventType, void* _lpEventData, void* _lpContext);
	virtual	void				ProcessService_Run				();

	// 3) Status
	virtual	void				ProcessStateChanged				(eOBJECT_STATE) {}

protected:
	// Declare) 
			CGOBJ<CGAPI::CServerStatusHandle>	m_hServerStatus;
			ATOMIC<eOBJECT_STATE>		m_statusObject;
};


}