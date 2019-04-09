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
// CGEvent::Object::CSchedule
//
// 1. CGEvent::Object::CSchedule��??
//    1) ����س��� �ð��� ����Ǵ� Event ��ü�̴�.
//    2) ���� �ð�(������)�� ����� ������ �ð�, ������ �ݺ�Ƚ���� ������ �� �ִ�.
//    3) ���� �ð��� ��� Ƚ���� ������ ����.
//    
// 2. ����ð��� ��ϰ� ���
//    1) ����ð��� EVENT_SCHEDULE ����ü�� ����Ͽ� ����Ѵ�.
//    2) EVENT_SCHEDULE�� ����Ͽ� ���� ����� �ð� (������ �� �������δ� ����
//       ���� �ð�)�� �ݺ������� ��� �ݺ��� ���ݰ� Ƚ���� ������ �ټ� �ִ�.
//    3) 1ȸ�� ����� ��� �ݺ�Ƚ���� 1�� ������ �ָ� �ȴ�.
//    4) ������ EVENT_SCHEDULE�� AddSchedule()�Լ��� ����Ͽ� ������ �� �ִ�.
//
//    5) SetNextEventAfterNow()�Լ�.
//       - ����ð��� ���� �ð� ���ķ� ������ �ͺ��� �����ϵ��� �Ѵ�.
//       - ���� �� �Լ��� �������� ������ �̹� ����ð��� ���� ���� ��� �����Ѵ�.
//    6) ���� ���Ǵ� ��� �Լ�.
//       - ���� ���Ǵ� �������� ������ ����� �� �ֵ��� �Լ��� ����� ���Ҵ�.
//         
//         AddScheduleHourly()   : �ѽð� �������� ����Ǵ� �������� �߰��Ѵ�.
//         AddScheduleDaily()    : �Ϸ� �������� ����Ǵ� �������� �߰��Ѵ�.
//         AddScheduleMonthly()  : �Ѵ� �������� ����Ǵ� �������� �߰��Ѵ�.
//         AddScheduleAnnually() : �� �������� ����Ǵ� �������� �߰��Ѵ�.
//
//    7) ������ ������ ����
//       - CGEvent::Object::CSchedule��  ��ӹ��� �� �����Լ��� ProcessEvent() 
//         �Լ��� �������Ͽ� ����� ������ ����Ѵ�.
//
//    ����) Tutorials/[Server] 4. Event system/Tutorial_Event03_Schedule
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CSchedule :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Definition)
// ----------------------------------------------------------------------------
public:
			typedef	EVENT_SCHEDULE	EVENT;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CSchedule();
			CSchedule(const char* _strName);
			CSchedule(const wchar_t* _wstrName);
	virtual ~CSchedule();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) �Ϲ����� Schedule �߰�
			void				AddSchedule(_In_ const EVENT& _EventInfo);
			void				AddSchedule(_In_ const TIME::duration& _durationInterval, _In_ const TIME::SYSTEM::time_point& p_rFirst, _In_ int p_iTimes=EVENT_TIMES_INFINITE);

	// 2) Schedule�� ����
			void				RemoveSchedule(int _Index);

	// 3) ���� ���� Event�� �����ϴ� �Լ�.
			void				SetNextEventAfterNow();

	// 4) Event�� ����
			int					GetEventCount() const;


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	virtual	eOBJECT_RESULT		ProcessEvent(_In_ const TIME::SYSTEM::time_point& _rtime) PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Event ��ü�� Reset���� �� ȣ��Ǵ� �Լ�.
	virtual	bool				ProcessResetEvent(_In_ uint32_t _Flag) override;

	// 2) Event ��ü�� Enable/Disable ���� �� ȣ��Ǵ� �Լ�
	virtual	bool				ProcessEnableEvent() override;
	virtual	bool				ProcessDisableEvent() override;

	// 3) Event ��ü�� ���������/����������� �� ȣ��Ǵ� �Լ�
	virtual	bool				ProcessCheckRegisterEvent() override;
	virtual	void				ProcessRegisterEvent() override;
	virtual	void				ProcessUnregisterEvent() override;

	// 4) Event ��ü�� ��� �߽� ���� ��/�ٽ� �������� �� ȣ��Ǵ� �Լ�
	virtual	bool				ProcessSuspendEvent() override;
	virtual	bool				ProcessResumeEvent() override;

	// 5) Event ��ü�� ������ �� ȣ���ϴ� �Լ�
	virtual	void				ProcessCloseEvent() override;

	// 6) Event�� Execution�Ǿ��� �� ó�������� ������ �Լ�(ICGExecutable)
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;

public:
	// 7) Event  List
			LOCKABLE<vector<EVENT>> m_queueEvent;

			const EVENT&		_top() const							{	return m_queueEvent.front();}
			void				_pop_heap();
			void				_push_heap(const EVENT& _schecule);
};


}
}