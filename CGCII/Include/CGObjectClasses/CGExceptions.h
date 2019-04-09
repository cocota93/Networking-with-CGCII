//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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
// 1. ICGExceptionThrowable and bases
//
//-----------------------------------------------------------------------------
class ICGExceptionHandleable
{
public:
	//! @brief 예외가 발생했을 때 호출될 함수 @param _rException 예외 객체 @param _strException 예외 문자열 @return true 처리 @return false 비처리
	virtual	bool				OnException(_In_ const std::exception& _rException, _In_z_ const _CHAR* _strException) PURE;
};

class ICGExceptionThrowable
{
public:
			ICGExceptionThrowable()						{}
	virtual	~ICGExceptionThrowable()					{}

public:
	virtual	const _CHAR*		What() const			{ return _CGTEXT(""); }
	virtual	const _CHAR*		Description() const		{ return _CGTEXT("");}
};

class ICGExceptionThrowableDescriptable : 
	virtual public				ICGExceptionThrowable
{
public:
			ICGExceptionThrowableDescriptable() {}
			ICGExceptionThrowableDescriptable(_In_z_ const _CHAR* _strMessage) : m_strMessage(_strMessage) {}
			ICGExceptionThrowableDescriptable(_In_ const _STRING& _strMessage) : m_strMessage(_strMessage) {}
	virtual	~ICGExceptionThrowableDescriptable() {}

public:
	virtual	const _CHAR*		Description() const override { return m_strMessage.c_str(); }

public:
			_STRING				m_strMessage;
};


//-----------------------------------------------------------------------------
//
// 2. Exception Bases
//
//-----------------------------------------------------------------------------
// Definitions) 
namespace CGException
{

class CThrow_Failure :
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_Failure() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_Failure(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage), m_reason(eOBJECT_RESULT::UNDEFINED), m_param(0) {}
			CThrow_Failure(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage), m_reason(eOBJECT_RESULT::UNDEFINED), m_param(0) {}
			CThrow_Failure(_In_ eOBJECT_RESULT _Reason, uint64_t _Param=0, _In_z_ const _CHAR* _strMessage=nullptr) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage), m_reason(_Reason), m_param(_Param) {}
			CThrow_Failure(_In_ eOBJECT_RESULT _Reason, uint64_t _Param, _In_ const _STRING& _strMessage=0) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage), m_reason(_Reason), m_param(_Param) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Failure"); }

public:
			eOBJECT_RESULT		m_reason;
			uint64_t			m_param;
};

class CThrow_Error :
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_Error() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_Error(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage), m_reason(eOBJECT_RESULT::UNDEFINED), m_param(0) {}
			CThrow_Error(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage), m_reason(eOBJECT_RESULT::UNDEFINED), m_param(0) {}
			CThrow_Error(_In_ eOBJECT_RESULT _Reason, uint64_t _Param=0, _In_z_ const _CHAR* _strMessage=nullptr) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage), m_reason(_Reason), m_param(_Param) {}
			CThrow_Error(_In_ eOBJECT_RESULT _Reason, uint64_t _Param, _In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage), m_reason(_Reason), m_param(_Param) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Error"); }

public:
			eOBJECT_RESULT		m_reason;
			uint64_t			m_param;
};



//-----------------------------------------------------------------------------
//
// 3. Standard Exceptions
//
//  1) CThrow_LogicError : exception
//     - CThrow_LengthError : logic_error
//     - CThrow_DomainError : logic_error
//     - CThrow_InvalidArgument : logic_error
//     - CThrow_OutOfRange : logic_error
//
//  2) CThrow_RuntimeError : exception
//     - CThrow_OverflowError : runtime_error
//     - CThrow_UnderflowError : runtime_error
//     - CThrow_RangeError : runtime_error
//
//  3) CThrow_BadAlloc : exception
//  4) CThrow_BadException : exception
//
//
//-----------------------------------------------------------------------------
class IThrow_LogicError :
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			IThrow_LogicError() : ICGExceptionThrowableDescriptable() {}
			IThrow_LogicError(_In_z_ const _CHAR* _strMessage) : ICGExceptionThrowableDescriptable(_strMessage) {}
			IThrow_LogicError(_In_ const _STRING& _strMessage) : ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Logic Error"); }
};

class CThrow_LogicError :
	public						std::logic_error,
	virtual public				IThrow_LogicError
{
public:
			CThrow_LogicError() : std::logic_error(""), IThrow_LogicError() {}
			CThrow_LogicError(_In_z_ const _CHAR* _strMessage) : std::logic_error(""), IThrow_LogicError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Logic Error"); }
};

