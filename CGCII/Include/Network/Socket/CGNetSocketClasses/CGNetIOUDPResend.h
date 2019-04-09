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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::IO::NUDPResend
//
// 1. CGNet::IO::NUDPResend��!
//    1) �Ϲ����� UDP�� Sendeing ��ɿ� ������ ������ ����� �߰��� ���̴�.
//    2) ���� �� RELIABLE �÷��׸� �����Ͽ� ������ ��� �ش� �޽����� ���ؼ��� 
//       ������ ����� �����Ѵ�.
//    3) ������ ����̶� ���۵� �޽����� ���ؼ� ACK ��ȣ�� �������� ���� ��� ����
//       �ð� ���� ���������ִ� ����� �ǹ��Ѵ�.
//    4) �����ð� �������� �����ص� �����ۿ� �������� ���� ��� OnFailSend()�Լ���
//       ȣ���Ѵ�.
//
//    ����) ���� ��Ը��� �������� ������ ��� �� Ŭ�������ٴ� Reliable Ŭ������ 
//         ����ϱ� �����Ѵ�. ��Ը��� �������� ������ ��� ���� Cogestion Control
//         �� �پ��� ������ �˰����� �߰��� Reliable Ŭ�������� ������ ���� ����
//         ����.
//
//-----------------------------------------------------------------------------
#define	MAX_RECEIVEPACKET_QUEUE		1024

namespace CGNet
{
namespace IO
{

class NUDPResend : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNet::IO::SendRequest::NUDPResend,		// (@) SendRequest
	public						CGNet::IO::Packetable::NDatagramResponse,	// (@) Packetable Base
	virtual protected			ICGMessageable,							//     Messageable
	virtual public				CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;

	virtual	void				ResetPacketable()	{}
};


}
}