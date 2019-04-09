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
// CGNet::IO::Sender::NStreamAddress
//
// 1. CGNet::IO::Sender::CProxyStream��~
//    - Sender�� Pointer�� ������ �ִ� Sender�� Send�� �� ��� Pointer�� ������
//      Send�� ���� Send�� �����Ѵ�. 
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
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);
};


inline bool NDatagramAddress::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf�� nullptr�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len�� 0�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	// Check) ���۰� Overflow�Ǿ��°�?
	CGASSERT(_Buffer._is_buffer_overflow()==false, false);

	// Check) Packet Validate Check�Ѵ�.
	#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&_Buffer, 1), false);
	#endif

	// Statistics) Sended Packet�� ����Ѵ�.
	Statistics_OnSendMessage();

	// 1) Peer Address�� ��´�.
	SOCKADDR_CGNETWORK	addrSocket	 = GetPeerAddress();

	// 2) �����Ѵ�.
	return	RequestSend(nullptr, &_Buffer, 1, _Buffer.get_reference(), &addrSocket);
}

inline	bool NDatagramAddress::ValidateSendMessage(_In_ const CCGBuffer* /*_Buffer*/, _In_ int /*_countBuffer*/)
{
	return	true;
}


}
}
}