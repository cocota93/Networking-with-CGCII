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

 @class		CBatchFunctionMember
 @brief		여러 개의 Executable 객체를 실행하기 위한 클래스로 완료 시 멤버 함수를 실행해 준다.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TOBJECT>
class CBatchFunctionMember :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NBatch
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
			typedef		void (TOBJECT::*PMEMBERFUNCTION)();


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CBatchFunctionMember() : m_pFunction(nullptr)				{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_FUNCTION_MEMBER);}
	/**	@brief	생성과 함게 멤버함수와 객체를 설정한다. @param	_Object 객체 @param	_pFunction 멤버함수 포인터*/
	explicit CBatchFunctionMember(_In_ TOBJECT* _Object, _In_ PMEMBERFUNCTION _pFunction) : m_pObject(_Object), m_pFunction(_pFunction)	{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_FUNCTION_MEMBER);}
	virtual	~CBatchFunctionMember()										{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) 실행할 클래스 객체와 함수를 정의하는 함수.
	//! @brief	실행할 객체를 설정한다. @param	_Object	실행할 객체
			void				SetObject(_In_ TOBJECT* _Object)		{	m_pObject=_Object;}
	//!	@brief	설정된 실행할 객체를 얻는다. @return	설정된 실행할 객체
			CGPTR<TOBJECT>		GetObject() const						{	return m_pObject;}
	//!	@brief	설정된 실행할 객체를 리셋한다.
			void				ResetObject()							{	m_pObject=nullptr;}
	//! @brief 실행할 멤버함수를 설정한다. @param	_pFunction	실행할 멤버함수
			void				SetFunction(_In_ PMEMBERFUNCTION _pFunction) {	m_pFunction=_pFunction;}
	//!	@brief	설정된 실행할 멤버함수를 얻는다. @return 설정된 실행할 멤버함수
			PMEMBERFUNCTION		GetFunction() const						{	return m_pFunction;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) 실행할 멤버함수의 포인터와 객체의 포인터
			PMEMBERFUNCTION		m_pFunction;
			CGPTR<TOBJECT>		m_pObject;

private:
	// 2) ProcessCompleteExecution
	virtual	void				ProcessCompleteExecution() override		{	RETURN_IF(m_pObject.empty() || m_pFunction==nullptr, ); (m_pObject->*m_pFunction)(); ResetObject();}
};


}

