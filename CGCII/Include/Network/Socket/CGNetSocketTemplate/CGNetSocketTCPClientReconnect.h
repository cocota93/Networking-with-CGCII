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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::Socket::CTCPClient
//
// 1. CGNet::Socket::CTCPClientReconnect��!
//    1) CGNet::Socket::CTCPClient�� �����ϳ� �ڵ� ������ ����� �߰��� ���̴�.
//
// 2. �ٽ� �Լ���.
//    1) �������� �⺻������ Connect()�� ���� �� �ϳ��� �ּҿ��� �̷������.
//    2) �ʿ信 ���� ���� �ּҷ� �������� ������ �� �ִ�.
//       - ������ ����Ǹ� ��ϵ� �ּҵ鿡 ���ʴ�� ���ӿ䱸�� �����ϰ� �ȴ�.
//
//		 - ������ �ּҸ� �߰��ϰ� ������ �� �ִ�.
//			bool AddPeerAddress((LPCSOCKADDR _paddrPeer);
//			bool RemovePeerAddress(LPCSOCKADDR _paddrPeer);
//          void RemoveAllPeerAddress();
//
//    3) ������ Connect�Լ��� ����Ͽ� �����Ѵ�.
//    4) Address�� ���� ���� ��� ��ϵ� Peer�ּҷ� ������ �õ��Ѵ�.
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