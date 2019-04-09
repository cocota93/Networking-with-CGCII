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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// CGEvent::Object::COnce
//
// 1. CGEvent::Object::COnce��??
//    1) ������ �ð� �� �ѹ��� ������ �Ǵ� Event Object�̴�.
//    2) SetEventTime()�Լ��� ����Ͽ� ����� �ð��� ������ �� �ִ�.
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�Ƿ� �����ؾ� �Ѵ�.
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
