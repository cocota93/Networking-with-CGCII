//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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
#define	CGOBJECT_CLASSES



//----------------------------------------------------------------------------
// Definitions for Configuration
//----------------------------------------------------------------------------
// 1) use Debug NEW
//    . Debugging시 NEW<T>를 사용해서 생성한 객체의 소스코드의 위치를 찾을 수
//      있도록 해주는 기능이다.
#ifdef _DEBUG
	#define _USE_DEBUG_NEW
#endif

// 2) All NET<T> manage...
//    기본적으로는 NCGPoolable<T> 객체만 객체의 생성수와 소멸 수와 같은 통계
//    정보를 작성하는데 이 옵션을 사용하게 되면 Pool을 사용하는 객체든 아니든
//    NEW<T>로 생성되는 모든 객체에 대한 통계 정보를 작성한다.
#ifdef _DEBUG
	#define	_USE_CREATE_FACTORY_FOR_ALL_OBJECT
#endif


//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 1) Object Classes
#include "CGCommon.h"										// Common

// 2) System Time
#include "CGObjectClasses/CGTimeWindows.h"

// 3) Object Definitions
#include "CGObjectClasses/CGDefinitionsObject.h"

// 4) Exception
#include "CGObjectClasses/CGExceptions.h"

// 5) Definitions for...
namespace CGD
{
	class _PASS;
}

class ICGInitializable;
class ICGStartable;
class ICGDestroyable;
class ICGStopable;


//----------------------------------------------------------------------------
// Creation & Reference Counting
//----------------------------------------------------------------------------
// 1) Reference Counting
#include "CGObjectClasses/ICGReferenceable.h"
#include "CGObjectClasses/ICGReferenceProxy.h"

// 2) Commentable
#include "CGObjectClasses/ICGDescribable.h"

// 3) Pointer
#include "CGObjectClasses/CGPTR.h"
#include "CGObjectClasses/CGOWN.h"
#include "CGObjectClasses/CGOBJ.h"
#include "CGObjectClasses/CGNEW.h"

// 4) Attachable
#include "CGObjectClasses/ICGAttachable.h"
#include "CGObjectClasses/NCGAttachable.h"

// 5) Registerable
#include "CGObjectClasses/ICGRegisterable.h"
#include "CGObjectClasses/NCGRegisterable.h"

// 6)
#include "CGObjectClasses/CGManagerRegister.h"

// 7) Acquirable
#include "CGObjectClasses/ICGAcquirable.h"


//----------------------------------------------------------------------------
// Messageable & Dispatcher
//----------------------------------------------------------------------------
// 1) Message Definitions
#include "CGObjectClasses/CGDefinitionsObjectMessage.h"

// 2) Messageable
#include "CGObjectClasses/ICGMessageable.h"
#include "CGObjectClasses/NCGMessageable.h"

// 3) Dispatchable
#include "CGObjectClasses/ICGDispatchable.h"
#include "CGObjectClasses/NCGDispatchable.h"
#include "CGObjectClasses/NCGDispatchableSingle.h"
#include "CGObjectClasses/NCGDispatchableStatic.h"


//----------------------------------------------------------------------------
// Nameable
//----------------------------------------------------------------------------
// 1) Nameable
#include "CGObjectClasses/ICGNameable.h"				// Nameable Interface
#include "CGObjectClasses/NCGNameableString.h"			// Nameable String

// 2) Identifiable
#include "CGObjectClasses/ICGObjectIdentifiable.h"		// Identifiable Interface


//----------------------------------------------------------------------------
// Object and ...
//----------------------------------------------------------------------------
#include "CGObjectClasses/ICGResource.h"				// Resource

#include "CGObjectClasses/ICGObjectState.h"				// Object
#include "CGObjectClasses/ICGDestroyable.h"				// Destroyable
#include "CGObjectClasses/ICGStartable.h"				// Startable (Start/Stop)
#include "CGObjectClasses/ICGPausable.h"				// Pausable (Pause/Resume)
#include "CGObjectClasses/ICGInitializable.h"			// Initializable (Initialize/Destroy)
#include "CGObjectClasses/ICGUpdatable.h"				// Updatable

