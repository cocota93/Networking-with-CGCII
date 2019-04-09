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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGException
{
//-----------------------------------------------------------------------------
/**

 @class		CThrow_SEHException
 @brief		SEH���� �� �߻����� �� �������� ���� ��ü�̴�.
 @todo		
 @ref		
 @details	\n
 �Ϲ������� Access violation, devide by zero�� ���� �ϵ���� ȣ�� O/S���� SEH ���ܰ�
 �߻����� �� ��������.

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
@brief		�߸��� ���ڰ� �߻����� �� �������� ���� ��ü�̴�.
@todo
@ref
@details	\n
������ ��ȭ�� strcpy_s, memcpy_s ��� ���� �޸� ���� �Լ����� ��� �� �Ķ���ͷ� ���޵�
������ ������ ���� ���� �߻��� ��������.

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
 @brief		���� ���� �߻��� ���� �� �������� ���� ��ü�̴�.
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
