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
// CGFSM::State::CMessagable
//
// 1. CGFSM::State::CMessagable이란...?
//    1) FSM용 State로 Message를 받아 처리하는 State를 의미한다.
//    2) 따라서 State 클래스와 ICGMessageable를 상속받은 클래스이다.
//
// 2. CGNetPacketMap의 핵심! Function의 기능 설명
//    1) 처리함수들 기본적인 I/O처리를 위한 처리함수들이다.
//					내부적으로 각종 I/O를 처리하기 위해 필요한 함수들에 대해서 정의한 것이다.
//    2) 진행함수들	Socket의 각 동작을 정의하는 함수들이다.
//    3) User함수들	재정의를 위해 만들어진 함수이다. 프로그래머가 이 부분들을 재정의
//					함을써 Socket을 게임에 맞게 만들게 된다.
//
// 3. 주의 사항
//  Run을 항상 일정 시간마다 실행을 시켜 I/O에 대한 처리를 반듯이 해주어야 한다.
//
//
//-----------------------------------------------------------------------------
namespace CGState
{

template <class _TSTATE_ID=_STRING>
class CUpdatableMessagable :
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						CUpdatable<_TSTATE_ID>,					// (@) StateProcess
	virtual public				ICGMessageable							// (I) ICGMessageable
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
			CUpdatableMessagable()										{}
			CUpdatableMessagable(const TSTATE_ID& _idState) : CUpdatable<TSTATE_ID>(_idState)	{}
	virtual	~CUpdatableMessagable()										{}
};


}
