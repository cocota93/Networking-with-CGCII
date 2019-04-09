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
* @class NStreamFixed<IMESSAGESIZE>
*
* @ingroup CGNet::IO::Packetable
*
* @brief 정해진 크기로 잘라 메시지를 구분하는 Stream(TCP)용 Packetable 클래스
*
*   정해진 크기로 잘라서 메시지를 만들어 ProgressMessage()로 넘기는 Packtable 클래스 
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Packetable
{

template<int IMESSAGESIZE>
class NStreamFixed :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISocket,						//     Packetable
	virtual public				CGNet::IO::IPacketable,					//     Packetable
	virtual protected			ICGMessageable,							//     Messageable
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual	void				ProcessPreMessage(CGNETMSG& /*_Msg*/)	{}
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;

	virtual	void				ResetPacketable() override				{}
};

template<int IMESSAGESIZE>
size_t NStreamFixed<IMESSAGESIZE>::ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)
{
	//-----------------------------------------------------------------
	// 설명) ProcessPacket
	//
	// - 해당 메모리 버퍼의 내용을 해석해서 하나의 Message단위로 잘라서 
	//   처리하는 작업을 수행하게 된다. 
	//   일반적으로 head의 크기는 제일 앞 2Byte에 기록되며 그다음 2Byte는
	//   Command로 사용된다. 그 이후에 필요에 따라 다양한 크기의 정보가
	//   붙어서 제공된다.
	//-----------------------------------------------------------------


	//-----------------------------------------------------------------
	// Check) Debug를 위한 잘못된 값을 검사.
	//-----------------------------------------------------------------
	// 2) _Buffer.buf가 0이어서는 안된다.
	CGASSERT(_Buffer.buf != nullptr, 0)

	// 3) _arrayBuffer->len가 0이어서는 안된다.
	CGASSERT(_Buffer.len != 0, 0)


	//-----------------------------------------------------------------
	// 1. 전송되어 왔을 때 처리
	//-----------------------------------------------------------------
	// Declare)
	int			countMessage	 = 0;

	// Declare) 임시 CCGBuffer를 만든다.
	CGNETMSG	msg;

	msg.Buffer		 = CCGBuffer(CGD::buffer(_Buffer.buf, IMESSAGESIZE), _Buffer.get_reference());
	msg.pSockAddr	 = _pSockAddr;

	// Loop) RemainedSize가 GetSizeOfPacketHead()보다 작으면 끝냄.
	uint32_t	RemainedSize	 = _Buffer.len;

	try
	{
		while(RemainedSize >= IMESSAGESIZE)
		{
			// 1) 훅함수 ProcessPreMessage()를 호출한다.
			ProcessPreMessage(msg);
		
			// 2) Message을 처리한다.
			ProcessMessage(msg);

			// 3) Paket수를 증가시킨다.
			++countMessage;

			// 4) Message Data를 이동시킨다.
			msg.Buffer.buf		+= IMESSAGESIZE;
			RemainedSize		-= IMESSAGESIZE;

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
	// 1) 남은 Message 설정한다.
	_Buffer.buf			 = msg.Buffer.buf;
	_Buffer.len			 = RemainedSize;
	
	// Return) 다음 Message의 크기를 return한다.
	return	static_cast<size_t>(msg.Buffer.len);
}


}
}
}