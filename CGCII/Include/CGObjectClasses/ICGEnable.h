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

 @class		ICGEnable
 @brief		가능/불가능 속성을 가진 인터페이스 클래스
 @todo		
 @ref		ICGReferenceable
 @details	\n
 
*/
//-----------------------------------------------------------------------------
class ICGEnable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGEnable()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief 메시지 처리를 요청한다. @param _Msg 처리 요청하는 메시지 @return true !0 처리됨 @return 0 처리하지 않음
			bool				Enable(bool _bState=true)			{	return ProcessSetEnable(_bState);}
			bool				Disable()							{	return ProcessSetEnable(false);}

			bool				IsEnable()							{	return ProcessGetEanble();}
			bool				IsDisable()							{	return !ProcessGetEanble();}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief 가능/불가능 상태의 설정 처리를 정의한다. @param _bState 설정할 State @return 이전 설정상태
	virtual	bool				ProcessSetEnable(bool _bState) PURE;

	//! @brief 현재의 가능/불가능 상태의 설정을 정의한다. @return 현재의 가능/불가능 설정상태
	virtual	bool				ProcessGetEnable() PURE;
};
