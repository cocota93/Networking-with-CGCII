//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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
//-----------------------------------------------------------------------------
/**

 @class		NCGStartable
 @brief		ICGStartable�� ������ Ŭ����
 @todo		
 @ref		
 @details	\n

 */
//-----------------------------------------------------------------------------
class NCGStartable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGStartable,
	virtual	public				ICGObjectState
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief ���� ���� ���� �����Ѵ�. @return true ���� @return false ����
			bool				Start() { CGMSG_CONTEXT tempMSG; return Start(tempMSG); }
	//! @brief �����Ѵ�. @param _pMSG ���۽� ������ ���� @return true ���� @return false ����
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override;
	//! @brief �����Ѵ�. @return true ���� @return false ����
	virtual	bool				Stop() override;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief �ʱ�ȭ�Ǳ� �� ȣ��ȴ�.(OnDestroy()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStarting(CGMSG_CONTEXT& /*_Msg*/)	{}
	//! @brief �ʱ�ȭ�� �� ȣ��ȴ�.(OnDestroying()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStart(CGMSG_CONTEXT& /*_Msg*/)	{}

	//! @brief �ı��Ǳ� �� ȣ��ȴ�.(OnInitialize()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStopping()						{}
	//! @brief �ı��� �� ȣ��ȴ�.(OnInitializing()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStop()							{}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	//! @brief ���۽� ó���ؾ��� ������ �����Ѵ�. @param _Msg ���۽� ������ ����
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg);
	//! @brief ������ ó���ؾ��� ������ �����Ѵ�.
	virtual	void				ProcessStop();

	//! @brief �ڽ� ����� ���� ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg){ OnStarting(_Msg); }
	//! @brief �ڽ� ����� ���� ó���� ����� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessStart(CGMSG_CONTEXT& _Msg)	{ OnStart(_Msg); }
	//! @brief �ڽ� ����� ���� ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessStopping()					{ try{OnStopping();}catch(...){}}
	//! @brief �ڽ� ����� ���� ó���� ����� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessStop()						{ try{OnStop();}catch(...){} }
};
