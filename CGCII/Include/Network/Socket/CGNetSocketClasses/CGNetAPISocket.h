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
// CGNetAPI::Socket
//
// 1. CGNetAPI::CAccountSocket은~
//    1) 그냥 단순히 Handle를 베이스로 OS에서 제공하는 Network API들을 
//       Warpping한 함수들이다.
//       특별한 기능이나 뭐 그런거 전혀 엄따아~ -_-;
//    2) Function등이나 기능 구현의 중복을 방지하기 위한 것이다.
//       AcceptEx, ConnectEx, DisconnectEX 등과 같은 확장된 기능등을 지원한다.
//
//-----------------------------------------------------------------------------
// Functions) 
bool operator==(_In_ const SOCKADDR_IN& p_rLeft, _In_ const SOCKADDR_IN& p_rRight);

namespace CGNetAPI
{

_Success_(return!=false) bool	StringToAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr, _In_z_ const char* _strAddress, uint16_t _Port, ADDRESS_FAMILY _Prefer);
_Success_(return!=false) bool	StringToAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr, _In_z_ const wchar_t* _wstrAddress, uint16_t _Port, ADDRESS_FAMILY _Prefer);
_Success_(return!=false) bool	StringToAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr, _In_z_ const char* _strAddress, uint16_t _Port=0, const ADDRINFOA* _Hints=nullptr);
_Success_(return!=false) bool	StringToAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr, _In_z_ const wchar_t* _wstrAddress, uint16_t _Port=0, const ADDRINFOW* _Hints=nullptr);
_Success_(return!=false) bool	StringToAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr, _In_z_ const char* _strAddress, _In_z_ const char* _strService, int _iSocketType=SOCK_STREAM, int _Protocol=IPPROTO_RESERVED_MAX);
_Success_(return!=false) bool	StringToAddress(_Out_ SOCKADDR_CGNETWORK& _rSockAddr, _In_z_ const wchar_t* _wstrAddress, _In_z_ const wchar_t* _wstrService, int _iSocketType=SOCK_STREAM, int _Protocol=IPPROTO_RESERVED_MAX);
SOCKADDR_CGNETWORK				StringToAddress(_In_z_ const char* _strAddress, uint16_t _Port=0, ADDRESS_FAMILY _Prefer=AF_INET);
SOCKADDR_CGNETWORK				StringToAddress(_In_z_ const wchar_t* _wstrAddress, uint16_t _Port=0, ADDRESS_FAMILY _Prefer=AF_INET);
SOCKADDR_CGNETWORK				StringToAddress(_In_z_ const char* _strAddress, _In_z_ const char* _strService, int _iSocketType=SOCK_STREAM, int _Protocol=IPPROTO_RESERVED_MAX);
SOCKADDR_CGNETWORK				StringToAddress(_In_z_ const wchar_t* _wstrAddress, _In_z_ const wchar_t* _wstrService, int _iSocketType=SOCK_STREAM, int _Protocol=IPPROTO_RESERVED_MAX);
template <class T>
bool							AddressToString(_Out_writes_(_MaxLen) T* _strAddress, _In_ size_t _MaxLen, _In_ const SOCKADDR_CGNETWORK& _SockAddr);
template <class T>
std::basic_string<T>			AddressToString(_In_ const SOCKADDR_CGNETWORK& _Address);

