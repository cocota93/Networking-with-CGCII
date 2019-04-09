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

 @class		ICGMessageable
 @brief		메시지를 전달을 수 있는 인터페이스 클래스
 @todo		
 @ref		ICGOpenable, ICGCloseable, ICGDestroyable
 @details	\n
 메시지를 전달받을 수 있는 인터페이스 클래스이다. 
 RequestProcessMessage(...)함수로 메시지를 전달받으며
 ProcessMessage(...) 함수에서 전달 받은 메시지에 대한 처리를 정의한다.

*/
//-----------------------------------------------------------------------------
class ICGMessageable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGMessageable()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief 메시지 처리를 요청한다. @param _Msg 처리 요청하는 메시지 @return true !0 처리됨 @return 0 처리하지 않음
			int					RequestProcessMessage(CGMSG& _Msg)		{	return ProcessMessage(_Msg);}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief 메시지 처리를 정의한다. @param _Msg 처리 요청하는 메시지 @return true !0 처리됨 @return 0 처리되지 않음
	virtual	int					ProcessMessage(CGMSG& _Msg) PURE;
};
