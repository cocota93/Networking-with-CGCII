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
// CGNet::IO::IConnectable
//
// 1. CGNet::IO::IConnectable��~
//    1) ������ �ʿ��� Socket�� �ʿ��� Connectable�̴�.
//    2) �Ϲ������� TCP socket�̳� Reliable UDP�� ���ȴ�.
//    3) TCP Socket�� ��� Server���̳� Client���̳� ��� ������ �ʿ��ϹǷ� 
//       TCP Socket�� ��� ICGConnectable�� ��ӹ��� ���̴�.
//    4) ���� �� ó�� ������ �ۼ��ϴ� Ŭ������ �Ʒ��� ���� �ֿ� �Լ��� �ִ�.
//
//       - bool ProcessCompleteConnect(_In_opt_ CGNet::IO::IConnective* _pConnective, _In_ uintptr_t _Return);
//         ���� �Ϸ� �� ó�������� �����ϴ� �Լ��̴�.
//
//       - bool ProcessCompleteDisconnect();
//         ���� ���� �� ���� ����ó�������� �����ϴ� �Լ��̴�.
//
//       - bool Disconnect();
//         ���� ���� �䱸�� ó���� �����ϴ� �Լ��̴�.
//
//    5) ICGConnectable�� ������ �����ǰų� Ȥ�� ���� ó���� ������ �� ó�� ������
//       �����ϴ� Ŭ�����̴�. 
//       ������ �䱸�ϴ� Ŭ������ IConnector�� Connective::IAcceptor�� ����ؾ�
//       �Ѵ�.
// 
// 
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IConnectable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				CGNet::IO::ISocket,						// (I) �ٽ� ����� Socket
	virtual public				IAddress,								// (@) Address
	virtual public				CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			IConnectable() : m_pConnective(nullptr)						{}
	virtual	~IConnectable()												{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Disconnect�� ������ �� �θ��� �Լ��̴�.(Graceful)
	virtual	bool				Disconnect() PURE;

	// 2) Reset�Ҷ� ȣ���ϴ� �Լ�.(�⺻�� ���...)
	virtual	void				ResetConnectable() PURE;


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
public:
	virtual	bool				ProcessCompleteConnect(_In_opt_ CGNet::IO::IConnective* _pConnective, _In_ uintptr_t _Return) PURE;
	virtual	bool				ProcessCompleteDisconnect() PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	// 1) Connective
			IConnective*		m_pConnective;
			flexible<16>		m_flexible;
			circular_list<CGNet::IO::IConnectable*>::iterator	m_iterConnectable;
};


}
}