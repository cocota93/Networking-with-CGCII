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
// CGNet::IO::IBindable
//
// 1. IBindable��~
//    Bind�� ���� Bind Interface�� ���� Interface Class��.
//
// 2. �ֿ���ó.
//    1) UDP Socket�� ���� Binder�̴�.
//    2) ���� UDP Socket�� Ư���� �ּҿ� Port�� Bind�ؾ� �Ѵٸ� �� Binder Ŭ������
//       ��ӹ޾� Bind()�Լ��� ����Ͽ� Ư�� �ּҿ� ��Ʈ�� Bind�� �� �ִ�.
//    3) Binder�� �ȴٸ� ���������� Binder Manager�� ��ϵȴ�. �� CloseSocket()
//       �Ǹ� Binder Manager���� ��������ȴ�.
//    4) ��ϵ� Binder���� �̱����� CGNet::IO::Binder::Manager ��ü�� ���� ������
//       ���� �� �ִ�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IBinder : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				CGNet::IO::ISocket,						// (I) Socket Handle
	virtual public				ICGMessageable,							// (I) Messageable
	virtual	public				ICGNameable								// (I) Nameable
{
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) �߰� Bind�Լ�
			bool				Bind(_In_opt_ const SOCKADDR_CGNETWORK* _pSocketAddr);
			bool				Bind(_In_ u_short p_dwPort = 0);


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	// 1) Bind�Լ�
	virtual	bool				RequestBind(_In_ const SOCKADDR_CGNETWORK& _rSocketAddr) PURE;

public:
	// 2) Reset�Ҷ� ȣ���ϴ� �Լ�.(�⺻�� ���...)
	virtual	void				ResetBinder() PURE;

protected:
			void				RegisterBinder();
			void				UnregisterBinder();
};



}
}