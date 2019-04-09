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
// 1. CGNet::Socket::CUDPResend��!
//    - CGNet::Socket::CUDP�� ���������� �������� SendRequest�� UDPResend�����
//      �ִ� ������ �ٲ����.
//    - Resend����� RELIABLE flag�� ��������ν� ������ �ŷڼ� �ִ� ��������
//      ������ �� �ִ� UDP Socket�̴�. ������ ��Ŷ������ Resend�� �����ϱ� ������
//      ��Ը�� ����� ��� ������ ���ϱ޼������� �������� ������ �ִ�.
//       ���� Resend������� Reliable������ ������ �������̰ų� ��Ը�� ���
//      �ϴµ����� ���� �ʴ�. �׷� ���� �׳� Reliable ������ �����ϴ� Reliable��
//      ����ϴ� ���� ���� ���̴�.
//
// 2. ����.
//    1) �޽����� head�� �� ''�� �����Ǿ� ������ ACK�� ���޵��� ���� �� ��������
//       �����Ѵ�.
//
// 3. ����
//    1) ���� ���� Resend�� �� ��� Reliable�� ���� ������ ���� ������ �� �ִ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

class CUDPResend : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNet::IO::Socket::NUDP,				// (@) Socket
	public						CGNet::IO::Binder::NUDP,				// (@) Binder
	public						CGNet::IO::Sendable::NUDP,				// (@) UDP Sendable
	public						CGNet::IO::NUDPResend,					// (@) Resendable UDP
	public						CGNet::IO::Sender::NDatagram,			// (@) Datagram Sender
	public						CGNet::IO::Receivable::NDatagram,		// (@) Receivable
	public						CGNet::IO::Messageable::NBase			// (@) Messageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CUDPResend(_In_ bool p_bReportConnectReset=false) : CGNet::IO::Socket::NUDP(p_bReportConnectReset) {}
	virtual ~CUDPResend()												{}
};


}
}