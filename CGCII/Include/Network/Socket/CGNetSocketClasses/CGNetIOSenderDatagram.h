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
// CGNet::IO::Sender::NContainer
//
// 1. CGNet::IO::Sender::CDatagram��~
//    Datagram�� Send�Լ��̴�. SendTo()�Լ��� Interface�� ������ �ִ�.
//
// 2. �Լ�.
//    1) SendTo()
//       Datagram�� Address�� Packet�� ������ Interface�Լ�.
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
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool				SendTo(_In_ const CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress=nullptr) override;


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);
};


inline bool NDatagram::SendTo(_In_ const CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress)
{
	// Check) _arrayBuffer->buf�� nullptr�� �ƴѰ�?
	CGASSERT(_Buffer.buf != nullptr, false)

	// Check) _arrayBuffer->len�� 0�� �ƴѰ�?
	CGASSERT(_Buffer.len != 0, false)

	// Check) ���۰� Overflow�Ǿ��°�?
	CGASSERT(_Buffer._is_buffer_overflow()==false, false);

	// Check) Packet Validate Check�Ѵ�.
	#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&_Buffer, 1), false);
	#endif

	// Statistics) Sended Packet�� ����Ѵ�.
	Statistics_OnSendMessage();

	// 1) �����Ѵ�.
	return	RequestSend(nullptr, &_Buffer, 1, _Buffer.get_reference(), _pSockAddress);
}

inline	bool NDatagram::ValidateSendMessage(_In_ const CCGBuffer* /*_Buffer*/, _In_ int /*_countBuffer*/)
{
	return	true;
}


}
}
}