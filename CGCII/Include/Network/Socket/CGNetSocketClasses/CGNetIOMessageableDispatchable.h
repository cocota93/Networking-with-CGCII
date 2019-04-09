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
* @class NDispatchable
*
* @ingroup CGNet::IO::Messageable
*
* @brief 메시지를 처리하는 클래스
*
*  ProcessMessage로 전달되어온 메시지의 먼저 Dispatch한 이후 OnMessage()함수로
*  호출하여 전달해 준다.
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Messageable
{

template <class TCLASS>
class NDispatchable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				NBase,									//     Messageable
	public						NCGDispatchable							// (@) Dispatchable
{
// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	virtual	int					ProcessMessage(CGMSG& _Msg);

			friend				NBaseProxy;
};

template <class TCLASS>
inline 	int NDispatchable<TCLASS>::ProcessMessage(CGMSG& _Msg)
{
	// Check) 제대로된 메시지인가를 확인한다.
	#ifdef _VALIDATE_RECEIVE_MESSAGE
	CGASSERT(ValidateReceivedMessage(_Msg), 0);
	#endif

	// 1) 먼저 Dispatch한다.
	NOTIFY_MESSAGE_SOURCE(_Msg, (TCLASS*)this);

	// Return) OnMessage 후...
	return	OnMessage(_Msg);
}


}
}
}