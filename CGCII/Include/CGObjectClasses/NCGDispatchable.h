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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		NCGDispatchable
 @brief		ICGDispatchable�� ������ Ŭ����
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
	//! @brief �޽����� ��ϵ� '��� ��ü'�鿡�� �����Ѵ�. @param _pMSG ������ �޽��� @return !0 �޽����� ó���ߴ�. @return 0 ó������ ���ߴ�.
	virtual	int					NotifyMessage(CGMSG& _Msg);



// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief ���ο� '��� ��ü'�� �ٱ� ���� ȣ��Ǵ� �Լ�. �� �Լ����� false�� �����ϸ� ���̱Ⱑ �����ȴ�. @param _pMessageable ���� '��� ��ü' @return true ���� @return false ����
	virtual	bool				OnMessageableAttaching(ICGMessageable* /*_pMessageable*/)	{ return true;}
	//! @brief ���ο� '��� ��ü'�� ���� �� ȣ��Ǵ� �Լ�. @param _pMessageable ���� '��� ��ü'
	virtual	void				OnMessageableAttached(ICGMessageable* /*_pMessageable*/)	{}
	//! @brief ��ϵ� '��� ��ü'�� ���� ���� ȣ��Ǵ� �Լ�. @param _pMessageable ��� '��� ��ü'
	virtual	void				OnMessageableDetaching(ICGMessageable* /*_pMessageable*/)	{}
	//! @brief ��ϵ� '��� ��ü'�� ������ �� ȣ��Ǵ� �Լ�. @param _pMessageable ������ '��� ��ü'
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
		// Check) �Ҹ�ɶ� ��� Messageable�� ��� �־�� �Ѵ�.
		CGASSERT_ERROR(m_arrayMessageable.empty());
	}
	LOCK_END
}


inline int NCGDispatchable::ProcessResetDispatchable()
{
	// Hold) �Ϸ� �� ������ Destroy���� �ʰ� Holding�Ѵ�.
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

		// - Release�Ѵ�.
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
		// Check) ���� �� �ִ� �ִ� Mediator�� �Ѿ ���!
		CGASSERT_ERROR(m_arrayMessageable.size()<MAX_MEDIATOR);

		// Check) �̹� ������ ��� �׳� ������.
		RETURN_IF(std::find(m_arrayMessageable.begin(), m_arrayMessageable.end(), _pMessageable)!=m_arrayMessageable.end(), false);

		// Declare) 
		bool	bResult;

		// 1) OnRegistering
		bResult	 = OnMessageableAttaching(_pMessageable);

		// Check)
		RETURN_IF(bResult==false, false);

		// 2) �߰��Ѵ�.
		m_arrayMessageable.push_front(_pMessageable);

		// 3) Reference Count�� ������Ų��.
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
		// Check) ���� �� �ִ� �ִ� Mediator�� �Ѿ ���!
		CGASSERT_ERROR(m_arrayMessageable.size()<MAX_MEDIATOR);

		// Check) �̹� ������ ��� �׳� ������.
		RETURN_IF(std::find(m_arrayMessageable.begin(), m_arrayMessageable.end(), _pMessageable)!=m_arrayMessageable.end(), false);

		// Declare) 
		bool	bResult;

		// 1) OnRegistering
		bResult	 = OnMessageableAttaching(_pMessageable);

		// Check)
		RETURN_IF(bResult==false, false);

		// 2) �߰��Ѵ�.
		m_arrayMessageable.push_back(_pMessageable);

		// 3) Reference Count�� ������Ų��.
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
		// - ��� �� �����Ѵ�.
		return	ResetDispatchable();
	}

	LOCK(m_arrayMessageable)
	{
		// 1) ���� ã�´�.
		auto iter	 = std::find(m_arrayMessageable.begin(), m_arrayMessageable.end(), _pMessageable);

		// Check) ���� ��� �׳� ������.
		RETURN_IF(iter==m_arrayMessageable.end(), 0);

		// 2) OnRegistering
		OnMessageableDetaching(_pMessageable);

		// 3) �����.
		m_arrayMessageable.erase(iter);
	}
	
	// 4) OnRegistering
	OnMessageableDetached(_pMessageable);

	// 5) Release�Ѵ�.
	Release();

	// Return) 
	return	true;
}

inline int NCGDispatchable::NotifyMessage(CGMSG& _Msg)
{
	// 1) Message�� NotifyMessage�� Mediator���� ����Ʈ�� ����.
	// Declare) 
	CGD::static_vector<CGPTR<ICGMessageable>, MAX_MEDIATOR>	arrayMessageable;

	LOCK(m_arrayMessageable)
	{
		arrayMessageable	 = m_arrayMessageable;
	}

	// 2) Mediator���� ��ȸ�ϸ� ProcessMessage�Լ��� ȣ���Ѵ�.
	for(auto& iter:arrayMessageable)
	{
		// - Process Message�� ó���Ѵ�.
		auto	result	 = iter->RequestProcessMessage(_Msg);

		// Check) result�� 0�� �ƴϸ� �ٷ� Return�Ѵ�.
		RETURN_IF(result>0, result);
	}
	
	// Return) 
	return 0;
}
