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
// CGFSM::CStateProcess<TSTATE, TEVENT>
//
// 1. CGFSM::CStateProcess<TSTATE, TEVENT>란!
//    1) Grouble 객체  여러 개를 묶어서 관리하는 것이 Group class이다.
//       이 Group Class는 는 Interface Class에 해당하는 것으로 상속을 받은 후 
//       정의하여 사용하여야 한다.
//
// 2. CGFSM::CStateProcess<TSTATE, TEVENT>의 핵심! Function의 기능 설명.
//    1) Process()
//       Group에서 Member 객체를 떼내는 함수이다. 이 함수는 abstract함수로
//      상속받은 Group은 반드시 재정의 해 주어야 한다.
//      이 함수만 virtual로 선언한 이유는 한 Group에서 다른 Group으로 옮겨갈시
//      자동으로 Group에서 떼내는 것을 처리하기 위해서이다.
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
