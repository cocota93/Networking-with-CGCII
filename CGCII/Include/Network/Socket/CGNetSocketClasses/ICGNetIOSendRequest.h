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
// CGNet::IO::ISendRequest
//
// 1. CGNet::IO::ISendRequest은~
//    1) SendRequest는 ISender의 호출을 ISendable로 전달해주는 중간자 역할을
//       하는 Interface이다. 
//    2) 일반적으로 Send로 전송된 Data를 그 처리과정에서 변경하거나 처리해야 되는
//       경우가 생길수 있는데 이것을 일반적으로 SendRequest에서 수행하도록 정의
//       한다.
//    3) 만약에 그런 것들이 없다면 RequestSend()는 단순히 ISendable의 ProcessSend()
//       로 값만 전달해서 불러주는 간단한 함수가 될 것이다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class ISendRequest
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				RequestSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
 	// 1) SendRequest를 Reset할 때 호출되는 함수.
	virtual	void				ResetSendRequest() PURE;
};

class ISendSub
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				RequestSendSub(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;
};


}
}