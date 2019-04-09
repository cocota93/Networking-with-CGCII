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
// ----------------------------------------------------------------------------
// Prototype
// ----------------------------------------------------------------------------
#define	CGSERVERQUERY_CLASSES

class ICGServerQuery;
class ICGServerQuerier;
class ICGServerQueryExecutable;

namespace CGServerQuery
{
	class ManagerQuerier;
}

using namespace CGServerQuery;

#define _ATL_DISABLE_NOTHROW_NEW

// ----------------------------------------------------------------------------
// head File
// ----------------------------------------------------------------------------
// 1) 
#include "CGExecuteClasses.h"

// 2) Definitions
#include "Server/ServerQuery/CGServerQueryClasses/CGDefinitionsServerQueryProtocol.h"
#include "Server/ServerQuery/CGServerQueryClasses/CGDefinitionsServerQuery.h"

// 3) Statistics
#include "Server/ServerQuery/CGServerQueryClasses/ICGServerQueryStatistics.h"

// 4) Base & Interfaces
#include "Server/ServerQuery/CGServerQueryClasses/ICGServerQueryRequestor.h"
#include "Server/ServerQuery/CGServerQueryClasses/ICGServerQuery.h"
#include "Server/ServerQuery/CGServerQueryClasses/ICGServerQueryExecutable.h"

// 5) Querier
#include "Server/ServerQuery/CGServerQueryClasses/CGServerQueryManagerQuerier.h"
#include "Server/ServerQuery/CGServerQueryClasses/ICGServerQuerier.h"


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#if !defined(_LIB) || defined(_CONSOLE)

#ifndef _MSC_PLATFORM_TOOLSET
	#if _MSC_VER>=_MSC_VER_2015
		#define	_MSC_PLATFORM_TOOLSET	140
	#elif _MSC_VER>=_MSC_VER_2013
		#define	_MSC_PLATFORM_TOOLSET	120
	#elif _MSC_VER>=_MSC_VER_2012
		#define	_MSC_PLATFORM_TOOLSET	110
	#elif _MSC_VER>=_MSC_VER_2010
		#define	_MSC_PLATFORM_TOOLSET	100
	#elif _MSC_VER>=_MSC_VER_2008
		#define	_MSC_PLATFORM_TOOLSET	90
	#else
		#define	_MSC_PLATFORM_TOOLSET	80
	#endif
#endif


//----------------------------------------------------------------------------
// * VS2015 Lib 
//----------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses_v140.lib")
		#endif
	#endif
#else
#endif


//----------------------------------------------------------------------------
// * VS2013 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=120

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses_v120.lib")
		#endif
	#endif
#else
#endif


//----------------------------------------------------------------------------
// * VS2012 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=110

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses_v110.lib")
		#endif
	#endif
#else
#endif


//----------------------------------------------------------------------------
// * VS2010 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET==100

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryClasses_v100.lib")
		#endif
	#endif
#else
#endif


#endif

#endif
