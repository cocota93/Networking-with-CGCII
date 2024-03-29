
//*****************************************************************************
//*                                                                           *
//*                                CGD::buffer                                *
//*                      Ver 2.0pre / Release 2015.01.05                      *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.com           *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// Includes
//
//-----------------------------------------------------------------------------
// 1) C++ Standard Libraries and Common Includes
#include <cstdint>
#include <cwchar>
#include <cstdarg>
#include <cassert>

// 2) 
#if defined(_MSC_VER)
	#include <xmemory>

	// Template) Visual C++과 gcc의 template 처리 방법의 차이로 인한 것
	#define	TEMPLATE	

#else
	#include <memory.h>
	#define	_aligned_malloc(a,b)	malloc(a)	

	#define	TEMPLATE	template

#endif

#include <stdexcept>
#include <malloc.h>
#include <stdarg.h>
#include <type_traits>

// 3) C++ Standard Template Libraries
namespace std
{
//template<class __TA, size_t __TB> class array;

template<class __TA, class __TB> class vector;
template<class __TA, class __TB> class deque;
template<class __TA, class __TB> class list;
template<class __TA, class __TB> class deque;

template<class __TA, class __TB, class __TC> class set;
template<class __TA, class __TB, class __TC> class multiset;

template<class __TA, class __TB, class __TC, class __TD> class map;
template<class __TA, class __TB, class __TC, class __TD> class multimap;

template<class __TA, class __TB, class __TC, class __TD> class hash_map;
template<class __TA, class __TB, class __TC, class __TD> class hash_multimap;

template<class __TA, class __TB, class __TC, class __TD> class unordered_set;
template<class __TA, class __TB, class __TC, class __TD> class unordered_multiset;

template<class __TA, class __TB, class __TC, class __TD, class __TE> class unordered_map;
template<class __TA, class __TB, class __TC, class __TD, class __TE> class unordered_multimap;
}

namespace CGD
{
template<class __TA, size_t __TB>	class static_vector;
template<class __TA>				class placement_vector;
template<class __TA, class __TB>	class circular_list;
}

// Defined in CGBufferClasses
template<class T> class CGPTR;
template<class T> class CGOWN;
template <class TOBJECT> class NCGPoolable;

#ifndef CGNEW_DEBUG_INFO_PARAMETERS
	#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
		// _CGNEW
		template <class TOBJECT, class... TARGS>
		typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
		_CGNEW(TARGS... _Args);
		template <class TOBJECT, class... TARGS>
		typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
		_CGNEW(TARGS... _Args);

		// _CGNEW_OWN
		template <class TOBJECT, class... TARGS>
		typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGOWN<TOBJECT>>::type
		_CGNEW_OWN(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _Args);
		template <class TOBJECT, class... TARGS>
		typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGOWN<TOBJECT>>::type
		_CGNEW_OWN(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _Args);

	#else
		template <class TOBJECT>
		typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
		_CGNEW();
		template <class TOBJECT>
		typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
		_CGNEW();

		// _CGNEW_OWN
		template <class TOBJECT>
		typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGOWN<TOBJECT>>::type
		_CGNEW_OWN();
		template <class TOBJECT>
		typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGOWN<TOBJECT>>::type
		_CGNEW_OWN();

	#endif
#endif


// 3) 
#include "CGDbufferConfigures.h"


//-----------------------------------------------------------------------------
//
// Disable Warning
//
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#include <sal.h>
	#if _MSC_VER<1700
		#define _In_reads_z_(a)
		#define _In_reads_(a)
		#define _In_reads_bytes_(a)
		#define	_Out_writes_(a)
		#define	_Field_size_bytes_(a)
	#endif
#else
	#define	_In_
	#define	_Inout_
	#define	_Inout_z_
	#define	_In_z_
	#define	_In_z_count_(a)
	#define	_In_opt_
	#define _In_reads_z_(a)
	#define _In_reads_(a)
	#define _In_reads_bytes_(a)
	#define	_Out_writes_(a)
	#define	_Field_size_bytes_(a)
	#define	__out_ecount(a)

	#define _ASSERT(a)

	#define	__FUNCTION__ ""
#endif

//-----------------------------------------------------------------------------
// 
// Memory Definitions
//
//-----------------------------------------------------------------------------
// 1) Definitions
#define	CGMEMPTR		CGD::ptr

#if defined(_MSC_VER)
	#define	CGMALLOC(size)	_aligned_malloc(size, 64)
	#define	CGFREE(ptr)		_aligned_free(ptr)
#else
	#define	CGMALLOC(size)	malloc(size)
	#define	CGFREE(ptr)		free(ptr)
#endif

namespace CGD
{

#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class...> struct enable_if_exist	{ typedef void type;};
#else
	template<class A, class B=void, class C=void, class D=void, class E=void, class F=void>	struct enable_if_exist	{	typedef void type;};
#endif

template<class, class = void>	struct is_iterator : std::false_type {};
template<class _Ty>				struct is_iterator<_Ty*> : std::true_type {};
template<class _Ty>				struct is_iterator<_Ty, typename enable_if_exist<
	typename _Ty::iterator_category,
	typename _Ty::value_type,
	typename _Ty::difference_type,
	typename _Ty::pointer,
	typename _Ty::reference
>::type>
: std::true_type
{
};

#ifdef _SUPPORT_CPP11_TRAITS
	#if defined(_MSC_VER)
		template <typename T> struct is_memcopy_able	{ static const bool value = std::is_trivially_copyable<T>::value && !std::is_pointer<T>::value;};
	#else
		template <typename T> struct is_memcopy_able	{ static const bool value = __has_trivial_copy(T) && !std::is_pointer<T>::value;};
	#endif
#else
template <typename T> struct is_memcopy_able	{ static const bool value = std::is_arithmetic<T>::value && !std::is_pointer<T>::value;};
#endif

}


//-----------------------------------------------------------------------------
//
// General Definitions
//
//-----------------------------------------------------------------------------
	// 2) CGD Assert
#define	CGD_ASSERT(condition, state)		if((condition)==false) { _ASSERT(condition); state;}


//-----------------------------------------------------------------------------
//
// 각종 append(<<)와 Extract(>>)용 정의들
//
//-----------------------------------------------------------------------------
namespace CGD
{

// Protytype) 
class ptr;
class buffer;

// 1) Skip
class SKIP
{
public:
	SKIP(size_t _Amount) : m_skip(_Amount) {}
public:
	size_t	m_skip;
};


// 2) Pointer (T형은 Pointer형이 될수는 없다.)
template <class T, class TENABLE = typename std::enable_if<!std::is_pointer<T>::value, void>::type>
class POINTER
{
public:
	POINTER() : ptr(nullptr) {}
public:
	T*		ptr;

public:
	T&		operator *() { return *ptr; }
	T*		operator ->() { return ptr; }
};

template<class I, class TENABLE = typename std::enable_if<is_iterator<I>::value, void>::type>
class _ITERATOR
{
public:
	_ITERATOR(const I& _Iter_begin, const I& _Iter_end) : iterFirst(_Iter_begin), iterLast(_Iter_end) {}
public:
	I		iterFirst;
	I		iterLast;
};

template<class I>
typename std::enable_if<is_iterator<I>::value, _ITERATOR<I,void>>::type
ITERATOR(const I& _Iter_begin, const I& _Iter_end)
{
	return	_ITERATOR<I, void>(_Iter_begin, _Iter_end);
}

// 3) Web String
struct WEB {};

// 3) Web String
struct WEB_MODIFY {};

// 4) Text
template <class T>
struct text
{
public:
	text() {}
	text(const text& _Rhs) : p(_Rhs.p) {}
	text(const T* _zstr) : p(_zstr) {}

public:
	text&		operator=(const text& _Rhs)		{ p = _Rhs.p; return *this; }
	text&		operator=(const T* _Rhs)		{ p = _Rhs; return *this; }

