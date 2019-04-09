#include "pch.h"
#include "../../../CGCII/Include/CGNetSocketTemplates.h"


namespace CGMESSAGE
{
	const uint32_t	SEND_A = 0x00000020;
	const uint32_t	SEND_B = 0x00000021;
}

class CSocketClient :
	public CGNet::Socket::CTCP<>,
	public CGNet::IO::Connector::NTCP
{
	virtual void OnConnect(CGNet::IO::IConnective* _pConnective) override
	{
		printf("Connected\n");
	}
	virtual void OnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t  _Reason) override
	{
		printf("Fail to Connect\n");
	}
	virtual void OnDisconnect(uint32_t) override
	{
		printf("Disconnected\n");
	}
	virtual int OnMessage(CGMSG& _Msg) override
	{
		printf("Message Received\n");

		return	0;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	CGExecutor::Default::InitInstance(CGEXECUTOR_NOTHREAD);
	auto	pSocket = NEW<CSocketClient>();
	pSocket->Connect("Localhost", 65535);


	for (;;)
	{
		if (_kbhit())
		{
			int	ch = _getch();
			if (ch == 27)
				break;
			else if (ch == 'a' || ch == 'A')
				CCGBuffer(MEM_POOL_ALLOC(32)) << uint32_t(12) << uint32_t(CGMESSAGE::SEND_A) << int(100) >> SEND(pSocket);
			else if (ch == 'b' || ch == 'B')
				CCGBuffer(MEM_POOL_ALLOC(32)) << uint32_t(8) << uint32_t(CGMESSAGE::SEND_B) >> SEND(pSocket);
		}
		CGExecutor::Default::RunExecutor();
		Sleep(1);
	}
	pSocket->CloseSocket();
	CGExecutor::Default::RunExecutor();


	return 0;
}
