#include "pch.h"
#include "../../../CGCII/Include/CGNetSocketTemplates.h"


namespace CGMESSAGE
{
	const uint32_t	SEND_A = 0x00000020;
	const uint32_t	SEND_B = 0x00000021;
}

class CSocketClient :
	public CGNet::Socket::CTCP<>,
	public CGNet::IO::Connector::NTCP	// (@) Client측에서는 Connector를 상속받아야 한다.
{
	// 1) 접속 시 호출되는 Hook함수
	virtual void OnConnect(CGNet::IO::IConnective* /*_pConnective*/) override
	{
		printf("Connected\n");
	}

	// 2) 접속 실패 시 호출되는 Hook함수  (@) 클라이언트에서는 접속에 실패할 수도 있으니 이 훅함수를 하나 더 추가했다!!
	virtual void OnFailConnect(CGNet::IO::IConnective* /*_pConnective*/, uint32_t  /*_Reason*/) override
	{
		printf("Fail to Connect\n");
	}

	// 3) 접속 종료 시 호출되는 Hook함수
	virtual void OnDisconnect(uint32_t) override
	{
		printf("Disconnected\n");
	}

	// 4) 메시지가 전송되어 왔을 때 호출 되는 함수.
	virtual int OnMessage(CGMSG& /*_Msg*/) override
	{
		printf("Message Received\n");

		return	0;
	}
};

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	// 1) 내부적 Thread를 만들지 않도록 한다.
	//    (이것을 하지 않으면 서버와 같이 Multi Thread로 동작한다.)
	CGExecutor::Default::InitInstance(CGEXECUTOR_NOTHREAD);

	// 2) Socket을 생성한다.
	auto	pSocket = NEW<CSocketClient>();

	// 3) '127.0.0.1' 호스트에 21000번 포트로 접속을 시도한다.
	//     주의) Connect()함수는 Blocking Mode로 동작하지 않는다.
	//pSocket->Connect("127.0.0.1", 21000);
	pSocket->Connect("Localhost", 21000);

	// Trace) 
	printf("  [설명] A키-CGMESSAGE::SEND_A 전송\n");
	printf("  [설명] B키-CGMESSAGE::SEND_B 전송\n");
	printf("  [설명] ESC-종료\n");

	// 4) 클라이언트 메인 루프
	for (;;)
	{
		// - Key를 눌렀을 경우 key값을 읽어 처리한다.
		if (_kbhit())
		{
			// - Key를 읽는다.
			int	ch = _getch();

			// - ESC키를 누르면 접속을 종료한다.
			if (ch == 27)
			{
				break;
			}
			// - A키 누르면 Message B를 전송한다.
			else if (ch == 'a' || ch == 'A')
			{
				CCGBuffer(MEM_POOL_ALLOC(32)) << uint32_t(12) << uint32_t(CGMESSAGE::SEND_A) << int(100) >> SEND(pSocket);
			}
			// - B키 누르면 Message B를 전송한다.
			else if (ch == 'b' || ch == 'B')
			{
				CCGBuffer(MEM_POOL_ALLOC(32)) << uint32_t(8) << uint32_t(CGMESSAGE::SEND_B) >> SEND(pSocket);
			}
		}

		// 5) Socket I/O Execution
		//    CGEXECUTOR_NOTHREAD 옵션으로 초기화를 하였으므로 반드시 
		//    따로 RunExecutor()함수를 호출해 주어야 한다. 이때 Socket I/O가 처리된다.
		CGExecutor::Default::RunExecutor();

		// 6) CPU를 너무 많이 먹으므로...
		Sleep(1);
	}

	// 7) Socket의 접속을 끊는다.
	pSocket->CloseSocket();

	// 8) CloseSocket 이후 I/O를 처리하기 위해...
	CGExecutor::Default::RunExecutor();


	return 0;
}
