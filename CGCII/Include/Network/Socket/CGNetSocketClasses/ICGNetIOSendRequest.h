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
// CGNet::IO::ISendRequest
//
// 1. CGNet::IO::ISendRequest��~
//    1) SendRequest�� ISender�� ȣ���� ISendable�� �������ִ� �߰��� ������
//       �ϴ� Interface�̴�. 
//    2) �Ϲ������� Send�� ���۵� Data�� �� ó���������� �����ϰų� ó���ؾ� �Ǵ�
//       ��찡 ����� �ִµ� �̰��� �Ϲ������� SendRequest���� �����ϵ��� ����
//       �Ѵ�.
//    3) ���࿡ �׷� �͵��� ���ٸ� RequestSend()�� �ܼ��� ISendable�� ProcessSend()
//       �� ���� �����ؼ� �ҷ��ִ� ������ �Լ��� �� ���̴�.
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
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool				RequestSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
 	// 1) SendRequest�� Reset�� �� ȣ��Ǵ� �Լ�.
	virtual	void				ResetSendRequest() PURE;
};

class ISendSub
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool				RequestSendSub(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;
};


}
}