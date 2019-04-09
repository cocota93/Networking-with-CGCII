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
// CGNet::IO::Sender::NContainer
//
// 1. CGNet::IO::Sender::CDatagram은~
//    Datagram용 Send함수이다. SendTo()함수를 Interface로 가지고 있다.
//
// 2. 함수.
//    1) SendTo()
//       Datagram용 Address로 Packet을 날리는 Interface함수.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sender
{

class NDatagram : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISendRequest,					// (I) SendRequest
	virtual public				CGNet::IO::ISenderDatagram,				//     Sender
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				SendTo(_In_ const CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress=nullptr) override;


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);
};


inline bool NDatagram::SendTo(_In_ const CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress)
{
	// Check) _arrayBuffer->buf가 nullptr이 아닌가?
	CGASSERT(_Buffer.buf != nullptr, false)

	// Check) _arrayBuffer->len이 0이 아닌가?
	CGASSERT(_Buffer.len != 0, false)

	// Check) 버퍼가 Overflow되었는가?
	CGASSERT(_Buffer._is_buffer_overflow()==false, false);

	// Check) Packet Validate Check한다.
	#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&_Buffer, 1), false);
	#endif

	// Statistics) Sended Packet을 계산한다.
	Statistics_OnSendMessage();

	// 1) 전송한다.
	return	RequestSend(nullptr, &_Buffer, 1, _Buffer.get_reference(), _pSockAddress);
}

inline	bool NDatagram::ValidateSendMessage(_In_ const CCGBuffer* /*_Buffer*/, _In_ int /*_countBuffer*/)
{
	return	true;
}


}
}
}