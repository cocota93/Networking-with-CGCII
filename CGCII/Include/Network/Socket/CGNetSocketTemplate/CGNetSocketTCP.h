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
//    1) TCP�� Send/Receive/Connect ���� ������ �� �ִ� Socket��. 
//    2) �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ���� Failure�� ���� ���ݴ�.
//
//
// 2. CGNet::Socket::CTCP�� �ٽ�! Function�� ��� ����
//    1) ó���Լ��� �⺻���� I/Oó���� ���� ó���Լ����̴�.
//					���������� ���� I/O�� ó���ϱ� ���� �ʿ��� �Լ��鿡 ���ؼ� ������ ���̴�.
//    2) �����Լ���	Socket�� �� ������ �����ϴ� �Լ����̴�.
//    3) User�Լ���	�����Ǹ� ���� ������� �Լ��̴�. ���α׷��Ӱ� �� �κе��� ������
//					������ Socket�� ���ӿ� �°� ����� �ȴ�.
//
//
// 3. ��� �Լ���.
//
//    1) Socket����...
//	     - SOCKET_STATUS		GetSocketState();
//       - SOCKADDR_CGNETWORK	 GetSocketAddress();
//       - SOCKADDR_CGNETWORK	 GetPeerAddress();
//
//    2) Connectable.
//	     - bool	Connect(LPCSOCKADDR _pSockAddr, int _nSockAddrLen);
//       - bool	Disconnect();
//
//    3) Sendable����...
// 	     - bool	Send(const CCGBuffer& _Buffer);
//
//    4) Socket�Ӽ� ����.
//
//
// 4. �ֿ��� ����ä�� �Լ�.
//    ������ �̺�Ʈ�� �߻��� �ش� On~���� �����ϴ� �����Լ��� ����ä���Լ��� ȣ��ȴ�.
//    �Ʒ��� ����ä�� �Լ��� ���� ���� ���Ǵ� �Լ���� �� �� �ִ�.
//    ���� ������ �Ǿ�����, ������ ����Ǿ��� ��, �޽����� ���޵Ǿ��� �� ȣ��Ǵ� 
//    ����ä�� �Լ��̴�. ��κ� �� �Լ��鸸 ���ȴ�.
//
//    1) void OnConnect(CGNet::IO::IConnective* _pConnective)	      
//      Clinet���� ���ӽõ��� �ͼ� ������ ���� �Ǿ��� �� ȣ��
//
//    2) void OnDisconnect(uint32_t _Reason)
//      ���ӵ� Socket�� ������ ����Ǿ��� �� ȣ��.
//
//    3) int OnMessage(CGMSG& _Msg)
//      ���ο� �޽����� �������� �� ȣ��.
//
//
// 5. ���� ������ �ʴ� ����ä�� �Լ�.
//    ���� ���Ǵ� ����ä�� �Լ� �̿ܿ� ���� �������� ������ ���ǵ� ����ä��
//    �Լ��� �Ʒ��� ����.
//    ���� �����ǿ� �������� ������ �ʿ��� ��� �������� �ʿ䰡 �ִ�.
//
//    1) void OnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t _Reason)  
//       - ������ �������� ��� ȣ��Ǵ� ����ä�� �Լ�.
//       - Acceptor���� �����ϴ� Socket�� ��� �� �Լ��� ���� ȣ����� �ʴ´�.
//       - �Ϲ������� Connector�� ���ؼ� Connet�� �õ��� �ʿ��� ���� �õ��� �������� ���
//         ȣ��ȴ�.
//
//	  2) void OnFailSending()
//       - ������ �������� �� ȣ��Ǵ� �Լ�.
//
//    3) void OnPrepareSocket()
//       - Socket�� ���� �Ҵ�޾� �غ��� �� ȣ��Ǵ� �Լ��̴�.
//
//    4) void OnCloseSocket()
//       - Socket�� ���� �� ȣ��ȴ�. ������ ����Ǵ� �Ͱ��� �ٸ���.
// 
//    5) void OnReceive(const CGD::buffer& _rWSABuffer, size_t _Transferred, const SOCKADDR_CGNETWORK* _pSockAddr)
//       - �����͸� �޾��� �� ȣ��Ǵ� �Լ�.
//       - ���� ���۹��� �����͸� ���ڸ� ���� ���޵Ǿ�����.
//
//    6) void ProcessPreMessage(CGMSG& _Msg)
//       - �޽����� ���޵Ǳ� ���� ȣ��Ǵ� ����ä�� �Լ��̴�.
//       - �޽����� ���޵Ǳ� ���� �޽����� �����ϰų� ó���ؾ��� ������ ������ ���⼭ ó���Ѵ�.
//       - �� �Լ��� ȣ����� ����ä�� �Լ��� OnMessage()�Լ��� ȣ��ȴ�.
//
//    7) bool ValidateReceivedMessage(const CGMSG& _Msg)
//       - Message�� ����� �� ���ΰ��� üũ�ϴ� ����ä�� �Լ��̴�. 
//       - ���޵Ǿ�� �޽����� �˻� �� �������̸� true�� �����ϰ� �߸��Ǿ��ٸ� false�� �����ϵ��� �ۼ��Ѵ�.
//       - ���� false�� ���ϵǸ� �ش� Message�� ó���� �ߴܵǰ� Exceptionó�� �ȴ�.
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