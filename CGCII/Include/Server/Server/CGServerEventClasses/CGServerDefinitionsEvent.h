//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Event Classes                            *
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
//
//
//  Definitions for Event Classes
//
//
//----------------------------------------------------------------------------
enum class eEVENT_SETTER : int32_t
{
	SYSTEM		 = 0,
	LOCAL		 = 1,	
	ADMIN		 = 2,
	MAX
};

enum class eEVENT_STATE : int32_t
{
	WAIT		 = 0,
	RUN			 = 1,
	DONE		 = 2,
	MAX
};

enum class eEVENT_TYPE : int32_t
{
	ONCE		 = 0,	// 0
	ITERATION,			// 1
	START_END,			// 2
	START_ITERATION_END,// 3
	SCHEDULE,			// 4
	SCHEDULE_FUNCTION,	// 5
	CUSTOM,				// 6
	MAX
};

struct EVENT_INFO
{
public:
	int64_t				idEvent;

	_CHAR				strName[MAX_NAME_LENGTH];	

	bool				flgEnable;
	eEVENT_TYPE			EventType;
	ATOMIC<eEVENT_STATE> EventState;
	eEVENT_SETTER		EventSetter;
	int					EventLevel;

	TIME::SYSTEM::time_point	timeSetup;
	TIME::SYSTEM::time_point	timeLastTry;
	TIME::SYSTEM::time_point	timeLastSucceeded;
	TIME::SYSTEM::time_point	timeLastFailed;
	TIME::SYSTEM::time_point	timeNext;

	ATOMIC<int64_t>		nExecute_Try;
	ATOMIC<int64_t>		nExecute_Succeeded;
	ATOMIC<int64_t>		nExecute_Failed;

public:
	EVENT_INFO() : 
		idEvent(-1),
		flgEnable(true),
		EventState(eEVENT_STATE::WAIT),
		EventSetter(eEVENT_SETTER::LOCAL),
		EventLevel(0),
		timeSetup(0),
		timeLastTry(0),
		timeLastSucceeded(0),
		timeLastFailed(0),
		timeNext(0),
		nExecute_Try(0),
		nExecute_Succeeded(0),
		nExecute_Failed(0)
	{
		strName[0]	 = 0;
	}

	EVENT_INFO(eEVENT_TYPE _EventType) : 
		idEvent(-1),
		flgEnable(true),
		EventType(_EventType),
		EventState(eEVENT_STATE::WAIT),
		EventSetter(eEVENT_SETTER::LOCAL),
		EventLevel(0),
		timeSetup(0),
		timeLastTry(0),
		timeLastSucceeded(0),
		timeLastFailed(0),
		timeNext(0),
		nExecute_Try(0),
		nExecute_Succeeded(0),
		nExecute_Failed(0)
	{
		strName[0]	 = 0;
	}

	EVENT_INFO(const EVENT_INFO& Value)				{	memcpy(this, &Value, sizeof(EVENT_INFO));}
	EVENT_INFO&	operator=(const EVENT_INFO& rhs)	{	memcpy(this, &rhs, sizeof(EVENT_INFO)); return *this;}

};

//struct EVENT_RESULT : virtual public ICGReferenceable
//{
//public:
//	EVENT_RESULT() : eResult(eOBJECT_RESULT::NOT_DEFINED)	{}
//
//	void		reset()
//	{
//		eResult	 = eOBJECT_RESULT::NOT_DEFINED;
//		stdMessage.clear();
//		message.clear();
//	}
//
//	void		append_result_string()
//	{
//		// 2) 이름을 설정한다.
//		stdMessage.append(_CGTEXT(" ["));
//		stdMessage.append(GetString_ObjectResult(eResult));
//		stdMessage.append(_CGTEXT("]"));
//	}
//
//	struct MESSAGE
//	{
//	public:
//		MESSAGE() {}
//		MESSAGE(const _STRING& _string, _In_ eLOG_TYPE _eType, _In_ int _iLevel) : message(_string), eType(_eType), iLevel(_iLevel)	{}
//
//	public:
//		_STRING	message;
//		eLOG_TYPE	eType;
//		int			iLevel;
//	};
//
//public:
//		eOBJECT_RESULT				eResult;
//		TIME::SYSTEM::time_point	time;
//		_STRING					stdMessage;
//		list<MESSAGE>				message;
//};


#define EVENT_TIMES_INFINITE	(-1)

typedef eOBJECT_RESULT (*EVENT_FUNCTION)(const TIME::SYSTEM::time_point&);

#if _MSC_VER>=_MSC_VER_2008
typedef std::function<eOBJECT_RESULT(const TIME::SYSTEM::time_point&)>		EVENT_LAMBDA;
#endif

// 2) Server (CGOBJECTTYPE_NETWORK==0x210000)
#define		CGOBJECTTYPE_SERVER_EVENT						 (0x210000 | 0x0100)
