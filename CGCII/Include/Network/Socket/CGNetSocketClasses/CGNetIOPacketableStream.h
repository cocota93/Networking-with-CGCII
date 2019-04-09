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
/*!
 * @class NStream<TMSG_HEAD>
 *
 * @ingroup CGNet::IO::Packetable
 *
 * @brief Stream(TCP)용 Packetable Class
 *
 *   TCP용으로 제작된 제작된 Packetable이다.
 *   전송받아온 데이터를 Message단위로 잘라서 IMessageable에 넘겨주는 역할을 한다.
 *   Steam으로 연속적으로 전달되어 오는 데이터의 head를 읽어 설정된 Message
 *      크기로 나누어 IMessageable의 ProcessMessage()함수를 호출해 전달해준다.
 *
 */
 //-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Packetable
{

template <class TTYPE>
struct PRIMITIVE
{
	typedef	TTYPE	type;
};

template <class TMSG_HEAD=PRIMITIVE<uint32_t>>
class NStream :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISocket,						//     Packetable
	virtual public				CGNet::IO::IPacketable,					//     Packetable
	virtual protected			ICGMessageable,							//     Messageable
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
	typedef		TMSG_HEAD		TMESSAGE_HEAD;

// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	uint32_t			ProcessGetMessageSize(const TMSG_HEAD* _pHead) { return *reinterpret_cast<const uint32_t*>(_pHead); }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual	void				ProcessPreMessage(CGNETMSG& /*_Msg*/)	{}
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;

	virtual	void				ResetPacketable() override				{}
};

template <class TMSG_HEAD>
size_t NStream<TMSG_HEAD>::ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)
{
	//-----------------------------------------------------------------
	// Check) Debug를 위한 잘못된 값을 검사.
	//-----------------------------------------------------------------
	// 1) _Buffer.buf가 0이어서는 안된다.
	ERROR_THROW_IF(_Buffer.buf == nullptr, CGException::CNetThrow_InvalidMessage_BufferIsNULL(__FUNCTION__), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGNetBase: _Buffer.buf is nullptr [_Buffer.len: %u] ") _CGFUNCTION, _Buffer.len))

	// 2) _Buffer->len가 0이어서는 안된다.
	CGASSERT_ERROR(_Buffer.len!= 0)


	//-----------------------------------------------------------------
	// 1. 전송되어 왔을 때 처리
	//-----------------------------------------------------------------
	// Declare) 
	int			countMessage = 0;		// 처리한 패킷 수의 처리르 위해...

	// Declare) 임시 CGNETMSG (전달용)
	CGNETMSG	msg;

	// 1) 전달용 Message를 설정한다.
	msg.Buffer.set_reference(_Buffer.get_reference());
	msg.pSockAddr	 = _pSockAddr;

	// Declare) 
	CGD::buffer		message;

	// 2) Buffer의 Address와 Length를 써넣는다.
	message.buf		 = _Buffer.buf;
	message.len		 = sizeof(TMSG_HEAD);

	// Loop) RemainedSize가 GetSizeOfPacketHead()보다 작으면 끝냄.
	uint32_t	RemainedSize = _Buffer.len;

	try
	{
		while(RemainedSize >= sizeof(TMSG_HEAD))
		{
			// 3) Message 길이를 구한다.
			message.len = ProcessGetMessageSize((const TMSG_HEAD*)message.buf);

			// Check) 만약 tempNetBuffer.len이 TMSG_HEAD보다 작으면 잘못된 것이므로 Exception을 던진다.
			//        (주의: Message크기가 0Byte일 경우 Exception을 던지지 않으면 무한루프에 빠져버릴수 있다.)
			ERROR_THROW_IF(message.len<sizeof(TMSG_HEAD), CGException::CNetThrow_InvalidMessage_TooShortLength(__FUNCTION__), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGNetBase: Message size is too short[Message Size: %u] ") _CGFUNCTION, message.len) );

			// Check) MessageHead크기 보다 작으면 빠져나간다.
			BREAK_IF(message.len > RemainedSize);

			// 4) 전달용 Buffer에 address와 length를 써넣는다.
			((CGD::buffer&)msg.Buffer)	 = message;

			// 5) 훅함수 ProcessPreMessage()를 호출한다.
			ProcessPreMessage(msg);
		
			// 6) Message을 IMessageable로 전달하여 처리한다.
			ProcessMessage(msg);

			// 7) Message수를 증가시킨다.
			++countMessage;

			// 8) Message Data를 이동시킨다.
			message.buf		+= message.len;
			RemainedSize	-= message.len;

			// Check) 접속이 종료되었으면 바로 끝낸다.(접속을 종료해 버렸을 때 바로 종료시키기 위해)
			BREAK_IF(GetSocketHandle()==INVALID_SOCKET);
		}
	}
	catch(...)
	{
		// Statistiscs) 이때까지 처리된 Packet의 통계처리를 한다.
		Statistics_OnReceiveMessage(countMessage);

		// Reraise) 
		throw;
	}
	
	// Statistics) Receive Message수를 세린다.
	Statistics_OnReceiveMessage(countMessage);


	//-----------------------------------------------------------------
	// 2. 최종 정리...
	//-----------------------------------------------------------------
	// 1) 남은 Message을 설정한다.
	_Buffer.buf			 = message.buf;
	_Buffer.len			 = RemainedSize;

	// Return) 다음 Message의 크기를 return한다.
	return	static_cast<size_t>(message.len);
}


}
}
}
