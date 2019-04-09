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

 @class		NCGDispatchable
 @brief		ICGDispatchable을 구현한 클래스
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
#define	MAX_MEDIATOR	64

class NCGDispatchable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGDispatchable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~NCGDispatchable();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 메시지를 등록된 '대상 객체'들에게 전달한다. @param _pMSG 전달할 메시지 @return !0 메시지를 처리했다. @return 0 처리하지 못했다.
	virtual	int					NotifyMessage(CGMSG& _Msg);



// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 새로운 '대상 객체'가 붙기 직전 호출되는 함수. 이 함수에서 false를 리턴하면 붙이기가 거절된다. @param _pMessageable 붙일 '대상 객체' @return true 인증 @return false 거절
	virtual	bool				OnMessageableAttaching(ICGMessageable* /*_pMessageable*/)	{ return true;}
	//! @brief 새로운 '대상 객체'가 붙은 후 호출되는 함수. @param _pMessageable 붙은 '대상 객체'
	virtual	void				OnMessageableAttached(ICGMessageable* /*_pMessageable*/)	{}
	//! @brief 등록된 '대상 객체'가 떼기 직전 호출되는 함수. @param _pMessageable 떼어낼 '대상 객체'
	virtual	void				OnMessageableDetaching(ICGMessageable* /*_pMessageable*/)	{}
	//! @brief 등록된 '대상 객체'가 떼어진 후 호출되는 함수. @param _pMessageable 떼어진 '대상 객체'
	virtual	void				OnMessageableDetached(ICGMessageable* /*_pMessageable*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Attach/Detach
	virtual bool				ProcessAttach(_In_ ICGMessageable* _pMessageable) override	{	return ProcessAttach_MessageableBack(_pMessageable);}
	virtual int					ProcessDetach(_In_opt_ ICGMessageable* _pMessageable) override;
	virtual int					ProcessResetDispatchable() override;

	// 2) Process Attach Front/Back
			bool				ProcessAttach_MessageableFront(ICGMessageable* _pMessageable);
			bool				ProcessAttach_MessageableBack(ICGMessageable* _pMessageable);
private:
			LOCKABLE<CGD::static_vector<CGPTR<ICGMessageable>, MAX_MEDIATOR>>	m_arrayMessageable;
};

inline NCGDispatchable::~NCGDispatchable()
{
	LOCK_BEGIN(m_arrayMessageable)
	{
		// Check) 소멸될때 모든 Messageable을 비어 있어야 한다.
		CGASSERT_ERROR(m_arrayMessageable.empty());
	}
	LOCK_END
}


inline int NCGDispatchable::ProcessResetDispatchable()
{
	// Hold) 완료 될 때까지 Destroy되지 않게 Holding한다.
	CGPTR<NCGDispatchable>	pHold(this);

	// Declare) 
	CGD::static_vector<CGPTR<ICGMessageable>, MAX_MEDIATOR>	listMessageable;

	LOCK(m_arrayMessageable)
	{
		// - Swap
		listMessageable	 = m_arrayMessageable;

		// - OnMessageableDetaching
		for(auto& iter:listMessageable)
		{
			OnMessageableDetaching(iter);
		}

		m_arrayMessageable.clear();
	}

	// Declare)
	int	iCount	 = static_cast<int>(listMessageable.size());

	for(auto& iter:listMessageable)
	{
		// - OnMessageableDetached
		OnMessageableDetached(iter);

		// - Release한다.
		Release();
	}

	// Return)
	return	iCount;
}

inline bool NCGDispatchable::ProcessAttach_MessageableFront(ICGMessageable* _pMessageable)
{
	// Check) 
	RETURN_IF(_pMessageable==nullptr, false);

	LOCK(m_arrayMessageable)
	{
		// Check) 가질 수 있는 최대 Mediator를 넘어설 경우!
		CGASSERT_ERROR(m_arrayMessageable.size()<MAX_MEDIATOR);

		// Check) 이미 존재할 경우 그냥 끝낸다.
		RETURN_IF(std::find(m_arrayMessageable.begin(), m_arrayMessageable.end(), _pMessageable)!=m_arrayMessageable.end(), false);

		// Declare) 
		bool	bResult;

		// 1) OnRegistering
		bResult	 = OnMessageableAttaching(_pMessageable);

		// Check)
		RETURN_IF(bResult==false, false);

		// 2) 추가한다.
		m_arrayMessageable.push_front(_pMessageable);

		// 3) Reference Count를 증가시킨다.
		AddRef();
	}

	// 4) OnRegistered
	OnMessageableAttached(_pMessageable);

	// Return) 
	return	true;
}

inline bool NCGDispatchable::ProcessAttach_MessageableBack(ICGMessageable* _pMessageable)
{
	// Check) 
	RETURN_IF(_pMessageable==nullptr, false);

	LOCK(m_arrayMessageable)
	{
		// Check) 가질 수 있는 최대 Mediator를 넘어설 경우!
		CGASSERT_ERROR(m_arrayMessageable.size()<MAX_MEDIATOR);

		// Check) 이미 존재할 경우 그냥 끝낸다.
		RETURN_IF(std::find(m_arrayMessageable.begin(), m_arrayMessageable.end(), _pMessageable)!=m_arrayMessageable.end(), false);

		// Declare) 
		bool	bResult;

		// 1) OnRegistering
		bResult	 = OnMessageableAttaching(_pMessageable);

		// Check)
		RETURN_IF(bResult==false, false);

		// 2) 추가한다.
		m_arrayMessageable.push_back(_pMessageable);

		// 3) Reference Count를 증가시킨다.
		AddRef();
	}

	// 4) OnRegistered
	OnMessageableAttached(_pMessageable);

	// Return) 
	return	true;
}

inline int NCGDispatchable::ProcessDetach(_In_opt_ ICGMessageable* _pMessageable)
{
	// Check) 
	if(_pMessageable==nullptr)
	{
		// - 모두 다 제거한다.
		return	ResetDispatchable();
	}

	LOCK(m_arrayMessageable)
	{
		// 1) 먼저 찾는다.
		auto iter	 = std::find(m_arrayMessageable.begin(), m_arrayMessageable.end(), _pMessageable);

		// Check) 없을 경우 그냥 끝낸다.
		RETURN_IF(iter==m_arrayMessageable.end(), 0);

		// 2) OnRegistering
		OnMessageableDetaching(_pMessageable);

		// 3) 지운다.
		m_arrayMessageable.erase(iter);
	}
	
	// 4) OnRegistering
	OnMessageableDetached(_pMessageable);

	// 5) Release한다.
	Release();

	// Return) 
	return	true;
}

inline int NCGDispatchable::NotifyMessage(CGMSG& _Msg)
{
	// 1) Message를 NotifyMessage할 Mediator들의 리스트를 얻어낸다.
	// Declare) 
	CGD::static_vector<CGPTR<ICGMessageable>, MAX_MEDIATOR>	arrayMessageable;

	LOCK(m_arrayMessageable)
	{
		arrayMessageable	 = m_arrayMessageable;
	}

	// 2) Mediator들을 순회하며 ProcessMessage함수를 호출한다.
	for(auto& iter:arrayMessageable)
	{
		// - Process Message를 처리한다.
		auto	result	 = iter->RequestProcessMessage(_Msg);

		// Check) result가 0이 아니면 바로 Return한다.
		RETURN_IF(result>0, result);
	}
	
	// Return) 
	return 0;
}
