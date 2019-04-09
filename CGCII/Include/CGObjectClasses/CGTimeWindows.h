//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//----------------------------------------------------------------------------
//
//
//  Definitions for Event Classes
//
//
//----------------------------------------------------------------------------
#define _CGD_TIME

namespace CGD
{
namespace TIME
{
class duration;
class _POINT;
typedef _POINT	time_point;

namespace SYSTEM
{
	class time_point;
	time_point now();
}

namespace LOCAL
{
	class time_point;
	time_point now();
}

class duration
{
public:
			duration(int _iYears=0, int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0): m_iSeconds(_iSeconds), m_iMinutes(_iMinutes), m_iHours(_iHours), m_iDays(_iDays), m_iMonths(_iMonths), m_iYears(_iYears) {}
			duration(const duration& _copy);
			duration(const TICK::duration& _value);
public:
			int					get_second() const		{	return m_iSeconds;}
			int					get_minute() const		{	return m_iMinutes;}
			int					get_hour() const		{	return m_iHours;}
			int					get_day() const			{	return m_iDays;}
			int					get_month() const		{	return m_iMonths;}
			int					get_year() const		{	return m_iYears;}

			void				set_second(int _value)	{	m_iSeconds	 = static_cast<uint16_t>(_value);}
			void				set_minute(int _value)	{	m_iMinutes	 = static_cast<uint16_t>(_value);}
			void				set_hour(int _value)	{	m_iHours	 = static_cast<uint16_t>(_value);}
			void				set_day(int _value)		{	m_iDays		 = static_cast<uint16_t>(_value);}
			void				set_month(int _value)	{	m_iMonths	 = static_cast<uint16_t>(_value);}
			void				set_year(int _value)	{	m_iYears	 = static_cast<uint16_t>(_value);}

			bool				operator==(const duration& rhs) const;
			bool				operator!=(const duration& rhs) const;
			bool				operator>=(const duration& rhs) const;
			bool				operator> (const duration& rhs) const;
			bool				operator<=(const duration& rhs) const;
			bool				operator< (const duration& rhs) const;
			duration			operator+ (const duration& rhs) const;
			duration			operator- (const duration& rhs) const;
			duration&			operator+=(const duration& rhs);
			duration&			operator-=(const duration& rhs);
			duration&			operator= (const duration& rhs);
			duration&			operator= (const CGD::TICK::duration& _value);

								operator CGD::TICK::duration() const;
public:
			int					m_iSeconds;
			int					m_iMinutes;
			int					m_iHours;
			int					m_iDays;
			int					m_iMonths;
			int					m_iYears;

public:
	static	duration			zero()	{	return duration();}
};

inline duration seconds(int v)	{	return duration(0, 0, 0, 0, 0, v);}
inline duration minutes(int v)	{	return duration(0, 0, 0, 0, v, 0);}
inline duration hours(int v)	{	return duration(0, 0, 0, v, 0, 0);}
inline duration days(int v)		{	return duration(0, 0, v, 0, 0, 0);}
inline duration months(int v)	{	return duration(0, v, 0, 0, 0, 0);}
inline duration years(int v)	{	return duration(v, 0, 0, 0, 0, 0);}

class _POINT
{
protected:
			_POINT()															{}
			_POINT(int _iYears, int _iMonths, int _iDays, int _iHours, int _iMinutes, int _iSeconds, int _iMillisecond);
			_POINT(_In_ const SYSTEMTIME& value):m_time(value)					{}
public:
	static _POINT	create_instance()											{ return _POINT();}
	static _POINT	create_instance(int _iYears, int _iMonths, int _iDays, int _iHours, int _iMinutes, int _iSeconds, int _iMillisecond)		{ return _POINT(_iYears, _iMonths, _iDays, _iHours, _iMinutes, _iSeconds, _iMillisecond);}
	static _POINT	create_instance(_In_ const SYSTEMTIME& value)				{ return _POINT(value);}

public:
			int				get_millisecond() const								{	return m_time.wMilliseconds;}
			int				get_second() const									{	return m_time.wSecond;}
			int				get_minute() const									{	return m_time.wMinute;}
			int				get_hour() const									{	return m_time.wHour;}
			int				get_day() const										{	return m_time.wDay;}
			int				get_dayofweek() const								{	return m_time.wDayOfWeek; }
			int				get_month() const									{	return m_time.wMonth;}
			int				get_year() const									{	return m_time.wYear;}
			tm				get_tm() const										{	tm temp; temp.tm_year=m_time.wYear-1900;temp.tm_mon=m_time.wMonth;temp.tm_mday=m_time.wDay;temp.tm_wday=m_time.wDayOfWeek;temp.tm_hour=m_time.wHour;temp.tm_min=m_time.wMinute;temp.tm_sec=m_time.wSecond;temp.tm_isdst=0; return temp;}

