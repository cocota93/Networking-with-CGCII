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


// ----------------------------------------------------------------------------
//  Definitions
// ----------------------------------------------------------------------------
// 1) Return If
#define	RETURN_IF_INVALID_SOCKET(value)					if(GetSocketHandle() == INVALID_SOCKET)		{ return value;}
#define	RETURN_IF_DISCONNECTED(value)					if(GetSocketState() == eSOCKET_STATE::CLOSED) { return value;}
#define	ERROR_RETURN_IF_INVALID_SOCKET(value, state)	if(GetSocketHandle() == INVALID_SOCKET)		{ state; return value;}
#define	ERROR_RETURN_IF_DISCONNECTED(value, state)		if(GetSocketState() <= eSOCKET_STATE::SYN)	{ state; return value;}

// 2) CGNetClass에서 쓰는 Socket Type
typedef	SOCKET					CGSOCKET, *LPCGSOCKET, &RPCGSOCKET;
typedef const SOCKADDR_IN*		LPCSOCKADDR_IN;
typedef const SOCKADDR*			LPCSOCKADDR;
typedef	const WSABUF*			LPCWSABUF;
template<class> class ICGServerGroup;

// 3) Exceptions
//    주의)
//      CGCATCH_ALL의 경우 모든 예외를 다 잡아버린다.
//      따라서 Access Violation과 같은 치명적인 Bug가 발생해도 그냥 지나쳐 버리게 된다.
//      이는 오히려 Debugging을 하는데 방해가 되므로 Debug모드일 때는 catch(...)은
//      사용하지 않는 것이 좋다.
//      CGException::NoCatch는 어떤 경우에도 Throw하지 않기로 약속한 것이므로
//      CGException::NoCatch를 잡는다는 것은 잡지 않는 다는 뜻이다.
#define	CGNET_RETHROW			throw
#define	CGNET_TRY				try
#define	CGNET_CATCH(x)			catch(x)
#define	CGNET_THROW(x, e)		e; throw(x)
#define	CGNET_THROW_IF(c, x, e)	if(c)	{ CGNET_THROW(x, e);}
#define	CGNET_CATCH_ALL			CGNET_CATCH(...)
#define	CGNET_HANDLE_UNTYPED_EXCEPTION	CGNET_TRY{CGRETHROW;} CGNET_CATCH(const std::exception& e){ CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));}	CGNET_CATCH_ALL{}

inline IN_ADDR _IN_ADDR_v4(BYTE a, BYTE b, BYTE c, BYTE d)
{
	IN_ADDR	addrTemp;

	addrTemp.S_un.S_un_b.s_b1	 = a;
	addrTemp.S_un.S_un_b.s_b2	 = b;
	addrTemp.S_un.S_un_b.s_b3	 = c;
	addrTemp.S_un.S_un_b.s_b4	 = d;

	return	addrTemp;
}

class SOCKADDR_CGNETWORK
{
public:
			SOCKADDR_CGNETWORK() NOEXCEPT;
			SOCKADDR_CGNETWORK(uint16_t _Port, ADDRESS_FAMILY _AddressFamily=AF_INET) NOEXCEPT;
			SOCKADDR_CGNETWORK(const char* _strAddress, uint16_t _Port=0) NOEXCEPT;
			SOCKADDR_CGNETWORK(const wchar_t* _strAddress, uint16_t _Port=0) NOEXCEPT;
			SOCKADDR_CGNETWORK(const SOCKADDR_IN& _addr_v4) NOEXCEPT;
			SOCKADDR_CGNETWORK(const SOCKADDR_IN6& _addr_v6) NOEXCEPT;
			SOCKADDR_CGNETWORK(const SOCKADDR_CGNETWORK& _copy) NOEXCEPT;
			SOCKADDR_CGNETWORK(const SOCKADDR* _paddrSock, int _AddrLength);

public:
			bool				empty() const NOEXCEPT				{	return length==0;}
			bool				exist() const NOEXCEPT				{	return length!=0;}
			bool				is_unspecified() const NOEXCEPT;
			bool				is_bind_any() const NOEXCEPT;
			bool				is_loopback() const NOEXCEPT;
			bool				is_localhost() const NOEXCEPT		{	return is_loopback();}

