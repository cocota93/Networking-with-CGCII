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

 @class		CSingleExecute
 @brief		정해진 시간에 1회만 실행되는 Executable을 처리하는 Executor이다.
 @todo		
 @ref		
 @details	\n
 정해진 시간에 1회만 실행되고 실행된 Executable은 제거한다.
 내부적으로는 우선순위큐(Priority Queue)를 사용해서 만들어졌기 때문에 매우 많은 
 Executable이 있어도 효율적으로 처리가 가능하다.
 만약 동시 실행 갯수의 제한으로 실행을 실패했을 경우 실행될 때까지 계속 시도한다.
 아직 실행되지 않은 Executable의 경우 CancelExecutable()함수로 제거할 수 있다.
 기본 최대 큐의 깊이는 8192개로 설정되어 있다. (필요시 자동 확장된다.)

 또 자체적으로 Executable을 실행하지는 않고 다른 Executor에 실행을 요청하기만 하므로
 반드시 실행 전에 SetExecutor()함수를 하용해 Executor를 반드시 설정해 주어야 한다.
 만약 Executor가 설정되어 있지 않으면 아무런 동작도 하지 않는다.

*///-----------------------------------------------------------------------------
class CSingleExecute : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CSingleExecute(_In_ ICGExecutor* _pExecutor=nullptr);
	virtual ~CSingleExecute();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Stop
	//!	@brief '실행자'를 닫는다. @return true 성공 @return false 실패
	virtual	bool				Stop() override;

	// 2) Cancel Execution
	//! @brief 정해진 '실행 객체'를 취소한다. @param	_pExecutable 취소할 Executable 객체 @return true 성공 @return false 실패
			bool				CancelExecutable(_In_ ICGExecutable* _pExecutable);
	//!	@brief	모든 '실행 객체'를 취소한다. 	@details 이 함수를 실행하면 큐잉된 Executable은 0개가 된다.
			void				CancelAllExecutable();

	// 3) Attribute
	//!	@brief 큐잉된 '실행 객체'의 갯수를 얻는다. @return 큐잉된 '스케쥴 객체'의 수
			size_t				GetExecutableCount() const;
	//! @brief 현재 큐잉된 '실행 객체'가 하나도 없는지 확인한다. @return true 비어있다. @return	false 존재한다. @details IsExist()와 반대 함수이다.
			bool				IsEmpty() const							{	return GetExecutableCount()==0;}
	//! @brief 현재 큐잉된 '실행 객체'가 존재하는지 확인한다. @return	true 존재한다. @return false 존재하지 않는다.
			bool				IsExist() const							{	return GetExecutableCount()!=0;}

	// 4) Executor
	//! @brief 설정되어진 '실행자'를 얻는다.	@return	설정된 '실행자'
			CGPTR<ICGExecutor>	GetExecutor() const						{	return m_pExecutor;}
	//! @brief '실행 객체'를 처리해 줄 '실행자'를 설정한다. @param _pExecutor 설정할 '실행자;
			void				SetExecutor(_In_ ICGExecutor* _pExecutor){	m_pExecutor=_pExecutor;}
	//! @brief 설정된 '실행자'를 리셋한다.(nullptr로 설정한다)
			void				ResetExecutor()							{	m_pExecutor.reset();}

	// 5) Post함수임.
	//!	@brief	정해진 시간에 '실행 객체'를 실행한다. @param _tickTime 실행할 시간(TICK) @param _pExecutable 실행할 '실행 객체' @param _Para 실행 시 전달할 인자 @return true 성공 @return false 실패
			bool				PostExecuteAt(_In_ TICK::time_point _tickTime, _In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0);
	//!	@brief	현재 시간을 기점으로 정해진 시간 이후에 '실행 객체'를 실행한다.	@param _tickDiffer 	실행할 시점까지의 시간차	@param _pExecutable	실행할 '실행 객체' @param _Para 실행 시 전달할 인자 @return true 성공 @return false 실패
			bool				PostExecuteAfter(_In_ TICK::duration _tickDiffer, _In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// Definitions)
			struct EXECUTION_AT;

	// 1) Executor(일반적으로 CGExecutor::Defualt의 Executor)
			CGPTR<ICGExecutor>	m_pExecutor;

	// 2) Executable list
			LOCKABLE<vector<EXECUTION_AT>>	m_priorityqueueExecutable;

	// 3) Executable Push/Pop
			void				PushExecutable(_In_ const EXECUTION_AT& _pExecutable);
			void				PopExecutable();

	//!	@brief	실행을 요청하는 순간 즉시 실행된다. @param _pExecutable 실행할 '실행 객체' @param _Para 실행시 넘길 인자 @return true 성공 @return false 실패
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0) override;

	// 4) Execute함수.
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) override;

};


}