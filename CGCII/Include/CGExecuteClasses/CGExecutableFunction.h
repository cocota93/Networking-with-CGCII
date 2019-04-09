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

 @class		CFunction
 @brief		Ư�� �Լ��� �������ش�.
 @todo		
 @ref		
 @details	\n
 ���� �Լ�, ���� �Լ�, std::bind() �Լ� ��ü ���� �������ش�.

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
	//! @brief ������ @param _Function ������ �Լ�
			CFunction(_In_ const TEXECUTE& _Function) : m_fFunction(_Function) { SetObjectType(eOBJECT_TYPE::EXECUTABLE_FUNCTION);}
	//! @brief ������ @param	_Function	������ �Լ�
	explicit CFunction(_In_ TEXECUTE&& _Function) : m_fFunction(std::move(_Function)) { SetObjectType(eOBJECT_TYPE::EXECUTABLE_FUNCTION);}
	virtual	~CFunction()												{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief ������ �Լ��� �����Ѵ�. @param	_Function ������ �Լ�
			void				SetFunction(_In_ const TEXECUTE& _Function) { m_fFunction = _Function; }
	//!	@brief ������ �Լ��� �����Ѵ�.(������) @param	_Function ������ �Լ�
			void				SetFunction(_In_ TEXECUTE&& _Function) { m_fFunction = _Function; }
	//!	@brief ������ ������ �Լ��� ��´�. @return ������ �Լ��� ������
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
