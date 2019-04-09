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
// CGEvent::Object::COnce
//
// 1. CGEvent::Object::COnce란??
//    1) 정해진 시간 딱 한번만 수행이 되는 Event Object이다.
//    2) SetEventTime()함수를 사용하여 실행될 시간을 설정할 수 있다.
//
//    주의!!!) 설정되는 시간은 모두 Local TIme이 아니라 System Time므로 주의해야 한다.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class COnce :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			COnce();
			COnce(const char* _strName);
			COnce(const wchar_t* _wstrName);
	virtual	~COnce();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetEventTime(_In_ const TIME::SYSTEM::time_point& _rtime);


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

protected:
	// 7) Event를 실행했는지 아닌지를 설정한 함수.
			bool				m_bEvent;
};


}
}