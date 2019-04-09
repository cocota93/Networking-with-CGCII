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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::IO::Sender::NStreamGather
//
// 1. CGNet::IO::Sender::NStreamGather��!
//    1) Stream(TCP)�� Sender�̴�. 
//    2) �⺻���� Stream Sender�� ��� �ѹ��� ���ۿ� �ѹ��� Overlapped I/O�� 
//       �ɰ� �ȴ�. 
//       ������ �Ѳ����� ���� Send�� �����ϰ� �Ǹ� �Ѳ����� �ʹ� ���� Overlapped I/O�� 
//       �ɰ� �ǰ� �̷� ���� ������ ���ϰ� ��Ÿ���� �ִ�. 
//       �� NStreamGather�� Send�� �Ѳ����� ���� �����ϴ��� 
//       �Ѳ����� ���� �ϳ� ���� OVerlapped I/O�� �ɰ� �ϴ� Sender�̴�.
//    3) Send�� ȣ���ϸ� Send �������� �ƴ� ���� Send�� ���� Overlapped I/O��
//       �Ǵ�. ������ �������� ���¶� ���� Send�� �Ϸ���� ���� ���¶�� 
//       �ϴ� ������ Message�� Queuing�� �� �� Send�Լ��� �����Ѵ�.
//       ���� ���� Send�� �Ϸ�Ǿ��� �� Queuing�� ���� �����ϰ� �ȴ�.
//
// 2. CGNet::IO::Sender::CStreamGather�� Ư¡
//    1) �Ѳ����� ��Ը� Send�� �ϴ� ������ ��쿡�� �� Sender�� ������ ��ȿ�ϴ�.
//        Ư�� ���� ũ���� Message�� �뷮���� ������ ��� ���� ��ȿ�ϴ�.
//         ���࿡ Send�� ������ ������� �ʰų� �����ϴ� Message�� ũ�Ⱑ ũ�ٸ�
//        ������ �� ��ȿ������ ���� �ִ�.
//        �̷� ��� �׳� CGNet::IO::Sender::NStream�� ����ϴ� ���� �� ȿ�����̴�.
//        (�Ϲ������� �� Sender�� ���� ȿ�����̴�.)
//    2) Queuing�ϴ� ����� Array�� �� Buffer�� �� ���� �����Ͽ� ���� ���ۿ��� 
//       ���� �������� Message ���۵��� �׸��� �ٸ� �ϳ� ������ ���� ���� ����
//       �ʰ� Queuing�� Message�� �����Ѵ�.
//       �������� Message ���۵���� ��� ���۵� �� Queuing�� Message ���۵���
//       �����ϸ� �̶� Queuing�� Message ���۵��� �������� Message ���۷� �ٲ��
//       Queueing�� Message���۵��� �������.
//       
//    3) ������ �����ؾ��� ���� Queuing���� �Ѱ谡 �־ ���� Ƚ�� �̻��� Message
//       Ȥ�� ���� Ƚ�� �̻��� ũ�� �̻����� Queuing�Ǹ� Overflow�� �߻��ϸ�
//       Send()�� ���ϰ��� false�� �ȴ�. 
//       �� ���۷��� ������ �����ϱ� ���� �Ʒ� �Լ��� ���� ������ �� �ִ�.
//
//        static	void SetDefaultMaxDepthOfSendBuffer(int iMax);
//        static	int  GetDefaultMaxDepthOfSendBuffer();
//
//        static	void SetDefaultMaxQueuedBytes(int iMax);
//        static	int  GetDefaultMaxQueuedBytes();
//
//        �� �Լ��� static�Լ��� �� �Լ� ���� �����Ǵ� ��� Sender::NStreamGather��
//        ����ȴ�.
//
//        int		GetMaxDepthOfSendBuffer() const;
//        uint32_t  GetMaxQueuedBytes() const;
//
//        �� �Լ��� ����Ͽ� Socket�� Queuing������ SendBuffer �ִ� ������ ����Ʈ����
//        ���� �� �ִ�.
//
// 3. �ٽ��Լ�!
//    1) bool Send(const CCGBuffer& _Buffer);
//       �� �״�� ������ �����ϴ� �Լ��̴�. CCGBuffer�� ������ Message�� �ְ� Send()
//       �Լ��� ȣ���ϸ� �� ���۸� �ѱ�� ������ �ȴ�.
// 
//    2) virtual bool ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);
//       �����ǰ����� �Լ��� �⺻ ������ ������ true�� �����ϵ��� �����Ǿ� �ִ�.
//       �� �Լ��� Send()�Լ��� ȣ���ϱ� �� Send()�Լ��� �Ѱ��� CCGBuffer�� �����ϰ�
//       �Ǵµ� �̶� ����ڰ� Message�� �ٸ��� �Ǿ����� Ȯ���ϴ� �ڵ带 �ۼ��Ͽ� ����
//       �� �ִ�. �� �Լ��� true��� ���������� �ۼ��� Message�̰� false��
//       �߸��� Message�� �����Ѵ�.
//       �Ϲ������� �� �Լ��� Debug��忡���� �����ϵ��� �Ѵ�.
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
	// 1) Send �Լ���
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

	// 2) Sustain Torrence ���� �Լ�.
			int					GetMaxDepthOfSendBuffer() const			{	return m_iMaxDepthOfSendBuffer;}
			void				SetMaxDepthOfSendBuffer(_In_ int _iDepth);
			uint32_t			GetMaxQueuedBytes() const				{	return m_bytesMaxQueued;}
			void				SetMaxQueuedBytes(_In_ int _iSize)		{	m_bytesMaxQueued=_iSize;}

	// 3) Default Gather Queue Depth ����
	static	void				SetDefaultMaxDepthOfSendBuffer(_In_ int iMax);
	static	int					GetDefaultMaxDepthOfSendBuffer();

	static	void				SetDefaultMaxQueuedBytes(_In_ int iMax);
	static	int					GetDefaultMaxQueuedBytes();


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) Send�Լ� ���ฦ �������� �� ȣ���ϴ� �Լ�.
	virtual	void				OnFailSending()							{}

	// 2) Validate Message
	virtual	bool				ValidateSendMessage(_In_ const CCGBuffer* _Buffer, _In_ int _countBuffer);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Sender�� Reset�ϴ� �Լ�.
	virtual	void				ResetSendCompletor() override;

	// 2) Completion �Ǿ��� �� ����Ǵ� �Լ�.(�����ǿ�)
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

	// 4) TwinQueue(WSABuffer�� Original�� �����Ѵ�.
			QUEUE_SENDING		m_queueQueued;
			QUEUE_SENDING		m_queueSending;
			char*				m_ptrQueuedBufferTail;

			uint32_t			m_byteQueued;
			uint32_t			m_bytesMaxQueued;
			int					m_iMaxDepthOfSendBuffer;

	// 5) Critical Section
			LOCKABLE<>			m_csSendQueue;

	// 6) ���������� ���Ǵ� �Լ���...
			bool				QueueBuffer(_In_ const CCGBuffer& _Buffer, int _countMessage);

	// Nested Class)
			class CSendCompletorCloser;
};

