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

namespace CGExecutable
{

//-----------------------------------------------------------------------------
/**

 @class		CFunction
 @brief		특정 함수를 실행해준다.
 @todo		
 @ref		
 @details	\n
 전역 함수, 람다 함수, std::bind() 함수 객체 등을 실행해준다.

*///-----------------------------------------------------------------------------
template <class TEXECUTE=TLAMBDA>
class CFunction :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CFunction() : m_fFunction(nullptr)							{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_FUNCTION);}
	//! @brief 생성자 @param _Function 실행할 함수
			CFunction(_In_ const TEXECUTE& _Function) : m_fFunction(_Function) { SetObjectType(eOBJECT_TYPE::EXECUTABLE_FUNCTION);}
	//! @brief 생성자 @param	_Function	실행할 함수
	explicit CFunction(_In_ TEXECUTE&& _Function) : m_fFunction(std::move(_Function)) { SetObjectType(eOBJECT_TYPE::EXECUTABLE_FUNCTION);}
	virtual	~CFunction()												{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief 실행할 함수를 설정한다. @param	_Function 실행할 함수
			void				SetFunction(_In_ const TEXECUTE& _Function) { m_fFunction = _Function; }
	//!	@brief 실행할 함수를 설정한다.(좌측값) @param	_Function 실행할 함수
			void				SetFunction(_In_ TEXECUTE&& _Function) { m_fFunction = _Function; }
	//!	@brief 설정된 실행할 함수를 얻는다. @return 실행할 함수의 포인터
			TEXECUTE			GetFunction() const						{ return m_fFunction; }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			TEXECUTE			m_fFunction;
private:
	virtual	intptr_t			ProcessExecute(_In_ intptr_t, _In_ size_t) override { return ProcessExecute_Result<decltype(m_fFunction())>();}
			template<class TRETURN>
			typename std::enable_if<std::is_void<TRETURN>::value, intptr_t>::type
								ProcessExecute_Result()					{ m_fFunction(); return intptr_t(0);}
			template<class TRETURN>
			typename std::enable_if<!std::is_void<TRETURN>::value, intptr_t>::type
								ProcessExecute_Result()					{ return static_cast<intptr_t>(m_fFunction());}
};


}
