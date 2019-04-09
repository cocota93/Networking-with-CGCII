//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Utility Classes                              *
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
// Prototype
//----------------------------------------------------------------------------
#define	CGUTIL_CLASSES

namespace CGEDC
{
	class CCRC;
}

// Zlib에 뜨는 Warning 때문임.
#if defined(_MSC_VER)
	#pragma warning (disable:6385)
#endif


//----------------------------------------------------------------------------
// head File (1)
//----------------------------------------------------------------------------
// 1) Object Classes
#include "CGObjectClasses.h"

// 2) Base
#include <malloc.h>
#include <typeinfo>
#include <memory>

// 3) Definitions
#include "CGUtilClasses/CGDefinitionsUtilProtocol.h"
#include "CGUtilClasses/CGDefinitionsUtil.h"


//----------------------------------------------------------------------------
// head File (2)
//----------------------------------------------------------------------------
// 1) EDC관련
#include "CGUtilClasses/CodeClasses/CGEDCCRC.h"
#include "CGUtilClasses/CodeClasses/CGEDCChecksum.h"
#include "CGUtilClasses/CodeClasses/CGEDCMD5.h"

// 2) Crytor관련
#include "CGUtilClasses/CodeClasses/CGCryptBase.h"
#include "CGUtilClasses/CodeClasses/CGCryptPNCodeBYTE.h"
#include "CGUtilClasses/CodeClasses/CGCryptPNCodeDWORD.h"
#include "CGUtilClasses/CodeClasses/CGCryptCSP.h"
#include "CGUtilClasses/CodeClasses/CGCryptBase64.h"

// 3) Compression관련
#include "CGUtilClasses/CodeClasses/CGCompress.h"


//----------------------------------------------------------------------------
// Extern
//----------------------------------------------------------------------------
// 1) Default CRC
namespace CGEDC
{
	extern	CGEDC::CCRC			DefaultCRC;
}


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
		#pragma comment (lib,"CGUtilCodeClasses64_DLL_v140_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses64_v140_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses_DLL_v140_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses_v140_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses_v140.lib")
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
		#pragma comment (lib,"CGUtilCodeClasses64_DLL_v120_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses64_v120_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses_DLL_v120_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses_v120_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses_v120.lib")
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
		#pragma comment (lib,"CGUtilCodeClasses64_DLL_v110_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses64_v110_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses_DLL_v110_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses_v110_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses_v110.lib")
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
		#pragma comment (lib,"CGUtilCodeClasses64_DLL_v100_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses64_v100_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses_DLL_v100_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
		#pragma comment (lib,"CGUtilCodeClasses_v100_Debug.lib")
		#else
		#pragma comment (lib,"CGUtilCodeClasses_v100.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


#else

#endif

#endif
