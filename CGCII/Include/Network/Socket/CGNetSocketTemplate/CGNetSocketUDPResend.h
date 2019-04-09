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
// 1. CGNet::Socket::CUDPResend란!
//    - CGNet::Socket::CUDP와 동일하지만 차이점은 SendRequest만 UDPResend기능이
//      있는 것으로 바뀌었다.
//    - Resend기능은 RELIABLE flag를 사용함으로써 간단히 신뢰성 있는 재전송을
//      수행할 수 있는 UDP Socket이다. 하지만 패킷단위로 Resend를 수행하기 때문에
//      대규모로 사용할 경우 성능이 기하급수적으로 떨어지는 단점이 있다.
//       따라서 Resend기능으로 Reliable전송을 수행은 연속적이거나 대규모로 사용
//      하는데에는 좋지 않다. 그런 것은 그냥 Reliable 전송을 수행하는 Reliable을
//      사용하는 거이 좋을 것이다.
//
// 2. 사용법.
//    1) 메시지의 head에 로 ''가 설정되어 있으면 ACK가 전달되지 않을 시 재전송을
//       수행한다.
//
// 3. 주의
//    1) 많은 수의 Resend를 할 경우 Reliable에 비해 성능이 많이 떨어질 수 있다.
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