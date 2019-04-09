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

 @class		ICGResource
 @brief		자원 속성 인터페이스 클래스이다.
 @todo		
 @ref		
 @details	\n
 자원(Resource)의 기본 속성을 가지는 인터페이스 클래스로 IObject를 상속받았다.
 이 인터페이스를 상속받으면 '자원 관리자'에 의해 관리될 수 있다.
 
*/
//-----------------------------------------------------------------------------
class ICGResource : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						ICGObjectIdentifiable,
	virtual public				ICGMessageable,
	virtual public				ICGNameable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual ~ICGResource()											{}
};
