#include "pch.h"
#include "CGNetSocketTemplates.h"

int connected = 0;
int disconnected = 0;

class CSocket :
	public CGNet::Socket::CTCP<>,
	public CGNet::IO::Connector::NTCP
{
public:
#pragma region public
	void SendMessageTest();
#pragma endregion

protected:
#pragma region protected
	virtual void OnConnect(CGNet::IO::IConnective* _pConnective) override
	{
		connected++;
		SendMessageTest();
		//printf("Connected\n");
	}
	virtual void OnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t  _Reason) override
	{
		disconnected++;
		//printf("Fail to Connect\n");
	}
	virtual void OnDisconnect(uint32_t) override
	{
		disconnected++;
		//printf("Disconnected\n");
	}
	virtual int OnMessage(CGMSG& /*_Msg*/) override
	{
		printf("Message Received\n");
		return	0;
	}
#pragma endregion
};

void CSocket::SendMessageTest()
{
	CCGBuffer	tempBuffer = MEM_POOL_ALLOC(64); // 버퍼 할당
	tempBuffer.append<uint32_t>(); // 길이 공간 만들기
	tempBuffer.append<uint32_t>(1); // 타입
	tempBuffer.append<int>(10); // 데이터
	tempBuffer.front<uint32_t>() = tempBuffer.len; // 길이 작성
	Send(tempBuffer);
}


int _tmain(int argc, _TCHAR* argv[])
{
	CGExecutor::Default::InitInstance(CGEXECUTOR_NOTHREAD);
	for (int i = 0; i < 500; i++) {
		auto	pSocket = NEW<CSocket>();
		pSocket->Connect("Localhost", 65535);
		CGExecutor::Default::RunExecutor();
	}

	printf("%d, %d", connected, disconnected);
	for (;;)
		Sleep(1);
	/*for (;;)
	{
		if (_kbhit())
		{
			int	ch = _getch();
			if (ch == 27)
				break;
			if (ch == 'a' || ch == 'A') {
				pSocket -> SendMessageTest();
				printf("A is pressed\n");
			}
		}
		CGExecutor::Default::RunExecutor();
		Sleep(1);
	}
	pSocket->CloseSocket();*/
	CGExecutor::Default::RunExecutor();
	return 0;
}
