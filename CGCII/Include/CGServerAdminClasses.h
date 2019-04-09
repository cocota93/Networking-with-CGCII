//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Admin Classes                            *
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
#define	CGSERVER_ADMIN_CLASSES

class CWnd;

namespace CGEvent
{
	class Manager;
}

namespace CGAPI
{
	class CPerformanceCounter;
}

class ICGServerService;

namespace CGServerAdmin
{
	class CSocketToHostAgent;
}


//----------------------------------------------------------------------------
// head File들
//----------------------------------------------------------------------------
// 1) Base Classes
#include "CGNetSocketTemplates.h"
#include "CGServerEventClasses.h"

// 2) Winsvs & PSAPI
#include <Winsvc.h>
#include <Psapi.h>

// 3) Definitions
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerDefinitionsAdminProtocol.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerDefinitionsAdmin.h"

// 4) API
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerAPIProcessInfo.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGAPIManagerPerfornamceQuery.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGAPIPerformanceCounter.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGAPIServiceHandle.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGAPIServerStatusHandle.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGAPIService.h"

// 5) Admin Info
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerAdminInfoConnective.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerAdminInfoBinder.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerAdminInfoPool.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerAdminInfoEvent.h"

// 6) Event
#include "Server/ServerAdmin/CGServerAdminClasses/CGEventObjectServiceInit.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGEventObjectServiceDestroy.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGEventObjectServiceStop.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGEventObjectServiceStart.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGEventScheduleServiceInit.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGEventScheduleServiceDestroy.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGEventScheduleServiceStart.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGEventScheduleServiceStop.h"

// 7) Socket
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerAdminSocketTCPAdmin.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerAdminSocketToHostAgent.h"

// 8) Service
#include "Server/ServerAdmin/CGServerAdminClasses/ICGServerService.h"
#include "Server/ServerAdmin/CGServerAdminClasses/NCGServerService.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGServerService.h"

// 9) Application
#include "Server/ServerAdmin/CGServerAdminClasses/NCGServiceApplication.h"
#include "Server/ServerAdmin/CGServerAdminClasses/CGServiceAppilcation.h"


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

#pragma comment (lib,"Psapi.lib")


//----------------------------------------------------------------------------
// * VS2015 Lib 
//----------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses_v140.lib")
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
			#pragma comment (lib,"CGServerAdminClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses_v120.lib")
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
			#pragma comment (lib,"CGServerAdminClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses_v110.lib")
		#endif
	#endif
#else
#endif


//----------------------------------------------------------------------------
// * VS2010 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=100

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminClasses_v100.lib")
		#endif
	#endif
#else
#endif


#endif

#endif
