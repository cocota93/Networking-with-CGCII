//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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

 @class		ICGSchedulable
 @brief		특정 시간을 지정해 실행해야 하는 것을 정의하는 클래스이다.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
class ICGSchedulable :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGObjectIdentifiable,
	virtual public				ICGReferenceable						// (@) Reference count
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGSchedulable()											{}
	virtual	~ICGSchedulable()											{}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	//! @brief 등록될 때 호출되는 함수
	virtual	void				ProcessOnRegister() PURE;

	//! @brief 등록이 해제될 때 호출되는 함수
	virtual	void				ProcessOnUnregister() PURE;

	//! @brief 스케쥴 처리를 위해 호출되는 함수.
	virtual	void				ProcessSchedule() PURE;

protected:
	// 3) 정해진 Schedule에 추가될 
			CGPTR<ICGExecutor>	m_pexecutor;

};
