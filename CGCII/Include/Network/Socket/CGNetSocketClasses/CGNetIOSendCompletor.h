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
// CGNet::IO::SendCompletor::NBase
//
// 1. CGNet::IO::SendCompletor::CBase��~
//    1) ���� �⺻���� Send SendCompletor�̴�.
//    2) �������� Send�� �Ϸ�ǰ� �Ǿ� ProcessCompleteSend�Լ��� ȣ��Ǹ� OnSended()
//       �Լ��� ȣ���ϵ��ϸ� �Ǿ� �ִ�.
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
	// 1) Completion �Ǿ��� �� ����Ǵ� �Լ�.(�����ǿ�)
	virtual	void				ProcessCompleteSend(_In_ uintptr_t _Return, _In_ size_t _Transfered) override;
};


}
}
}