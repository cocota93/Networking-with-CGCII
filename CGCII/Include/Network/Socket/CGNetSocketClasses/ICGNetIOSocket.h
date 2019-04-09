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
// CGNet::IO::ISocket
//
// 1. CGNet::IO::ISocket
//    1) Socket Interface로 Socket의 Handle을 가지고 있다.
//    2) Socket의 상태값(eSOCKET_STATE)을 가지고 있다.
//    3) Socket의 생성과 소멸을 위한 함수를 가지고 있다.
//    4) Socket을 재사용시 Reset하는 함수를 가지고 있다.
//
// 2. CGNet::IO::ISocket의 주요 함수
//    1) ProcessResetSocket()	Socket의 생성과정을 정의하는 함수이다.
//    2) ProcessCloseSocket(uint32_t _Reason)	Socket의 파괴과정을 정의하는 함수이다.
//    3) ResetSocket()			Socket의 재사용을 위해 Reset하는 과정을 정의하는 함수이다.
//    4) 기타함수들...
//       - Socket의 상태를 확인하는 함수.
//       - Socket의 Handle에 관련된 함수.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class ISocket : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				IAddress
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			ISocket() : m_hSocket(INVALID_SOCKET), m_SocketStatus(eSOCKET_STATE::CLOSED), m_ioPendingReceive(0), m_AddressFamily(AF_UNSPEC) {}
	virtual	~ISocket()													{}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
public:
	// 1) Socket을 준비하고 닫을 때 호출하는 함수.
	virtual	void				ProcessPrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) PURE;
	virtual	bool				ProcessCloseSocket(uint32_t _Reason=SOCKET_REASON_NONE) PURE;


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Prepare Socket/ Cloase Socket
			void				PrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET)	{	ProcessPrepareSocket(_AddressFamily);}
			bool				CloseSocket(_In_ uint32_t _Reason=SOCKET_REASON_NONE);

	// 2) Socket Handle관련...
			CGSOCKET			SetSocketHandle(_In_ CGSOCKET _hSocket);
			CGSOCKET			GetSocketHandle() const NOEXCEPT		{	return m_hSocket;}
			ADDRESS_FAMILY		GetAddressFamily() const NOEXCEPT		{	return m_AddressFamily;}

			bool				IsInvalidSocket() const NOEXCEPT		{	return (GetSocketHandle() == INVALID_SOCKET);}
			bool				IsValidSocket() const NOEXCEPT			{	return (GetSocketHandle() != INVALID_SOCKET);}

	// 3) Socket State관련.
			eSOCKET_STATE		GetSocketState() const NOEXCEPT					{	return m_SocketStatus;}
			eSOCKET_STATE		SetSocketState(_In_ eSOCKET_STATE _Status) NOEXCEPT{	return m_SocketStatus.exchange(_Status);}
			bool				SetSocketStateIf(_In_ eSOCKET_STATE _StatusComperand, _In_ eSOCKET_STATE _StatusNew) NOEXCEPT	{	return m_SocketStatus.compare_exchange_weak(_StatusComperand, _StatusNew);}
			bool				ExchangeSocketStateIf(_In_ eSOCKET_STATE& _StatusComperand, _In_ eSOCKET_STATE _StatusNew) NOEXCEPT	{	return m_SocketStatus.compare_exchange_weak(_StatusComperand, _StatusNew);}

			bool				IsDisconnected() const NOEXCEPT			{	return (m_SocketStatus== eSOCKET_STATE::CLOSED);}		// 0 : 접속이 종료된 상태.
			bool				IsBinded() const NOEXCEPT				{	return (m_SocketStatus>= eSOCKET_STATE::BINDED);}		// 1 : Listen중인가?
			bool				IsConnected() const NOEXCEPT			{	return (m_SocketStatus>= eSOCKET_STATE::ESTABLISHED);}	// 2 : 접속만 된 상태.
			bool				IsCertified() const NOEXCEPT			{	return (m_SocketStatus>= eSOCKET_STATE::CERTIFIED);}	// 3 : 접속이 되고 CGNet의 Client검증이 끝난 상태.
			bool				IsLogined() const NOEXCEPT				{	return (m_SocketStatus>= eSOCKET_STATE::LOGINED);}		// 4 : ID와 Password를 넣고 Log-In이 된 상태.
			bool				IsListening() const NOEXCEPT			{	return (m_SocketStatus== eSOCKET_STATE::LISTEN);}		// 9 : Listen중인가?

			void				SetSocketReason(_In_ uint32_t _Reason) NOEXCEPT	{	m_dwSocketReason=_Reason;}
			uint32_t			GetSocketReason() const NOEXCEPT		{	return m_dwSocketReason;}

	// 4) Executor
			void				SetExecutor(CGExecutor::CCompletionPort* p_pExecutor) NOEXCEPT	{	m_pExecutor=p_pExecutor;}
			CGPTR<CGExecutor::CCompletionPort>	GetExecutor() const NOEXCEPT		{	return m_pExecutor;}

	// 5) Socket Name을 얻는다.(자신의 Bind된 주소)
			template <class T>
			T*					GetSocketAddress(_Out_writes_bytes_(_iMaxLen) T* _strAddress, _In_ int _iMaxLen) const NOEXCEPT;
	virtual	SOCKADDR_CGNETWORK	GetSocketAddress() const NOEXCEPT;
			bool				GetSocketAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr) const NOEXCEPT	{	_rSockAddr.length=sizeof(SOCKADDR_CGNETWORK); return CGNetAPI::Socket::GetInstance().GetSocketAddress(m_hSocket, reinterpret_cast<LPSOCKADDR>(&_rSockAddr), &_rSockAddr.length);}
			SOCKADDR_CGNETWORK	GetSocketAddressInPublic() const NOEXCEPT{	SOCKADDR_CGNETWORK temp; ZeroMemory(&temp, sizeof(temp)); GetSocketAddressInPublic(temp); return temp;}
			bool				GetSocketAddressInPublic(_Out_ SOCKADDR_CGNETWORK& _prockAddr) const NOEXCEPT;

	// 6) Peer Name을 얻는다.(접속된 상대의 주소)
			template <class T>
			T*					GetPeerAddress(_Out_writes_bytes_(_iMaxLen) T* _strAddress, _In_ int _iMaxLen) const NOEXCEPT;
	virtual	SOCKADDR_CGNETWORK	GetPeerAddress() const NOEXCEPT;
			bool				GetPeerAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr) const NOEXCEPT	{	_rSockAddr.length=sizeof(SOCKADDR_CGNETWORK); return CGNetAPI::Socket::GetInstance().GetPeerAddress(m_hSocket, reinterpret_cast<LPSOCKADDR>(&_rSockAddr), &_rSockAddr.length);}
	virtual	bool				SetPeerAddress(const SOCKADDR_CGNETWORK& /*_addrPeer*/) override	{ CGASSERT_ERROR(false); return false;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Socket
			ATOMIC<CGSOCKET>	m_hSocket;
			ATOMIC<eSOCKET_STATE> m_SocketStatus;

	// 2) Executor
			CGPTR<CGExecutor::CCompletionPort>	m_pExecutor;
protected:
			uint32_t			m_dwSocketReason;
			ATOMIC<int>			m_ioPendingReceive;
			ADDRESS_FAMILY		m_AddressFamily;
};


