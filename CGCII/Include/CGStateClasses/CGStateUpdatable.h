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
// CGFSM::CStateProcess<TSTATE, TEVENT>
//
// 1. CGFSM::CStateProcess<TSTATE, TEVENT>��!
//    1) Grouble ��ü  ���� ���� ��� �����ϴ� ���� Group class�̴�.
//       �� Group Class�� �� Interface Class�� �ش��ϴ� ������ ����� ���� �� 
//       �����Ͽ� ����Ͽ��� �Ѵ�.
//
// 2. CGFSM::CStateProcess<TSTATE, TEVENT>�� �ٽ�! Function�� ��� ����.
//    1) Process()
//       Group���� Member ��ü�� ������ �Լ��̴�. �� �Լ��� abstract�Լ���
//      ��ӹ��� Group�� �ݵ�� ������ �� �־�� �Ѵ�.
//      �� �Լ��� virtual�� ������ ������ �� Group���� �ٸ� Group���� �Űܰ���
//      �ڵ����� Group���� ������ ���� ó���ϱ� ���ؼ��̴�.
//
//
//-----------------------------------------------------------------------------
namespace CGState
{

template <class _TSTATE_ID=_STRING>
class CUpdatable :
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGState<_TSTATE_ID>,				// (I) IState
	virtual public				ICGUpdatable						// (I) Updatable
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE_ID			TSTATE_ID;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CUpdatable()											{}
			CUpdatable(const TSTATE_ID& _idState) : ICGState<TSTATE_ID>(_idState)	{}
	virtual	~CUpdatable()											{}
};


}
