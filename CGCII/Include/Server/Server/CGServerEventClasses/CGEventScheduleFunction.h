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
// CGEvent::Schedule::CFunction
//
// 1. CGEvent::Schedule::CFunction란??
//    1) CGEvent::Object::CScheduleFunction에 등록되어 사용될 수 있도록 많은
//       CGEvent::ISchedule를 상속받아 만들어 놓은 클래스이다.
//    2) 일반적인 함수 포인터를 받아 정해진 시간에 실행되도록 한다.
//       사용할 수 있는 함수 포인터의 형식은 아래와 같다.
//
//        bool (*EVENT_FUNCTION)(const SYSTEMTIME&);
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Schedule
{

struct CFunction : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::ISchedule
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetFunction(const EVENT_FUNCTION& p_pFunction){	functionEvent=p_pFunction;}
			const EVENT_FUNCTION& GetFunction() const						{	return functionEvent;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual eOBJECT_RESULT		ProcessExecuteFunction(const TIME::SYSTEM::time_point& _rtime) {	return functionEvent(_rtime);}

protected:
			EVENT_FUNCTION		functionEvent;
};


}
}