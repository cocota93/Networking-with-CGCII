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
/*!
 * @class NDatagramResponse
 *
 * @ingroup CGNet::IO::Packetable
 *
 * @brief NDatagramResponse�� ACK ���� ����� �߰��� ���̴�.
 *
 *  NDatagram�� ���� ���� �����͸� �״�� ProcessMessage()�� ������ ���ش�.
 *  �� Reliable �޽����� �޾��� �� ACK�� ���� �������ִ� ����� ���� ���̴�. 
 *
 */
 //-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Packetable
{

class NDatagramResponse : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IPacketable,					//     Packetable
	virtual protected			ICGMessageable,							//     Messageable
	virtual protected			CGNet::IO::ISendRequest,					// (I) Sendable
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			bool				SendACK(_In_ uint32_t _Serial, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;

	virtual	void				ResetPacketable() override				{}
};


}
}
}