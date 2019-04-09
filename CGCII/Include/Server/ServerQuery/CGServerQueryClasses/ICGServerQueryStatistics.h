//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Query Classes                            *
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
// CGServerQuery::Statistics
//
// 1. CGServerQuery::Statistics란!
//    1) DB Classes를 위한 각종 통계용 클래스 정의
//
// 2. CGServerQuery::Statistics의 주요 클래스
//    1) 구조체
//       - CGServerQuery::Statistics::QUERY
//
//    2) 클래스
//       - CGServerQuery::Statistics::NQuerier
//
//
//-----------------------------------------------------------------------------
#define	TOTAL_INFO				32
extern	int						g_statisticsDBTime;

namespace CGServerQuery
{
namespace Statistics
{

struct QUERY
{
public:
	ATOMIC<uint64_t>	qwQueryTry;
	ATOMIC<uint64_t>	qwQuerySuccess;
	ATOMIC<uint64_t>	qwQueryFail;

	ATOMIC<uint64_t>	qwAllocSession;
	ATOMIC<uint64_t>	qwFreeSession;

	ATOMIC<uint64_t>	qwCreateSession;
	ATOMIC<uint64_t>	qwDestroySession;

public:
	QUERY&	operator =(const QUERY& rhs)
	{
		qwQueryTry.store(rhs.qwQueryTry);
		qwQuerySuccess.store(rhs.qwQuerySuccess);
		qwQueryFail.store(rhs.qwQueryFail);
		qwAllocSession.store(rhs.qwAllocSession);
		qwFreeSession.store(rhs.qwFreeSession);
		qwCreateSession.store(rhs.qwCreateSession);
		qwDestroySession.store(rhs.qwDestroySession);

		return	*this;
	}
};

struct QUERY_INFO
{
public:
			void				Reset()									{	ZeroMemory((void*)m_period, sizeof(m_period)); ZeroMemory((void*)&m_total, sizeof(m_total));}

			uint64_t			GetQueryTryTotal() const				{	return m_total.qwQueryTry+m_period[g_statisticsDBTime].qwQueryTry;}
			uint64_t			GetQueryTry() const						{	return m_period[g_statisticsDBTime].qwQueryTry;}
			uint64_t			GetQueryTry(int p_Time) const			{	return m_period[p_Time].qwQueryTry;}
									
			uint64_t			GetQuerySuccessTotal() const			{	return m_total.qwQuerySuccess+m_period[g_statisticsDBTime].qwQuerySuccess;}
			uint64_t			GetQuerySuccess() const					{	return m_period[g_statisticsDBTime].qwQuerySuccess;}
			uint64_t			GetQuerySuccess(int p_Time) const		{	return m_period[p_Time].qwQuerySuccess;}
								
			uint64_t			GetQueryFailTotal() const				{	return m_total.qwQueryFail+m_period[g_statisticsDBTime].qwQueryFail;}
			uint64_t			GetQueryFail() const						{	return m_period[g_statisticsDBTime].qwQueryFail;}
			uint64_t			GetQueryFail(int p_Time) const			{	return m_period[p_Time].qwQueryFail;}

			uint64_t			GetAllocSessionTotal() const			{	return m_total.qwAllocSession+m_period[g_statisticsDBTime].qwAllocSession;}
			uint64_t			GetAllocSession() const					{	return m_period[g_statisticsDBTime].qwAllocSession;}
			uint64_t			GetAllocSession(int p_Time) const		{	return m_period[p_Time].qwAllocSession;}

			uint64_t			GetFreeSessionTotal() const				{	return m_total.qwFreeSession+m_period[g_statisticsDBTime].qwFreeSession;}
			uint64_t			GetFreeSession() const					{	return m_period[g_statisticsDBTime].qwFreeSession;}
			uint64_t			GetFreeSession(int p_Time) const		{	return m_period[p_Time].qwFreeSession;}

			uint64_t			GetCreateSessionTotal() const			{	return m_total.qwCreateSession+m_period[g_statisticsDBTime].qwCreateSession;}
			uint64_t			GetCreateSession() const				{	return m_period[g_statisticsDBTime].qwCreateSession;}
			uint64_t			GetCreateSession(int p_Time) const		{	return m_period[p_Time].qwCreateSession;}

			uint64_t			GetDestroySessionTotal() const			{	return m_total.qwDestroySession+m_period[g_statisticsDBTime].qwDestroySession;}
			uint64_t			GetDestroySession() const				{	return m_period[g_statisticsDBTime].qwDestroySession;}
			uint64_t			GetDestroySession(int p_Time) const		{	return m_period[p_Time].qwDestroySession;}

			void				OnQueryTry()							{	++m_period[g_statisticsDBTime].qwQueryTry;}
			void				OnQuerySuccess()						{	++m_period[g_statisticsDBTime].qwQuerySuccess;}
			void				OnQueryFail()							{	++m_period[g_statisticsDBTime].qwQueryFail;}

