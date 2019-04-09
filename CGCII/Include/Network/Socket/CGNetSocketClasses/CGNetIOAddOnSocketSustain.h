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
// CGNet::IO::AddOn::NSocketSustain
//
// 1. CGNet::IO::AddOn::NSocketSustain��!
//    1) Socket�� �����ϱ� ���� ó���� �ϴ� Ŭ�����̴�.
//    2) �� Ŭ������ ��ӹ޾� �����ϰ� �Ǹ� �����ø� ���� ProcessSustain()�Լ���
//       ȣ���� �Ǹ� �� �� �Ϲ����� Socket�� ������ ���� ó���� �����ϰ� �ȴ�.
//    3) �Ϲ������� Ghost�� �� Socket�̸� �����ϰų� �����ð� ���� �ۼ����� ���� ��
//       ������ �����Ű�� ���� ������ �Ѵ�.
//    4) �⺻������ ���ӵ� Socket�� ���� �ð� ���� �ƹ��� �۽��̳� ������ ���� ��
//       ���� OnReceiveTimeOut(), OnSendTimeOut()�� ȣ�����ش�.
//    5) Add-On�����̶� ��ӹ޾� �����ϴ� Class�� �ΰ������� �پ �����Ѵ�.
//    6) �Ϲ������� Server���� Socket�� ���ȴ�.
//
//
// 2. CGNet::IO::AddOn::NSocketSustain�� �ֿ� Function�� ��� ����
//    1) SetConnectTimeOut()�Լ��� ConnectTimeOut ����.
//
//		 virtual void OnTimeOutConnect();
//
//	     ���ӵ� �� OnTimeOutConnect()�� ������ ȣ����� �ð��� ��Ÿ���� ����
//       �̴�.
//       �̴� �����ϰų� ��� �Լ��� �Ʒ��� ����.
//
//		 void SetConnectTimeOut(TICK::time_point p_tickTimeOut)
//		 TICK:duration GetConnectTimeOut()
//
//    2) OnTimeOutDisconnect()�Լ��� DisconnectTimeOut ����.
//
//		 virtual void OnTimeOutDisconnect();
//
//	     ��������� ���� �� �� OnTimeOutDisconnect()�� ȣ����� �ð��� 
//       ��Ÿ���� �����̴�.
//       �̴� �����ϰų� ��� �Լ��� �Ʒ��� ����.
//
//		 void SetDisconnectTimeOut(TICK::time_point p_tickTimeOut)
//		 TICK:duration GetDisconnectTimeOut()
//
//    3) OnTimeOutSend()�Լ��� SendTimeOut ����.
//
//		 virtual void OnTimeOutSend();
//
//	     �� ���� Send�� ����� OnTimeOutSend()�� ȣ����� �ð��� ��Ÿ���� ����
//       �̴�.
//       �̴� �����ϰų� ��� �Լ��� �Ʒ��� ����.
//
//		 void SetSendTimeOut(TICK::time_point p_tickTimeOut)
//		 TICK:duration GetSendTimeOut()
//
//    4) OnTimeOutReceive()�Լ��� ReceiveTimeOut
//
//		 virtual void OnTimeOutReceive();
//
//	     �� ���� Receive�� ����� OnTimeOutReceive()�� ȣ����� �ð��� ��Ÿ����
//       �����̴�.
//       �̴� �����ϰų� ��� �Լ��� �Ʒ��� ����.
//
//		 void SetReceiveTimeOut(TICK::time_point p_tickTimeOut)
//		 TICK:duration GetReceiveTimeOut()
//
//    5) �� Ŭ������ Add-On���� Socket�� �����Ǵ� ��� �����ϰ� �ȴ�.
//    6) �ڵ����� ������ ����ó���� �ϴ� ���� Socket�� eSOCKET_STATE::ESTABLISED
//       �� ���� ���۵ȴ�. �� ���� ���� ���� ���۵ȴ�.
//
//    7) ������ Time-Out���� 0���� �����Ǹ� �ش� Time-Out�� �������� �ʵ���
//       Disable�ȴ�.
//    8) OnTimeOut�� �ѹ�  ����� ���Ŀ� ���ο��� �ٽ� TimeOut�� �������� �ʴ���
//       TimeOut�� 0���� Reset�Ǿ OnTimeOut...()�Լ����� �ѹ��� ����ȴ�.
//       ���� OnTimeOut...()�Լ������� �ٽ� Set...TimeOut()�Լ��� ����Ͽ�
//       TimeOut()�� �ٽ� �����Ѵٸ� �ٽ� Time Out�� �߻��Ѵ�.
//       (�̶� Connect�� Disconnect�� Time-Out�� ������ ���ӽ��� Ȥ�� ���� ���� 
//       ������ �������� �ϴ� �Լ��Ƿ� �����ؾ� �Ѵ�.
//
//       ����) OnTimeOut�Լ��� ȣ��� �� �ش� m_tickTimeOut...������ �̹� 0����
//             Reset�� ���ĹǷ� �� ���� �����ϰ� �Ǹ� 0�� ���� ���̴�.
//
//  3. ����
//     1) ��� Time-Out�� �������� 0x7fffffff���� �۾ƾ� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace AddOn
{

class NSocketSustain :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Sendable
	virtual	protected			CGNet::IO::Statistics::NSocket			// (I) Statistics Socket
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			NSocketSustain();
	virtual ~NSocketSustain();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Keep Alive.
			bool				StartSocketSustain();
			bool				StopSocketSustain();

	// 2) Time ���� ����.
			void				SetConnectTimeOut(_In_ TICK::duration p_tickTimeOut){	m_tickTimeOutConnect = p_tickTimeOut; }
			void				ResetConnectTimeOut()						{	SetConnectTimeOut(TICK::duration::zero());}
			TICK::duration		GetConnectTimeOut() const					{	return m_tickTimeOutConnect;}

			void				SetDisconnectTimeOut(_In_ TICK::duration p_tickTimeOut){	m_tickTimeOutDisconnect = p_tickTimeOut; }
			void				ResetDisconnectTimeOut()					{	SetDisconnectTimeOut(TICK::duration::zero());}
			TICK::duration		GetDisconnectTimeOut() const				{	return m_tickTimeOutDisconnect;}

			void				SetReceiveTimeOut(_In_ TICK::duration p_tickTimeOut){	m_tickTimeOutReceive = p_tickTimeOut; }
			void				ResetReceiveTimeOut()						{	SetReceiveTimeOut(TICK::duration::zero());}
			TICK::duration		GetReceiveTimeOut() const					{	return m_tickTimeOutReceive;}

			void				SetSendTimeOut(_In_ TICK::duration p_tickTimeOut){	m_tickTimeOutSend = p_tickTimeOut; }
			void				ResetSendTimeOut()							{	SetSendTimeOut(TICK::duration::zero());}
			TICK::duration		GetSendTimeOut() const						{	return m_tickTimeOutSend;}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
private:
	virtual	void				OnTimeOutConnect(_In_ TICK::duration /*p_tickdifferExecute*/)	{}
	virtual	void				OnTimeOutDisconnect(_In_ TICK::duration /*p_tickdifferExecute*/){}
	virtual	void				OnTimeOutReceive(_In_ TICK::duration /*p_tickdifferExecute*/)	{ CloseSocket(); }
	virtual	void				OnTimeOutSend(_In_ TICK::duration /*p_tickdifferExecute*/)		{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// Friend) 
	friend class ManagerSocketSustain;

	// 1) Time-Out ����
			TICK::duration		m_tickTimeOutConnect;
			TICK::duration		m_tickTimeOutDisconnect;
			TICK::duration		m_tickTimeOutReceive;
			TICK::duration		m_tickTimeOutSend;

	// 2) Iterator�� ���� ���� ����...
			circular_list<NSocketSustain*>::iterator	m_iterListSocketSustain;
			CGPTR<ManagerSocketSustain>		m_pManager;

private:
	// 1) Process AutoClose
	virtual void				ProcessSocketSustain();
};


}
}
}
