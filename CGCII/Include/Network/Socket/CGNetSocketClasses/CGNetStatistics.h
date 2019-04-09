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
// CGNet::IO::Statistics
//
// 1. CGNet::IO::Statistics은~
//    1) Socket관련된 각종 통계처리를 위한 구조체와 클래스들이다.
//    2) 통계를 위한 구조체
//       - CONNECTIVE_DWORD/CONNECTIVE_QWORD 
//       - TRAFFIC/TRAFFIC_QWORD
//       - CONNECTIVE_INFO
//       - TRAFFIC_INFO
//    3) 클래스 객체를 위한 클래스
//       - NConnective
//       - NSocket
//
//-----------------------------------------------------------------------------
#include <intrin.h>

#if defined(_MSC_VER)
	#pragma warning(disable:4201)
#endif
#include <Mmsystem.h>
#if defined(_MSC_VER)
	#pragma warning(default:4201)
#endif


// ----------------------------------------------------------------------------
// I/O Statistics
// ----------------------------------------------------------------------------
//#define	_NO_STATISTICS

#ifndef _NO_STATISTICS
#define	_USE_STATISTICS_TOTAL
#endif

#ifndef _NO_STATISTICS
#define	_USE_STATISTICS_CONNECTIVE
#define	_USE_STATISTICS_SOCKET
#define	_USE_STATISTICS_POOL
#endif 

#ifdef	_USE_STATISTICS_CONNECTIVE
	#define	CONNECTIVE_STATISTICS(value)			value
#else
	#define	CONNECTIVE_STATISTICS(value)
#endif	// _USE_STATISTICS_CONNECTIVE


#ifdef	_USE_STATISTICS_SOCKET
	#define	SOCKET_STATISTICS(value)				value
#else
	#define	SOCKET_STATISTICS(value)
#endif	// _USE_STATISTICS_SOCKET

#ifdef	_USE_STATISTICS_POOL
	#define	POOL_STATISTICS(value)					value
#else
	#define	POOL_STATISTICS(value)
#endif	// _USE_STATISTICS_POOL



namespace CGNet
{
namespace IO
{
namespace Statistics
{

// 1) Acceptor Info
struct CONNECTIVE
{
	CONNECTIVE()	{}
	CONNECTIVE(const CONNECTIVE& rhs)				{	Set(rhs);}
	CONNECTIVE& operator =(const CONNECTIVE& rhs)	{	Set(rhs); return *this;}

	TICK::time_point	tickBegin;
	TICK::time_point	tickEnd;

	ATOMIC<uint64_t>	countTry;					// 접속시도 회수.
	ATOMIC<uint64_t>	countSuccessConnect;		// 접속성공 회수.
	ATOMIC<uint64_t>	countFailConnect;			// 접속성공 회수.
	ATOMIC<uint64_t>	countDisconnect;			// 접속종료 회수.
	ATOMIC<uint64_t>	countErrorDisconnect;		// 오류로 인한 접속 종료 회수.
	ATOMIC<uint64_t>	countKeep;					// 현 접속수.

	ATOMIC<uint64_t>	countOverlapped;			// Overlapped I/O횟수

	void	Set(const CONNECTIVE& rhs)
	{
		tickBegin	 = rhs.tickBegin;
		tickEnd		 = rhs.tickEnd;

		countTry.store(rhs.countTry);
		countSuccessConnect.store(rhs.countSuccessConnect);
		countFailConnect.store(rhs.countFailConnect);
		countDisconnect.store(rhs.countDisconnect);
		countErrorDisconnect.store(rhs.countErrorDisconnect);
		countKeep.store(rhs.countKeep);

		countOverlapped.store(rhs.countOverlapped);
	}

};

// 2) Socket Info
struct TRAFFIC
{
	TICK::time_point	tickBegin;
	TICK::time_point	tickEnd;

	ATOMIC<uint64_t>	countReceivedMessage;		// 받은 Message 수.
	ATOMIC<uint64_t>	countReceivedBytes;			// 받은 Bytes

	ATOMIC<uint64_t>	countSendedMessage;			// 보낸 Message 수.
	ATOMIC<uint64_t>	countSendedBytes;			// 보낸 Bytes

	ATOMIC<uint64_t>	countSendIO;				// 송신 I/O횟수
	ATOMIC<uint64_t>	countReceiveIO;				// 수신 I/O횟수

	ATOMIC<uint64_t>	countErrorOnSend;			// Send시 Error
	ATOMIC<uint64_t>	countErrorOnReceive;		// Receive시 Error

