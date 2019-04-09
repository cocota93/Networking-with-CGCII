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
// CGEvent::Object::CScheduleFunction
//
// 1. CGEvent::Object::CScheduleFunction란??
//    1) 등록해놓은 시간에 실행되는 Event 객체로 기본적인 동작은 CSchedule과
//       동일하다.
//       하지만 차이점은 실행되는 내용을 ProcessEvent()함수를 재정의하여 설정하는
//       것이 아니라 일반함수, 람다함수, 멤버함수 등의 함수포인터를 넘겨 해당 내용을
//       실행할 수 있도록 한다는 것이다.
//    2) 따라서 CSchedule와는 달리 일반적인 경우는 상속하지 않고 사용할 수 있다.
//       
//    
// 2. 실행시간의 등록과 사용
//    1) 실행할 시간과 함수 등의 내용은 CGEvent::ISchedule를 상속받은 Schedule 
//       객체를 등록하여 정의한다.
//    2) 실행할 시간에 대한 등록은 CSchedule에서 사용하는 EVENT_SCHEDULE을 그대로
//       사용함으로 동일하다. 
//       하지만 실행되는 함수의 종류에 따라 3가지 형으로 나뉘어 진다.
//       
//    3) 1회만 실행될 경우 반복횟수를 1로 설정해 주면 된다.
//    4) 설정된 EVENT_SCHEDULE를 AddSchedule()함수를 사용하여 설정할 수 있다.
//
//       - CEventScheduleFunction       : 일반 함수형
//       - CEventScheduleLambda         : 람다 함수형
//       - CEventScheduleMemberFunction : 멤버 함수형 
//
//    5) 기본적인 사용방법은 위의 3가지 형태의 Schedule객체 혹은 CGEvent::ISchedule를
//       상속하여 만든 Schedule객체에 동적 생성하여 값을 설정한 후 AddSchedule()
//       함수를 사용하여 등록한다.
//
//
//    예제) Tutorials/[Server] 4. Event system\Tutorial_Event04_ScheduleFunction
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CScheduleFunction :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CScheduleFunction();
			CScheduleFunction(const char* _strName);
			CScheduleFunction(const wchar_t* _wstrName);
	virtual ~CScheduleFunction();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 일반적인 Schedule 추가
			void				AddSchedule(_In_ CGEvent::ISchedule* _pEventInfo);
			void				RemoveSchedule(_In_ int _Index);

	// 2) 다음 실행 Event를 설정하는 함수.
			void				SetNextEventAfterNow();

	// 3) Event의 갯수
			int					GetEventCount() const;


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
			LOCKABLE<vector<CGPTR<CGEvent::ISchedule>>> m_queueEvent;

			CGPTR<CGEvent::ISchedule> _top() const				{	return m_queueEvent.front();}
			void				_pop_heap();
			void				_push_heap(_In_ CGEvent::ISchedule* _schecule);
	static	bool				compare_function(_In_ CGEvent::ISchedule* _Left, _In_ CGEvent::ISchedule* _Right);
};


}
}
