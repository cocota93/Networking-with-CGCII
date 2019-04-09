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
// CGD::seat
//
// 1. CGD::seat��!
//     ���� Room�� ���� ���� ������ �� ������� ������ ���� �¼���ȣ�� �Ҵ���
//    �ʿ��� ��찡 ����� ����. 
//     ���� ��� ��ü 8�ڸ��� �ִ� ���� ��� ����ڰ� ��������ϰ� �Ǹ� �����
//    ���������� ���ų� ��� ���� �ƴ϶� �߰� �߰� �¼��� ��ų� ���ų� �Ѵ�.
//    �̶� �Խ��� �Ҷ����� ���ڸ��� ã���� �ϴ� ������ �ʿ�� �Ѵ�. �̶�
//    seat�� ���� ���ȣ�� stack���·� �����ϰ� �ִٰ� ����ִ� �ڸ��� ���
//    ������ �ش�.
//
//    - ���ȣ�� �Ҵ��� ���� ��ȣ���� ���� ��ȣ�� �Ҵ��� ���ش�.
//    - �Ҵ�� ��ȣ�� �ٽ� �ǵ��� ���� �� Sort�� �Ͼ��.
//    - �¼���ȣ�� ������ ��Ҵ� �����ϴ�.
//      * ������ �Ҷ��� �̹� �Ҵ�� ��ȣ ������ ���� stack�� �ϸ�
//      * ���Ҹ� �Ҷ��� stack�� ���ҵ� �¼���ȣ ���� ������ stack���� ã��
//        �����Ѵ�. �̹� �Ҵ�� ���� �ٽ� free�Ǿ� ���ƿ��� �� stack�� ���� 
//        �ʴ´�.
//
//
// 2. CGD::seat�� ǥ�� �ؼ� ����
//    1) create_seat
//       - ���� seat�� �����Ѵ�.(�Ϲ������� ó�� �ѹ��� �����Ѵ�.)
//       - �ѹ� ������ ���Ŀ� ���� ������ ���� ���̸�ŭ�� �¼��� �����Ѵ�.
//    2) reset_seat
//       - seat�� clear�ϰ� �ٽ� �����Ѵ�. �̵� �̹� �Ҵ�Ǿ seat�� �ٽ�
//         ���ƿ� ��� ������ ���� �� �����Ƿ� �����ؾ��Ѵ�.
//    3) alloc_seat
//       - ���ο� seat�� �Ҵ����ش�. stack���� ���� ���� seat ��ȣ�� �Ҵ����ش�.
//    4) free_seat
//       - �Ҵ��seat�� �ǵ��� �޴´�.
//       - �ǵ��� ������ sort�� �����Ѵ�.
//
// 3. �߰����� or ��뿹��
//
//
//-----------------------------------------------------------------------------
#include "CGD/CGDDefinitions.h"

namespace CGD
{

class seat 
{
// ****************************************************************************
// Common Container Standard)
// ----------------------------------------------------------------------------
public:
			seat() : m_begin(0), m_step(0) 								{}
			seat(int _maxcount, int _begin=0, int _step=1) : m_begin(_begin), m_step(_step)	{	create(_maxcount, _begin, _step);}


// ****************************************************************************
// Public Interface)
// ----------------------------------------------------------------------------
public:
	// 1) Seat Create & Reset
	inline	void			create(int _max_seat_count, int _begin=0, int _step=1);
	inline	void			reset();

	// 2) Seat Alloc & Free
	inline	int				alloc_seat();
	inline	void			free_seat(int _seat);

	// 3) Status
			int				remained_seat() const						{	return static_cast<int>(m_vectorSeat.size())-1;}
			size_t			max_seat() const							{	return static_cast<int>(m_vectorSeat.capacity())-1;}
			bool			empty() const								{	return m_vectorSeat.size()==1;}

	// 4) Info
			int				begin() const								{	return m_begin;}
			int				step() const								{	return m_step;}


// ****************************************************************************
// Member Variable) 
// ----------------------------------------------------------------------------
private:
			int				m_begin;
			int				m_step;
			vector<int>		m_vectorSeat;
};

int seat::alloc_seat()
{
	// 1) ��� ������ Seat�� 0���̸� -1�� �Ѵ�.
	if(empty())
	{
		return	-1;
	}

	// Declare) �����ٰ�
	int	seat_return	 = m_vectorSeat[1];

	// 2) Down Heap
	int	value	 = m_vectorSeat.back();

	int	parent	 = 1;
	int	child	 = 2;
	int	end		 = static_cast<int>(m_vectorSeat.size())-2;

	while(child<=end)
	{
		if(child<end && m_vectorSeat[child]>m_vectorSeat[child+1])
			++child;

		if(value<=m_vectorSeat[child])	
			break;

		m_vectorSeat[parent]	 = m_vectorSeat[child];

		parent	 = child;
		child	<<= 1;
	}
	m_vectorSeat[parent]	 = value;
	m_vectorSeat.pop_back();

	// Return) 
	return	seat_return;
}

void seat::free_seat(int _seat)
{
	// 1) child...
	int	child	 = static_cast<int>(m_vectorSeat.size());

	// 2) �������� Push�Ѵ�.
	m_vectorSeat.push_back(_seat);

	// 3) Up Heap
	int	parent	 = (child>>1);
	while(parent && m_vectorSeat[parent]>_seat)
	{
		m_vectorSeat[child]	 = m_vectorSeat[parent];

		child = parent;
		parent>>=1;
	}
	m_vectorSeat[child]	 = _seat;
}

void seat::create(int _max_seat_count, int _begin, int _step)
{
	// Check) p_iMaxSeatCount�� 0������ Ȯ���Ѵ�.
	if(_max_seat_count==0)
	{
		return;
	}

	// Check) p_iMaxSeatCount�� 0������ Ȯ���Ѵ�.
	if(_step<1)
	{
		return;
	}

	// Check) p_iMaxSeatCount�� 0������ Ȯ���Ѵ�.
	if(_max_seat_count<_step)
	{
		return;
	}

	// 1) ���� �����Ѵ�.
	m_vectorSeat.reserve(_max_seat_count+1);

	// 2) Step�� �����Ѵ�.
	m_begin	 = _begin;
	m_step	 = _step;

	// 3) ��� �����.
	reset();
}

void seat::reset()
{
	// 1) �ϴ� clear�Ѵ�.
	m_vectorSeat.clear();

	// 2) �����Ѵ�.
	int	i	 = begin()-m_step;
	int	end	 = static_cast<int>(max_seat());

	// 3) Push back~~
	for(;i<end;i+=m_step)
	{
		m_vectorSeat.push_back(i);
	}
}


}