	TRAFFIC(){}
	TRAFFIC(const TRAFFIC& rhs)	{	Set(rhs);}
	TRAFFIC&	operator=(const TRAFFIC& rhs)	{	Set(rhs); return *this;}

	void Set(const TRAFFIC& rhs)
	{
		tickBegin	 = rhs.tickBegin;
		tickEnd		 = rhs.tickEnd;

		countReceivedMessage.store(rhs.countReceivedMessage);
		countReceivedBytes.store(rhs.countReceivedBytes);

		countSendedMessage.store(rhs.countSendedMessage);
		countSendedBytes.store(rhs.countSendedBytes);

		countSendIO.store(rhs.countSendIO);
		countReceiveIO.store(rhs.countReceiveIO);

		countErrorOnSend.store(rhs.countErrorOnSend);
		countErrorOnReceive.store(rhs.countErrorOnReceive);
	}
};


// 7일 동안의 정보 분량으로 1분 단위로 저장함.
//#define	TOTAL_INFO				1440*7
#define	TOTAL_INFO					32
extern	int							g_statisticsTime;

struct CONNECTIVE_INFO : virtual public ICGReferenceable
{
public:
			void				Reset();

			uint64_t			GetTryTotal() const						{	return m_total.countTry+m_period[g_statisticsTime].countTry;}
			uint64_t			GetTryNow() const						{	return m_period[g_statisticsTime].countTry;}
			uint64_t			GetTry(_In_ int _Time) const			{	return m_period[_Time].countTry; }

			uint64_t			GetSuccessConnectTotal() const			{	return m_total.countSuccessConnect+m_period[g_statisticsTime].countSuccessConnect;}
			uint64_t			GetSuccessConnectNow() const			{	return m_period[g_statisticsTime].countSuccessConnect;}
			uint64_t			GetSuccessConnect(_In_ int _Time) const{	return m_period[_Time].countSuccessConnect; }
							
			uint64_t			GetFailConnectTotal() const				{	return m_total.countFailConnect+m_period[g_statisticsTime].countFailConnect;}
			uint64_t			GetFailConnectNow() const				{	return m_period[g_statisticsTime].countFailConnect;}
			uint64_t			GetFailConnect(_In_ int _Time) const	{	return m_period[_Time].countFailConnect; }
							
			uint64_t			GetDisconnectTotal() const				{	return m_total.countDisconnect+m_period[g_statisticsTime].countDisconnect;}
			uint64_t			GetDisconnectNow() const				{	return m_period[g_statisticsTime].countDisconnect;}
			uint64_t			GetDisconnect(_In_ int _Time) const	{	return m_period[_Time].countDisconnect; }

			uint64_t			GetErrorDisconnectTotal() const			{	return m_total.countErrorDisconnect+m_period[g_statisticsTime].countErrorDisconnect;}
			uint64_t			GetErrorDisconnectNow() const			{	return m_period[g_statisticsTime].countErrorDisconnect;}
			uint64_t			GetErrorDisconnect(_In_ int _Time) const{	return m_period[_Time].countErrorDisconnect; }

			uint64_t			GetKeepNow() const						{	return m_period[g_statisticsTime].countKeep;}
			uint64_t			GetKeep(_In_ int _Time) const			{	return m_period[_Time].countKeep; }

			void				OnTry()									{	++m_period[g_statisticsTime].countTry;}
			void				OnSuccessConnect()						{	++m_period[g_statisticsTime].countSuccessConnect; ++m_period[g_statisticsTime].countKeep;}
			void				OnFailConnect()							{	++m_period[g_statisticsTime].countFailConnect;}
			void				OnDisconnect()							{	++m_period[g_statisticsTime].countDisconnect; --m_period[g_statisticsTime].countKeep;}
			void				OnErrorDisconnect()						{	++m_period[g_statisticsTime].countErrorDisconnect;}
			void				OnErrorDisconnect(_In_ uint64_t value)	{	m_period[g_statisticsTime].countErrorDisconnect+=value; }
			void				Keep(_In_ uint64_t p_dwKeep)			{	m_period[g_statisticsTime].countKeep = p_dwKeep; }

