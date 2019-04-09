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
class ICGServerService;

// Definitions
#define	HUNSPELL_STATIC
#define	THESAURUS

#ifdef _DEBUG
#define	SVN_DEBUG
#endif

namespace CGServerAdmin
{
	class ISVNCommand;
	class ISVNNotify;
	class SVN;
}


//----------------------------------------------------------------------------
// head File들
//----------------------------------------------------------------------------
// 1) Base Classes
#include "CGServerAdminClasses.h"

// 2) 
#include "apr_version.h"
#include "apu_version.h"

#ifdef _WIN64
#include "openssl/opensslv.h"
#else
#include "openssl/opensslv.h"
#endif
#include "../../ext/zlib/zlib.h"

#define __WIN32__
//#include "boost/pool/object_pool.hpp"

#define USE_GDI_GRADIENT
#define HISTORYCOMBO_WITH_SYSIMAGELIST

#ifdef _WIN64
#   define APP_X64_STRING   "x64"
#else
#   define APP_X64_STRING ""
#endif

#define HAVE_APPUTILS

#pragma warning(push)
#include "apr_general.h"
#include "svn_pools.h"
#include "svn_client.h"
#include "svn_path.h"
#include "svn_wc.h"
#include "svn_utf.h"
#include "svn_config.h"
#include "svn_error_codes.h"
#include "svn_subst.h"
#include "svn_repos.h"
#include "svn_time.h"
#include "svn_props.h"
#pragma warning(pop)

// 3) Definitions
#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerDefinitionsVersionControl.h"

// 4) SVN
#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/ICGServerAdminSVNNotify.h"
#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/ICGServerAdminSVN.h"

#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVN.h"

#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNUpdate.h"
#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNCheckOut.h"
#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNSwitch.h"
#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNInfo.h"
#include "Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNLog.h"


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _LIB

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

#pragma comment(lib, "libsvn_tsvn32.lib")
#pragma comment(lib, "libapr_tsvn.lib")
#pragma comment(lib, "libsasl.lib")
#pragma comment(lib, "libaprutil_tsvn.lib")
#pragma comment(lib, "intl3_tsvn.lib")
#pragma comment(lib, "intl3_tsvn.lib")


//----------------------------------------------------------------------------
// * VS2015 Lib 
//----------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses_v140.lib")
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
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses_v120.lib")
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
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses_v110.lib")
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
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGServerAdminVersionControlClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGServerAdminVersionControlClasses_v100.lib")
		#endif
	#endif
#else
#endif


#endif

#endif
