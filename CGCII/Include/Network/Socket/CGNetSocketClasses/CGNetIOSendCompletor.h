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
// CGNet::IO::SendCompletor::NBase
//
// 1. CGNet::IO::SendCompletor::CBase은~
//    1) 가장 기본적인 Send SendCompletor이다.
//    2) 실질적인 Send가 완료되게 되어 ProcessCompleteSend함수가 호출되면 OnSended()
//       함수를 호출하도록만 되어 있다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace SendCompletor
{

class NBase : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISendCompletor					//     Sendable
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
	// 1) 
	virtual	void				OnSended(_In_ uintptr_t /*_Return*/, _In_ size_t /*_Transfered*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Completion 되었을 때 수행되는 함수.(재정의용)
	virtual	void				ProcessCompleteSend(_In_ uintptr_t _Return, _In_ size_t _Transfered) override;
};


}
}
}