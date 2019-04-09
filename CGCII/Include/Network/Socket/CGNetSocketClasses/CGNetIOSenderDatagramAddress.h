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
// CGNet::IO::Sender::NStreamAddress
//
// 1. CGNet::IO::Sender::CProxyStream은~
//    - Sender의 Pointer를 가지고 있는 Sender로 Send를 할 경우 Pointer로 지정된
//      Send를 통해 Send를 수행한다. 
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sender
{

class NDatagramAddress : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IAddress,					// (I) Address
	virtual protected			CGNet::IO::ISendRequest,				// (I) Sendable
	virtual public				CGNet::IO::ISender,						//     Sender Stream
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);
};


inline bool NDatagramAddress::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf가 nullptr이 아닌가?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len이 0이 아닌가?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	// Check) 버퍼가 Overflow되었는가?
	CGASSERT(_Buffer._is_buffer_overflow()==false, false);

	// Check) Packet Validate Check한다.
	#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&_Buffer, 1), false);
	#endif

	// Statistics) Sended Packet을 계산한다.
	Statistics_OnSendMessage();

	// 1) Peer Address를 얻는다.
	SOCKADDR_CGNETWORK	addrSocket	 = GetPeerAddress();

	// 2) 전송한다.
	return	RequestSend(nullptr, &_Buffer, 1, _Buffer.get_reference(), &addrSocket);
}

inline	bool NDatagramAddress::ValidateSendMessage(_In_ const CCGBuffer* /*_Buffer*/, _In_ int /*_countBuffer*/)
{
	return	true;
}


}
}
}