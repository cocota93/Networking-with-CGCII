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

namespace CGExecutable
{

//-----------------------------------------------------------------------------
/**

 @class		NBatch
 @brief		한꺼번에 여러 개의 Executable 객체를 큐잉해 걸어주는 Executable이다. 
 @todo		
 @ref		CList<TEXECUTABLE>
 @details	\n
 여러 개의 Executable 객체를 큐잉해 실행해준다. 
 따라서 실행을 걸어주게 되면 큐잉된 Executable 객체들은 제거된다.

*///-----------------------------------------------------------------------------
class NBatch :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NBatch();
	virtual ~NBatch();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//!	@brief	실행 객체들을 큐잉한다. @param _pExecutable 큐잉할 '실행 객체' @param _Param 실행 시 전달할 인자
			void				QueueExecutable(_In_ ICGExecutable* _pExecutable, _In_ size_t _Param=0);
	//!	@brief	큐잉된 모든 객체들을 제거한다.
			void				Clear();

	//! @brief	실행을 요청한다. 이때 까지 큐잉된 모든 '실행 객체'를 실행한다. @param _pExecutor 실행을 요청할 '실행자' @return true 성공 @return false 실패 
			bool				RequestExecute(_In_ ICGExecutor* _pExecutor);

	//! @brief 현재 실행이 진행중인 '실행 객체'의 수를 얻는다.	@return 현재 실행 중인 '실행 객체'의 수
			size_t				GetExecutingCount() const;

	//! @brief 실행 객체를 큐잉을 한다. @param rhs 큐잉할 '실행 객체'
			NBatch&				operator<<(ICGExecutable* rhs)			{	QueueExecutable(rhs); return *this;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//!	@brief 일괄처리가 완료되었을 때 처리할 내용을 정의한다.
	virtual	void				ProcessCompleteExecution() PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// Declare) 
	struct QUEUE_EXECUTABLE
	{
		CGPTR<ICGExecutable>	pExecutable;
		size_t					dwParam;

		QUEUE_EXECUTABLE()												{}
		QUEUE_EXECUTABLE(_In_ ICGExecutable* _pExecutable, _In_ size_t _Param) : pExecutable(_pExecutable), dwParam(_Param) {}
	};

	// 2) Executable List
			LOCKABLE<circular_list<QUEUE_EXECUTABLE>> m_listExecutable;

	// 3) 실행을 처리한다.
	virtual intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


}
