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
// CGEvent::Object::CStartEnd
//
// 1. CGEvent::Object::CStartEnd
//    1) ������ Start()�ð��� ProcessEventStart()�Լ��� ȣ��ǰ�
//       ������ End�ð��� ProecssEventEnd()�Լ��� ȣ��Ǵ� Event��ü�̴�.
//    2) End���Ŀ��� ��ü�� �ڵ� Detach�ȴ�.
//    3) SetEventStartTime()�� SetEventEndTime()�Լ��� ����Ͽ� ���۽ð��� ���ð���
//       ������ �� �ִ�.
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�̴�.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CStartEnd :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CStartEnd();
			CStartEnd(const char* _strName);
			CStartEnd(const wchar_t* _wstrName);
			CStartEnd(_In_ eEVENT_TYPE _eType, const char* _strName);
			CStartEnd(_In_ eEVENT_TYPE _eType, const wchar_t* _wstrName=nullptr);
	virtual	~CStartEnd();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetEventStartTime(_In_ const TIME::SYSTEM::time_point& _Time);
			const TIME::SYSTEM::time_point&	GetEventStartTime() const	{	return m_timeEvent_Start;}

			void				SetEventEndTime(_In_ const TIME::SYSTEM::time_point& _Time);
			const TIME::SYSTEM::time_point&	GetEventEndTime() const		{	return m_timeEvent_Terminate;}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	// 1) Event�� ������ �� �ҷ����� �Լ�.
	virtual	eOBJECT_RESULT		ProcessEventStart(_In_ const TIME::SYSTEM::time_point& _rtime) PURE;

	// 2) Event�� ���� �� �ҷ����� �Լ�.
	virtual	eOBJECT_RESULT		ProcessEventEnd(_In_ const TIME::SYSTEM::time_point& _rtime) PURE;


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
	// 6) ���� �ð�.
			TIME::SYSTEM::time_point	m_timeEvent_Start;
			bool				m_bEvent_Start;

	// 7) ������ �ð�
			TIME::SYSTEM::time_point	m_timeEvent_Terminate;
			bool				m_bEvent_Terminate;
};


}
}