#include "pch.h"
#include "../../../CGCII/Include/CGNetSocketTemplates.h"
#include <iostream>

int connected = 0;
int disconnected = 0;

using namespace std;

class CSocket :
	public CGNet::Socket::CTCP<>,
	public CGNet::IO::Connector::NTCP
{
public:
	virtual void SendMessages();
	virtual void OnConnect(CGNet::IO::IConnective* _pConnective) override
	{
		connected++;
		SendMessages();
	}
	virtual void OnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t  _Reason) override
	{
		disconnected++;
	}
	virtual void OnDisconnect(uint32_t) override
	{
		disconnected++;
	}
	virtual int OnMessage(CGMSG& _Msg) override
	{
		printf("Message Received\n");

		return	0;
	}
};

void CSocket::SendMessages() {
	CCGBuffer tempBuffer = MEM_POOL_ALLOC(1024); // Alloc the buffer
	tempBuffer.append<uint32_t>(); // length init
	tempBuffer.append<uint32_t>(1); // type
	tempBuffer.append<int>(1024); // values
	tempBuffer.append<int>(1212); // values
	tempBuffer.front<uint32_t>() = tempBuffer.len; // write length
	Send(tempBuffer); // Send
}

int _tmain(int argc, _TCHAR* argv[])
{
	CGExecutor::Default::InitInstance(CGEXECUTOR_NOTHREAD);
	CGPTR<CSocket> clients[1];
	for (int i = 0; i < 1; i++) {
		auto test = NEW<CSocket>();
		test->Connect("Localhost", 65535);
		CGExecutor::Default::RunExecutor();
		clients[i] = test;
	}
	CGExecutor::Default::RunExecutor();
	cout << "Connected : " << connected << endl;
	cout << "Disconnected : " << disconnected << endl;
	for (;;)
	{
		if (_kbhit())
		{
			int	ch = _getch();
			if (ch == 27)
				break;
			else if (ch == 's' || ch == 'S') {
				for (int i = 0; i < 1; i++) {
					clients[i]->SendMessages();
					CGExecutor::Default::RunExecutor();
				}
			}
		}
		CGExecutor::Default::RunExecutor();
		Sleep(1);
	}


	return 0;
}
