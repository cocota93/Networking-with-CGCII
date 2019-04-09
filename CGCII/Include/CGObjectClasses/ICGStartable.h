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

 @class		ICGStartable
 @brief		시작/종료/잠시정지/다시시작 속성을 가진 인터페이스 클래드
 @todo		
 @ref		ICGOpenable, ICGCloseable, ICGInitializable, ICGDestroyable
 @details	\n
 시작(Start)/종료(Stop)/정지(Pause)/재개(Continue) 속성을 가지고 있는 인터페이스 클래스이다.

*/
//-----------------------------------------------------------------------------
class ICGStartable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual	~ICGStartable()		{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 시작한다. @param _pMSG 시작시 전달할 인자 @return true 성공 @return false 실패
			bool				Start()									{ CGMSG_CONTEXT tempMSG; return Start(tempMSG);}
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) PURE;

	//! @brief 중지한다. @return true 성공 @return false 실패
	virtual	bool				Stop() PURE;
};
