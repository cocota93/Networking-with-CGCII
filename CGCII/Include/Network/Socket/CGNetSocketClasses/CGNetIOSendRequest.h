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
// CGNet::IO::SendRequest::CBase
//
// 1. CGNet::IO::SendRequest::CBase란!
//    1) Send의 수행 과정중 전달역할을 하는 Class임.
//    2) Send과정 중 변경하거나 처리해야할 것이 있으면 이 Class를 상속받아 변경
//       시킨다.
//
// 2. CGNetSocket의 핵심! Function의 기능 설명
//    1) RequestSend	RequestSend함수에서 ProcessSend()함수를 호출하도록
//						되어 있다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace SendRequest
{

class NBase :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISendable,						// (I) Sendable
	virtual public				CGNet::IO::ISendRequest					//     SendRequest
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				RequestSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override
								{
									CGNet::IO::ISendable*	p	 = dynamic_cast<CGNet::IO::ISendable*>(this);

									// 1) ProcessSend함수를 호출한다.
									return	p->ProcessSend(_pSendCompletor, _arrayBuffer, _countBuffer, _pOriginal, _pSockAddress);
								}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	// 1) Reset SendRequest
	virtual	void				ResetSendRequest() override				{}
};


}
}
}