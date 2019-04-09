//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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
namespace CGExecutor
{

//-----------------------------------------------------------------------------
/**

 @class		CQueued
 @brief		IOCP�� ����� ������Ǯ�� ������ Executor�̴�.
 @todo		
 @ref		
 @details	\n
 @remark	\n
 IOCP�� Socket�� ���̰ų� IO�� Post�ϴ� �뵵�� �ַ� ���ȴ�.
 �� IOCP Completion Port�� ����� �Ͽ� Thread������ ���Ǳ⵵ ������ �ַ� .
 Client IOCP�� ���� ���ȴ�. MainLoop�� ������ Thread���� ����ϱ� ����
 Execut()�Լ��� TimeOut�� 0���� �����༭ ����Ѵ�.

*///-----------------------------------------------------------------------------
class CQueued :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor,							//     Executor Interface
	public						CGNameable::NString						// (@) Nameable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	//! @brief �⺻ ������
			CQueued();
	//! @brief ������ (�̸��� �����Ѵ�.) @param _strName '��ü �̸�'
			CQueued(_In_ const _CHAR* _strName);
	//! @brief ������ (�̸��� �����Ѵ�.) @param _strName '��ü �̸�'
			CQueued(_In_ const _CHAR_SUB* _strName);
	virtual	~CQueued();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Start/Stop function
	//! @brief ���� ���� ���� �����Ѵ�. @return true ���� @return false ����
			bool				Start() { CGMSG_CONTEXT tempMSG; return Start(tempMSG);}
	//! @brief '������'�� ����. @param _Msg ���� ������ �޽��� @return true ���� @return false ����
	virtual bool				Start(CGMSG_CONTEXT& _Msg) override;
	//!	@brief '������'�� �ݴ´�. @return true ���� @return false ����
	virtual	bool				Stop() override;

	// 2) Execute�Լ���...
	//! @brief ������ ó���ϴ� �Լ� @param _tickdiff �ִ� ���� ��� �ð�(�� �ð� ���� ó���� ���� ������ TIME_OUT���� �����Ѵ�.) @return	true ���� @return false ����
	virtual	bool				Execute(_In_ TICK::duration _tickMilliseconds=TICK::milliseconds(INFINITE)) override;

	//! @brief ť�׵� '���� ��ü'�� ��� �����Ѵ�.
			void				ExecuteAllQueued();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Post�Լ���.
	//! @brief '���� ��ü'�� ������ ��û�Ѵ�. @param _pExecutable ������ '���� ��ü' @param _Para ����� �ѱ� ���� @return true ���� @return false ����
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0) override;

protected:
		struct 	DATA_QUEUED;
		typedef	CGD::circular_list<DATA_QUEUED>	CONTAINER_EXECUTABLE_QUEUE;

			LOCKABLE<CONTAINER_EXECUTABLE_QUEUE>	m_queueExecutable;
			HANDLE				m_eventQueud;

			DATA_QUEUED			GetQueued();

};


}