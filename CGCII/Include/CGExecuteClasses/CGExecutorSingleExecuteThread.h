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

 @class		CSingleExecuteThread
 @brief		
 @todo		
 @ref		
 @details	\n

//
// CGExecutor::CNotifierThread
//
// 1. CGExecutor::CNotifierThread��~
//    1) UpdatableList�� Thread�� ���� ���� ���̴�.
//    2) Thread�� �����ϰ� ���߰� �����ð� ���� Execute�ϴ� ������ �����ϴ�
//       ����� �ִ�.
//
*///-----------------------------------------------------------------------------
class CSingleExecuteThread : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CSingleExecute,
	public						NThread
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	//! @brief '������' ������ �Բ� �����Ѵ�. @param _pExecutor '������' @param _tickGap ������ ����
	CSingleExecuteThread(_In_ ICGExecutor* _pExecutor=nullptr) : CSingleExecute(_pExecutor), NThread(true) { SetObjectType(eOBJECT_TYPE::EXECUTOR_SINGLE_EXECUTE_THREAD);}
	//! @brief '��ü �̸�'�� '������' ������ �Բ� �����Ѵ�. @param _strName ��ü �̸� @param _pExecutor '������' @param _tickGap ������ ����
			CSingleExecuteThread(_In_ const _CHAR* _strName, _In_ ICGExecutor* _pExecutor = nullptr) : CSingleExecute(_pExecutor), NThread(_strName, true) {}
	//! @brief '��ü �̸�'�� '������' ������ �Բ� �����Ѵ�. @param _strName ��ü �̸� @param _pExecutor '������' @param _tickGap ������ ����
			CSingleExecuteThread(_In_ const _CHAR_SUB* _strName, _In_ ICGExecutor* _pExecutor = nullptr) : CSingleExecute(_pExecutor), NThread(_strName, true) {}
	virtual	~CSingleExecuteThread() {}

// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//!	@brief �����ڸ� �ݴ´�. @return true ���� @return false ����
	virtual	bool				Stop() override							{	CSingleExecute::Stop(); NThread::Stop(); return true;}
};


}