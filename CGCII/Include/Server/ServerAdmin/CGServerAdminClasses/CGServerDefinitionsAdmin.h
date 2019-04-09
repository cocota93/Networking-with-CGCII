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
//-----------------------------------------------------------------
// AdminClient Info (Server의 정보)
//-----------------------------------------------------------------
#pragma pack(1)


//-----------------------------------------------------------------
// Server System Info
//-----------------------------------------------------------------
enum ECGSERVER_SYSTEM_TYPE
{
	ECGSERVER_SYSTEM_TYPE_UNKNOWN				 = 0,
	ECGSERVER_SYSTEM_TYPE_ADMINSERVER			 = 1,
	ECGSERVER_SYSTEM_TYPE_ADMINCLIENT			 = 2,
	ECGSERVER_SYSTEM_TYPE_HOSTAGENT				 = 3,
	ECGSERVER_SYSTEM_TYPE_WEBSERVER				 = 4,
	ECGSERVER_SYSTEM_TYPE_SERVER				 = 5,
	ECGSERVER_SYSTEM_TYPE_RDBMS					 = 6,
	ECGSERVER_SYSTEM_TYPE_NOSQL					 = 7,
};


namespace CGServerAdmin
{

//-----------------------------------------------------------------------------
//
// Fundamental 
//
//-----------------------------------------------------------------------------
const _CHAR* GetString_ServerType(ECGSERVER_SYSTEM_TYPE _eType);


//-----------------------------------------------------------------------------
/**

@class		ID
@brief		ID의 내용
@todo
@ref		SETTING_INFO, HOST_SETTING, SERVER_SETTING
@details	\n

*/
//-----------------------------------------------------------------------------
struct ID
{
public:
	// 1) Identifier (등록 ID-등록될 때 할당되는 ID로 영구적임, -1:비등록, >=0:등록)
			int64_t				i64ID;

	// 2) Code (객체 ID-객체화될 때 할당되는 ID로 매번 변경됨, -1:비객체화, >=0:객체화)
			int64_t				i64Code;

	// 3) Type
			ECGSERVER_SYSTEM_TYPE	eType;

public:
			bool operator!=(_In_ const ID& _rhs) const							{ return i64Code != _rhs.i64Code; }
			bool operator==(_In_ const ID& _rhs) const							{ return i64Code == _rhs.i64Code; }
			bool operator< (_In_ const ID& _rhs) const							{ return i64Code <  _rhs.i64Code; }
			bool operator<=(_In_ const ID& _rhs) const							{ return i64Code <= _rhs.i64Code; }
			bool operator> (_In_ const ID& _rhs) const							{ return i64Code >  _rhs.i64Code; }
			bool operator>=(_In_ const ID& _rhs) const							{ return i64Code >= _rhs.i64Code; }

			bool				IsRegistered() const							{ return i64ID >= 0;}
			bool				IsUnregistered() const							{ return i64ID < 0;}

			bool				IsAllocated() const								{ return i64Code >= 0;}
			bool				IsUnallocated() const							{ return i64Code < 0;}

public:
			ID(_In_ int64_t _i64ID, _In_ int64_t _i64Code=-1, _In_ ECGSERVER_SYSTEM_TYPE _eType=ECGSERVER_SYSTEM_TYPE_UNKNOWN) : i64ID(_i64ID), i64Code(_i64Code), eType(_eType) {}
			ID() : i64ID(-1), i64Code(-1), eType(ECGSERVER_SYSTEM_TYPE_UNKNOWN)	{}
};



//-----------------------------------------------------------------------------
/**

@class		SETTING_INFO
@brief		설정 정보의 기본 내용
@todo
@ref		HOST_SETTING, SERVER_SETTING, SERVICE_SETTING
@details	\n

*/
//-----------------------------------------------------------------------------
struct SETTING_INFO
{
public:
	// 1) System ID
			ID					id;

	// 2) Name
			_CHAR				strName[MAX_NAME_LENGTH];