			bool				is_private_address() const NOEXCEPT;
			bool				is_public_address() const NOEXCEPT;

			void				set_address(const char* _strAddress, uint16_t _Port=0, ADDRESS_FAMILY _Prefer=AF_INET);
			void				set_address(const wchar_t* _strAddress, uint16_t _Port=0, ADDRESS_FAMILY _Prefer=AF_INET);
			void				set_address_any(uint16_t _Port=0, ADDRESS_FAMILY _af=AF_INET);
			void				set_address_loopback(uint16_t _Port=0, ADDRESS_FAMILY _af=AF_INET);
			const void*			get_paddr() const					{	switch(sin_family){case AF_INET: return &v4.sin_addr; case AF_INET6: return &v6.sin6_addr; default: return &v4;} }

			template<class T>
			std::basic_string<T>	ToString() const
			{
				return	CGNetAPI::AddressToString<T>(*this);
			}

			template<class T>
			int					ToString(T* _Output, size_t _Length) const
			{
				return	CGNetAPI::AddressToString<T>(_Output, _Length, *this);
			}


public:
			SOCKADDR_CGNETWORK&	operator=(const SOCKADDR_IN& _rhs) NOEXCEPT			{ *reinterpret_cast<SOCKADDR_IN*>(this)=_rhs; length=sizeof(SOCKADDR_IN); return *this; }
			SOCKADDR_CGNETWORK&	operator=(const SOCKADDR_IN6& _rhs) NOEXCEPT		{ *reinterpret_cast<SOCKADDR_IN6*>(this)=_rhs; length=sizeof(SOCKADDR_IN6); return *this; }
			SOCKADDR_CGNETWORK& operator=(const SOCKADDR_CGNETWORK& _rhs) NOEXCEPT	{ sin_family=_rhs.sin_family; sin_port=_rhs.sin_port; v6=_rhs.v6; length=_rhs.length; return *this;}

							operator	const SOCKADDR_IN&() const NOEXCEPT			{	return *reinterpret_cast<const SOCKADDR_IN*>(this);}
							operator	const SOCKADDR_IN6&() const NOEXCEPT		{	return *reinterpret_cast<const SOCKADDR_IN6*>(this);}
public:
			union
			{
				ADDRESS_FAMILY	sin_family;			// AF_INET
				ADDRESS_FAMILY	sin6_family;		// AF_INET6
			};

			union
			{
				USHORT			sin_port;
				USHORT			sin6_port;			// Transport level port number.
			};

			union
			{
				struct
				{
					IN_ADDR		sin_addr;
					CHAR		sin_zero[8];
				} v4;

				struct
				{
					ULONG		sin6_flowinfo;		// IPv6 flow information.
					IN6_ADDR	sin6_addr;			// IPv6 address.
					union
					{
						ULONG	sin6_scope_id;     // Set of interfaces for a scope.
						SCOPE_ID sin6_scope_struct;
					};
				} v6;
			};

			int					length;
};

typedef SOCKADDR_CGNETWORK			*LPSOCKADDR_CGNETWORK, *PSOCKADDR_CGNETWORK;
typedef const SOCKADDR_CGNETWORK	*LPCSOCKADDR_CGNETWORK, *PCSOCKADDR_CGNETWORK;

inline SOCKADDR_IN _SOCKADDR_IN(BYTE a, BYTE b, BYTE c, BYTE d, uint16_t port)
{
	SOCKADDR_IN	addrTemp;

	addrTemp.sin_family	 = AF_INET;
	addrTemp.sin_addr	 = _IN_ADDR_v4(a, b, c, d);
	addrTemp.sin_port	 = htons(port);

	return	addrTemp;
}

