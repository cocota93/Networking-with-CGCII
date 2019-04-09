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
// CGNet::IO::Socket::NDummy
//
// 1. CGNet::IO::Socket::NDummy�� Ư¡!
//    1) �ƹ��� ����� �������� ���� Dummy �����̴�.
//    2) �Ϲ������� ���������� ISocket �������̽��� ������ �ʿ��� ��� �̰���
//       ���ȴ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Socket
{

class NDummy :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ISocket									//     ISocket
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
			bool				IsFree() const							{	return GetReferenceCount()<=1;}	// Reference Count�� 1���� �۰ų� ������ Free���¶�� �Ҽ� �ִ�.


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessResetSocket()�Լ��� ����ɶ� ȣ��Ǵ� On�Լ��̴�.
	virtual	void				OnPrepareSocket()						{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Socket�� �غ��ϰ� ���� �� ȣ���ϴ� �Լ�.
	virtual	void				ProcessPrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) override;
	virtual	bool				ProcessCloseSocket(uint32_t _Reason=SOCKET_REASON_NONE) override;
};


}
}
}