	// 3) Explanation
			_CHAR				strComment[MAX_NAME_LENGTH];

public:
	// Operator) 
			bool				operator!=(_In_ const SETTING_INFO& _rhs) const	{ return id!=_rhs.id;}
			bool				operator==(_In_ const SETTING_INFO& _rhs) const	{ return id==_rhs.id;}
			bool				operator< (_In_ const SETTING_INFO& _rhs) const	{ return id< _rhs.id;}
			bool				operator<=(_In_ const SETTING_INFO& _rhs) const	{ return id<=_rhs.id;}
			bool				operator> (_In_ const SETTING_INFO& _rhs) const	{ return id> _rhs.id;}
			bool				operator>=(_In_ const SETTING_INFO& _rhs) const	{ return id>=_rhs.id;}

			bool				operator!=(_In_ const ID& _rhs) const			{ return id != _rhs; }
			bool				operator==(_In_ const ID& _rhs) const			{ return id == _rhs; }
			bool				operator< (_In_ const ID& _rhs) const			{ return id< _rhs; }
			bool				operator<=(_In_ const ID& _rhs) const			{ return id <= _rhs; }
			bool				operator> (_In_ const ID& _rhs) const			{ return id> _rhs; }
			bool				operator>=(_In_ const ID& _rhs) const			{ return id >= _rhs; }

public:
			SETTING_INFO()														{ strName[0]=NULL; strComment[0]=NULL;}
			SETTING_INFO(_In_ const ID& _id) : id(_id)							{ strName[0]=NULL; strComment[0]=NULL;}
};


//-----------------------------------------------------------------------------
//
// Host Info
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**

@class		HOST_SETTING
@brief		HOST의 설정 내용
@todo
@ref		SETTING_INFO, SERVER_SETTING, SERVICE_SETTING
@details	\n

*/
//-----------------------------------------------------------------------------
struct HOST_SETTING : public SETTING_INFO
{
public:

public:
	// Operator) 
			bool				operator!=(const HOST_SETTING& _rhs) const		{ return id != _rhs.id; }
			bool				operator==(const HOST_SETTING& _rhs) const		{ return id == _rhs.id; }
			bool				operator< (const HOST_SETTING& _rhs) const		{ return id< _rhs.id; }
			bool				operator<=(const HOST_SETTING& _rhs) const		{ return id <= _rhs.id; }
			bool				operator> (const HOST_SETTING& _rhs) const		{ return id> _rhs.id; }
			bool				operator>=(const HOST_SETTING& _rhs) const		{ return id >= _rhs.id; }

			bool				operator!=(const ID& _rhs) const				{ return id != _rhs; }
			bool				operator==(const ID& _rhs) const				{ return id == _rhs; }
			bool				operator< (const ID& _rhs) const				{ return id< _rhs; }
			bool				operator<=(const ID& _rhs) const				{ return id <= _rhs; }
			bool				operator> (const ID& _rhs) const				{ return id> _rhs; }
			bool				operator>=(const ID& _rhs) const				{ return id >= _rhs; }

public:
			HOST_SETTING() : SETTING_INFO()									{}
			HOST_SETTING(_In_ const ID& _id) : SETTING_INFO(_id)			{}
};


// Host Info
struct HOST_INFO
{
public:
	// 1) Host ID
			ID					id;

	// 2) System/System Info
			SYSTEM_INFO			infoSystem;
			OSVERSIONINFOEXW	infoOS;

	// 3) Host Address
			SOCKADDR_CGNETWORK	addrHost;
			_CHAR				strHostName[MAX_NAME_LENGTH];

	// 4) 시작한 시간(Start Time)
			TIME::SYSTEM::time_point timeStart;

public:
	// Operator) 
			bool				operator!=(_In_ const HOST_INFO& _rhs) const	{ return id != _rhs.id; }
			bool				operator==(_In_ const HOST_INFO& _rhs) const	{ return id == _rhs.id; }
			bool				operator< (_In_ const HOST_INFO& _rhs) const	{ return id< _rhs.id; }
			bool				operator<=(_In_ const HOST_INFO& _rhs) const	{ return id <= _rhs.id; }
			bool				operator> (_In_ const HOST_INFO& _rhs) const	{ return id> _rhs.id; }
			bool				operator>=(_In_ const HOST_INFO& _rhs) const	{ return id >= _rhs.id; }

