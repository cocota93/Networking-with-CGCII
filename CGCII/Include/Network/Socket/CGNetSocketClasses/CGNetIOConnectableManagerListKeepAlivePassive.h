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
// CGNet::IO::ConnectableManager::CListKeepAlivePassive
//
// 1. CGNet::IO::ConnectableManager::CListKeepAlivePassive
//    1) Acceptor�� �޾� ���ӿ� ������ Socket�鿡 ���ؼ� KeepAlive�� �����ϴ� 
//       Connectable Manager�̴�.
//       (�����ϰ� ���ϸ� Keep-Alive��� ���ٴ� Ghost Socket ���ű�� �Ҽ� �ִ�.)
//    2) �� Socket���� ������ ���۹��� �ð����κ��� �����ð��� ������ �� Socket�� 
//       ������ ������ѹ�����.
//       Active Keep alive�� �ٸ� ���� Active Keep alive�� ���� ������ ���۹���
//       �ð� ���ķ� ���� �ð��� ������ ������ �����ϱ� ���� Ping�� ������ �ʴ´ٴ�
//       ���� �ٸ���.
//       �� ���� �ð� ������ ���� ���ϸ� ���������.
//    3) ���� Socket���� Keep Alive�� �ϰ� �ʹٸ� �̰��� ���� ���� Socket�� 
//       Keep alive Add-On�� ��ӹ޴� ���� ����.
//    4) EnableKeepAlive()�Լ��� DisableKeepAlive()�� ����Ͽ� Keep alive�����
//       �Ѱ� ���� �ִ�.
//       ������ Acceptor�������� �������ִ� Keep alive�� Socket���� Keep alive
//       ����� �Ѱ� ������ ����.
//    5) SetKeepAliveTimeOut()�Լ��� ����Ͽ� Keep alive Ÿ�Ӿƿ� �ð��� ������ 
//       �� �ִ�. (�⺻���� 2��(120000tick)���� �����Ǿ� �ִ�.)
//    6) Keep alive�� ���е��� 1�� �����̱� ������ �ִ� 2���� ������ �� �� �ִ�.
//
// 2. Passive�� Active Keep-alive �߰����� ����
//    1) �Ϲ������� Server�� ���忡���� Passive Keep-alive�� ����ϰ� Client�ʿ���
//       �����ð����� Keep-alive�� Message�� �����ϵ��� �ϴ� ���� Server�� ����
//       ������ �ξ� ȿ�����̴�.
//    2) Active Keep-alive�� Keep-Alive�� ���� Ping�� ���� ������ �ϱ� ������
//       Server������ �� ���� ���ϸ� �ְ� �� �Ӹ� �ƴ϶� ���������� �� ����
//       Traffic�� �߻���Ų��.
//       ���� Client���� ���� �ð����� Keep alive�� Message�� ������ �� ����
//       ��Ȳ���� ����ϴ� ���� ����.
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
		// 1) Connectable�� �߰��Ѵ�.
		bResult	 = CGNet::IO::ConnectableManager::CList<TCONNECTABLE>::AddConnectable(_pConnectable);

		// Check) �߰��� �����ߴٸ� �׳� ������.
		RETURN_IF(bResult==false, false);

		// 2) ���� ù��° �����ڶ�� KeepAlive�� �����Ѵ�.
		if(m_listConnectable.size()==1)
		{
			// - Executor�� ���δ�.
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
		// 1) Connectable�� �����Ѵ�.
		bResult	 = CGNet::IO::ConnectableManager::CList<TCONNECTABLE>::RemoveConnectable(_pConnectable);

		// Check) ���ſ� �����ߴٸ� ������.
		RETURN_IF(bResult==false, false);

		// 2) ���� �����ڰ� 0����� KeepAlive�� �����.
		if(m_listConnectable.size()==0)
		{
			// - Executor���� ������.
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
	// 1) ��� ������ �����Ѵ�.
	CGNet::IO::ConnectableManager::CList<TCONNECTABLE>::RemoveAllConnectable();

	// 2) Executor���� ������.
	LOCK(m_listConnectable)
	{
		// - Executor���� �����.
		CGExecutor::Default::GetInstance()->UnregisterExecutor(this);

		// Trace) 
		CGLOG_INFO_LOW(_CGTEXT("(Prgr ) Remove All Connectable"));
	}
}

template <class TCONNECTABLE>
intptr_t CListKeepAlivePassive<TCONNECTABLE>::ProcessExecute(_In_ intptr_t /*_Return*/, _In_ size_t /*_Param*/)
{
	// Check) ���� KeepAlive�� false��� Keep Alive�� �������� �ʴ´�.
	RETURN_IF(m_bEnableKeepAlive==false, intptr_t(1));

	// 1) ������ Tick�� ��´�.
	auto	tickNow	 = TICK::now();

	// 2) ��� Connectable�� ���ư��� Keep Alive �׽�Ʈ�� �����Ѵ�.
	LOCK(m_listConnectable)
	{
		for(auto& iter:m_listConnectable)
		{
			auto	pConnectable	= iter;

			// - ������ ���� Receive tick�� ��´�.
			auto	tickLastReceive	 = pConnectable->Statistics_GetTickLastReceive();

			// Check) ���� Tick���� ������ Receive Tick�� ũ�ų� ������ ���� �������� �Ѿ��.
			CONTINUE_IF(tickNow<=tickLastReceive);

			// 2) ������ ���۹��� ���� ���� �ð��� ���Ѵ�.
			auto	tickdifferExecute	 = tickNow-tickLastReceive;

			// Check) ���� ������ ���۹��� �� �����ð��� Keep-Alive Time-Out�ð����� �������� ������ �����Ѵ�.
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