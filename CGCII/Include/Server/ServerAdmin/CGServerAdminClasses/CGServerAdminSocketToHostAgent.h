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
// CGServerAdmin::CServerToHostAgent (Server -> HostAgent)
//
// 1. CGServerAdmin::CTCPAdminClient란!
//    1) Send/Receive/Connect 등을 수행할 수 있는 Socket임. 
//    2) 기본적으로 재사용을 위한 Recycle처리가 들어 있음.
//    3) 소량의 연결처리르 전제로 하였으므로 Socket Manager와 Socket Pool 등은
//       지원하지 않는다.
//    4) 그래도 과거에 비해 반응속도가 크게 증가하였고 각종 Pending현상으로 인한
//       Failure를 거의 없앴다.
//
//
// 2. CGServerAdmin의 핵심! Function의 기능 설명
//    1) 처리함수들 기본적인 I/O처리를 위한 처리함수들이다.
//					내부적으로 각종 I/O를 처리하기 위해 필요한 함수들에 대해서 정의한 것이다.
//    2) 진행함수들	Socket의 각 동작을 정의하는 함수들이다.
//    3) User함수들	재정의를 위해 만들어진 함수이다. 프로그래머가 이 부분들을 재정의
//					함을써 Socket을 게임에 맞게 만들게 된다.
//
// 3. 주의 사항
//  Run을 항상 일정 시간마다 실행을 시켜 I/O에 대한 처리를 반듯이 해주어야 한다.
//
// ----------------------------------------------------------------------------
namespace CGServerAdmin
{

class CSocketToHostAgent : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Connector::NTCPReconnect,	// (@) Connector
	public						CGNet::Socket::CTCP<>,					// (@) Socket
	public						NCGDispatchable,						// (@) Dispatchable
	public						CGSchedulable::NExecutable,				// (@) Scheduable
	public						NCGSingleton<CSocketToHostAgent>		// (@) singleton
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			CSocketToHostAgent();
	virtual ~CSocketToHostAgent();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Connect함수
			BOOL				ConnectToHostAgent();

	// 2) HostInfo Set/Get
			const CGServerAdmin::HOST_INFO&	GetHostInfo() const			{	return m_infoHost;}
			void				SetHostInfo(const CGServerAdmin::HOST_INFO& _rHostInfo);
		
	// 3) Server Info
			const SERVER_INFO&	GetServerInfo() const					{	return m_infoServer;}
			void				SetServerInfo(const SERVER_INFO& p_rServerInfo)	{	m_infoServer=p_rServerInfo;}

	// 4) Server Setting Info
			const SERVER_SETTING& GetServerSettingInfo() const			{	return m_infoServerSetting;}
			void				SetServerSettingInfo(const SERVER_SETTING& _rServerSettingInfo, const CCGBuffer& _bufParameters);

	// 5) Admin Server Info
			void				SetAdminServerInfo(const CGServerAdmin::LOGIN_ACCEPT& p_rLoginAccept);



// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
public:
	// 1) 접속이 되었을 때 불려지는 함수.
	virtual void				OnConnect(CGNet::IO::IConnective* _pConnective);
	virtual void				OnDisconnect(uint32_t _Reason);

	// 2) 인증이 되었을 때 불려지는 함수.
	virtual void				OnCertify()								{}


// ****************************************************************************
// Message functions) 
// ----------------------------------------------------------------------------
protected:
	// Declare CGMessage Map)
	DECLARE_CGMESSAGE_MAP

	// 1) Packet을 받았을 때 불려지는 함수.
	virtual int					OnMessage(CGMSG& _Msg);

	// 2) 각Message에 따라 실행될 Message Fuctions
			int					OnMessage_SendHostInfo			(CGNETMSG& _Msg);
			int					OnMessage_SendServerSettingInfo	(CGNETMSG& _Msg);

			int					OnMessage_ExceptionDump			(CGMSG_DUMP& _Msg);

public:
			void				SendMessage_SendServerInfo();
			void				SendMessage_AdminUpdateServiceStatus(eOBJECT_STATE _eStatus);

			CCGBuffer			GetMessage_SendinfoSystem();
			CCGBuffer			GetMessage_SendServerInfo();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Host Info
			HOST_INFO			m_infoHost;

	// 2) Server Info (실제 적용된 정보)
			SERVER_INFO			m_infoServer;

	// 3) Admin Server에서 설정한 정보.
			SERVER_SETTING		m_infoServerSetting;

			CCGBuffer			m_bufferParameters[2];

	// 4) Admin Client
			LOCKABLE<list<CGPTR<ICGServerService>>>	m_listService;

protected:
	// 1) Execute함수임...
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


}