	bool	operator==(const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) == 0; }
	bool	operator==(const T* _Rhs) const		{ return std::char_traits<T>::compare(p, _Rhs, 0) == 0; }
	bool	operator!=(const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) != 0; }
	bool	operator!=(const T* _Rhs) const		{ return std::char_traits<T>::compare(p, _Rhs, 0) != 0; }
	bool	operator>=(const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) >= 0; }
	bool	operator>=(const T* _Rhs) const		{ return std::char_traits<T>::compare(p, _Rhs, 0) >= 0; }
	bool	operator> (const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) > 0; }
	bool	operator> (const T* _Rhs) const		{ return std::char_traits<T>::compare(p, _Rhs, 0) > 0; }
	bool	operator<=(const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) <= 0; }
	bool	operator<=(const T* _Rhs) const		{ return std::char_traits<T>::compare(p, _Rhs, 0) <= 0; }
	bool	operator< (const text& _Rhs) const	{ return std::char_traits<T>::compare(p, _Rhs.p, 0) < 0; }
	bool	operator< (const T* _Rhs) const		{ return std::char_traits<T>::compare(p, _Rhs, 0) < 0; }
			operator const T*() const			{ return p; }
public:
	const T*	p;
};

template <class T>
text<T> _text(const T* _String)
{
	return text<T>(_String);
}

typedef text<char>		TEXT_CHAR;
typedef text<wchar_t>	TEXT_WCHAR;
typedef TEXT_CHAR		TEXT_WEB;

// 7) 
template<typename T, size_t X>
struct _RETURN_ARRAY
{
	_RETURN_ARRAY() {}
	T value[X];

	T&			operator [](size_t _Index)		{	CGD_ASSERT(_Index<X, ); if(_Index>=X) throw std::out_of_range("_Index is Out of Range!!(" __FUNCTION__ ")"); return value[_Index];}
};

template<typename T, size_t X>
struct _STORE_ARRAY
{
	_STORE_ARRAY(T* p) : value(p) {}
	_STORE_ARRAY&	operator=(const _RETURN_ARRAY<T, X>& rhs) { for (int i = 0; i < X; ++i)value[i] = rhs.value[i]; return *this; }
	_STORE_ARRAY&	operator=(const T* rhs)		{ int i=0; if(rhs!=nullptr){ for (; (i<(X-1)) && (*rhs!=0); ++i, ++rhs) value[i] = *rhs;}  value[i]=0; return *this; }
	T*	value;
};

template<typename T, size_t X>
_STORE_ARRAY<T, X> STORE(T(&p)[X])
{
	return _STORE_ARRAY<T, X>(p);
}

template<size_t X, typename T>
_STORE_ARRAY<T, X> STORE(T* p)
{
	return _STORE_ARRAY<T, X>(p);
}


class POS
{
public:
	POS() : offset(0) {}
	POS(const POS& p) : offset(p.offset) {}
	explicit POS(int p) : offset(p) {}
public:
	int		get_pos() const { return offset; }
	void	set_pos(int _Offset) { offset = _Offset; }

	POS&	operator=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
	POS&	operator=(int _Rhs) { offset += _Rhs; return *this; }

	bool	operator==(const POS& _Rhs) const { return offset == _Rhs.offset; }
	bool	operator==(int _Rhs) const { return offset == _Rhs; }
	bool	operator!=(const POS& _Rhs) const { return offset != _Rhs.offset; }
	bool	operator!=(int _Rhs) const { return offset != _Rhs; }
	bool	operator>=(const POS& _Rhs) const { return offset >= _Rhs.offset; }
	bool	operator>=(int _Rhs) const { return offset >= _Rhs; }
	bool	operator> (const POS& _Rhs) const { return offset > _Rhs.offset; }
	bool	operator> (int _Rhs) const { return offset > _Rhs; }
	bool	operator<=(const POS& _Rhs) const { return offset <= _Rhs.offset; }
	bool	operator<=(int _Rhs) const { return offset <= _Rhs; }
	bool	operator< (const POS& _Rhs) const { return offset < _Rhs.offset; }
	bool	operator<  (int _Rhs) const { return offset < _Rhs; }

	POS&	operator+=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
	POS&	operator+=(int _Rhs) { offset += _Rhs; return *this; }
	POS&	operator-=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
	POS&	operator-=(int _Rhs) { offset += _Rhs; return *this; }
	POS&	operator*=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
	POS&	operator*=(int _Rhs) { offset += _Rhs; return *this; }
	POS&	operator/=(const POS& _Rhs) { offset += _Rhs.offset; return *this; }
	POS&	operator/=(int _Rhs) { offset += _Rhs; return *this; }

	operator int&() { return offset; }
	operator const int&() const { return offset; }
public:
	int		offset;
};

// ----------------------------------------------------------------------------
// Static
// ----------------------------------------------------------------------------
template<size_t N>	_CONSTEXPR size_t const_string_length(const char(&)[N])		{ return N - 1; }
template<size_t N>	_CONSTEXPR size_t const_string_length(const wchar_t(&)[N])	{ return N - 1; }
template<size_t N>	_CONSTEXPR size_t const_string_length(const char16_t(&)[N]) { return N - 1; }
template<size_t N>	_CONSTEXPR size_t const_string_length(const char32_t(&)[N]) { return N - 1; }

template<size_t N>	_CONSTEXPR size_t const_string_size(const char(&)[N])		{ return (N - 1)*sizeof(char); }
template<size_t N>	_CONSTEXPR size_t const_string_size(const wchar_t(&)[N])	{ return (N - 1)*sizeof(wchar_t); }
template<size_t N>	_CONSTEXPR size_t const_string_size(const char16_t(&)[N])	{ return (N - 1)*sizeof(char16_t); }
template<size_t N>	_CONSTEXPR size_t const_string_size(const char32_t(&)[N])	{ return (N - 1)*sizeof(char32_t); }

template <class T, size_t N>
class const_string
{
public:
	const T* const	p;

	_CONSTEXPR const_string(const T(&_a)[N]) : p(_a) {}
	_CONSTEXPR std::size_t size() const				{ return N; }

	const_string<T,N>&	operator=(const const_string<T,N>& _Rhs)	{	p=_Rhs.p; return *this;}
};

template<class T, size_t N>
_CONSTEXPR const_string<T, N> _const(const T(&_Str)[N])
{
	return const_string<T, N>(_Str);
}
	
template <class T, size_t N>
class const_text
{
public:
	const T* const	p;

	_CONSTEXPR const_text(const T(&_a)[N]) : p(_a)	{}
	_CONSTEXPR std::size_t size() const				{ return N; }

	const_text<T,N>&	operator=(const const_text<T,N>& _Rhs)	{	p=_Rhs.p; return *this;}
};

template<class T, size_t N>
_CONSTEXPR const_text<T, N> _const_text(const T(&_Str)[N])
{
	return const_text<T, N>(_Str);
}


