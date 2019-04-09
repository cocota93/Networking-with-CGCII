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
namespace Executable
{

//-----------------------------------------------------------------------------
/**

 @class		CFunction
 @brief		특정 함수를 일정시간마다 Executor에 걸어주는 Schedulable 클래스
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TEXECUTE=TFUNCTION>
class CFunction :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGSchedulable::NExecutable,
	public						CGExecutable::CFunction<TEXECUTE>
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	//! @brief 기본 생성자.
	explicit CFunction() : NExecutable() { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}
	//! @brief 실행 간격 설정과 함께 생성한다. @param _tickGap 실행 간격
	explicit CFunction(_In_ TICK::duration _tickGap) : NExecutable(_tickGap) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}
	//! @brief 실행 함수의 설정과 함께 생성한다. @param _Function 실행 함수
	explicit CFunction(_In_ const TFUNCTION& _Function) : CGSchedulable::NExecutable(), CGExecutable::CFunction<TEXECUTE>(_Function) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}
	//! @brief 실행 함수와 실행 간격 설정과 함께 생성한다. @param _Function 실행 함수 @param _tickGap 실행 간격
	explicit CFunction(_In_ const TFUNCTION& _Function, _In_ TICK::duration _tickGap) : CGSchedulable::NExecutable(_tickGap), CGExecutable::CFunction<TEXECUTE>(_Function) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}

	virtual ~CFunction()		{}
};


}
}
