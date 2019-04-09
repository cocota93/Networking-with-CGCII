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

 @class		CListPriority
 @brief		큐잉된 Executable들을 우선순위큐 알고리즘을 사용해 차례로 실행한다.
 @todo		
 @ref		
 @details	\n
 기본적인 동작은 큐잉된 Executable 객체 중 예악된 실행시간이 지난 것들만 실행해준다.
 우선순위 큐(Priority queue)를 사용해 매번 모든 등록된 객체를 순회하지 않고도 현재 실행되어야 하는 객체만 실행해 준다.

*///-----------------------------------------------------------------------------
class CListPriority :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	//! @brief '실행자' 설정과 함께 생성한다. @param _pExecutor '실행자'
			CListPriority(ICGExecutor* _pExecutor=nullptr);
	virtual ~CListPriority();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//!	@brief 실행자를 닫는다. @return true 성공 @return false 실패
	virtual	bool				Stop() override;

	//! @brief '실행 객체'를 등록한다. @param _pExecutable 등록할 '실행 객체' @return true 성공 @return false 실패 (이미 등록된 객체일 경우 발생한다.)
			bool				RegisterExecutable(_In_ ICGExecutable* _pExecutable);
	//! @brief 등록된 '실행 객체'를 해제한다. @param _pExecutable 등록 해제 할 '실행 객체' @return true 성공 @return false 실패 (해당 개체가 등록된 상태가 아닐 경우 발생한다.)
			bool				UnregisterExecutable(_In_ ICGExecutable* _pExecutable);
	//!	@brief 등록된 모든 '실행 객체를' 해제한다.
			void				UnregisterAllExecutor();

	//!	@brief 등록된 '실행 객체'의 갯수를 얻는다. @return 등록된 '스케쥴 객체'의 수
			size_t				GetExecutorCount() const;
	//!	@brief 등록된 '실행 객체'가 하나도 없는지 확인한다. @return true 비어 있음. @return false 비어 있지 않음.
			bool				IsEmpty() const							{	return GetExecutorCount()==0;}
	//!	@brief 등록된 '실행 객체'들이 하나라도 있는지 확인한다. @return true 비어 있지 않음. @return false 비어 있음.
			bool				IsExist() const							{	return GetExecutorCount()!=0;}
			
	//! @brief 설정된 '실행자'를 얻는다. @return 설정된 '실행자'
			CGPTR<ICGExecutor>	GetExecutor() const						{	return m_pexecutorDefault;}
	//! @brief '실행자'를 설정한다. @param _pExecutor 등록할 '실행자'
			void				SetExecutor(_In_ ICGExecutor* _pExecutor){	m_pexecutorDefault=_pExecutor;}
	//! @brief 설정된 '실행자'를 리셋한다.
			void				ResetExecutor()							{	m_pexecutorDefault.reset();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Executor list
			LOCKABLE<vector<CGPTR<ICGExecutable>>>	m_priorityqueueExecutable;

	// 2) Executor
			CGPTR<ICGExecutor>	m_pexecutorDefault;

	//!	@brief '실행 객체'의 실행을 요청한다. @param _pExecutor 실행할 '실행 객체' @param _Param 실행 시 전달할 인자 @return true 성공 @return false 실패
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Param=0) override;

	// 3) Execute함수.
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) override;

			void				HeapDownExecutable();

};


}