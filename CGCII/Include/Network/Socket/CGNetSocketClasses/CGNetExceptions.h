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
// ICGExceptionThrowable
//
//-----------------------------------------------------------------------------
// Definitions) 
namespace CGException
{

class CNetThrow : 
	public						std::exception,
	public						ICGExceptionThrowable
{
public:
			CNetThrow(uint32_t _Reason=0, const char *const& _strPosition=nullptr) : std::exception(), ICGExceptionThrowable(), m_Reason(_Reason), m_strPosition(_strPosition) {}
			CNetThrow(const char *const& _What, uint32_t _Reason=0, const char *const& _strPosition=nullptr) : std::exception(_What), ICGExceptionThrowable(), m_Reason(_Reason), m_strPosition(_strPosition)	{}
	virtual	~CNetThrow()		{}
public:
			uint32_t			m_Reason;
			char const* 	 	m_strPosition;
};


// 설명) 잘못된 상태일 때
class CNetThrow_InvalidState : 
	virtual public				CNetThrow
{
public:
		CNetThrow_InvalidState(const char *const& _strPosition=nullptr) : CNetThrow("Invalid State", SOCKET_REASON_INVALID_STATE, _strPosition)	{}
};

// 설명) 잘못된 SocketHandle일 때
class CNetThrow_InvalidSocketHandle : 
	virtual public				CNetThrow
{
public:
		CNetThrow_InvalidSocketHandle(const char *const& _strPosition=nullptr) : CNetThrow("Invalid Socket Handle", SOCKET_REASON_INVALID_SOCKET_HANDLE, _strPosition)	{}
};

// 설명) Invalid Message
class CNetThrow_InvalidMessage :
	virtual public				CNetThrow
{
public:
	CNetThrow_InvalidMessage(uint32_t _Reason=0, const char *const&  _strPosition=0) : CNetThrow(_Reason, _strPosition) {}
	CNetThrow_InvalidMessage(const char *const& _What, uint32_t _Reason=0, const char *const& _strPosition=nullptr) : CNetThrow(_What, _Reason, _strPosition) {}
};

// 설명) Invalid Message - Message length is zero
class CNetThrow_InvalidMessage_Length :
	public						CNetThrow_InvalidMessage
{
public:
	CNetThrow_InvalidMessage_Length(uint32_t _Reason=0, const char *const&  _strPosition=0) : CNetThrow_InvalidMessage(_Reason, _strPosition) {}
	CNetThrow_InvalidMessage_Length(const char *const& _What, uint32_t _Reason=0, const char *const& _strPosition=nullptr) : CNetThrow_InvalidMessage(_What, _Reason, _strPosition) {}
};

// 설명) Invalid Message - Message length is zero
class CNetThrow_MessageSize_ZeroSize :
	public						CNetThrow_InvalidMessage_Length
{
public:
	CNetThrow_MessageSize_ZeroSize(uint32_t _Reason=0, const char *const& _strPosition=nullptr) : CNetThrow_InvalidMessage_Length("Message size is zero", _Reason, _strPosition) {}
};

// 설명) Invalid Message - Message length is too long
class CNetThrow_InvalidMessage_TooLongLength :
	public						CNetThrow_InvalidMessage_Length
{
public:
	CNetThrow_InvalidMessage_TooLongLength(const char *const& _strPosition) : CNetThrow_InvalidMessage_Length("Message size is too short", SOCKET_REASON_MESSAGE_LENGTH_TOO_LONG, _strPosition) {}
};

// 설명) Invalid Message - Message length is too short
class CNetThrow_InvalidMessage_TooShortLength :
	public						CNetThrow_InvalidMessage_Length
{
public:
	CNetThrow_InvalidMessage_TooShortLength(const char *const& _strPosition) : CNetThrow_InvalidMessage_Length("Message size is too long", SOCKET_REASON_MESSAGE_LENGTH_TOO_SHORT, _strPosition) {}
};

// 설명) Invalid Message - Unhandled Exception
class CNetThrow_InvalidMessage_UnhandledException :
	public						CNetThrow_InvalidMessage_Length
{
public:
	CNetThrow_InvalidMessage_UnhandledException(const char *const& _strPosition) : CNetThrow_InvalidMessage_Length("Unhandled exception on message process", SOCKET_REASON_MESSAGE_UNHANDLED_EXCEPTION, _strPosition) {}
};

// 설명) Invalid Message - Unhandled Exception
class CNetThrow_InvalidMessage_BufferIsNULL :
	public						CNetThrow_InvalidMessage_Length
{
public:
	CNetThrow_InvalidMessage_BufferIsNULL(const char *const& _strPosition) : CNetThrow_InvalidMessage_Length("Buffer is nullptr", SOCKET_REASON_BUFFER_IS_NULL, _strPosition) {}
};

// 설명) Socket API - Failure
class CNetThrow_SocketAPI_Failure :
	public						CNetThrow
{
public:
	CNetThrow_SocketAPI_Failure(const char *const& _What, uint32_t _Errorcode=0, uint32_t _Reason=0, const char *const& _strPosition=nullptr) : CNetThrow(_What, _Reason, _strPosition), m_ErrorCode(_Errorcode) {}
public:
				uint32_t		m_ErrorCode;
};

// 설명) General Error
class CNetThrow_Failure :
	public						CNetThrow
{
public:
	CNetThrow_Failure(const char *const& _What, uint32_t _Reason=0, const char *const& _strPosition=nullptr) : CNetThrow(_What, _Reason, _strPosition) {}
};


}
