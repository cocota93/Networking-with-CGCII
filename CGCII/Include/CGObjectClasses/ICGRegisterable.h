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

template<typename TTYPE> class ICGRegisterable;
template<typename TOBJECT> bool REGISTER(ICGRegisterable<TOBJECT>* _pAttach, TOBJECT* _Object);
template<typename TOBJECT> bool UNREGISTER(ICGRegisterable<TOBJECT>* _pAttach, TOBJECT* _Object);

//-----------------------------------------------------------------------------
/**

 @class		ICGRegisterable
 @brief		등록 가능 속성의 인터페이스 클래드
 @todo		
 @ref		
 @details	\n
 TTYPE형 객체를 등록하거나 등록 해제하는 속성을 가진 인터페이스 클래스이다.
 ProcessRegister(...)함수로 객체를 등록하고 ProcessUnregister(...)로 등록된 객체를 해제하는 인터페이스를 가진다.

*/
//-----------------------------------------------------------------------------
template <typename TTYPE>
class ICGRegisterable : 
	// ****************************************************************************
	// Inherited Classes) 
	// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
	// ****************************************************************************
	// Protected)
	// ----------------------------------------------------------------------------
public:
	//! @brief '대상 객체'를 등록한다. @param _Object 등록할 '대상 객체' @return true 성공 @return false 실패(일반적으로 이미 등록된 객체 일 경우)
	virtual bool				ProcessRegister(TTYPE* _Object) PURE;
	//! @brief 등록된 '대상 객체'를 해제한다. @param _Object 해제할 '대상 객체' @return true 성공 @return false 실패(일반적으로 등록되어 있지 않을 객체일 경우)
	virtual bool				ProcessUnregister(TTYPE* _Object) PURE;

public:
	//! @brief _Registerable 객체에 _Object 객체를 등록한다. @param _pRegisterable 피등록 객체 @param _Object 등록할 객체 @return true 성공 @return false 실패(일반적으로 이미 등록된 객체 일 경우)
	friend bool					REGISTER<>(ICGRegisterable<TTYPE>* _pRegisterable, TTYPE* _Object);
	//! @brief _Registerable 객체에서 _Object 객체를 등록 해제한다. @param _pRegisterable 피등록해제 객체 @param _Object 등록해제될 객체 @return true 성공 @return false 실패(일반적으로 등록되어 있지 않을 객체일 경우)
	friend bool					UNREGISTER<>(ICGRegisterable<TTYPE>* _pRegisterable, TTYPE* _Object);
};

template<class TOBJECT>
bool REGISTER(ICGAttachable<TOBJECT>* _pAttach, TOBJECT* _Object)
{
	return _pAttach->ProcessRegister(_Object);
}

template<typename TOBJECT>
bool UNREGISTER(ICGAttachable<TOBJECT>* _pAttach, TOBJECT* _Object)
{
	return _pAttach->ProcessUnregister(_Object);
}
