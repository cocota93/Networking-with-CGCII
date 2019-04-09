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
// CGNet::Socket::CUDP
//
// 1. CGNet::Socket::CUDP란!
//    - 기본적인 UDP Socket Class임. 
//    - UDP의 경우 Connect와 Disconnect가 없으므로 그에 관련된 함수가 없다.
//    - UDP Socket은 Connect대신 생성후 Bind()함수를 호출후 바로 사용할 수 있다.
//
// 2. 사용 함수들.
//    1) Socket관련...
//       * bool Bind(const SOCKADDR_CGNETWORK* _rSocketAddr, int p_sizePacket, int p_nBufferPreparedToReceive);
//       * bool Bind(u_short p_dwPort, int p_sizePacket, int p_nBufferPreparedToReceive);
//       * bool Stop();
//       * bool PrepareReceive(int p_sizePacket, uint32_t p_nBufferPreparedToReceive);
//       * SetPeerAddress()
//          UDP Socket의 경우 Target Address를 그때 그때 설정할 필요도 있기 때문에
//          이 함수를 넣었다.
// 
//    2) Sendable관련...
//       * bool SendTo(const CCGBuffer& _Buffer, const SOCKADDR_CGNETWORK& _pSockAddress);
//         특정 Address로 _pBuffer를 전송하는 함수이다.
// 
//    3) Receive관련...
//	     * GetMessageSize() const;
//          Receive를 걸때 할당하는 버퍼의 크기를 얻는 함수이다.
//
//	     * SetPacketSize(uint32_t p_dwPacketSize);
//          Receive를 걸때 할당하는 버퍼의 크기를 설정하는 함수이다.
//          기본적으로는 1024Byte로 설정되어 있다. 만약 이 크기가 전송되어온 Packet
//          의 크기보다 작으면 Packet의 Loss가 되므로 적절히 설정해 주어야 한다
//          반드시, Bind를 수행하기 전에 실행하여 설정해 주어야한다.
//
//
// 3. 재정의용 Hook함수들.
//
//		virtual	void	OnPrepareSocket();
//       - Socket을 생성하거나 Pool등에서 할당받아서 사용할때 Socket을 Reset을
//         한다. 이때 불려지는 함수이다.
//       - 소속) CGNet::IO::Socket::CAccountSocket
//
//		virtual	void	OnStop();
//       - Socket Handle을 닫을 때 불려지는 함수이다. 접속종료와는 상관없다.
//       - 소속) CGNet::IO::Socket::CAccountSocket
//
//		virtual	void	OnReceive(const CGD::buffer& _rWSABuffer, size_t _Transferred, const SOCKADDR_CGNETWORK* _pSockAddr);
//       - 데이터를 전송받았을 때 호출된다.
//       - 이때 전송되어온 데이터를 전송되어온 데이터 그 자체로 Packet화되지
//         않은 상태이므로 이때 데이터를 처리하면 안된다.
//       - 소속) CGNet::IO::Receivable::CTCP
//
//		virtual void	OnFailReceive(int p_ErrorCode, const CGD::buffer& _rWSABuffer, const SOCKADDR_CGNETWORK* _pSockAddr);
//       - Receive의 완료를 실패했을 불려지는 함수이다. 일반적으로 접속이 종료
//         등으로 인해 Receive가 완료되지 못했을 때 불려진다.
//       - 단, CONRESET을 true로 해 놓았을 경우 Send한 IP가 도달할수 없으면
//         이 함수가 호출될 수도 있다.
//       - 소속) CGNet::IO::Receivable::CTCP
//  
//		virtual int	OnMessage(CGMSG& _Msg) PURE;
//        - 현재의 Messageable에서 받은 Packet을 바로 OnMessage을 
//          호출해준다. (반드시 재정의 해줘야 한다.)
//        - 가장 많이 재정의 하는 핵심 훅함수이다.
//        - 소속) CGNet::IO::Messageable::CBase
//
//		기타 많다!!! 자세히 알고 싶다면 상속받은 class를 뒤져봐라!!!
//
//
// 4. 주의 사항.
//    1) Receive를 하기 위해서는 PrepareReceive()가 호출되어야함.
//    2) Bind()를 하게 되면 자동적으로 PrepareReceive()가 호출되기 때문에 따로
//       PrepareReceive()를 호출할 필요가 없음.
//    3) Bind()를 Parameter없이 하거나 Bind(0)과 같이 하면 임의의 Port에 Bind됨.
//    4) ConnectReset의 설정에 주의필요!!!
//       - ConnectReset을 Report받지 않으면 UDP의 경우 전달이 되지 않는 것을
//         확인할수 없다. 하지만 전달받으면 많은 부하가 걸릴 수 있다.
//       - 따라서 적절한 선택이 필요하다. 일반적으로 Server의 경우 false로
//         Client의 경우 TRUE로 한다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

class CUDP : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNet::IO::Socket::NUDP,				// (@) Socket
	public						CGNet::IO::Binder::NUDP,				// (@) Binder
	public						CGNet::IO::Sendable::NUDP,				// (@) UDP Sendable
	public						CGNet::IO::SendRequest::NBase,			// (@) SendRequstor
	public						CGNet::IO::Sender::NDatagram,			// (@) Datagram Sender
	public						CGNet::IO::Receivable::NDatagram,		// (@) Receivable
	public						CGNet::IO::Packetable::NDatagram,		// (@) Packetable
	public						CGNet::IO::Messageable::NBase			// (@) Messageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CUDP(_In_ bool p_bReportConnectReset=false) : CGNet::IO::Socket::NUDP(p_bReportConnectReset) { RegisterBinder(); }
	virtual ~CUDP()														{	UnregisterBinder();}
};


}
}