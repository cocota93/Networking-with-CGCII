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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// CGServerAdmin::CServerToHostAgent (Server -> HostAgent)
//
// 1. CGServerAdmin::CTCPAdminClient��!
//    1) Send/Receive/Connect ���� ������ �� �ִ� Socket��. 
//    2) �⺻������ ������ ���� Recycleó���� ��� ����.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� Socket Manager�� Socket Pool ����
//       �������� �ʴ´�.
//    4) �׷��� ���ſ� ���� �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ����
//       Failure�� ���� ���ݴ�.
//
//
// 2. CGServerAdmin�� �ٽ�! Function�� ��� ����
//    1) ó���Լ��� �⺻���� I/Oó���� ���� ó���Լ����̴�.
//					���������� ���� I/O�� ó���ϱ� ���� �ʿ��� �Լ��鿡 ���ؼ� ������ ���̴�.
//    2) �����Լ���	Socket�� �� ������ �����ϴ� �Լ����̴�.
//    3) User�Լ���	�����Ǹ� ���� ������� �Լ��̴�. ���α׷��Ӱ� �� �κе��� ������
//					������ Socket�� ���ӿ� �°� ����� �ȴ�.
//
// 3. ���� ����
//  Run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
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
	// 1) Connect�Լ�
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
	// 1) ������ �Ǿ��� �� �ҷ����� �Լ�.
	virtual void				OnConnect(CGNet::IO::IConnective* _pConnective);
	virtual void				OnDisconnect(uint32_t _Reason);

	// 2) ������ �Ǿ��� �� �ҷ����� �Լ�.
	virtual void				OnCertify()								{}


// ****************************************************************************
// Message functions) 
// ----------------------------------------------------------------------------
protected:
	// Declare CGMessage Map)
	DECLARE_CGMESSAGE_MAP

	// 1) Packet�� �޾��� �� �ҷ����� �Լ�.
	virtual int					OnMessage(CGMSG& _Msg);

	// 2) ��Message�� ���� ����� Message Fuctions
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

	// 2) Server Info (���� ����� ����)
			SERVER_INFO			m_infoServer;

	// 3) Admin Server���� ������ ����.
			SERVER_SETTING		m_infoServerSetting;

			CCGBuffer			m_bufferParameters[2];

	// 4) Admin Client
			LOCKABLE<list<CGPTR<ICGServerService>>>	m_listService;

protected:
	// 1) Execute�Լ���...
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


}