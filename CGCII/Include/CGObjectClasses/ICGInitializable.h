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

 @class		ICGInitializable
 @brief		초기화하기(Initialize) 함수를 가진 인터페이스 클래스이다.
 @todo		
 @ref		ICGOpenable, ICGCloseable, ICGDestroyable
 @details	\n
 초기화하기(Initialize) 함수를 가진 인터페이스 클래스이다.
 ICGDestroyable 클래스를 상속받아 소멸하기(Destroy)와 쌍으로 사용된다.
 
*/
//-----------------------------------------------------------------------------
class ICGInitializable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGDestroyable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGInitializable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 전달 인자 없이 초기화를 실행한다. @return true 성공 @return false 실패
			bool				Initialize() { CGMSG_CONTEXT tempMSG; return Initialize(tempMSG); }

	//! @brief 초기화 한다. @param _Msg 초기화 인자를 전달할 메시지 @return true 성공 @return false 실패
	virtual	bool				Initialize(CGMSG_CONTEXT& _Msg) PURE;
};
