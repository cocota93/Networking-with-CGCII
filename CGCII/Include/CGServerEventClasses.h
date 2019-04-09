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
//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------
#define	CGSERVER_EVENT_CLASSES

namespace CGEvent
{
	class Manager;
}


//----------------------------------------------------------------------------
// head File들
//----------------------------------------------------------------------------
// 1) Socket Classes
#include "CGExecuteClasses.h"
#include <queue>

// 2) Definitions
#include "Server/Server/CGServerEventClasses/CGServerDefinitionsEventProtocol.h"
#include "Server/Server/CGServerEventClasses/CGServerDefinitionsEvent.h"
#include "Server/Server/CGServerEventClasses/EVENT_SCHEDULE.h"

// 3) Event system
#include "Server/Server/CGServerEventClasses/ICGEventObject.h"

#include "Server/Server/CGServerEventClasses/CGEventObjectOnce.h"
#include "Server/Server/CGServerEventClasses/CGEventObjectOnceFunction.h"
#include "Server/Server/CGServerEventClasses/CGEventObjectIteration.h"
#include "Server/Server/CGServerEventClasses/CGEventObjectIterationFunction.h"
#include "Server/Server/CGServerEventClasses/CGEventObjectSchedule.h"

#include "Server/Server/CGServerEventClasses/ICGEventSchedule.h"
#include "Server/Server/CGServerEventClasses/CGEventScheduleFunction.h"
#include "Server/Server/CGServerEventClasses/CGEventScheduleLambda.h"
#include "Server/Server/CGServerEventClasses/CGEventScheduleMemberFunction.h"
#include "Server/Server/CGServerEventClasses/CGEventObjectScheduleFunction.h"

#include "Server/Server/CGServerEventClasses/CGEventObjectStartEnd.h"
#include "Server/Server/CGServerEventClasses/CGEventObjectStartEndFunction.h"

#include "Server/Server/CGServerEventClasses/CGEventObjectStartIterationEnd.h"
#include "Server/Server/CGServerEventClasses/CGEventObjectStartIterationEndFunction.h"

// 4) Manager
#include "Server/Server/CGServerEventClasses/CGEventManager.h"




//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#if !defined(_LIB) || defined(_CONSOLE)

#if defined(_MSC_VER) && !defined(_MSC_PLATFORM_TOOLSET)
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
			#pragma comment (lib,"CGServerEventClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses_v140.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2013 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=120

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses_v120.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2012 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=110

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses_v110.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2010 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=100

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerEventClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerEventClasses_v100.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


#else

#endif

#endif
