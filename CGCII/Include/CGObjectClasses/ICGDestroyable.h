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

 @class		ICGDestroyable
 @brief		소멸하기(Destroy) 함수를 가진 인터페이스 클래스
 @todo		
 @ref		ICGCloseable, ICGInitializable, ICGDestroyable
 @details	\n
 소멸하기(Destroy) 함수를 가진 인터페이스 클래스이다.
 일반적으로 ICGInitialzable 클래스의 Initialize()와 함께 사용된다.

*/
//-----------------------------------------------------------------------------
class ICGDestroyable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGDestroyable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 소멸한다. @return true 성공 @return false 실패
	virtual	bool				Destroy() PURE;
};
