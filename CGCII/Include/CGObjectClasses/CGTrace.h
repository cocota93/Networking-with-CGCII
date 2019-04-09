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
// ----------------------------------------------------------------------------
//
// Trace
//
// ----------------------------------------------------------------------------
#define	_ENABLE_CGLOG_SYSTEM
#define	_ENABLE_CGLOG_EXCEPTION
#define	_ENABLE_CGLOG_ERROR
#define	_ENABLE_CGLOG_USER

#ifdef _DEBUG
	#define	_ENABLE_CGLOG_DEBUG
#endif
#define	_ENABLE_CGLOG_INFO
//#define _ENABLE_CGLOG_INFO_LOW
#define	_ENABLE_CGLOG_PROGRESS

#define	MAX_TRACE_STRING_LENGTH	2048


enum class eLOG_TYPE : uint32_t
{
	INFO_		 = 0,
	PROGRESS_	 = 1,
	DEBUG_		 = 2,
	EXCEPTION_	 = 3,
	ERROR_		 = 4,
	USER_		 = 5,
	SYSTEM_		 = 6,
	MAX,
	CONTINUE_	 = 0x80000000,
	UNDEFINED_	 = 0xffff,
};

inline eLOG_TYPE operator & (eLOG_TYPE _lhs, eLOG_TYPE _rhs)	{	return	static_cast<eLOG_TYPE>(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs));}
inline eLOG_TYPE operator | (eLOG_TYPE _lhs, eLOG_TYPE _rhs)	{	return	static_cast<eLOG_TYPE>(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs));}
inline eLOG_TYPE operator & (eLOG_TYPE _lhs, uint32_t _rhs)		{	return	static_cast<eLOG_TYPE>(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs));}
inline eLOG_TYPE operator | (eLOG_TYPE _lhs, uint32_t _rhs)		{	return	static_cast<eLOG_TYPE>(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs));}

class eLOG_LEVEL
{
private:
	eLOG_LEVEL()	{}
	~eLOG_LEVEL()	{}

public:
	enum : int
	{
	LOWEST		 = INT_MIN,
	LOWER		 = -256,
	NORMAL		 = 0,
	HIGHER		 = 256,
	HIGHEST		 = INT_MAX,
	};
};


class CGLOG_RECORD : virtual public ICGReferenceable
{
public:
	CGLOG_RECORD() : eType(eLOG_TYPE::UNDEFINED_), iLevel(eLOG_LEVEL::NORMAL), eResult(eOBJECT_RESULT::SUCCESS), strMessage(), Attribute(0), timeOccure()	{}
	CGLOG_RECORD(eLOG_TYPE _eType, int _iLevel, const _CHAR* _strMessage, uint64_t _Attribute, const TIME::SYSTEM::time_point& _timeOccure) : eType(_eType), iLevel(_iLevel), eResult(eOBJECT_RESULT::SUCCESS), strMessage(_strMessage), Attribute(_Attribute), timeOccure(_timeOccure)	{}

public:
	void						clear()		{ strMessage.clear(); SubLog.clear();}

public:
	eLOG_TYPE					eType;
	int							iLevel;
	eOBJECT_RESULT				eResult;
	_STRING						strMessage;
	uint64_t					Attribute;

	TIME::SYSTEM::time_point	timeOccure;

	circular_list<CGPTR<CGLOG_RECORD>>	SubLog;
};

// 1) Log
#define	CGLOG(dis, type, level, ...)				NO_EXCEPTION_BEGIN { CGLog(dis, type, level, __VA_ARGS__); } NO_EXCEPTION_END

// 2) Information Log
#ifdef _ENABLE_CGLOG_SYSTEM
	#define	CGLOG_SYSTEM(dis, ...)					CGLOG(dis, eLOG_TYPE::SYSTEM_,	 eLOG_LEVEL::NORMAL, __VA_ARGS__)
	#define	CGLOG_SYSTEM_CONTINUE(dis, ...)			CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
#else
	#define	CGLOG_SYSTEM(dis, ...)
	#define	CGLOG_SYSTEM_CONTINUE(dis, ...)
#endif
#define	CGLOG_SYSTEM_IMPORTANT(dis, ...)			CGLOG(dis, eLOG_TYPE::SYSTEM_,	 eLOG_LEVEL::HIGHER, __VA_ARGS__)
#define	CGLOG_SYSTEM_IMPORTANT_CONTINUE(dis, ...)	CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::HIGHER, __VA_ARGS__)

