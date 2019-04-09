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
// CGNet::IO::IConnectManager
//
// 1. CGNet::IO::IConnectManager��~
//    1) Connect Interface�� ���� Interface Class�̴�.
//    2) �ܼ��� Connect()�� �����ϱ� ���� Interface��θ� �Ǿ� �ִ�.
//
// 2. Public �Լ�.
//    1) AddConnectable(...)/RemoveConnectable(...)
//       - IConnectable�� �߰��ϰ� �����ϴ� �Լ��̴�.
//
//    2) DisconnectAll()
//       - ��� Socket�� Graceful Close�� �����Ѵ�. ���������� �� Socket��
//         shutdown()�� �����Ѵ�.
//       - Graceful close�� ���������� ������ �������� ���ӵ� ���·� �����ִ�
//         Socket�� ������ ���� ���� �� �ִ�.
//       - ������ �Ϸ��ϴ� �������� TIME_WAIT ���°� ���������ν� ���� Socket��
//         �����ϰ� �� ���ɼ��� �ִ�.
//
//    3) CloseAll()
//       - ��� Socket�� ���� Abortive Close�� �����Ѵ�. ���������� Linger�ɼ���
//         Abortive�� ������ closesocket()�� �����Ѵ�.
//       - �Լ� ȣ�� ��� Socket�� ������ ����Ǹ� ��� Socket���� �Ҵ��� �����ȴ�.
//       - �Ϲ������� ������ ����� ���� Socket�� �����ϱⰡ ������ Server����
//         ���� ���ȴ�.
//
//    4) GetCount();
//       - �����ϰ� �ִ� IConnectable ��ü�� ���� �����ش�.
//
//    5) AllocIterator()
//       - ����� Connectable�� �����͸� ��ȸ�ϸ� ���� ��� ���� �� �� �Լ���
//         ȣ���Ͽ� Iterator�� ���� �� �ִ�.
//       - �Ϲ������� Iterator�� ��ԵǸ� ���� List�� Lock�� �ɸ��� �ȴ�.
//       - ��� ���� �� ���� Iterator�� �Ҹ�Ǹ� Lock�� �����ǰ� �ȴ�.
//       - AllocIterator()�Լ��� ���� ����� Iterator�� �Ҵ� ���� ���� ó��
//         Socket�� ��ġ�� �ִ�. �׸��� GetNext()�Լ��� ȣ���Ͽ� ���� IConnectable��
//         ������ �� �ִ�.
//       - ���� �����ϰ� �Ǹ� nullptr�� ������ �ȴ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IConnectableManager :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (I) Reference Counter.
{
public:
	class	CONNECTABLE_ITERATOR;

// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Connectable�� Add/Remove
	virtual	bool				AddConnectable(_In_ IConnectable* _pConnectable) PURE;
	virtual	bool				RemoveConnectable(_In_ IConnectable* _pConnectable) PURE;

	// 2) Disconnect All Accepted Socket
	virtual	void				DisconnectAllConnectable() PURE;
	virtual	void				CloseAllConnectable(uint32_t p_dwFlag=0) PURE;

	// 3) Connectable ��
	virtual	int					GetCount() const PURE;

	// 4) Iterator���
	virtual	CGPTR<CONNECTABLE_ITERATOR>	AllocIterator() PURE;
};


class IConnectableManager::CONNECTABLE_ITERATOR : virtual public ICGReferenceable
{
public:
	virtual	void			Reset() PURE;
	virtual	IConnectable*	GetPre() PURE;
	virtual	IConnectable*	GetNext() PURE;
};


}
}