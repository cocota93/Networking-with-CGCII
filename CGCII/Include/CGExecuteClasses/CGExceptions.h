//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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

namespace CGException
{
//-----------------------------------------------------------------------------
/**

 @class		CThrow_SEHException
 @brief		SEH예외 가 발생했을 때 던저지는 예외 객체이다.
 @todo		
 @ref		
 @details	\n
 일반적으로 Access violation, devide by zero와 같은 하드웨어 호은 O/S상의 SEH 예외가
 발생했을 때 던져진다.

*///-----------------------------------------------------------------------------
class CThrow_SEHException : 
	public						std::exception,
	virtual public				ICGExceptionThrowable
{
public:
			CThrow_SEHException() : std::exception(), ICGExceptionThrowable()	{}
			CThrow_SEHException(_EXCEPTION_POINTERS* p_ExceptionPointers) : 
				std::exception(),
				ICGExceptionThrowable()
			{
				// "System exception Errors"
				m_ExceptionRecord	 = *p_ExceptionPointers->ExceptionRecord;
				m_ContextRecord		 = *p_ExceptionPointers->ContextRecord;
			}

public:
	virtual	const _CHAR*		What() const override					{ return _CGTEXT("SEH Exception"); }
	virtual	const _CHAR*		Description() const override			{	return _CGTEXT("SEH Exception");}

public:
			EXCEPTION_RECORD	m_ExceptionRecord;
			CONTEXT				m_ContextRecord;
};


//-----------------------------------------------------------------------------
/**

@class		CThrow_InvalidParameterHandle
@brief		잘못된 인자가 발생했을 때 던져지는 예외 객체이다.
@todo
@ref
@details	\n
보안이 강화된 strcpy_s, memcpy_s 등과 같은 메모리 조작 함수들의 사용 중 파라메터로 전달된
버퍼의 부족과 같은 문제 발생시 던져진다.

*///-----------------------------------------------------------------------------
class CThrow_InvalidParameterHandle :
	public						std::exception,
	virtual public				ICGExceptionThrowable
{
public:
			CThrow_InvalidParameterHandle() : std::exception("System exception Errors", 0), ICGExceptionThrowable() {}

	virtual	const _CHAR*		What() const override					{ return _CGTEXT("Invalid Parameter Handle"); }
	virtual	const _CHAR*		Description() const override			{	return _CGTEXT("System exception Errors");}
};


//-----------------------------------------------------------------------------
/**

 @class		CThrow_ForceExceptionError
 @brief		강제 예외 발생을 했을 때 던져지는 예외 객체이다.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
class CThrow_ForceExceptionError : 
	public						std::exception,
	virtual public				ICGExceptionThrowable
{
public:
			CThrow_ForceExceptionError() : std::exception(), ICGExceptionThrowable()	{}
};


}
