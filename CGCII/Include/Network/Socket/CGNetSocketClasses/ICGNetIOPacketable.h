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
* @class IPacketable
*
* @ingroup CGNet::IO::Packetable
*
* @brief �����͸� �޽����� �߶��ִ� ������ �ϴ� Ŭ����
*
*  ProcessPacket���� �Ѱ����� �����͸� �޽����� ������ �������ִ� ������ �ϴ� Ŭ������
*  �������̽�(Interface) ��ü�̴�.
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
	// 1) �����͸� ó���ϴ� �Լ�.
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;

	// 2) IPacketable�� Reset�ϴ� �Լ�.
	virtual	void				ResetPacketable() PURE;
};


}
}