class Socket
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
private:
			Socket();
			~Socket();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Get Instance
	static	Socket&				GetInstance()							{	static Socket socket; return socket;}


	
	// 2) Create Socket & CloseSocket
			CGSOCKET			CreateSocket(_In_ ADDRESS_FAMILY _AddressFamily=AF_INET, _In_ int _iSocketType=SOCK_STREAM, _In_ int _iProtocolInfo=IPPROTO_TCP, _In_ uint32_t _Flags=WSA_FLAG_OVERLAPPED);
			_Success_(return!=false)
			bool				CloseSocket(_In_ CGSOCKET _hSocket);
			_Success_(return!=false)
			bool				AbortiveCloseSocket(_In_ CGSOCKET _hSocket);

	// 3) Basic Functions
			_Success_(return!=false)
			bool				GetPeerAddress(_In_ CGSOCKET _hSocket, _Out_writes_bytes_to_(*_pSockAddrLen,*_pSockAddrLen) LPSOCKADDR _pSockAddr, _Inout_ int* _pSockAddrLen)	{	return getpeername(_hSocket,_pSockAddr,_pSockAddrLen) != SOCKET_ERROR;}
			_Success_(return!=false)
			bool				GetSocketAddress(_In_ CGSOCKET _hSocket, _Out_writes_bytes_to_(*_pSockAddrLen,*_pSockAddrLen) LPSOCKADDR _pSockAddr, _Inout_ int* _pSockAddrLen)	{	return getsockname(_hSocket,_pSockAddr,_pSockAddrLen) != SOCKET_ERROR;}
			_Success_(return!=false)
			bool				SetSockOpt(_In_ CGSOCKET _hSocket, _In_ int _Level, _In_ int _iOptionName, _In_reads_bytes_opt_(_iOptionLen)  const void* _pOptionValue, int _iOptionLen)	{ return setsockopt(_hSocket, _Level, _iOptionName, reinterpret_cast<const char*>(_pOptionValue), _iOptionLen) != SOCKET_ERROR; }
			_Success_(return!=false)
			bool				GetSockOpt(_In_ CGSOCKET _hSocket, _In_ int _iOptionName, _Out_writes_bytes_(*_pOptionLen) void* _pOptionValue, _Inout_ int* _pOptionLen, _In_ int _Level = SOL_SOCKET) { return getsockopt(_hSocket, _Level, _iOptionName, reinterpret_cast<char*>(_pOptionValue), _pOptionLen) != SOCKET_ERROR; }
			size_t				GetPendingReadBuffer(_In_ CGSOCKET _hSocket)										{	int dwPending=0; ioctlsocket(_hSocket, FIONREAD, reinterpret_cast<u_long*>(&dwPending)); return dwPending;}

			int					GetMaxMsgSize(_In_ CGSOCKET _hSocket)												{	int iMaxMsgSize=0; int iOptionLen=sizeof(int); if(GetSockOpt(_hSocket, SO_MAX_MSG_SIZE, reinterpret_cast<void*>(&iMaxMsgSize), &iOptionLen)==false) return -1; return iMaxMsgSize;}
			_Success_(return!=false)
			bool				SetLingerOption(_In_ CGSOCKET _hSocket, _In_ uint16_t _Enable, _In_ uint16_t _wTimeOut=0)	{	linger tempLinger={_Enable, _wTimeOut};return SetSockOpt(_hSocket, SOL_SOCKET, SO_LINGER, reinterpret_cast<char*>(&tempLinger), sizeof(linger));}
			_Success_(return!=false)
			bool				SetReuseAddress(_In_ CGSOCKET _hSocket, _In_ int _Enable)							{	return SetSockOpt(_hSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&_Enable), sizeof(_Enable));}

			_Success_(return!=false)
			bool				UpdateAcceptContext(_In_ CGSOCKET _hSocket, _In_ CGSOCKET _hListenSocket)			{	return SetSockOpt(_hSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<char*>(&_hListenSocket), sizeof(_hListenSocket));}
			_Success_(return!=false)
			bool				UpdateConnectContext(_In_ CGSOCKET _hSocket)										{	return SetSockOpt(_hSocket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, nullptr, 0);}

			_Success_(return!=false)
			bool				SetSendBufferSize(_In_ CGSOCKET _hSocket, _In_ size_t _Size)						{	return SetSockOpt(_hSocket, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<char*>(&_Size), sizeof(_Size));}
			_Success_(return!=false)
			bool				SetReceiveBufferSize(_In_ CGSOCKET _hSocket, _In_ size_t _Size)						{	return SetSockOpt(_hSocket, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char*>(&_Size), sizeof(_Size));}
			_Success_(return!=false)
			bool				IOCtl(_In_ CGSOCKET _hSocket, _In_ long _Command, _In_reads_bytes_opt_(_cbInBuffer) void* _lpvInBuffer, _In_ uint32_t _cbInBuffer = sizeof(uint32_t), _Out_writes_bytes_to_opt_(_cbOutBuffer, *_lpcbBytesReturned) void* _lpvOutBuffer = nullptr, _In_ uint32_t _cbOutBuffer = 0, _In_opt_ uint32_t* _lpcbBytesReturned = nullptr);

	// 4) Bind & Connect
			int					Bind(
									_In_		CGSOCKET									_hSocket,
									_In_reads_bytes_(_lenSockAddr) LPCSOCKADDR				_pSocketAddr,
									_In_ int												_lenSockAddr)			{ return bind(_hSocket, _pSocketAddr, _lenSockAddr); }

			_Success_(return!=false)
			bool				Listen(_In_ CGSOCKET										_hSocket) 				{	return listen(_hSocket, SOMAXCONN) != SOCKET_ERROR;}

			_Success_(return!=false)
			bool				Connect(
									_In_		CGSOCKET									_hSocket,
									_In_reads_bytes_(_lenSockAddr) LPCSOCKADDR				_paddrSock,
									_In_		int											_lenSockAddr);

			_Success_(return!=false)
			bool				Shutdown(
									_In_ CGSOCKET											_hSocket,
									_In_ int												_How=SD_SEND)			{	return shutdown(_hSocket, _How) != SOCKET_ERROR;}

	// 5) Extention functions(For overlapped)
			_Success_(return!=false)
			bool				AcceptEx(
									_In_		CGSOCKET									_hSocket,
									_In_		CGSOCKET									_hAcceptSocket,
									_Out_		void*										_pOutputBuffer,
									_Inout_opt_ LPWSAOVERLAPPED								_pOverlapped);

			_Success_(return!=false)
			bool				ConnectEx(
									_In_		CGSOCKET									_hSocket,
									_In_		ICGExecutable*								_pExecutable,
									_In_reads_bytes_(_nAddrLen) LPCSOCKADDR					_paddrPeer,
									_In_		int											_nAddrLen);

			_Success_(return!=false)
			bool				DisconnectEx(
									_In_		CGSOCKET									_hSocket,
									_Inout_opt_ LPWSAOVERLAPPED								_pOverlapped,
									_In_		uint32_t									_Flags = 0);

	// 6) Send & Receive
			_Success_(return!=false)
			bool				Send(
									_In_		CGSOCKET									_hSocket,
									_In_reads_(_countBuffer) const CGD::buffer*				_pBuffer,
									_In_		int											_countBuffer,
									_Out_opt_	uint32_t*									_pbytesSent,
									_Inout_opt_ LPWSAOVERLAPPED								_pOverlapped,
									_In_opt_	LPWSAOVERLAPPED_COMPLETION_ROUTINE			_pCompletionRoutine = nullptr);
			_Success_(return!=false)
			bool				Send(
									_In_		CGSOCKET									_hSocket,
									_In_reads_z_(_Len) const char*							p_pBuf,
									_In_ int												_Len)	{ RETURN_IF(_hSocket == INVALID_SOCKET, false); return	send(_hSocket, p_pBuf, _Len, 0) != SOCKET_ERROR; }
			_Success_(return!=false)
			bool				Receive(
									_In_		CGSOCKET									_hSocket,
									_In_reads_(_countBuffer) CGD::buffer*					_arrayBuffer,
									_In_		int											_countBuffer,
									_Out_opt_	uint32_t*									_pBytesReceived,
									_Inout_		uint32_t*									_lpFlags,
									_Inout_opt_ LPWSAOVERLAPPED								_pOverlapped,
									_In_opt_	LPWSAOVERLAPPED_COMPLETION_ROUTINE			_pCompletionRoutine = nullptr);

			_Success_(return!=false)
			bool				SendTo(
									_In_		CGSOCKET									_hSocket,
									_In_reads_(_countBuffer) const CGD::buffer*				_pBuffer,
									_In_		uint32_t									_countBuffer,
									_Out_opt_	uint32_t*									_pbytesSent,
									_In_reads_bytes_opt_(_Tolen) LPSOCKADDR					_pTo,
									_In_		int											_Tolen,
									_Inout_opt_ LPWSAOVERLAPPED								_pOverlapped,
									_In_opt_	LPWSAOVERLAPPED_COMPLETION_ROUTINE			_pCompletionRoutine = nullptr);
			_Success_(return!=false)
			bool				ReceiveFrom(
									_In_		CGSOCKET									_hSocket,
									_In_reads_(_countBuffer) CGD::buffer*					_arrayBuffer,
									_In_ int												_countBuffer,
									_Out_opt_	uint32_t*									_pBytesReceived,
									_Inout_		uint32_t*									_lpFlags,
									_Out_writes_bytes_to_opt_(*_pFromlen,*_pFromlen) LPSOCKADDR _pFrom,
									_Inout_opt_ int*										_pFromlen,
									_Inout_opt_ LPWSAOVERLAPPED								_pOverlapped,
									_In_opt_	LPWSAOVERLAPPED_COMPLETION_ROUTINE			_pCompletionRoutine = nullptr);
	// 7) RIO Functions
			BOOL				RIOReceive(
									_In_		RIO_RQ										_SocketQueue,
									_In_reads_(_DataBufferCount) PRIO_BUF					_pData,
									_In_		uint32_t									_DataBufferCount,
									_In_		uint32_t									_Flags,
									_In_		void*										_RequestContext);
			int					RIOReceiveEx(
									_In_		RIO_RQ										_SocketQueue,
									_In_reads_(_DataBufferCount) PRIO_BUF					_pData,
									_In_		uint32_t									_DataBufferCount,
									_In_opt_	PRIO_BUF									_pLocalAddress,
									_In_opt_	PRIO_BUF									_pRemoteAddress,
									_In_opt_	PRIO_BUF									_pControlContext,
									_In_opt_	PRIO_BUF									_pFlags,
									_In_		uint32_t									_Flags,
									_In_		void*										_RequestContext);
			BOOL				RIOSend(
									_In_		RIO_RQ										_SocketQueue,
									_In_reads_(_DataBufferCount) PRIO_BUF					_pData,
									_In_		uint32_t									_DataBufferCount,
									_In_		uint32_t									_Flags,
									_In_		void*										_RequestContext);
			BOOL				RIOSendEx(	
									_In_		RIO_RQ										_SocketQueue,
									_In_reads_(_DataBufferCount) PRIO_BUF					_pData,
									_In_		uint32_t									_DataBufferCount,
									_In_opt_	PRIO_BUF									_pLocalAddress,
									_In_opt_	PRIO_BUF									_pRemoteAddress,
									_In_opt_	PRIO_BUF									_pControlContext,
									_In_opt_	PRIO_BUF									_pFlags,
									_In_		uint32_t									_Flags,
									_In_		void*										_RequestContext);

			VOID				RIOCloseCompletionQueue(_In_ RIO_CQ CQ);


			RIO_CQ				RIOCreateCompletionQueue(
									_In_ uint32_t											_QueueSize,
									_In_opt_ PRIO_NOTIFICATION_COMPLETION					 _NotificationCompletion);

			RIO_RQ				RIOCreateRequestQueue(
									_In_		SOCKET										_Socket,
									_In_		uint32_t									_MaxOutstandingReceive,
									_In_		uint32_t									_MaxReceiveDataBuffers,
									_In_		uint32_t									_MaxOutstandingSend,
									_In_		uint32_t									_MaxSendDataBuffers,
									_In_		RIO_CQ										_ReceiveCQ,
									_In_		RIO_CQ										_SendCQ,
									_In_		void*										_SocketContext);

			ULONG				RIODequeueCompletion(
									_In_		RIO_CQ										_CQ,
									_Out_writes_to_(_ArraySize, return) PRIORESULT			_Array,
									_In_		uint32_t									_ArraySize);

			VOID				RIODeregisterBuffer(_In_ RIO_BUFFERID						_BufferId);
			INT					RIONotify(_In_ RIO_CQ	_CQ);

			RIO_BUFFERID		RIORegisterBuffer(
									_In_		PCHAR										_DataBuffer,
									_In_		uint32_t									_DataLength);

			BOOL				RIOResizeCompletionQueue(
									_In_		RIO_CQ										_CQ,
									_In_		uint32_t									_QueueSize);

			BOOL				RIOResizeRequestQueue(
									_In_		RIO_RQ										_RQ,
									_In_		uint32_t									_MaxOutstandingReceive,
									_In_		uint32_t									_MaxOutstandingSend);

