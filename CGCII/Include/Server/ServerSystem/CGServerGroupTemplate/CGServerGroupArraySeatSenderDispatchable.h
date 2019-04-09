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

 @class		CArraySeatSenderDispatchable
 @brief		좌석식 배열형 멤버 관리와 전체 전송 기능 그리고 메시지 중계자 기능을 모두 상속한 클래스이다.
 @todo		
 @ref		CGServerGroup::CArraySeat, CGServerGroup::CArraySeatSender
 @details	\n
 좌석식 배열형 멤버 관리기능에 메시지 중계자 기능까지 상속한 객체이다.
 멤버가 Dispatchable을 상속받을 경우 자동으로 Register와 Unregister를 수행해준다.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA=int, class _TMEMBERBASE=_TMEMBER>
class CArraySeatSenderDispatchable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CArraySeatSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>,// (@) Group
	public						CGNet::IO::Messageable::NBase
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CArraySeatSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>	BASEGROUP;
	typedef	_TMEMBER												TMEMBER;
	typedef	_TMEMBERBASE											TMEMBERBASE;
	typedef	_TMEMBER_DATA											TMEMBER_DATA;
	typedef	typename BASEGROUP::TCONTAINER							TCONTAINER;
	typedef typename BASEGROUP::ITERATOR							ITERATOR;
	typedef typename BASEGROUP::CONST_ITERATOR						CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CArraySeatSenderDispatchable(int _nMaxMember = 256) : BASEGROUP(_nMaxMember)	{}
	virtual	~CArraySeatSenderDispatchable()	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);
};

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeatSenderDispatchable<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
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
uintptr_t CArraySeatSenderDispatchable<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
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