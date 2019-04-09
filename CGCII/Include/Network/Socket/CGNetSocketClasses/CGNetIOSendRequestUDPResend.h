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
// CGNet::IO::SendRequest::NUDPResend!!!!  ( ` ~`)b
//
// 1. CGNet::IO::SendRequest::NUDPResend��!
//    1) Reliable UDP Send/Receive�� �����ϱ� ���� ��� Class�̴�.
//    2) �� Class������ ���ۿ� ���� Reliable�� �����ϰ� �ִ�.
//    3) �� Class�� �������� Reliable�� ReliableSequenced�� �����Ѵ�.
//
// 2. Reliable�� �߰��� �Լ���...
//    1) Peer Key
//       - Peer���� ���ۿ� �־ ���� Ȯ���� ���� Key�� �ǹ��Ѵ�.
//       - �߸����޵ǰų� ���� �ٸ� ���۰��� ������ ���� Peer Key�� �����Ѵ�.
//       - Peer Key�� Send�� Receive Key�� ������ Send Key�� Connect�� ���
//         �� ���� ���޹޴´�.
//
//    2) Re-Send Interval
//	     - �����ð� ACK�� ���ƿ��� ������ �������� �����Ѵ�.  
//         GetReSendInterval()
//         SetReSendInterval(uint32_t p_dwResendInterval)
//
//    3) ��Ÿ
//       GetSendSequence()			���� Sequence�� ���Ѵ�.
//       GetRetransmittedCount()	�������� �� Ƚ���� ���Ѵ�.
//		 GetSendQueud()				Send�� ���� Queued�� Packet�� ���� ��� �Լ�.
//
// 3. ���� ����
//    1) �� Class�� �ϼ��� ���� �ƴϸ� CGNet::IO::CReliable�� CReliableSequenced
//       �� ����ϵ��� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
#define		SEND_QUEUE_SIZE				1024
#define		SEND_QUEUE_INDEX_MASK		0x3ff

namespace CGNet
{
namespace IO
{
namespace SendRequest
{

class NUDPResend : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISendable,						// (I) Sendable
	virtual public				CGNet::IO::ISendRequest,					//     ISendRequest
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NUDPResend();
			~NUDPResend();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool				RequestSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Reset�Ҷ� ȣ���ϴ� �Լ�.(�⺻�� ���...)
	virtual	void				ResetSendRequest() override;

	// Definition) Send Queues
			struct SENDED_PACKET
			{
				int						iSendOut;
				TICK::time_point		tickLastSend;
				CGD::buffer				WSABuffer;
				CGPTR<ICGReferenceable>	pOriginal;
				SOCKADDR_CGNETWORK		addrDestination;
				ISendCompletor*			pSendCompletor;
			};

	// Definition) Executor Resend
			class CExecutorResend;

	// 2) Re-Send�� Progress
			CGPTR<CExecutorResend>	m_pexecutorResend;

	// 3) ProcessResend
			void				ProgressResend();

	// 3) Sliding Window
			uint32_t			m_sizeSlindingWindow;			// Sliding Window�� ũ��

	// 4) Send Buffers
			uint32_t			m_dwSerialSend;					// Send Serial
			uint32_t			m_dwLastSerialSendAcked;		// �Ϸ� Ack���� ������ packet
			uint32_t			m_dwLastSerialSended;			// ���������� ���� Serial.

	// 5) Send Queues
			int					m_nSended;
			vector<SENDED_PACKET> m_queueSended;				// �̹� ���� Packet�� Array�� ������.
			circular_list<SENDED_PACKET>	m_listSendQueue;				// ���� ������ ���� Packet�� ������ Send Queue

	// 6) Criticalsection
			LOCKABLE<>			m_csSend;						// Send Queue�� Critical section

	// 7) Resend Interval (������ ����� ���� �ʾ��� �� �ٽ� �������� �ϴ� ����.)
			TICK::duration		m_tickReSendInterval;
			TICK::time_point	m_tickResendNext;

	// Statistics) 
			int					m_dwRetransmitted;				// �������� Ƚ��.

protected:
			bool				Ack(_In_ uint32_t p_dwPacketSerial, _In_ bool p_bResult=true);

			void				CreateBuffers();
			void				DestroyBuffers();
			void				ClearBuffers();
};


}
}
}