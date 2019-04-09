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

 @class		CBatchFunction
 @brief		여러 개의 Executable 객체를 실행하기 위한 클래스로 완료 시 함수를 실행해 준다.
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
	//! @brief 생성자 @param _Function 실행할 함수
			CBatchFunction(_In_ const TEXECUTE& _Function) : m_fFunction(_Function) { SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_FUNCTION);}
	//! @brief '실행할 함수' 설정과 함께 생성한다. @param _fFunction 실행할 함수
	explicit CBatchFunction(_In_ TEXECUTE&& _fFunction) : m_fFunction(_fFunction) { SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_FUNCTION);}
	virtual ~CBatchFunction()											{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief 실행할 함수를 설정한다. @param _fFunction 실행할 함수
			void				SetFunction(_In_ const TEXECUTE& _fFunction) { m_fFunction=_fFunction;}
	//! @brief 실행할 함수를 설정한다. @param _fFunction 실행할 함수
			void				SetFunction(_In_ TEXECUTE&& _fFunction)	{ m_fFunction=std::move(_fFunction); }
	//! @brief 설정된 실행할 함수를 얻는다. @return 실행할 함수의 포인터
			TEXECUTE			GetFunction() const						{ return m_fFunction;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) ProcessCompleteExecution
	virtual	void				ProcessCompleteExecution() override		{ RETURN_IF(m_fFunction==nullptr, ); m_fFunction();}

private:
	// 2) 실행할 함수의 포인터
	TEXECUTE			m_fFunction;
};


}
