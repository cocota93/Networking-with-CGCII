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
// CGServerAdmin::CSocketTCPAdmin
//
//
// ----------------------------------------------------------------------------
namespace CGServerAdmin
{

class CSocketTCPAdmin :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public					CGNet::Socket::CTCP<>						// (@) TCP Socket
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CSocketTCPAdmin();
	virtual ~CSocketTCPAdmin();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			const CGServerAdmin::SERVER_INFO&	GetServerInfo() const;


			eOBJECT_STATE	SetServerState(eOBJECT_STATE _State);
			eOBJECT_STATE	SetServerStateIf(eOBJECT_STATE _State, eOBJECT_STATE _StateCompare);
			eOBJECT_STATE	GetServerState() const;


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) 일반적인 On함수.
	virtual void			OnConnect(CGNet::IO::IConnective* _pConnective);
	virtual void			OnDisconnect(uint32_t _Reason);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// Declare CGMessagemap)
	DECLARE_CGMESSAGE_MAP

	// 1) Packet을 받았을 때 불려지는 함수.
	virtual int				OnMessage(CGMSG& _Msg);

protected:
	// 2) 각Message에 따라 실행될 Message Fuctions
			int				OnMessage_AdminCertified(CGNETMSG& _Msg);
			int				OnMessage_TestB(CGNETMSG& _Msg);
			int				OnMessage_TestC(CGNETMSG& _Msg);
			int				OnMessage_TestD(CGNETMSG& _Msg);
			int				OnMessage_TestE(CGNETMSG& _Msg);

public:
	// 3) Send 함수들
			void			SendMessage_ServerInfo();
			void			SendMessage_AcceptorInfo();
			void			SendMessage_UDPInfo();
			void			SendMessage_TrafficInfo();
			void			SendMessage_EventInfo();
			//void			SendMessage_ServerState();

protected:
			CGServerAdmin::SERVER_INFO	m_ServerInfo;
};


}