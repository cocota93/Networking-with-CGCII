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
// CGEvent::Schedule::CFunction
//
// 1. CGEvent::Schedule::CFunction��??
//    1) CGEvent::Object::CScheduleFunction�� ��ϵǾ� ���� �� �ֵ��� ����
//       CGEvent::ISchedule�� ��ӹ޾� ����� ���� Ŭ�����̴�.
//    2) �Ϲ����� �Լ� �����͸� �޾� ������ �ð��� ����ǵ��� �Ѵ�.
//       ����� �� �ִ� �Լ� �������� ������ �Ʒ��� ����.
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