//-----------------------------------------------------------------------------
//
// Time
//
//-----------------------------------------------------------------------------
struct DATETIME
{
public:
	DATETIME() : wYear(), wMonth(), wDay(), wHour(), wMinute(), wSecond(), dwMillisecond()	{}
public:
	static bool _is_leap_year(int _year)
	{
		return _year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0);
	}

	static int _get_day_of_year(int _year, int _month, int _day)
	{
		// Static)                  0    1    2    3    4    5    6    7    8    9   10   11   12   
		static int	t[2][14] = {{   0,   0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334 },
								{   0,   0,  31,  60,  91, 121, 152, 182, 213, 244, 274, 305, 335 }};

		return	t[_is_leap_year(_year)][_month] + _day;
	}

	static int _get_day_of_week(int _year, int _month, int _day)
	{
		// Static) 
		static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

		// 1) 2월 을 초과하지 않았을 경우 1을 뺀다.
		_year -= _month < 3;

		// 2) 요일을 리턴한다.
		return (_year + _year / 4 - _year / 100 + _year / 400 + t[_month - 1] + _day) % 7;
	}


	DATETIME(const tm& _Value) : 
		wYear			(static_cast<decltype(wYear)>	(_Value.tm_year+1900)),
		wMonth			(static_cast<decltype(wMonth)>	(_Value.tm_mon)),
		wDay			(static_cast<decltype(wDay)>	(_Value.tm_mday)),
		wHour			(static_cast<decltype(wHour)>	(_Value.tm_hour)),
		wMinute			(static_cast<decltype(wMinute)>	(_Value.tm_min)),
		wSecond			(static_cast<decltype(wSecond)>	(_Value.tm_sec)),
		dwMillisecond	(0)
	{
	}
				operator	tm() const					{ return get_tm();}
	DATETIME&	operator =(const tm& _Rhs)				{ set_time(_Rhs); return *this;}
	void set_time(const tm& _Value)
	{
		wYear				 = static_cast<decltype(wYear)>		(_Value.tm_year+1900);
		wMonth				 = static_cast<decltype(wMonth)>	(_Value.tm_mon);
		wDay				 = static_cast<decltype(wDay)>		(_Value.tm_mday);
		wHour				 = static_cast<decltype(wHour)>		(_Value.tm_hour);
		wMinute				 = static_cast<decltype(wMinute)>	(_Value.tm_min);
		wSecond				 = static_cast<decltype(wSecond)>	(_Value.tm_sec);
		dwMillisecond		 = 0; // Don't care
	}
	tm get_tm() const
	{
		// Check) 
		_ASSERT(wMonth>0 && wMonth <= 12);
		_ASSERT(wDay>0 && wDay <= 31);
		_ASSERT(wHour<24);
		_ASSERT(wMinute<60);
		_ASSERT(wSecond<60);

		tm		temp{0};

		// Check)
		if(wMonth==0 || wMonth>12 || wDay == 0 || wDay>31 || wHour>24 || wMinute>60 || wSecond>60) return temp;

		auto	year		 = wYear;

		temp.tm_year		 = static_cast<decltype(tm::tm_year)>	(year -1900);
		temp.tm_mon			 = static_cast<decltype(tm::tm_mon)>	(wMonth);
		temp.tm_mday		 = static_cast<decltype(tm::tm_mday)>	(wDay);
		temp.tm_yday		 = static_cast<decltype(tm::tm_yday)>	(_get_day_of_year(year, temp.tm_mon, temp.tm_mday));
		temp.tm_wday		 = static_cast<decltype(tm::tm_wday)>	(_get_day_of_week(year, temp.tm_mon, temp.tm_mday));
		temp.tm_hour		 = static_cast<decltype(tm::tm_hour)>	(wHour);
		temp.tm_min			 = static_cast<decltype(tm::tm_min)>	(wMinute);
		temp.tm_sec			 = static_cast<decltype(tm::tm_sec)>	(wSecond);
		temp.tm_isdst		 = static_cast<decltype(tm::tm_isdst)>	(0);

		return	temp;
	}

#if defined(_SYSTEMTIME_) || defined(_MINWINBASE_)
	DATETIME(const SYSTEMTIME& _Value)					{ set_time(_Value);}
				operator	SYSTEMTIME() const			{ return get_SYSTEMTIME();}
	DATETIME&	operator =(const SYSTEMTIME& _Rhs)		{ set_time(_Rhs); return *this;}
	void set_time(const SYSTEMTIME& _Value)
	{
		wYear				 = static_cast<decltype(wYear)>			(_Value.wYear);
		wMonth				 = static_cast<decltype(wMonth)>		(_Value.wMonth);
		wDay				 = static_cast<decltype(wDay)>			(_Value.wDay);
		wHour				 = static_cast<decltype(wHour)>			(_Value.wHour);
		wMinute				 = static_cast<decltype(wMinute)>		(_Value.wMinute);
		wSecond				 = static_cast<decltype(wSecond)>		(_Value.wSecond);
		dwMillisecond		 = static_cast<decltype(dwMillisecond)>	(_Value.wMilliseconds);
	}
	SYSTEMTIME get_SYSTEMTIME() const
	{
		SYSTEMTIME	temp;

		temp.wYear			 = static_cast<decltype(SYSTEMTIME::wYear)>			(wYear);
		temp.wMonth			 = static_cast<decltype(SYSTEMTIME::wMonth)>		(wMonth);
		temp.wDay			 = static_cast<decltype(SYSTEMTIME::wDay)>			(wDay);
		temp.wDayOfWeek		 = static_cast<decltype(SYSTEMTIME::wDayOfWeek)>	(_get_day_of_week(temp.wYear, temp.wMonth, temp.wDay));
		temp.wHour			 = static_cast<decltype(SYSTEMTIME::wHour)>			(wHour);
		temp.wMinute		 = static_cast<decltype(SYSTEMTIME::wMinute)>		(wMinute);
		temp.wSecond		 = static_cast<decltype(SYSTEMTIME::wSecond)>		(wSecond);
		temp.wMilliseconds	 = static_cast<decltype(SYSTEMTIME::wMilliseconds)>	(dwMillisecond);

		return	temp;
	}
#endif

