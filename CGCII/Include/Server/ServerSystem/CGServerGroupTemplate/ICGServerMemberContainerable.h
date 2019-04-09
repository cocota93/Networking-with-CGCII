//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Group Template Classes                           *
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
//-----------------------------------------------------------------------------
/**

 @class		ICGServerMemberContainerable
 @brief		그룹의 멤버가 되기 위한 인터페이스 클래스이다.
 @todo		
 @ref		
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE>
class ICGServerMemberContainerable : virtual public ICGReferenceable
{
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief 특정 멤버를 찾는다. @param _fCondition 찾는 조건 함수 @return 찾은 멤버 데이터
	virtual	CGPTR<_TMEMBERBASE>	FindMember(const std::function<bool(_TMEMBERBASE*)>& _fCondition) PURE;

	//! @brief 모든 멤버에 특정 함수를 실행한다. @param _fExecute 실행하는 함수 @return true 성공 @return false 실패
	virtual	bool				ForEachMember(const std::function<bool(_TMEMBERBASE*)>& _fExecute) PURE;

};
