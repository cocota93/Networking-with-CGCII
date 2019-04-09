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
// CGNETMSG_RESPONSE
//
// 1. CGNETMSG_RESPONSE란!
//    1) 원격으로 접속되어 있는(일반적으로 TCP) 상대에게 보낸 메시지에 대한 회신 
//       메시지를 받을 수 있도록 하는 시스템이다.
//    2) 전송할 때 실행할 Lambda함수를 정의해 주면 해당 메시지에 대한 답변 메시지가
//       도착하였을 때 그 Lambda 함수를 호출해 준다.
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
	pSender(p_pSender),								// Sender를 설정한다.
	iRequestID(_Buffer.front<int>(8)),				// Request ID를 설정한다.
	dwRequestSerial(_Buffer.front<uint32_t>(12))	// Request Serial을 설정한다.
{
}

inline bool CGNETMSG_RESPONSE::ResponseMessage(_In_ const CCGBuffer& _Buffer)
{
	// Check) 
	RETURN_IF(pSender.empty(), false);
	
	// 1) 버퍼를 할당한다.
	CCGBuffer	tempBuffer	 = MEM_POOL_ALLOC(32+_Buffer.len);

	// 2) Message를 만든다.
	tempBuffer.append<uint32_t>();
	tempBuffer.append<uint32_t>(CGMESSAGE::NETWORK::SOCKET::REMOTE_RESPONSE);
	tempBuffer.append<int>(iRequestID);
	tempBuffer.append<uint32_t>(dwRequestSerial);
	tempBuffer.append(_Buffer);
	tempBuffer.front<uint32_t>()	 = tempBuffer.len;

	// 3) 전송한다.
	return	pSender->Send(tempBuffer);
}

#define TRANSLATE_REQUEST_MESSAGE(msg, source)		if((msg.message==CGMESSAGE::SYSTEM::MESSAGE) && ((CGNETMSG&)msg).Buffer.front<uint32_t>(4)==CGMESSAGE::NETWORK::SOCKET::REMOTE_REQUEST) { msg=CGNETMSG_RESPONSE(source, msg);}
