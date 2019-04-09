//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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

 @class		NCGDispatchableStatic
 @brief		
 @todo		
 @ref		
 @details	\n

*/
//
// CCGDispatcherStatic
//
// 1. CCGDispatcherStatic은...
//    1) Message를 Messageable에 전달하는 Class로 Messageable가 Static으로 선언됨.
//
//
//-----------------------------------------------------------------------------
class NCGDispatchableStatic :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGDispatchable
{
// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief 메시지를 등록된 '대상 객체'들에게 전달한다. @param _pMSG 전달할 메시지 @return !0 메시지를 처리했다. @return 0 처리하지 못했다.
	virtual	int					NotifyMessage(CGMSG& _Msg) override;

	//! @brief 등록된 '대상 객체'를 얻는다.
	static	CGPTR<ICGMessageable> GetMessageable()							{	 return GetMessageableStatic();}

	//! @brief 모든 등록된 '대상 객체'들을 해제한다. (정적 함수)
	static	CGPTR<ICGMessageable> ResetDispatchableStatic();
	//! @brief 메시지를 전달할 '대상 객체'를 등록한다.(정적 함수) @param _pMessageable 등록할 '대상 객체' @return true 성공 @return false 실패(일반적으로 이미 등록되어 있는 경우)
	static	bool				RegisterMessageableStatic(ICGMessageable* _pMessageable);
	//! @brief 등록된 '대상 객체'를 해제낸다.(정적 함수) @param _pMessageable 해제할 '대상 객체' @return true 성공 @return false 실패(일반적으로 등록되어져 있지 않은 경우)
	static	int					UnregisterMessageableStatic(ICGMessageable* _pMessageable=nullptr);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	static	LOCKABLE<CGPTR<ICGMessageable>>&	GetMessageableStatic()		{	static LOCKABLE<CGPTR<ICGMessageable>> pMessageable; return pMessageable;}

public:
	virtual	bool				ProcessAttach(_In_ ICGMessageable* _pMessageable) override;
	virtual	int					ProcessDetach(_In_opt_ ICGMessageable* _pMessageable=nullptr) override;
	virtual	int					ProcessResetDispatchable() override;
};

inline bool NCGDispatchableStatic::ProcessAttach(_In_ ICGMessageable* _pMessageable)
{
	return RegisterMessageableStatic(_pMessageable);
}

inline int NCGDispatchableStatic::ProcessDetach(_In_opt_ ICGMessageable* _pMessageable)
{
	return UnregisterMessageableStatic(_pMessageable);
}

inline int NCGDispatchableStatic::ProcessResetDispatchable()
{
	return ResetDispatchableStatic().exist() ? 1:0;
}


inline CGPTR<ICGMessageable> NCGDispatchableStatic::ResetDispatchableStatic()
{
	// Declare) 
	CGPTR<ICGMessageable> pMessageable;

	// 1) Static Messageable를 얻는다.
	LOCKABLE<CGPTR<ICGMessageable>>&	rMessageable	 = GetMessageableStatic();

	LOCK(rMessageable)
	{
		// Check) 
		RETURN_IF(rMessageable.empty(), pMessageable); 

		// 1) 값을 임시로 복사
		pMessageable	 = rMessageable;

		// 3) Reset
		rMessageable.reset();
	}

	// Return)
	return	pMessageable;
}

inline bool NCGDispatchableStatic::RegisterMessageableStatic(ICGMessageable* _pMessageable)	
{
	// 1) 일단 Unregister
	UnregisterMessageableStatic(GetMessageableStatic());

	// 2) Messagable을...
	auto&	rMessageable	 = GetMessageableStatic();

	LOCK(rMessageable)
	{
		// Check) 
		RETURN_IF(rMessageable==_pMessageable, false); 

		// 4) Messageable한다~
		rMessageable	 = _pMessageable;
	}

	// Return) 
	return true;
}

inline int NCGDispatchableStatic::UnregisterMessageableStatic(ICGMessageable* _pMessageable)
{
	// Check) 
	if(_pMessageable==nullptr)
	{
		// - 모두 다 제거한다.
		return	ResetDispatchableStatic().exist() ? 1:0;
	}

	// 1) Messageable Static을 얻는다.
	LOCKABLE<CGPTR<ICGMessageable>>&	rMessageable	 = GetMessageableStatic();

	LOCK(rMessageable)
	{
		// Check) 제거하려는 Messageable이 아니면 그냥 끝낸다.
		RETURN_IF(rMessageable!=_pMessageable, 0);
	
		// 1) Reset한다.
		rMessageable.reset(); 
	}

	// Return) 
	return 1;
}

inline int NCGDispatchableStatic::NotifyMessage(CGMSG& _Msg)
{
	// 1) Messageable Static을 얻는다.
	LOCKABLE<CGPTR<ICGMessageable>>&	rMessageable	 = GetMessageableStatic();

	// Declare) 
	CGPTR<ICGMessageable> pMessageable;

	// 2) 복사
	LOCK(rMessageable)
	{
		// Check) rMessageable이 nullptr이면 끝낸다.
		RETURN_IF(rMessageable.empty(), 0);

		// - 값을 복사.
		pMessageable	 = rMessageable;
	}

	// 3) Message를 NotifyMessage한다.
	return pMessageable->RequestProcessMessage(_Msg);
}


