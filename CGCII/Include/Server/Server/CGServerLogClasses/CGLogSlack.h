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
/**

@class		CCGLogSlack
@brief		Slack�� Log�� �����ϱ� ���� Log��ü
@todo
@ref
@details	\n
Slack�� �����Ͽ� Log ������ Slack�� �����.

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
	//! @brief �޽��� ó���� ������ �Լ�
	virtual	int					ProcessMessage(CGMSG& _Msg) override;
	//! @brief �޽��� ó���� ������ �Լ�
	virtual	void				ProcessLog(CGLOG_RECORD* _pLogRecord) override;

	//! @brief �ڽ� ����� �ʱ�ȭ ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	//! @brief �ڽ� ����� �ı� ó���� ����Ǳ� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
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
