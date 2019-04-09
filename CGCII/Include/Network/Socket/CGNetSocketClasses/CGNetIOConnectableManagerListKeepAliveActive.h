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
// CGNet::IO::ConnectableManager::CListKeepAliveActive
//
// 1. CGNet::IO::ConnectableManager::CListKeepAliveActive
//    1) Acceptor가 받아 접속에 성공한 Socket들에 대해서 Active-KeepAlive를 수행하는 
//       Connectable Manager이다.
//    2) Active keep-alive란 각 Socket에서 마지막 전송받은 시간으로부터 일정시간이 
//       지나면 Keep alive를 유지하기 위해 Ping을 전송한다.
//       클라이언트는 이 Ping을 전송받으면 Ping을 다시 전송하게 될 것이다.
//       그렇게 되면 마지막 전송받은 시간이 다시 연장되게 되어 계속 Keep-alive를
//       유지하게 되는 것이다.
//        만약 클라이언트에서 Ping을 반송하지 않는다면 타임아웃에 걸려 접속을
//       종료시킨다.
//    3) 만약 Socket별로 Keep Alive를 하고 싶다면 이것을 쓰지 말고 Socket에 
//       Keep alive Add-On을 상속받는 것이 좋다.
//    4) EnableKeepAlive()함수와 DisableKeepAlive()를 사용하여 Keep alive기능을
//       켜고 끌수 있다.
//       하지만 Acceptor차원에서 제공해주는 Keep alive는 Socket별로 Keep alive
//       기능을 켜고 끌수는 없다.
//    5) SetKeepAliveTimeOut()함수를 사용하여 Keep alive 타임아웃 시간을 설정할 
//       수 있다. (기본값은 2분(120000tick)으로 설정되어 있다.)
//    6) SetPingInterval()함수를 사용하여 Ping을 전송하는 간격을 설정할 수 있다.
//    7) Keep alive의 정밀도는 1초 단위이기 때문에 최대 2초의 오차가 날 수 있다.
//
//
//-----------------------------------------------------------------------------
#define	KEEPALIVE_ACTIVE	CGNet::IO::ConnectableManager::CListKeepAliveActive

namespace CGNet
{
namespace IO
{
namespace ConnectableManager
{

template <class TCONNECTABLE=CGNet::IO::IConnectable>
class CListKeepAliveActive : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CListKeepAlivePassive<TCONNECTABLE>		//     Connectable manager
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CListKeepAliveActive();
	virtual	~CListKeepAliveActive();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Ping Send Gap
			TICK::duration		GetPingInterval() const					{	return m_tickdifffPing;}
			void				SetPingInterval(_In_ TICK::duration p_qwPingInterval){ m_tickdifffPing = p_qwPingInterval; }


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			TICK::duration		m_tickdifffPing;
};


template <class TCONNECTABLE>
CListKeepAliveActive<TCONNECTABLE>::CListKeepAliveActive() :
	m_tickdifffPing(TICK::seconds(1))
{
}

template <class TCONNECTABLE>
CListKeepAliveActive<TCONNECTABLE>::~CListKeepAliveActive()
{
}

template <class TCONNECTABLE>
intptr_t CListKeepAliveActive<TCONNECTABLE>::ProcessExecute(_In_ intptr_t /*_Return*/, _In_ size_t /*_Param*/)
{
	// Check) 만약 KeepAlive가 false라면 Keep Alive를 수행하지 않는다.
	RETURN_IF(m_bEnableKeepAlive==false, intptr_t(1));

	// 1) 현재의 Tick을 얻는다.
	auto	tickNow	 = TICK::now();

	// 2) Ping 전송용 메시지를 만든다.
	CCGBuffer	bufferPing	 = MEM_POOL_ALLOC(16);
	bufferPing.append<uint32_t>(16);
	bufferPing.append<uint32_t>(CGMESSAGE_SYSTEM_PING_REQ);
	bufferPing.append<TICK::time_point>(tickNow);

	// 3) 모든 Connectable을 돌아가며 Keep Alive 테스트를 수행한다.
	LOCK(m_listConnectable)
	{
		for(auto& iter:m_listConnectable)
		{
			auto	pConnectable	= *iter;

			// - 마지막 받은 Receive tick을 얻는다.
			auto	tickLastReceive	 = pConnectable->Statistics_GetTickLastReceive();

			// Check) 현재 Tick보다 마지막 Receive Tick이 크거나 같으면 다음 소켓으로 넘어간다.
			CONTINUE_IF(tickNow<=tickLastReceive);

			// - 마지막 전송받은 이후 지난 시간을 구한다.
			auto	toclGap	 = tickNow-tickLastReceive;

			// - 만약 마지막 전송받은 후 지난시간이 PingInterval보다 지났으면 Ping을 전송한다.
			if(tickdifferExecute>m_tickdifffPing)
			{
				pConnectable->Send(bufferPing);
			}

			// - 만약 마지막 전송받은 후 지난시간이 Keep-Alive Time-Out시간보다 지났으면 접속을 종료한다.
			if(tickdifferExecute>m_dwTimeOutKeepAlive)
			{
				pConnectable->ProcessCloseSocket(SOCKET_REASON_ACTIVE | SOCKET_REASON_ABORTIVE | SOCKET_REASON_KEEP_ALIVE_TIME_OUT);
			}
		}
	}

	// Return) Success!
	return	intptr_t(0);
}


}
}
}