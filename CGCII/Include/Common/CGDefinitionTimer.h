//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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
//-----------------------------------------------------------------------------
//                                                                            
// Definitions for Timer
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Configure)
//
// 1) Tick
//		#define		_USE_TICK_TICKCOUNT32
//		#define		_USE_TICK_TICKCOUNT64
//		#define		_USE_TICK_STANDARD_HIGH_RESOLUTION
//		#define		_USE_TICK_STANDARD_MONOTONIC
//		#define		_USE_TICK_STANDARD_SYSTEM
//
// 2) Time
//		#define		_USE_TIME_TICKCOUNT32
//		#define		_USE_TIME_TICKCOUNT64
//		#define		_USE_TIME_STANDARD_HIGH_RESOLUTION
//		#define		_USE_TIME_STANDARD_MONOTONIC
//		#define		_USE_TIME_STANDARD_SYSTEM
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Definitions)
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Include)
//-----------------------------------------------------------------------------
// 1) Standard Files
#include <chrono>
#include <ctime>
#include <ratio>
#include <time.h>
#include <type_traits>

#if !defined(_MSC_VER)

#include <sys/time.h>

namespace std
{
namespace chrono
{
	template<class _Ty>
	struct _Is_duration : std::false_type	{};

	template<class _Rep, class _Period>
	struct _Is_duration<std::chrono::duration<_Rep, _Period>> : std::true_type	{};
}
}
#endif

#if !defined (_MSC_VER)
inline uint64_t GetTickCount64()
{
	timeval	tick;
    gettimeofday (&tick, nullptr);
    return (static_cast<uint64_t>(tick.tv_sec)*1000 + static_cast<uint64_t>(tick.tv_usec)/1000);
}
#endif


//-----------------------------------------------------------------------------
// Timer
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning(disable:28159)
#endif

// 1) Clocks
struct windows_tick32
{
	#define _CGTICK64_TICKS_PER_TIME_T	1000000ll
	
	typedef uint32_t								rep;
	typedef std::ratio<1, 1000>						period;
	typedef std::chrono::duration<rep, period>		duration;
	typedef std::chrono::time_point<windows_tick32>	time_point;
	static const bool	is_monotonic	 = false;
	static const bool	is_steady		 = false;

	static time_point now() NOEXCEPT							{	return (time_point(duration(GetTickCount())));}
	static time_t to_time_t(const time_point& _Time) NOEXCEPT	{	return static_cast<time_t>(_Time.time_since_epoch().count()/ _CGTICK64_TICKS_PER_TIME_T);}
	static time_point from_time_t(time_t _Tm) NOEXCEPT			{	return (time_point(duration(_Tm * _CGTICK64_TICKS_PER_TIME_T)));}
};

struct windows_tick64
{
	#define _CGTICK64_TICKS_PER_TIME_T	1000000ll
	
	typedef uint64_t								rep;
	typedef std::ratio<1, 1000>						period;
	typedef std::chrono::duration<rep, period>		duration;
	typedef std::chrono::time_point<windows_tick64>	time_point;
	static const bool	is_monotonic	 = false;
	static const bool	is_steady		 = false;

	static time_point now() NOEXCEPT							{	return (time_point(duration(GetTickCount64())));}
	static time_t to_time_t(const time_point& _Time) NOEXCEPT	{	return static_cast<time_t>(_Time.time_since_epoch().count()/ _CGTICK64_TICKS_PER_TIME_T);}
	static time_point from_time_t(time_t _Tm) NOEXCEPT			{	return (time_point(duration(_Tm * _CGTICK64_TICKS_PER_TIME_T)));}
};

#if defined(_MSC_VER)
	#pragma warning(default:28159)
#endif


//-----------------------------------------------------------------------------
// Timers for TICK
//-----------------------------------------------------------------------------
namespace CGD
{
namespace TICK
{
#if defined(_USE_TICK_STANDARD_HIGH_RESOLUTION)
// 1) Standard Library Timer (High Resolution)
	typedef std::chrono::high_resolution_clock	CLOCK;

#elif defined(_USE_TICK_STANDARD_MONOTONIC)
// 2) Standard Library Timer (Monotonic Timer)
	typedef std::chrono::monotonic_clock		CLOCK;

#elif defined(_USE_TICK_STANDARD_SYSTEM)
// 3) Standard Library Timer (System Timer)
	typedef std::chrono::system_clock			CLOCK;

#elif defined(_USE_TICK_STANDARD_STEADY)
// 4) Standard Library TImer (Steady Clock)
	typedef std::chrono::steady_clock			CLOCK;

#elif defined(_USE_TICK_TICKCOUNT64)
// 5) Windows TickCount64
	typedef windows_tick64						CLOCK;

#elif defined(_USE_TICK_TICKCOUNT32)
// 6) Windows TickCount64
	typedef windows_tick32						CLOCK;

#else
// 7) Not Defined!
	#error "CGD::TICK not defined!"
#endif


//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------
// 1) Point/Duration
typedef	CLOCK::time_point			time_point;
typedef	CLOCK::duration				duration;

// 2) Get Now Tick
inline time_point	now()			{	return (CLOCK::now)();}

// 3) Seconds ...
typedef std::chrono::duration<uint64_t, std::ratio<1, 1000>>	milliseconds;
typedef std::chrono::duration<uint64_t>							seconds;
typedef std::chrono::duration<uint64_t, std::ratio<60>>			minutes;
typedef std::chrono::duration<uint64_t, std::ratio<60*60>>		hours;
typedef std::chrono::duration<uint64_t, std::ratio<60*60*24>>	days;
typedef std::chrono::duration<uint64_t, std::ratio<60*60*24*7>>	weeks;

inline	time_point	zero()			{	return time_point(duration::zero());}
inline	time_point	(max)()			{	return time_point((duration::max)());}

template<class _To, class _Rep, class _Period>
_To DURATION_CAST(const std::chrono::duration<_Rep, _Period>& _Dur)
{
	return std::chrono::duration_cast<_To, _Rep, _Period>(_Dur);
}

}
}

