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
/*!
 * @class NStream<PRIMITIVE<TMSG_HEAD>>
 *
 * @ingroup CGNet::IO::Packetable
 *
 * @brief Stream(TCP)�� Packetable Class
 *
 *   TCP������ ���۵� ���۵� Packetable�� Ưȭ�� Ŭ�����̴�.
 *   ���� TMSG_HEAD�� ������ Ŭ������ �⺻���̰� ��ü�� Message�� ũ�� ����
 *   ��� ProcessGetMessageSize()�Լ��� ȣ������ �ʵ��� �� Ŭ�����̴�.
 *   ������� Message Head�� char, short, int, uint�� ����� ���̴�.
 *
 */
 //-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Packetable
{

template <class TMSG_HEAD>
class NStream<PRIMITIVE<TMSG_HEAD>> :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISocket,						//     Packetable
	virtual public				CGNet::IO::IPacketable,					//     Packetable
	virtual protected			ICGMessageable,							//     Messageable
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
	typedef		TMSG_HEAD		TMESSAGE_HEAD;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual	void				ProcessPreMessage(CGNETMSG& /*_Msg*/)	{}
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;

	virtual	void				ResetPacketable() override				{}
};

template <class TMSG_HEAD>
size_t NStream<PRIMITIVE<TMSG_HEAD>>::ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)
{
	//-----------------------------------------------------------------
	// Check) Debug�� ���� �߸��� ���� �˻�.
	//-----------------------------------------------------------------
	// 1) _Buffer.buf�� 0�̾�� �ȵȴ�.
	ERROR_THROW_IF(_Buffer.buf == nullptr, CGException::CNetThrow_InvalidMessage_BufferIsNULL(__FUNCTION__), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGNetBase: _Buffer.buf is nullptr[_Buffer.len: %u] ") _CGFUNCTION, _Buffer.len))

	// 2) _Buffer->len�� 0�̾�� �ȵȴ�.
	CGASSERT_ERROR(_Buffer.len!= 0)


	//-----------------------------------------------------------------
	// 1. ���۵Ǿ� ���� �� ó��
	//-----------------------------------------------------------------
	// Declare) 
	int	countMessage = 0;		// ó���� Message �� ����� ����

	// Declare) �ӽ� CGNETMSG (���޿�)
	CGNETMSG	msg;

	// 1) Messageable�� ������ Message�� �ۼ��Ѵ�.
	msg.Buffer.set_reference(_Buffer.get_reference());
	msg.pSockAddr	 = _pSockAddr;

	// Declare) 
	CGD::buffer		message;

	// 2) Buffer�� Address�� Length�� ��ִ´�.
	message.buf		 = _Buffer.buf;
	message.len		 = sizeof(TMSG_HEAD);

	// Loop) RemainedSize�� GetSizeOfPacketHead()���� ������ ����.
	uint32_t	RemainedSize = _Buffer.len;

	try
	{
		while(RemainedSize >= sizeof(TMSG_HEAD))
		{
			// 3) Message ���̸� ���Ѵ�.
			message.len = *(const TMSG_HEAD*)message.buf;

			// Check) ���� tempNetBuffer.len�� TMSG_HEAD���� ������ �߸��� ���̹Ƿ� Exception�� ������.
			//        (����: Messageũ�Ⱑ 0Byte�� ��� Exception�� ������ ������ ���ѷ����� ���������� �ִ�.)
			ERROR_THROW_IF(message.len<sizeof(TMSG_HEAD), CGException::CNetThrow_InvalidMessage_TooShortLength(__FUNCTION__), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGNetBase: Message length is too short[Message Size: %u] ") _CGFUNCTION, message.len) );

			// Check) MessageHeadũ�� ���� ������ ����������.
			BREAK_IF(message.len > RemainedSize);

			// 4) ���޿� Buffer�� address�� length�� ��ִ´�.
			((CGD::buffer&)msg.Buffer)	 = message;

			// 5) ���Լ� ProcessPreMessage()�� ȣ���Ѵ�.
			ProcessPreMessage(msg);
		
			// 6) Message�� IMessageable�� �����Ͽ� ó���Ѵ�.
			ProcessMessage(msg);

			// 7) Message���� ������Ų��.
			++countMessage;

			// 8) Message Data�� �̵���Ų��.
			message.buf		+= message.len;
			RemainedSize	-= message.len;

			// Check) ������ ����Ǿ����� �ٷ� ������.
			BREAK_IF(GetSocketHandle()==INVALID_SOCKET);
		}
	}
	catch(...)
	{
		// Statistiscs) �̶����� ó���� Packet�� ���ó���� �Ѵ�.
		Statistics_OnReceiveMessage(countMessage);

		// Reraise) 
		throw;
	}
	
	// Statistics) Receive Message���� ������.
	Statistics_OnReceiveMessage(countMessage);


	//-----------------------------------------------------------------
	// 2. ���� ����...
	//-----------------------------------------------------------------
	// 1) ó���� ���� �����͸� �����Ѵ�.
	_Buffer.buf			 = message.buf;
	_Buffer.len			 = RemainedSize;

	// Return) ó������ Message�� ũ�⸦ return�Ѵ�.
	return	static_cast<size_t>(message.len);
}


}
}
}