inline SOCKADDR_IN _SOCKADDR_IN(const IN_ADDR& p_rInAddr, uint16_t port)
{
	SOCKADDR_IN	addrTemp;

	addrTemp.sin_family	 = AF_INET;
	addrTemp.sin_addr	 = p_rInAddr;
	addrTemp.sin_port	 = htons(port);

	return	addrTemp;
}

struct SOCKADDR_SECURITY : public SOCKADDR_CGNETWORK
{
public:
	_SOCKET_SECURITY_SETTINGS	securitySettings;
	const wchar_t*				serverSPN;
public:
	SOCKADDR_SECURITY() : serverSPN(nullptr)	{ securitySettings.SecurityProtocol=SOCKET_SECURITY_PROTOCOL_DEFAULT;securitySettings.SecurityFlags=SOCKET_SETTINGS_GUARANTEE_ENCRYPTION;}
	SOCKADDR_SECURITY(wchar_t* _serverSPN, const _SOCKET_SECURITY_SETTINGS& _SecuritySetting) : securitySettings(_SecuritySetting), serverSPN(_serverSPN) 	{}
};

// ----------------------------------------------------------------------------
// Basic
// ----------------------------------------------------------------------------
// 1) CG Network Socket의 상태를 나타탬
enum class eSOCKET_STATE : int32_t
{
	CLOSED				 = 0,	//  0 : 접속이 종료된 상태
	BINDED				 = 1,	//  1 : Binded
	SYN					 = 2,	//  2 : 접속진행 중인 상태
	SEND_DISCONNECTED	 = 3,	//  3 : (Active) 접속종료 진행상태
	FIN_WAIT_1			 = 4,	//  4 : (Active) 접속종료 진행상태
	FIN_WAIT_2			 = 5,	//  5 : (Active) 접속종료 진행상태
	TIME_WAIT			 = 6,	//  6 : (Active) 접속종료 진행상태
	CLOSE_WAIT			 = 7,	//  7 : (Passive) 접속종료 진행상태
	LAST_ACK			 = 8,	//  8 : (Passive) 접속종료 진행상태
	ESTABLISHED			 = 9,	//  9 : 접속만 된 상태
	LISTEN				 = 10,	// 10 : Listen상태
	CERTIFIED			 = 11,	// 11 : 접속이 되고 CGNet의 Client검증이 끝난 상태.
	LOGINED				 = 12,	// 12 : ID와 Password를 넣고 Log-In이 된 상태.
	MAX
};

// 2) Acceptor
#define	NO_START_ACCEPT						(-1)

const uint32_t	SOCKET_REASON_NONE						 = 0x00000000;	// 일상적인 처리 과정일 경우
const uint32_t	SOCKET_REASON_FAIL						 = 0x00010000;	// 오류로 인한 접속 종료인 경우(송수신 중 오류, 상대방에 의한 강제접속 종료)
const uint32_t	SOCKET_REASON_ACTIVE					 = 0x00020000;	// 접속 종료를 요청한 측일 경우(설정되어 있지 않으면 Passive)
const uint32_t	SOCKET_REASON_ABORTIVE					 = 0x00040000;	// 강제 접속종료일 경우(설정되어 있지 않으면 Graceful)
const uint32_t	SOCKET_REASON_EXCEPTION					 = 0x00080000;	// 예외로 인해 것일 경우
const uint32_t	SOCKET_REASON_MASK						 = 0xffff0000;	// Mask
const uint32_t	SOCKET_REASON_MASK_USER					 = 0x0000ffff;	// User 정의

