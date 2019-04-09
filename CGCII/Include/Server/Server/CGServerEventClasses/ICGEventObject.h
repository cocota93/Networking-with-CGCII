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
// ----------------------------------------------------------------------------
//
// ICGEventObject
//
// 1. ICGEventObject란?
//    1) EventObject 객체의 Interface Class이다.
//    2) ICGExecutalbe을 상속받은 클래스로 Executor에 물려 실행되도록 설계된다.
//
//
// ----------------------------------------------------------------------------
class ICGEventObject : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGNameable,							// (@) Nameable
	public						ICGExecutable							// (@) Executable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGEventObject() : ICGExecutable(1), m_infoEvent(), m_pResult(NEW<CGLOG_RECORD>()) {}
			ICGEventObject(_In_ eEVENT_TYPE _eType, const _CHAR* _strName=nullptr) : ICGExecutable(1), m_infoEvent(_eType), m_pResult(NEW<CGLOG_RECORD>()) { SetName(_strName);}
			ICGEventObject(_In_ eEVENT_TYPE _eType, const _CHAR_SUB* _wstrName) : ICGExecutable(1), m_infoEvent(_eType), m_pResult(NEW<CGLOG_RECORD>()) { SetName(_wstrName);}
	virtual ~ICGEventObject()											{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) CloseEvent하기
			void				CloseEvent()							{	ProcessCloseEvent();}

	// 2) Reset하기
			bool				ResetEvent(_In_ uint32_t _Flag=0)		{	return ProcessResetEvent(_Flag);}

	// 3) Event Flag
			bool				EnableEvent()							{	return ProcessEnableEvent();}
			bool				DisaableEvent()							{	return ProcessDisableEvent();}
			bool				IsEnable() const						{	return m_infoEvent.flgEnable;}
			bool				IsDisable() const						{	return !m_infoEvent.flgEnable;}

	// 4) Suspend/Resume
			bool				SuspendEvent()							{	return ProcessSuspendEvent();}
			bool				ResumeEvent()							{	return ProcessResumeEvent();}

	// 5) Event의 ID이다.
			__int64				GetEventID() const						{	return m_infoEvent.idEvent;}
			void				SetEventID(__int64 _idEvent)			{	m_infoEvent.idEvent=_idEvent;}

	// 6) Event의 Type이다.(Event의 Type이다.)
			eEVENT_TYPE			GetEventType() const					{	return m_infoEvent.EventType;}
			void				SetEventType(_In_ eEVENT_TYPE _eType)	{	m_infoEvent.EventType=_eType;}

	// 7) Event의 State이다.(Event의 Type이다.)
			eEVENT_STATE		GetEventState() const					{	return m_infoEvent.EventState;}
			void				SetEventState(_In_ eEVENT_STATE _State){	m_infoEvent.EventState=_State;}

	// 8) Event를 Setting한 곳.
	//    - Event를 설정한 곳으로 자체 Local에서 설정한 것일 수도 있고 
	//      Global에서 설정한 것일 수도 있다.
			eEVENT_SETTER		GetEventSetter() const					{	return m_infoEvent.EventSetter;}
			void				SetEventSetter(_In_ eEVENT_SETTER _Setter){ m_infoEvent.EventSetter=_Setter;}

	// 9) Event의 Level이다.
	//	  - Event의 Level이란 Event의 중요도이다.
			int					GetEventLevel() const					{	return m_infoEvent.EventLevel;}
			void				SetEventLevel(_In_ int _Level)			{	m_infoEvent.EventLevel=_Level;}

	// 10) Event Setup Time
	//    - Event를 설정한 시간을 의미한다.
	//    - 일반적으로 EventManager에 Attach 시킬 때에 시간이 설정된다.
			const TIME::SYSTEM::time_point&	GetSetupTime() const		{	return m_infoEvent.timeSetup;}
			void				SetSetupTime()							{	m_infoEvent.timeSetup=TIME::SYSTEM::now();}
			void				ResetSetupTime()						{	m_infoEvent.timeSetup=TIME::zero();}

			const TIME::SYSTEM::time_point&	GetLastTryTime() const		{	return m_infoEvent.timeLastTry;}
			void				ResetLastTryTime()						{	m_infoEvent.timeLastTry=TIME::zero();}

			const TIME::SYSTEM::time_point&	GetLastSucceededTime() const{	return m_infoEvent.timeLastSucceeded;}
			void				ResetLastSucceededTime()				{	m_infoEvent.timeLastSucceeded=TIME::zero();}

			const TIME::SYSTEM::time_point&	GetLastFailedTime() const	{	return m_infoEvent.timeLastFailed;}
			void				ResetLastFailedTime()					{	m_infoEvent.timeLastFailed=TIME::zero();}
			
			const TIME::SYSTEM::time_point&	GetNextTime() const			{	return m_infoEvent.timeNext; }

			int64_t				GetTryCount() const						{	return m_infoEvent.nExecute_Try;}
			int64_t				GetSucceededCount() const				{	return m_infoEvent.nExecute_Succeeded;}
			int64_t				GetFailedCount() const					{	return m_infoEvent.nExecute_Failed;}

	// 11) Event Info
			const EVENT_INFO&	GetEventInfo() const					{	return m_infoEvent;}
			void				SetEventInfo(_In_ const EVENT_INFO& _Info){ m_infoEvent =_Info;}

	// 12) Event Result
			const LOCKABLE<CGPTR<CGLOG_RECORD>>&	GetEventResult() const	{	return m_pResult;}

	// 12) Static Function
			bool				Register();
			bool				Unregister();


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Event 객체를 Reset했을 때 호출되는 함수.
	virtual	bool				ProcessResetEvent(_In_ uint32_t /*_Flag*/){	m_pResult->clear(); return true;}

	// 2) Event 객체를 Enable/Disable 했을 때 호출되는 함수
	virtual	bool				ProcessEnableEvent()					{	m_infoEvent.flgEnable = true; return true;}
	virtual	bool				ProcessDisableEvent()					{	m_infoEvent.flgEnable = false; return true;}

	// 3) Event 객체를 등록했을때/등록해제했을 때 호출되는 함수
	virtual	bool				ProcessCheckRegisterEvent()				{ return	true; }
	virtual	void				ProcessRegisterEvent()					{}
	virtual	void				ProcessUnregisterEvent()				{}

	// 4) Event 객체를 잠시 중시 했을 때/다시 시작했을 때 호출되는 함수
	virtual	bool				ProcessSuspendEvent()					{	eEVENT_STATE temp=eEVENT_STATE::RUN; m_infoEvent.EventState.compare_exchange_weak(temp, eEVENT_STATE::WAIT); return true;}
	virtual	bool				ProcessResumeEvent()					{	eEVENT_STATE temp=eEVENT_STATE::WAIT; m_infoEvent.EventState.compare_exchange_weak(temp, eEVENT_STATE::RUN); return true;}

	// 5) Event 객체를 닫는다.
	virtual	void				ProcessCloseEvent() PURE;

	// 6) Name
	virtual	bool				ProcessIsThis(_In_z_ const _CHAR* _strName) const {	return CGSTRCMP(_strName, m_infoEvent.strName)==0;}
	virtual	const _CHAR*		ProcessGetName() const					{ return m_infoEvent.strName; }
	virtual	void				ProcessSetName(_In_z_ const _CHAR* _strName){ RETURN_IF(_strName==nullptr, ); CGSTRCPY_S(m_infoEvent.strName, MAX_NAME_LENGTH, _strName); }

