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

 @class		ICGDispatchable
 @brief		ICGReferenceable�� ���� ��� ��ü�� ����� ��� ��ü�鿡�� �޽����� ������ �ټ� �ִ� �������̽� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ICGReferenceable �������̽� Ŭ������ ��ӹ��� ��ü�� ����� NotifyMessage()�Լ��� ȣ���ϸ� �� ��ϵ� ��� ��ü���� �ش� �޽����� ������ �ִ� �������̽� Ŭ�����̴�.

*/
//-----------------------------------------------------------------------------
#define	MAX_MEDIATOR	64

class ICGDispatchable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGAttachable<ICGMessageable>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGDispatchable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief �޽����� ��ϵ� ��� ��ü�� �����Ѵ�. @param _Msg ������ '�޽���' @return !0 ó���� @return 0 ó������ ����
	virtual	int					NotifyMessage(CGMSG& _Msg) PURE;

	// 2) Register/Unregister
	//! @brief �޽����� ������ '��� ��ü'�� ����Ѵ�. @param _pMessageable ����� '��� ��ü' @return true ���� @return false ����(�Ϲ������� �̹� ��ϵǾ� �ִ� ���)
			bool				RegisterMessageable(ICGMessageable* _pMessageable)		{	return ProcessAttach(_pMessageable);}
	//! @brief ��ϵ� '��� ��ü'�� ��������. @param _pMessageable ������ '��� ��ü' @return true ���� @return false ����(�Ϲ������� ��ϵǾ��� ���� ���� ���)
			bool				UnregisterMessageable(ICGMessageable* _pMessageable)	{	return ProcessDetach(_pMessageable)!=0;}
	//! @brief ��ϵ� '��� ��ü'�� ��� �����ϰ� Dispatchable��ü�� �ʱ�ȭ�Ѵ�. @return ��������� '��� ��ü' ��
	virtual	int					ResetDispatchable()										{	return ProcessResetDispatchable();}

public:
	//! @brief _Object ��ü�� ����ϴ� ������ �����Ѵ�. @param _Object ����� '��� ��ü' @return true ���� @return false ����(�Ϲ������� �̹� �پ� �ִ� ���)
	virtual bool				ProcessAttach(_In_ ICGMessageable* _Object) PURE;
	//! @brief _Object ��ϵ� '��� ��ü'�� �����ϴ� ������ �����Ѵ�. @param _Object ��� '��� ��ü' @return true ���� @return false ����(�Ϲ������� ��ϵǾ� ���� �ʴ� ���)
	virtual int					ProcessDetach(_In_opt_ ICGMessageable* _Object) PURE;
	//! @brief ��ϵ� '��� ��ü'�� ��� �����ϰ� Dispatchable��ü�� �ʱ�ȭ�Ѵ�. @return ��������� '��� ��ü' ��
	virtual int					ProcessResetDispatchable() PURE;
};

// Definitions)
#define	NOTIFY_MESSAGE(msg)					\
{											\
	auto result=NotifyMessage(msg);			\
											\
	if(result!=0)							\
	return result;							\
}

#define	NOTIFY_MESSAGE_SOURCE(msg, source)	\
{											\
	msg.pSource	 = source;					\
	auto result=NotifyMessage(msg);			\
											\
	if(result!=0)							\
	return result;							\
}


