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
/*!
* @class IPacketable
*
* @ingroup CGNet::IO::Packetable
*
* @brief 데이터를 메시지로 잘라주는 역할을 하는 클래스
*
*  ProcessPacket으로 넘겨져온 데이터를 메시지로 구분해 전달해주는 역할을 하는 클래스의
*  인터페이스(Interface) 객체이다.
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IPacketable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	// 1) 데이터를 처리하는 함수.
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;

	// 2) IPacketable을 Reset하는 함수.
	virtual	void				ResetPacketable() PURE;
};


}
}