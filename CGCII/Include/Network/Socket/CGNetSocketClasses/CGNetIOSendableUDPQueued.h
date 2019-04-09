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
// CGNet::IO::Sender::NUDPQueued
//
// 1. CGNet::IO::Sendable::NUDPQueued��!
//    1) UDP�� Sendable���ν� ȿ������ ������ ���� �ѹ��� �ɸ��� Overlapped 
//       Send���� �����ϴ� Sendable�̴�.
//    2) Send�� ������ �ʰ��ϰ� �Ǹ� ���̻� ��� Send���� �ʰ� Queuing�� ���״�
//       �ٸ� Send�� �Ϸ�Ǹ� �̾ Send�� �����ϵ��� �Ǿ� �ִ�.
//    3) ������ ȿ��ȭ�� ����� ����ȭ�� �߱��� �� �ִ�.
//    4) ������ �߰������� ������ Data�� Queuing�ϴ� ���� �߰��� �޸� ����
//       ���� �� �� �ֱ� ������ ��뿡 ������ ���� �ʿ䰡 �ִ�.
//    5) �� Send Queuing�� ��� ���� ���� �� ���� �̻� Queuing�� �� ��� �Ｎ
//       ���� ������ ������.
//    
//    ����) Ư���� ��찡 �ƴϸ� �̰��� ���� �ʾƵ� �ȴ�.
//          �� Sendable�� ���� �Ǹ� Ȯ���� ������ ��źȭ�� Ȯ���� �� ������
//          �߰����� �뷮�� �ʿ�� �ϰ� �ȴ�.
//          �߰��Ǵ� �뷮�� ���� ������� ȿ���� ũ�� ���� ���̴�.
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
	virtual public				CGNet::IO::Statistics::NSocket			// (@) ���
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
	//! @brief ť�� �� ���� ��û ���� ��´�. @return ť�� �� ���� ��û ��
			int					GetQueuedSending() const				{	return m_iNowSending;}

	//! @brief ������ '�ִ� ���� ���� ����'�� ��´�. @return ������ '�ִ� ���� ���� ����'
			int					GetMaxConcurrentSending() const			{	return m_iMaxConcurrentSending;}
	//! @brief '�ִ� ���� ���� ����'�� �����Ѵ�. @param _Max '�ִ� ���� ���� ����'
			void				SetMaxConcurrentSending(_In_ int _Max){ m_iMaxConcurrentSending = _Max; }

	//! @brief '�ִ� ť�� ����'�� ��´�. @return '�ִ� ť�� ����'
			int					GetSendQueuingThreshold() const			{	return m_iSendQueuingThreshing;}
	//! @brief '�ִ� ť�� ����'�� �����Ѵ�. @param _Threshold '�ִ� ť�� ����'
			void				SetSendQueuingThreshold(_In_ int _Threshold)	{ m_iSendQueuingThreshing = _Threshold; }


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
protected:
	//! @brief ���� ó�� ������ �����ϴ� �Լ�. @param _pSendCompletor �Ϸ��� ȣ��� �Լ� ��ü @param _arrayBuffer ������ ���� �迭 @param _countBuffer ������ ���� @param _pOriginal ������ ��������� ������ ��ü �������� ������ ��������� 1 �����ϸ� ������ �Ϸ�Ǹ� 1 ���ҽ�Ų��. @param _pSockAddress ������ �ּ�(UDP����)  @return true ����  @return false ����
	virtual	bool				ProcessSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override;

	//! @brief ������ �Ϸ�Ǿ��� �� ó���� �����ϴ� �Լ�. @param _pSendCompletor �Ϸ��� ȣ��� �Լ� ��ü @param _Return ���� ��� @param _Transfered ���۵� ����Ʈ ��
	virtual	void				ProcessCompleteSendable(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_ uintptr_t _Return, _In_ size_t _Transfered) override;

	//! @brief �ʱ�ȭ �� �� ȣ��Ǵ� �Լ�.
	virtual	void				ResetSendable() override;

	// 4) Threshold��
			int					m_iNowSending;
			int					m_iMaxConcurrentSending;
			int					m_iSendQueuingThreshing;

	// 5) Send Queue
			LOCKABLE<>			m_csSendQueue;
			circular_list<Executable::CSendBuffer*>	m_queueSend;

	// 6) Queue�� �ִ� Packet�� �����ϴ� �Լ�.
			void				SendQueued();
			void				ClearQueueSend();
};


}
}
}