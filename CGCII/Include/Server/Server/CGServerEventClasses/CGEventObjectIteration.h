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
// CGEvent::Object::CIteration
//
// 1. CGEvent::Object::CIteration란??
//    1) 일정한 시간마다 정해진 횟수 혹은 무한대로 수행하는 것이다.
//    2) SetInterval()함수를 사용하여 실행간격을 설정할 수 있다.
//    3) SetTimes()함수를 사용하여 횟수를 설정할 수 있다.
//    4) 최초 실행할 시간은 SetNextTime()를 사용하여 설정해야 한다.(반드시 해줘야 한다!)
//
//    주의!!!) 설정되는 시간은 모두 Local TIme이 아니라 System Time므로 주의해야 한다.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CIteration :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CIteration();
			CIteration(const char* _strName);
			CIteration(const wchar_t* _wstrName);
	virtual	~CIteration();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 기존적인 시간 설정 함수.
			void				SetTimes(_In_ int _Times)				{	m_iTimes=_Times;}
			int					GetTimes() const						{	return m_iTimes;}

			void				SetNextTime(_In_ const TIME::SYSTEM::time_point& _rtime);

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
			int					m_iTimes;				// 반복 횟수
			TIME::duration		m_timediffInterval;		// 반복 간격
};


}
}
