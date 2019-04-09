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
// CGNet::IO::Connective::IAcceptor
//
// 1. CGNet::IO::Connective::IAcceptor는~
//     Acceptor의 가장 Base class.
//
// 2. Process함수.
//    1) ProcessCompleteAccept()
//       - Accept가 들어 왔을 때 Accept를 처리하는 과정을 정의하는 함수이다.
//       - 일반적으로 Accept가 완료되면 ProcessExecute의 수행과정중 이 함수를 
//         호출한다.
//       - 이 과정에서는 접속된 Socket의 접속과 관련된 정보처리를 해주며
//       - 해당 Socket의 ProcessCompletConnect()함수를 호출해준다.
//       - 접속으로 하나의 Socket이 소진 된만큼 새로운 Socket을 생성하여 새로
//         Accept를 걸어준다.
//
//	  2) Start()/Stop()
//		 - Start()함수를 호출하면 Accept받을 준비를 한다.
//       - Stop()함수를 호출하면 더이상 Accept를 받지 않는다.
//
//    3) Accept
//       - Accept를 거는 함수로 새로운 Socket을 할당받아 AcceptEX를 걸어주는 역할을 한다.
//
//    4) ResetAcceptor
//       - Acceptor를 초기화할 때 호출되는 함수이다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connective
{

class IAcceptor : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISocket,						// (I) Socket
	virtual public				ICGStartable,							// (I) Startable
	virtual public				ICGObjectState,							// (I) Object Status
	virtual	public				CGNet::IO::IConnective,					// (I) IConnective
	virtual	public				IConnectableManager						// (I) IManagerConnectable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Open(=Listen)
			bool				Start(_In_ const SOCKADDR_CGNETWORK& _addrListen, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);
			bool				Start(_In_ u_short _Port, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);
			bool				Start(_In_z_ const char* _pServiceName, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);
			bool				Start(_In_z_ const wchar_t* _pServiceName, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);

	// 3) Accept
	virtual	bool				RequestAccept() PURE;
	virtual	void				ResetAcceptor() PURE;

	// 3) Enable/Disable
	virtual bool				Enable() PURE;
	virtual bool				Disable() PURE;


// ****************************************************************************
// Protected)
// ----------------------------------------------------------------------------
protected:
			void				PrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET)		{ CGNet::IO::ISocket::PrepareSocket(_AddressFamily); }
			bool				CloseSocket(_In_ uint32_t _Reason = SOCKET_REASON_NONE) { return CGNet::IO::ISocket::CloseSocket(_Reason);}

			eSOCKET_STATE		SetSocketState(_In_ eSOCKET_STATE _Status) { return CGNet::IO::ISocket::SetSocketState(_Status); }
			bool				SetSocketStateIf(_In_ eSOCKET_STATE _StatusComperand, _In_ eSOCKET_STATE _StatusNew) { return CGNet::IO::ISocket::SetSocketStateIf(_StatusComperand, _StatusNew); }
			bool				ExchangeSocketStateIf(_In_ eSOCKET_STATE& _StatusComperand, _In_ eSOCKET_STATE _StatusNew) { return CGNet::IO::ISocket::ExchangeSocketStateIf(_StatusComperand, _StatusNew); }

			void				SetSocketReason(_In_ uint32_t _Reason)	{ CGNet::IO::ISocket::SetSocketReason(_Reason); }
};


}
}
}