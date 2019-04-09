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
// CGNet::IO::Socket::NTCP
//
// 1. CGNet::IO::Socket::NTCP의 특징!
//    1) TCP용으로 제작된 Socket Class이다.
//    2) Socket을 생성하고 소멸하는 기능을 가지고 있다.
//    3) Socket의 Send Buffer와 Receive Buffer를 소켓별로 설정할 수 있지만
//       특별히 설정하지 않으면 기본으로 설정될 값을 아래의 전역함수로 변경할
//       수도 있다.
//       
//       static void	SetDefaultSendBufferSize(int _iSize);
//       static int		GetDefaultSendBufferSize() const;
//
//       static void	SetDefaultReceiveBufferSize(int _iSize);
//       static int		GetDefaultReceiveBufferSize() const;
//
//       소켓이 생성되면 일단 Default값으로 설정되며 소켓별로 변경을 할 경우
//       각기 따로 설정해 주어야 한다.
//
//    4) 일반적으로 소켓의 Send와 Receive 버퍼를 크게 하면 Traffic이 많이 몰릴
//       때 더 좋은 성능을 발휘해준다. 하지만 그만큼 용량을 많이 차지하므로 
//       적절히 설정해야 한다.
//        
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Socket
{

class NTCPRIO :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NTCP
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NTCPRIO() : NTCP(WSA_FLAG_REGISTERED_IO)					{}
			~NTCPRIO()													{}
};


}
}
}