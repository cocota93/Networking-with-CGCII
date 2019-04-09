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
// CGNet::IO::IConnector(�����)
//
// 1. IConnector��~
//    1) IConnectable�� ������ �������� �������� Client������ �� �� �ֵ��� ��
//       �ִ� Interface�̴�.
//    2) ���� Connect�Լ��� ����Ͽ� Connect�� ��û�� �� �ִ�.
//
// 2. ���� �Լ�.
//    1) ProcessRequestConnect()
//       - ������ ��û�ϴ� ������ �����ϴ� Process�Լ��̴�.
//
//    2) ResetConnector()
//       - �ʱ�ȭ�� ������ �� ȣ��Ǵ� �Լ��̴�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IConnector : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				ICGNameable,							// (I) Nameable
	virtual public				ICGReferenceable						// (I) Reference Counter.
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) �پ��� �Ķ������ Connect�Լ�.
			bool				Connect();
			bool				Connect(_In_ const SOCKADDR_CGNETWORK& _addrPeer);
			bool				Connect(_In_ const SOCKADDR_IN& _addrPeer);
			bool				Connect(_In_ const SOCKADDR_IN6& _addrPeer);
			bool				Connect(_In_ LPCSOCKADDR _paddrSock, _In_ int _addrLength);

			bool				Connect(_In_z_ const _CHAR* _pszaddrPeer, _In_ uint16_t _portPeer=0, ADDRESS_FAMILY _afPriority=AF_INET)					{	return	Connect(_pszaddrPeer, _portPeer, nullptr, _afPriority);}
			bool				Connect(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_ uint16_t _portPeer=0, ADDRESS_FAMILY _afPriority=AF_INET)				{	return	Connect(_pszaddrPeer, _portPeer, nullptr, _afPriority);}
			bool				Connect(_In_z_ const _CHAR* _pszaddrPeer, _In_z_ const _CHAR* _strService, ADDRESS_FAMILY _afPriority=AF_INET)				{	return	Connect(_pszaddrPeer, _strService, nullptr, _afPriority);}
			bool				Connect(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_z_ const _CHAR_SUB* _strService, ADDRESS_FAMILY _afPriority=AF_INET)		{	return	Connect(_pszaddrPeer, _strService, nullptr, _afPriority);}

			bool				Connect(_In_ const SOCKADDR_CGNETWORK& _addrPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind);
			bool				Connect(_In_z_ const _CHAR* _pszaddrPeer, _In_ uint16_t _portPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind, ADDRESS_FAMILY _afPriority=AF_INET);
			bool				Connect(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_ uint16_t _portPeer, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind, ADDRESS_FAMILY _afPriority=AF_INET);
			bool				Connect(_In_z_ const _CHAR* _pszaddrPeer, _In_z_ const _CHAR* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind, ADDRESS_FAMILY _afPriority=AF_INET);
			bool				Connect(_In_z_ const _CHAR_SUB* _pszaddrPeer, _In_z_ const _CHAR_SUB* _strService, _In_opt_ const SOCKADDR_CGNETWORK* _paddrBind, ADDRESS_FAMILY _afPriority=AF_INET);


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	// 1) Connect �䱸 ������ �����ϴ� �Լ�.
	virtual	bool				ProcessRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _addrPeer) PURE;

	// 2) Reset Connector
	virtual	void				ResetConnector() PURE;
};


}
}