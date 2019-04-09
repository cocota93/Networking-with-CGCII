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

 @class		CList
 @brief		여러 개의 Executable을 등록해 일정 시간마다 실행해주는 Schedulable객체이다.
 @todo		
 @ref		
 @details	\n
 RegisterExecutable()함수를 사용해 Executable을 등록할 수 있다.
 등록된 Executable들을 일정시간마다 모두 호출해준다.
 등록된 Executable들은 GetIterator()로 접근할 수 있다.

*///-----------------------------------------------------------------------------
template <class TEXECUTABLE=ICGExecutable>
class CList :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGSchedulable::NExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CList(uint32_t _tickGap=1000);
	virtual ~CList();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// Definitions) 
			typedef	circular_list<CGPTR<TEXECUTABLE>>	CONTAINER;
			class ITERATOR;

	// 1) Attach/Detach
	//! @brief '실행 객체'를 등록한다. @param _pExecutable 등록할 '실행 객체' @return true 성공 @return false 실패(이미 존재할 경우 실패한다.)
			bool				RegisterExecutable(_In_ TEXECUTABLE* _pExecutable);
	//! @brief 등록된 '실행 객체'를 해제한다. @param _pExecutable 등록해제할 '실행 객체' @return @return true 성공 @return false 실패(해당 객체가 조재하지 않을 경우 실패한다.)
			bool				UnregisterExecutable(_In_ TEXECUTABLE* _pExecutable);
	//! @brief 등록된 모든 '실행 객체'를 해제한다.
			void				UnregisterAllExecutable();

	// 2) Iterator
	//! @brief	등록된 '실행 객체'들에 접근하기 위한 반복자를 얻는다. @return !nullptr 반복자 @return nullptr 획득 실패
			ITERATOR			GetIterator();

	// 3) ExecutableCount
	//!	@brief 등록된 '실행 객체'의 갯수를 얻는다. @return 등록된 '스케쥴 객체'의 수
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
			LOCKABLE<CONTAINER>	m_listExecutable;
			typename CONTAINER::iterator	m_iterNow;
};


}
}

#include "CGExecuteclasses/CGSchedulableExecutableList.inl"
