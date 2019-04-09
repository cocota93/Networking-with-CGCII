//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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
// Class Definition
//-----------------------------------------------------------------------------
#define	CGEXECUTE_CLASSES

// 1) 
class ICGExecutable;
class ICGExecutor;
class ICGSchedulable;

namespace CGExecutor
{
	template <class TEXECUTOR=ICGExecutor> class CList;
}


//-----------------------------------------------------------------------------
// Basic
//-----------------------------------------------------------------------------
// 1) Default Definitions
#include "CGObjectClasses.h"
#include "CGUtilClasses.h"

// 2) Default Definitions
#if defined(_MSC_VER)
	#pragma warning(disable:4091)
#endif

#include <exception>

#if defined(_MSC_VER)
	#include <eh.h>
	#include <Dbghelp.h>
#endif


#if defined(_MSC_VER)
	#pragma warning(default:4091)
#endif

// 3) Thread
#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2012
	#include <thread>
#endif


//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------
// 1) 
#include "CGExecuteClasses/CGDefinitionsExecuteProtocol.h"
#include "CGExecuteClasses/CGDefinitionsExecute.h"


//-----------------------------------------------------------------------------
// Exceptions
//-----------------------------------------------------------------------------
#include "CGExecuteClasses/CGExceptions.h"
#include "CGExecuteClasses/CGExceptionManager.h"


//-----------------------------------------------------------------------------
// Interface class
//-----------------------------------------------------------------------------
#include "CGExecuteClasses/ICGExecutor.h"
#include "CGExecuteClasses/ICGExecutable.h"
#include "CGExecuteClasses/ICGSchedulable.h"


//-----------------------------------------------------------------------------
// API
//-----------------------------------------------------------------------------
#include "CGExecuteClasses/CGAPIIOCPCompletionPort.h"
#include "CGExecuteClasses/CGAPIManagerThread.h"
#include "CGExecuteClasses/CGAPIThread.h"
#include "CGExecuteClasses/CGAPIThreadPool.h"


//-----------------------------------------------------------------------------
// Executor/Thread
//-----------------------------------------------------------------------------
#include "CGExecuteClasses/CGExecutable.h"
#include "CGExecuteClasses/CGExecutorManager.h"
#include "CGExecuteClasses/CGExecutorList.h"
#include "CGExecuteClasses/CGExecutorCompletionport.h"
#include "CGExecuteClasses/CGExecutorCompletionPortThread.h"
#include "CGExecuteClasses/CGExecutorQueued.h"
#include "CGExecuteClasses/CGExecutorQueuedThread.h"
#include "CGExecuteClasses/CGExecutorThread.h"
#include "CGExecuteClasses/CGExecutorListThread.h"
#include "CGExecuteClasses/CGExecutorSingleExecute.h"
#include "CGExecuteClasses/CGExecutorSingleExecuteThread.h"
#include "CGExecuteClasses/CGExecutorListPriority.h"
#include "CGExecuteClasses/CGExecutorSchedulable.h"



//-----------------------------------------------------------------------------
// Executable
//-----------------------------------------------------------------------------
#include "CGExecuteClasses/CGExecutableFunction.h"
#include "CGExecuteClasses/CGExecutableFunctionMember.h"
#include "CGExecuteClasses/CGExecutableBatch.h"
#include "CGExecuteClasses/CGExecutableBatchWait.h"
#include "CGExecuteClasses/CGExecutableBatchNotify.h"
#include "CGExecuteClasses/CGExecutableBatchFunction.h"
#include "CGExecuteClasses/CGExecutableBatchFunctionMember.h"
#include "CGExecuteClasses/CGExecutableList.h"


//-----------------------------------------------------------------------------
// Schedulable
//-----------------------------------------------------------------------------
#include "CGExecuteClasses/NCGSchedulable.h"
#include "CGExecuteClasses/NCGSchedulableExecutable.h"
#include "CGExecuteClasses/CGSchedulableExecutable.h"
#include "CGExecuteClasses/CGSchedulableExecutableList.h"
#include "CGExecuteClasses/CGSchedulableExecutableFunction.h"
#include "CGExecuteClasses/CGSchedulableExecutableFunctionMember.h"


//-----------------------------------------------------------------------------
// Reference Counter
//-----------------------------------------------------------------------------
// Thread
#include "CGExecuteClasses/CGReferenceCountWaiter.h"


//-----------------------------------------------------------------------------
// Default Executor
//-----------------------------------------------------------------------------
// 1) Executor
#include "CGExecuteClasses/CGSchedulableSystemFactorySustain.h"
#include "CGExecuteClasses/CGSchedulableSystemExceptionObserver.h"
#include "CGExecuteClasses/CGExecutorDefault.h"


//-----------------------------------------------------------------------------
// Executable Batch
//-----------------------------------------------------------------------------
#include "CGExecuteClasses/CGUpdatableExecutableBatch.h"


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

#if defined(_MSC_VER)
	#pragma comment (lib,"Dbghelp.lib")
	#pragma comment (lib,"winmm.lib")
	#pragma comment (lib,"Psapi.lib")
#endif


//----------------------------------------------------------------------------
// * VS2015 Lib 
//----------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses_v140.lib")
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
			#pragma comment (lib,"CGExecuteClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses_v120.lib")
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
			#pragma comment (lib,"CGExecuteClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses_v110.lib")
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
			#pragma comment (lib,"CGExecuteClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGExecuteClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGExecuteClasses_X86_v100.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif

#else

#endif

#endif
