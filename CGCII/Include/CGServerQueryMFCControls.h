//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Server DB MFC Controls                           *
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
//----------------------------------------------------------------------------
//  Prototype
//----------------------------------------------------------------------------
#define	CGDBMFC_CONTROLS

#ifdef _CGSERVERQUERYMFCCONTROLS_EXT
	#define CGSERVERQUERYMFCCONTROL_EXT_API		__declspec(dllexport)
	#define CGSERVERQUERYMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGSERVERQUERYMFCCONTROL_EXT_DATA	__declspec(dllexport)
#else
	#define CGSERVERQUERYMFCCONTROL_EXT_API		__declspec(dllimport)
	#define CGSERVERQUERYMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGSERVERQUERYMFCCONTROL_EXT_DATA	__declspec(dllimport)
#endif


//----------------------------------------------------------------------------
//  head Fileµé                                                               
//----------------------------------------------------------------------------
// 1) CGNetServerAdminClasees
#include "CGMFCControls.h"
#include "CGServerQueryClasses.h"

// 2) Child Dialog
#include "Server/ServerQuery/CGServerQueryMFCControls/CGChildServerQueryQuerierList.h"

// 3) Functions
CGSERVERQUERYMFCCONTROL_EXT_API CCGChildQuerierList* WINAPI CGCreateChildQuerierList(CGServerQuery::ManagerQuerier* p_pQuerierManager, CWnd* pParentWnd);


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _CGSERVERQUERYMFCCONTROLS_EXT

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
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerQueryMFCControls64_v140_Debug.lib")
	#else
		#pragma comment (lib,"CGServerQueryMFCControls64_v140.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerQueryMFCControls_v140_Debug.lib")
	#else
		#pragma comment (lib,"CGServerQueryMFCControls_v140.lib")
	#endif
#else
#endif


//----------------------------------------------------------------------------
// * VS2013 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=120

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerQueryMFCControls64_v120_Debug.lib")
	#else
		#pragma comment (lib,"CGServerQueryMFCControls64_v120.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerQueryMFCControls_v120_Debug.lib")
	#else
		#pragma comment (lib,"CGServerQueryMFCControls_v120.lib")
	#endif
#else
#endif


//----------------------------------------------------------------------------
// * VS2012 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=110

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerQueryMFCControls64_v110_Debug.lib")
	#else
		#pragma comment (lib,"CGServerQueryMFCControls64_v110.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerQueryMFCControls_v110_Debug.lib")
	#else
		#pragma comment (lib,"CGServerQueryMFCControls_v110.lib")
	#endif
#else
#endif


//----------------------------------------------------------------------------
// * VS2010 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=100

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerQueryMFCControls64_v100_Debug.lib")
	#else
		#pragma comment (lib,"CGServerQueryMFCControls64_v100.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerQueryMFCControls_v100_Debug.lib")
	#else
		#pragma comment (lib,"CGServerQueryMFCControls_v100.lib")
	#endif
#else
#endif


#endif

#endif