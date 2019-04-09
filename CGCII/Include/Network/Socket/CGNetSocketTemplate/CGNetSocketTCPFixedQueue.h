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
// CGNet::Socket::CTCPQueue
//
// 1. CGNet::Socket::CTCPQueue란!
//    1) CGNet::Socket::CTCP와 모든 것은 동일하나 Receivable을 CGNet::IO::Receivable::
//       NStreamQueue로 사용한 것이다.
//    2) 이는 Receive와 Message의 처리를 다른 작업단위에서 처리할 있게 함으로써
//       시간당 수신량을 대폭 증가한 것이다.
//    3) 하지만 수신량이 적은 Socket에서는 오히려 더 많은 비용을 들일 수 있으므로
//       주의해야 한다.
//    4) 따라서 이 버전은 주로 단일 Socket으로 많은 데이터를 송수신하는 접속에 적합
//       한 형태라고 할 수 있다.
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