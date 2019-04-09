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

class ISchedule : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						EVENT_SCHEDULE,
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	virtual eOBJECT_RESULT		ProcessExecuteFunction(const TIME::SYSTEM::time_point& _rtime) PURE;
};


}
