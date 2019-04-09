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

@class		CCGLogSlack
@brief		Slack에 Log를 전달하기 위한 Log객체
@todo
@ref
@details	\n
Slack과 연결하여 Log 내용을 Slack에 남긴다.

*/
//-----------------------------------------------------------------------------
#define INFO_SIZE	4

class CCGLogSlack :
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
			CCGLogSlack();
			CCGLogSlack(_In_ const char* _strName, _In_opt_ const char* _strToken=nullptr, _In_opt_ const char* _strChannel = nullptr, _In_opt_ const char* _strAddress = nullptr);
			CCGLogSlack(_In_ const wchar_t* _strName, _In_opt_ const wchar_t* _strToken, _In_opt_ const wchar_t* _strChannel = nullptr, _In_opt_ const wchar_t* _strAddress = nullptr);
	virtual ~CCGLogSlack();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Init
			bool				Initialize(_In_ const char* _strToken, _In_ const char* _strChannel, _In_opt_ const char* _strAddress=nullptr);
			bool				Initialize(_In_ const wchar_t* _strToken, _In_ const wchar_t* _strChannel, _In_opt_ const wchar_t* _strAddress=nullptr);


// ****************************************************************************
// CGMessage) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 메시지 처리를 정의한 함수
	virtual	int					ProcessMessage(CGMSG& _Msg) override;
	//! @brief 메시지 처리를 정의한 함수
	virtual	void				ProcessLog(CGLOG_RECORD* _pLogRecord) override;

	//! @brief 자식 노드의 초기화 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	//! @brief 자식 노드의 파괴 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessDestroying() override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) 
			std::wstring		m_strAddress;
			std::wstring		m_strToken;
			std::wstring		m_strChannel;

	// Statistics) 
			int					m_countLog[static_cast<size_t>(eLOG_TYPE::MAX)+1];
};