			void			set_millisecond(int value)							{	m_time.wMilliseconds	= static_cast<uint16_t>(value);}
			void			set_second(int value)								{	m_time.wSecond			= static_cast<uint16_t>(value);}
			void			set_minute(int value)								{	m_time.wMinute			= static_cast<uint16_t>(value);}
			void			set_hour(int value)									{	m_time.wHour			= static_cast<uint16_t>(value);}
			void			set_day(int value)									{	m_time.wDay				= static_cast<uint16_t>(value);}
			void			set_dayofweek(int value)							{	m_time.wDayOfWeek		= static_cast<uint16_t>(value);}
			void			set_month(int value)								{	m_time.wMonth			= static_cast<uint16_t>(value);}
			void			set_year(int value)									{	m_time.wYear			= static_cast<uint16_t>(value);}

			template<class TTYPE>
			std::basic_string<TTYPE> to_string(const TTYPE* _format=reinterpret_cast<const TTYPE*>(nullptr)) const {}

	static	_POINT			zero()												{	return _POINT(0,0,0,0,0,0,0);}

protected:
			SYSTEMTIME		m_time;
			friend class	LOCAL::time_point;
			friend class	SYSTEM::time_point;
};

template<>
inline std::basic_string<char> _POINT::to_string<char>(const char* _format) const
{
	char temp[256]{};
	sprintf_s(temp, 256, (_format!=nullptr) ? _format : "%d-%d-%d %d:%d:%d", get_year(), get_month(), get_day(), get_hour(), get_minute(), get_second());
	return	std::basic_string<char>(temp);
}

template<>
inline std::basic_string<wchar_t> _POINT::to_string<wchar_t>(const wchar_t* _format) const
{
	wchar_t	temp[256]{};
	swprintf_s(temp, 256, (_format!=nullptr) ? _format : L"%d-%d-%d %d:%d:%d", get_year(), get_month(), get_day(), get_hour(), get_minute(), get_second());
	return	std::basic_string<wchar_t>(temp);
}



inline _POINT	zero()	{	return _POINT::zero();}

namespace LOCAL
{
	class time_point : public _POINT
	{
	public:
				time_point()														{}
				time_point(int _iYears, int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0, int _iMillisecond=0);
				time_point(_In_ const time_point& _copy):_POINT(_copy.m_time)		{}
				time_point(_In_ const SYSTEM::time_point& _copy);
				time_point(_In_ const CGD::TICK::time_point& _value);
	public:
				bool			operator!=(_In_ const time_point& rhs) const;
				bool			operator==(_In_ const time_point& rhs) const;
				bool			operator< (_In_ const time_point& rhs) const;
				bool			operator<=(_In_ const time_point& rhs) const;
				bool			operator> (_In_ const time_point& rhs) const;
				bool			operator>=(_In_ const time_point& rhs) const;

				time_point&		operator+=(_In_ const duration& rhs);
				time_point&		operator-=(_In_ const duration& rhs);
				time_point		operator+ (_In_ const duration& rhs) const;
				TICK::duration	operator- (_In_ const time_point& rhs) const;
				TICK::duration	operator- (_In_ const SYSTEM::time_point& rhs) const;
				time_point		operator- (_In_ const duration& rhs) const;