#ifdef _CGD_TIME
			 DATETIME(const CGD::TIME::_POINT& _Value)					{ set_time(_Value);}
			 DATETIME(const CGD::TIME::LOCAL::time_point& _Value)		{ set_time(static_cast<const CGD::TIME::_POINT&>(_Value));}
			 DATETIME(const CGD::TIME::SYSTEM::time_point& _Value)		{ set_time(static_cast<const CGD::TIME::_POINT&>(_Value));}

				operator	CGD::TIME::_POINT() const					{ return get_CGDTIME();}
				operator	CGD::TIME::LOCAL::time_point() const		{ CGD::TIME::_POINT t = get_CGDTIME(); return static_cast<CGD::TIME::LOCAL::time_point&>(t); }
				operator	CGD::TIME::SYSTEM::time_point() const		{ CGD::TIME::_POINT t = get_CGDTIME(); return static_cast<CGD::TIME::SYSTEM::time_point&>(t);}

	DATETIME&	operator =(const CGD::TIME::_POINT& _Rhs)				{ set_time(_Rhs); return *this;}
	DATETIME&	operator =(const CGD::TIME::LOCAL::time_point& _Rhs)	{ set_time(static_cast<const CGD::TIME::_POINT&>(_Rhs)); return *this;}
	DATETIME&	operator =(const CGD::TIME::SYSTEM::time_point& _Rhs)	{ set_time(static_cast<const CGD::TIME::_POINT&>(_Rhs)); return *this;}

	void set_time(const CGD::TIME::_POINT& _Value)
	{
		wYear				 = static_cast<decltype(wYear)>			(_Value.get_year());
		wMonth				 = static_cast<decltype(wMonth)>		(_Value.get_month());
		wDay				 = static_cast<decltype(wDay)>			(_Value.get_day());
		wHour				 = static_cast<decltype(wHour)>			(_Value.get_hour());
		wMinute				 = static_cast<decltype(wMinute)>		(_Value.get_minute());
		wSecond				 = static_cast<decltype(wSecond)>		(_Value.get_second());
		dwMillisecond		 = static_cast<decltype(dwMillisecond)>	(_Value.get_millisecond());
	}
	CGD::TIME::_POINT get_CGDTIME() const
	{
		auto	temp		 = CGD::TIME::_POINT::create_instance();

		temp.set_year		(static_cast<decltype(SYSTEMTIME::wYear)>(wYear));
		temp.set_month		(static_cast<decltype(SYSTEMTIME::wMonth)>(wMonth));
		temp.set_day		(static_cast<decltype(SYSTEMTIME::wDay)>(wDay));
		temp.set_dayofweek	(static_cast<decltype(SYSTEMTIME::wDayOfWeek)>(_get_day_of_week(temp.get_year(), temp.get_month(), temp.get_day())));
		temp.set_hour		(static_cast<decltype(SYSTEMTIME::wHour)>(wHour));
		temp.set_minute		(static_cast<decltype(SYSTEMTIME::wMinute)>(wMinute));
		temp.set_second		(static_cast<decltype(SYSTEMTIME::wSecond)>(wSecond));
		temp.set_millisecond(static_cast<decltype(SYSTEMTIME::wMilliseconds)>(dwMillisecond));

		return	temp;
	}
	CGD::TIME::LOCAL::time_point get_CGDLOCALTIME() const
	{
		CGD::TIME::LOCAL::time_point	temp;

		temp.set_year		(static_cast<decltype(SYSTEMTIME::wYear)>(wYear));
		temp.set_month		(static_cast<decltype(SYSTEMTIME::wMonth)>(wMonth));
		temp.set_day		(static_cast<decltype(SYSTEMTIME::wDay)>(wDay));
		temp.set_dayofweek	(static_cast<decltype(SYSTEMTIME::wDayOfWeek)>(_get_day_of_week(temp.get_year(), temp.get_month(), temp.get_day())));
		temp.set_hour		(static_cast<decltype(SYSTEMTIME::wHour)>(wHour));
		temp.set_minute		(static_cast<decltype(SYSTEMTIME::wMinute)>(wMinute));
		temp.set_second		(static_cast<decltype(SYSTEMTIME::wSecond)>(wSecond));
		temp.set_millisecond(static_cast<decltype(SYSTEMTIME::wMilliseconds)>(dwMillisecond));

		return	temp;
	}
	CGD::TIME::SYSTEM::time_point get_CGDSYSTEMTIME() const
	{
		CGD::TIME::SYSTEM::time_point	temp;

		temp.set_year		(static_cast<decltype(SYSTEMTIME::wYear)>(wYear));
		temp.set_month		(static_cast<decltype(SYSTEMTIME::wMonth)>(wMonth));
		temp.set_day		(static_cast<decltype(SYSTEMTIME::wDay)>(wDay));
		temp.set_dayofweek	(static_cast<decltype(SYSTEMTIME::wDayOfWeek)>(_get_day_of_week(temp.get_year(), temp.get_month(), temp.get_day())));
		temp.set_hour		(static_cast<decltype(SYSTEMTIME::wHour)>(wHour));
		temp.set_minute		(static_cast<decltype(SYSTEMTIME::wMinute)>(wMinute));
		temp.set_second		(static_cast<decltype(SYSTEMTIME::wSecond)>(wSecond));
		temp.set_millisecond(static_cast<decltype(SYSTEMTIME::wMilliseconds)>(dwMillisecond));

		return	temp;
	}

#endif
public:
	uint16_t	wYear;
	uint16_t	wMonth;
	uint16_t	wDay;
	uint16_t	wHour;
	uint16_t	wMinute;
	uint16_t	wSecond;
	uint32_t	dwMillisecond;
};



//-----------------------------------------------------------------------------
//
// 
//
//-----------------------------------------------------------------------------
// 1) Bounding Check를 위한 정보
struct CGD_CHECK_BOUND
{
public:
	void*	bound_lower;
	void*	bound_upper;
public:
	CGD_CHECK_BOUND() : bound_lower(0), bound_upper(reinterpret_cast<void*>(-1)) {}
	CGD_CHECK_BOUND(void* a, void* b) : bound_lower(a), bound_upper(b) {}
	void	clear() { bound_lower = 0; bound_upper = reinterpret_cast<void*>(-1); }
};

// 2) 
#ifdef _CGD_ENABLE_BUFFER_BOUND_CHECK
	#define _CGD_COMMA						,
	#define _CGD_BOUND_INFO_GET				_get_check_bound()
	#define _CGD_BOUND_INFO_PARAM			CGD_CHECK_BOUND _bound
	#define _CGD_BOUND_INFO_PASS			_bound
	#define	_CGD_BOUND_INFO_NOWARNING		_bound;
	#define	_CGD_BOUND_INFO(state)			state;
	#define _CGD_BUFFER_BOUND_CHECK(condition)	if((condition)==false) { _ASSERT(false);}
#else
	#define _CGD_COMMA 
	#define _CGD_BOUND_INFO_GET
	#define _CGD_BOUND_INFO_PARAM
	#define _CGD_BOUND_INFO_PASS
	#define	_CGD_BOUND_INFO_NOWARNING		
	#define	_CGD_BOUND_INFO(state)
	#define _CGD_BUFFER_BOUND_CHECK(condition)
#endif


//-----------------------------------------------------------------------------
//
// Buffer Serialization
//
//-----------------------------------------------------------------------------
#define	CGD_BUFFER_SERIAZABLE(_object)	\
				_object(const CGD::_PASS& _Rhs) : _object()							{	ProcessSerializeIn(*_Rhs.m_pbuffer);}	\
				_object& operator=(const CGD::_PASS& _Rhs)							{	ProcessSerializeIn(*_Rhs.m_pbuffer); return *this;}

#define	DEFINE_CGD_BUFFER_SERIALIZE(class_name, ...)	\
				CGD_BUFFER_SERIAZABLE (class_name);	\
				virtual	bool	ProcessSerializeIn(CGD::buffer& _Buffer) override	{ _Buffer.extract(std::tie(__VA_ARGS__)); return true; }\
				virtual	bool	ProcessSerializeOut(CGD::buffer& _Buffer) override	{ _Buffer.append(std::tie(__VA_ARGS__)); return	true; }\
				virtual size_t	ProcessSerializeSizeOf() const override				{ return CGD::SizeOf(std::tie(__VA_ARGS__));}

