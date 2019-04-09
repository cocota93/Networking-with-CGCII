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

 @class		CFunctionMember
 @brief		멤버 함수를 실행해준다.
 @todo		
 @ref		
 @details	\n
 특정 객체의 멤버함수를 실행해준다.
 그러기 위해 객체의 포인터와 멤버함수 포인터가 모두 설정되어야 한다.
 또 멤버함수의 포인터는 반드시 아무런 파라메터가 없는 함수여야 한다.

*///-----------------------------------------------------------------------------
template <class TCLASS>
class CFunctionMember :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
			typedef		intptr_t(TCLASS::*PMEMBERFUNCTION)();


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			 CFunctionMember() : m_pFunction(nullptr)					{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_FUNCTION_MEMBER);}
	//! @brief	생성과 함께 '실행 대상 객체'와 '실행할 멤버 함수'를 설정한다. @param _Object '실행 대상 객체' @param _pFunction '실행할 멤버 함수'
	explicit CFunctionMember(_In_ TCLASS* _Object, _In_ PMEMBERFUNCTION _pFunction) : m_pObject(_Object), m_pFunction(_pFunction)	{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_FUNCTION_MEMBER);}
	virtual	~CFunctionMember()											{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) 실행할 클래스 객체와 함수를 정의하는 함수.
	//! @brief '실행 대상 객체'를 설정한다. @param _Object 실행할 객체
			void				SetObject(_In_ TCLASS* _Object)			{	m_pObject=_Object;}
	//! @brief	설정된 '실행 대상 객체'를 얻는다. @return	'실행 대상 객체'
			CGPTR<TCLASS>		GetObject() const						{	return m_pObject;}
	//! @brief	실행할 객체를 제거한다.
			void				ResetObject()							{	m_pObject.reset();}

	//! @brief	실행할 멤버함수를 설정한다. @param _pFunction 실행할 멤버함수
			void				SetFunction(_In_ const PMEMBERFUNCTION& _pFunction) {	m_pFunction=_pFunction;}
	//! @brief	실행할 멤버함수를 설정한다. @param _pFunction 실행할 멤버함수
			void				SetFunction(_In_ PMEMBERFUNCTION&& _pFunction)		{	m_pFunction=std::move(_pFunction);}
	//! @brief	실행할 멤버함수를 얻는다. @return 실행할 멤버함수
			PMEMBERFUNCTION		GetFunction() const						{	return m_pFunction;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) 실행할 멤버함수의 포인터와 객체의 포인터
			PMEMBERFUNCTION		m_pFunction;
			CGPTR<TCLASS>		m_pObject;

private:
	virtual	intptr_t			ProcessExecute(_In_ intptr_t, _In_ size_t) override	{	RETURN_IF(m_pObject.empty() || m_pFunction==nullptr, intptr_t(1)); intptr_t hResult=(m_pObject->*m_pFunction)(); ResetObject(); return hResult;}
};


}