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

namespace CGSchedulable
{

//-----------------------------------------------------------------------------
/**

 @class		NExecutable
 @brief		일정시간마다 Executable을 걸어주는 Schedulable 클래스이다.
 @todo		
 @ref		
 @details	\n
 일정시간마다 Executor에 실행이 걸려지는 Schedulable 객체이다.
 실행간격은 SetExecuteInterval()함수로 설정할 수 있다
 실행할 Executor는 SetExecutor()함수로 설정할 수 있다.
 만약 Executor가 설정되어져 있지 않으면 Default Executor에서 실행된다.

*///-----------------------------------------------------------------------------
class CExecutable :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public				CGSchedulable::NExecutable,
	public				CGExecutable::CExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
	CExecutable(_In_ TICK::duration _tickdifferExecute=TICK::seconds(1)) : CGSchedulable::NExecutable(_tickdifferExecute), CGExecutable::CExecutable() { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_EXECUTABLE);}
	virtual ~CExecutable()		{}


};


}
