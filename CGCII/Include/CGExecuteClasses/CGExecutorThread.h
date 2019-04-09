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

 @class		NThread
 @brief		자체적인 쓰레드로 스스로 Execute()함수를 호출하는 Executor
 @todo		
 @ref		
 @details	\n
 자체적인 Thread를 가지고 있으며 m_dwExecuteGap마다 Execute()함수를 호출한다.
 StartTrhead()함수를 호출하여 Thread를 시작할 수 있으며 StopThread함수를 호출하여 Thread를 중단시킬수 있다.
 단일 Thread로만 동작한다.
 
*///-----------------------------------------------------------------------------
class NThread :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor,
	protected					CGAPI::CThread
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
	//! @brief 기본 생성자
			NThread();
	//! @brief 스킵 기능과 함께 생성한다. @param _tickdiff 실행 간격
			NThread(bool _bEnableFrameSkip);
	//! @brief 객체 이름과 실행 간격 설정과 함께 생성한다. @param _Name 객체 이름 @param _tickdiff 실행 간격
			NThread(_In_ const _CHAR* _strName, bool _bEnableFrameSkip=false);
			NThread(_In_ const _CHAR_SUB* _strName, bool _bEnableFrameSkip=false);
	virtual ~NThread();
	

// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Thread를 시작하고 정지시키기.
	//! @brief '실행자'를 연다. @param _Msg 값을 전달할 메시지 @return true 성공 @return false 실패
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override;
	//! @brief '실행 간격'을 설정해 '실행자'를 연다. @param _tickdiff '실행 간격' @return true 성공 @return false 실패
			bool				Start(_In_ TICK::duration _tickdiff);

	//!	@brief 실행자를 닫는다. @return true 성공 @return false 실패
	virtual bool				Stop() override;

	// 2) 실행간격 관련함수.
	//! @brief 설정된 '실행 간격'을 얻는다. @return '실행 간격'
			TICK::duration		GetExecuteGap() const					{	return m_tickdiffExecute;}
	//! @brief '실행 간격'을 설정한다.
			void				SetExecuteGap(_In_ TICK::duration _tickdiff);

	// 3) Skip설정
	//! @brief 프레임 스킵 기능이 활성화 되어 있는지를 확인한다. @return true 활성화 @return false 비활성화
			bool				IsEnableFrameSkip() const				{	return m_bEnableFrameSkip;}
	//! @brief 프레임 스킵 기능이 설정한다. @param _bEnable 활성화 여부 @return true 활성화
			void				EnableFrameSkip(bool _bEnable=true)		{	m_bEnableFrameSkip=_bEnable;}
	//! @brief 프레임 스킵 기능이 비설정한다. 
			void				DisableFrameSkip()						{	EnableFrameSkip(false);}
	//! @brief 프레임 스킵 기능의 상태를 반전한다.
			void				ToggleFrameSkip()						{	EnableFrameSkip(!m_bEnableFrameSkip);}

	// 4) Thread관련(Delegation함수)
	//! @brief 쓰레드의 실행을 잠시 중단한다. @return 쓰레드 핸들
			uint32_t			Suspend()								{	return CGAPI::CThread::Suspend();}
	//! @brief 잠시 중단 했던 쓰레드를 다시 시작한다. @return 쓰레드 핸들
			uint32_t			Resume()								{	return CGAPI::CThread::Resume();}
	//! @brief '쓰레드 핸들'을 얻는다. @return '쓰레드 핸들'
			THREAD_ID			GetThreadHandle() const					{	return CGAPI::CThread::GetThreadHandle();}
	//!	@brief 강제로 예외를 발생시킨다. @return true 성공 @return false 실패
			bool				RaiseException()						{	return CGAPI::CThread::RaiseException();}
			

// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) 실행상태를 나타내는 변수
	//    - m_bRun이 false면 Thread가 무한 루프에서 빠져나와 Thread를 종료하게 된다.
	//    - 이 변수는 StartThread()에서 true로 바뀌고 StopThread에서 false로 바뀐다.
			ATOMIC<int>			m_bRun;
			bool				m_bEnableFrameSkip;

	// 2) 실행하는 간격(tick)
	//    - m_dwExecuteGap마다 한번식 Execute()함수를 호출하게 된다.
			TICK::duration		m_tickdiffExecute;

protected:
	static	uint32_t			fnThread(_In_ NThread* p_this);
			uint32_t			ThreadRun();
};


}
