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

 @class		CListThread
 @brief		CGExecutor::CList<TEXECUTOR>�� �����带 ���� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 CGExecutor::CList<TEXECUTOR>�� Execute()�Լ��� ������Ǯ���� �������ش�.

*///-----------------------------------------------------------------------------
template <class TEXECUTOR=ICGExecutor>
class CListThread : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CList<TEXECUTOR>,
	public						NThread
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	//! @brief �⺻������
	CListThread() : NThread()	{	SetObjectType(eOBJECT_TYPE::EXECUTOR_LIST_THREAD);}
	//! @brief ���� ������ ������ �Բ� �����Ѵ�. @param _tickdiff '���� ����'
			CListThread(bool _bEnableSkipFrame) : NThread(_bEnableSkipFrame)	{}
	//! @brief ��ü�̸��� �Բ� �����Ѵ�. @param _Name '��ü �̸�' @param _tickdiff '���� ����'
			CListThread(_In_ const _CHAR* _Name, bool _bEnableSkipFrame=false) : NThread(_Name, _bEnableSkipFrame) {}
	//! @brief ��ü�̸��� �Բ� �����Ѵ�. @param _Name '��ü �̸�' @param _tickdiff '���� ����'
			CListThread(_In_ const _CHAR_SUB* _Name, bool _bEnableSkipFrame=false) : NThread(_Name, _bEnableSkipFrame) {}
	virtual	~CListThread() {}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//!	@brief �����ڸ� �ݴ´�. @return true ���� @return false ����
	virtual	bool				Stop() override							{	CList<TEXECUTOR>::Stop(); NThread::Stop(); return true;}
};


}
