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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CArray
 @brief		�¼��� �迭�� ��� ������ �޽��� �߰��� ����� ��� ����� Ŭ�����̴�.
 @todo		
 @ref		CGServerGroup::CArraySeat
 @details	\n
 CArraySeat�� Dispatchable ����� �߰��� ��ü�̴�.
 Member�� Dispatchable�� ��ӹ��� ��� �ڵ����� Register�� Unregister�� �������ش�.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA=int, class _TMEMBERBASE=_TMEMBER>
class CArraySeatDispatchable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>,	//     Group Base
	public						CGNet::IO::Messageable::NBase
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>		BASEGROUP;
	typedef	_TMEMBER												TMEMBER;
	typedef	_TMEMBERBASE											TMEMBERBASE;
	typedef	_TMEMBER_DATA											TMEMBER_DATA;
	typedef	typename BASEGROUP::TMEMBER_SET							TMEMBER_SET;
	typedef	typename BASEGROUP::TCONTAINER							TCONTAINER;
	typedef typename BASEGROUP::ITERATOR							ITERATOR;
	typedef typename BASEGROUP::CONST_ITERATOR						CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			CArraySeatDispatchable(int _nMaxMember=256) : BASEGROUP(_nMaxMember)	{}
	virtual	~CArraySeatDispatchable()	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);
};

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeatDispatchable<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) ���� Dispatchable�� Attach�Ѵ�.
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
uintptr_t CArraySeatDispatchable<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
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
		// - Unregister�Ѵ�.
		_pMember->UnregisterMessageable(this);

		// Reraise)
		throw;
	}

	// 2) Unregister�Ѵ�.
	_pMember->UnregisterMessageable(this);

	// Return)
	return	valueReturn;
}

}
