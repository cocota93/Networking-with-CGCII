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
// CGNet::Socket::CTCPFixedNoGather
//
// 1. CGNet::Socket::CTCPFixedNoGather��!
//    1) �⺻�����δ� CGNet::Socket::CTCPFixedNoGather�� �����ϳ� Socket�� Sender 
//       �κи� No Gather ������ ����� ���̴�.
//    2) ������ ���� ���� Socket�� ��� No Gather������ �� �뷮�� ó�� ���� �鿡��
//       ȿ�����̴�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class THEAD=uint32_t>
class CTCPFixedNoGather :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Socket::NTCP,				// (@) Socket TCP
	public						CGNet::IO::Connectable::NTCP,			// (@) Connectable TCP
	public						CGNet::IO::Sendable::NTCPOverlapped,	// (@) Sendable TCP Overlapped
	public				 		CGNet::IO::SendRequest::NBase,			// (@) SendRequest Base
	public						CGNet::IO::Sender::NStream,				// (@) Sender Stream (No Gather Version)
	public						CGNet::IO::Receivable::NStream,			// (@) Receivable Stream
	public						CGNet::IO::Packetable::NStreamFixed<sizeof(THEAD)>,// (@) Packetable Stream
	public						CGNet::IO::Messageable::NBase			// (@) Messageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCPFixedNoGather()											{}
	virtual	~CTCPFixedNoGather()										{}
};


}
}