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
// Definitions
//                                                                            
//-----------------------------------------------------------------------------
#define	INLINE										inline

#ifndef PURE
	#define	PURE									= 0
#endif

#ifndef EMPTY
	#define	EMPTY									{}
#endif

#ifndef EMPTY_TRUE
	#define	EMPTY_TRUE								{	return TRUE;}
#endif

#ifndef EMPTY_FALSE
	#define	EMPTY_FALSE								{	return FALSE;}
#endif

#ifndef EMPTY_ZERO
	#define	EMPTY_ZERO								{	return 0;}
#endif

#ifndef SAFE_FREE
	#define	SAFE_FREE(p)							if(p){ free(p);p=nullptr;}
#endif

#ifndef SAFE_DELETE
	#define	SAFE_DELETE(p)							if(p){ delete p; p=nullptr;}
#endif

#ifndef SAFE_DELETE_ARRAY
	#define SAFE_DELETE_ARRAY(p)					{ if(p) { delete[] (p);   (p) = nullptr; } }
#endif

#ifndef SAFE_RELEASE
	#define	SAFE_RELEASE(data)						if(data){ (data)->Release();(data)=nullptr;}
#endif

#ifndef SAFE_CLOSEHANDLE
	#define	SAFE_CLOSEHANDLE(data)					if(data!=INVALID_HANDLE_VALUE){ CloseHandle(data);data=INVALID_HANDLE_VALUE;}
#endif

#if defined(_MSC_VER)
	#define	NO_WARNING(v)							v;
#else
	#define	NO_WARNING(v)
#endif

#ifndef NOEXCEPT
#if _MSC_VER>=_MSC_VER_2015
	#define	NOEXCEPT	noexcept
#else
	#define	NOEXCEPT
#endif
#endif

#define	NO_EXCEPTION_BEGIN							try
#define	NO_EXCEPTION_END							catch (...) {}


//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// * VS2015 Lib 
#if _MSC_VER>=_MSC_VER_2015
#define	CGDK_CONFIGURATION_COMPILER	"v140"
#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v140.x64.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v140.x64.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v140.x64 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v140.x64 [RELEASE]"
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v140.x86.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v140.x86.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v140.x86 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v140.x86 [RELEASE]"
		#endif
	#endif
#else
	#ifdef _DEBUG
		#define	CGDK_CONFIGURATION	"CGDK8.v140.Unsupported [DEBUG]"
	#else
		#define	CGDK_CONFIGURATION	"CGDK8.v140.Unsupported [RELEASE]"
	#endif
#endif

// * VS2013 Lib 
#elif _MSC_VER>=_MSC_VER_2013
#define	CGDK_CONFIGURATION_COMPILER	"v120"
#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v120.x64.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v120.x64.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v120.x64 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v120.x64 [RELEASE]"
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v120.x86.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v120.x86.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v120.x86 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v120.x86 [RELEASE]"
		#endif
	#endif
#else
	#ifdef _DEBUG
		#define	CGDK_CONFIGURATION	"CGDK8.v120.Unsupported [DEBUG]"
	#else
		#define	CGDK_CONFIGURATION	"CGDK8.v120.Unsupported [RELEASE]"
	#endif
#endif

// * VS2012 Lib 
#elif _MSC_VER>=_MSC_VER_2012
#define	CGDK_CONFIGURATION_COMPILER	"v110"
#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v110.x64.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v110.x64.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v110.x64 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v110.x64 [RELEASE]"
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v110.x86.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v110.x86.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v110.x86 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v110.x86 [RELEASE]"
		#endif
	#endif
#else
	#ifdef _DEBUG
		#define	CGDK_CONFIGURATION	"CGDK8.v110.Unsupported [DEBUG]"
	#else
		#define	CGDK_CONFIGURATION	"CGDK8.v110.Unsupported [RELEASE]"
	#endif
#endif

// * VS2010 Lib 
#elif _MSC_VER>=_MSC_VER_2010
#define	CGDK_CONFIGURATION_COMPILER	"v100"
#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v100.x64.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v100.x64.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v100.x64 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v100.x64 [RELEASE]"
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v100.x86.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v100.x86.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.v100.x86 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.v100.x86 [RELEASE]"
		#endif
	#endif
#else
	#ifdef _DEBUG
		#define	CGDK_CONFIGURATION	"CGDK8.v100.Unsupported [DEBUG]"
	#else
		#define	CGDK_CONFIGURATION	"CGDK8.v100.Unsupported [RELEASE]"
	#endif
#endif

