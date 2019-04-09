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
// CCGLogEvent
//
// 1. CCGLogEvent은~
//     Log처리를 위한 것이다.
//
// 2. Log의 내용
//		0) Date/Time	Log가 남은 시간이다.(자동기록)
//		1) Logger		Log를 남기는 자의 이름이다.(자동 등록)
//		2) Type			Log의 종류이다. Errror, Progress, Warning, Info, ...
//	    3) Level		Log의 중요도이다.
//		4) Source		Log에 남기는 Event의 주체가 되는 것을 의미한다.
//		5) Dest			Log에 남기는 Event의 대상이 되는 것을 의미한다.
//		6) Where		Log에 남기는 Event가 발생하는 객체를 의미한다.
//		7) Function		Log가 남는 Event를 호출한 함수를 의미한다.
//		8) Message		남길 Log Message를 의미한다.
//
//-----------------------------------------------------------------------------
class CCGLogConsole : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGLog,
	public						CGNameable::NString,
	public						NCGObjectState,
	public						NCGInitializable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGLogConsole();
			CCGLogConsole(_In_ const char* _strName, _In_opt_ const char* _strFileName = nullptr);
			CCGLogConsole(_In_ const wchar_t* _strName, _In_opt_ const wchar_t* _strFileName = nullptr);
	virtual ~CCGLogConsole();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Init
			bool				Initialize()								{ return NCGInitializable::Initialize(); }
	virtual	bool				Initialize(CGMSG_CONTEXT& _Msg) override	{ return NCGInitializable::Initialize(_Msg); }

	// 2) Trace
	virtual	void				ProcessLog(CGLOG_RECORD* _pLogRecord) override;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 메시지 처리를 정의한 함수
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	//! @brief 초기화 절차를 정의한다. @param _MSg 초기활 할 때 전달된 메시지
	virtual	void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	//! @brief 파괴 절차를 정의한다.
	virtual	void				_ProcessDestroying() override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Filters
			int					m_countLog[static_cast<size_t>(eLOG_TYPE::MAX) + 1];
};