class _PASS
{
public:
	_PASS(_CGD_BOUND_INFO_PARAM _CGD_COMMA buffer* v) : m_pbuffer(v) { _CGD_BOUND_INFO(m_bound = _bound;) }
public:
	buffer*			m_pbuffer;

#ifdef _CGD_ENABLE_BUFFER_BOUND_CHECK
	CGD_CHECK_BOUND	m_bound;
#endif
};

class IBufferSerializable
{
public:
	virtual	bool	ProcessSerializeIn(CGD::buffer& _Buffer) = 0;
	virtual	bool	ProcessSerializeOut(CGD::buffer& _Buffer) = 0;

#if defined(_SUPPORT_SIZE_OF)
	virtual size_t	ProcessSerializeSizeOf() const = 0;
#endif
public:
	IBufferSerializable&	operator=(_PASS& _Rhs) { ProcessSerializeIn(*_Rhs.m_pbuffer); return *this; }
};


//-----------------------------------------------------------------------------
// Traits
//-----------------------------------------------------------------------------
// Is String Type)
template<class T> struct is_string_type : public std::false_type {};
template<> struct is_string_type<char> : public std::true_type{};
template<> struct is_string_type<wchar_t> : public std::true_type{};
template<> struct is_string_type<char16_t> : public std::true_type{};
template<> struct is_string_type<char32_t> : public std::true_type{};
template<> struct is_string_type<const char> : public std::true_type{};
template<> struct is_string_type<const wchar_t> : public std::true_type{};
template<> struct is_string_type<const char16_t> : public std::true_type{};
template<> struct is_string_type<const char32_t> : public std::true_type{};

}


//-----------------------------------------------------------------------------
//
//   Liberal
//
//-----------------------------------------------------------------------------
//#if _MSC_VER>=_MSC_VER_2015
//inline CGD::text<char>		operator"" _z(const char* _Str, const std::size_t _Size)	{ return CGD::text<char>(_Str);}
//inline CGD::text<wchar_t>	operator"" _z(const wchar_t* _Str, const std::size_t _Size) { return CGD::text<wchar_t>(_Str);}
//inline CGD::text<char16_t>	operator"" _z(const char16_t* _Str, const std::size_t _Size){ return CGD::text<char16_t>(_Str);}
//inline CGD::text<char32_t>	operator"" _z(const char32_t* _Str, const std::size_t _Size){ return CGD::text<char32_t>(_Str);}
//#endif

//-----------------------------------------------------------------------------
//
//   
//
//-----------------------------------------------------------------------------
namespace CGD
{
// Base
template<class T, class FLAG = void> class _RH { public:	typedef	T &t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset) { return s->TEMPLATE _front_general<T> (_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset); } };
template<class T, class FLAG = void> class _AF { public:	typedef	T &t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data) { return s->TEMPLATE _prepend_general<T> (_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<class T, class FLAG = void> class _AB { public:	typedef	T &t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data) { return s->TEMPLATE _append_general<T> (_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<class T, class FLAG = void> class _BF { public:	typedef	T &t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s) { return *(T*)s->TEMPLATE _extract_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T)); } };



// Functions for 
#include "CGDbufferFunctions.h"

// Class for prepend)
template<class T, size_t X>	class _AF<T[X], typename std::enable_if<!is_string_type<T>::value>::type>		
														{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T (&data)[X])				{ return s->TEMPLATE _prepend_array<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)data, X);}};
#ifdef _SUPPORT_ZERO_SIZED_ARRAY
template<class T>			class _AF<T[], typename std::enable_if<!is_string_type<T>::value>::type>		
														{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T (&)[])					{ static_assert(false, "CGD::buffer don not support 'prepend' on unsized array (array size must be specified)"); return nullptr;}};
#endif
template<>					class _AF<buffer>			{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const buffer& data)				{ return s->_prepend_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<>					class _AF<SKIP>				{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const SKIP& data)					{ return s->_prepend_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA data.m_skip);}};
template<class T,class E>	class _AF<POINTER<T,E>>		{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const POINTER<T,E>& data)			{ auto& tmp=const_cast<CGD::POINTER<T,E>&>(data); return tmp.ptr=(T*)s->_prepend_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T));}};
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class... T>		class _AF<std::tuple<T...>> {	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::tuple<T...>& data)		{ return s->TEMPLATE _prepend_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
#endif
template<class T,class E>	class _AF<_ITERATOR<T,E>>	{public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const _ITERATOR<T,E>& data)		{ return _Xprepend_iterator(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data.iterFirst, data.iterLast);}};
#ifdef _SUPPORT_INITIALIZER_LIST
template<class T>			class _AF<std::initializer_list<T>>{public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::initializer_list<T>& data){ s->TEMPLATE _prepend_initializer_list(_CGD_BOUND_INFO_PASS _CGD_COMMA data); return get_front_ptr();}};
#endif


// Class for append)
template<class T, size_t X>	class _AB<T[X], typename std::enable_if<!is_string_type<T>::value>::type>		
														{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T (&data)[X])				{ return s->TEMPLATE _append_array<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)data, X);}};
#ifdef _SUPPORT_ZERO_SIZED_ARRAY
template<class T>			class _AB<T[], typename std::enable_if<!is_string_type<T>::value>::type>		
														{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T (&)[])					{ static_assert(false, "CGD::buffer don not support 'append' on unsized array (array size must be specified)"); return nullptr;}};
#endif
template<class T>			class _AB<T, typename std::enable_if<std::is_base_of<buffer, T>::value>::type>
														{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const buffer& data)				{ return s->_append_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<>					class _AB<SKIP>				{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const SKIP& data)					{ return s->_append_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA data.m_skip);}};
template<class T,class E>	class _AB<POINTER<T,E>>		{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const POINTER<T,E>& data)			{ auto& tmp=const_cast<CGD::POINTER<T,E>&>(data); return tmp.ptr=(T*)s->_append_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(T));}};

#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class... T>		class _AB<std::tuple<T...>> {	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::tuple<T...>& data)		{ return s->TEMPLATE _append_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
#endif
template<class T,class E>	class _AB<_ITERATOR<T,E>>{public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const _ITERATOR<T,E>& data)			{ return _Xappend_iterator(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data.iterFirst, data.iterLast);}};
#ifdef _SUPPORT_INITIALIZER_LIST
template<class T>			class _AB<std::initializer_list<T>>{public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::initializer_list<T>& data){ void* p=s->get_back_ptr(); s->TEMPLATE _append_initializer_list(_CGD_BOUND_INFO_PASS _CGD_COMMA data); return p;}};
#endif
template<class T>			class _AB<T, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
														{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)					{ _CGD_BOUND_INFO_NOWARNING; const_cast<T&>(data).ProcessSerializeOut(*s); return nullptr;}};
template<class T>			class _AB<CGPTR<T>, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
														{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ _CGD_BOUND_INFO_NOWARNING; if(data!=nullptr) {const_cast<T*>(data)->ProcessSerializeOut(*s);} else { s->TEMPLATE _append<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA COUNT_T(0)-1);} return nullptr;}};
template<class T>			class _AB<CGOWN<T>, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
														{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ _CGD_BOUND_INFO_NOWARNING; if(data!=nullptr) {const_cast<T*>(data)->ProcessSerializeOut(*s);} else { s->TEMPLATE _append<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA COUNT_T(0)-1);} return nullptr;}};

