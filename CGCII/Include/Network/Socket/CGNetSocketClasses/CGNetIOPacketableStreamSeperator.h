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
* @class NStreamSeperator<class TNCHAR=_CHAR>
*
* @ingroup CGNet::IO::Packetable
*
* @brief Web과 같은 문자열 Stream 메시지 처리를 위한 Packetable 클래스
*
*   Web과 같은 문자열로 된 Stream 메시지의 처리를 위한 Packetable 클래스다.
*   전송되어 오는 Stream 데이터를 문자열의 끝문자('/r/n')을 Sequencial Detect하여
*   메시지를 구분해 ProcessMessage()로 전달해 준다.
*   기본적으로 이 방법은 끝문자를 찾기 위해 모든 데이터를 차례로 읽어 비교를 해야
*   하므로 다른 방식에 비해 부하가 많이 든다.
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Packetable
{

template <class TNCHAR=_CHAR>
class NStreamSeperator :
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
	// 1) Get Line
	virtual	int					ProcessFindSeperator(_In_ TNCHAR* p_strPos, _In_ const TNCHAR* p_strEnd);

	// 2) ProcessPacket/PreMessage
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;
	virtual	void				ProcessPreMessage(CGNETMSG& /*_Msg*/)	{}

	// 3) Reset
	virtual	void				ResetPacketable() override				{}
};


template <class TNCHAR>
int NStreamSeperator<TNCHAR>::ProcessFindSeperator(_In_ TNCHAR* p_strPos, _In_ const TNCHAR* p_strEnd)
{
	for(int iLength=0; p_strPos<p_strEnd; ++iLength)
	{
		// Check) Seperator를 찾았을 경우!!! 
		if(*(p_strPos++)=='\r')
		{
			return	iLength;
		}
	}

	// Return) 찾지 못했다!
	return	0;
}


template <class TNCHAR>
size_t NStreamSeperator<TNCHAR>::ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)
{
	//-----------------------------------------------------------------
	// Check) Debug를 위한 잘못된 값을 검사.
	//-----------------------------------------------------------------
	// 1) _Buffer.buf가 0이어서는 안된다.
	CGASSERT_ERROR(_Buffer.buf != nullptr)

	// 2) _Buffer->len가 0이어서는 안된다.
	CGASSERT_ERROR(_Buffer.len!= 0)


	//-----------------------------------------------------------------
	// 1. 전송되어 왔을 때 처리
	//-----------------------------------------------------------------
	// Declare) 처리한 패킷 수의 처리르 위해...
	int			countMessage	 = 0;

	// Declare) 임시 CGNETMSG를 만든다.
	CGNETMSG	msg;

	msg.Buffer		 = CCGBuffer(CGD::buffer(_Buffer.buf, 0), _Buffer.get_reference());
	msg.pSockAddr	 = _pSockAddr;

	// Loop) Buffer의 끝까지 Seperator가 존재하는지 검사한다.
	TNCHAR*	pPos	 = (TNCHAR*)(_Buffer.buf);
	TNCHAR*	pEnd	 = (TNCHAR*)(_Buffer.buf+_Buffer.len);

	try
	{
		while(pPos<pEnd)
		{
			// 1) Seperator를 찾는다.
			_Buffer.len	 = ProcessFindSeperator(pPos, pEnd);

			// Check) 찾지 못했으면 여기서 끝낸다.
			BREAK_IF(_Buffer.len==0);

			// 2) 찾았으면 ProcessPreMessage()를 호출한다.
			ProcessPreMessage(msg);
		
			// 3) IMessageable로 메시지를 전달한다.
			ProcessMessage(msg);

			// 4) 처리한 Message수를 증가시킨다.
			++countMessage;

			// 5) 새로운 시작점을 설정한다.
			_Buffer.buf	+= (_Buffer.len+1)*sizeof(TNCHAR);

			// Check) 접속이 종료되었으면 바로 끝낸다.
			BREAK_IF(GetSocketHandle()==INVALID_SOCKET);
		}
	}
	catch(...)
	{
		// Statistiscs) 이 때까지 처리된 Packet의 통계처리를 한다.
		Statistics_OnReceiveMessage(countMessage);

		// Reraise) 
		throw;
	}

	// Statistics) Receive Message 수
	Statistics_OnReceiveMessage(countMessage);


	//-----------------------------------------------------------------
	// 2. 최종 정리...
	//-----------------------------------------------------------------
	// 1) 남은 Message를 설정한다.
	_Buffer.len		 = static_cast<uint32_t>((reinterpret_cast<char*>(pPos))-_Buffer.buf);

	// 2) 다음 Message의 크기를 남음 크기에 1024자분량을 더 확보하도록 한다.
	int		iSizeMessage	 = static_cast<int>(_Buffer.len+sizeof(_CHAR)*1024);

	// Return) 다음 Message의 크기를 return한다.
	return	MIN(iSizeMessage, 65536);
}


}
}
}
