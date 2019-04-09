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
// CGEvent::Object::CSchedule
//
// 1. CGEvent::Object::CSchedule란??
//    1) 등록해놓은 시간에 실행되는 Event 객체이다.
//    2) 실행 시간(스케쥴)의 등록은 임의의 시간, 임의의 반복횟수를 설정할 수 있다.
//    3) 실행 시간의 등록 횟수는 제한이 없다.
//    
// 2. 실행시간의 등록과 사용
//    1) 실행시간은 EVENT_SCHEDULE 구조체를 사용하여 등록한다.
//    2) EVENT_SCHEDULE을 사용하여 다음 실행될 시간 (설정될 때 기준으로는 최초
//       실행 시간)과 반복실행할 경우 반복할 간격과 횟수를 설정해 줄수 있다.
//    3) 1회만 실행될 경우 반복횟수를 1로 설정해 주면 된다.
//    4) 설정된 EVENT_SCHEDULE를 AddSchedule()함수를 사용하여 설정할 수 있다.
//
//    5) SetNextEventAfterNow()함수.
//       - 실행시간이 현재 시간 이후로 설정된 것부터 실행하도록 한다.
//       - 만약 이 함수를 실행하지 않으면 이미 실행시간이 지난 것을 모두 실행한다.
//    6) 자주 사용되는 등록 함수.
//       - 자주 사용되는 스케쥴은 간단히 등록할 수 있도록 함수로 만들어 놓았다.
//         
//         AddScheduleHourly()   : 한시간 간격으로 실행되는 스케쥴을 추가한다.
//         AddScheduleDaily()    : 하루 간격으로 실행되는 스케쥴을 추가한다.
//         AddScheduleMonthly()  : 한달 간격으로 실행되는 스케쥴을 추가한다.
//         AddScheduleAnnually() : 년 간격으로 실행되는 스케쥴을 추가한다.
//
//    7) 실행할 내용의 정의
//       - CGEvent::Object::CSchedule를  상속받은 후 가상함수인 ProcessEvent() 
//         함수를 재정의하여 실행될 내용을 기술한다.
//
//    예제) Tutorials/[Server] 4. Event system/Tutorial_Event03_Schedule
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CSchedule :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Definition)
// ----------------------------------------------------------------------------
public:
			typedef	EVENT_SCHEDULE	EVENT;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CSchedule();
			CSchedule(const char* _strName);
			CSchedule(const wchar_t* _wstrName);
	virtual ~CSchedule();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 일반적인 Schedule 추가
			void				AddSchedule(_In_ const EVENT& _EventInfo);
			void				AddSchedule(_In_ const TIME::duration& _durationInterval, _In_ const TIME::SYSTEM::time_point& p_rFirst, _In_ int p_iTimes=EVENT_TIMES_INFINITE);

	// 2) Schedule의 삭제
			void				RemoveSchedule(int _Index);

	// 3) 다음 실행 Event를 설정하는 함수.
			void				SetNextEventAfterNow();

	// 4) Event의 갯수
			int					GetEventCount() const;


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	virtual	eOBJECT_RESULT		ProcessEvent(_In_ const TIME::SYSTEM::time_point& _rtime) PURE;


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

public:
	// 7) Event  List
			LOCKABLE<vector<EVENT>> m_queueEvent;

			const EVENT&		_top() const							{	return m_queueEvent.front();}
			void				_pop_heap();
			void				_push_heap(const EVENT& _schecule);
};


}
}