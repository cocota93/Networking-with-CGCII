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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::Socket::CTCP
//
// 1. CGNet::Socket::CTCP��!
//    1) TCP�� Send/Receive ���� ������ �� �ִ� Socket��. 
//    2) �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ���� Failure�� ���� ���ݴ�.
//
//
// 2. CGNet::Socket::CTCP�� �ٽ�! Function�� ��� ����
//    1) �����Լ�(Process~)�� Socket�� �� ������ �����ϴ� �Լ����̴�.
//    2) ����ä���Լ�(On~)���� �����Ǹ� ���� ������� �Լ��̴�. ���α׷��Ӱ� �� 
//		 �κе��� ������������ Socket�� �ʿ��� ����� �߰��� �� �ִ�.
//
//
// 3. ��� �Լ���.
//
//    1) Socket����...
//	     - SOCKET_STATUS		GetSocketState();
//       - SOCKADDR_CGNETWORK	GetSocketAddress();
//       - SOCKADDR_CGNETWORK	GetPeerAddress();
//       - bool					CloseSocket();
//
//    2) Connectable.
//       - bool	Disconnect();
//
//    3) Send ����...
// 	     - bool	Send(const CGBuffer& _Buffer);
//
//    4) Socket�Ӽ� ����.
//
//
// 4. �����ǿ� ����ä�� �Լ���.
//
//    1) void OnConnect(CGNet::IO::IConnective* _pConnective)
//       - ������ �����Ǿ��� �� ȣ��Ǵ� �Լ��̴�.
//       - Accept�� Ȥ�� Connect�� ���ؼ� ���� ��ο� �ش��Ѵ�.
//       - �Ҽ�) CGNet::IO::Connectable::CTCP
//
//    2) void OnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t _Reason)  
//       - ������ �������� ��� ȣ��Ǵ� ����ä�� �Լ�.
//       - Acceptor���� �����ϴ� Socket�� ��� �� �Լ��� ���� ȣ����� �ʴ´�.
//       - �Ϲ������� Connector�� ���ؼ� Connet�� �õ��� �ʿ��� ���� �õ��� �������� ���
//         ȣ��ȴ�.
// 
//    3) OnDisconnect(uint32_t _Reason)
//       - ���ӵ� Socket�� ������ ����Ǿ��� �� ȣ��.
//
//	  4) void OnReceive(const CCGWSABuffer& _rWSABuffer, size_t _Transferred, const SOCKADDR_CGNETWORK& _pSockAddr);
//
//       - �����͸� ���۹޾��� �� ȣ��ȴ�.
//       - �̶� ���۵Ǿ�� �����͸� ���۵Ǿ�� ������ �� ��ü�� Messageȭ����
//         ���� �����̹Ƿ� �̶� �����͸� ó���ϸ� �ȵȴ�.
//
//    5) void OnFailReceive(int p_ErrorCode, const CCGWSABuffer& _rWSABuffer, const SOCKADDR_CGNETWORK& _pSockAddr);
//       - Receive�� �ϷḦ �������� �ҷ����� �Լ��̴�. �Ϲ������� ������ ����
//         ������ ���� Receive�� �Ϸ���� ������ �� �ҷ�����.
//
//    6) void ProcessPreMessage(CGMSG& _Msg)
//       - �޽����� ���޵Ǳ� ���� ȣ��Ǵ� ����ä�� �Լ��̴�.
//       - �޽����� ���޵Ǳ� ���� �޽����� �����ϰų� ó���ؾ��� ������ ������ ���⼭ ó���Ѵ�.
//       - �� �Լ��� ȣ����� ����ä�� �Լ��� OnMessage()�Լ��� ȣ��ȴ�.
//
//    7) int OnMessage(CGMSG& _Msg)
//       - ���۹޾� Message�� �ϼ��Ǿ��� �� Message���� ȣ��Ǵ� �Լ��̴�.
//       - OnMessage()�Լ��� �Ѿ���� �����ʹ� �ϳ��� �ϼ��� Message�̴�.
//
//    8) bool ValidateReceivedMessage(CGMSG& _Msg)
//       - Message�� ����� �� ���ΰ��� üũ�ϴ� ����ä�� �Լ��̴�. 
//       - ���޵Ǿ�� �޽����� �˻� �� �������̸� true�� �����ϰ� �߸��Ǿ��ٸ� false�� �����ϵ��� �ۼ��Ѵ�.
//       - ���� false�� ���ϵǸ� �ش� Message�� ó���� �ߴܵǰ� Exceptionó�� �ȴ�.
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