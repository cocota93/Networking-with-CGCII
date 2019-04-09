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
// CGNet::IO::NAddress
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

class NAddress : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				IAddress
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NAddress()			{}
	virtual ~NAddress()			{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual	SOCKADDR_CGNETWORK	GetSocketAddress() const override		{	CGASSERT_ERROR(false); return SOCKADDR_CGNETWORK();}
	virtual	SOCKADDR_CGNETWORK	GetPeerAddress() const override			{	return m_addrPeer;}
	virtual	bool				SetPeerAddress(const SOCKADDR_CGNETWORK& _addrSocket) override { m_addrPeer = _addrSocket; return true; }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			SOCKADDR_CGNETWORK	m_addrPeer;
};


}
}