#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			void				CGLOG_EVENT(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _Level, _In_z_ const _CHAR* _strMessage);
			template <class... TARGS>
			void				CGLOG_EVENT(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _Level, _In_z_ const _CHAR* _Format, TARGS... _Args);
#else
			void				CGLOG_EVENT(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _Level, _In_z_ const _CHAR* _Format, ...);
#endif


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Event Info
			EVENT_INFO			m_infoEvent;
			LOCKABLE<CGPTR<CGLOG_RECORD>>	m_pResult;

	// 2) Manager
			friend	class CGEvent::Manager;

	// 3) Next Time설정
			void				_SetNextEventTime(const TIME::SYSTEM::time_point& _time) { m_infoEvent.timeNext = _time; }
			void				_ResetNextEventTime()					{	m_infoEvent.timeLastFailed.set_year(0); }
			CGPTR<CGLOG_RECORD>	_AppendResult(const _CHAR* _strState);
			void				_AppendResult_Post(CGLOG_RECORD* _pLogResult);

	// 4) Statistics
			void				Statistics_EventTry()					{	++m_infoEvent.nExecute_Try; m_infoEvent.timeLastTry=TIME::SYSTEM::now();}
			void				Statistics_EventSucceeded()				{	++m_infoEvent.nExecute_Succeeded; m_infoEvent.timeLastSucceeded=TIME::SYSTEM::now();}
			void				Statistics_EventFailed()				{	++m_infoEvent.nExecute_Failed; m_infoEvent.timeLastFailed=TIME::SYSTEM::now();}
};

