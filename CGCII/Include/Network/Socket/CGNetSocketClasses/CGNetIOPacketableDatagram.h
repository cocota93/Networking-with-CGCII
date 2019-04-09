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
* @class NDatagram
*
* @ingroup CGNet::IO::Packetable
*
* @brief Datagram(UDP)용 Packetable로 받은 데이터를 그대로 ProcessMessage()로 전달한다.
*
*  Datagram(UDP)과 같이 블록으로 끊어져 들어오는 데이터용 Packetable이다.
*  아무것도 하지 않고 그냥 ProcessMessageable()로 받은 데이터를 그대로 넘겨 주기만 한다.
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Packetable
{

class NDatagram : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IPacketable,					//     Packetable
	virtual protected			ICGMessageable,							//     Messageable
	virtual protected			CGNet::IO::ISendRequest,					// (I) Sendable
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _psockAddr) override;

	virtual	void				ResetPacketable() override				{}
};


}
}
}