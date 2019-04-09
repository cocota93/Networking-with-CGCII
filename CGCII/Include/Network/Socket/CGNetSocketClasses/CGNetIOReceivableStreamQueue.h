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
/*!
* @class NStreamQueue
*
* @ingroup CGNet::IO::Receivable
*
* @brief ��Ը� ��Ʈ��(TCP) ������ ������ ���� ����ȭ�� ������ I/O IReceivable Ŭ����
*
*  TCP�� ���� Stream���� ���޵Ǿ� ���� �������� Receive�� ó���ϴ� class�̴�.
*  NStream�� ������ ���������� �������� �����͸� ���� �� �ִ��� ���� �ٽ� Receive�� 
*  �����Ѵٴ� ���̴�. �׸��� �������� ó���� �ٸ� �����忡�� ó���ϵ��� �Ǿ� �ִ�.
*  �̶� �������� ó���� ������ ����ȴ�.
*  ���� ���� ������ ���� ��Ը� �����͸� ������ ��� ������ ������ ���� �ִ�.
*  ������ �������� ó���� ���� ��� ������ ������ �������� �߰����� ���ϸ� ���� �� �ִ�.
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

	// 2) Sustain Torrence ���� �Լ�.
			size_t				GetMaxMaxReceivedBytesQueued() const	{	return m_iMaxReceivedBytesQueued;}
			void				SetMaxMaxReceivedBytesQueued(_In_ size_t p_Max){	m_iMaxReceivedBytesQueued=p_Max;}

	// 3) Default Gather Queue Depth ����
	static	void				SetDefaultMaxReceivedBytesQueued(_In_ size_t iMax){	m_iDefaultMaxReceivedBytesQueued=iMax;}
	static	size_t				GetDefaultMaxReceivedBytesQueued()		{	return m_iDefaultMaxReceivedBytesQueued;}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) �Ϲ����� On�Լ�.
	virtual	void				OnReceive(_In_ const CGD::buffer& /*_rWSABuffer*/, _In_ size_t /*_Transferred*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Buffers
			CCGBuffer			m_bufferReceiving;	// Receive�� �ɾ� ���� Buffer...
			size_t				m_sizeBufferReceive;

	// 2) Send Queue
			LOCKABLE<>			m_cs_queueReceived;
			circular_list<CCGBuffer>	m_queueReceived;
			size_t				m_byteQueued;

	// 3) Packet Processing����
			CCGBuffer			m_bufProcessing;
			size_t				m_bytesRequired;
			bool				m_bPosted;

	// 4) Limits
			size_t				m_iMaxReceivedBytesQueued;

	// 5) Default Values
	static	size_t				m_iDefaultMaxReceivedBytesQueued;

protected:
	// 6) Receive�Լ�.
			bool				Receive(_In_ CGD::buffer* _arrayBuffer);

	// 7) Reset�� �� ȣ���ϴ� �Լ�.
	virtual	void				ResetReceivable() override;

	// 8) Prepare Receive
	virtual	bool				PrepareReceive() override;

private:
	// 9) Completion �Ǿ��� �� ����Ǵ� �Լ�.
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