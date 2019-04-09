//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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

 @class		ICGUpdatable
 @brief		업데이트 속성의 인터페이스 클래스
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class ICGUpdatable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGUpdatable()		{}
	virtual	~ICGUpdatable()		{}

// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	//! @brief 업데이트 과정을 정의한다. @param _pMSG 전달할 인자 @return true 성공 @return false 실패
	virtual	int					ProcessUpdate(CGMSG& _Msg) PURE;
};
