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
* @class NStreamFixed<IMESSAGESIZE>
*
* @ingroup CGNet::IO::Packetable
*
* @brief ������ ũ��� �߶� �޽����� �����ϴ� Stream(TCP)�� Packetable Ŭ����
*
*   ������ ũ��� �߶� �޽����� ����� ProgressMessage()�� �ѱ�� Packtable Ŭ���� 
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Packetable
{

template<int IMESSAGESIZE>
class NStreamFixed :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISocket,						//     Packetable
	virtual public				CGNet::IO::IPacketable,					//     Packetable
	virtual protected			ICGMessageable,							//     Messageable
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual	void				ProcessPreMessage(CGNETMSG& /*_Msg*/)	{}
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;

	virtual	void				ResetPacketable() override				{}
};

template<int IMESSAGESIZE>
size_t NStreamFixed<IMESSAGESIZE>::ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)
{
	//-----------------------------------------------------------------
	// ����) ProcessPacket
	//
	// - �ش� �޸� ������ ������ �ؼ��ؼ� �ϳ��� Message������ �߶� 
	//   ó���ϴ� �۾��� �����ϰ� �ȴ�. 
	//   �Ϲ������� head�� ũ��� ���� �� 2Byte�� ��ϵǸ� �״��� 2Byte��
	//   Command�� ���ȴ�. �� ���Ŀ� �ʿ信 ���� �پ��� ũ���� ������
	//   �پ �����ȴ�.
	//-----------------------------------------------------------------


	//-----------------------------------------------------------------
	// Check) Debug�� ���� �߸��� ���� �˻�.
	//-----------------------------------------------------------------
	// 2) _Buffer.buf�� 0�̾�� �ȵȴ�.
	CGASSERT(_Buffer.buf != nullptr, 0)

	// 3) _arrayBuffer->len�� 0�̾�� �ȵȴ�.
	CGASSERT(_Buffer.len != 0, 0)


	//-----------------------------------------------------------------
	// 1. ���۵Ǿ� ���� �� ó��
	//-----------------------------------------------------------------
	// Declare)
	int			countMessage	 = 0;

	// Declare) �ӽ� CCGBuffer�� �����.
	CGNETMSG	msg;

	msg.Buffer		 = CCGBuffer(CGD::buffer(_Buffer.buf, IMESSAGESIZE), _Buffer.get_reference());
	msg.pSockAddr	 = _pSockAddr;

	// Loop) RemainedSize�� GetSizeOfPacketHead()���� ������ ����.
	uint32_t	RemainedSize	 = _Buffer.len;

	try
	{
		while(RemainedSize >= IMESSAGESIZE)
		{
			// 1) ���Լ� ProcessPreMessage()�� ȣ���Ѵ�.
			ProcessPreMessage(msg);
		
			// 2) Message�� ó���Ѵ�.
			ProcessMessage(msg);

			// 3) Paket���� ������Ų��.
			++countMessage;

			// 4) Message Data�� �̵���Ų��.
			msg.Buffer.buf		+= IMESSAGESIZE;
			RemainedSize		-= IMESSAGESIZE;

			// Check) ������ ����Ǿ����� �ٷ� ������.(������ ������ ������ �� �ٷ� �����Ű�� ����)
			BREAK_IF(GetSocketHandle()==INVALID_SOCKET);
		}
	}
	catch(...)
	{
		// Statistiscs) �̶����� ó���� Packet�� ���ó���� �Ѵ�.
		Statistics_OnReceiveMessage(countMessage);

		// Reraise) 
		throw;
	}

	// Statistics) Receive Message���� ������.
	Statistics_OnReceiveMessage(countMessage);


	//-----------------------------------------------------------------
	// 2. ���� ����...
	//-----------------------------------------------------------------
	// 1) ���� Message �����Ѵ�.
	_Buffer.buf			 = msg.Buffer.buf;
	_Buffer.len			 = RemainedSize;
	
	// Return) ���� Message�� ũ�⸦ return�Ѵ�.
	return	static_cast<size_t>(msg.Buffer.len);
}


}
}
}