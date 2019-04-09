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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
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
// 1. CGExecutor::CNotifierThread은~
//    1) UpdatableList에 Thread를 같이 붙힌 것이다.
//    2) Thread를 시작하고 멈추고 일정시간 마다 Execute하는 간격을 설정하는
//       기능이 있다.
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
	//! @brief '실행자' 설정과 함께 생성한다. @param _pExecutor '실행자' @param _tickGap 실행할 간격
	CSingleExecuteThread(_In_ ICGExecutor* _pExecutor=nullptr) : CSingleExecute(_pExecutor), NThread(true) { SetObjectType(eOBJECT_TYPE::EXECUTOR_SINGLE_EXECUTE_THREAD);}
	//! @brief '객체 이름'과 '실행자' 설정과 함께 생성한다. @param _strName 객체 이름 @param _pExecutor '실행자' @param _tickGap 실행할 간격
			CSingleExecuteThread(_In_ const _CHAR* _strName, _In_ ICGExecutor* _pExecutor = nullptr) : CSingleExecute(_pExecutor), NThread(_strName, true) {}
	//! @brief '객체 이름'과 '실행자' 설정과 함께 생성한다. @param _strName 객체 이름 @param _pExecutor '실행자' @param _tickGap 실행할 간격
			CSingleExecuteThread(_In_ const _CHAR_SUB* _strName, _In_ ICGExecutor* _pExecutor = nullptr) : CSingleExecute(_pExecutor), NThread(_strName, true) {}
	virtual	~CSingleExecuteThread() {}

// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//!	@brief 실행자를 닫는다. @return true 성공 @return false 실패
	virtual	bool				Stop() override							{	CSingleExecute::Stop(); NThread::Stop(); return true;}
};


}