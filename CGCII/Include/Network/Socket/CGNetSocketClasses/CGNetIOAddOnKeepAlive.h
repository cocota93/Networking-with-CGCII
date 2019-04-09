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
// CGNet::IO::AddOn::NKeepAlive
//
// 1. CGNet::IO::AddOn::NKeepAlive란!
//    1) UDP나 TCP에서 접속상태를 유지하거나 확인을 위해 일정시간마다 Ping을 
//       날려주는 역할을 하는 class이다.
//    2) Add-On형식이라 상속받아 결합하는 Class에 부가적으로 붙어서 동작한다.
//
//
// 2. CGNet::Socket::CUDP의 주요 Function의 기능 설명
//    1) StartKeepAlive()
//	      이 함수를 수행하면 Keep Alive를 수행하기 시작한다.
//    2) StopKeepAlive()
//        이 함수를 수행하면 Keep Alive 동작을 중지한다.
//    3) Ping을 날리게 되면 다시 돌아오는 Turn-Around-Time이 구해진다.
//    4) Ping을 날리는 간격을 설정할수 있다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace AddOn
{

class NKeepAlive :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISendable,					// (I) Sendable
	virtual	protected			CGNet::IO::IPacketable,					// (I) Packetable
	virtual	protected			CGNet::IO::Statistics::NSocket			// (I) Statistics Socket
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NKeepAlive();
	virtual ~NKeepAlive()												{	StopKeepAlive();}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			bool				StartKeepAlive();
			bool				StopKeepAlive();

			TICK::duration		GetTurnAroundTime() const				{	return m_nested.m_tickTAT;}

			void				SetPingGap(_In_ TICK::duration p_tickPingGap) {	m_nested.m_tickPingGap = p_tickPingGap; }
			TICK::duration		GetPingGap() const						{	return m_nested.m_tickPingGap;}

			void				SetTimeOut(_In_ TICK::duration p_tickTimeOut) {	m_nested.m_tickTimeOut = p_tickTimeOut; }
			TICK::duration		GetTimeOut() const						{	return m_nested.m_tickTimeOut;}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
private:
	virtual	void				OnKeepAliveTimeOut();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	class	CNested : 
		public					ICGMessageable,					//     Messageable
		public					CGSchedulable::NExecutable		//     Executable
	{
	public:
		virtual	int				ProcessMessage(CGMSG& _Msg) override	{	return m_pParent->NestedProcessMessage(_Msg);}
		virtual intptr_t		ProcessExecute(_In_ intptr_t, _In_ size_t) override {	return m_pParent->NestedUpdate();}

	public:
				NKeepAlive*		m_pParent;

				TICK::duration	m_tickTAT;
				TICK::duration	m_tickTimeOut;
				TICK::duration	m_tickPingGap;
	};
	friend	CNested;

private:
			CGOBJ<CNested>		m_nested;
			uint32_t			m_dwPingKey[2];

private:
			int					NestedProcessMessage(CGMSG& _Msg);
			intptr_t			NestedUpdate();

			bool				SendPingReq();
};


}
}
}