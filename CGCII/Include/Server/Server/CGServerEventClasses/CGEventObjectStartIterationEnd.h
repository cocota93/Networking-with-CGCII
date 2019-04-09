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
// CGEvent::Object::CStartIterationEnd
//
// 1. CGEvent::Object::CStartIterationEnd�̶�?
//    1) ���۰� ����� ����� Event�� �����Ǹ� �� ���̿� �Ⱓ ���� ���� ��������  
//       Event�Լ��� ȣ���ϴ� ��ü�̴�.
//    2) ���� ���ؼ� CStartEnd�� CIteration�� ���� ���̸� ���� �Լ� ���� �� Ŭ����
//       �� �����ϴ�.
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�̴�.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CStartIterationEnd :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::Object::CStartEnd				// (@) Event Timer
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CStartIterationEnd();
			CStartIterationEnd(const char* _strName);
			CStartIterationEnd(const wchar_t* _wstrName);
	virtual	~CStartIterationEnd();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) ���� Ƚ���� �����Ѵ�.(-1�̸� Ƚ���� ������� End������ �ݺ� ����ȴ�. �⺻ �������� -1�̴�.)
			void				SetTimes(_In_ int _Times)				{	m_iTimesMax=_Times;}
			int					AddTimes(_In_ int _Times) 				{	m_iTimesMax+=_Times; return m_iTimesMax;}
			int					GetExecutedTimes() const				{	return m_iTimesMax-m_iTimesRemained;}
			int					GetRemainedTimes() const				{	return m_iTimesRemained;}

	// 2) ���� ������ �����Ѵ�.
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

protected:
	// 7) Ƚ�� ����
			int					m_iTimesRemained;		// ���� ���� �ִ� �ݺ� Ƚ��
			int					m_iTimesMax;			// ��ǥ �ݺ� Ƚ��
			TIME::duration		m_timediffInterval;			// �ݺ� ����

	// 8) ���ο��� ���Ǵ� �Լ�(ProcessExecute�Լ������� ȣ��Ǵ� �Լ�)
			bool				ProcessExecute_Start(_In_ const TIME::SYSTEM::time_point& p_rtimeNow);
			bool				ProcessExecute_Iteration(_In_ const TIME::SYSTEM::time_point& p_rtimeNow);
			bool				ProcessExecute_End(_In_ const TIME::SYSTEM::time_point& p_rtimeNow);
};


}
}