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
// CGNet::IO::IAddress
//
// 1. CGNet::IO::IAddress��!
//    1) Socket Address�� Peer Address�� ���ϴ� �Լ��� ���� Interface Class
//    2) Socket Address : �ڱ� Socket Address
//       Peer Address : ���ӵ� ����� �ּ�
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
	// 1) Socket Address(�ڽ��� Address)
	virtual	SOCKADDR_CGNETWORK	GetSocketAddress() const PURE;

	// 2) Peer Address(����� ��� Address)
	virtual	SOCKADDR_CGNETWORK	GetPeerAddress() const PURE;
	virtual	bool				SetPeerAddress(const SOCKADDR_CGNETWORK& _addrPeer) PURE;
};


}
}
