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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGUpdatable
{

//-----------------------------------------------------------------------------
/**

 @class		CExecutableBatch
 @brief		비동기적 Update를 처리하기 위한 클래스이다.
 @todo		
 @ref		
 @details	\n
 Update처리를 Executor에 전달해 실행하기 위한 클래스이다.
 일반적으로 Update처리를 비동기 처리해야할 때 사용된다.

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
	//! @brief '업데이트블 객체'를 큐잉한다. @param _pUpdatable 업데이트할 '업데이트 객체'
			void				QueueUpdatable(ICGUpdatable* _pUpdatable);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	virtual	int					ProcessUpdate(CGMSG& _Msg) override;

protected:
	// 1) 생성/파괴
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

	// 5) 실행을 처리한다.
	virtual intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


}



