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
//
// CGNet::IO::Sender::NDatagramProxy
//
// 1. CGNet::IO::Sender::CDatagramProxy은~
//    - Sender의 Pointer를 가지고 있는 Sender로 Send를 할 경우 Pointer로 지정된
//      Send를 통해 Send를 수행한다. 
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sender
{

class NDatagramProxy : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISenderDatagram,				//     Sender
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NDatagramProxy(_In_opt_ ISenderDatagram* p_pSender = nullptr) : m_pSender(p_pSender)	{}
	virtual	~NDatagramProxy()												{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				SendTo(_In_ const CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress = nullptr) override;

	// 2) 
			void				SetSender(_In_ ISenderDatagram* p_pSender)	{ m_pSender = p_pSender; }
			CGPTR<ISenderDatagram>	GetSender() const						{	 return m_pSender;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			CGPTR<ISenderDatagram>	m_pSender;

// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);
};


inline bool NDatagramProxy::SendTo(_In_ const CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress)
{
	// Check) _arrayBuffer->buf가 nullptr이 아닌가?
	CGASSERT(_Buffer.buf != nullptr, false)

	// Check) _arrayBuffer->len이 0이 아닌가?
	CGASSERT(_Buffer.len != 0, false)

	// Check) Packet Validate Check한다.
	#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&_Buffer, 1), false);
	#endif

	// Check) Sender가 nullptr이면 안됀다.
	CGASSERT(m_pSender.exist(), false);

	// Statistics) Sended Packet을 계산한다.
	Statistics_OnSendMessage();

	// 1) Send한다.) 	
	return m_pSender->SendTo(_Buffer, _pSockAddress);
}

inline	bool NDatagramProxy::ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer)
{
	return	validate_message(_Buffer, _countBuffer);
}


}
}
}