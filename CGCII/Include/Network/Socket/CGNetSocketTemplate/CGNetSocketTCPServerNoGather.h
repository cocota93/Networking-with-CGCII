//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                      Network Socket Template Classes                      *
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
// CGNet::Socket::CTCPServerNoGather
//
// 1. CGNet::Socket::CTCPServerNoGather란!
//    1) 기본적으로는 CGNet::Socket::CTCPServer와 동일하나 Socket의 Sender부분만
//       No Gather 버전이 적용된 것이다.
//    2) 전송이 잦지 않은 Socket의 경우 No Gather버전이 더 용량과 처리 부하 면에서
//       효율적이다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class THEAD=CGNet::IO::Packetable::PRIMITIVE<uint32_t>>
class CTCPServerNoGather :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::Socket::CTCPNoGather<THEAD>,		// (@) TCP Socket
	public						CGNet::IO::AddOn::NSocketSustain		// (@) Socket Sustainer
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCPServerNoGather()										{}
	virtual	~CTCPServerNoGather()										{}
};


}
}