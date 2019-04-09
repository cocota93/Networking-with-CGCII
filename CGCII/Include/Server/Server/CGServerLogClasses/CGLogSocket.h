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
// CCGLogSocket
//
// 1. CCGLogSocket��~
//     Logó���� ���� ���̴�.
//
// 2. Log�� ����
//		0) Date/Time	Log�� ���� �ð��̴�.(�ڵ����)
//		1) Logger		Log�� ����� ���� �̸��̴�.(�ڵ� ���)
//		2) Type			Log�� �����̴�. Errror, Progress, Warning, Info, ...
//	    3) Level		Log�� �߿䵵�̴�.
//		4) Source		Log�� ����� Event�� ��ü�� �Ǵ� ���� �ǹ��Ѵ�.
//		5) Dest			Log�� ����� Event�� ����� �Ǵ� ���� �ǹ��Ѵ�.
//		6) Where		Log�� ����� Event�� �߻��ϴ� ��ü�� �ǹ��Ѵ�.
//		7) Function		Log�� ���� Event�� ȣ���� �Լ��� �ǹ��Ѵ�.
//		8) Message		���� Log Message�� �ǹ��Ѵ�.
//
//-----------------------------------------------------------------------------
class CCGLogSocket : 
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
			CCGLogSocket();
			CCGLogSocket(_In_ const char* _strName, _In_opt_ const char* _strAddress=nullptr);
			CCGLogSocket(_In_ const wchar_t* _wstrName, _In_opt_ const wchar_t* _wstrAddress=nullptr);
	virtual ~CCGLogSocket();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Init
			bool				Initialize(_In_ const char* _strAddress);
			bool				Initialize(_In_ const wchar_t* _wstrAddress);


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief �޽��� ó���� ������ �Լ�
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	//! @brief Log�� ó���� ������ �Լ�
	virtual	void				ProcessLog(CGLOG_RECORD* _pLogRecord) override;

	//! @brief �ʱ�ȭ ������ �����Ѵ�. @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual	void				_ProcessInitializing(CGMSG_CONTEXT& _Msg) override;
	//! @brief �ı� ������ �����Ѵ�.
	virtual	void				_ProcessDestroying() override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Filters
			int					m_countLog[static_cast<size_t>(eLOG_TYPE::MAX) + 1];
			CGPTR<CGNet::Socket::CTCPClientReconnect<>>	m_psocketLog;
};
