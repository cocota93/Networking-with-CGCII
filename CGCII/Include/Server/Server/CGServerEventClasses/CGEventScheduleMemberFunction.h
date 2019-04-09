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
// CGEvent::Schedule::CMemberFunction<TCLASS>
//
// 1. CGEvent::Schedule::CMemberFunction<TCLASS>란??
//    1) CGEvent::Object::CScheduleFunction에 등록되어 사용될 수 있도록 많은
//       CGEvent::ISchedule를 상속받아 만들어 놓은 클래스이다.
//    2) 객체의 멤버함수를 받아 정해진 시간에 실행되도록 한다.
//       따라서 멤버함수의 포인터뿐만 아니라 객체의 포인터 역시 설정해 주어야 한다.
//       또 TCLASS는 객체의 형과 일치하도록 설정해 주어야 한다.
//    3) 사용할 수 있는 멤버 함수의 형식은 PMEMBERFUNCTION에 정의에 따른다.
//       즉, const SYSTEM&형을 인자로 받으며 리턴값이 bool형인 람다함수이다.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Schedule
{

template <typename TCLASS>
struct CMemberFunction :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::ISchedule
{
// ****************************************************************************
// Definition)
// ----------------------------------------------------------------------------
public:
			typedef	eOBJECT_RESULT (TCLASS::*PMEMBERFUNCTION)(const TIME::SYSTEM::time_point& _rtime);


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetFunction(TCLASS* p_pObject, const PMEMBERFUNCTION& p_pFunction)	{	pObject=p_pObject; functionEvent=p_pFunction;}
			PMEMBERFUNCTION		GetFunction() const							{	return functionEvent;}
			TCLASS*				GetObject() const							{	return pObject;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual eOBJECT_RESULT		ProcessExecuteFunction(const TIME::SYSTEM::time_point& _rtime)	{	return	(pObject->*functionEvent)(_rtime);}

protected:
			PMEMBERFUNCTION		functionEvent;
			TCLASS*				pObject;
};


}
}