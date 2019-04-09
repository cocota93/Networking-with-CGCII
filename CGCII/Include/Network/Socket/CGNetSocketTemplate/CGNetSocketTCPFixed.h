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
//    1) TCP의 Send/Receive 등을 수행할 수 있는 Socket임. 
//    2) 반응속도가 크게 증가하였고 각종 Pending현상으로 인한 Failure를 거의 없앴다.
//
//
// 2. CGNet::Socket::CTCP의 핵심! Function의 기능 설명
//    1) 진행함수(Process~)들 Socket의 각 동작을 정의하는 함수들이다.
//    2) 가로채기함수(On~)들은 재정의를 위해 만들어진 함수이다. 프로그래머가 이 
//		 부분들을 재정의함을써 Socket에 필요한 기능을 추가할 수 있다.
//
//
// 3. 사용 함수들.
//
//    1) Socket관련...
//	     - SOCKET_STATUS		GetSocketState();
//       - SOCKADDR_CGNETWORK	GetSocketAddress();
//       - SOCKADDR_CGNETWORK	GetPeerAddress();
//       - bool					CloseSocket();
//
//    2) Connectable.
//       - bool	Disconnect();
//
//    3) Send 관련...
// 	     - bool	Send(const CGBuffer& _Buffer);
//
//    4) Socket속성 관련.
//
//
// 4. 재정의용 가로채기 함수들.
//
//    1) void OnConnect(CGNet::IO::IConnective* _pConnective)
//       - 접속이 성립되었을 때 호출되는 함수이다.
//       - Accept나 혹은 Connect를 통해서 접속 모두에 해당한다.
//       - 소속) CGNet::IO::Connectable::CTCP
//
//    2) void OnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t _Reason)  
//       - 접속이 실패했을 경우 호출되는 가로채기 함수.
//       - Acceptor에서 동작하는 Socket의 경우 이 함수는 거의 호출되지 않는다.
//       - 일반적으로 Connector에 의해서 Connet를 시도한 쪽에서 접속 시도를 실패했을 경우
//         호출된다.
// 
//    3) OnDisconnect(uint32_t _Reason)
//       - 접속된 Socket이 접속이 종료되었을 때 호출.
//
//	  4) void OnReceive(const CCGWSABuffer& _rWSABuffer, size_t _Transferred, const SOCKADDR_CGNETWORK& _pSockAddr);
//
//       - 데이터를 전송받았을 때 호출된다.
//       - 이때 전송되어온 데이터를 전송되어온 데이터 그 자체로 Message화되지
//         않은 상태이므로 이때 데이터를 처리하면 안된다.
//
//    5) void OnFailReceive(int p_ErrorCode, const CCGWSABuffer& _rWSABuffer, const SOCKADDR_CGNETWORK& _pSockAddr);
//       - Receive의 완료를 실패했을 불려지는 함수이다. 일반적으로 접속이 종료
//         등으로 인해 Receive가 완료되지 못했을 때 불려진다.
//
//    6) void ProcessPreMessage(CGMSG& _Msg)
//       - 메시지가 전달되기 전에 호출되는 가로채기 함수이다.
//       - 메시지가 전달되기 전에 메시지를 변경하거나 처리해야할 내용이 있으면 여기서 처리한다.
//       - 이 함수가 호출된후 가로채기 함수인 OnMessage()함수가 호출된다.
//
//    7) int OnMessage(CGMSG& _Msg)
//       - 전송받아 Message가 완성되었을 때 Message마다 호출되는 함수이다.
//       - OnMessage()함수로 넘어오는 데이터는 하나의 완성된 Message이다.
//
//    8) bool ValidateReceivedMessage(CGMSG& _Msg)
//       - Message가 제대로 된 것인가를 체크하는 가로채기 함수이다. 
//       - 전달되어온 메시지를 검사 후 정상적이면 true를 리턴하고 잘못되었다면 false를 리턴하도록 작성한다.
//       - 만약 false가 리턴되면 해당 Message의 처리는 중단되고 Exception처리 된다.
//
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class THEAD=uint32_t>
class CTCPFixed :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Socket::NTCP,				// (@) Socket TCP
	public						CGNet::IO::Connectable::NTCP,			// (@) Connectable TCP
	public						CGNet::IO::Sendable::NTCPOverlapped,	// (@) Sendable TCP Overlapped
	public				 		CGNet::IO::SendRequest::NBase,			// (@) SendRequest Base
	public						CGNet::IO::Sender::NStreamGather,		// (@) Sender Stream (Gather Version)
	public						CGNet::IO::Receivable::NStream,			// (@) Receivable Stream
	public						CGNet::IO::Packetable::NStreamFixed<sizeof(THEAD)>,// (@) Packetable Stream
	public						CGNet::IO::Messageable::NBase			// (@) Messageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCPFixed()													{}
	virtual	~CTCPFixed()												{}
};


}
}