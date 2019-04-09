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

 @class		ICGPausable
 @brief		잠시정지/다시시작 속성을 가진 인터페이스 클래드
 @todo		
 @ref		ICGInitializable, ICGDestroyable, ICGStartable
 @details	\n
 잠시정지(Pause)/재개(Continue) 속성을 가지고 있는 인터페이스 클래스이다.

*/
//-----------------------------------------------------------------------------
class ICGAcuquirable :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual	~ICGAcuquirable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 정지한다. @return true 성공 @return false 실패
	virtual	eOBJECT_RESULT		Acquire() PURE;

	//! @brief 재개한다. @return true 성공 @return false 실패
	virtual	void				Unacquire() PURE;
};
