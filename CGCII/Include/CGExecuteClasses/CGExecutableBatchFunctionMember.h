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

namespace CGExecutable
{

//-----------------------------------------------------------------------------
/**

 @class		CBatchFunctionMember
 @brief		���� ���� Executable ��ü�� �����ϱ� ���� Ŭ������ �Ϸ� �� ��� �Լ��� ������ �ش�.
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
	/**	@brief	������ �԰� ����Լ��� ��ü�� �����Ѵ�. @param	_Object ��ü @param	_pFunction ����Լ� ������*/
	explicit CBatchFunctionMember(_In_ TOBJECT* _Object, _In_ PMEMBERFUNCTION _pFunction) : m_pObject(_Object), m_pFunction(_pFunction)	{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_FUNCTION_MEMBER);}
	virtual	~CBatchFunctionMember()										{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) ������ Ŭ���� ��ü�� �Լ��� �����ϴ� �Լ�.
	//! @brief	������ ��ü�� �����Ѵ�. @param	_Object	������ ��ü
			void				SetObject(_In_ TOBJECT* _Object)		{	m_pObject=_Object;}
	//!	@brief	������ ������ ��ü�� ��´�. @return	������ ������ ��ü
			CGPTR<TOBJECT>		GetObject() const						{	return m_pObject;}
	//!	@brief	������ ������ ��ü�� �����Ѵ�.
			void				ResetObject()							{	m_pObject=nullptr;}
	//! @brief ������ ����Լ��� �����Ѵ�. @param	_pFunction	������ ����Լ�
			void				SetFunction(_In_ PMEMBERFUNCTION _pFunction) {	m_pFunction=_pFunction;}
	//!	@brief	������ ������ ����Լ��� ��´�. @return ������ ������ ����Լ�
			PMEMBERFUNCTION		GetFunction() const						{	return m_pFunction;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) ������ ����Լ��� �����Ϳ� ��ü�� ������
			PMEMBERFUNCTION		m_pFunction;
			CGPTR<TOBJECT>		m_pObject;

private:
	// 2) ProcessCompleteExecution
	virtual	void				ProcessCompleteExecution() override		{	RETURN_IF(m_pObject.empty() || m_pFunction==nullptr, ); (m_pObject->*m_pFunction)(); ResetObject();}
};


}

