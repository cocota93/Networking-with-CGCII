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

 @class		NCGDispatchableStatic
 @brief		
 @todo		
 @ref		
 @details	\n

*/
//
// CCGDispatcherStatic
//
// 1. CCGDispatcherStatic��...
//    1) Message�� Messageable�� �����ϴ� Class�� Messageable�� Static���� �����.
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
	//! @brief �޽����� ��ϵ� '��� ��ü'�鿡�� �����Ѵ�. @param _pMSG ������ �޽��� @return !0 �޽����� ó���ߴ�. @return 0 ó������ ���ߴ�.
	virtual	int					NotifyMessage(CGMSG& _Msg) override;

	//! @brief ��ϵ� '��� ��ü'�� ��´�.
	static	CGPTR<ICGMessageable> GetMessageable()							{	 return GetMessageableStatic();}

	//! @brief ��� ��ϵ� '��� ��ü'���� �����Ѵ�. (���� �Լ�)
	static	CGPTR<ICGMessageable> ResetDispatchableStatic();
	//! @brief �޽����� ������ '��� ��ü'�� ����Ѵ�.(���� �Լ�) @param _pMessageable ����� '��� ��ü' @return true ���� @return false ����(�Ϲ������� �̹� ��ϵǾ� �ִ� ���)
	static	bool				RegisterMessageableStatic(ICGMessageable* _pMessageable);
	//! @brief ��ϵ� '��� ��ü'�� ��������.(���� �Լ�) @param _pMessageable ������ '��� ��ü' @return true ���� @return false ����(�Ϲ������� ��ϵǾ��� ���� ���� ���)
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

	// 1) Static Messageable�� ��´�.
	LOCKABLE<CGPTR<ICGMessageable>>&	rMessageable	 = GetMessageableStatic();

	LOCK(rMessageable)
	{
		// Check) 
		RETURN_IF(rMessageable.empty(), pMessageable); 

		// 1) ���� �ӽ÷� ����
		pMessageable	 = rMessageable;

		// 3) Reset
		rMessageable.reset();
	}

	// Return)
	return	pMessageable;
}

inline bool NCGDispatchableStatic::RegisterMessageableStatic(ICGMessageable* _pMessageable)	
{
	// 1) �ϴ� Unregister
	UnregisterMessageableStatic(GetMessageableStatic());

	// 2) Messagable��...
	auto&	rMessageable	 = GetMessageableStatic();

	LOCK(rMessageable)
	{
		// Check) 
		RETURN_IF(rMessageable==_pMessageable, false); 

		// 4) Messageable�Ѵ�~
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
		// - ��� �� �����Ѵ�.
		return	ResetDispatchableStatic().exist() ? 1:0;
	}

	// 1) Messageable Static�� ��´�.
	LOCKABLE<CGPTR<ICGMessageable>>&	rMessageable	 = GetMessageableStatic();

	LOCK(rMessageable)
	{
		// Check) �����Ϸ��� Messageable�� �ƴϸ� �׳� ������.
		RETURN_IF(rMessageable!=_pMessageable, 0);
	
		// 1) Reset�Ѵ�.
		rMessageable.reset(); 
	}

	// Return) 
	return 1;
}

inline int NCGDispatchableStatic::NotifyMessage(CGMSG& _Msg)
{
	// 1) Messageable Static�� ��´�.
	LOCKABLE<CGPTR<ICGMessageable>>&	rMessageable	 = GetMessageableStatic();

	// Declare) 
	CGPTR<ICGMessageable> pMessageable;

	// 2) ����
	LOCK(rMessageable)
	{
		// Check) rMessageable�� nullptr�̸� ������.
		RETURN_IF(rMessageable.empty(), 0);

		// - ���� ����.
		pMessageable	 = rMessageable;
	}

	// 3) Message�� NotifyMessage�Ѵ�.
	return pMessageable->RequestProcessMessage(_Msg);
}