// 3) Information Log
#ifdef _ENABLE_CGLOG_INFO
	#define	CGLOG_INFO(dis, ...)					CGLOG(dis, eLOG_TYPE::INFO_,	 eLOG_LEVEL::NORMAL, __VA_ARGS__)
	#define	CGLOG_INFO_CONTINUE(dis, ...)			CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
#else
	#define	CGLOG_INFO(dis, ...)
	#define	CGLOG_INFO_CONTINUE(dis, ...)
#endif
#define	CGLOG_INFO_IMPORTANT(dis, ...)				CGLOG(dis, eLOG_TYPE::INFO_,	 eLOG_LEVEL::HIGHER, __VA_ARGS__)
#define	CGLOG_INFO_IMPORTANT_CONTINUE(dis, ...)		CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::HIGHER, __VA_ARGS__)

#ifdef _ENABLE_CGLOG_INFO_LOW
	#define	CGLOG_INFO_LOW(dis, ...)				CGLOG(dis, eLOG_TYPE::INFO_,	 eLOG_LEVEL::LOWER, __VA_ARGS__)
	#define	CGLOG_INFO_LOW_CONTINUE(dis, ...)		CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::LOWER, __VA_ARGS__)
#else
	#define	CGLOG_INFO_LOW(dis, ...)					
	#define	CGLOG_INFO_LOW_CONTINUE(dis, ...)			
#endif


// 4) Progress Log
#ifdef _ENABLE_CGLOG_PROGRESS
	#define	CGLOG_PROGRESS(dis, ...)				CGLOG(dis, eLOG_TYPE::PROGRESS_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
	#define	CGLOG_PROGRESS_CONTINUE(dis, ...)		CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
#else
	#define	CGLOG_PROGRESS(dis, ...)
	#define	CGLOG_PROGRESS_CONTINUE(dis, ...)
#endif
#define	CGLOG_PROGRESS_IMPORTANT(dis, ...)			CGLOG(dis, eLOG_TYPE::PROGRESS_, eLOG_LEVEL::HIGHER, __VA_ARGS__)
#define	CGLOG_PROGRESS_IMPORTANT_CONTINUE(dis, ...)	CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::HIGHER, __VA_ARGS__)

// 5) Debug Log
#ifdef _ENABLE_CGLOG_DEBUG
	#define	CGLOG_DEBUG(dis, ...)					CGLOG(dis, eLOG_TYPE::DEBUG_,	 eLOG_LEVEL::NORMAL, __VA_ARGS__)
	#define	CGLOG_DEBUG_CONTINUE(dis, ...)			CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
#else
	#define	CGLOG_DEBUG(dis, ...)
	#define	CGLOG_DEBUG_CONTINUE(dis, ...)
#endif
#define	CGLOG_DEBUG_IMPORTANT(dis, ...)				CGLOG(dis, eLOG_TYPE::DEBUG_,	 eLOG_LEVEL::HIGHER, __VA_ARGS__)
#define	CGLOG_DEBUG_IMPORTANT_CONTINUE(dis, ...)	CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::HIGHER, __VA_ARGS__)

// 6) Exception Log
#ifdef _ENABLE_CGLOG_EXCEPTION
	#define	CGLOG_EXCEPTION(dis, ...)				CGLOG(dis, eLOG_TYPE::EXCEPTION_,eLOG_LEVEL::NORMAL, __VA_ARGS__)
	#define	CGLOG_EXCEPTION_CONTINUE(dis, ...)		CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
#else
	#define	CGLOG_EXCEPTION(dis, ...)
	#define	CGLOG_EXCEPTION_CONTINUE(dis, ...)
#endif
#define	CGLOG_EXCEPTION_IMPORTANT(dis, ...)			CGLOG(dis, eLOG_TYPE::EXCEPTION_,eLOG_LEVEL::HIGHER, __VA_ARGS__)
#define	CGLOG_EXCEPTION_IMPORTANT_CONTINUE(dis, ...)CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::HIGHER, __VA_ARGS__)

// 7) Error Log
#ifdef _ENABLE_CGLOG_ERROR
	#define	CGLOG_ERROR(dis, ...)					CGLOG(dis, eLOG_TYPE::ERROR_,	 eLOG_LEVEL::NORMAL, __VA_ARGS__)
	#define	CGLOG_ERROR_CONTINUE(dis, ...)			CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
#else
	#define	CGLOG_ERROR(dis, ...)					CGLOG(dis, eLOG_TYPE::ERROR_,	 eLOG_LEVEL::NORMAL, __VA_ARGS__)
	#define	CGLOG_ERROR_CONTINUE(dis, ...)			CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
