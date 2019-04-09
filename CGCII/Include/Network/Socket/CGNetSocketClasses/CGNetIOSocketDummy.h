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
// CGNet::IO::Socket::NDummy
//
// 1. CGNet::IO::Socket::NDummy의 특징!
//    1) 아무런 기능을 수행하지 않은 Dummy 소켓이다.
//    2) 일반적으로 형식적으로 ISocket 인터페이스의 구현이 필요한 경우 이것이
//       사용된다.
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
			bool				IsFree() const							{	return GetReferenceCount()<=1;}	// Reference Count가 1보다 작거나 같으면 Free상태라고 할수 있다.


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessResetSocket()함수가 수행될때 호출되는 On함수이다.
	virtual	void				OnPrepareSocket()						{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Socket을 준비하고 닫을 때 호출하는 함수.
	virtual	void				ProcessPrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) override;
	virtual	bool				ProcessCloseSocket(uint32_t _Reason=SOCKET_REASON_NONE) override;
};


}
}
}