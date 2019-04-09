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

 @class		CList
 @brief		여러 개의 Executor를 묶은 Executor 객체이다.
 @todo		
 @ref		
 @details	\n
 Execute()함수가 호출되면 등록된 모든 Executor의 Execute()함수를 호출해 준다.

*///-----------------------------------------------------------------------------
template <class TEXECUTOR>
class CList :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor,
	virtual public				ICGAttachable<TEXECUTOR>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CList();
	virtual ~CList();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// Definitions) 
			typedef	circular_list<CGPTR<TEXECUTOR>>	CONTAINER;
			class ITERATOR;

	//!	@brief 실행자를 닫는다. @return true 성공 @return false 실패
	virtual	bool				Stop() override;

	// 2) Attach/Detach
	//! @brief '실행자'를 등록한다. @param _pExecutor 등록할 '실행자' @return true 등록 성공 @return false 등록 실패(일반적으로 동일한 객체가 등록되어 있을 경우 실패한다.)
			bool				RegisterExecutor(_In_ TEXECUTOR* _pExecutor)	{ return ProcessAttach(_pExecutor);}
	//! @brief 등록된 '실행자'를 해제한다. @param _pExecutor 등록해제할 '실행자' @return true 등록해제 성공 @return false 등록해제 실패(일반적으로 해당 객체가 등록되어 있지 않을 경우 실패한다.)
			bool				UnregisterExecutor(_In_opt_ TEXECUTOR* _pExecutor)	{ return ProcessDetach(_pExecutor);}
	//! @brief 등록된 모든 '실행자'를 해제한다.
			int					UnregisterAllExecutor();

	// 3) Iterator
	//! @brief	등록된 '실행 객체'들에 접근하기 위한 반복자를 얻는다. @return !nullptr 반복자 @return nullptr 획득 실패
			ITERATOR			GetIterator();

	// 4) Attribute
	//!	@brief 등록된 '실행 객체'의 갯수를 얻는다. @return 등록된 '스케쥴 객체'의 수
			size_t				GetExecutorCount() const;
	//!	@brief 등록된 '실행자'가 하나도 없는지 확인한다. @return true 비어 있음. @return false 비어 있지 않음.
			bool				IsEmpty() const;
	//!	@brief 등록된 '실행자'들이 하나라도 있는지 확인한다. @return true 비어 있지 않음. @return false 비어 있음.
			bool				IsExist() const;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Executor list
			LOCKABLE<CONTAINER>	m_listExecutor;

	// 2) Execute
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) override;

	// 3) Post함수임.
	//! @brief '실행 객체'의 처리를 요청한다. @param _pExecutable '실행 객체' @param _Para 실행 시 전달할 인자 @return true 성공 @return false 실패
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0) override;

	// 4) Attach/Detach
	virtual	bool				ProcessAttach(_In_ TEXECUTOR* _pSchedulable) override;
	virtual	int					ProcessDetach(_In_opt_ TEXECUTOR* _pSchedulable) override;
};


}

#include "CGExecuteclasses/CGExecutorList.inl"