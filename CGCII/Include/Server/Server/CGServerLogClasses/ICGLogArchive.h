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

@class		ICGLogArchive
@brief		Log 처리의 저장이 가능한 객체의 Interface Class
@todo
@ref
@details	\n

*/
//-----------------------------------------------------------------------------
class ICGLogArchive :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGMessageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGLogArchive()		{}
	virtual	~ICGLogArchive()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Trace Function
	virtual	bool				Store(CGLOG_RECORD* _pLogRecord)		{	return ProcessStore(_pLogRecord);}

	// 2) Max Log
			int					GetLogCount() const						{	return m_countLogTotal;}
			void				SetMaxLogRecordCount(int _Max)			{	m_countMaxLog = _Max; }
			int					GetMaxLogRecordCount() const			{	return m_countMaxLog; }


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	virtual bool				ProcessStore(CGLOG_RECORD* _pLogRecord) PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Filters
			CGPTR<ICGLogArchive>	m_pLogArchiveParent;

	// Statistics) 
			int					m_countMaxLog;
			int					m_countLogTotal;
			LOCKABLE<>			m_csCountLog;

};

