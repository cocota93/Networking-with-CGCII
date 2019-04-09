//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Event Classes                            *
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
// ----------------------------------------------------------------------------
//
// CGEvent::Object::CStartIterationEnd
//
// 1. CGEvent::Object::CStartIterationEnd이란?
//    1) 시작과 종료시 실행될 Event가 설정되며 그 사이에 기간 동안 일정 간격으로  
//       Event함수를 호출하는 객체이다.
//    2) 쉽게 말해서 CStartEnd와 CIteration를 합한 것이며 설정 함수 역시 두 클래스
//       와 동일하다.
//
//    주의!!!) 설정되는 시간은 모두 Local TIme이 아니라 System Time이다.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CStartIterationEnd :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::Object::CStartEnd				// (@) Event Timer
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CStartIterationEnd();
			CStartIterationEnd(const char* _strName);
			CStartIterationEnd(const wchar_t* _wstrName);
	virtual	~CStartIterationEnd();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 실행 횟수를 설정한다.(-1이면 횟수에 관계없이 End때까지 반복 실행된다. 기본 설정값은 -1이다.)
			void				SetTimes(_In_ int _Times)				{	m_iTimesMax=_Times;}
			int					AddTimes(_In_ int _Times) 				{	m_iTimesMax+=_Times; return m_iTimesMax;}
			int					GetExecutedTimes() const				{	return m_iTimesMax-m_iTimesRemained;}
			int					GetRemainedTimes() const				{	return m_iTimesRemained;}

	// 2) 실행 간격을 설정한다.
			void				SetInterval(_In_ const TIME::duration& _durationInterval);
			const TIME::duration& GetInterval() const					{	return m_timediffInterval;}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	virtual	eOBJECT_RESULT		ProcessEventIteration(_In_ const TIME::SYSTEM::time_point& _rtime) PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Event 객체를 Reset했을 때 호출되는 함수.
	virtual	bool				ProcessResetEvent(_In_ uint32_t _Flag) override;

	// 2) Event 객체를 Enable/Disable 했을 때 호출되는 함수
	virtual	bool				ProcessEnableEvent() override;
	virtual	bool				ProcessDisableEvent() override;

	// 3) Event 객체를 등록했을때/등록해제했을 때 호출되는 함수
	virtual	bool				ProcessCheckRegisterEvent() override;
	virtual	void				ProcessRegisterEvent() override;
	virtual	void				ProcessUnregisterEvent() override;

	// 4) Event 객체를 잠시 중시 했을 때/다시 시작했을 때 호출되는 함수
	virtual	bool				ProcessSuspendEvent() override;
	virtual	bool				ProcessResumeEvent() override;

	// 5) Event 객체를 종료할 때 호출하는 함수
	virtual	void				ProcessCloseEvent() override;

	// 6) Event가 Execution되었을 때 처리과정을 설정한 함수(ICGExecutable)
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;

protected:
	// 7) 횟수 관계
			int					m_iTimesRemained;		// 현재 남아 있는 반복 횟수
			int					m_iTimesMax;			// 목표 반복 횟수
			TIME::duration		m_timediffInterval;			// 반복 간격

	// 8) 내부에서 사용되는 함수(ProcessExecute함수내에서 호출되는 함수)
			bool				ProcessExecute_Start(_In_ const TIME::SYSTEM::time_point& p_rtimeNow);
			bool				ProcessExecute_Iteration(_In_ const TIME::SYSTEM::time_point& p_rtimeNow);
			bool				ProcessExecute_End(_In_ const TIME::SYSTEM::time_point& p_rtimeNow);
};


}
}