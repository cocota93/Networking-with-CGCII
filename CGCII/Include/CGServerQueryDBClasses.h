//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Server Query DB Classes                          *
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
#define	CGSERVERSERVERDB_CLASSES

// OLE-DB 
#if defined(_MSC_VER)
	#pragma warning(disable:6001)
#endif


// ----------------------------------------------------------------------------
// head File
// ----------------------------------------------------------------------------
// 1) BaseClasses
#include "CGServerQueryClasses.h"

// 2) ...
#include <SQL.h>
#include <SQLExt.h>

//#if defined(_MSC_VER)
	#include <atldbcli.h>
//#else
	//#error "OLEDB is not supported!"
//#endif

// Definitions) 
namespace CGServerQuery
{
namespace DB
{
	class IQuery;
	class IQueryExecutable;

	class CQuerier;
	class Session;

	bool QueryResult(_In_ ICGServerQuery* _pQuery, _In_opt_ CGServerQuery::DB::Session* _pSession, _In_ intptr_t _hResult, _In_opt_ const _CHAR* _strQuery=nullptr);
	bool QueryResult(_In_ ICGServerQuery* _pQuery, _In_opt_ CGServerQuery::DB::Session* _pSession, _In_ intptr_t _hResult, _In_opt_ const _CHAR_SUB* _strQuery);
}
}

// 2) Additional
//#include "Server/ServerQuery/CGServerQueryDBClasses/CDynamicParameterAccessorEx.h"

// 3) Definitions
#include "Server/ServerQuery/CGServerQueryDBClasses/CGDefinitionsServerQueryDBProtocol.h"
#include "Server/ServerQuery/CGServerQueryDBClasses/CGDefinitionsServerQueryDB.h"

// 4) Base & Interfaces
#include "Server/ServerQuery/CGServerQueryDBClasses/CGServerQueryDBDataSource.h"
#include "Server/ServerQuery/CGServerQueryDBClasses/CGServerQueryDBSession.h"

// 5) Query

#include "Server/ServerQuery/CGServerQueryDBClasses/ICGServerQueryDBQuery.h"
#include "Server/ServerQuery/CGServerQueryDBClasses/CGServerQueryDBQuery.h"
#include "Server/ServerQuery/CGServerQueryDBClasses/ICGServerQueryDBQueryExecutable.h"
#include "Server/ServerQuery/CGServerQueryDBClasses/CGServerQueryDBQueryExecutable.h"
#include "Server/ServerQuery/CGServerQueryDBClasses/CGServerQueryDBQueryExecutableLambda.h"

// 6) Querier
#include "Server/ServerQuery/CGServerQueryDBClasses/CGServerQueryDBQuerier.h"

// 7) Scoped Transaction
#include "Server/ServerQuery/CGServerQueryDBClasses/CGServerQueryDBScopedTransaction.h"


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
			#pragma comment (lib,"CGServerQueryDBClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses_v140.lib")
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
			#pragma comment (lib,"CGServerQueryDBClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses_v120.lib")
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
			#pragma comment (lib,"CGServerQueryDBClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses_v110.lib")
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
			#pragma comment (lib,"CGServerQueryDBClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerQueryDBClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerQueryDBClasses_v100.lib")
		#endif
	#endif
#else
#endif


#endif

#endif