#include "CGObjectClasses/NCGObjectState.h"				// Object Status
#include "CGObjectClasses/NCGStartable.h"				// Startable (Start/Stop)
#include "CGObjectClasses/NCGPausable.h"				// Pausable (Pause/Resume)
#include "CGObjectClasses/NCGInitializable.h"			// Initializable (Initialize/Destroy)

#include "CGObjectClasses/CGResourceManager.h"			// Resource Manager

#include "CGObjectClasses/CGTrace.h"					// Resource Manager

#include "CGObjectClasses/NCGsingleton.h"				// Singleton



//-----------------------------------------------------------------------------
// Buffer
//-----------------------------------------------------------------------------
// 1) Util Classes
#include "CGUtilClasses/CodeClasses/CGEDCCRC.h"
#include "CGUtilClasses/CodeClasses/CGCompress.h"

// 2) Default CRC
namespace CGEDC
{
	extern	CGEDC::CCRC			DefaultCRC;
}

// Begin Pragma
#if defined(_MSC_VER)
	// warning C4344: behavior change: use of explicit template arguments results in call to ...
	//    - Causes in front function
	#pragma warning(disable:4344)
#else
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wvarargs"
#endif



// 3) Definitions
class	CCGBuffer;
struct	SEND;
struct	SEND_TO;

// 4) Default Definitions
#include <atomic>

// 5) CGD Buffer
#include <CGDbuffer>

#include "CGObjectClasses/ICGBuffer.h"
#include "CGObjectClasses/CGBuffer.h"


//-----------------------------------------------------------------------------
// Factory
//-----------------------------------------------------------------------------
// Definitions) 
namespace CGFactory
{
	class Manager;
}

// 1) Definitions for Factory
#include "CGObjectClasses/CGDefinitionsFactory.h"
#include "CGObjectClasses/CGDefinitionsFactoryProtocol.h"

// 2) Factory
#include "CGObjectClasses/ICGFactory.h"					// ICGFactory
#include "CGObjectClasses/CGFactoryManager.h"			// Factory Manager

// Definitions) 
struct SEND;
struct SEND_TO;

// End Pragma
#if defined(_MSC_VER)
#pragma warning(default:4344)
#else
#pragma GCC diagnostic pop
#endif


//-----------------------------------------------------------------------------
// Pool
//-----------------------------------------------------------------------------
namespace CGPool
{
	class _traits_has_pool {};
	class _traits_system {};
	class _traits_memory {};

	template<class TOBJECT> typename std::enable_if<!std::is_base_of<_traits_system, TOBJECT>::value && !std::is_base_of<_traits_memory, TOBJECT>::value, eFACTORY_TYPE>::type	_get_default_factory_type() { return eFACTORY_TYPE::POOL_USER; }
	template<class TOBJECT> typename std::enable_if<std::is_base_of<_traits_system, TOBJECT>::value, eFACTORY_TYPE>::type	_get_default_factory_type() { return eFACTORY_TYPE::POOL_SYSTEM; }
	template<class TOBJECT>	typename std::enable_if<std::is_base_of<_traits_memory, TOBJECT>::value, eFACTORY_TYPE>::type	_get_default_factory_type() { return eFACTORY_TYPE::POOL_MEMORYBLOCK; }
}

// 1) Base
#include <malloc.h>
#include <typeinfo>
#include <memory>

// 2) Pre Definitions
#include "CGObjectClasses/CGDefinitionsFactoryPoolMemoryBlock.h"

// 3) Interfaces
#include "CGObjectClasses/ICGPoolable.h"				// IPoolable

// 4) Pool
#include "CGObjectClasses/CGFactoryObject.h"			// Allocator
#include "CGObjectClasses/CGFactoryPoolObject.h"		// Object Pool
#include "CGObjectClasses/CGFactoryPoolObjectTLS.h"		// TLS Object Pool
#include "CGObjectClasses/CGFactoryPoolMemory.h"		// Fixed-size Memory Pool
#include "CGObjectClasses/CGFactoryPoolBuffer.h"		// Buffer Pool

