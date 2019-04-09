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
// CGState::CManager
//
// 1. CGState::CManager란?
//    등록된 State로 진이를 
// 
// 2. 구성
//    크게 State와 어떤 State에서 어떤 Event받으면 어떤 State로 전이하는가의 정보를
//    들고 있는 Transition Table로 구성되어 있다.
// 
//
//-----------------------------------------------------------------------------
template <class _TSTATE>
class ICGStateTable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (I) Reference Count    
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE				TSTATE;
	typedef	typename _TSTATE::TSTATE_ID	TSTATE_ID;


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) State를 조작하는 함수.
	virtual	bool				RegisterState(_In_ TSTATE* p_pState, bool p_bIsInitial=false) PURE;
	virtual	CGPTR<TSTATE>		UnregisterState(_In_ const TSTATE_ID& p_rStateID) PURE;
	virtual	CGPTR<TSTATE>		FindState(_In_ const TSTATE_ID& p_rStateID) PURE;
	virtual	CGPTR<TSTATE>		GetInitialState() PURE;
};
