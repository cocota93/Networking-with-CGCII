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

 @class		CCompletionPortThread
 @brief		CGExecutor::CCompletionPort�� Thread Pool�� ������ Ŭ�����̴�.
 @todo		
 @ref		CGExecutor::CCompletionPort
 @details	\n
 CGExecutor::CCompletePort�� Execute()�Լ��� CGAPI::CThreadPool�� �����忡��
 ȣ�����ش�.

*///-----------------------------------------------------------------------------
class CCompletionPortThread : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGAPI::CThreadPool,						// (@) I/Oó���� ���� Thread Pool
	public						CGExecutor::CCompletionPort				// (@) CompletionPort
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCompletionPortThread();
	//! @brief ���� �� ��ü �̸��� �����Ѵ�. @param '��ü �̸�'
			CCompletionPortThread(_In_ const _CHAR* _strName);
			CCompletionPortThread(_In_ const _CHAR_SUB* _strName);
	virtual ~CCompletionPortThread();

	
// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief '������'�� ������� �Բ� �����Ѵ�. @param _iThreadCount ������ ������ ���� @return true ���� @return false ����
			bool				Start(_In_ int _iThreadCount=0);
	//! @brief '������'�� ����. @param _Msg ���� ������ �޽��� @return true ���� @return false ����
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override;
	//!	@brief	'������'�� �ݴ´�. @return true �ݱ⿡ ���� @return false	����(�̹� �ݱⰡ ���� ���� ���)
	virtual	bool				Stop() override;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			uint32_t			ProcessThreadRun();

protected:
			bool				m_bDone;
};


}
