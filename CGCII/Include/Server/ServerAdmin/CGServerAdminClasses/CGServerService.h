//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// NCGServerService
//
// 1. Service�� Server�� ���۽�Ű�� ���� ���񽺸� ��üȭ�� ���̴�.
//    1) Service�� ���� �⺻���� ������ ������ ���� Service Ŭ�����̴�.
//    2) 
//
//
// ----------------------------------------------------------------------------
class CCGServerService : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NCGServerService						//     CGServerService
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CCGServerService(_In_opt_z_ const _CHAR* _strName);
			CCGServerService(_In_opt_z_ const _CHAR_SUB* _strName = nullptr);
	virtual ~CCGServerService();


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
	//! @brief ���� ���� �����ϱ� ���� �Լ�
	virtual	void				OnServiceSetting(CGMSG_CONTEXT& /*_Msg*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Status�� ����Ǿ��� �� ȣ��Ǵ� �Լ�.
	virtual	void				ProcessStateChanged(eOBJECT_STATE _eStatus) override;

	// 2) Init/Destroy
	virtual	void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	virtual	void				_ProcessDestroying() override;

	//! @brief �ڽ� ����� ���� ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;

	// 3) Open/Close
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg) override;
	virtual	void				ProcessStop() override;
	virtual	void				ProcessPause() override;
	virtual	void				ProcessContinue() override;

protected:
	// 4) Admin System�� ���� Socket��
			CGPTR<CGServerAdmin::CSocketToHostAgent>	m_psocketHostAgent;
};