template <class TCHARACTER>
TCHARACTER* ISocket::GetPeerAddress(_Out_writes_bytes_(_iMaxLen) TCHARACTER* _strAddress, _In_ int _iMaxLen) const NOEXCEPT
{
	// Declare) 
	SOCKADDR_CGNETWORK addrPeer;

	// 1) Address를 읽어낸다.
	auto	bResult	 = GetPeerAddress(addrPeer);
	
	// Check) 
	ERROR_RETURN_IF(bResult==false, _strAddress, _strAddress[0]=NULL);

	// 2) Address를 String으로 쓴다.
	CGNetAPI::AddressToString<_CHAR>(_strAddress, _iMaxLen, addrPeer);
	
	// Return) 
	return _strAddress;
}

template <class TCHARACTER>
TCHARACTER* ISocket::GetSocketAddress(_Out_writes_bytes_(_iMaxLen) TCHARACTER* _strAddress, _In_ int _iMaxLen) const NOEXCEPT
{
	// Declare) 
	SOCKADDR_CGNETWORK addrSock;

	// 1) Address를 읽어낸다.
	auto	bResult	 = GetSocketAddress(addrSock);
	
	// Check) 
	ERROR_RETURN_IF(bResult==false, _strAddress, _strAddress[0]=NULL);

	// 2) Address를 String으로 쓴다.
	CGAddressToString(_strAddress, _iMaxLen, addrSock);

	// Return) 
	return _strAddress;
}


}
}