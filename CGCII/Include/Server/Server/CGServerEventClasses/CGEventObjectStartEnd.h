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
// CGEvent::Object::CStartEnd
//
// 1. CGEvent::Object::CStartEnd
//    1) 정해진 Start()시간에 ProcessEventStart()함수가 호출되고
//       정해진 End시간에 ProecssEventEnd()함수가 호출되는 Event객체이다.
//    2) End이후에는 객체가 자동 Detach된다.
//    3) SetEventStartTime()과 SetEventEndTime()함수를 사용하여 시작시간과 끝시간을
//       설정할 수 있다.
//
//    주의!!!) 설정되는 시간은 모두 Local TIme이 아니라 System Time이다.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CStartEnd :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CStartEnd();
			CStartEnd(const char* _strName);
			CStartEnd(const wchar_t* _wstrName);
			CStartEnd(_In_ eEVENT_TYPE _eType, const char* _strName);
			CStartEnd(_In_ eEVENT_TYPE _eType, const wchar_t* _wstrName=nullptr);
	virtual	~CStartEnd();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetEventStartTime(_In_ const TIME::SYSTEM::time_point& _Time);
			const TIME::SYSTEM::time_point&	GetEventStartTime() const	{	return m_timeEvent_Start;}

			void				SetEventEndTime(_In_ const TIME::SYSTEM::time_point& _Time);
			const TIME::SYSTEM::time_point&	GetEventEndTime() const		{	return m_timeEvent_Terminate;}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	// 1) Event를 시작할 때 불려지는 함수.
	virtual	eOBJECT_RESULT		ProcessEventStart(_In_ const TIME::SYSTEM::time_point& _rtime) PURE;

	// 2) Event가 끝날 때 불려지는 함수.
	virtual	eOBJECT_RESULT		ProcessEventEnd(_In_ const TIME::SYSTEM::time_point& _rtime) PURE;


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
	// 6) 시작 시간.
			TIME::SYSTEM::time_point	m_timeEvent_Start;
			bool				m_bEvent_Start;

	// 7) 끝나는 시간
			TIME::SYSTEM::time_point	m_timeEvent_Terminate;
			bool				m_bEvent_Terminate;
};


}
}