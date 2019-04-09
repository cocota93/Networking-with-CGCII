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

 @class		CBatchFunction
 @brief		���� ���� Executable ��ü�� �����ϱ� ���� Ŭ������ �Ϸ� �� �Լ��� ������ �ش�.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TEXECUTE=TFUNCTION>
class CBatchFunction :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NBatch
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CBatchFunction() : m_fFunction(nullptr)						{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_FUNCTION);}
	//! @brief ������ @param _Function ������ �Լ�
			CBatchFunction(_In_ const TEXECUTE& _Function) : m_fFunction(_Function) { SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_FUNCTION);}
	//! @brief '������ �Լ�' ������ �Բ� �����Ѵ�. @param _fFunction ������ �Լ�
	explicit CBatchFunction(_In_ TEXECUTE&& _fFunction) : m_fFunction(_fFunction) { SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_FUNCTION);}
	virtual ~CBatchFunction()											{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief ������ �Լ��� �����Ѵ�. @param _fFunction ������ �Լ�
			void				SetFunction(_In_ const TEXECUTE& _fFunction) { m_fFunction=_fFunction;}
	//! @brief ������ �Լ��� �����Ѵ�. @param _fFunction ������ �Լ�
			void				SetFunction(_In_ TEXECUTE&& _fFunction)	{ m_fFunction=std::move(_fFunction); }
	//! @brief ������ ������ �Լ��� ��´�. @return ������ �Լ��� ������
			TEXECUTE			GetFunction() const						{ return m_fFunction;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) ProcessCompleteExecution
	virtual	void				ProcessCompleteExecution() override		{ RETURN_IF(m_fFunction==nullptr, ); m_fFunction();}

private:
	// 2) ������ �Լ��� ������
	TEXECUTE			m_fFunction;
};


}
