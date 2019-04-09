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
//  _MSC_VER
//
//  1300 : Visual C++ .NET
//  1310 : Visual C++ .NET 2003
//  1400 : Visual C++ .NET 2005
//  1500 : Visual C++ .NET 2008
//  1600 : Visual C++ .NET 2010
//  1700 : Visual C++ .NET 2012
//  1800 : Visual C++ .NET 2013
//  1900 : Visual C++ .NET 2015
//-----------------------------------------------------------------------------
#define	_MSC_VER_2001	1300
#define	_MSC_VER_2003	1310
#define	_MSC_VER_2005	1400
#define	_MSC_VER_2008	1500
#define	_MSC_VER_2010	1600
#define	_MSC_VER_2012	1700
#define	_MSC_VER_2013	1800
#define	_MSC_VER_2015	1900

// if defined(__clang__)	// for Clang
// __clang_major__
// __clang_minor__
// __clang_patchlevel__
// __clang_version__

// if defined(__GNUG__)		// gcc/g++
// __GNUC_MINOR__
// __GNUC_PATCHLEVEL__

#ifndef NOEXCEPT
	#if _MSC_VER>=_MSC_VER_2015
		#define	NOEXCEPT	noexcept
	#else
		#define	NOEXCEPT
	#endif
#endif

// 6) STL..
#ifndef _DEBUG
	#ifndef _SECURE_SCL
		#define	_SECURE_SCL	0
	#endif
	#ifndef _HAS_ITERATOR_DEBUGGING
		#define _HAS_ITERATOR_DEBUGGING 0
	#endif
#endif



//-----------------------------------------------------------------------------
// Options Configure
//-----------------------------------------------------------------------------
// 1) Support =delete (C++11)
#ifndef _SUPPORT_DELETE_FUNCTION
	#if defined(_MSC_VER)
		#if _MSC_VER>=1800
			#define _SUPPORT_DELETE_FUNCTION
		#endif
	#else
		#if __cplusplus>=201103L
			#define _SUPPORT_DELETE_FUNCTION
		#endif
	#endif
#endif

// 2) Support variodic template paramter (C++11)
#ifndef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
	#if defined(_MSC_VER)
		#if _MSC_VER>=1800
			#define _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
		#endif
	#else
		#if __cplusplus>=201103L
			#define _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
		#endif
	#endif
#endif

// 3) Support constexpr (C++11)
#ifndef _CONSTEXPR
	#if defined(_MSC_VER)
		#if _MSC_VER>=1900
			#define	_CONSTEXPR	constexpr
		#else
			#define	_CONSTEXPR
		#endif
	#else
		#if __cplusplus>=201103L
			#define	_CONSTEXPR	constexpr
		#else
			#define	_CONSTEXPR
		#endif
	#endif
#endif // !_CONSTEXPR

// 4) Zero-sized Array (C++11)
#ifndef _SUPPORT_ZERO_SIZED_ARRAY
	#if defined(_MSC_VER)
		#if _MSC_VER>=1700
			#define _SUPPORT_ZERO_SIZED_ARRAY
		#endif
	#else
		#if __cplusplus>=201103L
		#endif
	#endif
#endif

// 5) Suport C++11 Traits 
#ifndef _SUPPORT_CPP11_TRAITS
	#if defined(_MSC_VER)
		#if _MSC_VER>=1700
			#define _SUPPORT_CPP11_TRAITS
		#endif
	#else
		#if __cplusplus>=201103L
			#define _SUPPORT_CPP11_TRAITS
		#endif
	#endif
#endif


//-----------------------------------------------------------------------------
// Options
//-----------------------------------------------------------------------------
#ifdef _SUPPORT_DELETE_FUNCTION
	#define	_DELETE			=delete;
	#define	_DELETE_RETURN	=delete;
#else
	#define	_DELETE			{	CGASSERT_ERROR(false);}
	#define	_DELETE_RETURN	{	CGASSERT_ERROR(false); return 0;}
#endif


//-----------------------------------------------------------------------------
// Basic)
//-----------------------------------------------------------------------------
// For Min/Max Disable
#ifndef NOMINMAX
	#define NOMINMAX
#endif

#include <string.h>
#include <functional>
#include <stdint.h>
#include <type_traits>
#include <utility>
#include <limits.h>

#ifndef SIZE_T_MAX
	#define SIZE_T_MAX	SIZE_MAX
#endif


// 1) Base
#if defined(_MSC_VER)
#include <sal.h>

