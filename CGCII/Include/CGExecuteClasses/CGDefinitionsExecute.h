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
//
// Definitions
//
//-----------------------------------------------------------------------------
template<class T> struct is_lambda_functor_type : std::false_type {};
template<class T> struct is_lambda_functor_type<std::function<T>> : std::true_type {};
template<class T> struct is_functor_type
{
	static const bool value = is_lambda_functor_type<typename std::decay<T>::type>::value || std::is_function<typename std::remove_pointer<typename std::decay<T>::type>::type>::value;
};


//-----------------------------------------------------------------------------
//
// For Exception
//
//-----------------------------------------------------------------------------
namespace CGException
{

#if !defined(_MSC_VER)
typedef enum _MINIDUMP_TYPE
{
    MiniDumpNormal                         = 0x00000000,
    MiniDumpWithDataSegs                   = 0x00000001,
    MiniDumpWithFullMemory                 = 0x00000002,
    MiniDumpWithHandleData                 = 0x00000004,
    MiniDumpFilterMemory                   = 0x00000008,
    MiniDumpScanMemory                     = 0x00000010,
    MiniDumpWithUnloadedModules            = 0x00000020,
    MiniDumpWithIndirectlyReferencedMemory = 0x00000040,
    MiniDumpFilterModulePaths              = 0x00000080,
    MiniDumpWithProcessThreadData          = 0x00000100,
    MiniDumpWithPrivateReadWriteMemory     = 0x00000200,
    MiniDumpWithoutOptionalData            = 0x00000400,
    MiniDumpWithFullMemoryInfo             = 0x00000800,
    MiniDumpWithThreadInfo                 = 0x00001000,
    MiniDumpWithCodeSegs                   = 0x00002000,
    MiniDumpWithoutAuxiliaryState          = 0x00004000,
    MiniDumpWithFullAuxiliaryState         = 0x00008000,
    MiniDumpWithPrivateWriteCopyMemory     = 0x00010000,
    MiniDumpIgnoreInaccessibleMemory       = 0x00020000,
    MiniDumpWithTokenInformation           = 0x00040000,
    MiniDumpWithModuleHeaders              = 0x00080000,
    MiniDumpFilterTriage                   = 0x00100000,
    MiniDumpValidTypeFlags                 = 0x001fffff,
} MINIDUMP_TYPE;
#endif

// 1) Mini Dump (가장 기본적인 Dump만 출력한다.)
const MINIDUMP_TYPE	MINIDUMP_TYPE_MINI	  =	MINIDUMP_TYPE(
								MiniDumpNormal							// 가장 기본적인 사항
								);
// 2) Midium Dump 
const MINIDUMP_TYPE	MINIDUMP_TYPE_DETAIL  =	MINIDUMP_TYPE(
								MiniDumpWithPrivateReadWriteMemory |	// 읽거나 쓸수 있는 메모리들(Stack/Heap/TLS)
								MiniDumpWithDataSegs |					// 전역변수
								MiniDumpWithHandleData |				// 핸들 정보(Socket, File, 등등...)
								MiniDumpWithFullMemoryInfo | 			// 가상 메모리 상의 레이아웃 정보
								MiniDumpWithThreadInfo |				// 추가적인 Thread 정보 (Thread시간들, 시작주소 등등...)
								MiniDumpWithUnloadedModules				// 
								);

// 3) Full Dump
const MINIDUMP_TYPE	MINIDUMP_TYPE_FULL	  =	MINIDUMP_TYPE(
								MiniDumpWithFullMemory |				// 모든 메모리읽거나 쓸수 있는 메모리들(Stack/Heap/TLS)
								MiniDumpWithFullMemoryInfo |			// 가상 메모리 상의 레이아웃 정보
								MiniDumpWithHandleData |				// 핸들 정보(Socket, File, 등등...)
								MiniDumpWithThreadInfo |				// 추가적인 Thread 정보 (Thread시간들, 시작주소 등등...)
								MiniDumpWithUnloadedModules				// 
								);

// 4) 
#define	DEFAULT_MAX_EXCEPTIONLIMIT	4096
#define	DEFAULT_MINIDUMP_TYPE		MINIDUMP_TYPE_MINI

// 5) Dump Info 
struct CGDUMP_INFO
{
	// 1) 발생한 Thread
    uint32_t					dwThreadId;

	// 2) 발생한 시간
	TIME::SYSTEM::time_point	timeOccureFirst;
	TIME::SYSTEM::time_point	timeOccureLast;

	// 3) 발생한 횟수
	size_t						iTimes;

	// 4) 발행한 내용
#if defined(_MSC_VER)
	EXCEPTION_RECORD			sExceptionRecords;
	CONTEXT						sContextRecord;
#endif

	// 5) 덤프 파일
	_STRING					strDumpName;
};


}

// 6) Message for DUMP Notification
struct CGMSG_DUMP : public CGMSG
{
public:
	CGMSG_DUMP()			{}
	CGMSG_DUMP(const CGException::CGDUMP_INFO& p_rData) : CGMSG(CGMESSAGE::DUMP), sDumpInfo(p_rData)	{}

public:
	CGException::CGDUMP_INFO	sDumpInfo;
};


//-----------------------------------------------------------------------------
//
// Thread
//
//-----------------------------------------------------------------------------
// 1) Thread ID
#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2012
	typedef	std::thread::native_handle_type	THREAD_ID;
#else
	typedef	HANDLE		THREAD_ID;
#endif

// 1) Thread Info
struct THREAD_STATISTICS
{
public:
	THREAD_ID			idThread;			// Thread ID

	uint64_t			qwExecuted;			// 실행된 횟수
	uint64_t			qwError;			// Error 횟수

	TICK::time_point	tickLastExecute;	// 마지막 실행된 Tick
	bool				bExecuting;			// 실행중인지 여부

public:
	THREAD_STATISTICS() : 
		idThread(0),
		qwExecuted(0),
		qwError(0),
		tickLastExecute(TICK::duration::zero()),
		bExecuting(false)
	{}
};

// 3) Definitions for Thread
typedef void	(*TFUNCTION)();
typedef void	(*TFUNCTION_PARAM)(void* lpThreadParameter);
typedef intptr_t(*TFUNCTION_HRESULT)();
typedef intptr_t(*TFUNCTION_PARAM_HRESULT)(void* lpThreadParameter);
typedef	std::function<void()>				TLAMBDA;
typedef	std::function<intptr_t()>			TLAMBDA_HRESULT;

extern "C" void* _ReturnAddress(void);

#if defined(_MSC_VER)
	#pragma intrinsic	(_ReturnAddress)
#endif
