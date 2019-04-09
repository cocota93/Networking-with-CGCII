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
// CGNet::IO::Connector::NTCP (TCP 연결자)
//
// 1. CGNet::IO::Connector::NTCP이란!
//    1) TCP Socket을 Client 입장에서 접속을...
//    2) 
//    3) 기본적으로 ICGNameable을 상속받아 이름을 설정할 수 있다.
//
// 2. 중요 함수.
//    1) 일반적인 사용은 CGNet::IO::IConnector에 정의된 다양한 형태의 Connect(...)
//		 함수를 활용한다.
//    2) 만약 Connect를 요청했을 때 처리되어야 하는 것이 있다면 다음의 함수를
//       재정의하여 구현할 수 있다.
//
//       virtual void OnRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _paddrPeer);
//
//    주의) ICGExecutable을 상속받아 처리하므로 이 클래스를 상속받은 클래스에서
//          ProcessExecute()를 재정의하면 접속처리가 되지 않을 수 있다.
// 
// 3. Initialize/Start String
//
//	  ["NAME"]["AddressFormat"]		Address Format ("IPv4", "IPv6", "IPv6prefer", "IPv4prefer", "default") (Optional:Default="IPv4")
//    ["NAME"]["Address"]			접속할 주소
//	  ["NAME"]["Port"]				접속할 포트
//
//    예)  객체명이 "NAME"이라고 한다면....
//
//		   CGMSG msgContext;
//         msgContext.Setting["NAME"]["AddressFormat"]	  = "IPv6";	// "IPv4", "IPv4Prefer", "IPv6", "IPv6Prefer"
//         msgContext.Setting["NAME"]["Address"]		 = "192.168.0.100";
//         msgContext.Setting["NAME"]["Port"]			 = 20000;
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connector
{

class NTCP :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IConnector,
	virtual protected			CGNet::IO::IConnectable,
	public						CGNameable::NString,
	public						CGNet::IO::Binder::NTCP,
	public						NCGObjectState,
	public						NCGStartable,
	public						NCGInitializable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NTCP();
			NTCP(const char* _strName);
			NTCP(const wchar_t* _strName);
	virtual	~NTCP();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Start
			bool				Start(CGMSG_CONTEXT& _Msg) override																								{ return NCGStartable::Start(_Msg);}
			bool				Start()																															{ return Connect();}
			bool				Start(_In_ const SOCKADDR_CGNETWORK& _addrPeer)																					{ return Connect(_addrPeer);}
			bool				Start(_In_ const SOCKADDR_IN& _addrPeer)																						{ return Connect(_addrPeer);}
			bool				Start(_In_ const SOCKADDR_IN6& _addrPeer)																						{ return Connect(_addrPeer);}
			bool				Start(_In_ LPCSOCKADDR _addrPeer, _In_ int _addrLength)																			{ return Connect(_addrPeer, _addrLength);}

			bool				Start(_In_z_ const _CHAR* _pszaddrPeer, _In_ uint16_t _portPeer=0, ADDRESS_FAMILY _afPriority=AF_INET)							{ return Connect(_pszaddrPeer, _portPeer, _afPriority);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_ uint16_t _portPeer=0, ADDRESS_FAMILY _afPriority=AF_INET)						{ return Connect(_pszaddrPeer, _portPeer, _afPriority);}
			bool				Start(_In_z_ const _CHAR* _pszaddrPeer, _In_z_ const _CHAR* _strService, ADDRESS_FAMILY _afPriority=AF_INET)					{ return Connect(_pszaddrPeer, _strService, _afPriority);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_z_ const _CHAR_SUB* _strService, ADDRESS_FAMILY _afPriority=AF_INET)			{ return Connect(_pszaddrPeer, _strService, _afPriority);}

			bool				Start(_In_ const SOCKADDR_CGNETWORK& _addrPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)									{ return Connect(_addrPeer, _paddrBind); }
			bool				Start(_In_z_ const _CHAR* _pszaddrPeer, _In_ uint16_t _portPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)					{ return Connect(_pszaddrPeer, _portPeer, _paddrBind);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_ uint16_t _portPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)				{ return Connect(_pszaddrPeer, _portPeer, _paddrBind);}
			bool				Start(_In_z_ const _CHAR* _pszaddrPeer, _In_z_ const _CHAR* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)			{ return Connect(_pszaddrPeer, _strService, _paddrBind);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_z_ const _CHAR_SUB* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)	{ return Connect(_pszaddrPeer, _strService, _paddrBind);}

			eOBJECT_RESULT		Wait(TICK::duration _durationWait=TICK::seconds(30));


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	//! @brief 접속을 요청했을 때 호출된다. @param _SockAddr 접속을 시도할 주소
	virtual void				OnRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* /*_paddrPeer*/) {}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	//! @brief Connect할 때 부르는 함수이다.
	virtual	bool				ProcessRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _paddrPeer) override;
	//! @brief Reset할때 호출하는 함수.
	virtual	void				ResetConnector() override;

	//! @brief 시작시 처리해야할 내용을 정의한다. @param _Msg 시작시 전달할 인자
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg) override;
	//! @brief 중지시 처리해야할 내용을 정의한다.
	virtual	void				ProcessStop() override;

	//! @brief 자식 노드의 시작 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;
	//! @brief 자식 노드의 종료 처리가 진행되기 전 처리할 내용을 정의하는 함수
	virtual void				_ProcessStopping() override;

	//! @brief 접속처리과정을 정의한다.
	virtual	void				ProcessConnect(_In_ uintptr_t _Return);

public:
			eOBJECT_RESULT		m_resultConnecting;
};


}
}
}