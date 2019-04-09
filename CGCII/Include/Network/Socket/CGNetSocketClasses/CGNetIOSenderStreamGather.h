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
// CGNet::IO::Sender::NStreamGather
//
// 1. CGNet::IO::Sender::NStreamGather란!
//    1) Stream(TCP)용 Sender이다. 
//    2) 기본적인 Stream Sender의 경우 한번의 전송에 한번의 Overlapped I/O를 
//       걸게 된다. 
//       하지만 한꺼번에 많은 Send를 수행하게 되면 한꺼번에 너무 많은 Overlapped I/O를 
//       걸게 되고 이로 인해 성능의 저하가 나타날수 있다. 
//       이 NStreamGather는 Send를 한꺼번에 많이 수행하더라도 
//       한꺼번에 번에 하나 씩의 OVerlapped I/O를 걸게 하는 Sender이다.
//    3) Send를 호출하면 Send 전송중이 아닐 때는 Send를 위한 Overlapped I/O를
//       건다. 하지만 전송중인 상태라 아직 Send가 완료되지 않은 상태라면 
//       일단 전송한 Message를 Queuing을 한 후 Send함수를 종료한다.
//       전송 중인 Send가 완료되었을 때 Queuing된 것을 전송하게 된다.
//
// 2. CGNet::IO::Sender::CStreamGather의 특징
//    1) 한꺼번에 대규모 Send를 하는 형태일 경우에만 이 Sender의 성능이 유효하다.
//        특히 작은 크기의 Message를 대량으로 전송할 경우 더욱 유효하다.
//         만약에 Send의 전송이 빈번하지 않거나 전송하는 Message의 크기가 크다면
//        오히려 더 비효율적일 수도 있다.
//        이럴 경우 그냥 CGNet::IO::Sender::NStream를 사용하는 것이 더 효율적이다.
//        (일반적으로 이 Sender가 가장 효율적이다.)
//    2) Queuing하는 방법을 Array로 된 Buffer를 두 조를 마련하여 한쪽 버퍼에는 
//       현재 전송중인 Message 버퍼들을 그리고 다른 하나 조에는 아직 전송 되지
//       않고 Queuing된 Message를 저장한다.
//       전송중인 Message 버퍼들들이 모두 전송된 후 Queuing된 Message 버퍼들을
//       전송하며 이때 Queuing된 Message 버퍼들은 전송중인 Message 버퍼로 바뀌며
//       Queueing된 Message버퍼들은 비워진다.
//       
//    3) 하지만 주의해야할 점은 Queuing에는 한계가 있어서 일정 횟수 이상의 Message
//       혹은 일정 횟수 이상의 크기 이상으로 Queuing되면 Overflow가 발생하며
//       Send()의 리턴값이 false가 된다. 
//       이 버퍼량은 소켓을 생성하기 전에 아래 함수를 통해 설정할 수 있다.
//
//        static	void SetDefaultMaxDepthOfSendBuffer(int iMax);
//        static	int  GetDefaultMaxDepthOfSendBuffer();
//
//        static	void SetDefaultMaxQueuedBytes(int iMax);
//        static	int  GetDefaultMaxQueuedBytes();
//
//        위 함수는 static함수로 이 함수 이후 생성되는 모든 Sender::NStreamGather에
//        적용된다.
//
//        int		GetMaxDepthOfSendBuffer() const;
//        uint32_t  GetMaxQueuedBytes() const;
//
//        위 함수를 사용하여 Socket의 Queuing가능한 SendBuffer 최대 갯수와 바이트수를
//        얻을 수 있다.
//
// 3. 핵심함수!
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
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sender
{

class NStreamGather :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISendRequest,				// (I) SendRequest
	virtual public				CGNet::IO::ISender,						//     Sender Stream
	public						CGNet::IO::ISendCompletor,				//     SendCompletor
	virtual protected			CGNet::IO::IConnectable,				// (I) Socket
	virtual public				CGNet::IO::IReceivable,					// (I) Receivable
	virtual public				ISenderClosser							//     Sender Closer
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NStreamGather();
			~NStreamGather();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send 함수들
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;
	template <int ICOUNT>
			bool				Send(_In_ const CCGBuffer (&_arrayBuffer)[ICOUNT]);
	template <class TITERATOR>
			bool				Send(_In_ TITERATOR _begin, _In_ TITERATOR _End);
	template <class T>
			bool				Send(const T& _Data);

	// 2) Send Multiple Buffers
			bool				Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB);
			bool				Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB, _In_ const CCGBuffer& _bufC);
			bool				Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB, _In_ const CCGBuffer& _bufC, _In_ const CCGBuffer& _bufD);
			bool				Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB, _In_ const CCGBuffer& _bufC, _In_ const CCGBuffer& _bufD, _In_ const CCGBuffer& _bufE);

	// 2) Sustain Torrence 관련 함수.
			int					GetMaxDepthOfSendBuffer() const			{	return m_iMaxDepthOfSendBuffer;}
			void				SetMaxDepthOfSendBuffer(_In_ int _iDepth);
			uint32_t			GetMaxQueuedBytes() const				{	return m_bytesMaxQueued;}
			void				SetMaxQueuedBytes(_In_ int _iSize)		{	m_bytesMaxQueued=_iSize;}

	// 3) Default Gather Queue Depth 설정
	static	void				SetDefaultMaxDepthOfSendBuffer(_In_ int iMax);
	static	int					GetDefaultMaxDepthOfSendBuffer();

	static	void				SetDefaultMaxQueuedBytes(_In_ int iMax);
	static	int					GetDefaultMaxQueuedBytes();


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) Send함수 수행를 실패했을 때 호출하는 함수.
	virtual	void				OnFailSending()							{}

	// 2) Validate Message
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Sender를 Reset하는 함수.
	virtual	void				ResetSendCompletor() override;

	// 2) Completion 되었을 때 수행되는 함수.(재정의용)
	virtual	void				ProcessCompleteSend(_In_ uintptr_t _Return, _In_ size_t _Transfered) override;
	virtual	void				ProcessCloseSender() override;

