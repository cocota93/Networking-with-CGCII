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

namespace CGExecutor
{

//-----------------------------------------------------------------------------
/**

 @class		CCompletionPortThread
 @brief		CGExecutor::CCompletionPort에 Thread Pool을 결합한 클래스이다.
 @todo		
 @ref		CGExecutor::CCompletionPort
 @details	\n
 CGExecutor::CCompletePort의 Execute()함수를 CGAPI::CThreadPool의 쓰레드에서
 호출해준다.

*///-----------------------------------------------------------------------------
class CCompletionPortThread : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGAPI::CThreadPool,						// (@) I/O처리를 위한 Thread Pool
	public						CGExecutor::CCompletionPort				// (@) CompletionPort
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCompletionPortThread();
	//! @brief 생성 시 객체 이름을 설정한다. @param '객체 이름'
			CCompletionPortThread(_In_ const _CHAR* _strName);
			CCompletionPortThread(_In_ const _CHAR_SUB* _strName);
	virtual ~CCompletionPortThread();

	
// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief '실행자'를 쓰레드와 함께 실행한다. @param _iThreadCount 시작할 쓰레드 갯수 @return true 성공 @return false 실패
			bool				Start(_In_ int _iThreadCount=0);
	//! @brief '실행자'를 연다. @param _Msg 값을 전달할 메시지 @return true 성공 @return false 실패
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override;
	//!	@brief	'실행자'를 닫는다. @return true 닫기에 성공 @return false	실해(이미 닫기가 진행 중일 경우)
	virtual	bool				Stop() override;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			uint32_t			ProcessThreadRun();

protected:
			bool				m_bDone;
};


}
