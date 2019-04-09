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
// CGNet::IO::Sender::NStreamProxy
//
// 1. CGNet::IO::Sender::NStreamProxy��~
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sender
{

class NStreamProxy : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public			CGNet::IO::ISender							//     Sender
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NStreamProxy(ISender* const p_pSender=nullptr)				{	SetSender(p_pSender);}
	virtual ~NStreamProxy()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool			Send(_In_ const CCGBuffer* _pBuffer) override {	CGASSERT(m_pSender!=nullptr, false); return m_pSender->Send(_pBuffer);}

	// 2) Sender����.
			void			SetSender(_In_ ISender* p_pSender)			{	 m_pSender=p_pSender;}
			ISender*		GetSender() const							{	 return m_pSender;}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) Send�Լ� ���ฦ �������� �� ȣ���ϴ� �Լ�.
	virtual	void			OnFailSending()								{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			ISender*	m_pSender;
};


}
}
}