// Class for extract)
template<class T, size_t X>	class _BF<T[X], typename std::enable_if<!is_string_type<T>::value>::type>
														{	public:	typedef	_RETURN_ARRAY<T,X> t;template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return _Xextract_array<S,T,X>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
#ifdef _SUPPORT_ZERO_SIZED_ARRAY
template<class T>			class _BF<T[], typename std::enable_if<!is_string_type<T>::value>::type>
														{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ static_assert(false, "CGD::buffer don not support 'extract' on unsized array(use 'vector or list' instead)"); return nullptr;}};
#endif
template<class T>			class _BF<T, typename std::enable_if<std::is_base_of<buffer, T>::value>::type>
														{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return _Xextract_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};

template<>					class _BF<CGD::WEB>			{	public:	typedef	std::string t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return s->_extract_web(_CGD_BOUND_INFO_PASS);}};
template<>					class _BF<CGD::WEB_MODIFY>	{	public:	typedef	char* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return s->_extract_web_modify(_CGD_BOUND_INFO_PASS);}};
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class... T>		class _BF<std::tuple<T...>> {	public:	typedef	std::tuple<T...> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ std::tuple<T...> temp; s->TEMPLATE _extract_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return temp;} };
#endif
template<class T>			class _BF<T, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
														{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ _CGD_BOUND_INFO_NOWARNING; T tx; tx.ProcessSerializeIn(*s); return std::move(tx);}};
template<class T>			class _BF<CGPTR<T>, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
														{	public:	typedef	CGD::_PASS t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return CGD::_PASS(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<class T>			class _BF<CGOWN<T>, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
														{	public:	typedef	CGD::_PASS t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return CGD::_PASS(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};


// Class for front)
template<class T, size_t X> class _RH<T[X], typename std::enable_if<!is_string_type<T>::value>::type>
														{	public:	typedef	_RETURN_ARRAY<T,X> t; template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ S tempBuffer=*s+(size_t)_Offset; auto temp=_Xextract_array<S,T,X>(_CGD_BOUND_INFO_PASS _CGD_COMMA &tempBuffer); _Offset=(int)(tempBuffer.get_front_ptr()-s->get_front_ptr()); return temp;}};
#ifdef _SUPPORT_ZERO_SIZED_ARRAY
template<class T>			class _RH<T[], typename std::enable_if<!is_string_type<T>::value>::type>
														{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ static_assert(false, "CGD::buffer don not support 'front' on unsized array(use 'vector or list' instead)"); return nullptr;}};
#endif
template<class T>			class _RH<T, typename std::enable_if<std::is_base_of<buffer, T>::value>::type>
														{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ S tempBuffer=*s+(size_t)_Offset; auto temp = _Xextract_buffer<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA &tempBuffer); _Offset = (int)(tempBuffer.get_front_ptr() - s->get_front_ptr()); return temp;}};

template<>					class _RH<CGD::WEB>			{	public:	typedef	char* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->_front_web(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
template<>					class _RH<CGD::WEB_MODIFY>	{	public:	typedef	char* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ S tempBuffer=*s+(size_t)_Offset; return tempBuffer._extract_web_modify(_CGD_BOUND_INFO_PASS);}};
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template<class... T>		class _RH<std::tuple<T...>> {	public:	typedef	std::tuple<T...> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ S tempBuffer=*s+(size_t)_Offset; std::tuple<T...> temp; tempBuffer._extract_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); _Offset=(int)(tempBuffer.get_front_ptr()-s->get_front_ptr()); return temp;}};
#endif
template<class T>			class _RH<T, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
														{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ _CGD_BOUND_INFO_NOWARNING; S tempBuffer=*s+(size_t)_Offset; T tx; tx.ProcessSerializeIn(tempBuffer); return std::move(tx);}};
template<class T>			class _RH<CGPTR<T>, typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value>::type>
														{	public:	typedef	CGD::_PASS t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ S tempBuffer=*s+(size_t)_Offset; return CGD::_PASS(_CGD_BOUND_INFO_PASS _CGD_COMMA tempBuffer);}};


//-----------------------------------------------------------------------------
//
// For Time
//-----------------------------------------------------------------------------
// For tm)
template<>					class _AF<tm> { public:	typedef	void *t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const tm& data) { return s->_prepend_tm(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<>					class _AB<tm> { public:	typedef	void *t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const tm& data) { return s->_append_tm(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<>					class _BF<tm> { public:	typedef	tm t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s) { return s->_extract_tm(_CGD_BOUND_INFO_PASS); } };
template<>					class _RH<tm> { public:	typedef	tm t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset) { return s->_front_tm(_CGD_BOUND_INFO_PASS); } };

// For SYSTEMTIME)
#if defined(_SYSTEMTIME_) || defined(_MINWINBASE_)
template<>					class _AF<SYSTEMTIME> { public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const SYSTEMTIME& data) { return s->_prepend_SYSTEMTIME(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<>					class _AB<SYSTEMTIME> { public:	typedef	void *t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const SYSTEMTIME& data) { return s->_append_SYSTEMTIME(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<>					class _BF<SYSTEMTIME> { public:	typedef	SYSTEMTIME t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s) { return s->_extract_SYSTEMTIME(_CGD_BOUND_INFO_PASS); } };
template<>					class _RH<SYSTEMTIME> { public:	typedef	SYSTEMTIME t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset) { return s->_front_SYSTEMTIME(_CGD_BOUND_INFO_PASS); } };
#endif


#ifdef _CGD_TIME

// Class for prepend)
template<>					class _AF<CGD::TIME::time_point>			{ public:	typedef	void *t;							template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::TIME::time_point& data)			{ return s->_prepend_timepoint(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<>					class _AF<CGD::TIME::SYSTEM::time_point>	{ public:	typedef	void *t;							template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::TIME::SYSTEM::time_point& data)	{ return s->_prepend_timepoint_system(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<>					class _AF<CGD::TIME::LOCAL::time_point>		{ public:	typedef	void *t;							template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::TIME::LOCAL::time_point& data)		{ return s->_prepend_timepoint_local(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };

// Class for append)
template<>					class _AB<CGD::TIME::time_point>			{ public:	typedef	void *t;							template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::TIME::time_point& data)			{ return s->_append_timepoint(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<>					class _AB<CGD::TIME::SYSTEM::time_point>	{ public:	typedef	void *t;							template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::TIME::SYSTEM::time_point& data)	{ return s->_append_timepoint_system(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };
template<>					class _AB<CGD::TIME::LOCAL::time_point>		{ public:	typedef	void *t;							template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::TIME::LOCAL::time_point& data)		{ return s->_append_timepoint_local(_CGD_BOUND_INFO_PASS _CGD_COMMA data); } };

// Class for extract)
template<>					class _BF<CGD::TIME::time_point>			{ public:	typedef	CGD::TIME::time_point t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)												{ return s->_extract_timepoint(_CGD_BOUND_INFO_PASS); } };
template<>					class _BF<CGD::TIME::SYSTEM::time_point>	{ public:	typedef	CGD::TIME::SYSTEM::time_point t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)												{ return s->_extract_timepoint_system(_CGD_BOUND_INFO_PASS); } };
template<>					class _BF<CGD::TIME::LOCAL::time_point>		{ public:	typedef	CGD::TIME::LOCAL::time_point t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)												{ return s->_extract_timepoint_local(_CGD_BOUND_INFO_PASS); } };

// Class for front)
template<>					class _RH<CGD::TIME::time_point>			{ public:	typedef	CGD::TIME::time_point t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)							{ t temp; return temp; } };
template<>					class _RH<CGD::TIME::SYSTEM::time_point>	{ public:	typedef	CGD::TIME::SYSTEM::time_point t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)							{ t temp; return temp; } };
template<>					class _RH<CGD::TIME::LOCAL::time_point>		{ public:	typedef	CGD::TIME::LOCAL::time_point t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)							{ t temp; return temp; } };

#endif


//-----------------------------------------------------------------------------
//
// For Strings
//-----------------------------------------------------------------------------
// Class for prepend)
template<class T>			class _AF<T*, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ return s->TEMPLATE _prepend_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T, size_t N>	class _AF<T[N], typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ return s->TEMPLATE _prepend_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)data);}};
template<class T, size_t N>	class _AF<CGD::const_string<T, N>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::const_string<T, N>& data){ return s->TEMPLATE _prepend_const_string<T,N>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T>			class _AF<CGD::text<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::text<T>& data)			{ return s->TEMPLATE _prepend_text<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data.p);} };
template<class T, size_t N>	class _AF<CGD::const_text<T,N>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::const_text<T, N>& data){ return s->TEMPLATE _prepend_const_text<T,N>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);} };
template<class T>			class _AF<std::basic_string<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::basic_string<T>& data)	{ return s->TEMPLATE _prepend_string<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};


