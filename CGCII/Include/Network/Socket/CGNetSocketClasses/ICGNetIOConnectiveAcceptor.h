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
// CGNet::IO::Connective::IAcceptor
//
// 1. CGNet::IO::Connective::IAcceptor��~
//     Acceptor�� ���� Base class.
//
// 2. Process�Լ�.
//    1) ProcessCompleteAccept()
//       - Accept�� ��� ���� �� Accept�� ó���ϴ� ������ �����ϴ� �Լ��̴�.
//       - �Ϲ������� Accept�� �Ϸ�Ǹ� ProcessExecute�� ��������� �� �Լ��� 
//         ȣ���Ѵ�.
//       - �� ���������� ���ӵ� Socket�� ���Ӱ� ���õ� ����ó���� ���ָ�
//       - �ش� Socket�� ProcessCompletConnect()�Լ��� ȣ�����ش�.
//       - �������� �ϳ��� Socket�� ���� �ȸ�ŭ ���ο� Socket�� �����Ͽ� ����
//         Accept�� �ɾ��ش�.
//
//	  2) Start()/Stop()
//		 - Start()�Լ��� ȣ���ϸ� Accept���� �غ� �Ѵ�.
//       - Stop()�Լ��� ȣ���ϸ� ���̻� Accept�� ���� �ʴ´�.
//
//    3) Accept
//       - Accept�� �Ŵ� �Լ��� ���ο� Socket�� �Ҵ�޾� AcceptEX�� �ɾ��ִ� ������ �Ѵ�.
//
//    4) ResetAcceptor
//       - Acceptor�� �ʱ�ȭ�� �� ȣ��Ǵ� �Լ��̴�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connective
{

class IAcceptor : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISocket,						// (I) Socket
	virtual public				ICGStartable,							// (I) Startable
	virtual public				ICGObjectState,							// (I) Object Status
	virtual	public				CGNet::IO::IConnective,					// (I) IConnective
	virtual	public				IConnectableManager						// (I) IManagerConnectable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Open(=Listen)
			bool				Start(_In_ const SOCKADDR_CGNETWORK& _addrListen, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);
			bool				Start(_In_ u_short _Port, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);
			bool				Start(_In_z_ const char* _pServiceName, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);
			bool				Start(_In_z_ const wchar_t* _pServiceName, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);

	// 3) Accept
	virtual	bool				RequestAccept() PURE;
	virtual	void				ResetAcceptor() PURE;

	// 3) Enable/Disable
	virtual bool				Enable() PURE;
	virtual bool				Disable() PURE;


// ****************************************************************************
// Protected)
// ----------------------------------------------------------------------------
protected:
			void				PrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET)		{ CGNet::IO::ISocket::PrepareSocket(_AddressFamily); }
			bool				CloseSocket(_In_ uint32_t _Reason = SOCKET_REASON_NONE) { return CGNet::IO::ISocket::CloseSocket(_Reason);}

			eSOCKET_STATE		SetSocketState(_In_ eSOCKET_STATE _Status) { return CGNet::IO::ISocket::SetSocketState(_Status); }
			bool				SetSocketStateIf(_In_ eSOCKET_STATE _StatusComperand, _In_ eSOCKET_STATE _StatusNew) { return CGNet::IO::ISocket::SetSocketStateIf(_StatusComperand, _StatusNew); }
			bool				ExchangeSocketStateIf(_In_ eSOCKET_STATE& _StatusComperand, _In_ eSOCKET_STATE _StatusNew) { return CGNet::IO::ISocket::ExchangeSocketStateIf(_StatusComperand, _StatusNew); }

			void				SetSocketReason(_In_ uint32_t _Reason)	{ CGNet::IO::ISocket::SetSocketReason(_Reason); }
};


}
}
}