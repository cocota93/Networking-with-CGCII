//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Group Template Classes                           *
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

namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CNoManageDispatchable
 @brief		무관리 그룹에서 메시지 중계자 기능을 추가한 클래스
 @todo		
 @ref		CGServerGroup::CNoManage
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBERBASE=_TMEMBER>
class CNoManageDispatchable : 
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				CNoManage<_TMEMBER, _TMEMBERBASE>,		//     Group Base
	public						CGNet::IO::Messageable::NBase
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CNoManage<_TMEMBER, _TMEMBERBASE>						BASEGROUP;
	typedef	_TMEMBER												TMEMBER;
	typedef	_TMEMBERBASE											TMEMBERBASE;


// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			CNoManageDispatchable() : BASEGROUP()						{}
	virtual	~CNoManageDispatchable()									{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);
};

template <class _TMEMBER, class _TMEMBERBASE>
void CNoManageDispatchable<_TMEMBER, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) 먼저 Dispatchable에 Attach한다.
	_pMember->RegisterMessageable(this);

	// 2) OnMemberEntered
	try
	{
		OnMemberEntered(_pMember, _Msg);
	}
	catch(...)
	{
		// - Unreigster 
		_pMember->UnregisterMessageable(this);

		// Reraise) 
		throw;
	}
}

template <class _TMEMBER, class _TMEMBERBASE>
uintptr_t CNoManageDispatchable<_TMEMBER, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// Declare) 
	uintptr_t	valueReturn;

	// 1) OnMemberEntered
	try
	{
		valueReturn	 = OnMemberLeaving(_pMember);
	}
	catch(...)
	{
		// - Unregister한다.
		_pMember->UnregisterMessageable(this);

		// Reraise)
		throw;
	}

	// 2) Unregister한다.
	_pMember->UnregisterMessageable(this);

	// Return)
	return	valueReturn;
}


}