public:
			bool				HasAcceptEx() const							{	return WSAcceptEx != nullptr;}
			bool				HasConnectEx() const						{	return WSConnectEx != nullptr;}
			bool				HasDisconnectEx() const						{	return WSDisconnectEx != nullptr;}

	// 7) Local Address 구하기. (GetLocalAddress()의 결과가 -1이 되돌아올 경우 Socket이 초기화 되지 않았다는 의미이다.)
			int					GetLocalAddressCount() const				{	return m_naddressLocal;}
			const SOCKADDR_CGNETWORK&	GetLocalAddress(_In_ int _Index=0) const	{	return m_addrLocal[_Index];}
			_Success_(return!=false)
			bool				GetLocalAddressLocal(_Inout_ SOCKADDR_CGNETWORK& _SockAddr) const;
			_Success_(return!=false)
			bool				GetLocalAddressPublic(_Inout_ SOCKADDR_CGNETWORK& _SockAddr) const;
			_Success_(return!=false)
			bool				GetLocalAddressPublicFirst(_Inout_ SOCKADDR_CGNETWORK& _SockAddr) const;



// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Socket의 수
			ATOMIC<int>			m_nSocket;						// Socket의 수임.

			volatile long		m_naddressLocal;				// Local Address의 갯수.
			SOCKADDR_CGNETWORK	m_addrLocal[64];

