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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		ICGDispatchable
 @brief		ICGReferenceable를 가진 대상 객체를 등록해 대상 객체들에게 메시지를 전달해 줄수 있는 인터페이스 클래스이다.
 @todo		
 @ref		
 @details	\n
 ICGReferenceable 인터페이스 클래스를 상속받은 객체는 등록해 NotifyMessage()함수를 호출하면 이 등록된 대상 객체에게 해당 메시지를 전달해 주는 인터페이스 클래스이다.

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
	//! @brief 메시지를 등록된 대상 객체에 전달한다. @param _Msg 전달할 '메시지' @return !0 처리됨 @return 0 처리되지 않음
	virtual	int					NotifyMessage(CGMSG& _Msg) PURE;

	// 2) Register/Unregister
	//! @brief 메시지를 전달할 '대상 객체'를 등록한다. @param _pMessageable 등록할 '대상 객체' @return true 성공 @return false 실패(일반적으로 이미 등록되어 있는 경우)
			bool				RegisterMessageable(ICGMessageable* _pMessageable)		{	return ProcessAttach(_pMessageable);}
	//! @brief 등록된 '대상 객체'를 해제낸다. @param _pMessageable 해제할 '대상 객체' @return true 성공 @return false 실패(일반적으로 등록되어져 있지 않은 경우)
			bool				UnregisterMessageable(ICGMessageable* _pMessageable)	{	return ProcessDetach(_pMessageable)!=0;}
	//! @brief 등록된 '대상 객체'를 모두 해제하고 Dispatchable객체를 초기화한다. @return 등록해제된 '대상 객체' 수
	virtual	int					ResetDispatchable()										{	return ProcessResetDispatchable();}

public:
	//! @brief _Object 객체를 등록하는 과정을 정의한다. @param _Object 등록할 '대상 객체' @return true 성공 @return false 실패(일반적으로 이미 붙어 있는 경우)
	virtual bool				ProcessAttach(_In_ ICGMessageable* _Object) PURE;
	//! @brief _Object 등록된 '대상 객체'를 해제하는 과정을 정의한다. @param _Object 떼어낼 '대상 객체' @return true 성공 @return false 실패(일반적으로 등록되어 있지 않는 경우)
	virtual int					ProcessDetach(_In_opt_ ICGMessageable* _Object) PURE;
	//! @brief 등록된 '대상 객체'를 모두 해제하고 Dispatchable객체를 초기화한다. @return 등록해제된 '대상 객체' 수
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