#endif
#define	CGLOG_ERROR_IMPORTANT(dis, ...)				CGLOG(dis, eLOG_TYPE::ERROR_,	 eLOG_LEVEL::HIGHER, __VA_ARGS__)
#define	CGLOG_ERROR_IMPORTANT_CONTINUE(dis, ...)	CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::HIGHER, __VA_ARGS__)

// 8) User Log
#ifdef _ENABLE_CGLOG_USER
	#define	CGLOG_USER(dis, ...)					CGLOG(dis, eLOG_TYPE::USER_,     eLOG_LEVEL::NORMAL, __VA_ARGS__)
	#define	CGLOG_USER_CONTINUE(dis, ...)			CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::NORMAL, __VA_ARGS__)
#else
	#define	CGLOG_USER(dis, ...)
	#define	CGLOG_USER_CONTINUE(dis, ...)
#endif
#define	CGLOG_USER_IMPORTANT(dis, ...)				CGLOG(dis, eLOG_TYPE::USER_,     eLOG_LEVEL::HIGHER, __VA_ARGS__)
#define	CGLOG_USER_IMPORTANT_CONTINUE(dis, ...)		CGLOG(dis, eLOG_TYPE::CONTINUE_, eLOG_LEVEL::HIGHER, __VA_ARGS__)

// 9) 
#define	CGLOG_IF(condition, state)					if(condition)	{ state;}

// 10) Default Tracer
CGPTR<ICGMessageable> 	GetDefaultTracer();
void					SetDefaultTracer(ICGMessageable* _pMessageable);
void					ResetDefaultTracer(ICGMessageable* _pMessageable=nullptr);

#define	DEFAULT_LOGGER	GetDefaultTracer()



//-----------------------------------------------------------------------------
//
// 3. Trace
//
//-----------------------------------------------------------------------------
struct CGMSG_LOG : public CGMSG
{
public:
	CGMSG_LOG() : CGMSG(CGMESSAGE::SYSTEM::LOG)	{}
	CGMSG_LOG(CGLOG_RECORD* _pLogRecord) : CGMSG(CGMESSAGE::SYSTEM::LOG), pLogRecord(_pLogRecord) {}
	CGMSG_LOG(_In_ eLOG_TYPE _Type, _In_ int _iLevel, _In_z_ const _CHAR* _strMessage) : CGMSG(CGMESSAGE::SYSTEM::LOG)
	{
		// Declare) 
		CGPTR<CGLOG_RECORD>	ptempLogRecord;

		// 1) 생성한다.
		ptempLogRecord		 = _CGNEW<CGLOG_RECORD>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL);

		ptempLogRecord->eType		 = _Type;
		ptempLogRecord->iLevel		 = _iLevel;
		ptempLogRecord->strMessage	 = _strMessage;
		ptempLogRecord->timeOccure	 = TIME::SYSTEM::now();

		pLogRecord	 = ptempLogRecord;
	}

public:
			CGPTR<CGLOG_RECORD>	pLogRecord;
};

inline void _CGLog(_In_opt_ ICGMessageable* _pMessageable, _In_ CGLOG_RECORD* _plogRecord) NOEXCEPT
{
	try
	{
		// Check) _plogRecord shouldn't be nullptr
		CGASSERT_ERROR(_plogRecord!=nullptr);

		// Check) _Format shouldn't be nullptr
		RETURN_IF(_plogRecord==nullptr, );

		// 1) Output Trace Message
		CGOUTPUTDEBUGSTRING(_plogRecord->strMessage.c_str());
		CGOUTPUTDEBUGSTRING(_CGTEXT("\n"));

		// 2) Messageable을 얻는다.
		CGPTR<ICGMessageable>	pMessageable = (_pMessageable!=nullptr) ? _pMessageable : GetDefaultTracer();

		// 3) Messageable이 존재하면 Trace Dispatch
		if(pMessageable!=nullptr)
		{
			CGMSG_LOG	msgLog(_plogRecord);

			pMessageable->RequestProcessMessage(msgLog);
		}
	}
	catch (...)
	{
	}
}

