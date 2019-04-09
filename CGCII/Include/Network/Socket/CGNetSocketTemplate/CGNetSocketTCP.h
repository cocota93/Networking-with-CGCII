//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                      Network Socket Template Classes                      *
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
// CGNet::Socket::CTCP
//
// 1. CGNet::Socket::CTCP란!
//    1) TCP의 Send/Receive/Connect 등을 수행할 수 있는 Socket임. 
//    2) 반응속도가 크게 증가하였고 각종 Pending현상으로 인한 Failure를 거의 없앴다.
//
//
// 2. CGNet::Socket::CTCP의 핵심! Function의 기능 설명
//    1) 처리함수들 기본적인 I/O처리를 위한 처리함수들이다.
//					내부적으로 각종 I/O를 처리하기 위해 필요한 함수들에 대해서 정의한 것이다.
//    2) 진행함수들	Socket의 각 동작을 정의하는 함수들이다.
//    3) User함수들	재정의를 위해 만들어진 함수이다. 프로그래머가 이 부분들을 재정의
//					함을써 Socket을 게임에 맞게 만들게 된다.
//
//
// 3. 사용 함수들.
//
//    1) Socket관련...
//	     - SOCKET_STATUS		GetSocketState();
//       - SOCKADDR_CGNETWORK	 GetSocketAddress();
//       - SOCKADDR_CGNETWORK	 GetPeerAddress();
//
//    2) Connectable.
//	     - bool	Connect(LPCSOCKADDR _pSockAddr, int _nSockAddrLen);
//       - bool	Disconnect();
//
//    3) Sendable관련...
// 	     - bool	Send(const CCGBuffer& _Buffer);
//
//    4) Socket속성 관련.
//
//
// 4. 주요한 가로채기 함수.
//    정해진 이벤트가 발생시 해당 On~으로 시작하는 가상함수인 가로채기함수가 호출된다.
//    아래의 가로채기 함수가 가장 많이 사용되는 함수라고 할 수 있다.
//    각각 접속이 되었을때, 접속이 종료되었을 때, 메시지가 전달되었을 때 호출되는 
//    가로채기 함수이다. 대부분 이 함수들만 사용된다.
//
//    1) void OnConnect(CGNet::IO::IConnective* _pConnective)	      
//      Clinet에서 접속시도가 와서 접속이 성립 되었을 때 호출
//
//    2) void OnDisconnect(uint32_t _Reason)
//      접속된 Socket이 접속이 종료되었을 때 호출.
//
//    3) int OnMessage(CGMSG& _Msg)
//      새로운 메시지가 도착했을 때 호출.
//
//
// 5. 자주 사용되지 않는 가로채기 함수.
//    자주 사용되는 가로채기 함수 이외에 자주 사용되지는 않지만 정의된 가로채기
//    함수는 아래와 같다.
//    거의 재정의에 사용되지는 않지만 필요할 경우 재정의할 필요가 있다.
//
//    1) void OnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t _Reason)  
//       - 접속이 실패했을 경우 호출되는 가로채기 함수.
//       - Acceptor에서 동작하는 Socket의 경우 이 함수는 거의 호출되지 않는다.
//       - 일반적으로 Connector에 의해서 Connet를 시도한 쪽에서 접속 시도를 실패했을 경우
//         호출된다.
//
//	  2) void OnFailSending()
//       - 전송이 실패했을 때 호출되는 함수.
//
//    3) void OnPrepareSocket()
//       - Socket을 새로 할당받아 준비할 때 호출되는 함수이다.
//
//    4) void OnCloseSocket()
//       - Socket을 닫을 때 호출된다. 접속이 종료되는 것과는 다르다.
// 
//    5) void OnReceive(const CGD::buffer& _rWSABuffer, size_t _Transferred, const SOCKADDR_CGNETWORK* _pSockAddr)
//       - 데이터를 받았을 때 호출되는 함수.
//       - 새로 전송받은 데이터만 인자를 통해 전달되어진다.
//
//    6) void ProcessPreMessage(CGMSG& _Msg)
//       - 메시지가 전달되기 전에 호출되는 가로채기 함수이다.
//       - 메시지가 전달되기 전에 메시지를 변경하거나 처리해야할 내용이 있으면 여기서 처리한다.
//       - 이 함수가 호출된후 가로채기 함수인 OnMessage()함수가 호출된다.
//
//    7) bool ValidateReceivedMessage(const CGMSG& _Msg)
//       - Message가 제대로 된 것인가를 체크하는 가로채기 함수이다. 
//       - 전달되어온 메시지를 검사 후 정상적이면 true를 리턴하고 잘못되었다면 false를 리턴하도록 작성한다.
//       - 만약 false가 리턴되면 해당 Message의 처리는 중단되고 Exception처리 된다.
//
//
// ----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class THEAD=CGNet::IO::Packetable::PRIMITIVE<uint32_t>>
class CTCP :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Socket::NTCP,				// (@) Socket TCP
	public						CGNet::IO::Connectable::NTCP,			// (@) Connectable TCP
	public						CGNet::IO::Sendable::NTCPOverlapped,	// (@) Sendable TCP Overlapped
	public				 		CGNet::IO::SendRequest::NBase,			// (@) SendRequest Base
	public						CGNet::IO::Sender::NStreamGather,		// (@) Sender Stream (Gather Version)
	public						CGNet::IO::Receivable::NStream,			// (@) Receivable Stream
	public						CGNet::IO::Packetable::NStream<THEAD>,	// (@) Packetable Stream
	public						CGNet::IO::Messageable::NBase			// (@) Messageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCP()														{}
	virtual	~CTCP()														{}
};


}
}