#include "pch.h"
#include "../../../CGCII/Include/CGNetSocketTemplates.h"

int received = 0;

class CSocket : public CGNet::Socket::CTCP<>
{
	virtual void OnConnect(CGNet::IO::IConnective*) override
	{
		printf("Connected\n");
	}

	virtual void OnDisconnect(uint32_t) override
	{
		printf("Disconnected\n");
	}

	virtual int OnMessage(CGMSG& /*_Msg*/) override
	{
		received++;
		return	0;
	}
};

int _tmain(int, _TCHAR*[])
{
	auto	pacceptor = NEW<CGNet::CAcceptor<CSocket>>();
	pacceptor->Start(65535);
	printf("Server Opened\n");
	for (;;)
	{
		if (_kbhit())
		{
			int	ch = _getch();
			if (ch == 27)
				break;
			else if (ch == 'a' || ch == 'A')
				printf("received : %d \n", received);
		}
		Sleep(1);
	}
	return 0;
}