			bool				operator!=(_In_ const ID& _rhs) const			{ return id != _rhs; }
			bool				operator==(_In_ const ID& _rhs) const			{ return id == _rhs; }
			bool				operator< (_In_ const ID& _rhs) const			{ return id< _rhs; }
			bool				operator<=(_In_ const ID& _rhs) const			{ return id <= _rhs; }
			bool				operator> (_In_ const ID& _rhs) const			{ return id> _rhs; }
			bool				operator>=(_In_ const ID& _rhs) const			{ return id >= _rhs; }

public:
			HOST_INFO()														{ strHostName[0]=NULL;}
			HOST_INFO(_In_ const ID& _id) : id(_id)							{ strHostName[0]=NULL;}
};


// Host Status - 지속적으로 Host에서 전송되어오는 정보.
struct HOST_STATUS
{
public:
			ID					id;							// - Host ID

			int					usageProcessor;				// - CPU의 사용률
			PERFORMANCE_INFORMATION	statusMemory;		// - Memory Status
			int					usageNetwork;				// - Network Traffic

};


//-----------------------------------------------------------------------------
//
// Server Info
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**

@class		SERVER_SETTING
@brief		SERVER의 설정 내용
@todo
@ref		SETTING_INFO, HOST_SETTING, SERVICE_SETTING
@details	\n

*/
//-----------------------------------------------------------------------------
struct SERVER_SETTING : public SETTING_INFO
{
public:
	// 1) Execute File/Directory
			_CHAR				fileExecute[260];			// - Execute File
			_CHAR				strPath[260];				// - Fileset
			_CHAR				strPathWorking[260];		// - Working Directory

	// 2) SVN 
			_CHAR				strURL[512];				// - SVN URL
			int					iRevision;					// - SVN Version

	// 35) Register 여부
			ID					idHost;
			BOOL				bRegisterted;

public:
			SERVER_SETTING(_In_ const ID& _ID) : SETTING_INFO(_ID), iRevision(-1), bRegisterted(FALSE) { fileExecute[0] = NULL; strPath[0] = NULL; strPathWorking[0] = NULL; strURL[0] = NULL; }
			SERVER_SETTING() : SETTING_INFO(), iRevision(-1), bRegisterted(FALSE)	{ fileExecute[0] = NULL; strPath[0] = NULL; strPathWorking[0] = NULL; strURL[0] = NULL; }

			bool				Load(_In_z_ const _CHAR* p_strPath=_CGTEXT("."));
			bool				Load(_In_z_ const _CHAR_SUB* p_strPath);
			bool				Save();
};

struct SERVER_INFO
{
public:
	 // 1) System ID
			 ID					id;

	 // 2) Version
			 uint32_t			dwVersionHigh;				// - Version High
			 uint32_t			dwVersionLow;				// - Version Low

	// 3) Status
			 eOBJECT_STATE		iState;						// - Server의 현재 상태
	   
	// 4) Time
			 TIME::SYSTEM::time_point timeCreated;			// - 생성된 시간.

public:
	SERVER_INFO() : dwVersionHigh(0), dwVersionLow(0), iState(eOBJECT_STATE::NONE) {}
};


//-----------------------------------------------------------------------------
//
// Service Info
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**

@class		SERVICE_SETTING
@brief		SERVICE의 설정 내용
@todo
@ref		SETTING_INFO, HOST_SETTING, SERVER_SETTING
@details	\n

*/
//-----------------------------------------------------------------------------
struct SERVICE_SETTING : public SETTING_INFO
{
public:
	// 1) Type
	uint32_t				dwService;						// - Service 종류
	int						iGroup;							// - 속해 있는 Group
	int						iSerial;						// - Service의 Serial

	// 2) Version
	uint32_t				dwVersionHigh;					// - Version High
	uint32_t				dwVersionLow;					// - Version Low

	// 3) Access Type
	uint32_t				dwAthorityAttribute;			// - Athority Attribute

	// 4) Time
	TIME::SYSTEM::time_point timeCreated;					// - 생성된 시간.