#if	_MSC_VER<=_MSC_VER_2010
	#define	_Null_terminated_				__nullterminated
	#define	_In_reads_opt_(n)				_In_opt_bytecount_(n)
	#define	_Out_writes_bytes_(n)	
	#define	_Out_writes_z_(n)
	#define	_Out_writes_bytes_to_(m,n)
	#define	_Out_writes_bytes_to_opt_(m,n)
	#define	_Out_writes_opt_z_(n)			
	#define	_Inout_updates_(n)
#endif


#else

#define _In_bytecount_(a)
#define _In_reads_(a)
#define _In_reads_bytes_opt_(a)
#define _Inout_opt_
#define	__out_ecount(a)
#define	_Success_(a)
#define	_In_count_(a)
#define	__field_bcount(a)
#define	_In_opt_bytecount_(a)
#define	__nullterminated
#define	_In_opt_z_
#define	_Out_
#define	_Out_opt_
#define _Inout_updates_bytes_(a)

#define	_Null_terminated_				__nullterminated
#define	_In_reads_opt_(n)				_In_opt_bytecount_(n)
#define	_Out_writes_bytes_(n)	
#define	_Out_writes_z_(n)
#define	_Out_writes_bytes_to_(m,n)
#define	_Out_writes_bytes_to_opt_(m,n)
#define	_Out_writes_opt_z_(n)			
#define	_Inout_updates_(n)

#ifndef _CGD_BUFFER
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
#endif

#define	__FUNCTION__ ""

#if !defined(INT_MAX)
	#define INT_MAX		(int32_t)0x7fffffff
	#define INT_MIN		(int32_t)-0x7fffffff
	#define UINT_MAX	(uint32_t)0xffffffff
#endif

namespace std
{

inline size_t _Hash_seq(const unsigned char *_First, size_t _Count)
{	// FNV-1a hash function for bytes in [_First, _First + _Count)
#if defined(_WIN64)
	static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
	const size_t _FNV_offset_basis = 14695981039346656037ULL;
	const size_t _FNV_prime = 1099511628211ULL;

#else /* defined(_WIN64) */
	static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
	const size_t _FNV_offset_basis = 2166136261U;
	const size_t _FNV_prime = 16777619U;
#endif /* defined(_WIN64) */

	size_t _Val = _FNV_offset_basis;
	for (size_t _Next = 0; _Next < _Count; ++_Next)
	{	// fold in another byte
		_Val ^= (size_t)_First[_Next];
		_Val *= _FNV_prime;
	}
	return (_Val);
}
}
#endif

template<class _Ty> 
typename std::decay<_Ty>::type DECAY_COPY(_Ty&& _Arg)
{
	return (std::forward<_Ty>(_Arg));
}


// ----------------------------------------------------------------------------
//
// Debug NEW
//
// ----------------------------------------------------------------------------
#include <new.h>

// Debug)
#ifdef _DEBUG
	#if defined(_MSC_VER)
		#define _CRTDBG_MAP_ALLOC
		#define _INC_MALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif
#endif

#if defined(_USE_DEBUG_NEW)
	#define	NEW												DEBUG_INFO_SETTER(__FILE__, __LINE__)=MAKE_CREATE_PARAMETERS
	#define	POOL_ALLOC										DEBUG_INFO_SETTER(__FILE__, __LINE__)=_CGPOOL_ALLOC
	#define	MEM_ALLOC(size)									_CGMEM_ALLOC(size, __FILE__, __LINE__)
	#define	MEM_POOL_ALLOC(size)							_CGMEM_POOL_ALLOC(size, __FILE__, __LINE__)
	#define	MEM_POOL_ALLOC_WITH_DEBUG_INFO(size, f, l)		_CGMEM_POOL_ALLOC(size, f, l)
	#define	CGNEW_DEBUG										new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define	CGNEW_DEBUG_INFO_INITIALIZE						,m_DebugInfo_Filename(nullptr), m_DebugInfo_Line(0)
	#define	CGNEW_DEBUG_INFO_PARAMETERS						const char* _Filename, int _Line
	#define	CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT		const char* _Filename=__FILE__, int _Line=__LINE__
	#define	CGNEW_DEBUG_INFO_PARAMETERS_PASSING				_Filename, _Line
	#define	CGNEW_DEBUG_INFO_PARAMETERS_INITIAL				__FILE__, __LINE__
	#define	CGNEW_DEBUG_INFO_COMMA							,
	#define	CGNEW_DEBUG_INFO_SET(pobject, filename, line)	pobject->SetDebugInfo(filename, line)
	#define	CGNEW_DEBUG_INFO_RESET(pobject)					pobject->ResetDebugInfo()
	#define	CGNEW_DEBUG_INFO_DECLARE						void SetDebugInfo(const char* _Filename, int _Line)	{ m_DebugInfo_Filename=_Filename; m_DebugInfo_Line=_Line;}	\
															void ResetDebugInfo()								{ m_DebugInfo_Filename=nullptr; m_DebugInfo_Line=0;}		\
															const char*	m_DebugInfo_Filename; int m_DebugInfo_Line;
