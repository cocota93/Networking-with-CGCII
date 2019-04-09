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

 @class		NThread
 @brief		��ü���� ������� ������ Execute()�Լ��� ȣ���ϴ� Executor
 @todo		
 @ref		
 @details	\n
 ��ü���� Thread�� ������ ������ m_dwExecuteGap���� Execute()�Լ��� ȣ���Ѵ�.
 StartTrhead()�Լ��� ȣ���Ͽ� Thread�� ������ �� ������ StopThread�Լ��� ȣ���Ͽ� Thread�� �ߴܽ�ų�� �ִ�.
 ���� Thread�θ� �����Ѵ�.
 
*///-----------------------------------------------------------------------------
class NThread :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor,
	protected					CGAPI::CThread
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
	//! @brief �⺻ ������
			NThread();
	//! @brief ��ŵ ��ɰ� �Բ� �����Ѵ�. @param _tickdiff ���� ����
			NThread(bool _bEnableFrameSkip);
	//! @brief ��ü �̸��� ���� ���� ������ �Բ� �����Ѵ�. @param _Name ��ü �̸� @param _tickdiff ���� ����
			NThread(_In_ const _CHAR* _strName, bool _bEnableFrameSkip=false);
			NThread(_In_ const _CHAR_SUB* _strName, bool _bEnableFrameSkip=false);
	virtual ~NThread();
	

// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Thread�� �����ϰ� ������Ű��.
	//! @brief '������'�� ����. @param _Msg ���� ������ �޽��� @return true ���� @return false ����
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override;
	//! @brief '���� ����'�� ������ '������'�� ����. @param _tickdiff '���� ����' @return true ���� @return false ����
			bool				Start(_In_ TICK::duration _tickdiff);

	//!	@brief �����ڸ� �ݴ´�. @return true ���� @return false ����
	virtual bool				Stop() override;

	// 2) ���ణ�� �����Լ�.
	//! @brief ������ '���� ����'�� ��´�. @return '���� ����'
			TICK::duration		GetExecuteGap() const					{	return m_tickdiffExecute;}
	//! @brief '���� ����'�� �����Ѵ�.
			void				SetExecuteGap(_In_ TICK::duration _tickdiff);

	// 3) Skip����
	//! @brief ������ ��ŵ ����� Ȱ��ȭ �Ǿ� �ִ����� Ȯ���Ѵ�. @return true Ȱ��ȭ @return false ��Ȱ��ȭ
			bool				IsEnableFrameSkip() const				{	return m_bEnableFrameSkip;}
	//! @brief ������ ��ŵ ����� �����Ѵ�. @param _bEnable Ȱ��ȭ ���� @return true Ȱ��ȭ
			void				EnableFrameSkip(bool _bEnable=true)		{	m_bEnableFrameSkip=_bEnable;}
	//! @brief ������ ��ŵ ����� �����Ѵ�. 
			void				DisableFrameSkip()						{	EnableFrameSkip(false);}
	//! @brief ������ ��ŵ ����� ���¸� �����Ѵ�.
			void				ToggleFrameSkip()						{	EnableFrameSkip(!m_bEnableFrameSkip);}

	// 4) Thread����(Delegation�Լ�)
	//! @brief �������� ������ ��� �ߴ��Ѵ�. @return ������ �ڵ�
			uint32_t			Suspend()								{	return CGAPI::CThread::Suspend();}
	//! @brief ��� �ߴ� �ߴ� �����带 �ٽ� �����Ѵ�. @return ������ �ڵ�
			uint32_t			Resume()								{	return CGAPI::CThread::Resume();}
	//! @brief '������ �ڵ�'�� ��´�. @return '������ �ڵ�'
			THREAD_ID			GetThreadHandle() const					{	return CGAPI::CThread::GetThreadHandle();}
	//!	@brief ������ ���ܸ� �߻���Ų��. @return true ���� @return false ����
			bool				RaiseException()						{	return CGAPI::CThread::RaiseException();}
			

// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) ������¸� ��Ÿ���� ����
	//    - m_bRun�� false�� Thread�� ���� �������� �������� Thread�� �����ϰ� �ȴ�.
	//    - �� ������ StartThread()���� true�� �ٲ�� StopThread���� false�� �ٲ��.
			ATOMIC<int>			m_bRun;
			bool				m_bEnableFrameSkip;

	// 2) �����ϴ� ����(tick)
	//    - m_dwExecuteGap���� �ѹ��� Execute()�Լ��� ȣ���ϰ� �ȴ�.
			TICK::duration		m_tickdiffExecute;

protected:
	static	uint32_t			fnThread(_In_ NThread* p_this);
			uint32_t			ThreadRun();
};


}