// 5) Poolable
#include "CGObjectClasses/NCGPoolable.h"				// NPoolable

// 6) Memory Block Pool
#include "CGObjectClasses/CGFactoryPoolMemoryBlock.h"	// Memory Block Pool.(Default)

// 7) Definitions for Buffer
#include "CGObjectClasses/CGDefinitionsBuffer.h"	// Definitions

inline CCGBuffer CCGBuffer::clone(CGNEW_DEBUG_INFO_PARAMETERS)
{
	CCGBuffer a=MEM_POOL_ALLOC_WITH_DEBUG_INFO(len, _Filename, _Line);
	
	a.copy(*this); 
	
	return a; 
}

inline CCGBuffer CCGBuffer::operator+(const CCGBuffer& _Rhs) const
{
	// 1) 새로운 Buffer를  할당한다.
	CCGBuffer	buffer	 = MEM_POOL_ALLOC(len+_Rhs.len);

	// 2) 추가한다.
	buffer.append(*this);
	buffer.append(_Rhs);

	// Return) 
	return	buffer;
}

inline uint32_t CCGBuffer::get_CRC() const
{
	return CGEDC::DefaultCRC.get_CRC((unsigned char*)buf, len);
}

inline uint32_t CCGBuffer::get_CRC(_In_ const CGEDC::CCRC* _CRC) const
{
	return _CRC->get_CRC((unsigned char*)buf, len);
}


//----------------------------------------------------------------------------
// CGDK
//----------------------------------------------------------------------------
#include "CGObjectClasses/CGDK.h"						// CGDK


// ----------------------------------------------------------------------------
// Function
// ----------------------------------------------------------------------------
char*			ByteDWORDToString(_Out_writes_(_iSize) char* _strBuffer, _In_ int _iSize, _In_ unsigned int _dwValue);
wchar_t*		ByteDWORDToString(_Out_writes_(_iSize) wchar_t* _strBuffer, _In_ int _iSize, _In_ unsigned int _dwValue);

char*			ByteQWORDToString(_Out_writes_(_iSize) char* _strBuffer, _In_ int _iSize, _In_ uint64_t _qwValue);
wchar_t*		ByteQWORDToString(_Out_writes_(_iSize) wchar_t* _strBuffer, _In_ int _iSize, _In_ uint64_t _qwValue);

char*			ByteFloatToString(_Out_writes_(_iSize) char* _strBuffer, _In_ int _iSize, _In_ float p_fValue);
wchar_t*		ByteFloatToString(_Out_writes_(_iSize) wchar_t* _strBuffer, _In_ int _iSize, _In_ float p_fValue);

struct CGMSG_BUFFER : public CGMSG
{
public:
	CGMSG_BUFFER() {}
	CGMSG_BUFFER(uint32_t _message) : CGMSG(_message) {}
	CGMSG_BUFFER(uint32_t _message, void* _pSource) : CGMSG(_message, _pSource) {}
	CGMSG_BUFFER(uint32_t _message, void* _pSource, const CCGBuffer& _Buffer) : CGMSG(_message, _pSource), Buffer(_Buffer) {}
	CGMSG_BUFFER(uint32_t _message, const CCGBuffer& _Buffer) : CGMSG(_message), Buffer(_Buffer) {}
	CGMSG_BUFFER(const CCGBuffer& _Buffer) : CGMSG(CGMESSAGE::SYSTEM::BUFFER), Buffer(_Buffer) {}

public:
	CCGBuffer			Buffer;
};



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
			#pragma comment (lib,"CGObjectClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses_v140.lib")
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
			#pragma comment (lib,"CGObjectClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses_v120.lib")
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
			#pragma comment (lib,"CGObjectClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses_v110.lib")
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
			#pragma comment (lib,"CGObjectClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGObjectClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGObjectClasses_v100.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


#else

#endif

#endif
