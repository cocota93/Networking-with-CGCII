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
// CGNet::IO::AddOn::NKeepAlive
//
// 1. CGNet::IO::AddOn::NKeepAlive��!
//    1) UDP�� TCP���� ���ӻ��¸� �����ϰų� Ȯ���� ���� �����ð����� Ping�� 
//       �����ִ� ������ �ϴ� class�̴�.
//    2) Add-On�����̶� ��ӹ޾� �����ϴ� Class�� �ΰ������� �پ �����Ѵ�.
//
//
// 2. CGNet::Socket::CUDP�� �ֿ� Function�� ��� ����
//    1) StartKeepAlive()
//	      �� �Լ��� �����ϸ� Keep Alive�� �����ϱ� �����Ѵ�.
//    2) StopKeepAlive()
//        �� �Լ��� �����ϸ� Keep Alive ������ �����Ѵ�.
//    3) Ping�� ������ �Ǹ� �ٽ� ���ƿ��� Turn-Around-Time�� ��������.
//    4) Ping�� ������ ������ �����Ҽ� �ִ�.
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