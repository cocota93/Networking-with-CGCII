//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                            Server Log Classes                             *
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
#define	CGSERVER_LOG_CLASSES


//----------------------------------------------------------------------------
// head File들
//----------------------------------------------------------------------------
// 1) Base Classes
#include "CGNetSocketTemplates.h"
#include "CGServerEventClasses.h"

// 2) Windows Internet Library
#if defined(_MSC_VER)
	#include <Wininet.h>
#endif

// 3) Definitions
#include "Server/Server/CGServerLogClasses/CGServerDefinitionsLog.h"

// 4) File
#include "Server/Server/CGServerLogClasses/CGFile.h"

// 5) Log Record/Source/Logable/Archive
#include "Server/Server/CGServerLogClasses/ICGLogSource.h"
#include "Server/Server/CGServerLogClasses/ICGLogArchive.h"

// 6) Log Filter
#include "Server/Server/CGServerLogClasses/ICGLogFilter.h"
#include "Server/Server/CGServerLogClasses/CGLogFilterDefault.h"

// 7) Log
#include "Server/Server/CGServerLogClasses/ICGLog.h"

#include "Server/Server/CGServerLogClasses/CGLogHub.h"
#include "Server/Server/CGServerLogClasses/CGLogFile.h"
#include "Server/Server/CGServerLogClasses/CGLogSlack.h"
#include "Server/Server/CGServerLogClasses/CGLogSocket.h"
#include "Server/Server/CGServerLogClasses/CGLogConsole.h"


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

// 1) Windows Internet Library
#if defined(_MSC_VER)
	#pragma comment (lib,"Wininet.lib")
#endif


//----------------------------------------------------------------------------
// * VS2013 Lib 
//----------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses_v140.lib")
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
			#pragma comment (lib,"CGServerLogClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses_v120.lib")
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
			#pragma comment (lib,"CGServerLogClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses_v110.lib")
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
			#pragma comment (lib,"CGServerLogClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerLogClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerLogClasses_v100.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


#else

#endif

#endif
