//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                            Server MFC Controls                            *
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
#define	CGSERVER_MFC_CONTROLS

#ifdef _CGSERVERMFCCONTROLS_EXT
	#define CGSERVERMFCCONTROL_EXT_API		__declspec(dllexport)
	#define CGSERVERMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGSERVERMFCCONTROL_EXT_DATA		__declspec(dllexport)
#else
	#define CGSERVERMFCCONTROL_EXT_API		__declspec(dllimport)
	#define CGSERVERMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGSERVERMFCCONTROL_EXT_DATA		__declspec(dllimport)
#endif

#pragma warning(disable:4407)


//----------------------------------------------------------------------------
//  head Fileµé                                                               
//----------------------------------------------------------------------------
// 1) CGNetServerAdminClasees
#include "CGMFCControls.h"
#include "CGServerEventClasses.h"
#include "CGServerLogClasses.h"

// 2) Child Dialog
#include "Server/Server/CGServerMFCControls/CGServerChildEventList.h"
#include "Server/Server/CGServerMFCControls/CGServerChildLogView.h"
#include "Server/Server/CGServerMFCControls/CGEventInfoDlg.h"


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _CGSERVERMFCCONTROLS_EXT

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
		#pragma comment (lib,"CGServerMFCControls64_v140_Debug.lib")
	#else
		#pragma comment (lib,"CGServerMFCControls64_v140.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerMFCControls_v140_Debug.lib")
	#else
		#pragma comment (lib,"CGServerMFCControls_v140.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2013 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=120

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerMFCControls64_v120_Debug.lib")
	#else
		#pragma comment (lib,"CGServerMFCControls64_v120.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerMFCControls_v120_Debug.lib")
	#else
		#pragma comment (lib,"CGServerMFCControls_v120.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2012 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=110

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerMFCControls64_v110_Debug.lib")
	#else
		#pragma comment (lib,"CGServerMFCControls64_v110.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerMFCControls_v110_Debug.lib")
	#else
		#pragma comment (lib,"CGServerMFCControls_v110.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2010 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=100

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerMFCControls64_v100_Debug.lib")
	#else
		#pragma comment (lib,"CGServerMFCControls64_v100.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGServerMFCControls_v100_Debug.lib")
	#else
		#pragma comment (lib,"CGServerMFCControls_v100.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


#else
	#error	"Unsupport Platform Toolset"
#endif

#endif