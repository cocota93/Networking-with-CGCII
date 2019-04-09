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

 @class		CList
 @brief		여러 개의 Exectutable 객체를 가지고 있는 Executable 클래스이다.
 @todo		
 @ref		
 @details	\n
 여러 개의 Executable을 list형태로 가지고 있으며 실행될 때 자신이 가진 Executable의 ProcessExecute()를 모두 호출해준다.
 또 ITERATOR를 얻어 내부 Executable을 접근 할 수 있다.

*///-----------------------------------------------------------------------------
template <class TEXECUTABLE=ICGExecutable>
class CList :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual protected			ICGExecutable
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
			typedef	circular_list<CGPTR<TEXECUTABLE>>	CONTAINER;
			class ITERATOR;

	// 1) Attach/Detach
	//! @brief Executable '실행 객체'를 등록한다. @param _pExecutable 등록할 '실행 객체' @return true 등록 성공 @return false 등록 실패(일반적으로 동일한 객체가 등록되어 있을 경우 실패한다.)
			bool				RegisterExecutable(_In_ TEXECUTABLE* _pExecutable);
	//! @brief 등록된 '실행 객체'를 해제한다. @param _pExecutable 등록해제할 '실행 객체' @return true 등록해제 성공 @return false 등록해제 실패(일반적으로 해당 객체가 등록되어 있지 않을 경우 실패한다.)
			bool				UnregisterExecutable(_In_ TEXECUTABLE* _pExecutable);
	//! @brief 모든 등록된 Executable 객체들을 등록해제한다.
			void				DetachAllExecutable();

	// 2) Iterator
	//! @brief 등록된 '실행 객체'들에 접근하기 위한 반복자를 얻는다. @return !nullptr 반복자 @return nullptr 획득 실패
			ITERATOR			GetIterator();

	// 3) ExecutableCount
	//! @brief 등록된 '실행 객체'들의 갯수를 얻는다.	@return	등록된 '실행 객체'들의 갯수
			size_t				GetExecutableCount() const;
	//!	@brief 등록된 '실행 객체'가 하나도 없는지 확인한다. @return true 비어 있음. @return false 비어 있지 않음.
			bool				IsEmpty() const;
	//!	@brief 등록된 '실행 객체'들이 하나라도 있는지 확인한다. @return true 비어 있지 않음. @return false 비어 있음.
			bool				IsExist() const;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	virtual intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;

private:
			LOCKABLE<CONTAINER>				m_listExecutable;
			typename CONTAINER::iterator	m_iterNow;
};


}

#include "CGExecuteclasses/CGExecutableList.inl"