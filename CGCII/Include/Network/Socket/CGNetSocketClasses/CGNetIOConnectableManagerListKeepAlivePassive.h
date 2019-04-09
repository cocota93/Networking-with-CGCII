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
// CGNet::IO::ConnectableManager::CListKeepAlivePassive
//
// 1. CGNet::IO::ConnectableManager::CListKeepAlivePassive
//    1) Acceptor가 받아 접속에 성공한 Socket들에 대해서 KeepAlive를 수행하는 
//       Connectable Manager이다.
//       (엄밀하게 말하면 Keep-Alive라기 보다는 Ghost Socket 제거기라 할수 있다.)
//    2) 각 Socket에서 마지막 전송받은 시간으로부터 일정시간이 지나면 그 Socket의 
//       접속을 종료시켜버린다.
//       Active Keep alive와 다른 점은 Active Keep alive와 같이 마지막 전송받은
//       시간 이후로 일정 시간이 지나면 접속을 유지하기 위해 Ping을 날리지 않는다는
//       접이 다르다.
//       즉 일정 시간 전송을 받지 못하면 끊어버린다.
//    3) 만약 Socket별로 Keep Alive를 하고 싶다면 이것을 쓰지 말고 Socket에 
//       Keep alive Add-On을 상속받는 것이 좋다.
//    4) EnableKeepAlive()함수와 DisableKeepAlive()를 사용하여 Keep alive기능을
//       켜고 끌수 있다.
//       하지만 Acceptor차원에서 제공해주는 Keep alive는 Socket별로 Keep alive
//       기능을 켜고 끌수는 없다.
//    5) SetKeepAliveTimeOut()함수를 사용하여 Keep alive 타임아웃 시간을 설정할 
//       수 있다. (기본값은 2분(120000tick)으로 설정되어 있다.)
//    6) Keep alive의 정밀도는 1초 단위이기 때문에 최대 2초의 오차가 날 수 있다.
//
// 2. Passive와 Active Keep-alive 추가적인 설명
//    1) 일반적으로 Server의 입장에서는 Passive Keep-alive를 사용하고 Client쪽에서
//       일정시간마다 Keep-alive용 Message를 전송하도록 하는 것이 Server의 입장
//       에서는 훨씬 효율적이다.
//    2) Active Keep-alive는 Keep-Alive를 위해 Ping을 먼저 날려야 하기 때문에
//       Server측에서 더 많은 부하를 주게 될 뿐만 아니라 전반적으로 더 많은
//       Traffic을 발생시킨다.
//       따라서 Client에서 일정 시간마다 Keep alive용 Message를 전송할 수 없는
//       상황에만 사용하는 것이 좋다.
//
//-----------------------------------------------------------------------------
#define	KEEPALIVE_PASSIVE	CGNet::IO::ConnectableManager::CListKeepAlivePassive

namespace CGNet
{
namespace IO
{
namespace ConnectableManager
{

template <class TCONNECTABLE=CGNet::IO::IConnectable>
class CListKeepAlivePassive : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNet::IO::ConnectableManager::CList<TCONNECTABLE>,//     Connectable manager
	public						CGExecutor::NExecutable					// (@) Executable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CListKeepAlivePassive();
	virtual	~CListKeepAlivePassive();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Add/Remove/RemoveAll
	virtual	bool				AddConnectable(_In_ IConnectable* _pConnectable) override;
	virtual	bool				RemoveConnectable(_In_ IConnectable* _pConnectable) override;
			void				RemoveAllConnectable();

	// 2) Keep alive Enable/Disable
			bool				IsEnableKeepAlive() const					{	return m_bEnableKeepAlive;}
			bool				EnableKeepAlive(_In_ bool p_bResult = true) { m_bEnableKeepAlive = p_bResult; }
			bool				DisableKeepAlive()							{	m_bEnableKeepAlive=false;}

