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
// CGNet::IO::IAddress
//
// 1. CGNet::IO::IAddress는!
//    1) Socket Address와 Peer Address를 구하는 함수를 가진 Interface Class
//    2) Socket Address : 자기 Socket Address
//       Peer Address : 접속된 상대의 주소
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IAddress : 
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Socket Address(자신의 Address)
	virtual	SOCKADDR_CGNETWORK	GetSocketAddress() const PURE;

	// 2) Peer Address(연결된 상대 Address)
	virtual	SOCKADDR_CGNETWORK	GetPeerAddress() const PURE;
	virtual	bool				SetPeerAddress(const SOCKADDR_CGNETWORK& _addrPeer) PURE;
};


}
}