			const CONNECTIVE&	GetConnectiveInfo() const				{	return *(const CONNECTIVE*)(m_period+g_statisticsTime);}
			const CONNECTIVE&	GetConnectiveInfo(_In_ int _Index) const{ CGASSERT_ERROR(_Index<TOTAL_INFO); return *(const CONNECTIVE*)(m_period + _Index); }

private:
			CONNECTIVE			m_period[TOTAL_INFO];
			CONNECTIVE			m_total;
};


struct TRAFFIC_INFO : virtual public ICGReferenceable
{
public:
			void				Reset();

			uint64_t			GetSendedMessageTotal() const			{	return m_total.countSendedMessage+m_period[g_statisticsTime].countSendedMessage;}
			uint64_t			GetSendedMessageNow() const				{	return m_period[g_statisticsTime].countSendedMessage;}
			uint64_t			GetSendedMessage(_In_ int _Time) const	{	return m_period[_Time].countSendedMessage; }
							
			uint64_t			GetSendedBytesTotal() const				{	return m_total.countSendedBytes+m_period[g_statisticsTime].countSendedBytes;}
			uint64_t			GetSendedBytesNow() const				{	return m_period[g_statisticsTime].countSendedBytes;}
			uint64_t			GetSendedBytes(_In_ int _Time) const	{	return m_period[_Time].countSendedBytes; }
								
			uint64_t			GetReceivedMessageTotal() const			{	return m_total.countReceivedMessage+m_period[g_statisticsTime].countReceivedMessage;}
			uint64_t			GetReceivedMessageNow() const			{	return m_period[g_statisticsTime].countReceivedMessage;}
			uint64_t			GetReceivedMessage(_In_ int _Time) const{	return m_period[_Time].countReceivedMessage; }

			uint64_t			GetReceivedBytesTotal() const			{	return m_total.countReceivedBytes+m_period[g_statisticsTime].countReceivedBytes;}
			uint64_t			GetReceivedBytesNow() const				{	return m_period[g_statisticsTime].countReceivedBytes;}
			uint64_t			GetReceivedBytes(_In_ int _Time) const	{	return m_period[_Time].countReceivedBytes; }

			uint64_t			GetErrorOnSendTotal() const				{	return m_total.countErrorOnSend+m_period[g_statisticsTime].countErrorOnSend;}
			uint64_t			GetErrorOnSendNow() const				{	return m_period[g_statisticsTime].countErrorOnSend;}
			uint64_t			GetErrorOnSend(_In_ int _Time) const	{	return m_period[_Time].countErrorOnSend; }

			uint64_t			GetErrorOnReveiveTotal() const			{	return m_total.countErrorOnReceive+m_period[g_statisticsTime].countErrorOnReceive;}
			uint64_t			GetErrorOnReveiveNow() const			{	return m_period[g_statisticsTime].countErrorOnReceive;}
			uint64_t			GetErrorOnReveive(_In_ int _Time) const{	return m_period[_Time].countErrorOnReceive; }

			uint64_t			GetOverlappedSendTotal() const			{	return m_total.countSendIO+m_period[g_statisticsTime].countSendIO;}
			uint64_t			GetOverlappedSendNow() const			{	return m_period[g_statisticsTime].countSendIO;}
			uint64_t			GetOverlappedSend(_In_ int _Time) const	{	return m_period[_Time].countSendIO; }

			uint64_t			GetOverlappedReveiveTotal() const		{	return m_total.countReceiveIO+m_period[g_statisticsTime].countReceiveIO;}
			uint64_t			GetOverlappedReveiveNow() const			{	return m_period[g_statisticsTime].countReceiveIO;}
			uint64_t			GetOverlappedReveive(_In_ int _Time) const	{ return m_period[_Time].countReceiveIO; }

			void				OnReceiveMessage()						{	++m_period[g_statisticsTime].countReceivedMessage;}
			void				OnReceiveMessage(_In_ uint64_t _Cnt)	{	m_period[g_statisticsTime].countReceivedMessage += _Cnt; }
			void				OnReceiveBytes(_In_ uint64_t _Bytes)	{	m_period[g_statisticsTime].countReceivedBytes += _Bytes; }
			void				OnSendMessage()							{	++m_period[g_statisticsTime].countSendedMessage;}
			void				OnSendMessage(_In_ uint64_t _Cnt)		{	m_period[g_statisticsTime].countSendedMessage += _Cnt; }
			void				OnSendBytes(_In_ uint64_t _Bytes)		{	m_period[g_statisticsTime].countSendedBytes += _Bytes; }
			void				OnErrorSend()							{	++m_period[g_statisticsTime].countErrorOnSend;}
			void				OnErrorReceive()						{	++m_period[g_statisticsTime].countErrorOnReceive;}
			void				OnOverlappedReceive()					{	++m_period[g_statisticsTime].countReceiveIO;}
			void				OnOverlappedSend()						{	++m_period[g_statisticsTime].countSendIO;}