#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
inline void ICGEventObject::CGLOG_EVENT(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _Level, _In_z_ const _CHAR* _strMessage)
{
	// Check) _Format shouldn't be nullptr
	CGASSERT_ERROR(_strMessage != nullptr);

	//  Declare) 
	CGPTR<CGLOG_RECORD>	plogSub;

	LOCK(m_pResult)
	{
		// Check) m_pResult가 nullptr면 안됀다.
		RETURN_IF(m_pResult.empty(), );

		// Check) m_pResult의 SubLog가 Empty면 안됀다.
		RETURN_IF(m_pResult->SubLog.empty(), );

		// 1) 제일 마지막의 SubEvent객체를 얻어 온다.
		auto	presultEvent	 = m_pResult->SubLog.back();

		// 2) Log객체를 생성한다.
		plogSub					 = NEW<CGLOG_RECORD>();
		plogSub->eType			 = _Type;
		plogSub->iLevel			 = _Level;
		plogSub->strMessage		 = _strMessage;
		plogSub->timeOccure		 = presultEvent->timeOccure;

		// 3) 제일 마지막의 SubEvent객체에 추가한다.
		presultEvent->SubLog.push_back(plogSub);
	}

	// Log)
	_CGLog(_pMessageable, plogSub);
}
template <class... TARGS>
void ICGEventObject::CGLOG_EVENT(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _Level, _In_z_ const _CHAR* _Format, TARGS... _Args)
{
	// Check) _Format shouldn't be nullptr
	CGASSERT_ERROR(_Format != nullptr);

	// Declare) 
	CGPTR<CGLOG_RECORD>	plogSub;

	LOCK(m_pResult)
	{
		// Check) m_pResult가 nullptr면 안됀다.
		RETURN_IF(m_pResult.empty(), );

		// Check) m_pResult의 SubLog가 Empty면 안됀다.
		RETURN_IF(m_pResult->SubLog.empty(), );

		// 1) 제일 마지막의 SubEvent객체를 얻어 온다.
		auto	presultEvent	 = m_pResult->SubLog.back();

		// Declare) 
		_CHAR	strMessage[MAX_TRACE_STRING_LENGTH] = { 0 };
		int		lengthMessage;

		// 2) 이벤트 메시지를 생성한다.
		lengthMessage = CGSNPRINTF_S(strMessage, _TRUNCATE, _Format, _Args...);

		// 3) Log객체를 생성한다.
		plogSub					 = NEW<CGLOG_RECORD>();
		plogSub->eType			 = _Type;
		plogSub->iLevel			 = _Level;
		plogSub->strMessage		 = strMessage;
		plogSub->timeOccure		 = presultEvent->timeOccure;

		// 4) 제일 마지막의 SubEvent객체에 추가한다.
		presultEvent->SubLog.push_back(plogSub);
	}

	// Log)
	_CGLog(_pMessageable, plogSub);
}
#else
inline void ICGEventObject::CGLOG_EVENT(_In_opt_ ICGMessageable* _pMessageable, _In_ eLOG_TYPE _Type, _In_ int _Level, _In_z_ const _CHAR* _Format, ...)
{
	// Check) _Format shouldn't be nullptr
	CGASSERT_ERROR(_Format != nullptr);

	// Declare) 
	CGPTR<CGLOG_RECORD>	plogSub;

	LOCK(m_pResult)
	{
		// Check) m_pResult가 nullptr면 안됀다.
		RETURN_IF(m_pResult.empty(), );

		// Check) m_pResult의 SubLog가 Empty면 안됀다.
		RETURN_IF(m_pResult->SubLog.empty(), );

		// 1) 제일 마지막의 SubEvent객체를 얻어 온다.
		auto&	presultEvent = m_pResult->SubLog.back();

		// Declare) 
		_CHAR	strMessage[MAX_TRACE_STRING_LENGTH] = { 0 };
		int		lengthMessage;
		va_list	ap;

		// 2) valist 
		va_start(ap, _Format);

		// 3) Generate EventLog Message
		lengthMessage = CGVSPRINTF_S(strMessage, MAX_TRACE_STRING_LENGTH, _TRUNCATE, _Format, ap);

		// 4) 로그 리스트에 추가한다.
		auto	logSub		 = NEW<CGLOG_RECORD>();
		logSub->eType		 = _Type;
		logSub->iLevel		 = _Level;
		logSub->strMessage	 = strMessage;
		logSub->timeOccure	 = presultEvent->timeOccure;

		presultEvent->SubLog.push_back(logSub);

		// 5) Va_End
		va_end(ap);
	}

	// Log) 
	_CGLog(_pMessageable, plogSub);
}
#endif

inline CGPTR<CGLOG_RECORD> ICGEventObject::_AppendResult(const _CHAR* _strState)
{
	LOCK(m_pResult)
	{
		// 1) Event 객체를 생성한다.
		auto	peventResult	 = NEW<CGLOG_RECORD>();

		// 2) 이름을 설정한다.
		peventResult->strMessage	 = _strState;

		// 3) 추가한 시간을 기록한다.
		peventResult->timeOccure	 = TIME::SYSTEM::now();

		// 4) 새로운 Result 객체를 추가한다.
		m_pResult->SubLog.push_back(peventResult);

		// Check) 보관하는 Result의 객체가 한계를 넘을 경우 제일 앞의 Result를 하나 제거한다.
		if (m_pResult->SubLog.size() > 256)
		{
			m_pResult->SubLog.pop_front();
		}

		// Return) 
		return	peventResult;
	}
}

inline void ICGEventObject::_AppendResult_Post(CGLOG_RECORD* _pLogResult)
{
	LOCK_BEGIN(m_pResult)
	{
		_pLogResult->strMessage.append(_CGTEXT(" ["));
		_pLogResult->strMessage.append(GetString_ObjectResult(_pLogResult->eResult));
		_pLogResult->strMessage.append(_CGTEXT("]"));
	}
	LOCK_END
}

