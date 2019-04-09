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
// CGNet::IO::Socket::NBase
//
// 1. CGNet::IO::Socket::NBase�� Ư¡!
//    1) �Ϲ����� Socket�� ����� �����ϴ� �⺻���� �����̴�.
//    2) Socket�� ���� �⺻ ������� Ŭ������ �ʱ�ȭ�� ���õ� �Լ����� ������ �ִ�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Socket
{

class NBase :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ISocket,								//     ISocket
	virtual public				CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) ���� Socket�� ���� ������ ���� �ݾ��� �� ȣ��Ǵ� �Լ��̴�.
	virtual	void				OnPrepareSocket()						{}
	virtual	void				OnCloseSocket()							{}

	// 2) Socket�� �����ϴ� ������ �����ϴ� �Լ��̴�.
	virtual	void				ProcessCreateSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) ������ �غ��ϴ� �Լ��̴�.
	virtual	void				ProcessPrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) override;
};


}
}
}