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
// CGNet::IO::ISocket
//
// 1. CGNet::IO::ISocket
//    1) Socket Interface�� Socket�� Handle�� ������ �ִ�.
//    2) Socket�� ���°�(eSOCKET_STATE)�� ������ �ִ�.
//    3) Socket�� ������ �Ҹ��� ���� �Լ��� ������ �ִ�.
//    4) Socket�� ����� Reset�ϴ� �Լ��� ������ �ִ�.
//
// 2. CGNet::IO::ISocket�� �ֿ� �Լ�
//    1) ProcessResetSocket()	Socket�� ���������� �����ϴ� �Լ��̴�.
//    2) ProcessCloseSocket(uint32_t _Reason)	Socket�� �ı������� �����ϴ� �Լ��̴�.
//    3) ResetSocket()			Socket�� ������ ���� Reset�ϴ� ������ �����ϴ� �Լ��̴�.
//    4) ��Ÿ�Լ���...
//       - Socket�� ���¸� Ȯ���ϴ� �Լ�.
//       - Socket�� Handle�� ���õ� �Լ�.
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
	// 1) Socket�� �غ��ϰ� ���� �� ȣ���ϴ� �Լ�.
	virtual	void				ProcessPrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) PURE;
	virtual	bool				ProcessCloseSocket(uint32_t _Reason=SOCKET_REASON_NONE) PURE;


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Prepare Socket/ Cloase Socket
			void				PrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET)	{	ProcessPrepareSocket(_AddressFamily);}
			bool				CloseSocket(_In_ uint32_t _Reason=SOCKET_REASON_NONE);

	// 2) Socket Handle����...
			CGSOCKET			SetSocketHandle(_In_ CGSOCKET _hSocket);
			CGSOCKET			GetSocketHandle() const NOEXCEPT		{	return m_hSocket;}
			ADDRESS_FAMILY		GetAddressFamily() const NOEXCEPT		{	return m_AddressFamily;}

			bool				IsInvalidSocket() const NOEXCEPT		{	return (GetSocketHandle() == INVALID_SOCKET);}
			bool				IsValidSocket() const NOEXCEPT			{	return (GetSocketHandle() != INVALID_SOCKET);}

	// 3) Socket State����.
			eSOCKET_STATE		GetSocketState() const NOEXCEPT					{	return m_SocketStatus;}
			eSOCKET_STATE		SetSocketState(_In_ eSOCKET_STATE _Status) NOEXCEPT{	return m_SocketStatus.exchange(_Status);}
			bool				SetSocketStateIf(_In_ eSOCKET_STATE _StatusComperand, _In_ eSOCKET_STATE _StatusNew) NOEXCEPT	{	return m_SocketStatus.compare_exchange_weak(_StatusComperand, _StatusNew);}
			bool				ExchangeSocketStateIf(_In_ eSOCKET_STATE& _StatusComperand, _In_ eSOCKET_STATE _StatusNew) NOEXCEPT	{	return m_SocketStatus.compare_exchange_weak(_StatusComperand, _StatusNew);}

			bool				IsDisconnected() const NOEXCEPT			{	return (m_SocketStatus== eSOCKET_STATE::CLOSED);}		// 0 : ������ ����� ����.
			bool				IsBinded() const NOEXCEPT				{	return (m_SocketStatus>= eSOCKET_STATE::BINDED);}		// 1 : Listen���ΰ�?
			bool				IsConnected() const NOEXCEPT			{	return (m_SocketStatus>= eSOCKET_STATE::ESTABLISHED);}	// 2 : ���Ӹ� �� ����.
			bool				IsCertified() const NOEXCEPT			{	return (m_SocketStatus>= eSOCKET_STATE::CERTIFIED);}	// 3 : ������ �ǰ� CGNet�� Client������ ���� ����.
			bool				IsLogined() const NOEXCEPT				{	return (m_SocketStatus>= eSOCKET_STATE::LOGINED);}		// 4 : ID�� Password�� �ְ� Log-In�� �� ����.
			bool				IsListening() const NOEXCEPT			{	return (m_SocketStatus== eSOCKET_STATE::LISTEN);}		// 9 : Listen���ΰ�?

			void				SetSocketReason(_In_ uint32_t _Reason) NOEXCEPT	{	m_dwSocketReason=_Reason;}
			uint32_t			GetSocketReason() const NOEXCEPT		{	return m_dwSocketReason;}

	// 4) Executor
			void				SetExecutor(CGExecutor::CCompletionPort* p_pExecutor) NOEXCEPT	{	m_pExecutor=p_pExecutor;}
			CGPTR<CGExecutor::CCompletionPort>	GetExecutor() const NOEXCEPT		{	return m_pExecutor;}

	// 5) Socket Name�� ��´�.(�ڽ��� Bind�� �ּ�)
			template <class T>
			T*					GetSocketAddress(_Out_writes_bytes_(_iMaxLen) T* _strAddress, _In_ int _iMaxLen) const NOEXCEPT;
	virtual	SOCKADDR_CGNETWORK	GetSocketAddress() const NOEXCEPT;
			bool				GetSocketAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr) const NOEXCEPT	{	_rSockAddr.length=sizeof(SOCKADDR_CGNETWORK); return CGNetAPI::Socket::GetInstance().GetSocketAddress(m_hSocket, reinterpret_cast<LPSOCKADDR>(&_rSockAddr), &_rSockAddr.length);}
			SOCKADDR_CGNETWORK	GetSocketAddressInPublic() const NOEXCEPT{	SOCKADDR_CGNETWORK temp; ZeroMemory(&temp, sizeof(temp)); GetSocketAddressInPublic(temp); return temp;}
			bool				GetSocketAddressInPublic(_Out_ SOCKADDR_CGNETWORK& _prockAddr) const NOEXCEPT;

	// 6) Peer Name�� ��´�.(���ӵ� ����� �ּ�)
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

	// 1) Address�� �о��.
	auto	bResult	 = GetPeerAddress(addrPeer);
	
	// Check) 
	ERROR_RETURN_IF(bResult==false, _strAddress, _strAddress[0]=NULL);

	// 2) Address�� String���� ����.
	CGNetAPI::AddressToString<_CHAR>(_strAddress, _iMaxLen, addrPeer);
	
	// Return) 
	return _strAddress;
}

template <class TCHARACTER>
TCHARACTER* ISocket::GetSocketAddress(_Out_writes_bytes_(_iMaxLen) TCHARACTER* _strAddress, _In_ int _iMaxLen) const NOEXCEPT
{
	// Declare) 
	SOCKADDR_CGNETWORK addrSock;

	// 1) Address�� �о��.
	auto	bResult	 = GetSocketAddress(addrSock);
	
	// Check) 
	ERROR_RETURN_IF(bResult==false, _strAddress, _strAddress[0]=NULL);

	// 2) Address�� String���� ����.
	CGAddressToString(_strAddress, _iMaxLen, addrSock);

	// Return) 
	return _strAddress;
}


}
}