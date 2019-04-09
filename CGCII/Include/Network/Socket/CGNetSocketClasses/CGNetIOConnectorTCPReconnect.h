//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Network Socket Classes                           *
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
// CGNet::IO::Connector::NTCPReconnect (자동재접속 기능을 가진 TCP 연결자)
//
// 1. CGNet::IO::Connective::NTCPReconnect이란!
//    1) 자동 재접속 기능이 있는 Connector이다.
//    2) CGNet::IO::Connector::NTCP을 상속받아 접속 종료시 자동 재접속 기능을 추가
//       한 것이다.
//    3) CGNet::IO::IConnectable과 같이 다중상속받아서 사용하도록 설계되었다.
//
// 2. 핵심 함수들.
//    1) 재접속은 기본적으로 Connect()를 했을 때 하나의 주소에만 이루어진다.
//    2) 필요에 따라 여러 주소로 재접속을 수행할 수 있다.
//       - 접속이 종료되면 등록된 주소들에 차례대로 접속요구를 수행하게 된다.
//
//		 - 접속할 주소를 추가하고 삭제할 수 있다.
//			bool AddPeerAddress((LPCSOCKADDR _paddrPeer);
//			bool RemovePeerAddress(LPCSOCKADDR _paddrPeer);
//          void RemoveAllPeerAddress();
//
//    3) 접속은 Connect함수를 사용하여 수행한다.
//    4) Address를 넣지 않을 경우 등록된 Peer주소로 접속을 시도한다.
//    5) 아래의 함수를 사용하여  재접속 기능을 켜거나 끌 수 있다.
//       
//       void EnableReconnect(bool _bEnable=true);
//       void DisableReconnect();
//
//       또 아래의 함수를 사용하여 재접속 기능의 동작여부를 확인할 수 있다.
//
//       bool IsEnable() const
//
//    6) 아래의 함수를  사용하여 재접속 시도  시간을 조절하거나 얻을 수 있다.
//       재접속 시도는 마지막 접속을 성공한 시점에서 부터 계산이 된다.
//       따라서 접속한 이후 재접속 시도 시간 이후에 접속이 종료되었을
//       경우 바로 재접속이 수행된다.
//
//       void			SetReconnectInterval(TICK::duration p_tick);
//       TICK::duration	GetReconnectInterval() const;
//
//    7) 재접속 시 마다 어떠한 기능이 수행되어야 한다면 다음 virtual함수를
//       재정의하여 기능을 추가할 수 있다.
//
//       virtual void OnRequestReconnect(CGNet::IO::IConnective* _pConnective);
// 
//    
//    주의) 접속을 종료할 때는 반드시 아래와 같이 DisableReconnect()함수를 
//          호출하여 재접속 접속 종료후 다시 접속을 수행할 수 있다.
//
//           pSocket->DisableReconnection();
//           pSocket->CloseSocket();
//
// 3. Initialize/Start String
//
//	  "[Name]/AddressFormat"		Address Format ("IPv4", "IPv6Prefer", "IPv6", "IPv4Prefer", "default")
//    "[Name]/Address"				접속할 주소(주소와 포트 모두 포함)
//	  "[Name]/Port"					접속할 포트
//	  "[Name]/EnableReconnection"	재접속을 활성화한다.
//	  "[Name]/DisableReconnection"	재접속을 비활성화한다.
//	  "[Name]/Reconnection"			재접속 상태를 설정한다.(true/false)
//
//    예)  객체명이 "NAME"이라고 한다면....
//
//		   CGMSG msgContext;
//         msgContext.Setting["NAME"]["AddressFormat"]		  = "IPv6";	// "IPv4", "IPv4Prefer", "IPv6", "IPv6Prefer"
//         msgContext.Setting["NAME"]["Address"]			  = "192.168.0.100";
//         msgContext.Setting["NAME"]["Port"]				  = 20000;
//         msgContext.Setting["NAME"]["Reconnection"]		  = "true";	// "true", "false", "default"
//         msgContext.Setting["NAME"]["ReconnectionInterval"] = 1000;	// millisecond
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connector
{

class NTCPReconnect :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Connector::NTCP,				// (I) Socket
	virtual public				CGNet::IO::IConnective					// (I) Connector
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NTCPReconnect();
			NTCPReconnect(const char* _strName);
			NTCPReconnect(const wchar_t* _strName);
	virtual	~NTCPReconnect();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Start
			bool				Start(CGMSG_CONTEXT& _Msg) override													{ return NCGStartable::Start(_Msg);}
			bool				Start()																				{ return Connect();}
			bool				Start(_In_ const SOCKADDR_CGNETWORK& _addrHost)										{ return Connect(_addrHost);}

			bool				Start(_In_z_ const _CHAR* _pszHostAddress, _In_ uint16_t _nHostPort=0)				{ return Connect(_pszHostAddress, _nHostPort);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_ uint16_t _nHostPort=0)			{ return Connect(_pszHostAddress, _nHostPort);}
			bool				Start(_In_z_ const _CHAR* _pszHostAddress, _In_z_ const _CHAR* _strService)			{ return Connect(_pszHostAddress, _strService);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_z_ const _CHAR_SUB* _strService)	{ return Connect(_pszHostAddress, _strService);}

			bool				Start(_In_z_ const _CHAR* _pszHostAddress, _In_ uint16_t _nHostPort, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)					{ return Connect(_pszHostAddress, _nHostPort, _pSockAddr);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_ uint16_t _nHostPort, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)				{ return Connect(_pszHostAddress, _nHostPort, _pSockAddr);}
			bool				Start(_In_z_ const _CHAR* _pszHostAddress, _In_z_ const _CHAR* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)			{ return Connect(_pszHostAddress, _strService, _pSockAddr);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_z_ const _CHAR_SUB* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)	{ return Connect(_pszHostAddress, _strService, _pSockAddr);}

	// 2) 재접속할 주소를 추가/삭제/모두삭제 한다.(여러 개의 Address가 존재시 돌아가며 접속된다.)
			bool				AddPeerAddress(_In_ const SOCKADDR_CGNETWORK& _rPeerAddress);
			bool				RemovePeerAddress(_In_ const SOCKADDR_CGNETWORK& _rPeerAddress);
			void				RemoveAllPeerAddress();
	   
	// 3) 자동 재접속 Enable/Disable함수.
			void				EnableReconnect(_In_ bool _bEnable = true)	{ m_bReconnectEnable = _bEnable; }
			void				DisableReconnect()							{	m_bReconnectEnable=false;}

	// 4) Enable함수.
	virtual	bool				IsEnable() const override					{ return IsReconnectEnable();}
			bool				IsReconnectEnable() const					{ return m_bReconnectEnable; }

	// 5) 재접속 간격 (단위는 1tick(1ms)이며 기본값은 10초(10000)이다.)
			void				SetReconnectInterval(_In_ TICK::duration p_tick){ m_tickReconnectionInterval = p_tick; }
			TICK::duration		GetReconnectInterval() const				{	return m_tickReconnectionInterval;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) 재접속을 시도하기 전 호출되는 함수.
	virtual	void				OnRequestReconnect(CGNet::IO::IConnective* /*_pConnective*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) RequestConnect
	virtual	bool				ProcessRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _addrPeer) override;

	// 2) ProcessConnect
	virtual	void				ProcessConnect(_In_ uintptr_t _Return) override;

	// 3) Connective
	virtual	void				ProcessConnectiveConnect(_In_ CGNet::IO::IConnectable* _pConnectable, _In_ uintptr_t _Return) override;
	virtual	void				ProcessConnectiveDisconnect(_In_ CGNet::IO::IConnectable* _pConnectable) override;

	// 4) Start/Stop
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;
	virtual void				_ProcessStopping() override;

	// 5) Reconnect를 수행하는 함수이다.
			void				ProcessWaitReconnect();
			void				RequestReconnect();
			void				CancelReconnector();
	
protected:
	// 1) Address List
			LOCKABLE<circular_list<SOCKADDR_CGNETWORK>>	m_listPeerAddress;
			circular_list<SOCKADDR_CGNETWORK>::const_iterator	m_iterNowPeerAddress;

	// 2) Enable
			bool				m_bReconnectEnable;
			TICK::duration		m_tickReconnectionInterval;

	// 3) 접속종료된 Tick (Dealy가 있는 재접속을 위해 사용한다.)
			TICK::time_point	m_tickDisconnected;

	// Definition) 
			class CReconnector;

	// 4) Reconnector
			CGPTR<CReconnector>	m_pReconnector;
			bool				m_bReconnecting;
			LOCKABLE<>			m_csReconnector;
};


}
}
}