public:
			bool				ProcessRequestSend(_In_ const CCGBuffer& _Buffer, int _countMessage);
			bool				ProcessRequestSendArray(_In_ const CCGBuffer* _Buffer, int _countBuffer, int _countMessage);

private:
	struct QUEUE_SENDING
	{
	public:
			QUEUE_SENDING();
			~QUEUE_SENDING();

			void				reset();
			void				swap(_Inout_ QUEUE_SENDING& _rMessage);
			void				recreate(_In_ int p_iMaxDepth);

	public:
			CGD::buffer*		vectorWSABuf;
			ICGReferenceable**	vectorOriginal;
			int					iQueued;
			int					countMessage;
	};

private:
	// 3) Default Values
	static	int					m_iDefaultMaxDepthOfSendBuffer;
	static	int					m_iDefaultMaxQueuedBytes;

	// 4) TwinQueue(WSABuffer과 Original을 보관한다.
			QUEUE_SENDING		m_queueQueued;
			QUEUE_SENDING		m_queueSending;
			char*				m_ptrQueuedBufferTail;

			uint32_t			m_byteQueued;
			uint32_t			m_bytesMaxQueued;
			int					m_iMaxDepthOfSendBuffer;

	// 5) Critical Section
			LOCKABLE<>			m_csSendQueue;

	// 6) 내부적으로 사용되는 함수들...
			bool				QueueBuffer(_In_ const CCGBuffer& _Buffer, int _countMessage);

	// Nested Class)
			class CSendCompletorCloser;
};

inline bool NStreamGather::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) Packet Validate Check한다.
#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&_Buffer, 1), false);
#endif

	// Return) 
	return	ProcessRequestSend(_Buffer, 1);
}

template <int ICOUNT>
bool NStreamGather::Send(_In_ const CCGBuffer(&_arrayBuffer)[ICOUNT])
{
	return ProcessRequestSendArray(_arrayBuffer, ICOUNT, 1); 
}

template <class TITERATOR>
bool NStreamGather::Send(_In_ TITERATOR _begin, _In_ TITERATOR _End) 
{
	for(auto iter=_begin; iter!=_End; ++iter)
	{
		Send(iter);
	}

	// Return) 
	return	false;
}

inline bool NStreamGather::Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB)
{
	// 1) Buffer List를 만든다.
	CCGBuffer listBuf[]	 = {_bufA, _bufB};

	// Check) Packet Validate Check한다.
#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(listBuf, 2), false);
#endif

	// 2) 
	ProcessRequestSend(_bufA, 0);
	ProcessRequestSend(_bufB, 1);

	// Return)
	return	true;
}

template <class T>
bool NStreamGather::Send(const T& _Data)
{
	// 1) Buffer를 할당받는다.
	CCGBuffer bufTemp	 = MEM_POOL_ALLOC(sizeof(T));

	// 2) 붙인다.
	bufTemp.append<T>(_Data);

	// Check) Packet Validate Check한다.
#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&bufTemp, 1), false);
#endif

	// 3) 전송한다.
	return	ProcessRequestSend(&bufTemp, 1);
}


inline bool NStreamGather::Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB, _In_ const CCGBuffer& _bufC)
{
	// 1) Buffer List를 만든다.
	CCGBuffer listBuf[]	 = {_bufA, _bufB, _bufC};

	// Check) Packet Validate Check한다.
#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(listBuf, 3), false);
#endif

	// 2) 
	ProcessRequestSend(_bufA, 0);
	ProcessRequestSend(_bufB, 0);
	ProcessRequestSend(_bufC, 1);

	// Return)
	return	true;
}

inline bool NStreamGather::Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB, _In_ const CCGBuffer& _bufC, _In_ const CCGBuffer& _bufD)
{
	// 1) Buffer List를 만든다.
	CCGBuffer listBuf[]	 = {_bufA, _bufB, _bufC, _bufD};

	// Check) Packet Validate Check한다.
#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(listBuf, 4), false);
#endif

	// 2) 
	ProcessRequestSend(_bufA, 0);
	ProcessRequestSend(_bufB, 0);
	ProcessRequestSend(_bufC, 0);
	ProcessRequestSend(_bufD, 1);

	// Return)
	return	true;
}

inline bool NStreamGather::Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB, _In_ const CCGBuffer& _bufC, _In_ const CCGBuffer& _bufD, _In_ const CCGBuffer& _bufE)
{
	// 1) Buffer List를 만든다.
	CCGBuffer listBuf[]	 = {_bufA, _bufB, _bufC, _bufD, _bufE};

	// Check) Packet Validate Check한다.
#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(listBuf, 5), false);
#endif

	// 2) 
	ProcessRequestSend(_bufA, 0);
	ProcessRequestSend(_bufB, 0);
	ProcessRequestSend(_bufC, 0);
	ProcessRequestSend(_bufD, 0);
	ProcessRequestSend(_bufE, 1);

	// Return)
	return	true;
}


}
}
}