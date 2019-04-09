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
// CGNet::IO::Sender::NUDPQueued
//
// 1. CGNet::IO::Sendable::NUDPQueued란!
//    1) UDP용 Sendable으로써 효율적인 전송을 위해 한번에 걸리는 Overlapped 
//       Send수를 제한하는 Sendable이다.
//    2) Send의 제한을 초과하게 되면 더이상 즉시 Send되지 않고 Queuing을 시켰다
//       다른 Send가 완료되면 이어서 Send를 수행하도록 되어 있다.
//    3) 전성요 효율화와 더블어 안전화를 추구할 수 있다.
//    4) 하지만 추가적으로 전송할 Data를 Queuing하는 등의 추가적 메모리 낭비를
//       가져 올 수 있기 때문에 사용에 신중을 기할 필요가 있다.
//    5) 또 Send Queuing을 어느 정도 수행 후 일정 이상 Queuing이 될 경우 즉석
//       에서 전송해 버린다.
//    
//    주의) 특별한 경우가 아니면 이것은 쓰지 않아도 된다.
//          이 Sendable을 쓰게 되면 확실히 전송의 평탄화는 확보할 수 있지만
//          추가적인 용량이 필요로 하게 된다.
//          추가되는 용량에 비해 얻어지는 효과는 크지 않은 편이다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sendable
{

class NUDPQueued : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Socket.
	virtual public				CGNet::IO::ISendable,					//     Sendable.
	virtual public				CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NUDPQueued();
			~NUDPQueued();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 큐잉 된 전송 요청 수를 얻는다. @return 큐잉 된 전송 요청 수
			int					GetQueuedSending() const				{	return m_iNowSending;}

	//! @brief 설정된 '최대 동시 전송 개수'를 얻는다. @return 설정된 '최대 동시 전송 개수'
			int					GetMaxConcurrentSending() const			{	return m_iMaxConcurrentSending;}
	//! @brief '최대 동시 전송 개수'를 설정한다. @param _Max '최대 동시 전송 개수'
			void				SetMaxConcurrentSending(_In_ int _Max){ m_iMaxConcurrentSending = _Max; }

	//! @brief '최대 큐잉 개수'를 얻는다. @return '최대 큐잉 개수'
			int					GetSendQueuingThreshold() const			{	return m_iSendQueuingThreshing;}
	//! @brief '최대 큐잉 개수'를 설정한다. @param _Threshold '최대 큐잉 개수'
			void				SetSendQueuingThreshold(_In_ int _Threshold)	{ m_iSendQueuingThreshing = _Threshold; }


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
protected:
	//! @brief 전송 처리 과정을 정의하는 함수. @param _pSendCompletor 완료후 호출된 함수 객체 @param _arrayBuffer 전송할 버퍼 배열 @param _countBuffer 버퍼의 개수 @param _pOriginal 전송중 참조계수를 유지할 객체 전송중일 때에는 참조계수가 1 증가하며 전송이 완료되면 1 감소시킨다. @param _pSockAddress 전송할 주소(UDP전용)  @return true 성공  @return false 실패
	virtual	bool				ProcessSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override;

	//! @brief 전송이 완료되었을 때 처리를 정의하는 함수. @param _pSendCompletor 완료후 호출된 함수 객체 @param _Return 전송 결과 @param _Transfered 전송된 바이트 수
	virtual	void				ProcessCompleteSendable(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_ uintptr_t _Return, _In_ size_t _Transfered) override;

	//! @brief 초기화 될 때 호출되는 함수.
	virtual	void				ResetSendable() override;

	// 4) Threshold값
			int					m_iNowSending;
			int					m_iMaxConcurrentSending;
			int					m_iSendQueuingThreshing;

	// 5) Send Queue
			LOCKABLE<>			m_csSendQueue;
			circular_list<Executable::CSendBuffer*>	m_queueSend;

	// 6) Queue에 있는 Packet을 전송하는 함수.
			void				SendQueued();
			void				ClearQueueSend();
};


}
}
}