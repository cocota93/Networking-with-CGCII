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
// CGNet::Socket::CTCPFixedNoGather
//
// 1. CGNet::Socket::CTCPFixedNoGather란!
//    1) 기본적으로는 CGNet::Socket::CTCPFixedNoGather와 동일하나 Socket의 Sender 
//       부분만 No Gather 버전이 적용된 것이다.
//    2) 전송이 잦지 않은 Socket의 경우 No Gather버전이 더 용량과 처리 부하 면에서
//       효율적이다.
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