// Class for append)
template<class T>			class _AB<T*, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ return s->TEMPLATE _append_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T, size_t N>	class _AB<T[N], typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T* data)					{ return s->TEMPLATE _append_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (T*)data);}};
template<class T, size_t N>	class _AB<CGD::const_string<T,N>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::const_string<T, N>& data){ return s->TEMPLATE _append_const_string<T,N> (_CGD_BOUND_INFO_PASS _CGD_COMMA data);}};
template<class T>			class _AB<CGD::text<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::text<T>& data)			{ return s->TEMPLATE _append_text<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data.p);} };
template<class T, size_t N>	class _AB<CGD::const_text<T,N>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CGD::const_text<T,N>& data)	{ return s->TEMPLATE _append_const_text<T, N>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);} };
template<class T>			class _AB<std::basic_string<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	void* t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const std::basic_string<T>& data)	{ return s->TEMPLATE _append_string<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA data);} };


// Class for extract)
template<class T>			class _BF<T*, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	T* t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return s->TEMPLATE _extract_string_pointer<T>(_CGD_BOUND_INFO_PASS);}};
template<class T, size_t N>	class _BF<T[N], typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	T* t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)									{ return s->TEMPLATE _extract_string_pointer<T>(_CGD_BOUND_INFO_PASS);}};
template<class T>			class _BF<CGD::text<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	std::basic_string<T> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return s->TEMPLATE _extract_text<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA static_cast<T>(NULL));} };
template<class T>			class _BF<std::basic_string<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	std::basic_string<T> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return s->TEMPLATE _extract_string<T>(_CGD_BOUND_INFO_PASS);} };


// Class for front)
template<class T>			class _RH<T*, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	T* t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->TEMPLATE _front_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
template<class T, size_t N>	class _RH<T[N], typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	T* t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)				{ return s->TEMPLATE _front_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};
template<class T>			class _RH<CGD::text<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	std::basic_string<T> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return s->TEMPLATE _front_text<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA static_cast<T>(NULL));} };
template<class T>			class _RH<std::basic_string<T>, typename std::enable_if<is_string_type<T>::value>::type>
													{	public:	typedef	std::basic_string<T> t;	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return s->TEMPLATE _front_string_pointer<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset);}};


//-----------------------------------------------------------------------------
//
// With Push_back only (list, deque, circular_list, ...)
//-----------------------------------------------------------------------------
// Linear container<T>)
template<class T> struct is_linear_container : public std::false_type {};
template<class A, class B> struct is_linear_container<std::list<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<std::deque<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<CGD::circular_list<A, B>> : public std::true_type {};
template<class A, class B> struct is_linear_container<std::list<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<std::deque<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<CGD::circular_list<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<std::list<CGOWN<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<std::deque<CGOWN<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_container<CGD::circular_list<CGOWN<A>, B>> : public std::false_type {};
// std::list<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_linear_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_linear_container<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_linear_container<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


// Linear container<CGPTR<T>>)
template<class T> struct is_linear_CGPTR_container : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::list<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::deque<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<CGD::circular_list<A, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::list<CGPTR<A>, B>> : public std::true_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::deque<CGPTR<A>, B>> : public std::true_type {};
template<class A, class B> struct is_linear_CGPTR_container<CGD::circular_list<CGPTR<A>, B>> : public std::true_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::list<CGOWN<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<std::deque<CGOWN<A>, B>> : public std::false_type {};
template<class A, class B> struct is_linear_CGPTR_container<CGD::circular_list<CGOWN<A>, B>> : public std::false_type {};
// std::list<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_linear_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_CGPTR_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_linear_CGPTR_container<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_CGPTR_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_linear_CGPTR_container<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_CGPTR_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


// Linear container<CGOWN<T>>)
template<class T> struct is_linear_CGOWN_container : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container<std::list<A, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container<std::deque<A, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container<CGD::circular_list<A, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container<std::list<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container<std::deque<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container<CGD::circular_list<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container<std::list<CGOWN<A>, B>> : public std::true_type {};
template<class A, class B>	struct is_linear_CGOWN_container<std::deque<CGOWN<A>, B>> : public std::true_type {};
template<class A, class B>	struct is_linear_CGOWN_container<CGD::circular_list<CGOWN<A>, B>> : public std::true_type {};
// std::list<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_CGOWN_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_linear_CGOWN_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_CGOWN_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_linear_CGOWN_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_CGOWN_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_linear_CGOWN_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_CGOWN_list<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


//-----------------------------------------------------------------------------
//
// With Push_back and Reserve (vector, ...)
//-----------------------------------------------------------------------------
// Associated container<T>)
template<class T> struct is_linear_container_with_reserve : public std::false_type {};
template<class A, class B>	struct is_linear_container_with_reserve<std::vector<A, B>> : public std::true_type {};
template<class A, size_t B>	struct is_linear_container_with_reserve<CGD::static_vector<A, B>> : public std::true_type {};
template<class A, class B>	struct is_linear_container_with_reserve<std::vector<CGPTR<A>, B>> : public std::false_type {};
template<class A, size_t B>	struct is_linear_container_with_reserve<CGD::static_vector<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_container_with_reserve<std::vector<CGOWN<A>, B>> : public std::false_type {};
template<class A, size_t B>	struct is_linear_container_with_reserve<CGD::static_vector<CGOWN<A>, B>> : public std::false_type {};
// std::vector<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_container_with_reserve<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_array<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_linear_container_with_reserve<T>::value>::type>			
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_linear_container_with_reserve<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_linear_container_with_reserve<T>::value>::type>			
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


