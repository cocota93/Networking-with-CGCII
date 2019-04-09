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
// 1. CGNet::Socket::CTCPClient��!
//    1) Client�� Socket���� Connect�� ����� �� �ִ� IConnectable�� ��ӹ��� Ŭ������.
//    2) �⺻���� Socket�� CGNet::Socket::CTCP�� ������ ���� Connector�� ���� ���̴�.
//    3) Connect()�� ConnectTo()�Լ��� ����Ͽ� ������ ������ �� �ִ�.
//
// 2. �ٽ� �Լ���.
//    1) CGNet::IO::Connector::NTCP�� ��ӹ������ν� �Ʒ��� �Լ��� ����� �� �ִ�.
//
//		- SOCKADDR_CGNETWORK�� �����ϴ� �����Լ�...
//			bool Connect(const SOCKADDR_CGNETWORK* _paddrPeer=nullptr);
//			bool Connect(LPCSOCKADDR _paddrPeer, int _nAddrLen);
//
//		- ��Ʈ���� ����� ���ӹ���� ������ ���� �ſ� �پ��ϰ� �������� �ֱ� �����̴�.
//        * MULTIBYTE ������ UNICODE ����
//		  * BindAddress���� ���� ������ �� �ִ� ������ �ƴ� ����
//		  * Address�� ��Ʈ���� �����ϰ� Port�� ���� ������ �� �ִ� ������
//          ��Ʈ���� Address�� Port�� ���ÿ� �����ϴ� ����
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
//          @ �� �Լ��鿡�� _pSockAddr�� Bind�ϴ� �ּ��̴�.
//
//
// 3. �����ǿ� Hook�Լ���.
//
//	// 1) OnRequestConnect �Լ�.
//
//   	virtual void	OnRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _paddrPeer);
//
//		������ ��û���� �� �� Connect()�Լ��� ȣ������ �� ȣ��Ǵ� ���Լ���.
//      �Ϲ������� ���󵵰� ����.
//
//    2) ��Ÿ... ���Լ�.
//       - ��Ÿ ���Լ��� CGNet::Socket::CTCP�� �����ϴ�.
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