			const TRAFFIC&		GetTrafficInfo() const					{	return *(const TRAFFIC*)(m_period+g_statisticsTime);}
			const TRAFFIC&		GetTrafficInfo(_In_ int _Index) const	{	CGASSERT_ERROR(_Index<TOTAL_INFO); return *(const TRAFFIC*)(m_period + _Index); }
private:
			TRAFFIC				m_period[TOTAL_INFO];
			TRAFFIC				m_total;
};


class NConnective
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NConnective() : m_pStatisticsConnection(NEW<CONNECTIVE_INFO>())		{	ResetStatistics();}
			~NConnective()														{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				ResetStatistics();

			int					GetConnectiveID() const							{	return m_iConnectiveID;}

			CGPTR<CONNECTIVE_INFO> Statistics_GetConnectionInfo() const			{	return m_pStatisticsConnection;}

			uint64_t			Statistics_GetTry() const						{	return m_pStatisticsConnection->GetTryTotal();}
			uint64_t			Statistics_GetSuccessConnect() const			{	return m_pStatisticsConnection->GetSuccessConnectTotal();}
			uint64_t			Statistics_GetFailConnect() const				{	return m_pStatisticsConnection->GetFailConnectTotal();}
			uint64_t			Statistics_GetDisconnect() const				{	return m_pStatisticsConnection->GetDisconnectTotal();}
			uint64_t			Statistics_GetErrorDisconnect() const			{	return m_pStatisticsConnection->GetErrorDisconnectTotal();}
			uint64_t			Statistics_GetKeep() const						{	return m_pStatisticsConnection->GetKeepNow(); }
			uint64_t			Statistics_GetNowOverlappedIO() const			{	return m_iOverlapped;}

			TIME::SYSTEM::time_point	Statistics_GetCreateTime() const		{	return m_timeCreate;}
			TIME::SYSTEM::time_point	Statistics_GetStartTime() const			{	return m_timeStart;}
			TIME::SYSTEM::time_point	Statistics_GetStopTime() const			{	return m_timeStop;}

			void				Statistics_OnTry()								{	CONNECTIVE_STATISTICS(m_pStatisticsConnection->OnTry());		m_StatisticsConnectionTotal.OnTry();}
			void				Statistics_OnSuccessConnect()					{	CONNECTIVE_STATISTICS(m_pStatisticsConnection->OnSuccessConnect());}
			void				Statistics_OnFailConnect()						{	CONNECTIVE_STATISTICS(m_pStatisticsConnection->OnFailConnect());m_StatisticsConnectionTotal.OnFailConnect();}
			void				Statistics_OnDisconnect()						{	CONNECTIVE_STATISTICS(m_pStatisticsConnection->OnDisconnect());}
			void				Statistics_OnErrorDisconnect(_In_ uint64_t value){	CONNECTIVE_STATISTICS(m_pStatisticsConnection->OnErrorDisconnect(value)); }

			long				Statistics_OnIncreseOverlapped()				{	return ++m_iOverlapped;}
			long				Statistics_OnDecreseOverlapped()				{	return --m_iOverlapped;}

			void				Statistics_SetCreateTime()						{	m_timeCreate=TIME::SYSTEM::now();}
			void				Statistics_SetStartTime()						{	m_timeStart=TIME::SYSTEM::now();}
			void				Statistics_SetStopTime()						{	m_timeStop=TIME::SYSTEM::now();}


	static	void				Statistics_TotalOnTry()							{	m_StatisticsConnectionTotal.OnTry();}
	static	void				Statistics_TotalOnSuccessConnect()				{	m_StatisticsConnectionTotal.OnSuccessConnect();}
	static	void				Statistics_TotalOnDisconnect()					{	m_StatisticsConnectionTotal.OnDisconnect();}
	static	void				Statistics_TotalOnErrorDisconnect(_In_ uint64_t value){ m_StatisticsConnectionTotal.OnErrorDisconnect(value); }

	static	CONNECTIVE_INFO*	Statistics_GetTotalConnectionInfo()				{	return &m_StatisticsConnectionTotal;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) 전송량 통계
			CGPTR<CONNECTIVE_INFO> m_pStatisticsConnection;
	static	CGOBJ<CONNECTIVE_INFO>	m_StatisticsConnectionTotal;

	// 2) Connective ID
			int					m_iConnectiveID;

	// 3) 시간
			TIME::SYSTEM::time_point	m_timeCreate;
			TIME::SYSTEM::time_point	m_timeStart;
			TIME::SYSTEM::time_point	m_timeStop;

			ATOMIC<int>			m_iOverlapped;

			friend	CGNet::IO::Connective::Manager;
};


class NSocket
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NSocket();
			~NSocket();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Get 함수.
			uint64_t			Statistics_GetCountConnectTry() const			{	return m_countConnectTry;}
			TIME::SYSTEM::time_point Statistics_GetConnectTime() const			{	return m_timeConnect;}
			TICK::time_point	Statistics_GetTickConnect() const				{	return m_tickConnect;}
			TICK::time_point	Statistics_GetTickDisconnect() const			{	return m_tickDisconnect;}

