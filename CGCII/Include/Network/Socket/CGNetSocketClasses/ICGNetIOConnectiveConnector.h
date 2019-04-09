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
// CGNet::IO::Connective::Connector(연결 중계기)
//
// 1. CGNet::IO::Connective::Connector은~
//    1) Connectable의 대량 연결을 처리해 시켜주는 것이다.
//    2) 대표적인 것으로 TCP의 Acceptor와 Connetor가 있다.
//
// 2. 가상 함수.
//    1) ProcessConnect()
//       - 접속처리 과정을 정의하는 함수.
//
//    2) ProcessDisconnect()
//       - 접속해제 과정을 정의하는 함수.
//
// 3. 주의점!!!
//	  1) Connector를 소멸하기 전에 반드시 Stop함수를 호출하여 Stop된 상태에서
//	     종료해야 한다!!! 그렇지 않으면 메모리 Leak이 발생할 수 있다.
//		  이를 위해 이 클래스와 ConnectableManager를 동시에 상속받은 클래스에 
//		 소멸자에 Stop()함수를 넣어 주는 것을 강력 권장한다.
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