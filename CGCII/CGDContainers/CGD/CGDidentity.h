//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 6.1 / Release 2012.05.28                        *
//*                                                                           *
//*                           Data Template Classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangducks@gmail.com          *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                           http://www.CGDK.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGD::identity<ISIZE>
//
// 1. CGD::identity<ISIZE>��??
//    1) �� �״�� ISIZE��ŭ�� ������ȣ�� �Ҵ����ִ� �������̴�. 
//    2) alloc�� ȣ��Ǹ� 0~(ISIZE-1) ���̿��� �Ҵ���� ���� ��ȣ�� �����ش�.
//    3) free�� �Ҵ�޾Ҵ� ��ȣ�� ��ȯ�Ǹ� ���ѵ� ������ȣ�� ������ �ٽ� �Ҵ�
//       �Ǿ����� �Ϳ� ���ȴ�.
//    4) ���̻� �Ҵ��� ������ȣ�� ������ -1�� return�ȴ�.
//    5) ������ Container�δ� seat�� �ִ�. seat�� �ٸ� ���� ������ȣ�� sort����
//       ���� �ʴ´ٴ� ���̴�. seat�� �Ҵ���� ���� ��ȣ �߿��� ���� ���� ��ȣ��
//       �Ҵ��������� �� identity�� �׷��� �ʴ�.
//
// 2. ����
//    1) �ִ� ���� template�� ���ڸ� �Ѱ� �����Ѵ�. 
//
//       locked_identity<200>   tempseat;
//
//    2) ���� �Ҵ�ޱ� ���ؼ��� alloc()�Լ��� ����϶�.
//       (�̶� ��� seat�� �� ����Ͽ� ���̻� �Ҵ��� seat�� ���� �ô� -1�� �����Ѵ�.)
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
// 2. ������
//    1) �� Container�� alloc�� free�� �Ҷ� Thread-Safe���� �ʴ�. �׷��Ƿ�
//       ���࿡ Thread-Safe�ϰ� ���۽�Ű���� �Ѵٸ� Lock�� �ɾ� ����ؾ� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
#include "CGD/CGDDefinitions.h"

namespace CGD
{

template <int ISIZE, int IMIN=0, int ISTEP=1, int IEMPTYCODE=-1>
class identity
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			identity()	{	reset();}
			~identity()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Alloc�� Free
			int			alloc_seat();
			void		free_seat(int p_iSeat);

	// 2) Clear
			void		reset();

	// 3) Size�� Max_size
			int			size() const								{	return m_stacked;}
			int			max_size() const							{	return ISIZE;}
			int			min_value() const							{	return IMIN;}
			int			max_value() const							{	return IMIN+ISTEP*(ISIZE-1);}
			int			empty_code() const							{	return IEMPTYCODE;}
			int			step() const								{	return ISTEP;}
			bool		empty() const								{	return (size()==0);}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			int			m_arrayStack[ISIZE];
			int			m_stacked;
};


template <int ISIZE, int IMIN, int ISTEP, int IEMPTYCODE>
int identity<ISIZE, IMIN, ISTEP, IEMPTYCODE>::alloc_seat()
{
	// Check) Empty�̸� IEMPTYCODE�� Return�Ѵ�.
	if(empty())
	{
		return	IEMPTYCODE;
	}

	// 1) Seat���� Pop�ؼ� �ǵ�����.
	return	m_arrayStack[--m_stacked];
}

template <int ISIZE, int IMIN, int ISTEP, int IEMPTYCODE>
void identity<ISIZE, IMIN, ISTEP, IEMPTYCODE>::free_seat(int p_iSeat)
{
	m_arrayStack[m_stacked++]	 = p_iSeat;
}

template <int ISIZE, int IMIN, int ISTEP, int IEMPTYCODE>
void identity<ISIZE, IMIN, ISTEP, IEMPTYCODE>::reset()
{
	// 1) �ϴ� clear�Ѵ�.
	m_stacked	 = ISIZE;

	// 2) Seat���� 0���� SIZE-1���� ������ �ִ´�.
	for(int i=0, value=max_value(); i<ISIZE; ++i,value-=ISTEP)
	{
		m_arrayStack[i]	 = value;
	}
}


}
