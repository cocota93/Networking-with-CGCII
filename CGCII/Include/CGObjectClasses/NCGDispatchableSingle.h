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

 @class		NCGDispatchableSingle
 @brief		���� ��� ��ü���� ������ Dispatchable ��ü
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
	//! @brief �޽����� ��ϵ� '��� ��ü'�鿡�� �����Ѵ�. @param _pMSG ������ �޽��� @return !0 �޽����� ó���ߴ�. @return 0 ó������ ���ߴ�.
	virtual	int					NotifyMessage(CGMSG& _Msg);

	//! @brief ��ϵ� '��� ��ü'�� ��´�.
			CGPTR<ICGMessageable> GetMessageable() const					{	return m_pMessageable;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief ���ο� '��� ��ü'�� �ٱ� ���� ȣ��Ǵ� �Լ�. �� �Լ����� false�� �����ϸ� ���̱Ⱑ �����ȴ�. @param _pMessageable ���� '��� ��ü' @return true ���� @return false ����
	virtual	bool				OnMessageableRegistering(ICGMessageable* /*_pMessageable*/)		{ return true;}
	//! @brief ���ο� '��� ��ü'�� ���� �� ȣ��Ǵ� �Լ�. @param _pMessageable ���� '��� ��ü'
	virtual	void				OnMessageableRegistered(ICGMessageable* /*_pMessageable*/)		{}
	//! @brief ��ϵ� '��� ��ü'�� ���� ���� ȣ��Ǵ� �Լ�. @param _pMessageable ��� '��� ��ü'
	virtual	void				OnMessageableUnregistering(ICGMessageable* /*_pMessageable*/)	{}
	//! @brief ��ϵ� '��� ��ü'�� ������ �� ȣ��Ǵ� �Լ�. @param _pMessageable ������ '��� ��ü'
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
		// Check) �Ҹ�ɶ� ��� m_pMessageable�� ��� �־�� �Ѵ�.
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

		// 1) OnMessageableRegistering ȣ��
		bResult	 = OnMessageableRegistering(_pMessageable);

		// Check) 
		RETURN_IF(bResult==false, false);

		// 2) Pre
		pMessageablePre	 = m_pMessageable;

		// 3) OnMessageableUnregistering ȣ��
		OnMessageableUnregistering(pMessageablePre);

		// 4) Set Messageable
		m_pMessageable	 = _pMessageable; 
	}

	// 5) OnMessageableUnregistered ȣ��
	if(pMessageablePre.exist())
	{
		OnMessageableUnregistered(pMessageablePre);
	}

	// 6) OnMessageableRegistered ȣ��
	OnMessageableRegistered(_pMessageable);

	// Return) 
	return true;
}

inline int NCGDispatchableSingle::ProcessDetach(_In_opt_ ICGMessageable* _pMessageable)
{
	// Check) 
	if(_pMessageable==nullptr)
	{
		// - ��� �� �����Ѵ�.
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

		// 1) ���� �ӽ÷� ����
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
	// 1) Mediator�� ��´�.
	CGPTR<ICGMessageable> pMessageable;

	// 2) ����
	LOCK(m_pMessageable)
	{
		pMessageable	 = m_pMessageable;
	}

	// Check) pMessageable�� nullptr�̸� �׳� ������.
	RETURN_IF(pMessageable.empty(), 0);

	// 3) Message�� NotifyMessage�Ѵ�.
	return pMessageable->RequestProcessMessage(_Msg);
}
