#include "pch.h"
#include "../../../CGCII/Include/CGNetSocketTemplates.h"

int received = 0;

class CSocket : public CGNet::Socket::CTCP<>
{
	virtual int OnMessage_A(CGD::buffer&);
	virtual void OnConnect(CGNet::IO::IConnective*) override
	{
		printf("Connected\n");
	}

	virtual void OnDisconnect(uint32_t) override
	{
		printf("Disconnected\n");
	}

	virtual int OnMessage(CGMSG& _Msg) override
	{
		if (_Msg.message == CGMESSAGE::SYSTEM::MESSAGE)
		{
			CGNETMSG&	rMSG = (CGNETMSG&)_Msg;
			CGD::buffer	bufTemp = rMSG.Buffer;
			bufTemp.extract<uint32_t>(); // 길이
			uint32_t	uMessage = bufTemp.extract<uint32_t>();
			switch (uMessage)
			{
			case	1:
				OnMessage_A(bufTemp);
				break;
			}
		}
		received++;
		return	0;
	}
};

int CSocket::OnMessage_A(CGD::buffer& _Msg) {

	// @) 읽어내기 위해 buffer에 임시로 복사.
	//CGD::buffer	bufTemp = _Msg;

	// @) Message 구조체에서 전송되어온 버퍼에서 데이터를 읽는다.
	auto	a = _Msg.extract<int>();
	auto	b = _Msg.extract<int>();
	printf("%d, %d\n", a, b);
	return 0;
}

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
