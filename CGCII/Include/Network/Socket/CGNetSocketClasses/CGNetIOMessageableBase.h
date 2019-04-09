//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Network Socket Classes                           *
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
/*!
* @class NBase
*
* @ingroup CGNet::IO::Messageable
*
* @brief 메시지를 처리하는 클래스
*
*  ProcessMessage로 전달되어온 메시지의 OnMessage()함수를 호출하여 전달해 준다.
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Messageable
{

class NBase : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGMessageable							//     Messageable
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) OnMessage
	virtual int					OnMessage(CGMSG& /*_Msg*/)				{	return 0;}

	// 2) ValidateMessage
	virtual	bool				ValidateReceivedMessage(_In_ const CGMSG& /*_Msg*/){	return true;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	virtual	int					ProcessMessage(CGMSG& _Msg) override;
};

inline 	int NBase::ProcessMessage(CGMSG& _Msg)
{
	// Check) 제대로된 메시지인가를 확인한다.
	#ifdef _VALIDATE_RECEIVE_MESSAGE
	CGASSERT(ValidateReceivedMessage(_Msg), 0);
	#endif

	// Return) OnMessage 후...
	return	OnMessage(_Msg);
}


}
}
}