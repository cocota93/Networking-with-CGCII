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
// CGNet::IO::Socket::NUDP
//
// 1. CGNet::IO::Socket::NUDP의 특징!
//    1) UDP용으로 제작된 Socket이다.
//    2) UDP용으로 각종 설정이나 옵션이 기본적으로 적용된다.
//    3) UDP의 Send/Receive 버퍼 크기를 아래와 같이 설정하고 얻을 수 있다.
//
//    4) Socket의 Send Buffer와 Receive Buffer를 소켓별로 설정할 수 있지만
//       특별히 설정하지 않으면 기본으로 설정될 값을 아래의 전역함수로 변경할
//       수도 있다.
//       
//       static void	SetDefaultSendBufferSize(int _iSize);
//       static int		GetDefaultSendBufferSize() const;
//
//       static void	SetDefaultReceiveBufferSize(int _iSize);
//       static int		GetDefaultReceiveBufferSize() const;
//
//       소켓이 생성되면 일단 Default값으로 설정되며 소켓별로 변경을 할 경우
//       각기 따로 설정해 주어야 한다.
//
//    5) 일반적으로 소켓의 Send와 Receive 버퍼를 크게 하면 Traffic이 많이 몰릴
//       때 더 좋은 성능을 발휘해준다. 하지만 그만큼 용량을 많이 차지하므로 
//       적절히 설정해야 한다.
//       
//    6) ConnectReset의 통보 여부 설정.
//       - UDP의 경우 ConnectReset이 중요하다. SendTo로 전송했을 때 특정 
//         Address에 전달할수 없는 상황일 때 SendTo의 결과로 통보해주는 것이 
//         아니라 Receive에서 CONNECT_RESET Error를 발생시킨다. 
//       - 이 CONNECT_RESET의 경우 UDP에서는 실질적으로 Error가 아니지만
//         중요한 정보가 될수 있다.
//         따라서 이 CONNECT_RESET 신호를 받을 것인지 받지 않을 것인지를
//         설정할수 있다.
//       - 일반적으로 경우는 Server나 Client로 동작시킬때 이 Option을 
//         꺼주게 되지만 Reliable로 동작시키는 UDP Socket이 있을 경우 이 
//         옵션을 켜준다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Socket
{

class NUDP :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NBase									// (@) IOCP Socket
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NUDP(_In_ bool p_bReportConnectReset=false);
			~NUDP();

// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) UDP 기본 Send/Receive Buffer를 설정한다.
	static	void				SetDefaultSendBufferSize(_In_ size_t _iSize) NOEXCEPT{	m_iDefaultSendBufferSize=_iSize;}
	static	size_t				GetDefaultSendBufferSize() NOEXCEPT			{	return m_iDefaultSendBufferSize;}

	static	void				SetDefaultReceiveBufferSize(_In_ size_t _iSize) NOEXCEPT{	m_bytesDefaultReceiveBufferSize=_iSize;}
	static	size_t				GetDefaultReceiveBufferSize() NOEXCEPT		{	return m_bytesDefaultReceiveBufferSize;}

	// 2) Address
	virtual	SOCKADDR_CGNETWORK	GetPeerAddress() const NOEXCEPT				{	return m_addrPeer;}
	virtual	bool				SetPeerAddress(const SOCKADDR_CGNETWORK& _addrSocket) NOEXCEPT { m_addrPeer = _addrSocket; return true; }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Socket을 Reset하거나 CloseSocket할 때의 과정을 정의한 함수.
	//    (필요할 경우 재정의할수 있다.)
	virtual	void				ProcessCreateSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) override;
	virtual	bool				ProcessCloseSocket(uint32_t _Reason=SOCKET_REASON_NONE) override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Connect Reset을 할 것인가 아닌가를 설정하는 변수임.
			bool				m_bReportConnectReset;	// UDP ConnectReset Report여부

	// 2) UDP Socket에 에 기본 적용되는 Default Send/Receive Buffer 크기
	static	size_t				m_iDefaultSendBufferSize;
	static	size_t				m_bytesDefaultReceiveBufferSize;

	// 3) 
			SOCKADDR_CGNETWORK	m_addrPeer;
};


}
}
}