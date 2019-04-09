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

 @class		NCGDispatchableSingle
 @brief		단일 대상 객체만을 가지는 Dispatchable 객체
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class NCGDispatchableSingle : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGDispatchable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NCGDispatchableSingle();
	virtual	~NCGDispatchableSingle();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 메시지를 등록된 '대상 객체'들에게 전달한다. @param _pMSG 전달할 메시지 @return !0 메시지를 처리했다. @return 0 처리하지 못했다.
	virtual	int					NotifyMessage(CGMSG& _Msg);

	//! @brief 등록된 '대상 객체'를 얻는다.
			CGPTR<ICGMessageable> GetMessageable() const					{	return m_pMessageable;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 새로운 '대상 객체'가 붙기 직전 호출되는 함수. 이 함수에서 false를 리턴하면 붙이기가 거절된다. @param _pMessageable 붙일 '대상 객체' @return true 인증 @return false 거절
	virtual	bool				OnMessageableRegistering(ICGMessageable* /*_pMessageable*/)		{ return true;}
	//! @brief 새로운 '대상 객체'가 붙은 후 호출되는 함수. @param _pMessageable 붙은 '대상 객체'
	virtual	void				OnMessageableRegistered(ICGMessageable* /*_pMessageable*/)		{}
	//! @brief 등록된 '대상 객체'가 떼기 직전 호출되는 함수. @param _pMessageable 떼어낼 '대상 객체'
	virtual	void				OnMessageableUnregistering(ICGMessageable* /*_pMessageable*/)	{}
	//! @brief 등록된 '대상 객체'가 떼어진 후 호출되는 함수. @param _pMessageable 떼어진 '대상 객체'
	virtual	void				OnMessageableUnregistered(ICGMessageable* /*_pMessageable*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			LOCKABLE<CGPTR<ICGMessageable>>	m_pMessageable;
public:
	virtual	bool				ProcessAttach(_In_ ICGMessageable* _pMessageable) override;
	virtual	int					ProcessDetach(_In_opt_ ICGMessageable* _pMessageable) override;
	virtual int					ProcessResetDispatchable() override;
};

inline NCGDispatchableSingle::NCGDispatchableSingle()
{
}

inline NCGDispatchableSingle::~NCGDispatchableSingle()
{
	LOCK_BEGIN(m_pMessageable)
	{
		// Check) 소멸될때 모든 m_pMessageable는 비어 있어야 한다.
		CGASSERT_ERROR(m_pMessageable.empty());
	}
	LOCK_END
}

inline bool NCGDispatchableSingle::ProcessAttach(_In_ ICGMessageable* _pMessageable)
{
	// Check) 
	CGASSERT_ERROR(_pMessageable!=nullptr);

	// Declare) 
	CGPTR<ICGMessageable>	pMessageablePre;

	LOCK(m_pMessageable)
	{
		// Check) 
		RETURN_IF(m_pMessageable==_pMessageable, false); 

		// Declare) 
		bool	bResult;

		// 1) OnMessageableRegistering 호출
		bResult	 = OnMessageableRegistering(_pMessageable);

		// Check) 
		RETURN_IF(bResult==false, false);

		// 2) Pre
		pMessageablePre	 = m_pMessageable;

		// 3) OnMessageableUnregistering 호출
		OnMessageableUnregistering(pMessageablePre);

		// 4) Set Messageable
		m_pMessageable	 = _pMessageable; 
	}

	// 5) OnMessageableUnregistered 호출
	if(pMessageablePre.exist())
	{
		OnMessageableUnregistered(pMessageablePre);
	}

	// 6) OnMessageableRegistered 호출
	OnMessageableRegistered(_pMessageable);

	// Return) 
	return true;
}

inline int NCGDispatchableSingle::ProcessDetach(_In_opt_ ICGMessageable* _pMessageable)
{
	// Check) 
	if(_pMessageable==nullptr)
	{
		// - 모두 다 제거한다.
		return	ResetDispatchable();
	}
	
	LOCK(m_pMessageable)
	{
		// Check) 
		RETURN_IF(m_pMessageable!=_pMessageable, 0); 

		// 1) OnRegistering
		OnMessageableUnregistering(_pMessageable);

		// 2) Reset
		m_pMessageable.reset(); 
	}
	
	// 3) OnRegistering
	OnMessageableUnregistered(_pMessageable);

	// Return) 
	return true;
}

inline int NCGDispatchableSingle::ProcessResetDispatchable()
{
	// Declare) 
	CGPTR<ICGMessageable> pMessageable;

	LOCK(m_pMessageable)
	{
		// Check) 
		RETURN_IF(m_pMessageable.empty(), 0); 

		// 1) 값을 임시로 복사
		pMessageable	 = m_pMessageable;

		// 2) OnRegistering
		OnMessageableUnregistering(pMessageable);

		// 3) Reset
		m_pMessageable.reset();
	}

	// 4) OnRegistering
	OnMessageableUnregistered(pMessageable);

	// Return)
	return	1;
}


inline int NCGDispatchableSingle::NotifyMessage(CGMSG& _Msg)
{
	// 1) Mediator를 얻는다.
	CGPTR<ICGMessageable> pMessageable;

	// 2) 복사
	LOCK(m_pMessageable)
	{
		pMessageable	 = m_pMessageable;
	}

	// Check) pMessageable이 nullptr이면 그냥 끝낸다.
	RETURN_IF(pMessageable.empty(), 0);

	// 3) Message를 NotifyMessage한다.
	return pMessageable->RequestProcessMessage(_Msg);
}
