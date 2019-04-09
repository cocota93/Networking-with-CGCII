//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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

template<typename TTYPE> class ICGAttachable;
template<typename TOBJECT> bool ATTACH(ICGAttachable<TOBJECT>* _pTarget, TOBJECT* _Object);
template<typename TOBJECT> bool DETACH(ICGAttachable<TOBJECT>* _pTarget, TOBJECT* _Object);

//-----------------------------------------------------------------------------
/**

 @class		ICGAttachable
 @brief		T형의 객체를 붙일 수 있는 속성 인터페이스 클래스
 @todo		
 @ref		
 @details	\n
 T 클래스 객체를 붙이거나(Attach) 붙어 있는 객체를 떼어내는(Detach) 인터페이스를 가지고 있다.

*/
//-----------------------------------------------------------------------------
template <typename TTYPE>
class ICGAttachable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Protected)
// ----------------------------------------------------------------------------
public:
	//! @brief _Object 객체 붙이기 과정을 정의한다. @param _pChild '피 붙임 객체' @return true 성공 @return false 실패(일반적으로 이미 붙어 있을 경우)
	virtual bool				ProcessAttach(_In_ TTYPE* _pChild) PURE;
	//! @brief 붙어 있는 _Object 객체를 떼어내는 과정을 정의한다. @param _pChild '피 해제 객체' @return true 성공 @return false 실패(일반적으로 붙어 있지 않을 경우)
	virtual int					ProcessDetach(_In_opt_ TTYPE* _pChild) PURE;

public:
	friend bool					ATTACH<>(ICGAttachable<TTYPE>* _pParent, TTYPE* _pChild);
	friend bool					DETACH<>(ICGAttachable<TTYPE>* _pParent, TTYPE* _pChild);
};

//! @brief _pParent객체에 _pChild를 붙인다. @param _pAttach 피 붙임 객체 @param _pChild 붙일 객체 @return true 성공 @return false 실패(일반적으로 이미 붙어 있을 경우)
template<class TOBJECT>
bool ATTACH(ICGAttachable<TOBJECT>* _pParent, TOBJECT* _pChild)
{
	return _pParent->ProcessAttach(_pChild);
}

//! @brief _pParent객체에서 _pChild를 떼낸다. @param _pParent 피 해제 객체 @param _pChild 떼어낼 객체 @return true 성공 @return false 실패(일반적으로 붙어 있지 않을 경우)
template<typename TOBJECT>
bool DETACH(ICGAttachable<TOBJECT>* _pParent, TOBJECT* _pChild)
{
	return _pParent->ProcessDetach(_pChild)!=0;
}
