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
// CGEvent::Schedule::CLambda
//
// 1. CGEvent::Schedule::CLambda��??
//    1) CGEvent::Object::CScheduleFunction�� ��ϵǾ� ���� �� �ֵ��� ����
//       CGEvent::ISchedule�� ��ӹ޾� ����� ���� Ŭ�����̴�.
//    2) �����Լ��� �޾� ������ �ð��� ����ǵ��� �Ѵ�.
//    3) ����� �� �ִ� �����Լ��� ������ TFUNCTION�� ���ǿ� ������.
//       ��, const SYSTEM&���� ���ڷ� ������ ���ϰ��� bool���� �����Լ��̴�.
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
