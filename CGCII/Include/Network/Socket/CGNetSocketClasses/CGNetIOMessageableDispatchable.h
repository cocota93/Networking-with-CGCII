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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
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
* @brief �޽����� ó���ϴ� Ŭ����
*
*  ProcessMessage�� ���޵Ǿ�� �޽����� ���� Dispatch�� ���� OnMessage()�Լ���
*  ȣ���Ͽ� ������ �ش�.
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
	// Check) ����ε� �޽����ΰ��� Ȯ���Ѵ�.
	#ifdef _VALIDATE_RECEIVE_MESSAGE
	CGASSERT(ValidateReceivedMessage(_Msg), 0);
	#endif

	// 1) ���� Dispatch�Ѵ�.
	NOTIFY_MESSAGE_SOURCE(_Msg, (TCLASS*)this);

	// Return) OnMessage ��...
	return	OnMessage(_Msg);
}


}
}
}