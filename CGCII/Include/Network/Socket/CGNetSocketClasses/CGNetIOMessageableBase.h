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
* @class NBase
*
* @ingroup CGNet::IO::Messageable
*
* @brief �޽����� ó���ϴ� Ŭ����
*
*  ProcessMessage�� ���޵Ǿ�� �޽����� OnMessage()�Լ��� ȣ���Ͽ� ������ �ش�.
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
	// Check) ����ε� �޽����ΰ��� Ȯ���Ѵ�.
	#ifdef _VALIDATE_RECEIVE_MESSAGE
	CGASSERT(ValidateReceivedMessage(_Msg), 0);
	#endif

	// Return) OnMessage ��...
	return	OnMessage(_Msg);
}


}
}
}