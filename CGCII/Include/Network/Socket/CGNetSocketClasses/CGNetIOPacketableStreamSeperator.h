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
* @class NStreamSeperator<class TNCHAR=_CHAR>
*
* @ingroup CGNet::IO::Packetable
*
* @brief Web�� ���� ���ڿ� Stream �޽��� ó���� ���� Packetable Ŭ����
*
*   Web�� ���� ���ڿ��� �� Stream �޽����� ó���� ���� Packetable Ŭ������.
*   ���۵Ǿ� ���� Stream �����͸� ���ڿ��� ������('/r/n')�� Sequencial Detect�Ͽ�
*   �޽����� ������ ProcessMessage()�� ������ �ش�.
*   �⺻������ �� ����� �����ڸ� ã�� ���� ��� �����͸� ���ʷ� �о� �񱳸� �ؾ�
*   �ϹǷ� �ٸ� ��Ŀ� ���� ���ϰ� ���� ���.
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Packetable
{

template <class TNCHAR=_CHAR>
class NStreamSeperator :
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
	// 1) Get Line
	virtual	int					ProcessFindSeperator(_In_ TNCHAR* p_strPos, _In_ const TNCHAR* p_strEnd);

	// 2) ProcessPacket/PreMessage
	virtual	size_t				ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;
	virtual	void				ProcessPreMessage(CGNETMSG& /*_Msg*/)	{}

	// 3) Reset
	virtual	void				ResetPacketable() override				{}
};


template <class TNCHAR>
int NStreamSeperator<TNCHAR>::ProcessFindSeperator(_In_ TNCHAR* p_strPos, _In_ const TNCHAR* p_strEnd)
{
	for(int iLength=0; p_strPos<p_strEnd; ++iLength)
	{
		// Check) Seperator�� ã���� ���!!! 
		if(*(p_strPos++)=='\r')
		{
			return	iLength;
		}
	}

	// Return) ã�� ���ߴ�!
	return	0;
}


template <class TNCHAR>
size_t NStreamSeperator<TNCHAR>::ProcessPacket(_Inout_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr)
{
	//-----------------------------------------------------------------
	// Check) Debug�� ���� �߸��� ���� �˻�.
	//-----------------------------------------------------------------
	// 1) _Buffer.buf�� 0�̾�� �ȵȴ�.
	CGASSERT_ERROR(_Buffer.buf != nullptr)

	// 2) _Buffer->len�� 0�̾�� �ȵȴ�.
	CGASSERT_ERROR(_Buffer.len!= 0)


	//-----------------------------------------------------------------
	// 1. ���۵Ǿ� ���� �� ó��
	//-----------------------------------------------------------------
	// Declare) ó���� ��Ŷ ���� ó���� ����...
	int			countMessage	 = 0;

	// Declare) �ӽ� CGNETMSG�� �����.
	CGNETMSG	msg;

	msg.Buffer		 = CCGBuffer(CGD::buffer(_Buffer.buf, 0), _Buffer.get_reference());
	msg.pSockAddr	 = _pSockAddr;

	// Loop) Buffer�� ������ Seperator�� �����ϴ��� �˻��Ѵ�.
	TNCHAR*	pPos	 = (TNCHAR*)(_Buffer.buf);
	TNCHAR*	pEnd	 = (TNCHAR*)(_Buffer.buf+_Buffer.len);

	try
	{
		while(pPos<pEnd)
		{
			// 1) Seperator�� ã�´�.
			_Buffer.len	 = ProcessFindSeperator(pPos, pEnd);

			// Check) ã�� �������� ���⼭ ������.
			BREAK_IF(_Buffer.len==0);

			// 2) ã������ ProcessPreMessage()�� ȣ���Ѵ�.
			ProcessPreMessage(msg);
		
			// 3) IMessageable�� �޽����� �����Ѵ�.
			ProcessMessage(msg);

			// 4) ó���� Message���� ������Ų��.
			++countMessage;

			// 5) ���ο� �������� �����Ѵ�.
			_Buffer.buf	+= (_Buffer.len+1)*sizeof(TNCHAR);

			// Check) ������ ����Ǿ����� �ٷ� ������.
			BREAK_IF(GetSocketHandle()==INVALID_SOCKET);
		}
	}
	catch(...)
	{
		// Statistiscs) �� ������ ó���� Packet�� ���ó���� �Ѵ�.
		Statistics_OnReceiveMessage(countMessage);

		// Reraise) 
		throw;
	}

	// Statistics) Receive Message ��
	Statistics_OnReceiveMessage(countMessage);


	//-----------------------------------------------------------------
	// 2. ���� ����...
	//-----------------------------------------------------------------
	// 1) ���� Message�� �����Ѵ�.
	_Buffer.len		 = static_cast<uint32_t>((reinterpret_cast<char*>(pPos))-_Buffer.buf);

	// 2) ���� Message�� ũ�⸦ ���� ũ�⿡ 1024�ںз��� �� Ȯ���ϵ��� �Ѵ�.
	int		iSizeMessage	 = static_cast<int>(_Buffer.len+sizeof(_CHAR)*1024);

	// Return) ���� Message�� ũ�⸦ return�Ѵ�.
	return	MIN(iSizeMessage, 65536);
}


}
}
}
