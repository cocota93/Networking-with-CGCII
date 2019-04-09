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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::IO::Sender::NStream
//
// 1. CGNet::IO::Sender::CStream은~
//    1) 가장 일반적인 Sender로 CGNet::IO::ISendRequest의 RequestSend()함수를 호출해
//       준다.
//    2) 한번의 전송에 한번의 Overlapped I/O를 걸어 Send()를 수행하는 Sender로
//       가장 일반적이고 기본적인 Sender이다. 
//       하지만 작은 Message를 대량으로 한꺼번에 보내게 되면 성능이 많이 떨어진다.
//       만약 Message를 대량으로 한꺼번에 효율적으로 전송하고 싶다면 NStreamGather
//       클래스를 사용하길 권장한다.
//
// 2. 핵심함수!
//    1) bool Send(const CCGBuffer& _Buffer);
//       말 그대로 전송을 수행하는 함수이다. CCGBuffer에 전송할 Message를 넣고 Send()
//       함수를 호출하며 그 버퍼를 넘기면 전송이 된다.
// 
//    2) virtual bool ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);
//       재정의가능한 함수로 기본 설정은 무조건 true를 리턴하도록 설정되어 있다.
//       이 함수는 Send()함수를 호출하기 전 Send()함수로 넘겨진 CCGBuffer를 전달하게
//       되는데 이때 사용자가 Message가 바르게 되었는지 확인하는 코드를 작성하여 넣을
//       수 있다. 이 함수가 true라면 정상적으로 작성된 Message이고 false면
//       잘못된 Message로 가정한다.
//       일반적으로 이 함수는 Debug모드에서만 동작하도록 한다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sender
{

class NStream : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISendRequest,					// (I) SendRequest
	virtual public				CGNet::IO::ISender,						//     Sender Stream
	virtual protected			CGNet::IO::ISocket,						// (I) Socket
	virtual public				CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;
	template <int ICOUNT>
			bool				Send(_In_ const CCGBuffer (&_arrayBuffer)[ICOUNT]);
	template <class TITERATOR>
			bool				Send(_In_ TITERATOR _begin, _In_ TITERATOR _End);


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);

public:
			bool				ProcessRequestSend(_In_ const CCGBuffer& _Buffer, int _countMessage);
			bool				ProcessRequestSendArray(_In_ const CCGBuffer* _Buffer, int _countBuffer, int _countMessage);
};

template <int ICOUNT>
bool NStream::Send(_In_ const CCGBuffer(&_arrayBuffer)[ICOUNT])
{
	return ProcessRequestSendArray(_arrayBuffer, ICOUNT, 1);
}

template <class TITERATOR>
bool NStream::Send(_In_ TITERATOR _begin, _In_ TITERATOR _End)
{
	// Check)
	CGASSERT_ERROR(false);

	// Return) 
	return	false;
}


}
}
}