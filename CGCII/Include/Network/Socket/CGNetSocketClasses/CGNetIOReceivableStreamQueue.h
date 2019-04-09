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
/*!
* @class NStreamQueue
*
* @ingroup CGNet::IO::Receivable
*
* @brief 대규모 스트림(TCP) 데이터 수신을 위해 최적화된 저수준 I/O IReceivable 클래스
*
*  TCP와 같이 Stream으로 전달되어 오는 데이터의 Receive를 처리하는 class이다.
*  NStream과 구현은 유사하지나 차이점은 데이터를 받은 후 최대한 빨리 다시 Receive를 
*  수행한다는 것이다. 그리고 데이터의 처리는 다른 쓰레드에서 처리하도록 되어 있다.
*  이때 데이터의 처리는 순서가 보장된다.
*  파일 수신 서버와 같이 대규모 데이터를 수신할 경우 최적의 성능을 낼수 있다.
*  하지만 데이터의 처리가 적을 경우 오히려 복잡한 동작으로 추가적인 부하만 만들 수 있다.
*
* @see CGNet::IO::Receiveable::NStream
* @see CGNet::IO::Receiveable::NStreamRIO
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Receivable
{

class NStreamQueue :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IReceivable,
	virtual protected			CGNet::IO::IConnectable,
	virtual protected			CGNet::IO::IPacketable,
	virtual public				ICGReferenceable,
	protected					ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NStreamQueue();
			~NStreamQueue();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Received Data
			size_t				GetQueuedReceiveBytes() const			{	return m_byteQueued;}
			size_t				GetQueuedReceiveIO() const				{	return m_queueReceived.size();}

	// 2) Sustain Torrence 관련 함수.
			size_t				GetMaxMaxReceivedBytesQueued() const	{	return m_iMaxReceivedBytesQueued;}
			void				SetMaxMaxReceivedBytesQueued(_In_ size_t p_Max){	m_iMaxReceivedBytesQueued=p_Max;}

	// 3) Default Gather Queue Depth 설정
	static	void				SetDefaultMaxReceivedBytesQueued(_In_ size_t iMax){	m_iDefaultMaxReceivedBytesQueued=iMax;}
	static	size_t				GetDefaultMaxReceivedBytesQueued()		{	return m_iDefaultMaxReceivedBytesQueued;}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) 일반적인 On함수.
	virtual	void				OnReceive(_In_ const CGD::buffer& /*_rWSABuffer*/, _In_ size_t /*_Transferred*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Buffers
			CCGBuffer			m_bufferReceiving;	// Receive를 걸어 놓은 Buffer...
			size_t				m_sizeBufferReceive;

	// 2) Send Queue
			LOCKABLE<>			m_cs_queueReceived;
			circular_list<CCGBuffer>	m_queueReceived;
			size_t				m_byteQueued;

	// 3) Packet Processing관련
			CCGBuffer			m_bufProcessing;
			size_t				m_bytesRequired;
			bool				m_bPosted;

	// 4) Limits
			size_t				m_iMaxReceivedBytesQueued;

	// 5) Default Values
	static	size_t				m_iDefaultMaxReceivedBytesQueued;

protected:
	// 6) Receive함수.
			bool				Receive(_In_ CGD::buffer* _arrayBuffer);

	// 7) Reset할 때 호출하는 함수.
	virtual	void				ResetReceivable() override;

	// 8) Prepare Receive
	virtual	bool				PrepareReceive() override;

private:
	// 9) Completion 되었을 때 수행되는 함수.
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;

	// 10) Process Message
			void				QueueReceivedMessage(_In_ const CCGBuffer& _Buffer);
			void				QueueCloseMessage();
			void				PostReceivedBuffer();
			void				ProcessReceivedBuffer();

	// 11) Executable for Process Receive
			class : virtual public ICGExecutable
			{
			public:
				NStreamQueue*	m_pParent;

			public:
				virtual	intptr_t ProcessExecute(_In_ intptr_t, _In_ size_t) override	{	m_pParent->ProcessReceivedBuffer(); m_pParent->Release(); return intptr_t(0);}
				virtual	void	ProcessDispose() override	{}
			} m_executableProcessReceived;
};


}
}
}