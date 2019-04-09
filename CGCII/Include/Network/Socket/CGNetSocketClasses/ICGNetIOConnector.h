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
// CGNet::IO::IConnector(연결기)
//
// 1. IConnector은~
//    1) IConnectable에 스스로 연결기능을 제공해줘 Client역할을 할 수 있도록 해
//       주는 Interface이다.
//    2) 각종 Connect함수를 사용하여 Connect을 요청할 수 있다.
//
// 2. 가상 함수.
//    1) ProcessRequestConnect()
//       - 접속을 요청하는 과정을 정의하는 Process함수이다.
//
//    2) ResetConnector()
//       - 초기화를 수행할 때 호출되는 함수이다.
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
	// 1) 다양한 파라메터의 Connect함수.
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
	// 1) Connect 요구 과정을 정의하는 함수.
	virtual	bool				ProcessRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _addrPeer) PURE;

	// 2) Reset Connector
	virtual	void				ResetConnector() PURE;
};


}
}