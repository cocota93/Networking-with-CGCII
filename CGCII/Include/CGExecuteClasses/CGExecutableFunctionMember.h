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

 @class		CFunctionMember
 @brief		��� �Լ��� �������ش�.
 @todo		
 @ref		
 @details	\n
 Ư�� ��ü�� ����Լ��� �������ش�.
 �׷��� ���� ��ü�� �����Ϳ� ����Լ� �����Ͱ� ��� �����Ǿ�� �Ѵ�.
 �� ����Լ��� �����ʹ� �ݵ�� �ƹ��� �Ķ���Ͱ� ���� �Լ����� �Ѵ�.

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
	//! @brief	������ �Բ� '���� ��� ��ü'�� '������ ��� �Լ�'�� �����Ѵ�. @param _Object '���� ��� ��ü' @param _pFunction '������ ��� �Լ�'
	explicit CFunctionMember(_In_ TCLASS* _Object, _In_ PMEMBERFUNCTION _pFunction) : m_pObject(_Object), m_pFunction(_pFunction)	{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_FUNCTION_MEMBER);}
	virtual	~CFunctionMember()											{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) ������ Ŭ���� ��ü�� �Լ��� �����ϴ� �Լ�.
	//! @brief '���� ��� ��ü'�� �����Ѵ�. @param _Object ������ ��ü
			void				SetObject(_In_ TCLASS* _Object)			{	m_pObject=_Object;}
	//! @brief	������ '���� ��� ��ü'�� ��´�. @return	'���� ��� ��ü'
			CGPTR<TCLASS>		GetObject() const						{	return m_pObject;}
	//! @brief	������ ��ü�� �����Ѵ�.
			void				ResetObject()							{	m_pObject.reset();}

	//! @brief	������ ����Լ��� �����Ѵ�. @param _pFunction ������ ����Լ�
			void				SetFunction(_In_ const PMEMBERFUNCTION& _pFunction) {	m_pFunction=_pFunction;}
	//! @brief	������ ����Լ��� �����Ѵ�. @param _pFunction ������ ����Լ�
			void				SetFunction(_In_ PMEMBERFUNCTION&& _pFunction)		{	m_pFunction=std::move(_pFunction);}
	//! @brief	������ ����Լ��� ��´�. @return ������ ����Լ�
			PMEMBERFUNCTION		GetFunction() const						{	return m_pFunction;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) ������ ����Լ��� �����Ϳ� ��ü�� ������
			PMEMBERFUNCTION		m_pFunction;
			CGPTR<TCLASS>		m_pObject;

private:
	virtual	intptr_t			ProcessExecute(_In_ intptr_t, _In_ size_t) override	{	RETURN_IF(m_pObject.empty() || m_pFunction==nullptr, intptr_t(1)); intptr_t hResult=(m_pObject->*m_pFunction)(); ResetObject(); return hResult;}
};


}