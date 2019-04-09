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

 @class		CFunctionMember
 @brief		특정 멤버 함수를 일정시간마다 Executor에 걸어주는 Schedulable 클래스
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TCLASS>
class CFunctionMember :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGSchedulable::NExecutable,
	public						CGExecutable::CFunctionMember<TCLASS>
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
			typedef		void (TCLASS::*PMEMBERFUNCTION)();


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	//! @brief 실행 간격 설정과 함께 생성한다. @param _tickGap 실행 간격
	explicit CFunctionMember(_In_ TICK::duration _tickGap=TICK::seconds(1)) : CGSchedulable::NExecutable(_tickGap) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION_MEMBER);}
	//! @brief 실행할 멤버 함수와 객체 그리고 실행 간격을 설정하며 생성한다. @param _Object '대상 객체' @param _pMemberFunction '실행 할 멤버 함수' @param _tickGap '실행 간격'
	explicit CFunctionMember(_In_ TCLASS* _Object, _In_ PMEMBERFUNCTION _pMemberFunction, _In_ TICK::duration _tickGap=TICK::seconds(1)) : CGSchedulable::NExecutable(_tickGap), CGExecutable::CFunctionMember<TCLASS>(_Object, _pMemberFunction) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION_MEMBER);}
	virtual ~CFunctionMember()	{}
};


}
}