	// 3) Keep-alive Time-Out
			TICK::duration		GetKeepAliveTimeOut() const					{	return m_tickTimeOutKeepAlive;}
			void				SetKeepAliveTimeOut(_In_ TICK::duration p_tickTimeOut){ m_tickTimeOutKeepAlive = p_tickTimeOut; }


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			bool				m_bEnableKeepAlive;
			TICK::duration		m_tickTimeOutKeepAlive;

protected:
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


template <class TCONNECTABLE>
CListKeepAlivePassive<TCONNECTABLE>::CListKeepAlivePassive() :
	CGExecutor::NExecutable(TICK::seconds(1)),
	m_bEnableKeepAlive(true),
	m_tickTimeOutKeepAlive(TICK::seconds(120))
{
}

template <class TCONNECTABLE>
CListKeepAlivePassive<TCONNECTABLE>::~CListKeepAlivePassive()
{
}

template <class TCONNECTABLE>
bool CListKeepAlivePassive<TCONNECTABLE>::AddConnectable(IConnectable* _pConnectable)
{
	// Declare) 
	bool	bResult;

	LOCK(m_listConnectable)
	{
		// 1) Connectable을 추가한다.
		bResult	 = CGNet::IO::ConnectableManager::CList<TCONNECTABLE>::AddConnectable(_pConnectable);

		// Check) 추가에 실패했다면 그냥 끝낸다.
		RETURN_IF(bResult==false, false);

		// 2) 만약 첫번째 접속자라면 KeepAlive를 시작한다.
		if(m_listConnectable.size()==1)
		{
			// - Executor에 붙인다.
			CGExecutor::Default::GetInstance()->RegisterExecutor(this);

			// Trace)
			CGLOG_INFO_LOW(_CGTEXT("(Prgr ) Start Keep Alive"));
		}
	}

	// Return) Return~
	return	bResult;
}

template <class TCONNECTABLE>
bool CListKeepAlivePassive<TCONNECTABLE>::RemoveConnectable(IConnectable* _pConnectable)
{
	// Declare) 
	bool	bResult;

	LOCK(m_listConnectable)
	{
		// 1) Connectable을 제거한다.
		bResult	 = CGNet::IO::ConnectableManager::CList<TCONNECTABLE>::RemoveConnectable(_pConnectable);

		// Check) 제거에 실패했다면 끝낸다.
		RETURN_IF(bResult==false, false);

		// 2) 만약 접속자가 0개라면 KeepAlive를 멈춘다.
		if(m_listConnectable.size()==0)
		{
			// - Executor에서 떼낸다.
			CGExecutor::Default::GetInstance()->UnregisterExecutor(this);

			// Trace) 
			CGLOG_INFO_LOW(_CGTEXT("(Prgr ) Closing Keep Alive\n"));
		}
	}

	// Return) Return~
	return	bResult;
}

template <class TCONNECTABLE>
void CListKeepAlivePassive<TCONNECTABLE>::RemoveAllConnectable()
{
	// 1) 모든 접속을 종료한다.
	CGNet::IO::ConnectableManager::CList<TCONNECTABLE>::RemoveAllConnectable();

	// 2) Executor에서 떼낸다.
	LOCK(m_listConnectable)
	{
		// - Executor에서 떼어낸다.
		CGExecutor::Default::GetInstance()->UnregisterExecutor(this);

		// Trace) 
		CGLOG_INFO_LOW(_CGTEXT("(Prgr ) Remove All Connectable"));
	}
}

template <class TCONNECTABLE>
intptr_t CListKeepAlivePassive<TCONNECTABLE>::ProcessExecute(_In_ intptr_t /*_Return*/, _In_ size_t /*_Param*/)
{
	// Check) 만약 KeepAlive가 false라면 Keep Alive를 수행하지 않는다.
	RETURN_IF(m_bEnableKeepAlive==false, intptr_t(1));

	// 1) 현재의 Tick을 얻는다.
	auto	tickNow	 = TICK::now();

	// 2) 모든 Connectable을 돌아가며 Keep Alive 테스트를 수행한다.
	LOCK(m_listConnectable)
	{
		for(auto& iter:m_listConnectable)
		{
			auto	pConnectable	= iter;

			// - 마지막 받은 Receive tick을 얻는다.
			auto	tickLastReceive	 = pConnectable->Statistics_GetTickLastReceive();

			// Check) 현재 Tick보다 마지막 Receive Tick이 크거나 같으면 다음 소켓으로 넘어간다.
			CONTINUE_IF(tickNow<=tickLastReceive);

			// 2) 마지막 전송받은 이후 지난 시간을 구한다.
			auto	tickdifferExecute	 = tickNow-tickLastReceive;

			// Check) 만약 마지막 전송받은 후 지난시간이 Keep-Alive Time-Out시간보다 지났으면 접속을 종료한다.
			if(tickdifferExecute>m_tickTimeOutKeepAlive)
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