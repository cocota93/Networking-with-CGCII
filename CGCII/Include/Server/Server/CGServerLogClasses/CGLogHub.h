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
// CCGLogHub
//
// 1. CCGLogHub은~
//    하나의 Log로 여러 곳에 Log를 남기기 위한 Log용 Hub 객체라고 할수 있다.
//    다양한 형태와 종류의 Log객체를 CCGLogHub 객체에 RegisterMessageable()
//    함수로 등록해 놓으면 CCGLogHub 객체에 Log가 전달되었을 시 모든 등록된
//    Log 객체들에게 메시지를 전파한다.
//
// 2. Log의 내용
//		0) Date/Time	Log가 남은 시간이다.(자동기록)
//		1) Type			Log의 종류이다. Errror, Progress, Warning, Info, ...
//	    2) Level		Log의 중요도이다.
//		3) Message		남길 Log Message를 의미한다.
//
//-----------------------------------------------------------------------------
class CCGLogHub : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NCGDispatchable,
	public						NCGObjectState,
	public						NCGInitializable,
	virtual public				ICGMessageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGLogHub();
	virtual ~CCGLogHub();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Filtering
			void				SetFilter(_In_ ICGLogFilter* _pLogFilter){	m_pLogFilter=_pLogFilter;}
			CGPTR<ICGLogFilter>	GetFilter() const						{	return m_pLogFilter;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Filters
			CGPTR<ICGLogFilter>	m_pLogFilter;

	// 2) Process Message
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	//! @brief 자식 노드의 파괴 처리가 진행된 후 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessDestroy() override;
};