// Associated container<CGPTR<T>>)
template<class T> struct is_linear_CGPTR_container_with_reserve : public std::false_type {};
template<class A, class B>	struct is_linear_CGPTR_container_with_reserve<std::vector<A, B>> : public std::false_type {};
template<class A, size_t B>	struct is_linear_CGPTR_container_with_reserve<CGD::static_vector<A, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGPTR_container_with_reserve<std::vector<CGPTR<A>, B>> : public std::true_type {};
template<class A, size_t B>	struct is_linear_CGPTR_container_with_reserve<CGD::static_vector<CGPTR<A>, B>> : public std::true_type {};
template<class A, class B>	struct is_linear_CGPTR_container_with_reserve<std::vector<CGOWN<A>, B>> : public std::false_type {};
template<class A, size_t B>	struct is_linear_CGPTR_container_with_reserve<CGD::static_vector<CGOWN<A>, B>> : public std::false_type {};
// std::vector<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_CGPTR_container_with_reserve<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_array<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_linear_CGPTR_container_with_reserve<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_linear_CGPTR_container_with_reserve<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_CGPTR_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_linear_CGPTR_container_with_reserve<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGPTR_vector<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


// Associated container<CGOWN<T>>)
template<class T> struct is_linear_CGOWN_container_with_reserve : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container_with_reserve<std::vector<A, B>> : public std::false_type {};
template<class A, size_t B> struct is_linear_CGOWN_container_with_reserve<CGD::static_vector<A, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container_with_reserve<std::vector<CGPTR<A>, B>> : public std::false_type {};
template<class A, size_t B> struct is_linear_CGOWN_container_with_reserve<CGD::static_vector<CGPTR<A>, B>> : public std::false_type {};
template<class A, class B>	struct is_linear_CGOWN_container_with_reserve<std::vector<CGOWN<A>, B>> : public std::true_type {};
template<class A, size_t B> struct is_linear_CGOWN_container_with_reserve<CGD::static_vector<CGOWN<A>, B>> : public std::true_type {};
// std::vector<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_linear_CGOWN_container_with_reserve<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_array<S, T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_linear_CGOWN_container_with_reserve<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_linear_CGOWN_container_with_reserve<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_CGOWN_array<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_linear_CGOWN_container_with_reserve<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGOWN_vector<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};

														
//-----------------------------------------------------------------------------
//
// With Insert
//-----------------------------------------------------------------------------
// Set container<T>)
template<class T> struct is_set_container : public std::false_type {};
template<class A, class B, class C>	struct is_set_container<std::set<A, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_container<std::multiset<A, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_container<std::set<CGPTR<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_container<std::multiset<CGPTR<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_container<std::set<CGOWN<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_container<std::multiset<CGOWN<A>, B, C>> : public std::false_type {};

// std::set<T>/ std::multiset<T>
template<typename T>		class _AF<T, typename std::enable_if<is_set_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_set_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_set_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_set_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


// Set container<T>)
template<class T> struct is_set_CGPTR_container : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGPTR_container<std::set<A, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGPTR_container<std::multiset<A, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGPTR_container<std::set<CGPTR<A>, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_CGPTR_container<std::multiset<CGPTR<A>, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_CGPTR_container<std::set<CGOWN<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGPTR_container<std::multiset<CGOWN<A>, B, C>> : public std::false_type {};
// std::set<T>/ std::multiset<T>
template<typename T>		class _AF<T, typename std::enable_if<is_set_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_set_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_set_CGPTR_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_CGPTR_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_set_CGPTR_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGPTR_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


// Set container<T>)
template<class T> struct is_set_CGOWN_container : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGOWN_container<std::set<A, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGOWN_container<std::multiset<A, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGOWN_container<std::set<CGPTR<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGOWN_container<std::multiset<CGPTR<A>, B, C>> : public std::false_type {};
template<class A, class B, class C>	struct is_set_CGOWN_container<std::set<CGOWN<A>, B, C>> : public std::true_type {};
template<class A, class B, class C>	struct is_set_CGOWN_container<std::multiset<CGOWN<A>, B, C>> : public std::true_type {};
// std::set<T>/ std::multiset<T>
template<typename T>		class _AF<T, typename std::enable_if<is_set_CGOWN_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _AB<T, typename std::enable_if<is_set_CGOWN_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_list<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);} };
template<typename T>		class _BF<T, typename std::enable_if<is_set_CGOWN_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_CGOWN_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);} };
template<typename T>		class _RH<T, typename std::enable_if<is_set_CGOWN_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGOWN_set<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


//-----------------------------------------------------------------------------
//
// For Associated Container
//-----------------------------------------------------------------------------
// Associated container<T>)
template<class T> struct is_associative_container : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::map<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::multimap<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_set<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_multiset<A, B, C, D>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_map<A, B, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_multimap<A, B, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::map<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::multimap<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_set<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_multiset<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_map<A, CGPTR<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_multimap<A, CGPTR<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::map<A, CGOWN<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::multimap<A, CGOWN<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_set<A, CGOWN<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_container<std::unordered_multiset<A, CGOWN<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_map<A, CGOWN<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_container<std::unordered_multimap<A, CGOWN<B>, C, D, E>> : public std::false_type {};
// Associated container<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_associative_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_associative_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_associative_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_associative_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


template<class T> struct is_associative_CGPTR_container : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::map<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::multimap<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::unordered_set<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::unordered_multiset<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGPTR_container<std::unordered_map<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGPTR_container<std::unordered_multimap<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::map<A, CGPTR<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::multimap<A, CGPTR<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::unordered_set<A, CGPTR<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::unordered_multiset<A, CGPTR<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGPTR_container<std::unordered_map<A, CGPTR<B>, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGPTR_container<std::unordered_multimap<A, CGPTR<B>, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::map<A, CGOWN<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::multimap<A, CGOWN<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::unordered_set<A, CGOWN<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGPTR_container<std::unordered_multiset<A, CGOWN<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGPTR_container<std::unordered_map<A, CGOWN<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGPTR_container<std::unordered_multimap<A, CGOWN<B>, C, D, E>> : public std::false_type {};
// Associated container<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_associative_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_associative_CGPTR_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_associative_CGPTR_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_CGPTR_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_associative_CGPTR_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGPTR_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


template<class T> struct is_associative_CGOWN_container : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::map<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::multimap<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::unordered_set<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::unordered_multiset<A, B, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGOWN_container<std::unordered_map<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGOWN_container<std::unordered_multimap<A, B, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::map<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::multimap<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::unordered_set<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::unordered_multiset<A, CGPTR<B>, C, D>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGOWN_container<std::unordered_map<A, CGPTR<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGOWN_container<std::unordered_multimap<A, CGPTR<B>, C, D, E>> : public std::false_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::map<A, CGOWN<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::multimap<A, CGOWN<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::unordered_set<A, CGOWN<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D>			struct is_associative_CGOWN_container<std::unordered_multiset<A, CGOWN<B>, C, D>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGOWN_container<std::unordered_map<A, CGOWN<B>, C, D, E>> : public std::true_type {};
template<class A, class B, class C, class D, class E>	struct is_associative_CGOWN_container<std::unordered_multimap<A, CGOWN<B>, C, D, E>> : public std::true_type {};
// Associated container<T>)
template<typename T>		class _AF<T, typename std::enable_if<is_associative_CGOWN_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xprepend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _AB<T, typename std::enable_if<is_associative_CGOWN_container<T>::value>::type>
													{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const T& data)				{ return _Xappend_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<typename T>		class _BF<T, typename std::enable_if<is_associative_CGOWN_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _Xextract_CGOWN_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};
template<typename T>		class _RH<T, typename std::enable_if<is_associative_CGOWN_container<T>::value>::type>
													{	public:	typedef	T t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _Xfront_CGOWN_container_associative<S,T>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};

}