private:
	// 1) Bind & Connect
			int					(PASCAL FAR* WSAcceptEx)(IN CGSOCKET sListenSocket, IN CGSOCKET sAcceptSocket, IN PVOID lpOutputBuffer, IN uint32_t dwReceivedDataLength, IN uint32_t dwLocalAddressLength, IN uint32_t dwRemoteAddressLength, OUT uint32_t* lpdwBytesReceived, IN LPOVERLAPPED lpOverlapped);
			int					(PASCAL FAR* WSConnectEx)(IN CGSOCKET s, IN const struct sockaddr FAR *name, IN int namelen, IN void* lpSendBuffer OPTIONAL, IN uint32_t dwSendedDataLength, OUT uint32_t* lpdwBytesSent, IN LPOVERLAPPED lpOverlapped);
			int					(PASCAL FAR* WSDisconnectEx)(IN CGSOCKET s, IN LPOVERLAPPED lpOverlapped, IN uint32_t  dwFlags, IN uint32_t  dwReserved);

	// 2) RIO Functions
			RIO_EXTENSION_FUNCTION_TABLE	m_RIOFunctions;

			
	// 3) Extention Function을 얻는 함수.
			void				GetExtensionFunction();

	// 4) Socket초기화 함수.
			bool				InitSocket();
			void				CleanupSocket();
};

template<>
inline bool AddressToString<char>(_Out_writes_(_MaxLen) char* _strAddress, _In_ size_t _MaxLen, _In_ const SOCKADDR_CGNETWORK& _Address)
{
	return InetNtopA(_Address.sin_family, const_cast<void*>(_Address.get_paddr()), _strAddress, _MaxLen) !=nullptr;
}

template<>
inline bool AddressToString<wchar_t>(_Out_writes_(_MaxLen) wchar_t* _strAddress, _In_ size_t _MaxLen, _In_ const SOCKADDR_CGNETWORK& _Address)
{
	return InetNtopW(_Address.sin_family, const_cast<void*>(_Address.get_paddr()), _strAddress, _MaxLen) !=nullptr;
}

template <class T>
std::basic_string<T> AddressToString(_In_ const SOCKADDR_CGNETWORK& _Address)
{
	// Declare) 
	T	temp[256]{0};

	// 1) Address to String
	auto result	 = AddressToString(temp, 256, _Address);

	// Return) 
	return	(result) ? std::basic_string<T>(temp) : std::basic_string<T>();
}


}
