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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGFSM::CManager
//
// 1. CGFSM::CManager��?
//    Event�� ������ Transition Table�� ���� State���� �������ִ� Manager�̴�.
// 
// 2. ����
//    ũ�� State�� � State���� � Event������ � State�� �����ϴ°��� ������
//    ��� �ִ� Transition Table�� �����Ǿ� �ִ�.
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
