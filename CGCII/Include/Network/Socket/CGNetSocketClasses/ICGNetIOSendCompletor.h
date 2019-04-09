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
// CGNet::IO::ISendCompletor
//
// 1. CGNet::IO::ISendCompletor은~
//     Send가 완료되었을 때 호출되는 함수를 정의한 Interface Class이다.
//    Send가 완료되었을 때 ProcessCompleteSend()함수를 호촐하게 된다.
//    
//     만약 Send가 완료되었을 때 처리해야할 내용이 있다면 이 Interface를 받아
//    정의하고 Send시 Parameter로 넘기면 된다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class ISendCompletor : virtual public ICGReferenceable
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	// 1) Completion 되었을 때 수행되는 함수.(재정의용)
	virtual	void				ProcessCompleteSend(_In_ uintptr_t _Return, _In_ size_t _Transfered) PURE;

public:
	virtual	void				ResetSendCompletor() EMPTY;
};


}
}