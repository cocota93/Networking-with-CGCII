//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                         Socket template Classes                           *
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

 @class		CArray
 @brief		옵저버를 가질수 있기 위한 인터페이스 클래스이다.
 @todo		
 @ref		
 @details	\n
 동작 형태는 그룹과 동일하다 다만 그룹과 다르게 배타적으로 동작하지 않는다.
 즉 옵저버는 동시에 여러 객체를 옵저빙할수 있다.
       
*///-----------------------------------------------------------------------------
template <class _TOBSERVER>
class ICGServerObservers :
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (I) Reference Counter.
{
// ****************************************************************************
// Declare) Member의 Type
// ----------------------------------------------------------------------------
public:
	typedef	_TOBSERVER			TOBSERVER;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGServerObservers()										{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief '옵저버 객체'를 등록한다. @param _pObserver 등록할 '옵저버 객체' @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
	virtual	eOBJECT_RESULT		RegisterObserver(TOBSERVER* _pObserver) PURE;
	//! @brief 등록된 '옵저버 객체'를 해제한다. @param _pObserver 등록 해제할 '옵저버 객체' @return true 성공 @return false 실패
	virtual	bool				UnregisterObserver(TOBSERVER* _pObserver) PURE;
	//! @brief 모든 '옵저버 객체'를 등록 해제한다.
	virtual	void				UnregisterAllObserver() PURE;
};
