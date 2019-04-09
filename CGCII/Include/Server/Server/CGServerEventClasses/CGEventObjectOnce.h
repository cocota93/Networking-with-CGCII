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
namespace Object
{

class COnce :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGEventObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			COnce();
			COnce(const char* _strName);
			COnce(const wchar_t* _wstrName);
	virtual	~COnce();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetEventTime(_In_ const TIME::SYSTEM::time_point& _rtime);


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

protected:
	// 7) Event�� �����ߴ��� �ƴ����� ������ �Լ�.
			bool				m_bEvent;
};


}
}