#else
	#define	NEW												_CGNEW
	#define	POOL_ALLOC										_CGPOOL_ALLOC
	#define	MEM_ALLOC(size)									_CGMEM_ALLOC(size)
	#define	MEM_POOL_ALLOC(size)							_CGMEM_POOL_ALLOC(size)
	#define	MEM_POOL_ALLOC_WITH_DEBUG_INFO(size, f, l)		_CGMEM_POOL_ALLOC(size)
	#define	CGNEW_DEBUG										new
	#define	CGNEW_DEBUG_INFO_INITIALIZE
	#define	CGNEW_DEBUG_INFO_PARAMETERS						
	#define	CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT
	#define	CGNEW_DEBUG_INFO_PARAMETERS_PASSING				
	#define	CGNEW_DEBUG_INFO_PARAMETERS_INITIAL
	#define	CGNEW_DEBUG_INFO_COMMA							
	#define	CGNEW_DEBUG_INFO_SET(pobject, filename, line)	
	#define	CGNEW_DEBUG_INFO_RESET(pobject)					
	#define	CGNEW_DEBUG_INFO_DECLARE						void SetDebugInfo(const char* , int )					{}	\
															void ResetDebugInfo()									{}
#endif


//-----------------------------------------------------------------------------
// Configuration
//-----------------------------------------------------------------------------
// 1) Platform

// 2) Tick Timer
//#define		_USE_TICK_TICKCOUNT32
//#define		_USE_TICK_TICKCOUNT64
//#define		_USE_TICK_STANDARD_HIGH_RESOLUTION
//#define		_USE_TICK_STANDARD_MONOTONIC
#define		_USE_TICK_STANDARD_SYSTEM
//#define		_USE_TICK_STANDARD_STEADY

// 3) Time
#define		_USE_TIME_WINDOWS
//#define		_USE_TIME_STANDARD

// 4) String
//#define		_USE_CHAR_STRING
#define		_USE_WCHAR_STRING

// 5) Lock
#define		_USE_NATIVE_LOCK


//-----------------------------------------------------------------------------
// Containers
//-----------------------------------------------------------------------------
// 1) Array & Vector
#include <CGD/static_vector>
//#include <array>
//#include <CGD/vector>
#include <vector>
#include <CGD/circular>

// 2) List
#include <CGD/circular_list>
#include <CGD/slist>
#include <list>

// 3) Associated
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

// 4) Algorithm
#include <algorithm>

// 5) Ptrs
#include <memory>

// Using) 
using namespace CGD;
//using CGD::vector;
using std::vector;
using std::list;
using std::set;

//-----------------------------------------------------------------------------
// ...
//-----------------------------------------------------------------------------
// 1) Adaptor
#include "CGD/CGDidentity.h"
#include "CGD/CGDidentity_priority.h"
#include "CGD/CGDseat.h"
#include "CGD/CGDstack.h"
#include "CGD/CGDqueue.h"
#include "CGD/CGDpriority_queue.h"

// 2) flexible
#include "CGD/CGDflexible.h"

// 3) Etc
#include "CGD/CGDsmart_ptr.h"

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------
// 1) Fundamental Definitions
#include "Common/CGDefinitions.h"

// 2) Definition for Debug
#include "Common/CGDefinitionsAssert.h"

// 3) Type Definitions
#include "Common/CGDefinitionsTypes.h"

// 4) Definitions for String
#include "Common/CGDefinitionString.h"

// 5) Definitions for Locked Object
#include "Common/CGDefinitionLock.h"

// 6) Definitions for Timer
#include "Common/CGDefinitionTimer.h"

// 7) Message
#include "Common/CGDefinitionsMessage.h"
#include "Common/CGMessageMap.h"

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------
// 1) Queury Performance
#include "Common/CGQueryPerformance.h"
