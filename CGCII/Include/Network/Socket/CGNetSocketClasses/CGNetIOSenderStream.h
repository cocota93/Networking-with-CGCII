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
// CGNet::IO::Sender::NStream
//
// 1. CGNet::IO::Sender::CStream��~
//    1) ���� �Ϲ����� Sender�� CGNet::IO::ISendRequest�� RequestSend()�Լ��� ȣ����
//       �ش�.
//    2) �ѹ��� ���ۿ� �ѹ��� Overlapped I/O�� �ɾ� Send()�� �����ϴ� Sender��
//       ���� �Ϲ����̰� �⺻���� Sender�̴�. 
//       ������ ���� Message�� �뷮���� �Ѳ����� ������ �Ǹ� ������ ���� ��������.
//       ���� Message�� �뷮���� �Ѳ����� ȿ�������� �����ϰ� �ʹٸ� NStreamGather
//       Ŭ������ ����ϱ� �����Ѵ�.
//
// 2. �ٽ��Լ�!
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
	virtual public				CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send�� �� �θ��� �Լ�.
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