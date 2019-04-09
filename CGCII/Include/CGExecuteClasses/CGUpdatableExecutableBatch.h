//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              CG3D D3D Classes                             *
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

namespace CGUpdatable
{

//-----------------------------------------------------------------------------
/**

 @class		CExecutableBatch
 @brief		�񵿱��� Update�� ó���ϱ� ���� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 Updateó���� Executor�� ������ �����ϱ� ���� Ŭ�����̴�.
 �Ϲ������� Updateó���� �񵿱� ó���ؾ��� �� ���ȴ�.

*///-----------------------------------------------------------------------------
class CExecutableBatch : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGUpdatable,
	virtual public				ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CExecutableBatch(size_t p_iThread=CGEXECUTOR_AUTO);
	virtual	~CExecutableBatch();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 2) Queue
	//! @brief '������Ʈ�� ��ü'�� ť���Ѵ�. @param _pUpdatable ������Ʈ�� '������Ʈ ��ü'
			void				QueueUpdatable(ICGUpdatable* _pUpdatable);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	virtual	int					ProcessUpdate(CGMSG& _Msg) override;

protected:
	// 1) ����/�ı�
			void				ProcessInitialize(size_t p_iThread);
	virtual	void				ProcessDestroy();

	// 2) Rendering Context
			CGMSG*				m_pMSG;

	// 3) Executable List
			LOCKABLE<circular_list<CGPTR<ICGUpdatable>>> m_listUpdatable;
			
	// 4) Thread...
			size_t				m_iMaxThreadCount;
			HANDLE				m_hComplete;
			ATOMIC<size_t>		m_iCount;

	// 5) ������ ó���Ѵ�.
	virtual intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


}



