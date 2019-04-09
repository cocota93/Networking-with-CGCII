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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// eOBJECT_STATE
//
//    1) Initialize	eOBJECT_STATE::NONE    ->eOBJECT_STATE::INITIALIZING_PENDING ->eOBJECT_STATE::STOPPED
//    2) Start		eOBJECT_STATE::STOPPED ->eOBJECT_STATE::START_PENDING        ->eOBJECT_STATE::RUNNING
//    3) Stop		eOBJECT_STATE::RUNNING ->eOBJECT_STATE::STOP_PENDING		   ->eOBJECT_STATE::STOPPED
//    4) Destory	eOBJECT_STATE::STOPPED ->eOBJECT_STATE::DESTROYING_PENDING   ->eOBJECT_STATE::NONE
//    5) Pause		eOBJECT_STATE::RUNNING ->eOBJECT_STATE::PAUSE_PENDING		   ->eOBJECT_STATE::PAUSED
//    6) Continue	eOBJECT_STATE::PAUSED  ->eOBJECT_STATE::CONTINUE_PENDING	   ->eOBJECT_STATE::RUNNING
//
//-----------------------------------------------------------------------------
enum class eOBJECT_STATE : int32_t
{
	NONE									 = 0,
	STOPPED									 = 1,	// SERVICE_STOPPED
	START_PENDING							 = 2,	// SERVICE_START_PENDING
	STOP_PENDING							 = 3,	// SERVICE_STOP_PENDING
	RUNNING									 = 4,	// SERVICE_RUNNING
	CONTINUE_PENDING						 = 5,	// SERVICE_CONTINUE_PENDING
	PAUSE_PENDING							 = 6,	// SERVICE_PAUSE_PENDING
	PAUSED									 = 7,	// SERVICE_PAUSED
	INITIALIZING_PENDING					 = 8,
	DESTROYING_PENDING						 = 9,
	UPDATE									 = 10,
	COMMIT									 = 11,
	NOTCONNECT								 = 12,
	DEFAULT									 = 0xff
};

enum class  eOBJECT_RESULT : uint32_t
{
	SUCCESS									 = 0x0000,	// 0x0*** Success
	PENDING									 = 0x0001,	//        Success Setting and Execution Pended
	FAIL									 = 0x1000,	// 0x1*** Fail
	FAIL_DISABLED							 = 0x1001,
	TIME_OUT								 = 0x1012,
	ALEADY_EXIST							 = 0x1003,
	EXPIRED									 = 0x1014,
	NOT_EXIST								 = 0x1005,
	NOT_READY								 = 0x1006,
	BANNED_MEMBER							 = 0x1017,
	MEMBER_FULL								 = 0x1018,
	INVALID_MEMBER							 = 0x1019,
	INVALID_PASSWORD						 = 0x101a,
	INVALID_PLATFORM						 = 0x101b,
	ALEADY_EXIST_NICKNAME					 = 0x101c,
	ALEADY_DONE								 = 0x101d,

	CANCEL									 = 0x2000,	// 0x2*** Cancel

	ERROR_									 = 0x3000,	// 0x3*** Error
	LOGIC_ERROR								 = 0x3001,
	LENGTH_ERROR							 = 0x3002,
	DOMAIN_ERROR							 = 0x3003,
	OUT_OF_REANGE							 = 0x3004,
	RUNTIME_ERROR							 = 0x3005,
	OVERFLOW_ERROR							 = 0x3006,
	UNDERFLOW_ERROR							 = 0x3007,
	RANGE_ERROR								 = 0x3008,
	BAD_ALLOC								 = 0x3009,
	BAD_FUNCTION_CALL						 = 0x300a,
	CONCURRENT_LOCK_ERROR					 = 0x300b,
	ACCESS_DENIED							 = 0x300c,
	NO_INITIALIZED							 = 0x300d,
	INVALID_ARGUMENT						 = 0x300e,
	NOT_ALLOWED								 = 0x3010,

	EXCEPTION								 = 0x4000,	// 0x4*** Exception
	BAD_EXCEPTION							 = 0x4001,
	FORCE_CLOSE								 = 0x4002,
	NOT_SUPPORT								 = 0x4003,
	INVALID_CALL							 = 0x4004,

