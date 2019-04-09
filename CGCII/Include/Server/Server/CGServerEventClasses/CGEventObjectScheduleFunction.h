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
// CGEvent::Object::CScheduleFunction
//
// 1. CGEvent::Object::CScheduleFunction��??
//    1) ����س��� �ð��� ����Ǵ� Event ��ü�� �⺻���� ������ CSchedule��
//       �����ϴ�.
//       ������ �������� ����Ǵ� ������ ProcessEvent()�Լ��� �������Ͽ� �����ϴ�
//       ���� �ƴ϶� �Ϲ��Լ�, �����Լ�, ����Լ� ���� �Լ������͸� �Ѱ� �ش� ������
//       ������ �� �ֵ��� �Ѵٴ� ���̴�.
//    2) ���� CSchedule�ʹ� �޸� �Ϲ����� ���� ������� �ʰ� ����� �� �ִ�.
//       
//    
// 2. ����ð��� ��ϰ� ���
//    1) ������ �ð��� �Լ� ���� ������ CGEvent::ISchedule�� ��ӹ��� Schedule 
//       ��ü�� ����Ͽ� �����Ѵ�.
//    2) ������ �ð��� ���� ����� CSchedule���� ����ϴ� EVENT_SCHEDULE�� �״��
//       ��������� �����ϴ�. 
//       ������ ����Ǵ� �Լ��� ������ ���� 3���� ������ ������ ����.
//       
//    3) 1ȸ�� ����� ��� �ݺ�Ƚ���� 1�� ������ �ָ� �ȴ�.
//    4) ������ EVENT_SCHEDULE�� AddSchedule()�Լ��� ����Ͽ� ������ �� �ִ�.
//
//       - CEventScheduleFunction       : �Ϲ� �Լ���
//       - CEventScheduleLambda         : ���� �Լ���
//       - CEventScheduleMemberFunction : ��� �Լ��� 
//
//    5) �⺻���� ������� ���� 3���� ������ Schedule��ü Ȥ�� CGEvent::ISchedule��
//       ����Ͽ� ���� Schedule��ü�� ���� �����Ͽ� ���� ������ �� AddSchedule()
//       �Լ��� ����Ͽ� ����Ѵ�.
//
//
//    ����) Tutorials/[Server] 4. Event system\Tutorial_Event04_ScheduleFunction
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CScheduleFunction :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CScheduleFunction();
			CScheduleFunction(const char* _strName);
			CScheduleFunction(const wchar_t* _wstrName);
	virtual ~CScheduleFunction();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) �Ϲ����� Schedule �߰�
			void				AddSchedule(_In_ CGEvent::ISchedule* _pEventInfo);
			void				RemoveSchedule(_In_ int _Index);

	// 2) ���� ���� Event�� �����ϴ� �Լ�.
			void				SetNextEventAfterNow();

	// 3) Event�� ����
			int					GetEventCount() const;


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
			LOCKABLE<vector<CGPTR<CGEvent::ISchedule>>> m_queueEvent;

			CGPTR<CGEvent::ISchedule> _top() const				{	return m_queueEvent.front();}
			void				_pop_heap();
			void				_push_heap(_In_ CGEvent::ISchedule* _schecule);
	static	bool				compare_function(_In_ CGEvent::ISchedule* _Left, _In_ CGEvent::ISchedule* _Right);
};


}
}
