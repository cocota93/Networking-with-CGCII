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

 @class		CCountDispatchable
 @brief		������� �����ϴ� ��ɿ� �޽��� �߰��� ����� �߰��� Ŭ�����̴�.
 @todo		
 @ref		CGServerGroup::CCount
 @details	\n
 CGServerGroup::CCount�� Dispatchable ����� �߰��� ��ü�̴�.
 ����� Dispatchable�� ��ӹ��� ��� �ڵ����� Register�� Unregister�� �������ش�.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBERBASE=_TMEMBER>
class CCountDispatchable : 
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	public						CCount<_TMEMBER, _TMEMBERBASE>,			//     Group Base
	public						CGNet::IO::Messageable::NBase
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CCount<_TMEMBER, _TMEMBERBASE>							BASEGROUP;
	typedef	_TMEMBER												TMEMBER;
	typedef	_TMEMBERBASE											TMEMBERBASE;


// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			CCountDispatchable(int _nMaxMember=INT_MAX) : BASEGROUP(_nMaxMember)	{}
	virtual	~CCountDispatchable()										{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);
};

template <class _TMEMBER, class _TMEMBERBASE>
void CCountDispatchable<_TMEMBER, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
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

template <class _TMEMBER, class _TMEMBERBASE>
uintptr_t CCountDispatchable<_TMEMBER, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
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
