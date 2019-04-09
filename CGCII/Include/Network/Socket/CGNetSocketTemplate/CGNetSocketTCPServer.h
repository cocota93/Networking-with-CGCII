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
// CGNet::Socket::CTCPServer
//
// 1. CGNet::Socket::CTCPServer란!
//    1) 기본적으로는 CGNet::Socket::CTCP나 CTCPQueue와 동일하다. 그러나 여기에 
//       일정 시간의 송수신이 없을 경우 자동으로 접속을 끊어버리는 동작을 수행할 
//       Add-On을 추가한 것이다.
//    2) 기본적으로 이런 형태는 Server에서 많이 사용된다고 할 수 있다.
//
//       @ 물론 이렇게 정의된 형태 외에 다양한 형태를 직접 조합하여 사용가능하다.
//         이 Template은 많이 사용하기 때문에 미리 만들어 놓은 것에 불과하다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class TCLASS, class THEAD=CGNet::IO::Packetable::PRIMITIVE<uint32_t>>
class CTCPServer :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::Socket::CTCPDispatchable<TCLASS, THEAD>,// (@) TCP Socket
	public						CGNet::IO::AddOn::NSocketSustain		// (@) Socket Sustainer
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCPServer()												{}
	virtual	~CTCPServer()												{}
};


}
}