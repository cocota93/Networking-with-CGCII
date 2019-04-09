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
// CGNet::IO::SendRequest::CBase
//
// 1. CGNet::IO::SendRequest::CBase��!
//    1) Send�� ���� ������ ���޿����� �ϴ� Class��.
//    2) Send���� �� �����ϰų� ó���ؾ��� ���� ������ �� Class�� ��ӹ޾� ����
//       ��Ų��.
//
// 2. CGNetSocket�� �ٽ�! Function�� ��� ����
//    1) RequestSend	RequestSend�Լ����� ProcessSend()�Լ��� ȣ���ϵ���
//						�Ǿ� �ִ�.
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
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool				RequestSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override
								{
									CGNet::IO::ISendable*	p	 = dynamic_cast<CGNet::IO::ISendable*>(this);

									// 1) ProcessSend�Լ��� ȣ���Ѵ�.
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