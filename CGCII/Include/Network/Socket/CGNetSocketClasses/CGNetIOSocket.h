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
// CGNet::IO::Socket::NBase
//
// 1. CGNet::IO::Socket::NBase의 특징!
//    1) 일반적인 Socket의 기능을 수행하는 기본적인 소켓이다.
//    2) Socket을 위한 기본 통계정보 클래스와 초기화에 관련된 함수들을 가지고 있다.
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
	virtual public				CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) 각각 Socket을 새로 열었을 때와 닫았을 때 호출되는 함수이다.
	virtual	void				OnPrepareSocket()						{}
	virtual	void				OnCloseSocket()							{}

	// 2) Socket을 생성하는 과정을 정의하는 함수이다.
	virtual	void				ProcessCreateSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) 소켓을 준비하는 함수이다.
	virtual	void				ProcessPrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) override;
};


}
}
}