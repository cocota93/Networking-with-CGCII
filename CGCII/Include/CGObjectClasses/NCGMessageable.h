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
namespace CGMessageable
{

//-----------------------------------------------------------------------------
/**

 @class		NBase
 @brief		메시지를 전달 받는 클래스
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class NBase : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGMessageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NBase() : m_bEnableMessageable(true)						{}
	virtual ~NBase()													{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) ProcessMessage Function
	virtual	int					ProcessMessage(CGMSG& _Msg)				{	if(IsMessageableDisabled()) return 0; return OnMessage(_Msg);}

	// 2) Enable Status
	//! @brief 메시지 수신을 활성화 시킨다.
			void				EnableMessageable()						{	m_bEnableMessageable=true;}
	//! @brief 메시지 수신을 금지 시킨다.
			void				DisableMessageable()					{	m_bEnableMessageable=false;}
	//! @brief 메시지를 받을 수 있는 상태인가를 검사한다. @return true 받을 수 있음. @return false 받을 수 없음.
			bool				IsMessageableEnabled()					{	return m_bEnableMessageable;}
	//! @brief 메시지를 받을 수 없는 상태인가를 검사한다. @return true 받을 수 없음. @return false 받을 수 있음.
			bool				IsMessageableDisabled()					{	return !IsMessageableEnabled();}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief 메시지를 전달 받았을 때 호출되는 함수 @param _Msg 전달받은 메시지 @return !0 메시지를 처리함. @return 0 메시지를 처리하지 않음.
	virtual	int					OnMessage(CGMSG& _Msg) PURE;


// ****************************************************************************
// Implmentations)
// ----------------------------------------------------------------------------
private:
	// 1) Flag
			bool				m_bEnableMessageable;
};


}