//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               MFC Controls                                *
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
#define	CGMFC_CONTROLS

#ifdef _CGMFCCONTROLS_EXT
	#define CGMFCCONTROL_EXT_API	__declspec(dllexport)
	#define CGMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGMFCCONTROL_EXT_DATA	__declspec(dllexport)
#else
	#define CGMFCCONTROL_EXT_API	__declspec(dllimport)
	#define CGMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGMFCCONTROL_EXT_DATA	__declspec(dllimport)
#endif

#define	CGUPDATE							1


//----------------------------------------------------------------------------
//  head Fileµé                                                               
//----------------------------------------------------------------------------
// 1) ´Ù¸¥ Project
#include "CGExecuteClasses.h"

#define	CGDIALOG	CDialogEx
#include "afxdialogex.h"

// 2) Definitions
#include "CGMFCControls/CGStaticGraph.h"
#include "CGMFCControls/CGListBox.h"
#include "CGMFCControls/CGListBoxLog.h"

// 3) Child Dialog
#include "CGMFCControls/CGChildDialog.h"
#include "CGMFCControls/CGChildThreadList.h"
#include "CGMFCControls/CGChildReferenceList.h"
#include "CGMFCControls/CGChildSchedulableList.h"
#include "CGMFCControls/CGChildExecutorList.h"
#include "CGMFCControls/CGDialogCGDKComponentInfo.h"

// 4) Dialog
#include "CGMFCControls/CGDialogObjectFactoryStatus.h"
#include "CGMFCControls/CGDialogThreadStatus.h"
#include "CGMFCControls/CGDialogReferenceStatus.h"

// 5) Functions
CGMFCCONTROL_EXT_API	CCGStaticGraph* WINAPI CGCreateControlStaticGraph(int _DataSize, int _GridUnit);
CGMFCCONTROL_EXT_API	INT_PTR WINAPI	DoModalObjectFactoryStatus(CGFactory::Manager* p_pManager);
CGMFCCONTROL_EXT_API	INT_PTR WINAPI	DoModalThreadStatus(CGAPI::ManagerThread* p_pManager);
CGMFCCONTROL_EXT_API	INT_PTR WINAPI	DoModalReferenceStatus(ICGReferenceable* _Object);
CGMFCCONTROL_EXT_API	INT_PTR WINAPI	DoModalCGDKComponentInfo(const std::vector<CGDK::COMPONENT>& _vectorCGDKComponents);



//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _CGMFCCONTROLS_EXT

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

#ifndef _UNICODE
#error	"CGNetSocketMFCControls support UNICODE Only"
#endif


//----------------------------------------------------------------------------
// * VS2015 Lib 
//----------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGMFCControls64_v140_Debug.lib")
	#else
		#pragma comment (lib,"CGMFCControls64_v140.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGMFCControls_v140_Debug.lib")
	#else
		#pragma comment (lib,"CGMFCControls_v140.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2012 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=120

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGMFCControls64_v120_Debug.lib")
	#else
		#pragma comment (lib,"CGMFCControls64_v120.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGMFCControls_v120_Debug.lib")
	#else
		#pragma comment (lib,"CGMFCControls_v120.lib")
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
		#pragma comment (lib,"CGMFCControls64_v110_Debug.lib")
	#else
		#pragma comment (lib,"CGMFCControls64_v110.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGMFCControls_v110_Debug.lib")
	#else
		#pragma comment (lib,"CGMFCControls_v110.lib")
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
		#pragma comment (lib,"CGMFCControls64_v100_Debug.lib")
	#else
		#pragma comment (lib,"CGMFCControls64_v100.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGMFCControls_v100_Debug.lib")
	#else
		#pragma comment (lib,"CGMFCControls_v100.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


#else

#endif

#endif