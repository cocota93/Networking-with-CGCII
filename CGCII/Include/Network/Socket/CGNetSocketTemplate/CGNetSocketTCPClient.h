//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                      Network Socket Template Classes                      *
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
// CGNet::Socket::CTCPClient
//
// 1. CGNet::Socket::CTCPClient란!
//    1) Client용 Socket으로 Connect를 사용할 수 있는 IConnectable을 상속받은 클래스다.
//    2) 기본적인 Socket인 CGNet::Socket::CTCP에 접속을 위한 Connector를 붙인 것이다.
//    3) Connect()나 ConnectTo()함수를 사용하여 접속을 수행할 수 있다.
//
// 2. 핵심 함수들.
//    1) CGNet::IO::Connector::NTCP를 상속받음으로써 아래의 함수를 사용할 수 있다.
//
//		- SOCKADDR_CGNETWORK를 전달하는 접속함수...
//			bool Connect(const SOCKADDR_CGNETWORK* _paddrPeer=nullptr);
//			bool Connect(LPCSOCKADDR _paddrPeer, int _nAddrLen);
//
//		- 스트링을 사용한 접속방법은 다음과 같이 매우 다양하게 나뉘어져 있기 때문이다.
//        * MULTIBYTE 버전과 UNICODE 버전
//		  * BindAddress까지 직접 지정할 수 있는 버전과 아닌 버전
//		  * Address로 스트링을 설정하고 Port는 따로 설정할 수 있는 버전과
//          스트링에 Address와 Port를 동시에 설정하는 버전
//        
//			bool Connect(_In_z_ const char* _pszHostAddress, uint16_t _nHostPort);
//			bool Connect(_In_z_ const char* _pszHostAddress);
//			bool Connect(_In_z_ const char* _pszHostAddress, uint16_t _nHostPort, LPCSOCKADDR _pSockAddr, int _nSockAddrLen);
//			bool Connect(_In_z_ const char* _pszHostAddress, LPCSOCKADDR _pSockAddr, int _nSockAddrLen);
//			bool Connect(_In_z_ const wchar_t* _pszHostAddress, uint16_t _nHostPort);
//			bool Connect(_In_z_ const wchar_t* _pszHostAddress);
//			bool Connect(_In_z_ const wchar_t* _pszHostAddress, uint16_t _nHostPort, LPCSOCKADDR _pSockAddr, int _nSockAddrLen);
//			bool Connect(_In_z_ const wchar_t* _pszHostAddress, LPCSOCKADDR _pSockAddr, int _nSockAddrLen);
//
//          @ 위 함수들에서 _pSockAddr는 Bind하는 주소이다.
//
//
// 3. 재정의용 Hook함수들.
//
//	// 1) OnRequestConnect 함수.
//
//   	virtual void	OnRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _paddrPeer);
//
//		접속을 요청했을 때 즉 Connect()함수를 호출했을 때 호출되는 훅함수다.
//      일반적으로 사용빈도가 낮다.
//
//    2) 기타... 훅함수.
//       - 기타 훅함수는 CGNet::Socket::CTCP와 동일하다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class THEAD=CGNet::IO::Packetable::PRIMITIVE<uint32_t>>
class CTCPClient :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Connector::NTCP,				// (@) Connector
	public						CGNet::Socket::CTCP<THEAD>				// (@) TCP Socket
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCPClient()												 {}
			CTCPClient(const char* _strName) : CGNet::IO::Connector::NTCP(_strName){}
			CTCPClient(const wchar_t* _strName) : CGNet::IO::Connector::NTCP(_strName) {}
	virtual	~CTCPClient()												{}
};


}
}