	PROCESS									 = 0x5000,	// 0x5*** Process
	REQUEST									 = 0x5001,
	COMPLETE								 = 0x5002,

	CGCII_EXPIRED							 = 0xfe00,
	UNDEFINED								 = 0xff00	// 0xff** Not Defined
};

enum class  eOBJECT_TYPE : uint32_t
{
	// 1) Not Defined
	UNDEFINED								 = 0x00000000,

	// 2) Common
	EXECUTOR								 = 0x00100000,
	EXECUTOR_THREAD							 = 0x00100001,
	EXECUTOR_SCHEDULABLE					 = 0x00100002,
	EXECUTOR_COMPLETION_PORT				 = 0x00100003,
	EXECUTOR_COMPLETION_PORT_THREAD			 = 0x00100004,
	EXECUTOR_LIST							 = 0x00100005,
	EXECUTOR_LIST_PRIORITY					 = 0x00100006,
	EXECUTOR_LIST_THREAD					 = 0x00100007,
	EXECUTOR_QUEUED							 = 0x00100008,
	EXECUTOR_QUEUED_THREAD					 = 0x00100009,
	EXECUTOR_SINGLE_EXECUTE					 = 0x0010000a,
	EXECUTOR_SINGLE_EXECUTE_THREAD			 = 0x0010000b,
	EXECUTABLE								 = 0x0011000c,
	EXECUTABLE_BATCH_FUNCTION				 = 0x0011000d,
	EXECUTABLE_BATCH_FUNCTION_MEMBER		 = 0x0011000e,
	EXECUTABLE_BATCH_NOTIFY					 = 0x0011000f,
	EXECUTABLE_BATCH_WAIT					 = 0x00110010,
	EXECUTABLE_FUNCTION						 = 0x00110011,
	EXECUTABLE_FUNCTION_MEMBER				 = 0x00110012,
	EXECUTABLE_LIST							 = 0x00110013,
	EXECUTABLE_EXECUTABLE					 = 0x00110014,
	SCHEDULABLE								 = 0x00120000,
	SCHEDULABLE_EXECUTABLE					 = 0x00120001,
	SCHEDULABLE_FUNCTION					 = 0x00120002,
	SCHEDULABLE_FUNCTION_MEMBER				 = 0x00120003,
	SCHEDULABLE_LIST						 = 0x00120004,
	SCHEDULABLE_EXCEPTION_OBSERVER			 = 0x00120005,
	SCHEDULABLE_FACTORY_GARBAGE				 = 0x00120006,
	UPDATABLE								 = 0x00130000,
	UPDATABLE_BATCH							 = 0x00130001,
	FILE									 = 0x00140000,

	// 3) Socket
	SOCKET									 = 0x00200000,
	ACCEPTOR								 = 0x00210000,
	CONNECTOR								 = 0x00220000,

	// 4) Server
	EVENT_OBJECT							 = 0x0030000,
	EVENT_OBJECT_ITERATION					 = 0x0030001,
	EVENT_OBJECT_ITERATION_FUNCTION			 = 0x0030002,
	EVENT_OBJECT_ONCE						 = 0x0030003,
	EVENT_OBJECT_ONCE_FUNCTION				 = 0x0030004,
	EVENT_OBJECT_SCHEDULE					 = 0x0030005,
	EVENT_OBJECT_SCHEDULE_FUNCTION			 = 0x0030006,
	EVENT_OBJECT_START_END					 = 0x0030007,
	EVENT_OBJECT_START_END_FUNCTION			 = 0x0030008,
	EVENT_OBJECT_START_ITERATION_END		 = 0x0030009,
	EVENT_OBJECT_START_ITERATION_END_FUNCTION= 0x003000a,
	EVENT_SCHEDULE							 = 0x0031000,
	EVENT_SCHEDULE_FUNCTION					 = 0x0031001,
	EVENT_SCHEDULE_LAMBDA					 = 0x0031002,