	// 5) Status
	eOBJECT_STATE		iState;

public:
	// Operator) 
			bool			operator!=(_In_ const SERVICE_SETTING& _rhs) const	{ return id != _rhs.id; }
			bool			operator==(_In_ const SERVICE_SETTING& _rhs) const	{ return id == _rhs.id; }
			bool			operator< (_In_ const SERVICE_SETTING& _rhs) const	{ return id< _rhs.id; }
			bool			operator<=(_In_ const SERVICE_SETTING& _rhs) const	{ return id <= _rhs.id; }
			bool			operator> (_In_ const SERVICE_SETTING& _rhs) const	{ return id> _rhs.id; }
			bool			operator>=(_In_ const SERVICE_SETTING& _rhs) const	{ return id >= _rhs.id; }


			bool			operator!=(_In_ const ID& _rhs) const				{ return id != _rhs; }
			bool			operator==(_In_ const ID& _rhs) const				{ return id == _rhs; }
			bool			operator< (_In_ const ID& _rhs) const				{ return id< _rhs; }
			bool			operator<=(_In_ const ID& _rhs) const				{ return id <= _rhs; }
			bool			operator> (_In_ const ID& _rhs) const				{ return id> _rhs; }
			bool			operator>=(_In_ const ID& _rhs) const				{ return id >= _rhs; }

public:
			SERVICE_SETTING() : SETTING_INFO()									{}
			SERVICE_SETTING(_In_ const ID& _id) : SETTING_INFO(_id)				{}
};

struct STATUS
{
public:
			ID				id;								// - Service의 고유번호
			eOBJECT_STATE iState;						// - 현재 Service의 상태

public:
			STATUS() {}
			STATUS(eOBJECT_STATE _iState) : iState(_iState) {}
			STATUS(const ID& _id, eOBJECT_STATE _iState) : id(_id), iState(_iState) {}
};


//-----------------------------------------------------------------
// Connective
//-----------------------------------------------------------------
// 1) Connective Info
struct CONNECTIVE_INFO
{
	// - Name
			_CHAR			strName[64];					// - Acceptor

	// - Serial ID
			uint32_t		iSerialID;						// Acceptor의 SerialID(고유번호)

	// - Time
			TIME::SYSTEM::time_point timeCreate;				// 생성된 시간.

	// - Bind Address
			SOCKADDR_CGNETWORK	addressSocket;					// Accept된 Address.

};

// 2) Connective Status
struct CONNECTIVE_STATUS
{
	// - Serial ID
			uint32_t		iSerialID;						// Acceptor의 SerialID(고유번호)

	// - Time
			TIME::SYSTEM::time_point timeStart;				// Accept Start 시간.
			TIME::SYSTEM::time_point timeClose;				// 닫은 시간.

	// - 상태정보
			int				bEnable;						// Enable

	// - Connective Info
			CGNet::IO::Statistics::CONNECTIVE statisticsConnective;

};


//-----------------------------------------------------------------
// Binder
//-----------------------------------------------------------------
// 1) Binder Info
struct SOCKET_INFO
{
public:
	// - Name
	_CHAR				strName[64];						// - Acceptor

	// - Socket의 Handle(고유번호)
	CGSOCKET			iSocketHandle;

	// - Bind/Connect Address
	SOCKADDR_CGNETWORK	addressSocket;
	SOCKADDR_CGNETWORK	addressPeer;

	// - Time
	TIME::SYSTEM::time_point timeCreate;					// 생성된 시간.

};

// 2) Binder Status
struct SOCKET_STATUS
{
public:
	// - Socket의 Handle(고유번호)
	CGSOCKET			iSocketHandle;

	// - Socket State
	eSOCKET_STATE		eSocketState;

	// - Connect/Close time
	TIME::SYSTEM::time_point timeConnect;
	TIME::SYSTEM::time_point timeClose;

	int					dummy;