class CThrow_LengthError : 
	public						std::length_error,
	virtual public				IThrow_LogicError
{
public:
			CThrow_LengthError() : std::length_error(""), IThrow_LogicError() {}
			CThrow_LengthError(_In_z_ const _CHAR* _strMessage) : std::length_error(""), IThrow_LogicError(_strMessage) {}
			CThrow_LengthError(_In_ const _STRING& _strMessage) : std::length_error(""), IThrow_LogicError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Length Error"); }
};

class CThrow_DomainError : 
	public						std::domain_error,
	virtual public				IThrow_LogicError
{
public:
			CThrow_DomainError() : std::domain_error(""), IThrow_LogicError() {}
			CThrow_DomainError(_In_z_ const _CHAR* _strMessage) : std::domain_error(""), IThrow_LogicError(_strMessage) {}
			CThrow_DomainError(_In_ const _STRING& _strMessage) : std::domain_error(""), IThrow_LogicError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Domain Error"); }
};

class CThrow_InvalidArgument : 
	public						std::invalid_argument,
	virtual public				IThrow_LogicError
{
public:
			CThrow_InvalidArgument() : std::invalid_argument(""), IThrow_LogicError() {}
			CThrow_InvalidArgument(_In_z_ const _CHAR* _strMessage) : std::invalid_argument(""), IThrow_LogicError(_strMessage) {}
			CThrow_InvalidArgument(_In_ const _STRING& _strMessage) : std::invalid_argument(""), IThrow_LogicError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Invalid Argument"); }
};

class CThrow_OutOfRange : 
	public						std::out_of_range,
	virtual public				IThrow_LogicError
{
public:
			CThrow_OutOfRange() : std::out_of_range(""), IThrow_LogicError() {}
			CThrow_OutOfRange(_In_z_ const _CHAR* _strMessage) : std::out_of_range(""), IThrow_LogicError(_strMessage) {}
			CThrow_OutOfRange(_In_ const _STRING& _strMessage) : std::out_of_range(""), IThrow_LogicError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Out of Range"); }
};


class IThrow_RuntimeError :
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			IThrow_RuntimeError() : ICGExceptionThrowableDescriptable() {}
			IThrow_RuntimeError(_In_z_ const _CHAR* _strMessage) : ICGExceptionThrowableDescriptable(_strMessage) {}
			IThrow_RuntimeError(_In_ const _STRING& _strMessage) : ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Runtime Error"); }
};

class CThrow_RuntimeError :
	public						std::runtime_error,
	virtual public				IThrow_RuntimeError
{
public:
			CThrow_RuntimeError() : std::runtime_error(""), IThrow_RuntimeError() {}
			CThrow_RuntimeError(_In_z_ const _CHAR* _strMessage) : std::runtime_error(""), IThrow_RuntimeError(_strMessage) {}
			CThrow_RuntimeError(_In_ const _STRING& _strMessage) : std::runtime_error(""), IThrow_RuntimeError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Runtime Error"); }
};

class CThrow_OverflowError : 
	public						std::overflow_error,
	virtual public				IThrow_RuntimeError
{
public:
			CThrow_OverflowError() : std::overflow_error(""), IThrow_RuntimeError() {}
			CThrow_OverflowError(_In_z_ const _CHAR* _strMessage) : std::overflow_error(""), IThrow_RuntimeError(_strMessage) {}
			CThrow_OverflowError(_In_ const _STRING& _strMessage) : std::overflow_error(""), IThrow_RuntimeError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Overflow Error"); }
};

class CThrow_UnderflowError : 
	public						std::underflow_error,
	virtual public				IThrow_RuntimeError
{
public:
			CThrow_UnderflowError() : std::underflow_error(""), IThrow_RuntimeError() {}
			CThrow_UnderflowError(_In_z_ const _CHAR* _strMessage) : std::underflow_error(""), IThrow_RuntimeError(_strMessage) {}
			CThrow_UnderflowError(_In_ const _STRING& _strMessage) : std::underflow_error(""), IThrow_RuntimeError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Underflow Error"); }
};

