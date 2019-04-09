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
// CGEvent::Schedule::CMemberFunction<TCLASS>
//
// 1. CGEvent::Schedule::CMemberFunction<TCLASS>��??
//    1) CGEvent::Object::CScheduleFunction�� ��ϵǾ� ���� �� �ֵ��� ����
//       CGEvent::ISchedule�� ��ӹ޾� ����� ���� Ŭ�����̴�.
//    2) ��ü�� ����Լ��� �޾� ������ �ð��� ����ǵ��� �Ѵ�.
//       ���� ����Լ��� �����ͻӸ� �ƴ϶� ��ü�� ������ ���� ������ �־�� �Ѵ�.
//       �� TCLASS�� ��ü�� ���� ��ġ�ϵ��� ������ �־�� �Ѵ�.
//    3) ����� �� �ִ� ��� �Լ��� ������ PMEMBERFUNCTION�� ���ǿ� ������.
//       ��, const SYSTEM&���� ���ڷ� ������ ���ϰ��� bool���� �����Լ��̴�.
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