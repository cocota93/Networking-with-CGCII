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
//    Event를 받으면 Transition Table에 따라 State들을 변경해주는 Manager이다.
// 
// 2. 구성
//    크게 State와 어떤 State에서 어떤 Event받으면 어떤 State로 전이하는가의 정보를
//    들고 있는 Transition Table로 구성되어 있다.
// 
//
//-----------------------------------------------------------------------------
namespace CGFSM
{

template <class _TSTATE, class _TEVENT=int>
class CControl: 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						CGFSM::NControl<_TSTATE, _TEVENT>,		// (@) FSM Control
	public						CGStateable::NControl<_TSTATE>,			// (@) State Control
	public						CCGStateable<_TSTATE>					// (@) Statable
{
};


}
