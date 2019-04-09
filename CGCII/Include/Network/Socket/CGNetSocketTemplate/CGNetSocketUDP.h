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
// CGNet::Socket::CUDP
//
// 1. CGNet::Socket::CUDP��!
//    - �⺻���� UDP Socket Class��. 
//    - UDP�� ��� Connect�� Disconnect�� �����Ƿ� �׿� ���õ� �Լ��� ����.
//    - UDP Socket�� Connect��� ������ Bind()�Լ��� ȣ���� �ٷ� ����� �� �ִ�.
//
// 2. ��� �Լ���.
//    1) Socket����...
//       * bool Bind(const SOCKADDR_CGNETWORK* _rSocketAddr, int p_sizePacket, int p_nBufferPreparedToReceive);
//       * bool Bind(u_short p_dwPort, int p_sizePacket, int p_nBufferPreparedToReceive);
//       * bool Stop();
//       * bool PrepareReceive(int p_sizePacket, uint32_t p_nBufferPreparedToReceive);
//       * SetPeerAddress()
//          UDP Socket�� ��� Target Address�� �׶� �׶� ������ �ʿ䵵 �ֱ� ������
//          �� �Լ��� �־���.
// 
//    2) Sendable����...
//       * bool SendTo(const CCGBuffer& _Buffer, const SOCKADDR_CGNETWORK& _pSockAddress);
//         Ư�� Address�� _pBuffer�� �����ϴ� �Լ��̴�.
// 
//    3) Receive����...
//	     * GetMessageSize() const;
//          Receive�� �ɶ� �Ҵ��ϴ� ������ ũ�⸦ ��� �Լ��̴�.
//
//	     * SetPacketSize(uint32_t p_dwPacketSize);
//          Receive�� �ɶ� �Ҵ��ϴ� ������ ũ�⸦ �����ϴ� �Լ��̴�.
//          �⺻�����δ� 1024Byte�� �����Ǿ� �ִ�. ���� �� ũ�Ⱑ ���۵Ǿ�� Packet
//          �� ũ�⺸�� ������ Packet�� Loss�� �ǹǷ� ������ ������ �־�� �Ѵ�
//          �ݵ��, Bind�� �����ϱ� ���� �����Ͽ� ������ �־���Ѵ�.
//
//
// 3. �����ǿ� Hook�Լ���.
//
//		virtual	void	OnPrepareSocket();
//       - Socket�� �����ϰų� Pool��� �Ҵ�޾Ƽ� ����Ҷ� Socket�� Reset��
//         �Ѵ�. �̶� �ҷ����� �Լ��̴�.
//       - �Ҽ�) CGNet::IO::Socket::CAccountSocket
//
//		virtual	void	OnStop();
//       - Socket Handle�� ���� �� �ҷ����� �Լ��̴�. ��������ʹ� �������.
//       - �Ҽ�) CGNet::IO::Socket::CAccountSocket
//
//		virtual	void	OnReceive(const CGD::buffer& _rWSABuffer, size_t _Transferred, const SOCKADDR_CGNETWORK* _pSockAddr);
//       - �����͸� ���۹޾��� �� ȣ��ȴ�.
//       - �̶� ���۵Ǿ�� �����͸� ���۵Ǿ�� ������ �� ��ü�� Packetȭ����
//         ���� �����̹Ƿ� �̶� �����͸� ó���ϸ� �ȵȴ�.
//       - �Ҽ�) CGNet::IO::Receivable::CTCP
//
//		virtual void	OnFailReceive(int p_ErrorCode, const CGD::buffer& _rWSABuffer, const SOCKADDR_CGNETWORK* _pSockAddr);
//       - Receive�� �ϷḦ �������� �ҷ����� �Լ��̴�. �Ϲ������� ������ ����
//         ������ ���� Receive�� �Ϸ���� ������ �� �ҷ�����.
//       - ��, CONRESET�� true�� �� ������ ��� Send�� IP�� �����Ҽ� ������
//         �� �Լ��� ȣ��� ���� �ִ�.
//       - �Ҽ�) CGNet::IO::Receivable::CTCP
//  
//		virtual int	OnMessage(CGMSG& _Msg) PURE;
//        - ������ Messageable���� ���� Packet�� �ٷ� OnMessage�� 
//          ȣ�����ش�. (�ݵ�� ������ ����� �Ѵ�.)
//        - ���� ���� ������ �ϴ� �ٽ� ���Լ��̴�.
//        - �Ҽ�) CGNet::IO::Messageable::CBase
//
//		��Ÿ ����!!! �ڼ��� �˰� �ʹٸ� ��ӹ��� class�� ��������!!!
//
//
// 4. ���� ����.
//    1) Receive�� �ϱ� ���ؼ��� PrepareReceive()�� ȣ��Ǿ����.
//    2) Bind()�� �ϰ� �Ǹ� �ڵ������� PrepareReceive()�� ȣ��Ǳ� ������ ����
//       PrepareReceive()�� ȣ���� �ʿ䰡 ����.
//    3) Bind()�� Parameter���� �ϰų� Bind(0)�� ���� �ϸ� ������ Port�� Bind��.
//    4) ConnectReset�� ������ �����ʿ�!!!
//       - ConnectReset�� Report���� ������ UDP�� ��� ������ ���� �ʴ� ����
//         Ȯ���Ҽ� ����. ������ ���޹����� ���� ���ϰ� �ɸ� �� �ִ�.
//       - ���� ������ ������ �ʿ��ϴ�. �Ϲ������� Server�� ��� false��
//         Client�� ��� TRUE�� �Ѵ�.
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