			uint64_t			Statistics_GetReceivedMessage() const			{	return m_pStatisticsTraffic->GetReceivedMessageTotal(); }
			uint64_t			Statistics_GetReceivedBytes() const				{	return m_pStatisticsTraffic->GetReceivedBytesTotal();}
			TICK::time_point	Statistics_GetTickLastSend() const				{	return m_tickLastSend;}
			uint64_t			Statistics_GetSendedMessage() const				{	return m_pStatisticsTraffic->GetSendedMessageTotal();}
			uint64_t			Statistics_GetSendedBytes() const				{	return m_pStatisticsTraffic->GetSendedBytesTotal();}
			TICK::time_point	Statistics_GetTickLastReceive() const			{	return m_tickLastReceive;}

			long				Statistics_GetNowOverlappedIO() const			{	return m_countOverlappedConDis+m_countOverlappedSending+m_countOverlappedReceiving;}
			uint64_t			Statistics_GetOverlappedSend() const			{	return m_pStatisticsTraffic->GetOverlappedSendTotal();}
			long				Statistics_GetOverlappedSending() const			{	return m_countOverlappedSending;}
			uint64_t			Statistics_GetOverlappedReceive() const			{	return m_pStatisticsTraffic->GetOverlappedReveiveTotal();}
			long				Statistics_GetOverlappedReceiving() const		{	return m_countOverlappedReceiving;}

			int					IsErrorDisconnected() const						{	return m_bErrorDisconnect;}

	// 2) Socket의 생성후 전체 정보
			uint64_t			Statistics_GetTotalCountConnectTry() const		{	return m_countTotalConnectTry;}
			uint64_t			Statistics_GetTotalCountConnectSuccess() const	{	return m_countTotalConnect;}
			uint64_t			Statistics_GetTotalCountConnectFail() const		{	return m_countTotalConnectTry-m_countTotalConnect;}

	// 3) Socket 전체 정보
	static	const TRAFFIC_INFO&	GetTotal()										{	return m_StatisticsTrafficTotal;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) 전송량 통계
			CGPTR<TRAFFIC_INFO>	m_pStatisticsTraffic;
	static	CGOBJ<TRAFFIC_INFO>	m_StatisticsTrafficTotal;

	// 2) Total관련(이것은 Socket이 Disconnect되어도 Reset되지 않는다.)
			ATOMIC<uint64_t>	m_countTotalConnectTry;		// 총 접속 시도 횟수
			ATOMIC<uint64_t>	m_countTotalConnect;		// 총 접속 성공 횟수

	// 3) 전송시간 관련
			uint64_t			m_countConnectTry;			// 접속 시도 횟수
			TIME::SYSTEM::time_point m_timeConnect;			// 접속한 시간.
			TICK::time_point	m_tickConnect;				// 접속한 시간.(Tick)
			TICK::time_point	m_tickLastSend;				// 최후에 보낸 시간.(Tick)
			TICK::time_point	m_tickLastReceive;			// 최후에 받은 시간.(Tick)
			TICK::time_point	m_tickWaitTime;				// 기다리는 시간
			TICK::time_point	m_tickDisconnect;			// 접속종료한 시간.(Tick)
			ATOMIC<int>			m_bErrorDisconnect;			// Error로 인한 강제접속종료 여부

			ATOMIC<int>			m_countOverlappedConDis;	// 현재 진행중인 Connect/Disconnect Overlapped I/O의 수.
			ATOMIC<int>			m_countOverlappedSending;	// 현재 진행중인 Send Overlapped I/O의 수.
			ATOMIC<int>			m_countOverlappedReceiving;	// 현재 진행중인 Receive Overlapped I/O의 수.

public:
			void				ResetStatistics();

