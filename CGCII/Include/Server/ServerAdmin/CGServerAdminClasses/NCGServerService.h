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
class NCGServerService : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGServerService,
	public						CGNameable::NString,
	public						NCGObjectState,
	public						NCGStartable,
	public						NCGInitializable,
	public						NCGPausable,
	public						CGNet::IO::Messageable::NBase,
	virtual public				NCGDispatchable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NCGServerService(_In_opt_z_ const _CHAR* _strName);
			NCGServerService(_In_opt_z_ const _CHAR_SUB* _strName = nullptr);
	virtual ~NCGServerService();


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	//! @brief ���� ���� �����ϱ� ���� �Լ�
	virtual	void				OnServiceSetting(CGMSG_CONTEXT& /*_Msg*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	//! @brief �ʱ�ȭ ������ �����Ѵ�. @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual	void				ProcessInitialize(CGMSG_CONTEXT& _Msg) override;
	//! @brief �ı� ������ �����Ѵ�.
	virtual	void				ProcessDestroy() override;
	//! @brief ���۽� ó���ؾ��� ������ �����Ѵ�. @param _Msg ���۽� ������ ����
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg) override;
	//! @brief ������ ó���ؾ��� ������ �����Ѵ�.
	virtual	void				ProcessStop() override;
	//! @brief ��� ������ �� ó���ؾ��� ������ �����Ѵ�. @param _Msg ������ ����
	virtual	void				ProcessPause() override;
	//! @brief ������ ������ �� ó���ؾ��� ������ �����Ѵ�.
	virtual	void				ProcessContinue() override;


	//! @brief �ڽ� ����� �ʱ�ȭ ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	//! @brief �ڽ� ����� ���� ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;

	//! @brief ���°� �ٲ���� ���� ó�� @param _eStatus �ٲ� ���ο� ����
	virtual	void				ProcessStateChanged(eOBJECT_STATE _eStatus) override;
};
