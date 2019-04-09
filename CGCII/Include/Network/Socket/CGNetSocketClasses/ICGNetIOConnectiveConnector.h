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
// CGNet::IO::Connective::Connector(���� �߰��)
//
// 1. CGNet::IO::Connective::Connector��~
//    1) Connectable�� �뷮 ������ ó���� �����ִ� ���̴�.
//    2) ��ǥ���� ������ TCP�� Acceptor�� Connetor�� �ִ�.
//
// 2. ���� �Լ�.
//    1) ProcessConnect()
//       - ����ó�� ������ �����ϴ� �Լ�.
//
//    2) ProcessDisconnect()
//       - �������� ������ �����ϴ� �Լ�.
//
// 3. ������!!!
//	  1) Connector�� �Ҹ��ϱ� ���� �ݵ�� Stop�Լ��� ȣ���Ͽ� Stop�� ���¿���
//	     �����ؾ� �Ѵ�!!! �׷��� ������ �޸� Leak�� �߻��� �� �ִ�.
//		  �̸� ���� �� Ŭ������ ConnectableManager�� ���ÿ� ��ӹ��� Ŭ������ 
//		 �Ҹ��ڿ� Stop()�Լ��� �־� �ִ� ���� ���� �����Ѵ�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connective
{

class IConnector :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGInitializable,						// (I) Initializable
	virtual public				ICGStartable,							// (I) Startable
	virtual public				ICGObjectState,							// (I) Object State
	virtual	public				CGNet::IO::IConnective,					// (I) IConnective
	virtual	public				IConnectableManager						// (I) IManagerConnectable
{
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) RequestConnect
			CGPTR<IConnectable>	RequestConnect(_In_opt_ const  SOCKADDR_CGNETWORK* __pSockAddr);
			CGPTR<IConnectable>	RequestConnect(_In_z_ const _CHAR* _pszHostAddress, _In_ uint16_t _nHostPort=0);
			CGPTR<IConnectable>	RequestConnect(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_ uint16_t _nHostPort=0);
			CGPTR<IConnectable>	RequestConnect(_In_z_ const _CHAR* _pszHostAddress, _In_z_ const _CHAR* _iService);
			CGPTR<IConnectable>	RequestConnect(_In_z_ const _CHAR_SUB* _pszHostAddress, _In_z_ const _CHAR_SUB* _iService);

			bool				Connecting(_In_ IConnectable* _pConnectable, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr);
			bool				Connecting(_In_ IConnectable* _pConnectable, _In_z_ const _CHAR* _pszHostAddress, _In_ uint16_t _nHostPort=0);
			bool				Connecting(_In_ IConnectable* _pConnectable, _In_z_ const _CHAR_SUB* _pszHostAddress, _In_ uint16_t _nHostPort=0);
			bool				Connecting(_In_ IConnectable* _pConnectable, _In_z_ const _CHAR* _pszHostAddress, _In_z_ const _CHAR* _iService);
			bool				Connecting(_In_ IConnectable* _pConnectable, _In_z_ const _CHAR_SUB* _pszHostAddress, _In_z_ const _CHAR_SUB* _iService);

	// 2) Alloc Connectable
	virtual	CGPTR<IConnectable>	AllocConnectable(ADDRESS_FAMILY _AddressFamily=AF_INET) PURE;

	// 3) 
	virtual	CGPTR<IConnectable>	ProcessRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;
	virtual	bool				ProcessConnecting(_In_ IConnectable* _pConnectable, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;

};


}
}
}