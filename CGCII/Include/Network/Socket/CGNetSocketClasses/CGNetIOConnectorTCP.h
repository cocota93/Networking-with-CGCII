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
// CGNet::IO::Connector::NTCP (TCP ������)
//
// 1. CGNet::IO::Connector::NTCP�̶�!
//    1) TCP Socket�� Client ���忡�� ������...
//    2) 
//    3) �⺻������ ICGNameable�� ��ӹ޾� �̸��� ������ �� �ִ�.
//
// 2. �߿� �Լ�.
//    1) �Ϲ����� ����� CGNet::IO::IConnector�� ���ǵ� �پ��� ������ Connect(...)
//		 �Լ��� Ȱ���Ѵ�.
//    2) ���� Connect�� ��û���� �� ó���Ǿ�� �ϴ� ���� �ִٸ� ������ �Լ���
//       �������Ͽ� ������ �� �ִ�.
//
//       virtual void OnRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _paddrPeer);
//
//    ����) ICGExecutable�� ��ӹ޾� ó���ϹǷ� �� Ŭ������ ��ӹ��� Ŭ��������
//          ProcessExecute()�� �������ϸ� ����ó���� ���� ���� �� �ִ�.
// 
// 3. Initialize/Start String
//
//	  ["NAME"]["AddressFormat"]		Address Format ("IPv4", "IPv6", "IPv6prefer", "IPv4prefer", "default") (Optional:Default="IPv4")
//    ["NAME"]["Address"]			������ �ּ�
//	  ["NAME"]["Port"]				������ ��Ʈ
//
//    ��)  ��ü���� "NAME"�̶�� �Ѵٸ�....
//
//		   CGMSG msgContext;
//         msgContext.Setting["NAME"]["AddressFormat"]	  = "IPv6";	// "IPv4", "IPv4Prefer", "IPv6", "IPv6Prefer"
//         msgContext.Setting["NAME"]["Address"]		 = "192.168.0.100";
//         msgContext.Setting["NAME"]["Port"]			 = 20000;
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connector
{

class NTCP :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IConnector,
	virtual protected			CGNet::IO::IConnectable,
	public						CGNameable::NString,
	public						CGNet::IO::Binder::NTCP,
	public						NCGObjectState,
	public						NCGStartable,
	public						NCGInitializable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NTCP();
			NTCP(const char* _strName);
			NTCP(const wchar_t* _strName);
	virtual	~NTCP();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Start
			bool				Start(CGMSG_CONTEXT& _Msg) override																								{ return NCGStartable::Start(_Msg);}
			bool				Start()																															{ return Connect();}
			bool				Start(_In_ const SOCKADDR_CGNETWORK& _addrPeer)																					{ return Connect(_addrPeer);}
			bool				Start(_In_ const SOCKADDR_IN& _addrPeer)																						{ return Connect(_addrPeer);}
			bool				Start(_In_ const SOCKADDR_IN6& _addrPeer)																						{ return Connect(_addrPeer);}
			bool				Start(_In_ LPCSOCKADDR _addrPeer, _In_ int _addrLength)																			{ return Connect(_addrPeer, _addrLength);}

			bool				Start(_In_z_ const _CHAR* _pszaddrPeer, _In_ uint16_t _portPeer=0, ADDRESS_FAMILY _afPriority=AF_INET)							{ return Connect(_pszaddrPeer, _portPeer, _afPriority);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_ uint16_t _portPeer=0, ADDRESS_FAMILY _afPriority=AF_INET)						{ return Connect(_pszaddrPeer, _portPeer, _afPriority);}
			bool				Start(_In_z_ const _CHAR* _pszaddrPeer, _In_z_ const _CHAR* _strService, ADDRESS_FAMILY _afPriority=AF_INET)					{ return Connect(_pszaddrPeer, _strService, _afPriority);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_z_ const _CHAR_SUB* _strService, ADDRESS_FAMILY _afPriority=AF_INET)			{ return Connect(_pszaddrPeer, _strService, _afPriority);}

			bool				Start(_In_ const SOCKADDR_CGNETWORK& _addrPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)									{ return Connect(_addrPeer, _paddrBind); }
			bool				Start(_In_z_ const _CHAR* _pszaddrPeer, _In_ uint16_t _portPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)					{ return Connect(_pszaddrPeer, _portPeer, _paddrBind);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_ uint16_t _portPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)				{ return Connect(_pszaddrPeer, _portPeer, _paddrBind);}
			bool				Start(_In_z_ const _CHAR* _pszaddrPeer, _In_z_ const _CHAR* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)			{ return Connect(_pszaddrPeer, _strService, _paddrBind);}
			bool				Start(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_z_ const _CHAR_SUB* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind)	{ return Connect(_pszaddrPeer, _strService, _paddrBind);}

			eOBJECT_RESULT		Wait(TICK::duration _durationWait=TICK::seconds(30));


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	//! @brief ������ ��û���� �� ȣ��ȴ�. @param _SockAddr ������ �õ��� �ּ�
	virtual void				OnRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* /*_paddrPeer*/) {}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	//! @brief Connect�� �� �θ��� �Լ��̴�.
	virtual	bool				ProcessRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _paddrPeer) override;
	//! @brief Reset�Ҷ� ȣ���ϴ� �Լ�.
	virtual	void				ResetConnector() override;

	//! @brief ���۽� ó���ؾ��� ������ �����Ѵ�. @param _Msg ���۽� ������ ����
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg) override;
	//! @brief ������ ó���ؾ��� ������ �����Ѵ�.
	virtual	void				ProcessStop() override;

	//! @brief �ڽ� ����� ���� ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;
	//! @brief �ڽ� ����� ���� ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ�
	virtual void				_ProcessStopping() override;

	//! @brief ����ó�������� �����Ѵ�.
	virtual	void				ProcessConnect(_In_ uintptr_t _Return);

public:
			eOBJECT_RESULT		m_resultConnecting;
};


}
}
}