class CThrow_RangeError : 
	public						std::range_error,
	virtual public				IThrow_RuntimeError
{
public:
			CThrow_RangeError() : std::range_error(""), IThrow_RuntimeError() {}
			CThrow_RangeError(_In_z_ const _CHAR* _strMessage) : std::range_error(""), IThrow_RuntimeError(_strMessage) {}
			CThrow_RangeError(_In_ const _STRING& _strMessage) : std::range_error(""), IThrow_RuntimeError(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Range Error"); }
};

class CThrow_BadAlloc :
	public						std::bad_alloc,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_BadAlloc() : std::bad_alloc(), ICGExceptionThrowableDescriptable() {}
			CThrow_BadAlloc(_In_z_ const _CHAR* _strMessage) : std::bad_alloc(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_BadAlloc(_In_ const _STRING& _strMessage) : std::bad_alloc(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Bad Alloc"); }
};

class CThrow_BadException :
	public						std::bad_exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_BadException() : std::bad_exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_BadException(_In_z_ const _CHAR* _strMessage) : std::bad_exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_BadException(_In_ const _STRING& _strMessage) : std::bad_exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Bad Exception"); }
};




//-----------------------------------------------------------------------------
//
// 3. CGCII Exceptions
//
//  1) CThrow_BadFunctionCall : exception
//  2) CThrow_ConcurrenceLockError : exception
//  3) CThrow_AccessDenied : exception
//  4) CThrow_NoInitialized : exception
//  5) CThrow_NotExist :exception
//  6) CThrow_NotReady :exception
//  7) CThrow_TimeOut :exception
//  8) CThrow_Expired :exception
//  9) CThrow_CGCIIExpired
//
//-----------------------------------------------------------------------------
class CThrow_BadFunctionCall : 
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_BadFunctionCall() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_BadFunctionCall(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_BadFunctionCall(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Bad Function call"); }
};

class CThrow_ConcurrenceLockError : 
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_ConcurrenceLockError() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_ConcurrenceLockError(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_ConcurrenceLockError(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Concurrent Lock Error"); }
};

class CThrow_AccessDenied : 
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_AccessDenied() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_AccessDenied(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_AccessDenied(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
};

class CThrow_NoInitialized : 
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_NoInitialized() : std::exception(), ICGExceptionThrowable() {}
			CThrow_NoInitialized(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_NoInitialized(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("No Initialized"); }
};

class CThrow_NotExist :
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_NotExist() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_NotExist(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_NotExist(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Not Exist"); }
};

class CThrow_NotReady :
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_NotReady() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_NotReady(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_NotReady(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Not Ready"); }
};

class CThrow_AleadyExist :
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
	CThrow_AleadyExist() : std::exception(), ICGExceptionThrowableDescriptable() {}
	CThrow_AleadyExist(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
	CThrow_AleadyExist(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Aleady Exist"); }
};

class CThrow_TimeOut :
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_TimeOut() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_TimeOut(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_TimeOut(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Time Out"); }
};

class CThrow_Expired :
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_Expired() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_Expired(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_Expired(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Expired"); }
};

class CThrow_CGCIIExpired :
	public						std::exception,
	virtual public				ICGExceptionThrowable
{
public:
			CThrow_CGCIIExpired() : std::exception(), ICGExceptionThrowable() {}

public:
	virtual	const _CHAR*		What() const override					{ return _CGTEXT("CGCII Expired"); }
	virtual	const _CHAR*		Description() const override			{ return _CGTEXT("Update new version or contact us (sangduck@cgcii.co.kr)"); }
};

class CThrow_Critical :
	public						std::exception,
	virtual public				ICGExceptionThrowableDescriptable
{
public:
			CThrow_Critical() : std::exception(), ICGExceptionThrowableDescriptable() {}
			CThrow_Critical(_In_z_ const _CHAR* _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}
			CThrow_Critical(_In_ const _STRING& _strMessage) : std::exception(), ICGExceptionThrowableDescriptable(_strMessage) {}

public:
	virtual	const _CHAR*		What() const override { return _CGTEXT("Critical"); }
};




//-----------------------------------------------------------------------------
//
// 4. ...
//
//-----------------------------------------------------------------------------
template <class TOBJECT>
bool ExecuteExceptionHandler(TOBJECT* _pExceptionObject, const std::exception& _rException, _In_z_ const _CHAR* _strException)
{
	// 1) pExceptionHandler을 casting한다.
	auto*	pExceptionHandler = dynamic_cast<ICGExceptionHandleable*>(_pExceptionObject);

	// Check) pExceptionHandler가 nullptr이면 안됀다.
	RETURN_IF(pExceptionHandler == nullptr, false)

	// 2)  pExceptionHandler함수를 호출한다. 
	return	pExceptionHandler->OnException(_rException, _strException);
}


}