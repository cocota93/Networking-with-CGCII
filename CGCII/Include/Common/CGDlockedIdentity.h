//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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
//
// CGD::locked_identity<ISIZE>
//
// 1. CGD::locked_identity<ISIZE>란??
//    1) 기본적으로 CGD::identity와 동일하지면 Thread safe하게 동작한다는 것만
//       차이가 있다.
//    2) 값의 유일성은 보장하지만 값의 순서는 보장하지 않는다.
//       *값의 순서까지 보장하기를 원한다면 CGD::seat를 사용하라
//
// 2. 사용법
//    1) 최대 값은 template의 임자를 넘겨 선언한다. 
//
//       locked_identity<200>   tempseat;
//
//    2) 값을 할당받기 위해서는 alloc()함수를 사용하라.
//
//       int value = tempseat.alloc();
//
//    3) 값의 사용이 끝났으면 free()함수를 사용하여 값을 반환한다.
//
//       tempseat.free(value);
//
//    4) 다음의 함수를 사용하여 현재 상태를 확인할 수 있다.
//       size()   <- 현재 남아 있는 seat의 갯수
//       max_size <- 최대 seat의 수 선언시 template 인자로 넣었던 값이다.
//       empty()  <- 완전히 비어 있는지를 확인하는 함수.
//
//
//-----------------------------------------------------------------------------
#include "CGD/CGDDefinitions.h"

namespace CGD
{

template <size_t ISIZE>
class locked_identity
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			locked_identity()	{	reset();}
			~locked_identity()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Alloc와 Free
			int			alloc_seat();
			void		free_seat(int _iSeat);

	// 2) Clear
			void		reset();

	// 3) Size와 Max_size
			size_t		size() const								{	return m_identity.size();}
			size_t		max_size() const							{	return m_identity.max_size();}
			bool		empty() const								{	return m_identity.empty();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			LOCKABLE<identity<ISIZE>>	m_identity;
};

template <size_t ISIZE>
int locked_identity<ISIZE>::alloc_seat()
{
	LOCK(m_identity)
	{
		return	m_identity.alloc_seat();
	}
}

template <size_t ISIZE>
void locked_identity<ISIZE>::free_seat(int _iSeat)
{
	LOCK(m_identity)
	{
		m_identity.free_seat(_iSeat);
	}
}

template <size_t ISIZE>
void locked_identity<ISIZE>::reset()
{
	LOCK(m_identity)
	{
		m_identity.reset();
	}
}


}