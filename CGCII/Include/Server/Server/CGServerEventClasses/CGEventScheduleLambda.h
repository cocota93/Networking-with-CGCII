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
// CGEvent::Schedule::CLambda
//
// 1. CGEvent::Schedule::CLambda란??
//    1) CGEvent::Object::CScheduleFunction에 등록되어 사용될 수 있도록 많은
//       CGEvent::ISchedule를 상속받아 만들어 놓은 클래스이다.
//    2) 람다함수를 받아 정해진 시간에 실행되도록 한다.
//    3) 사용할 수 있는 람다함수의 형식은 TFUNCTION에 정의에 따른다.
//       즉, const SYSTEM&형을 인자로 받으며 리턴값이 bool형인 람다함수이다.
//
// ----------------------------------------------------------------------------
#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2008
namespace CGEvent
{
namespace Schedule
{

struct CLambda : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::ISchedule
{
// ****************************************************************************
// Definition)
// ----------------------------------------------------------------------------
public:
			typedef	std::function<eOBJECT_RESULT(const TIME::SYSTEM::time_point&)>	TFUNCTION;


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetFunction(const TFUNCTION& p_pFunction)	{	functionEvent=p_pFunction;}
			const TFUNCTION&	GetFunction() const							{	return functionEvent;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual eOBJECT_RESULT		ProcessExecuteFunction(const TIME::SYSTEM::time_point& _rtime) {	return functionEvent(_rtime);}

protected:
			TFUNCTION			functionEvent;

};

}
}
#endif
