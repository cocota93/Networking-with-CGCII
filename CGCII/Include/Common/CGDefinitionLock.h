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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//                                                                            
// Definitions for Locked objects
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Configure)
//-----------------------------------------------------------------------------
#define	LOCKFREE_SELF_STACK		lockfree_self_stack
#define	ATOMIC					std::atomic

// Pre) 아래의 Warning을 Disable시킨다.
//      warning C4201: The use of attribute annotations on this function will 
//                     invalidate all of its existing __declspec annotations
//#pragma warning(disable:6540)

//-----------------------------------------------------------------------------
// Intrinsic
//-----------------------------------------------------------------------------
// 1) Include
#include <atomic>
#include <mutex>

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <pthread.h>

#if defined (_M_X64)
inline unsigned char _InterlockedCompareExchange128(__int64 volatile * _Destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 * _ComparandResult)
//inline __uint128_t InterlockedCompareExchange128(__uint128_t volatile * _Destination, __uint128_t _Comparand, __uint128_t with )
{
  __asm__ __volatile__
  (
      "lock cmpxchg16b %1"
      : "+A" ( _ComparandResult )
      , "+m" ( *_Destination )
      : "b" ( (long long)_ExchangeLow )
      , "c" ( (long long)_ExchangeHigh )
      : "cc"
  );

  return _ExchangeLow==*_ComparandResult && _ExchangeHigh==*(_ComparandResult+1);
}
#else
	#error "Not supported Platform (_InterlockedCompareExchange128 is not defined)"
#endif

#endif

//-----------------------------------------------------------------------------
// Intrinsic)
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)

#pragma intrinsic(memcmp)
#pragma intrinsic(memcpy)
#pragma intrinsic(memset)

#pragma intrinsic(strlen)
#pragma intrinsic(strcmp)
#pragma intrinsic(strcpy)
#pragma intrinsic(strcat)
#pragma intrinsic(_strset)

#pragma intrinsic(abs)
#pragma intrinsic(fabs)
#pragma intrinsic(labs)
#pragma intrinsic(_rotl)
#pragma intrinsic(_rotr)

#pragma intrinsic(acos)
#pragma intrinsic(cosh)
#pragma intrinsic(pow)
#pragma intrinsic(tanh)
#pragma intrinsic(asin)
#pragma intrinsic(fmod)
#pragma intrinsic(sinh)

#pragma intrinsic(atan)
#pragma intrinsic(exp)
#pragma intrinsic(log10)
#pragma intrinsic(sqrt)
#pragma intrinsic(atan2)
#pragma intrinsic(log)
#pragma intrinsic(sin)
#pragma intrinsic(cos)
#pragma intrinsic(tan)

#pragma intrinsic(_InterlockedCompareExchange64)

#if defined(_M_X64)
#pragma intrinsic(_InterlockedCompareExchange128)
#endif

#endif


//-----------------------------------------------------------------------------
// Definitions)
//-----------------------------------------------------------------------------
// 1) Critical section
#include "Common/CGDCriticalSection.h"
#include "Common/CGDSlipLock.h"
#include "Common/CGDscopedLock.h"

// 2) CGD Locked Container
#include "Common/CGDInterlockedSelfStack.h"
#include "Common/CGDLockfreeSelfStack.h"
#include "Common/CGDLockfreeSelfStack64.h"
#include "Common/CGDLockfreeQueue.h"
#include "Common/CGDLockedStack.h"
#include "Common/CGDLockedQueue.h"
#include "Common/CGDLockedIdentity.h"
#include "Common/CGDTLSStack.h"