inline bool NStreamGather::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) Packet Validate Check�Ѵ�.
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
	// 1) Buffer List�� �����.
	CCGBuffer listBuf[]	 = {_bufA, _bufB};

	// Check) Packet Validate Check�Ѵ�.
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
	// 1) Buffer�� �Ҵ�޴´�.
	CCGBuffer bufTemp	 = MEM_POOL_ALLOC(sizeof(T));

	// 2) ���δ�.
	bufTemp.append<T>(_Data);

	// Check) Packet Validate Check�Ѵ�.
#ifdef _VALIDATE_SEND_MESSAGE
	CGASSERT(ValidateSendMessage(&bufTemp, 1), false);
#endif

	// 3) �����Ѵ�.
	return	ProcessRequestSend(&bufTemp, 1);
}


inline bool NStreamGather::Send(_In_ const CCGBuffer& _bufA, _In_ const CCGBuffer& _bufB, _In_ const CCGBuffer& _bufC)
{
	// 1) Buffer List�� �����.
	CCGBuffer listBuf[]	 = {_bufA, _bufB, _bufC};

	// Check) Packet Validate Check�Ѵ�.
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
	// 1) Buffer List�� �����.
	CCGBuffer listBuf[]	 = {_bufA, _bufB, _bufC, _bufD};

	// Check) Packet Validate Check�Ѵ�.
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
	// 1) Buffer List�� �����.
	CCGBuffer listBuf[]	 = {_bufA, _bufB, _bufC, _bufD, _bufE};

	// Check) Packet Validate Check�Ѵ�.
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