inline void _CGLog(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _iLevel, _In_ int /*_lengthMessage*/, _In_z_ const _CHAR* _strMessage) NOEXCEPT
{
	try
	{
		// 1) Output Trace Message
		CGOUTPUTDEBUGSTRING(_strMessage);
		CGOUTPUTDEBUGSTRING(_CGTEXT("\n"));

		// 2) Messageable을 얻는다.
		CGPTR<ICGMessageable>	pMessageable = (_pMessageable!=nullptr) ? _pMessageable : GetDefaultTracer();

		// 3) Messageable이 존재하면 Trace Dispatch
		if(pMessageable!=nullptr)
		{
			CGMSG_LOG	msgLog(_Type, _iLevel, _strMessage);

			pMessageable->RequestProcessMessage(msgLog);
		}
	}
	catch (...)
	{
	}
}

inline void _CGLog_Static(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _iLevel, _In_z_ const _CHAR* _strMessage) NOEXCEPT
{
	try
	{
		// 1) Output Trace Message
		CGOUTPUTDEBUGSTRING(_strMessage);
		CGOUTPUTDEBUGSTRING(_CGTEXT("\n"));

		// 2) Messageable을 얻는다.
		CGPTR<ICGMessageable>	pMessageable = (_pMessageable!=nullptr) ? _pMessageable : GetDefaultTracer();

		// 3) Messageable이 존재하면 Trace Dispatch
		if(pMessageable!=nullptr)
		{
			CGPTR<CGLOG_RECORD>	pLogRecord	 = _CGNEW_RAW<CGLOG_RECORD>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL);
			pLogRecord->eType		 = _Type;
			pLogRecord->iLevel		 = _iLevel;
			pLogRecord->strMessage	 = _strMessage;
			pLogRecord->timeOccure	 = TIME::SYSTEM::now();

			CGMSG_LOG	msgLog(pLogRecord);

			pMessageable->RequestProcessMessage(msgLog);
		}
	}
	catch(...)
	{
	}
}

#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template <class TA, class... TARGS>
void _CGLog_Static(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _iLevel, _In_z_ const _CHAR* _Format, TA _A, TARGS... _Args) NOEXCEPT
{
	// Check) _Format shouldn't be nullptr
	CGASSERT_ERROR(_Format!=nullptr);

	// Declare) 
	_CHAR	strMessage[MAX_TRACE_STRING_LENGTH] {0};

	// 1) Generate Trace Message
	CGSNPRINTF_S(strMessage, _TRUNCATE, _Format, _A, _Args...);

	// 2) Trace를 건다.
	_CGLog_Static(_pMessageable, _Type, _iLevel, strMessage);
}
#else
#endif


#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
inline void CGLog(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _iLevel, _In_z_ const _CHAR* _strMessage) NOEXCEPT
{
	// Check) _Format shouldn't be nullptr
	CGASSERT_ERROR(_strMessage!=nullptr);

	_CGLog(_pMessageable, _Type, _iLevel, static_cast<int>(std::char_traits<_CHAR>::length(_strMessage)), _strMessage);
}

template <class TA, class... TARGS>
void CGLog(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _iLevel, _In_z_ const _CHAR* _Format, TA _A, TARGS... _Args) NOEXCEPT
{
	// Check) _Format shouldn't be nullptr
	CGASSERT_ERROR(_Format!=nullptr);

	// Declare) 
	_CHAR	strMessage[MAX_TRACE_STRING_LENGTH] {0};

	// 1) Generate Trace Message
	int	lengthMessage	 = CGSNPRINTF_S(strMessage, _TRUNCATE, _Format, _A, _Args...);

	// 2) Trace를 건다.
	_CGLog(_pMessageable, _Type, _iLevel, (lengthMessage!=-1) ? lengthMessage : (MAX_TRACE_STRING_LENGTH-1), strMessage);
}
#else
inline void CGLog(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _iLevel, _In_z_ const _CHAR* _Format, ...) NOEXCEPT
{
	// Check) _Format shouldn't be nullptr
	CGASSERT_ERROR(_Format!=nullptr);

	// Declare) 
	va_list	ap;

	// 1) valist 
	va_start(ap, _Format);

	// Declare) 
	_CHAR	strMessage[MAX_TRACE_STRING_LENGTH];

	// 2) Generate Trace Message
	int	lengthMessage	 = CGVSPRINTF_S(strMessage, MAX_TRACE_STRING_LENGTH, _TRUNCATE, _Format, ap);
	
	// 3) Trace를 건다.
	_CGLog(_pMessageable, _Type, _iLevel, (lengthMessage!=-1) ? lengthMessage : (MAX_TRACE_STRING_LENGTH-1), strMessage);

	// 3) Va_End
	va_end(ap);
}
#endif

