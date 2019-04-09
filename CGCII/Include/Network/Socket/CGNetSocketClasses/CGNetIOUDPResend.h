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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::IO::NUDPResend
//
// 1. CGNet::IO::NUDPResend란!
//    1) 일반적인 UDP의 Sendeing 기능에 선택적 재전송 기능을 추가한 것이다.
//    2) 전송 시 RELIABLE 플래그를 설정하여 전송할 경우 해당 메시지에 대해서만 
//       재전송 기능이 동작한다.
//    3) 재전송 기능이란 전송된 메시지에 대해서 ACK 신호가 도착하지 않을 경우 일정
//       시간 동안 재전송해주는 기능을 의미한다.
//    4) 일정시간 재전송을 수행해도 재전송에 성공하지 못할 경우 OnFailSend()함수를
//       호출한다.
//
//    주위) 만약 대규모의 재전송을 수행할 경우 이 클래스보다는 Reliable 클래스를 
//         사용하길 권장한다. 대규모의 재전송을 수행할 경우 각종 Cogestion Control
//         및 다양한 재전송 알고리즘이 추가된 Reliable 클래스보다 성능이 많이 떨어
//         진다.
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
	virtual public				CGNet::IO::Statistics::NSocket			// (@) 통계
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