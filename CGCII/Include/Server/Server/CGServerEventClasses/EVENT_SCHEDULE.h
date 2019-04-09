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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// EVENT_SCHEDULE
//
// 1. EVENT_SCHEDULE��??
//    1) CGEvent::Object::CSchedule���� ���Ǵ� ����ü�̴�.
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
	// 1) ���� ���� �ð�.
			void				SetNextTime(const TIME::SYSTEM::time_point& _rtime) {	timeEventNext=_rtime;}
			const TIME::SYSTEM::time_point&	GetNextTime() const				{	return timeEventNext;}

	// 2) ���� ����
			void				SetInterval(const TIME::duration& _rtime)	{	timeInterval=_rtime;}
			const TIME::duration& GetInterval() const						{	return timeInterval;}

	// 3) ���� ���� Ƚ��(-1�� ���Ѵ�)
			void				SetTimes(int p_iTimes)						{	iTimes=p_iTimes;}
			int					GetTimes() const							{	return iTimes;}

	// 4) ���� Ƚ��
			int					GetExecutedCount() const { return iExecuted; }

	// 5) ���� ���� ����
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
	// 1) ���� ���� �ð�
			TIME::SYSTEM::time_point	timeEventNext;

	// 2) ���� ����
			TIME::duration		timeInterval;

	// 3) ���� Ƚ��
			int					iTimes;

	// 4) ������ Ƚ��
			int					iExecuted;
};

