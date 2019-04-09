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
// CGNet::IO::Binder::NTCP
// 
// 1. Binder��~
//    1) TCP�� ���� Bind() ����� �ִ� �Լ��� TCP�� ���� ���۵� Ŭ�����̴�.
//    2) TCP�� ��� Accept�� ���� Bind�� �����ϴµ� �̸� ���� Ŭ�����̴�.
//    3) Accept�� ���� �ʴ��� Ŭ���̾�Ʈ TCP ������ ��� BInd�� �ϰ��� �� ����
//       �ִ� �̶� ����� �� �ִ�.
//    4) TCP�� Connector ��ü�� �⺻������ BInder�� ��ӹ޾� ���۵ȴ�.
//    5) Bind�� �ּҿ� 0����  �����ϸ� �ϵ������ ��� �ּҿ� Bind�Ǹ� ��Ʈ�� 0����
//       �ϸ� ������ �� ��Ʈ�� �ڵ������� �����Ͽ� Bind�ȴ�.
//    6) Ư���� �ּҿ� ��Ʈ�� ���ε带 �� ���� �ǵ��� 1000�̻��� ��Ʈ�� ����ϴ�
//       ���� ����. �ֳ��ϸ� �� ������ ��Ʈ�� ����� ��Ʈ�� ���� �����̴�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Binder
{

class NTCP : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Socket
	virtual public				CGNet::IO::IBinder,						//     Binder
	virtual public				CGNet::IO::Statistics::NSocket			//     Socket Stistics
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	virtual	bool				RequestBind(_In_ const SOCKADDR_CGNETWORK& _pSocketAddr) override;
	virtual	void				ResetBinder() override					{}
};


}
}
}