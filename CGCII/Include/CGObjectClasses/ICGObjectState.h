//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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
/**

 @class		ICGObjectState
 @brief		상태 속성을 가지고 설정하는 속성을 가진 인터페이스 클래드
 @todo		
 @ref		
 @details	\n
 객체의 상태값을 가지는 인터페이스 클래스이다.
 상태값은 eOBJECT_STATE 형이다.
 SetStatue()함수로 현재의 상태를 설정할 수 있으며 GetStatus()함수로 현재 상태를 얻을 수도 있다.
 기본적인 상태는 초기화(Initialize)-시작(Start)-중지(Stop)-소멸(Destroy)의 4가지를 기본으로 가지고 있으며 이들간의 전이 상태들도 존재한다.

  1) Initialize		eOBJECT_STATE::NONE    ->eOBJECT_STATE::INITIALIZING_PENDING ->eOBJECT_STATE::STOPPED
  2) Start			eOBJECT_STATE::STOPPED ->eOBJECT_STATE::START_PENDING        ->eOBJECT_STATE::RUNNING
  3) Stop			eOBJECT_STATE::RUNNING ->eOBJECT_STATE::STOP_PENDING		 ->eOBJECT_STATE::STOPPED
  4) Destory		eOBJECT_STATE::STOPPED ->eOBJECT_STATE::DESTROYING_PENDING   ->eOBJECT_STATE::NONE
  5) Pause			eOBJECT_STATE::RUNNING ->eOBJECT_STATE::PAUSE_PENDING		 ->eOBJECT_STATE::PAUSED
  6) Continue		eOBJECT_STATE::PAUSED  ->eOBJECT_STATE::CONTINUE_PENDING	 ->eOBJECT_STATE::RUNNING
//

*/
//-----------------------------------------------------------------------------
class ICGObjectState : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NCGAttachable<ICGObjectState>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGObjectState()	{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief 현재 객체 상태를 얻는다. @return true 현재 객체 상태
	virtual	eOBJECT_STATE		GetObjectState() const PURE;
	//! @brief 현재 객체 상태를 설정한다. @param _Status 설정하고자 하는 '객체 상태' @return 이전의 '객체 상태'
	virtual	eOBJECT_STATE		SetObjectState(_In_ eOBJECT_STATE _Status) NOEXCEPT PURE;
	//! @brief 현재 상태가 _StatusCompare일 경우 _Status로 변경한다. @param _StatusCompare 비교할 객체 상태 @ param _Status 변경할 객체 상태 @return true 변경 성공 @return false 변경 실패
	virtual	bool				SetObjectStateIf(_In_ eOBJECT_STATE _StateCompare, _In_ eOBJECT_STATE _States) NOEXCEPT PURE;
};

namespace CGObject
{

bool	Initialize(ICGObjectState* _Object, CGMSG_CONTEXT& _Msg);
bool	Start(ICGObjectState* _Object, CGMSG_CONTEXT& _Msg);
bool	Stop(ICGObjectState* _Object);
bool	Destroy(ICGObjectState* _Object);
bool	Continue(ICGObjectState* _Object);
bool	Pause(ICGObjectState* _Object);

}