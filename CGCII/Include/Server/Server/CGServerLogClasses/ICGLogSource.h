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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// ICGLogFilter
//
// 1. ICGLogFilter��~
//    ������ Log�� ����ϰų� �����ϱ� ���� Filtering�� �����ϴ� Class�̴�.
//    �Ϲ������� CCGLogFile�̳� Server MFC Control�� CCGChildLogView� ���ȴ�.
//
// 2. ICGLogFilter�� �ٽ� �Լ�
//		1) Filtering �Լ�
//
//         bool ProcessFiltering(const CGMSG_LOG& _Msg) PURE;
//
//         ���������Լ��� ProcessFiltering�� �������Ͽ� Log�� ���� �ʿ䰡 �ִ�
//         ��Ȳ�� true�� ���ϵǾ� ������ �Լ��� ������ �ָ� �ȴ�.
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

	// Check) _strMessage�� nullptr�̸� nullptr�� �����Ѵ�.
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
	// 1) Log Recored�� �����Ѵ�.
	auto	pLogRecord	 = NEW<CGLOG_RECORD>();

	// 2) ���� �����Ѵ�.
	pLogRecord->eType		 = _eType;
	pLogRecord->iLevel		 = _iLevel;
	pLogRecord->strMessage	 = _strMessage;
	pLogRecord->timeOccure	 = TIME::SYSTEM::now();

	// Return) 
	return	pLogRecord;
}
