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
//
// CGNet::IO::Sender::NStreamStaticProxy
//
// 1. CGNet::IO::Sender::CStreamProxy��~
//    - Sender�� Pointer�� ������ �ִ� Sender�� Send�� �� ��� Pointer�� ������
//      Send�� ���� Send�� �����Ѵ�. 
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sender
{

template <class TSENDER=ISender>
class NStreamStaticProxy : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISender,						//     Sender
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NStreamStaticProxy()										{}
			~NStreamStaticProxy()										{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;

	// 2) Sender����.
	static	void				SetSender(_In_ TSENDER* p_pSender)		{	 m_pSender=p_pSender;}
	static	void				ResetSender()							{	 m_pSender.reset();}
	static	CGPTR<TSENDER>		GetSender()								{	 return m_pSender;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	static	CGPTR<TSENDER>		m_pSender;
};


template <class TSENDER>
CGPTR<TSENDER> NStreamStaticProxy<TSENDER>::m_pSender;

template <class TSENDER>
bool NStreamStaticProxy<TSENDER>::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf�� nullptr�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len�� 0�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	// Check) ���۰� Overflow�Ǿ��°�?
	CGASSERT(_Buffer._is_buffer_overflow()==false, false);

	// Check) Packet Validate Check�Ѵ�.
	#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&_Buffer, 1), false);
	#endif

	// Check) Sender�� nullptr�̸� �ȉ´�.
	CGASSERT(m_pSender!=nullptr, false);

	// Statistics) Sended Packet�� ����Ѵ�.
	Statistics_OnSendMessage();

	// 1) Send�Ѵ�.) 	
	return m_pSender->Send(_Buffer);
}

template <class TSENDER>
bool NStreamStaticProxy<TSENDER>::ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer)
{
	return	validate_message(_Buffer, _countBuffer);
}


}
}
}