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
// CGNet::IO::Connector::NTCPReconnect (�ڵ������� ����� ���� TCP ������)
//
// 1. CGNet::IO::Connective::NTCPReconnect�̶�!
//    1) �ڵ� ������ ����� �ִ� Connector�̴�.
//    2) CGNet::IO::Connector::NTCP�� ��ӹ޾� ���� ����� �ڵ� ������ ����� �߰�
//       �� ���̴�.
//    3) CGNet::IO::IConnectable�� ���� ���߻�ӹ޾Ƽ� ����ϵ��� ����Ǿ���.
//
// 2. �ٽ� �Լ���.
//    1) �������� �⺻������ Connect()�� ���� �� �ϳ��� �ּҿ��� �̷������.
//    2) �ʿ信 ���� ���� �ּҷ� �������� ������ �� �ִ�.
//       - ������ ����Ǹ� ��ϵ� �ּҵ鿡 ���ʴ�� ���ӿ䱸�� �����ϰ� �ȴ�.
//
//		 - ������ �ּҸ� �߰��ϰ� ������ �� �ִ�.
//			bool AddPeerAddress((LPCSOCKADDR _paddrPeer);
//			bool RemovePeerAddress(LPCSOCKADDR _paddrPeer);
//          void RemoveAllPeerAddress();
//
//    3) ������ Connect�Լ��� ����Ͽ� �����Ѵ�.
//    4) Address�� ���� ���� ��� ��ϵ� Peer�ּҷ� ������ �õ��Ѵ�.
//    5) �Ʒ��� �Լ��� ����Ͽ�  ������ ����� �Ѱų� �� �� �ִ�.
//       
//       void EnableReconnect(bool _bEnable=true);
//       void DisableReconnect();
//
//       �� �Ʒ��� �Լ��� ����Ͽ� ������ ����� ���ۿ��θ� Ȯ���� �� �ִ�.
//
//       bool IsEnable() const
//
//    6) �Ʒ��� �Լ���  ����Ͽ� ������ �õ�  �ð��� �����ϰų� ���� �� �ִ�.
//       ������ �õ��� ������ ������ ������ �������� ���� ����� �ȴ�.
//       ���� ������ ���� ������ �õ� �ð� ���Ŀ� ������ ����Ǿ���
//       ��� �ٷ� �������� ����ȴ�.
//
//       void			SetReconnectInterval(TICK::duration p_tick);
//       TICK::duration	GetReconnectInterval() const;
//
//    7) ������ �� ���� ��� ����� ����Ǿ�� �Ѵٸ� ���� virtual�Լ���
//       �������Ͽ� ����� �߰��� �� �ִ�.
//
//       virtual void OnRequestReconnect(CGNet::IO::IConnective* _pConnective);
// 
//    
//    ����) ������ ������ ���� �ݵ�� �Ʒ��� ���� DisableReconnect()�Լ��� 
//          ȣ���Ͽ� ������ ���� ������ �ٽ� ������ ������ �� �ִ�.
//
//           pSocket->DisableReconnection();
//           pSocket->CloseSocket();
//
// 3. Initialize/Start String
//
//	  "[Name]/AddressFormat"		Address Format ("IPv4", "IPv6Prefer", "IPv6", "IPv4Prefer", "default")
//    "[Name]/Address"				������ �ּ�(�ּҿ� ��Ʈ ��� ����)
//	  "[Name]/Port"					������ ��Ʈ
//	  "[Name]/EnableReconnection"	�������� Ȱ��ȭ�Ѵ�.
//	  "[Name]/DisableReconnection"	�������� ��Ȱ��ȭ�Ѵ�.
//	  "[Name]/Reconnection"			������ ���¸� �����Ѵ�.(true/false)
//
//    ��)  ��ü���� "NAME"�̶�� �Ѵٸ�....
//
//		   CGMSG msgContext;
//         msgContext.Setting["NAME"]["AddressFormat"]		  = "IPv6";	// "IPv4", "IPv4Prefer", "IPv6", "IPv6Prefer"
//         msgContext.Setting["NAME"]["Address"]			  = "192.168.0.100";
//         msgContext.Setting["NAME"]["Port"]				  = 20000;
//         msgContext.Setting["NAME"]["Reconnection"]		  = "true";	// "true", "false", "default"
//         msgContext.Setting["NAME"]["ReconnectionInterval"] = 1000;	// millisecond
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connector
{

class NTCPReconnect :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Connector::NTCP,				// (I) Socket
	virtual public				CGNet::IO::IConnective					// (I) Connector
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NTCPReconnect();
			NTCPReconnect(const char* _strName);
			NTCPReconnect(const wchar_t* _strName);
	virtual	~NTCPReconnect();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Start
			bool				Start(CGMSG_CONTEXT& _Msg) override													{ return NCGStartable::Start(_Msg);}
			bool				Start()																				{ return Connect();}
			bool				Start(_In_ const SOCKADDR_CGNETWORK& _addrHost)										{ return Connect(_addrHost);}

			bool				Start(_In_z_ const _CHAR* _pszHostAddress, _In_ uint16_t _nHostPort=0)				{ return Connect(_pszHostAddress, _nHostPort);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_ uint16_t _nHostPort=0)			{ return Connect(_pszHostAddress, _nHostPort);}
			bool				Start(_In_z_ const _CHAR* _pszHostAddress, _In_z_ const _CHAR* _strService)			{ return Connect(_pszHostAddress, _strService);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_z_ const _CHAR_SUB* _strService)	{ return Connect(_pszHostAddress, _strService);}

			bool				Start(_In_z_ const _CHAR* _pszHostAddress, _In_ uint16_t _nHostPort, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)					{ return Connect(_pszHostAddress, _nHostPort, _pSockAddr);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_ uint16_t _nHostPort, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)				{ return Connect(_pszHostAddress, _nHostPort, _pSockAddr);}
			bool				Start(_In_z_ const _CHAR* _pszHostAddress, _In_z_ const _CHAR* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)			{ return Connect(_pszHostAddress, _strService, _pSockAddr);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_z_ const _CHAR_SUB* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)	{ return Connect(_pszHostAddress, _strService, _pSockAddr);}

	// 2) �������� �ּҸ� �߰�/����/��λ��� �Ѵ�.(���� ���� Address�� ����� ���ư��� ���ӵȴ�.)
			bool				AddPeerAddress(_In_ const SOCKADDR_CGNETWORK& _rPeerAddress);
			bool				RemovePeerAddress(_In_ const SOCKADDR_CGNETWORK& _rPeerAddress);
			void				RemoveAllPeerAddress();
	   
	// 3) �ڵ� ������ Enable/Disable�Լ�.
			void				EnableReconnect(_In_ bool _bEnable = true)	{ m_bReconnectEnable = _bEnable; }
			void				DisableReconnect()							{	m_bReconnectEnable=false;}

	// 4) Enable�Լ�.
	virtual	bool				IsEnable() const override					{ return IsReconnectEnable();}
			bool				IsReconnectEnable() const					{ return m_bReconnectEnable; }

	// 5) ������ ���� (������ 1tick(1ms)�̸� �⺻���� 10��(10000)�̴�.)
			void				SetReconnectInterval(_In_ TICK::duration p_tick){ m_tickReconnectionInterval = p_tick; }
			TICK::duration		GetReconnectInterval() const				{	return m_tickReconnectionInterval;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) �������� �õ��ϱ� �� ȣ��Ǵ� �Լ�.
	virtual	void				OnRequestReconnect(CGNet::IO::IConnective* /*_pConnective*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) RequestConnect
	virtual	bool				ProcessRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _addrPeer) override;

	// 2) ProcessConnect
	virtual	void				ProcessConnect(_In_ uintptr_t _Return) override;

	// 3) Connective
	virtual	void				ProcessConnectiveConnect(_In_ CGNet::IO::IConnectable* _pConnectable, _In_ uintptr_t _Return) override;
	virtual	void				ProcessConnectiveDisconnect(_In_ CGNet::IO::IConnectable* _pConnectable) override;

	// 4) Start/Stop
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;
	virtual void				_ProcessStopping() override;

	// 5) Reconnect�� �����ϴ� �Լ��̴�.
			void				ProcessWaitReconnect();
			void				RequestReconnect();
			void				CancelReconnector();
	
protected:
	// 1) Address List
			LOCKABLE<circular_list<SOCKADDR_CGNETWORK>>	m_listPeerAddress;
			circular_list<SOCKADDR_CGNETWORK>::const_iterator	m_iterNowPeerAddress;

	// 2) Enable
			bool				m_bReconnectEnable;
			TICK::duration		m_tickReconnectionInterval;

	// 3) ��������� Tick (Dealy�� �ִ� �������� ���� ����Ѵ�.)
			TICK::time_point	m_tickDisconnected;

	// Definition) 
			class CReconnector;

	// 4) Reconnector
			CGPTR<CReconnector>	m_pReconnector;
			bool				m_bReconnecting;
			LOCKABLE<>			m_csReconnector;
};


}
}
}