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
// CGNet::IO::AddOn::NSocketSustain
//
// 1. CGNet::IO::AddOn::NSocketSustain란!
//    1) Socket을 유지하기 위한 처리를 하는 클래스이다.
//    2) 이 클래스를 상속받아 부착하게 되면 일정시만 마다 ProcessSustain()함수가
//       호출이 되며 이 때 일반적인 Socket의 유지를 위한 처리를 수행하게 된다.
//    3) 일반적으로 Ghost가 된 Socket이면 제거하거나 일정시간 동안 송수신이 없을 시
//       접속을 종료시키는 등의 역할을 한다.
//    4) 기본적으로 접속된 Socket이 일정 시간 동안 아무런 송신이나 수신이 없을 때
//       각각 OnReceiveTimeOut(), OnSendTimeOut()을 호출해준다.
//    5) Add-On형식이라 상속받아 결합하는 Class에 부가적으로 붙어서 동작한다.
//    6) 일반적으로 Server쪽의 Socket에 사용된다.
//
//
// 2. CGNet::IO::AddOn::NSocketSustain의 주요 Function의 기능 설명
//    1) SetConnectTimeOut()함수와 ConnectTimeOut 설정.
//
//		 virtual void OnTimeOutConnect();
//
//	     접속된 후 OnTimeOutConnect()이 지나면 호출될지 시간을 나타내는 변수
//       이다.
//       이는 설정하거나 얻는 함수는 아래와 같다.
//
//		 void SetConnectTimeOut(TICK::time_point p_tickTimeOut)
//		 TICK:duration GetConnectTimeOut()
//
//    2) OnTimeOutDisconnect()함수와 DisconnectTimeOut 설정.
//
//		 virtual void OnTimeOutDisconnect();
//
//	     접속종료된 이후 얼마 후 OnTimeOutDisconnect()이 호출될지 시간을 
//       나타내는 변수이다.
//       이는 설정하거나 얻는 함수는 아래와 같다.
//
//		 void SetDisconnectTimeOut(TICK::time_point p_tickTimeOut)
//		 TICK:duration GetDisconnectTimeOut()
//
//    3) OnTimeOutSend()함수와 SendTimeOut 설정.
//
//		 virtual void OnTimeOutSend();
//
//	     얼마 동안 Send가 없어야 OnTimeOutSend()이 호출될지 시간을 나타내는 변수
//       이다.
//       이는 설정하거나 얻는 함수는 아래와 같다.
//
//		 void SetSendTimeOut(TICK::time_point p_tickTimeOut)
//		 TICK:duration GetSendTimeOut()
//
//    4) OnTimeOutReceive()함수와 ReceiveTimeOut
//
//		 virtual void OnTimeOutReceive();
//
//	     얼마 동안 Receive가 없어야 OnTimeOutReceive()이 호출될지 시간을 나타내는
//       변수이다.
//       이는 설정하거나 얻는 함수는 아래와 같다.
//
//		 void SetReceiveTimeOut(TICK::time_point p_tickTimeOut)
//		 TICK:duration GetReceiveTimeOut()
//
//    5) 이 클래스는 Add-On으로 Socket이 생성되는 즉시 동작하게 된다.
//    6) 자동으로 접속을 종료처리를 하는 것은 Socket이 eSOCKET_STATE::ESTABLISED
//       일 때만 동작된다. 즉 접속 중일 때만 동작된다.
//
//    7) 각각의 Time-Out값이 0으로 설정되면 해당 Time-Out은 동작하지 않도록
//       Disable된다.
//    8) OnTimeOut은 한번  실행된 이후에 내부에서 다시 TimeOut을 설정하지 않는한
//       TimeOut이 0으로 Reset되어서 OnTimeOut...()함수들은 한번만 실행된다.
//       만약 OnTimeOut...()함수내에서 다시 Set...TimeOut()함수를 사용하여
//       TimeOut()을 다시 설정한다면 다시 Time Out이 발생한다.
//       (이때 Connect나 Disconnect의 Time-Out의 설정은 접속시점 혹은 접속 종료 
//       시점을 기준으로 하는 함수므로 주의해야 한다.
//
//       주의) OnTimeOut함수가 호출될 때 해당 m_tickTimeOut...값들은 이미 0으로
//             Reset된 이후므로 이 값을 참조하게 되면 0을 얻을 뿐이다.
//
//  3. 주의
//     1) 모든 Time-Out의 설정값은 0x7fffffff보다 작아야 한다.
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

	// 2) Time 설정 관련.
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

	// 1) Time-Out 설정
			TICK::duration		m_tickTimeOutConnect;
			TICK::duration		m_tickTimeOutDisconnect;
			TICK::duration		m_tickTimeOutReceive;
			TICK::duration		m_tickTimeOutSend;

	// 2) Iterator에 붙일 때의 정보...
			circular_list<NSocketSustain*>::iterator	m_iterListSocketSustain;
			CGPTR<ManagerSocketSustain>		m_pManager;

private:
	// 1) Process AutoClose
	virtual void				ProcessSocketSustain();
};


}
}
}