	// - I/O Status
	CGNet::IO::Statistics::TRAFFIC	statisticsTraffic;
};




//-----------------------------------------------------------------
// Memory Block Pool Info
//-----------------------------------------------------------------
typedef struct CGNETSTATISTICS_MBPOOL_INFO
{

} *LPCGNETSTATISTICS_MBPOOL_INFO, &RPCGNETSTATISTICS_MBPOOL_INFO;


//-----------------------------------------------------------------
// Object Pool Info
//-----------------------------------------------------------------
// 4) 
typedef struct _SCGNetPoolInfo
{
public:
	int			Type;


} CGNETSTATISTICS_POOL_INFO, *LPCGNETSTATISTICS_POOL_INFO, &RPCGNETSTATISTICS_POOL_INFO;



// CGMESSAGE::ADMIN::SERVER_SETTING_REGISTER
CCGBuffer GetMessage_RequestRegisterServerSettingInfo	(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer, const CGServerAdmin::SERVER_SETTING& _ServerRegisterInfo, const CCGBuffer& _bufParameters, bool _bUpdate = false);
// CGMESSAGE::ADMIN::SERVER_SETTING_UNREGISTER
CCGBuffer GetMessage_RequestUnregisterServerSettingInfo	(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);
// CGMESSAGE::ADMIN::SERVER_SETTING_UPDATE
CCGBuffer GetMessage_RequestUpdateServerSettingInfo		(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer, const CGServerAdmin::SERVER_SETTING& _ServerRegisterInfo, const CCGBuffer& _bufParameters, bool _bUpdate=false);
// CGMESSAGE::ADMIN::REQUEST_VERSION_UPDATE
CCGBuffer GetMessage_RequestVersionUpdate				(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);

// CGMESSAGE::ADMIN::REQUEST_INIT_SERVICE
CCGBuffer GetMessage_RequestInitService					(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);
// CGMESSAGE::ADMIN::REQUEST_DESTROY_SERVICE
CCGBuffer GetMessage_RequestDestroyService				(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);
// CGMESSAGE::ADMIN::REQUEST_KILL_SERVICE
CCGBuffer GetMessage_RequestKillService					(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);

// CGMESSAGE::ADMIN::REQUEST_START_SERVICE
CCGBuffer GetMessage_RequestStartService				(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);
// CGMESSAGE::ADMIN::REQUEST_STOP_SERVICE
CCGBuffer GetMessage_RequestStopService					(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);
// CGMESSAGE::ADMIN::REQUEST_PAUSE_SERVICE
CCGBuffer GetMessage_RequestPauseService				(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);
// CGMESSAGE::ADMIN::REQUEST_CONTINUE_SERVICE
CCGBuffer GetMessage_RequestContinueService				(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);

// CGMESSAGE::ADMIN::SERVICE_STATE_UPDATE
CCGBuffer GetMessage_AdminServiceStateUpdate			(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer, eOBJECT_STATE _eStatus);

// CGMESSAGE::ADMIN::SERVER_ENTER
CCGBuffer GetMessage_EnterServer						(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer, const CGServerAdmin::SERVER_INFO& _ServerInfo);
// CGMESSAGE::ADMIN::SERVER_LEAVE
CCGBuffer GetMessage_LeaveServer						(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer);
// CGMESSAGE::ADMIN::SERVER_UPDATE
CCGBuffer GetMessage_UpdateServer						(const CGServerAdmin::ID& _idHost, const CGServerAdmin::ID& _idServer, const CGServerAdmin::SERVER_INFO& _ServerInfo);

// CGMESSAGE::ADMIN::SEND_CONTROL_INFO
CCGBuffer GetMessage_SendControlInfo();
// CGMESSAGE::ADMIN::HOST_STATUS_UPDATE
CCGBuffer GetMessage_AdminHostStatusUpdate				(const CGServerAdmin::HOST_STATUS& _HostStatus);

// CGMESSAGE::ADMIN::SEND_HOST_INFO
CCGBuffer GetMessage_AdminSendHostInfo					(const CGServerAdmin::HOST_INFO& _HostInfo);
// CGMESSAGE::ADMIN::SEND_HOST_SETTING,
CCGBuffer GetMessage_AdminSendHostSetting				(const CGServerAdmin::HOST_SETTING& _HostSetting);
// CGMESSAGE::ADMIN::SEND_ADMINSERVER_ADDRESS,
CCGBuffer GetMessage_AdminSendAdminServerAddress		(const wchar_t* _strAddress);


}

#pragma pack()


#define	CGNET_INI_FILE_NAMETEXT	"CGNetHostAgentInfo.ini"
