//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Event Classes                            *
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
// ----------------------------------------------------------------------------
//
// EVENT_SCHEDULE
//
// 1. EVENT_SCHEDULE란??
//    1) CGEvent::Object::CSchedule에서 사용되는 구조체이다.
//
// ----------------------------------------------------------------------------
// Declare) Event Info
class EVENT_SCHEDULE
{
// ****************************************************************************
// Constructor)
// ----------------------------------------------------------------------------
public:
			EVENT_SCHEDULE();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 다음 실행 시간.
			void				SetNextTime(const TIME::SYSTEM::time_point& _rtime) {	timeEventNext=_rtime;}
			const TIME::SYSTEM::time_point&	GetNextTime() const				{	return timeEventNext;}

	// 2) 실행 간격
			void				SetInterval(const TIME::duration& _rtime)	{	timeInterval=_rtime;}
			const TIME::duration& GetInterval() const						{	return timeInterval;}

	// 3) 남은 시행 횟수(-1은 무한대)
			void				SetTimes(int p_iTimes)						{	iTimes=p_iTimes;}
			int					GetTimes() const							{	return iTimes;}

	// 4) 시행 횟수
			int					GetExecutedCount() const { return iExecuted; }

	// 5) 자주 쓰는 설정
			void				SetSchedule(const TIME::duration& _durationInterval, const TIME::SYSTEM::time_point& _rtime, int p_iTimes);


// ****************************************************************************
// Operators)
// ----------------------------------------------------------------------------
public:
	// 1) Compare Operators 
			bool				operator==(const EVENT_SCHEDULE& rhs) const	{	return timeEventNext==rhs.timeEventNext;}
			bool				operator!=(const EVENT_SCHEDULE& rhs) const	{	return timeEventNext!=rhs.timeEventNext;}
			bool				operator>=(const EVENT_SCHEDULE& rhs) const	{	return timeEventNext>=rhs.timeEventNext;}
			bool				operator> (const EVENT_SCHEDULE& rhs) const	{	return timeEventNext> rhs.timeEventNext;}
			bool				operator<=(const EVENT_SCHEDULE& rhs) const	{	return timeEventNext<=rhs.timeEventNext;}
			bool				operator< (const EVENT_SCHEDULE& rhs) const	{	return timeEventNext< rhs.timeEventNext;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) 다음 실행 시간
			TIME::SYSTEM::time_point	timeEventNext;

	// 2) 실행 간격
			TIME::duration		timeInterval;

	// 3) 남은 횟수
			int					iTimes;

	// 4) 실행한 횟수
			int					iExecuted;
};

