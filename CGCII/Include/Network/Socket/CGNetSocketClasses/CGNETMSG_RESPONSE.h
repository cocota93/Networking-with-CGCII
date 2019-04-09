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
// CGNETMSG_RESPONSE
//
// 1. CGNETMSG_RESPONSE��!
//    1) �������� ���ӵǾ� �ִ�(�Ϲ������� TCP) ��뿡�� ���� �޽����� ���� ȸ�� 
//       �޽����� ���� �� �ֵ��� �ϴ� �ý����̴�.
//    2) ������ �� ������ Lambda�Լ��� ������ �ָ� �ش� �޽����� ���� �亯 �޽�����
//       �����Ͽ��� �� �� Lambda �Լ��� ȣ���� �ش�.
//
//-----------------------------------------------------------------------------
// Message) 
struct CGNETMSG_RESPONSE : public CGNETMSG
{
public:
	CGNETMSG_RESPONSE(_In_ CGNet::IO::ISender* p_pSender, _In_ const CCGBuffer& _Buffer);

public:
			bool		ResponseMessage(_In_ const CCGBuffer& _Buffer);
protected:
	// 1) Sender
			CGPTR<CGNet::IO::ISender>	pSender;

	// 2) RequestID/ RequestSerial
			int					iRequestID;
			uint32_t			dwRequestSerial;
};

inline CGNETMSG_RESPONSE::CGNETMSG_RESPONSE(_In_ CGNet::IO::ISender* p_pSender, _In_ const CCGBuffer& _Buffer) :
	CGNETMSG(CGMESSAGE::NETWORK::SOCKET::REMOTE_RESPONSE, _Buffer+16), 
	pSender(p_pSender),								// Sender�� �����Ѵ�.
	iRequestID(_Buffer.front<int>(8)),				// Request ID�� �����Ѵ�.
	dwRequestSerial(_Buffer.front<uint32_t>(12))	// Request Serial�� �����Ѵ�.
{
}

inline bool CGNETMSG_RESPONSE::ResponseMessage(_In_ const CCGBuffer& _Buffer)
{
	// Check) 
	RETURN_IF(pSender.empty(), false);
	
	// 1) ���۸� �Ҵ��Ѵ�.
	CCGBuffer	tempBuffer	 = MEM_POOL_ALLOC(32+_Buffer.len);

	// 2) Message�� �����.
	tempBuffer.append<uint32_t>();
	tempBuffer.append<uint32_t>(CGMESSAGE::NETWORK::SOCKET::REMOTE_RESPONSE);
	tempBuffer.append<int>(iRequestID);
	tempBuffer.append<uint32_t>(dwRequestSerial);
	tempBuffer.append(_Buffer);
	tempBuffer.front<uint32_t>()	 = tempBuffer.len;

	// 3) �����Ѵ�.
	return	pSender->Send(tempBuffer);
}

#define TRANSLATE_REQUEST_MESSAGE(msg, source)		if((msg.message==CGMESSAGE::SYSTEM::MESSAGE) && ((CGNETMSG&)msg).Buffer.front<uint32_t>(4)==CGMESSAGE::NETWORK::SOCKET::REMOTE_REQUEST) { msg=CGNETMSG_RESPONSE(source, msg);}
