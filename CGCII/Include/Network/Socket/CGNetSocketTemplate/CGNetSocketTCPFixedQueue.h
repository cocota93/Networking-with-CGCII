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
// CGNet::Socket::CTCPQueue
//
// 1. CGNet::Socket::CTCPQueue��!
//    1) CGNet::Socket::CTCP�� ��� ���� �����ϳ� Receivable�� CGNet::IO::Receivable::
//       NStreamQueue�� ����� ���̴�.
//    2) �̴� Receive�� Message�� ó���� �ٸ� �۾��������� ó���� �ְ� �����ν�
//       �ð��� ���ŷ��� ���� ������ ���̴�.
//    3) ������ ���ŷ��� ���� Socket������ ������ �� ���� ����� ���� �� �����Ƿ�
//       �����ؾ� �Ѵ�.
//    4) ���� �� ������ �ַ� ���� Socket���� ���� �����͸� �ۼ����ϴ� ���ӿ� ����
//       �� ���¶�� �� �� �ִ�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class THEAD=uint32_t>
class CTCPFixedQueue :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Socket::NTCP,				// (@) Socket TCP
	public						CGNet::IO::Connectable::NTCP,			// (@) Connectable TCP
	public						CGNet::IO::Sendable::NTCPOverlapped,	// (@) Sendable TCP Overlapped
	public						CGNet::IO::SendRequest::NBase,			// (@) SendRequest Base
	public						CGNet::IO::Sender::NStreamGather,		// (@) Sender Stream (Gather Version)
	public						CGNet::IO::Receivable::NStreamQueue,	// (@) Receivable Stream (Queue Version)
	public						CGNet::IO::Packetable::NStreamFixed<sizeof(THEAD)>,// (@) Packetable Stream
	public						CGNet::IO::Messageable::NBase			// (@) Messageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCPFixedQueue()											{}
	virtual	~CTCPFixedQueue()											{}
};


}
}