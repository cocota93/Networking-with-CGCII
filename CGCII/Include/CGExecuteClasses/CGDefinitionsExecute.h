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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
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

// 1) Mini Dump (���� �⺻���� Dump�� ����Ѵ�.)
const MINIDUMP_TYPE	MINIDUMP_TYPE_MINI	  =	MINIDUMP_TYPE(
								MiniDumpNormal							// ���� �⺻���� ����
								);
// 2) Midium Dump 
const MINIDUMP_TYPE	MINIDUMP_TYPE_DETAIL  =	MINIDUMP_TYPE(
								MiniDumpWithPrivateReadWriteMemory |	// �аų� ���� �ִ� �޸𸮵�(Stack/Heap/TLS)
								MiniDumpWithDataSegs |					// ��������
								MiniDumpWithHandleData |				// �ڵ� ����(Socket, File, ���...)
								MiniDumpWithFullMemoryInfo | 			// ���� �޸� ���� ���̾ƿ� ����
								MiniDumpWithThreadInfo |				// �߰����� Thread ���� (Thread�ð���, �����ּ� ���...)
								MiniDumpWithUnloadedModules				// 
								);

// 3) Full Dump
const MINIDUMP_TYPE	MINIDUMP_TYPE_FULL	  =	MINIDUMP_TYPE(
								MiniDumpWithFullMemory |				// ��� �޸��аų� ���� �ִ� �޸𸮵�(Stack/Heap/TLS)
								MiniDumpWithFullMemoryInfo |			// ���� �޸� ���� ���̾ƿ� ����
								MiniDumpWithHandleData |				// �ڵ� ����(Socket, File, ���...)
								MiniDumpWithThreadInfo |				// �߰����� Thread ���� (Thread�ð���, �����ּ� ���...)
								MiniDumpWithUnloadedModules				// 
								);

// 4) 
#define	DEFAULT_MAX_EXCEPTIONLIMIT	4096
#define	DEFAULT_MINIDUMP_TYPE		MINIDUMP_TYPE_MINI

// 5) Dump Info 
struct CGDUMP_INFO
{
	// 1) �߻��� Thread
    uint32_t					dwThreadId;

	// 2) �߻��� �ð�
	TIME::SYSTEM::time_point	timeOccureFirst;
	TIME::SYSTEM::time_point	timeOccureLast;

	// 3) �߻��� Ƚ��
	size_t						iTimes;

	// 4) ������ ����
#if defined(_MSC_VER)
	EXCEPTION_RECORD			sExceptionRecords;
	CONTEXT						sContextRecord;
#endif

	// 5) ���� ����
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

	uint64_t			qwExecuted;			// ����� Ƚ��
	uint64_t			qwError;			// Error Ƚ��

	TICK::time_point	tickLastExecute;	// ������ ����� Tick
	bool				bExecuting;			// ���������� ����

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
