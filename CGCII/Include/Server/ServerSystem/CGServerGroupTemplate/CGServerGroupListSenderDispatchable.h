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

 @class		CListSenderDispatchable
 @brief		링크드 리스트형 배열과 전체 전송 기능 그리고 메시지 중계자 기능을 모두 추가한 클래스이다.
 @todo		
 @ref		CGServerGroup::CListSender
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA=int, class _TMEMBERBASE=_TMEMBER>
class CListSenderDispatchable : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CListSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>,// (@) Group List
	public						CGNet::IO::Messageable::NBase
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CListSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>		BASEGROUP;
	typedef	_TMEMBER												TMEMBER;
	typedef	_TMEMBERBASE											TMEMBERBASE;
	typedef	_TMEMBER_DATA											TMEMBER_DATA;
	typedef typename BASEGROUP::ITERATOR							ITERATOR;
	typedef typename BASEGROUP::CONST_ITERATOR						CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CListSenderDispatchable(int _nMaxMember=INT_MAX) : BASEGROUP(_nMaxMember) {}
	virtual	~CListSenderDispatchable()									{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);
};

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CListSenderDispatchable<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
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

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t CListSenderDispatchable<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
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