				time_point&		operator= (_In_ const _POINT& rhs)					{	m_time=rhs.m_time; return *this;}
				time_point&		operator= (_In_ const time_point& rhs)				{	m_time=rhs.m_time; return *this;}
				time_point&		operator= (_In_ const SYSTEM::time_point& rhs);
				time_point&		operator= (_In_ const CGD::TICK::time_point& value);

								operator CGD::TICK::time_point() const;
								operator SYSTEMTIME&()								{	return m_time;}
	private:
			#if defined(_MSC_VER)
				friend class	time_point;
			#endif
				friend class	SYSTEM::time_point;
	public:
	static		time_point		_get_now()											{	time_point temp; ::GetLocalTime(&temp.m_time); return temp;}
	static		time_point		_get_past(int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0);
	static		time_point		_get_future(int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0);
	};

	inline time_point now()		{	return time_point::_get_now();}
	inline time_point zero()	{	time_point temp; temp.zero(); return temp;}
	inline time_point PAST(int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0)	{	return time_point::_get_past(_iMonths, _iDays, _iHours, _iMinutes, _iSeconds);}
	inline time_point FUTURE(int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0)	{	return time_point::_get_future(_iMonths, _iDays, _iHours, _iMinutes, _iSeconds);}
}

namespace SYSTEM
{
	class time_point : public _POINT
	{
	public:
				time_point()														{}
				time_point(int _iYears, int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0, int _iMillisecond=0);
				time_point(_In_ const time_point& _copy):_POINT(_copy.m_time)		{}
				time_point(_In_ const LOCAL::time_point& _copy);
				time_point(_In_ const CGD::TICK::time_point& _value);
	public:
				bool			operator!=(_In_ const time_point& rhs) const;
				bool			operator==(_In_ const time_point& rhs) const;
				bool			operator< (_In_ const time_point& rhs) const;
				bool			operator<=(_In_ const time_point& rhs) const;
				bool			operator> (_In_ const time_point& rhs) const;
				bool			operator>=(_In_ const time_point& rhs) const;

				time_point&		operator+=(_In_ const duration& rhs);
				time_point&		operator-=(_In_ const duration& rhs);
				time_point		operator+ (_In_ const duration& rhs) const;
				TICK::duration	operator- (_In_ const time_point& rhs) const;
				TICK::duration	operator- (_In_ const LOCAL::time_point& rhs) const;
				time_point		operator- (_In_ const duration& rhs) const;

				time_point&		operator= (_In_ const _POINT& rhs)					{	m_time=rhs.m_time; return *this;}
				time_point&		operator= (_In_ const time_point& rhs)				{	m_time=rhs.m_time; return *this;}
				time_point&		operator= (_In_ const LOCAL::time_point& rhs);
				time_point&		operator= (_In_ const CGD::TICK::time_point& value);

								operator CGD::TICK::time_point() const;
								operator SYSTEMTIME&()								{	return m_time;}
	private:
			#if defined(_MSC_VER)
				friend class	time_point;
			#endif
				friend class	LOCAL::time_point;
	public:
	static		time_point		_get_now()											{	time_point temp; ::GetSystemTime(&temp.m_time); return temp;}
	static		time_point		_get_past(int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0);
	static		time_point		_get_future(int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0);
	};

	inline time_point now()		{	return time_point::_get_now();}
	inline time_point zero()	{	time_point temp; temp.zero(); return temp;}
	inline time_point PAST(int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0)	{	return time_point::_get_past(_iMonths, _iDays, _iHours, _iMinutes, _iSeconds);}
	inline time_point FUTURE(int _iMonths=0, int _iDays=0, int _iHours=0, int _iMinutes=0, int _iSeconds=0)	{	return time_point::_get_future(_iMonths, _iDays, _iHours, _iMinutes, _iSeconds);}
}


}
}
