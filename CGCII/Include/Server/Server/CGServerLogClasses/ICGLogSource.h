//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                            Server Log Classes                             *
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
// ICGLogFilter
//
// 1. ICGLogFilter은~
//    설정된 Log만 출력하거나 저장하기 위해 Filtering을 수행하는 Class이다.
//    일반적으로 CCGLogFile이나 Server MFC Control의 CCGChildLogView등에 사용된다.
//
// 2. ICGLogFilter의 핵심 함수
//		1) Filtering 함수
//
//         bool ProcessFiltering(const CGMSG_LOG& _Msg) PURE;
//
//         순수가상함수인 ProcessFiltering을 재정의하여 Log를 남길 필요가 있는
//         상황에 true가 리턴되어 오도록 함수를 정의해 주면 된다.
//
//-----------------------------------------------------------------------------
class ICGLogSource : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			CGPTR<CGLOG_RECORD>	GenerateLog(_In_ eLOG_TYPE _eType, _In_ int _iLevel, _In_z_ const _CHAR* _strMessage);

			template <class... TARGS>
			CGPTR<CGLOG_RECORD> GenerateLog(_In_ eLOG_TYPE _eType, _In_ int _iLevel, _In_z_ const _CHAR* _strFormat, TARGS... _Args);
	#else
			CGPTR<CGLOG_RECORD>	GenerateLog(_In_ eLOG_TYPE _Type, _In_ int _iLevel, _In_z_ const _CHAR* _strFormat, ...);
	#endif

// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	virtual CGPTR<CGLOG_RECORD>	ProcessGenerate(_In_ eLOG_TYPE _eType, _In_ int _iLevel, _In_z_ const _CHAR* _strMessage) PURE;

};

#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
inline CGPTR<CGLOG_RECORD> ICGLogSource::GenerateLog(_In_ eLOG_TYPE _eType, _In_ int _iLevel, _In_z_ const _CHAR* _strMessage)
{
	// Check) _strMessage shouldn't be nullptr
	CGASSERT_ERROR(_strMessage!=nullptr);

	// Check) _strMessage이 nullptr이면 nullptr를 리턴한다.
	RETURN_IF(_strMessage==nullptr, CGPTR<CGLOG_RECORD>());

	// Return)
	return	ProcessGenerate(_eType, _iLevel, _strMessage);
}

template <class... TARGS>
CGPTR<CGLOG_RECORD> ICGLogSource::GenerateLog(_In_ eLOG_TYPE _eType, _In_ int _iLevel, _In_z_ const _CHAR* _strFormat, TARGS... _Args)
{
	// Check) _strFormat shouldn't be nullptr
	CGASSERT_ERROR(_strFormat!=nullptr);

	// Declare) 
	_CHAR	strMessage[MAX_TRACE_STRING_LENGTH]{};

	// 1) Generate Trace Message
	CGSNPRINTF_S(strMessage, _TRUNCATE, _strFormat, _Args...);

	// 2)
	return	ProcessGenerate(_eType, _iLevel, _strMessage);
}
#else
inline CGPTR<CGLOG_RECORD> ICGLogSource::GenerateLog(_In_ eLOG_TYPE _eType, _In_ int _iLevel, _In_z_ const _CHAR* _strFormat, ...)
{
	// Check) _strFormat shouldn't be nullptr
	CGASSERT_ERROR(_strFormat!=nullptr);

	// Declare) 
	va_list	ap;

	// 1) valist 
	va_start(ap, _strFormat);

	// Declare) 
	_CHAR	strMessage[MAX_TRACE_STRING_LENGTH];

	// 2) Generate Trace Message
	CGVSPRINTF_S(strMessage, MAX_TRACE_STRING_LENGTH, _TRUNCATE, _strFormat, ap);

	// 3) Va_End
	va_end(ap);

	// Return)
	return	ProcessGenerate(_eType, _iLevel, strMessage);
}
#endif

inline CGPTR<CGLOG_RECORD>	ICGLogSource::ProcessGenerate(_In_ eLOG_TYPE _eType, _In_ int _iLevel, _In_z_ const _CHAR* _strMessage)
{
	// 1) Log Recored를 생성한다.
	auto	pLogRecord	 = NEW<CGLOG_RECORD>();

	// 2) 값을 설정한다.
	pLogRecord->eType		 = _eType;
	pLogRecord->iLevel		 = _iLevel;
	pLogRecord->strMessage	 = _strMessage;
	pLogRecord->timeOccure	 = TIME::SYSTEM::now();

	// Return) 
	return	pLogRecord;
}
