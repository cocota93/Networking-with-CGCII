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
/**

@class		ICGLog
@brief		Log를 기록할 수 있는 객체의 Interface Class
@todo
@ref
@details	\n
Log처리를 위한 기본적인 구성품을 가지고 있는 Inteface 클래스이다.

*/
//-----------------------------------------------------------------------------
class ICGLog :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGMessageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGLog() : m_countMaxLog(DEFAULT_MAX_LOG_COUNT), m_countLogTotal(0) {}
	virtual	~ICGLog()			{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Trace Function
			void				Trace(CGLOG_RECORD* _pLogRecord)		{	ProcessLog(_pLogRecord);}

	// 2) Filtering
			void				SetFilter(_In_ ICGLogFilter* _pLogFilter){	m_pLogFilter=_pLogFilter;}
			CGPTR<ICGLogFilter>	GetFilter() const						{	return m_pLogFilter;}

	// 3) Max Log
			void				SetMaxLogCount(int _Max)				{	m_countMaxLog = _Max; }
			int					GetMaxLogCount() const					{	return m_countMaxLog; }

	// 4) Stored Message
			int					GetLogCount() const						{	return m_countLogTotal;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	virtual	void				ProcessLog(CGLOG_RECORD* _pLogRecord) PURE;

protected:
	// 2) Filters
			CGPTR<ICGLogFilter>	m_pLogFilter;

	// Statistics) 
			int					m_countMaxLog;
			int					m_countLogTotal;
			LOCKABLE<>			m_csCountLog;

};

#define CGTRACE					Trace(GenerateLog());