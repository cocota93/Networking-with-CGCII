//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                  MFC Controls for Network Socket Classes                  *
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
//  Prototype
//----------------------------------------------------------------------------
#define	CGNET_SOCKET_MFC_CONTROLS

#ifdef _CGNETSOCKETMFCCONTROLS_EXT
	#define CGNETSOCKETMFCCONTROL_EXT_API	__declspec(dllexport)
	#define CGNETSOCKETMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGNETSOCKETMFCCONTROL_EXT_DATA	__declspec(dllexport)
#else
	#define CGNETSOCKETMFCCONTROL_EXT_API	__declspec(dllimport)
	#define CGNETSOCKETMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGNETSOCKETMFCCONTROL_EXT_DATA	__declspec(dllimport)
#endif


//----------------------------------------------------------------------------
//  head File들                                                               
//----------------------------------------------------------------------------
// 1) CGCII Header files
#include "CGMFCControls.h"
#include "CGNetSocketClasses.h"

// 2) Definitions
#include "Network/Socket/CGNetSocketMFCControls/CGComboBoxConnective.h"

// 3) Child Dialog
#include "Network/Socket/CGNetSocketMFCControls/CGChildConnectableManager.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildConnectiveList.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildBinderControl.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildConnectiveInfo.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildConnectiveInfoMini.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildConnectiveConnectorControl.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildConnectorControl.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildConnectorControlEx.h"
//#include "Network/Socket/CGNetSocketMFCControls/CGChildConnectorList.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildTrafficInfo.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildTrafficInfoMini.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildTrafficInfoBriefReceive.h"
#include "Network/Socket/CGNetSocketMFCControls/CGChildTrafficInfoBriefSend.h"

// 4) Dialog
#include "Network/Socket/CGNetSocketMFCControls/CGDialogConnectiveStatus.h"
#include "Network/Socket/CGNetSocketMFCControls/CGDialogConnectableStatus.h"

// 5) 후순위...(AcceptorControl은 DialogConnectiveStatus가 필요함. 그래서 뒤에 따로...)
#include "Network/Socket/CGNetSocketMFCControls/CGChildAcceptorControl.h"

// 6) Functions
CGNETSOCKETMFCCONTROL_EXT_API	INT_PTR WINAPI	DoModalConnectiveStatus(CGNet::IO::Connective::Manager* p_pmangerConnective);
CGNETSOCKETMFCCONTROL_EXT_API	INT_PTR WINAPI	DoModalConnectableStatus(CGNet::IO::IConnectable* _pConnectable);



//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _CGNETSOCKETMFCCONTROLS_EXT

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

#ifndef _UNICODE
	#error	"CGNetSocketMFCControls support UNICODE Only"
#endif


//----------------------------------------------------------------------------
// * VS2015 Lib 
//---------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGNetSocketMFCControls64_v140_Debug.lib")
	#else
		#pragma comment (lib,"CGNetSocketMFCControls64_v140.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGNetSocketMFCControls_v140_Debug.lib")
	#else
		#pragma comment (lib,"CGNetSocketMFCControls_v140.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2013 Lib 
//---------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=120

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGNetSocketMFCControls64_v120_Debug.lib")
	#else
		#pragma comment (lib,"CGNetSocketMFCControls64_v120.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGNetSocketMFCControls_v120_Debug.lib")
	#else
		#pragma comment (lib,"CGNetSocketMFCControls_v120.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2012 Lib 
//-----------------------------------------------------------`-----------------
#elif _MSC_PLATFORM_TOOLSET>=110

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGNetSocketMFCControls64_v110_Debug.lib")
	#else
		#pragma comment (lib,"CGNetSocketMFCControls64_v110.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGNetSocketMFCControls_v110_Debug.lib")
	#else
		#pragma comment (lib,"CGNetSocketMFCControls_v110.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2010 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET==100

#if defined(_M_X64)
	#ifdef _DEBUG
		#pragma comment (lib,"CGNetSocketMFCControls64_v100_Debug.lib")
	#else
		#pragma comment (lib,"CGNetSocketMFCControls64_v100.lib")
	#endif
#elif defined(_M_IX86)
	#ifdef _DEBUG
		#pragma comment (lib,"CGNetSocketMFCControls_v100_Debug.lib")
	#else
		#pragma comment (lib,"CGNetSocketMFCControls_v100.lib")
	#endif
#else
	#error	"Unsupport Platform"
#endif


#else
	#error	"Unsupport Platform Toolset"
#endif

#endif