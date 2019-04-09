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
// CGNet::IO::SendRequest::NUDPResend!!!!  ( ` ~`)b
//
// 1. CGNet::IO::SendRequest::NUDPResend란!
//    1) Reliable UDP Send/Receive를 구현하기 위한 기반 Class이다.
//    2) 이 Class에서는 전송에 대한 Reliable을 구현하고 있다.
//    3) 이 Class를 바탕으로 Reliable과 ReliableSequenced를 제작한다.
//
// 2. Reliable에 추가된 함수들...
//    1) Peer Key
//       - Peer간의 전송에 있어서 서로 확인을 위한 Key를 의미한다.
//       - 잘못전달되거나 여러 다른 전송과의 구분을 위해 Peer Key를 설정한다.
//       - Peer Key는 Send와 Receive Key가 있으며 Send Key는 Connect시 상대
//         로 부터 전달받는다.
//
//    2) Re-Send Interval
//	     - 일정시간 ACK가 돌아오지 않으면 재전송을 수행한다.  
//         GetReSendInterval()
//         SetReSendInterval(uint32_t p_dwResendInterval)
//
//    3) 기타
//       GetSendSequence()			전송 Sequence를 구한다.
//       GetRetransmittedCount()	재전송한 총 횟수를 구한다.
//		 GetSendQueud()				Send를 위해 Queued된 Packet의 수를 얻는 함수.
//
// 3. 주의 사항
//    1) 이 Class은 완성된 것이 아니며 CGNet::IO::CReliable과 CReliableSequenced
//       를 사용하도록 한다.
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
	// 1) Send할 때 부르는 함수.
	virtual	bool				RequestSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Reset할때 호출하는 함수.(기본은 빈것...)
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

	// 2) Re-Send용 Progress
			CGPTR<CExecutorResend>	m_pexecutorResend;

	// 3) ProcessResend
			void				ProgressResend();

	// 3) Sliding Window
			uint32_t			m_sizeSlindingWindow;			// Sliding Window의 크기

	// 4) Send Buffers
			uint32_t			m_dwSerialSend;					// Send Serial
			uint32_t			m_dwLastSerialSendAcked;		// 완료 Ack받은 마지막 packet
			uint32_t			m_dwLastSerialSended;			// 마지막으로 보낸 Serial.

	// 5) Send Queues
			int					m_nSended;
			vector<SENDED_PACKET> m_queueSended;				// 이미 보낸 Packet을 Array로 저장함.
			circular_list<SENDED_PACKET>	m_listSendQueue;				// 아직 보내지 않은 Packet을 보관한 Send Queue

	// 6) Criticalsection
			LOCKABLE<>			m_csSend;						// Send Queue용 Critical section

	// 7) Resend Interval (전송이 제대로 되지 않았을 때 다시 재전송을 하는 간격.)
			TICK::duration		m_tickReSendInterval;
			TICK::time_point	m_tickResendNext;

	// Statistics) 
			int					m_dwRetransmitted;				// 재전송한 횟수.

protected:
			bool				Ack(_In_ uint32_t p_dwPacketSerial, _In_ bool p_bResult=true);

			void				CreateBuffers();
			void				DestroyBuffers();
			void				ClearBuffers();
};


}
}
}