	// 5) Server System
	GROUP									 = 0x00400000,
	GROUP_COUNT								 = 0x00410000,
	GROUP_LIST								 = 0x00420000,
	GROUP_ARRAY								 = 0x00430000,

	// 6) Account
	REPOSITORY								 = 0x00500000,
	REPOSITORY_DB							 = 0x00511000,
	REPOSITORY_REDIS						 = 0x00512000,
	REPOSITORY_HUB							 = 0x00513000,
	REPOSITORY_REMOTE						 = 0x00514000,
	ACCESSABLE								 = 0x00520000,
	ACCESSABLE_HOLDER						 = 0x00521000,
	DEPOT									 = 0x00530000,
	DEPOT_REMOTE							 = 0x00531000,

	// 7) Querier
	QUERIER									 = 0x006000000,
	QUERIER_DB_SQL							 = 0x006100000,
	QUERIER_DB_CASSANDRA					 = 0x006200001,
	QUERIER_DB_MONGODB						 = 0x006200002,
	QUERIER_REDIS							 = 0x006200003,
	QUERIER_HTTP							 = 0x006300000,
};

const _CHAR* GetString_ObjectState(eOBJECT_STATE _iState);
const _CHAR* GetString_ObjectResult(eOBJECT_RESULT _iResult);
const _CHAR* GetString_ObjectType(eOBJECT_TYPE _iType);


//-----------------------------------------------------------------------------
//
// OBJECT_ID
//
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning(disable:4201)
#endif

struct OBJECT_ID
{
public:
			union
			{
				struct
				{
					eOBJECT_TYPE		dwType;
					uint32_t			dwFactory;
				};
				uint64_t				qwType;
			};

			union
			{
				struct
				{
					uint32_t			iProductSerial;
					uint32_t			wShipmentSerial;
				};
				uint64_t				qwSerial;
			};
public:
			OBJECT_ID()	{}
			OBJECT_ID(const OBJECT_ID& _Rhs) : qwType(_Rhs.qwType), qwSerial(_Rhs.qwSerial)	{}
			OBJECT_ID(uint64_t _qwSerial, uint64_t _qwType=0) : qwType(_qwType), qwSerial(_qwSerial) {}
			OBJECT_ID(uint64_t _qwSerial, eOBJECT_TYPE _dwType, uint32_t _dwFactory) : dwType(_dwType), dwFactory(_dwFactory), qwSerial(_qwSerial) {}
public:
			OBJECT_ID&	operator=(const OBJECT_ID& _Rhs)		{ qwType=_Rhs.qwType; qwSerial=_Rhs.qwSerial; return *this;}
																  
			bool		operator==(const OBJECT_ID& _Rhs) const	{ return qwSerial==_Rhs.qwSerial;}
			bool		operator!=(const OBJECT_ID& _Rhs) const	{ return qwSerial!=_Rhs.qwSerial;}
			bool		operator> (const OBJECT_ID& _Rhs) const	{ return qwSerial> _Rhs.qwSerial;}
			bool		operator>=(const OBJECT_ID& _Rhs) const	{ return qwSerial>=_Rhs.qwSerial;}
			bool		operator< (const OBJECT_ID& _Rhs) const	{ return qwSerial< _Rhs.qwSerial;}
			bool		operator<=(const OBJECT_ID& _Rhs) const	{ return qwSerial<=_Rhs.qwSerial;}
																  
			bool		operator==(const uint64_t& _Rhs) const	{ return qwSerial==_Rhs;}
			bool		operator!=(const uint64_t& _Rhs) const	{ return qwSerial!=_Rhs;}
			bool		operator> (const uint64_t& _Rhs) const	{ return qwSerial> _Rhs;}
			bool		operator>=(const uint64_t& _Rhs) const	{ return qwSerial>=_Rhs;}
			bool		operator< (const uint64_t& _Rhs) const	{ return qwSerial< _Rhs;}
			bool		operator<=(const uint64_t& _Rhs) const	{ return qwSerial<=_Rhs;}
};

#define	DEFAULT_POOL_TLS_CACH_SIZE		8


#if defined(_MSC_VER)
	#pragma warning(default:4201)
#endif