const uint32_t	SOCKET_REASON_OVERFLOW_MAX_MESSAGES		 = 0x00000001;	// Send시 Message 수의 Overflow로 접속을 종료했다.
const uint32_t	SOCKET_REASON_OVERFLOW_MAX_BYTES		 = 0x00000002;	// Send시 Bytes 수의 Overflow로 접속을 종료했다.
const uint32_t	SOCKET_REASON_MESSAGE_LENGTH_TOO_LONG	 = 0x00000003;	// Message의 길이가 너무 길다
const uint32_t	SOCKET_REASON_MESSAGE_LENGTH_TOO_SHORT	 = 0x00000004;	// Message의 길이가 너무 짧다
const uint32_t	SOCKET_REASON_MESSAGE_UNHANDLED_EXCEPTION= 0x00000005;	// Message처리 중 핸들링 되지 않은 Exception
const uint32_t	SOCKET_REASON_BUFFER_IS_NULL			 = 0x00000006;	// CCGBuffer의 buf값이 nullptr이다.
const uint32_t	SOCKET_REASON_INVALID_STATE				 = 0x00000007;	// 처리 과정상 있을 수 없는 상태이다.
const uint32_t	SOCKET_REASON_INVALID_SOCKET_HANDLE		 = 0x00000008;	// Socket handle이 INVALID_SOCKET_HANDLE이다.
const uint32_t	SOCKET_REASON_FAIL_TO_SOCKET_PREPARE	 = 0x00000009;	// Socket의 Prepare단계에서 실패했다.
const uint32_t	SOCKET_REASON_FAIL_TO_SOCKET_ACCEPT		 = 0x0000000a;	// Socket의 Accept 과정에서실패했다.
const uint32_t	SOCKET_REASON_FAIL_TO_SOCKET_CONNECT	 = 0x0000000b;	// Socket의 Connect 단계에서 실패했다.
const uint32_t	SOCKET_REASON_KEEP_ALIVE_TIME_OUT		 = 0x0000000c;	// Socket의 Prepare단계에서 실패했다.


const uint32_t	SOCKET_REASON_SUCCESS					 = 0;
const uint32_t	SOCKET_REASON_GRACEFUL					 = 0;
const uint32_t	SOCKET_REASON_FAIL_TIMEOUT				 = (SOCKET_REASON_FAIL | SOCKET_REASON_ACTIVE);
const uint32_t	SOCKET_REASON_FAIL_ABORTIVE				 = (SOCKET_REASON_FAIL | SOCKET_REASON_ABORTIVE | SOCKET_REASON_ACTIVE);
const uint32_t	SOCKET_REASON_FAIL_EXCEPTION			 = (SOCKET_REASON_FAIL | SOCKET_REASON_EXCEPTION);


// ----------------------------------------------------------------------------
// Structures
// ----------------------------------------------------------------------------
struct SEND
{
	SEND(CGNet::IO::ISender* p_pSender)	{	m_pSender=p_pSender;}
	SEND(CGNet::IO::ISender& p_pSender)	{	m_pSender=&p_pSender;}

	CGNet::IO::ISender*			m_pSender;
};

struct SEND_TO
{
	SEND_TO(CGNet::IO::ISenderDatagram* _pSender, const SOCKADDR_CGNETWORK* _pSockAddress) :m_pSenderDatagram(_pSender), m_pSockAddr(_pSockAddress)		{}
	SEND_TO(CGNet::IO::ISenderDatagram& _pSender, const SOCKADDR_CGNETWORK* _pSockAddress) :m_pSenderDatagram(&_pSender), m_pSockAddr(_pSockAddress)	{}

	CGNet::IO::ISenderDatagram*	m_pSenderDatagram;
	const SOCKADDR_CGNETWORK*	m_pSockAddr;
};


// ----------------------------------------------------------------------------
// ...
// ----------------------------------------------------------------------------
#define	MINIMUM_REMAINED_RECEIVE_BUFFER		64



// ----------------------------------------------------------------------------
// Object Type
// ----------------------------------------------------------------------------
// 1) Network
#define		CGOBJECTTYPE_NETWORK							 0x200000
#define		CGOBJECTTYPE_NETWORK_ACCEPTOR					 (CGOBJECTTYPE_NETWORK | 0x0100)
#define		CGOBJECTTYPE_NETWORK_CONNECTOR					 (CGOBJECTTYPE_NETWORK | 0x0300)
#define		CGOBJECTTYPE_NETWORK_SOCKET						 (CGOBJECTTYPE_NETWORK | 0x0200)