			void				OnAllocSession()						{	++m_period[g_statisticsDBTime].qwAllocSession;}
			void				OnAllocSession(int _iCount)				{	m_period[g_statisticsDBTime].qwAllocSession+=_iCount;}
			void				OnFreeSession()							{	++m_period[g_statisticsDBTime].qwFreeSession;}
			void				OnFreeSession(int _iCount)				{	m_period[g_statisticsDBTime].qwFreeSession+=_iCount;}

			void				OnCreateSession()						{	++m_period[g_statisticsDBTime].qwCreateSession;}
			void				OnCreateSession(int _iCount)			{	m_period[g_statisticsDBTime].qwCreateSession+=_iCount;}
			void				OnDestroySession()						{	++m_period[g_statisticsDBTime].qwDestroySession;}
			void				OnDestroySession(int _iCount)			{	m_period[g_statisticsDBTime].qwDestroySession+=_iCount;}
private:
			volatile QUERY		m_period[TOTAL_INFO];
			volatile QUERY		m_total;
};


class NQuerier
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NQuerier()										 			{	m_pStatisticsQuerier=new QUERY_INFO; ResetStatistics();}
			~NQuerier()													{	delete m_pStatisticsQuerier;}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
			void				ResetStatistics()						{	m_pStatisticsQuerier->Reset();}

			const QUERY_INFO*	Statistics_GetQueryInfo() const			{	return m_pStatisticsQuerier;}

			uint64_t			Statistics_GetQueryTry() const			{	return m_pStatisticsQuerier->GetQueryTryTotal();}
			uint64_t			Statistics_GetQuerySuccess() const		{	return m_pStatisticsQuerier->GetQuerySuccessTotal();}
			uint64_t			Statistics_GetQueryFail() const			{	return m_pStatisticsQuerier->GetQueryFailTotal();}
			uint64_t			Statistics_GetQueryProcessing() const	{	return (Statistics_GetQueryTry()-Statistics_GetQuerySuccess()-Statistics_GetQueryFail());}
			uint64_t			Statistics_GetAllocSession() const		{	return m_pStatisticsQuerier->GetAllocSessionTotal();}
			uint64_t			Statistics_GetFreeSession() const		{	return m_pStatisticsQuerier->GetFreeSessionTotal();}
			uint64_t			Statistics_GetExistSession() const		{	return (m_pStatisticsQuerier->GetAllocSessionTotal()-m_pStatisticsQuerier->GetFreeSessionTotal());}

			void				Statistics_OnQueryTry()					{	m_pStatisticsQuerier->OnQueryTry();		m_StatisticsQuerierTotal.OnQueryTry();}
			void				Statistics_OnQuerySuccess()				{	m_pStatisticsQuerier->OnQuerySuccess();	m_StatisticsQuerierTotal.OnQuerySuccess();}
			void				Statistics_OnQueryFail()				{	m_pStatisticsQuerier->OnQueryFail();	m_StatisticsQuerierTotal.OnQueryFail();}

			void				Statistics_OnAllocSession()				{	m_pStatisticsQuerier->OnAllocSession();	m_StatisticsQuerierTotal.OnAllocSession();}
			void				Statistics_OnFreeSession()				{	m_pStatisticsQuerier->OnFreeSession();	m_StatisticsQuerierTotal.OnFreeSession();}

			void				Statistics_OnCreateSession()			{	m_pStatisticsQuerier->OnCreateSession();	m_StatisticsQuerierTotal.OnCreateSession();}
			void				Statistics_OnCreateSession(int _Count)	{	m_pStatisticsQuerier->OnCreateSession(_Count);	m_StatisticsQuerierTotal.OnCreateSession(_Count);}
			void				Statistics_OnDestroySession()			{	m_pStatisticsQuerier->OnDestroySession();	m_StatisticsQuerierTotal.OnDestroySession();}
			void				Statistics_OnDestroySession(int _Count)	{	m_pStatisticsQuerier->OnDestroySession(_Count);	m_StatisticsQuerierTotal.OnDestroySession(_Count);}

	static	void				Statistics_TotalOnQueryTry()			{	m_StatisticsQuerierTotal.OnQueryTry();}
	static	void				Statistics_TotalOnQuerySuccess()		{	m_StatisticsQuerierTotal.OnQuerySuccess();}
	static	void				Statistics_TotalOnQueryFail()			{	m_StatisticsQuerierTotal.OnQueryFail();}
	static	QUERY_INFO*			Statistics_GetTotalQueryInfo()			{	return &m_StatisticsQuerierTotal;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			QUERY_INFO*			m_pStatisticsQuerier;
	static	QUERY_INFO			m_StatisticsQuerierTotal;
};


}
}