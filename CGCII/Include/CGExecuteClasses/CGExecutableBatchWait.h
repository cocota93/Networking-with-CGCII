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

 @class		CBatchWait
 @brief		여러 개의 Executable 객체를 실행하기 위한 클래스로 완료 될 때 까지 블록킹해준다.
 @todo		
 @ref		
 @details	\n
 WaitExecuteCompletion()를 사용하면 실행된 모든 Executable이 완료될 때까지 블록킹상태로 대기한다.
 모든 Executable 객체가 완료되면 그때 블록킹이 풀리며 진행된다.

*///-----------------------------------------------------------------------------
class CBatchWait :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NBatch
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CBatchWait();
	virtual ~CBatchWait();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) 실행 완료를 기다린다.
	/**
	@brief	모든 실행이 완료될 때까지 블록킹한다.
	@param	_Millisecond	최대 대기 시간 ( 이 시간이 지나면 완료되지 않아도 TIME_OUT으로 리턴된다.)
	@return	true			대기 설정에 성공
	@return	false			대기 설정에 실패 (일반적으로 객체가 하나도 없을 때 false를 리턴한다.)
	*/
			bool				WaitExecuteCompletion(_In_ uint32_t _Millisecond=INFINITE);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessCompleteExecution
	virtual	void				ProcessCompleteExecution() override;

	// 2) Executor
			HANDLE				m_hComplete;
};


}