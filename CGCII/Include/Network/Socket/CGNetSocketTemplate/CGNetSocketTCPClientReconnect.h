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
// 1. CGNet::Socket::CTCPClientReconnect란!
//    1) CGNet::Socket::CTCPClient와 동일하나 자동 재접속 기능을 추가한 것이다.
//
// 2. 핵심 함수들.
//    1) 재접속은 기본적으로 Connect()를 했을 때 하나의 주소에만 이루어진다.
//    2) 필요에 따라 여러 주소로 재접속을 수행할 수 있다.
//       - 접속이 종료되면 등록된 주소들에 차례대로 접속요구를 수행하게 된다.
//
//		 - 접속할 주소를 추가하고 삭제할 수 있다.
//			bool AddPeerAddress((LPCSOCKADDR _paddrPeer);
//			bool RemovePeerAddress(LPCSOCKADDR _paddrPeer);
//          void RemoveAllPeerAddress();
//
//    3) 접속은 Connect함수를 사용하여 수행한다.
//    4) Address를 넣지 않을 경우 등록된 Peer주소로 접속을 시도한다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{
	
template <class THEAD=CGNet::IO::Packetable::PRIMITIVE<uint32_t>, uint32_t TMESSAGEID=CGMESSAGE::SYSTEM::MESSAGE>
class CTCPClientReconnect :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::IO::Connector::NTCPReconnect,	// (@) Connector with Reconnectable
	public						CGNet::Socket::CTCP<THEAD>				// (@) TCP Socket
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:	
			CTCPClientReconnect()								 		{}
			CTCPClientReconnect(const char* _strName) : CGNet::IO::Connector::NTCPReconnect(_strName) {}
			CTCPClientReconnect(const wchar_t* _strName) : CGNet::IO::Connector::NTCPReconnect(_strName) {}
	virtual	~CTCPClientReconnect()										{}
};


}
}