// * Eclips
#else
#define	CGDK_CONFIGURATION_COMPILER	"eclips"
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.eclips.x86.DLL [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.eclips.x86.DLL [RELEASE]"
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#define	CGDK_CONFIGURATION	"CGDK8.eclips.x86 [DEBUG]"
		#else
			#define	CGDK_CONFIGURATION	"CGDK8.eclips.x86 [RELEASE]"
		#endif
	#endif
#endif


// ----------------------------------------------------------------------------
// Check
// ----------------------------------------------------------------------------
// 1) Control State
#define	CONTINUE_IF(equation)						if(equation) { continue;}
#define	DO_AND_CONTINUE_IF(equation, todo)			if(equation) { todo; continue;}
#define	BREAK_IF(equation)							if(equation) { break;}
#define	THROW_IF(equation, value)					if(equation) { throw value;}
#define	RETURN_IF(equation, value)					if(equation) { return value;}

// 2) Control State with STATE
#define	ERROR_IF(equation, state)					if(equation) { state;}
#define	ERROR_CONTINUE_IF(equation, state)			if(equation) { state; continue;}
#define	ERROR_BREAK_IF(equation, state)				if(equation) { state; break;}
#define	ERROR_THROW(value, state)					{state; throw value;}
#define	ERROR_THROW_IF(equation, value, state)		if(equation) { state; throw value;}
#define	ERROR_RETURN_IF(equation, value, state)		if(equation) { state; return value;}

// 3) Conditional
#define	CGIF(condition, state)						if(condition) { state;}

// 4) Debug Only
#ifdef _DEBUG
	#define	CGDEBUG_ONLY(a)							a
#else
	#define	CGDEBUG_ONLY(a)
#endif



// ----------------------------------------------------------------------------
// Simple Operations
// ----------------------------------------------------------------------------
// 1) Settings
#define	SET_ZERO(variable)							variable=0
#define SET_ZERO_VECTOR3(variable)					variable.x=variable.y=variable.z=0.0f;
#define SET_ZERO_VECTOR4(variable)					variable.x=variable.y=variable.z=variable.w=0.0f;
#define	SET_NULL(variable)							variable=nullptr
#define	SET_TRUE(variable)							variable=TRUE
#define	SET_FALSE(variable)							variable=FALSE

// 2) Bit operations
// Toggle(TRUE는 FALSE로 FALSE는 TRUE로 바꿉니다.)
#define	TOGGLE(value)								(value) = !(value)

// 3) Simple Operations
template <typename T> T MAX(T a, T b)				{return (a>b) ? a:b;}
template <typename T> T MAX(T a, T b, T c)			{return (a>b) ? ((a>c) ? a:c) : ((b>c) ? b:c);}
template <typename T> T MAX(T a, T b, T c, T d)		{return MAX(MAX(a,b), MAX(c,d));}
template <typename T> T MIN(T a, T b)				{return (a<b) ? a:b;}
template <typename T> T MIN(T a, T b, T c)			{return (a<b) ? ((a<c) ? a:c) : ((b<c) ? b:c);}
template <typename T> T MIN(T a, T b, T c, T d)		{return MIN(MIN(a,b), MIN(c,d));}
#define	UPDATE_MAX(a, b)							if(a<(b)) {a=(b);}
#define	UPDATE_MIN(a, c)							if(a>(c)) {a=(c);}
#define	SATURATE_MAX(a, c)							if(a>(c)) a=(c);
#define	SATURATE_MIN(a, b)							if(a<(b)) a=(b);
#define	SATURATE(a, b, c)							if(a<(b)) a=(b); else if(a>(c)) a=(c);
#define	ROUND_MAX(a, c)								if(a>(c)) a-=(c);
#define	ROUND_MIN(a, b)								if(a<(b)) a+=(b);
#define	ROUND_MINIMAX(a, b, c)						if(a<(b)) a+=(b); else if(a>(c)) a-=(c);
#define	UINT_DIFFER(a, b)							(a>=b) ? (a-b) : (UINT_MAX-a+b);

// 4) SWAP
template <typename TA>
void	SWAP(TA& a, TA& b)							{TA t=std::move(a); a=std::move(b); b=std::move(t);}

// 5) Increase/Decrese
#define	INCREASE(value)								++value
#define	INCREASE_IF(condition, value)				if(condition) {++value;}
#define	DECREASE(value)								--value
#define	DECREASE_IF(condition, value)				if(condition) {--value;}
#define	DISCOUNT_TO_ZERO(value)						if(value > 0) {--value;}

// 7) 계산 관련
#define	SQURE(value)								(value*value)
#define	VECTOR3_DISTANCE_SQURE(value)				(value.x*value.x+value.y*value.y+value.z*value.z)

// 8) Unique name
#define _MERGE_(a,b)  a##b
#define _LABEL_(a,b) _MERGE_(a,b)
#define _UNIQUE_TEMPORARY_NAME(name) _LABEL_(name, __LINE__)
