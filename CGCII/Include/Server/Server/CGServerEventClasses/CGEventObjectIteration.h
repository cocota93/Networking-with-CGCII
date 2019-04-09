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
// CGEvent::Object::CIteration
//
// 1. CGEvent::Object::CIteration��??
//    1) ������ �ð����� ������ Ƚ�� Ȥ�� ���Ѵ�� �����ϴ� ���̴�.
//    2) SetInterval()�Լ��� ����Ͽ� ���ణ���� ������ �� �ִ�.
//    3) SetTimes()�Լ��� ����Ͽ� Ƚ���� ������ �� �ִ�.
//    4) ���� ������ �ð��� SetNextTime()�� ����Ͽ� �����ؾ� �Ѵ�.(�ݵ�� ����� �Ѵ�!)
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�Ƿ� �����ؾ� �Ѵ�.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CIteration :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CIteration();
			CIteration(const char* _strName);
			CIteration(const wchar_t* _wstrName);
	virtual	~CIteration();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) �������� �ð� ���� �Լ�.
			void				SetTimes(_In_ int _Times)				{	m_iTimes=_Times;}
			int					GetTimes() const						{	return m_iTimes;}

			void				SetNextTime(_In_ const TIME::SYSTEM::time_point& _rtime);

			void				SetInterval(_In_ const TIME::duration& _durationInterval);
			const TIME::duration& GetInterval() const					{	return m_timediffInterval;}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	virtual	eOBJECT_RESULT		ProcessEventIteration(_In_ const TIME::SYSTEM::time_point& _rtime) PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
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

protected:
	// 7) Ƚ�� ����
			int					m_iTimes;				// �ݺ� Ƚ��
			TIME::duration		m_timediffInterval;		// �ݺ� ����
};


}
}
