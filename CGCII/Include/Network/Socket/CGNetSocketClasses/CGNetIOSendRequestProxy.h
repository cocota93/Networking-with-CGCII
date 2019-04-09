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
// CGNet::IO::SendRequest::NProxy
//
// 1. CGNet::IO::SendRequest::NProxy란!
//    1) 다른 SendRequest를 포인팅하고 있다가 Request가 수행되면 포인팅된
//		 SendRequest를 수행하는 class이다.
//    2) 음...
//
//
// 2. CGNet::IO::SendRequest::CProxy의 기능 설명
//    1) SetSendRequest/GetSendRequest
//		 ISendRequest를 설정하고 얻어내는 함수이다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace SendRequest
{

class NProxy :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISendRequest					//     SendRequest
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NProxy() : m_pSendRequest(nullptr)							{}
			~NProxy()													{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				RequestSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override	{ return m_pSendRequest->RequestSend(_pSendCompletor, _arrayBuffer, _countBuffer, _pOriginal, _pSockAddress); }

	// 2) Sendable 설정/얻기 함수.
			void				SetSendRequest(_In_ ISendRequest* p_pSendRequest){	 m_pSendRequest=p_pSendRequest;}
			ISendRequest*		GetSendRequest() const					{	 return m_pSendRequest;}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
protected:
	virtual	void				ResetSendRequest() override				{	m_pSendRequest=nullptr;}

private:
			ISendRequest*		m_pSendRequest;
};


}
}
}