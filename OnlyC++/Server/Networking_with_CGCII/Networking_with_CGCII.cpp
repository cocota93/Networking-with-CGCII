#include "pch.h"
#include "../../../CGCII/Include/CGNetSocketTemplates.h"


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
		printf("Message Received\n");

		return	0;
	}
};

int _tmain(int, _TCHAR*[])
{
	auto	pacceptor = NEW<CGNet::CAcceptor<CSocket>>();
	pacceptor->Start(65535);
	printf("Server Opened\n");
	while (_getch() != 27);
	return 0;
}
