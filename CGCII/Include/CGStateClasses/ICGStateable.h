//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               State Classes                               *
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
//
// CGFSM::CManager
//
// 1. CGFSM::CManager란?
//     각 Member를 Array형태로 관리하는 Group System이다.
// 
//
//-----------------------------------------------------------------------------
template <class _TSTATE>
class ICGStateable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE				TSTATE;


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) State를 조작하는 함수.
	virtual	CGPTR<TSTATE>		GetState() PURE;
	virtual	bool				SetState(_In_ TSTATE* p_pState=nullptr) PURE;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
			LOCKABLE<>			m_csState;

};
