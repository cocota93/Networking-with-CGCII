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
// CGNet::IO::ConnectableManager::CListKeepAliveActive
//
// 1. CGNet::IO::ConnectableManager::CListKeepAliveActive
//    1) Acceptor�� �޾� ���ӿ� ������ Socket�鿡 ���ؼ� Active-KeepAlive�� �����ϴ� 
//       Connectable Manager�̴�.
//    2) Active keep-alive�� �� Socket���� ������ ���۹��� �ð����κ��� �����ð��� 
//       ������ Keep alive�� �����ϱ� ���� Ping�� �����Ѵ�.
//       Ŭ���̾�Ʈ�� �� Ping�� ���۹����� Ping�� �ٽ� �����ϰ� �� ���̴�.
//       �׷��� �Ǹ� ������ ���۹��� �ð��� �ٽ� ����ǰ� �Ǿ� ��� Keep-alive��
//       �����ϰ� �Ǵ� ���̴�.
//        ���� Ŭ���̾�Ʈ���� Ping�� �ݼ����� �ʴ´ٸ� Ÿ�Ӿƿ��� �ɷ� ������
//       �����Ų��.
//    3) ���� Socket���� Keep Alive�� �ϰ� �ʹٸ� �̰��� ���� ���� Socket�� 
//       Keep alive Add-On�� ��ӹ޴� ���� ����.
//    4) EnableKeepAlive()�Լ��� DisableKeepAlive()�� ����Ͽ� Keep alive�����
//       �Ѱ� ���� �ִ�.
//       ������ Acceptor�������� �������ִ� Keep alive�� Socket���� Keep alive
//       ����� �Ѱ� ������ ����.
//    5) SetKeepAliveTimeOut()�Լ��� ����Ͽ� Keep alive Ÿ�Ӿƿ� �ð��� ������ 
//       �� �ִ�. (�⺻���� 2��(120000tick)���� �����Ǿ� �ִ�.)
//    6) SetPingInterval()�Լ��� ����Ͽ� Ping�� �����ϴ� ������ ������ �� �ִ�.
//    7) Keep alive�� ���е��� 1�� �����̱� ������ �ִ� 2���� ������ �� �� �ִ�.
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
	// Check) ���� KeepAlive�� false��� Keep Alive�� �������� �ʴ´�.
	RETURN_IF(m_bEnableKeepAlive==false, intptr_t(1));

	// 1) ������ Tick�� ��´�.
	auto	tickNow	 = TICK::now();

	// 2) Ping ���ۿ� �޽����� �����.
	CCGBuffer	bufferPing	 = MEM_POOL_ALLOC(16);
	bufferPing.append<uint32_t>(16);
	bufferPing.append<uint32_t>(CGMESSAGE_SYSTEM_PING_REQ);
	bufferPing.append<TICK::time_point>(tickNow);

	// 3) ��� Connectable�� ���ư��� Keep Alive �׽�Ʈ�� �����Ѵ�.
	LOCK(m_listConnectable)
	{
		for(auto& iter:m_listConnectable)
		{
			auto	pConnectable	= *iter;

			// - ������ ���� Receive tick�� ��´�.
			auto	tickLastReceive	 = pConnectable->Statistics_GetTickLastReceive();

			// Check) ���� Tick���� ������ Receive Tick�� ũ�ų� ������ ���� �������� �Ѿ��.
			CONTINUE_IF(tickNow<=tickLastReceive);

			// - ������ ���۹��� ���� ���� �ð��� ���Ѵ�.
			auto	toclGap	 = tickNow-tickLastReceive;

			// - ���� ������ ���۹��� �� �����ð��� PingInterval���� �������� Ping�� �����Ѵ�.
			if(tickdifferExecute>m_tickdifffPing)
			{
				pConnectable->Send(bufferPing);
			}

			// - ���� ������ ���۹��� �� �����ð��� Keep-Alive Time-Out�ð����� �������� ������ �����Ѵ�.
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