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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
#pragma once

//-----------------------------------------------------------------------------
//
// CGD::locked_identity<ISIZE>
//
// 1. CGD::locked_identity<ISIZE>��??
//    1) �⺻������ CGD::identity�� ���������� Thread safe�ϰ� �����Ѵٴ� �͸�
//       ���̰� �ִ�.
//    2) ���� ���ϼ��� ���������� ���� ������ �������� �ʴ´�.
//       *���� �������� �����ϱ⸦ ���Ѵٸ� CGD::seat�� ����϶�
//
// 2. ����
//    1) �ִ� ���� template�� ���ڸ� �Ѱ� �����Ѵ�. 
//
//       locked_identity<200>   tempseat;
//
//    2) ���� �Ҵ�ޱ� ���ؼ��� alloc()�Լ��� ����϶�.
//
//       int value = tempseat.alloc();
//
//    3) ���� ����� �������� free()�Լ��� ����Ͽ� ���� ��ȯ�Ѵ�.
//
//       tempseat.free(value);
//
//    4) ������ �Լ��� ����Ͽ� ���� ���¸� Ȯ���� �� �ִ�.
//       size()   <- ���� ���� �ִ� seat�� ����
//       max_size <- �ִ� seat�� �� ����� template ���ڷ� �־��� ���̴�.
//       empty()  <- ������ ��� �ִ����� Ȯ���ϴ� �Լ�.
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
	// 1) Alloc�� Free
			int			alloc_seat();
			void		free_seat(int _iSeat);

	// 2) Clear
			void		reset();

	// 3) Size�� Max_size
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