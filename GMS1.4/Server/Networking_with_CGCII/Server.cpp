#include "pch.h"
#include "SocketTCP.h"
#include "OnConnect.cpp"
#include "OnMessage.cpp"
#include "OnDisconnect.cpp"
#include "Ping.cpp"

int _tmain(int, _TCHAR*[])
{
	auto	server = NEW<CGNet::CAcceptor<CSocketTCP>>();
	server->Start(65535);
	
	for (;;)
	{
		if (_kbhit())
		{
			int	ch = _getch();
			if (ch == 27)
				break;
		}
		Sleep(1);
	}
	return 0;
}
