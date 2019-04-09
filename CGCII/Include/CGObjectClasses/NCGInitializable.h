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

 @class		NCGInitializable
 @brief		ICGInitializable�� ������ Ŭ����
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class NCGInitializable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				ICGObjectState,
	virtual public				ICGInitializable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual ~NCGInitializable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief ���� ���� ���� �ʱ�ȭ�� �����Ѵ�. @return true ���� @return false ����
			bool				Initialize() { CGMSG_CONTEXT tempMSG; return Initialize(tempMSG); }
	//! @brief �ʱ�ȭ�Ѵ�. @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���@return true ���� @return false ����
	virtual	bool				Initialize(CGMSG_CONTEXT& _Msg) override;
	//! @brief �ı��Ѵ�. @return true ���� @return false ����
	virtual	bool				Destroy() override;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief �ʱ�ȭ�Ǳ� �� ȣ��ȴ�.(OnDestroy()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnInitializing(CGMSG_CONTEXT& /*_Msg*/)			{}
	//! @brief �ʱ�ȭ�� �� ȣ��ȴ�.(OnDestroying()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnInitialize(CGMSG_CONTEXT& /*_Msg*/)			{}

	//! @brief �ı��Ǳ� �� ȣ��ȴ�.(OnInitialize()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnDestroying()							{}
	//! @brief �ı��� �� ȣ��ȴ�.(OnInitializing()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnDestroy()								{}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	//! @brief �ʱ�ȭ ������ �����Ѵ�. @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual	void				ProcessInitialize(CGMSG_CONTEXT& _Msg);
	//! @brief �ı� ������ �����Ѵ�.
	virtual	void				ProcessDestroy();

	//! @brief �ڽ� ����� �ʱ�ȭ ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessInitializing(CGMSG_CONTEXT& _Msg){ OnInitializing(_Msg);}
	//! @brief �ڽ� ����� �ʱ�ȭ ó���� ����� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessInitialize(CGMSG_CONTEXT& _Msg)	{ OnInitialize(_Msg);}
	//! @brief �ڽ� ����� �ı� ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessDestroying()					{ OnDestroying();}
	//! @brief �ڽ� ����� �ı� ó���� ����� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessDestroy()						{ OnDestroy();}
};