			CGPTR<TRAFFIC_INFO>	Statistics_GetTrafficInfo() const				{	return m_pStatisticsTraffic;}

			void				Statistics_OnConnectTry()						{	SOCKET_STATISTICS(++m_countConnectTry); SOCKET_STATISTICS(++m_countTotalConnectTry); NConnective::Statistics_TotalOnTry(); m_tickDisconnect=TICK::time_point(TICK::duration::zero());}
			void				Statistics_OnConnect()							{	m_timeConnect=TIME::SYSTEM::now(); m_tickLastReceive=m_tickLastSend=m_tickConnect=TICK::now(); NConnective::Statistics_TotalOnSuccessConnect(); SOCKET_STATISTICS(++m_countTotalConnect);}
			void				Statistics_OnDisconnect()						{	m_tickDisconnect=TICK::now(); m_countConnectTry=0;}
			void				Statistics_SetErrorDisconnect()					{	m_bErrorDisconnect=static_cast<int>(true);}
			void				Statistics_CheckErrorDisconnect()				{	int iErrorDisconnect=m_bErrorDisconnect.exchange(false); CGNet::IO::Statistics::NConnective::Statistics_TotalOnErrorDisconnect(iErrorDisconnect);}

			void				Statistics_OnReceiveMessage()					{	SOCKET_STATISTICS(m_pStatisticsTraffic->OnReceiveMessage());		m_StatisticsTrafficTotal.OnReceiveMessage();}
			void				Statistics_OnReceiveMessage(_In_ uint64_t _Cnt)	{	SOCKET_STATISTICS(m_pStatisticsTraffic->OnReceiveMessage(_Cnt));		m_StatisticsTrafficTotal.OnReceiveMessage(_Cnt); }
			void				Statistics_OnReceiveBytes(_In_ uint64_t _Bytes)	{	SOCKET_STATISTICS(m_pStatisticsTraffic->OnReceiveBytes(_Bytes));	m_StatisticsTrafficTotal.OnReceiveBytes(_Bytes); m_tickLastReceive = TICK::now(); }
			void				Statistics_OnReceiveOverlapped()				{	SOCKET_STATISTICS(m_pStatisticsTraffic->OnOverlappedReceive());		m_StatisticsTrafficTotal.OnOverlappedReceive(); }
			void				Statistics_OnSendMessage()						{	SOCKET_STATISTICS(m_pStatisticsTraffic->OnSendMessage());			m_StatisticsTrafficTotal.OnSendMessage(); }
			void				Statistics_OnSendMessage(_In_ uint64_t _Cnt)	{	SOCKET_STATISTICS(m_pStatisticsTraffic->OnSendMessage(_Cnt));		m_StatisticsTrafficTotal.OnSendMessage(_Cnt);}
			void				Statistics_OnSendBytes(_In_ uint64_t _Bytes)	{	SOCKET_STATISTICS(m_pStatisticsTraffic->OnSendBytes(_Bytes));		m_StatisticsTrafficTotal.OnSendBytes(_Bytes);  m_tickLastSend=TICK::now();}
			void				Statistics_OnSendOverlapped()					{	SOCKET_STATISTICS(m_pStatisticsTraffic->OnOverlappedSend());		m_StatisticsTrafficTotal.OnOverlappedSend();}
			void				Statistics_OnErrorSend()						{	m_StatisticsTrafficTotal.OnErrorSend();}
			void				Statistics_OnErrorReceive()						{	m_StatisticsTrafficTotal.OnErrorReceive();}
			void				Statistics_UpdateTickLastSend(_In_ TICK::time_point _Tick){ m_tickLastSend = _Tick; }
			void				Statistics_UpdateTickLastReceive(_In_ TICK::time_point _Tick){ m_tickLastReceive = _Tick; }

			int					OnIncreaseOverlappedConDis()					{	return ++m_countOverlappedConDis;}
			int					OnDecreaseOverlappedConDis()					{	return --m_countOverlappedConDis;}
			int					OnIncreaseOverlappedSending()					{	return ++m_countOverlappedSending;}
			int					OnDecreaseOverlappedSending()					{	return --m_countOverlappedSending;}
			int					OnIncreaseOverlappedReceiveing()				{	return ++m_countOverlappedReceiving;}
			int					OnDecreaseOverlappedReceiveing()				{	return --m_countOverlappedReceiving;}

};


}
}
}
