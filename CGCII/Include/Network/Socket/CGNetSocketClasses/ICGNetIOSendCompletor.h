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
// CGNet::IO::ISendCompletor
//
// 1. CGNet::IO::ISendCompletor��~
//     Send�� �Ϸ�Ǿ��� �� ȣ��Ǵ� �Լ��� ������ Interface Class�̴�.
//    Send�� �Ϸ�Ǿ��� �� ProcessCompleteSend()�Լ��� ȣ���ϰ� �ȴ�.
//    
//     ���� Send�� �Ϸ�Ǿ��� �� ó���ؾ��� ������ �ִٸ� �� Interface�� �޾�
//    �����ϰ� Send�� Parameter�� �ѱ�� �ȴ�.
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
	// 1) Completion �Ǿ��� �� ����Ǵ� �Լ�.(�����ǿ�)
	virtual	void				ProcessCompleteSend(_In_ uintptr_t _Return, _In_ size_t _Transfered) PURE;

public:
	virtual	void				ResetSendCompletor() EMPTY;
};


}
}