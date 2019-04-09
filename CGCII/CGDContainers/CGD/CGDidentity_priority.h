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

template <int ISIZE>
class identity_priority
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			identity_priority()										{	reset();}
			~identity_priority()									{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Alloc�� Free
			int			alloc_identity();
			void		free_identity(int p_iSeat);

	// 2) Clear
			void		reset();

	// 3) Size�� Max_size
			int			size() const								{	return m_iQueued-1;}
			int			max_size() const							{	return ISIZE;}
			bool		empty() const								{	return (size()==0);}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			int			m_arrayQueue[ISIZE+1];
			int			m_iQueued;
};

template <int ISIZE>
int identity_priority<ISIZE>::alloc_identity()
{
	// Check) Empty�̸� -1�� Return�Ѵ�.
	if(empty())
	{
		return	-1;
	}

	// Declare) �����ٰ�
	int	iReturn	 = m_arrayQueue[1];

	// 2) Down Heap
	int	value	 = m_arrayQueue[--m_iQueued];

	int	parent	 = 1;
	int	child	 = 2;
	int	end		 = m_iQueued-1;

	while(child<=end)
	{
		if(child<end && m_arrayQueue[child]>m_arrayQueue[child+1])
			++child;

		if(value<=m_arrayQueue[child])	
			break;

		m_arrayQueue[parent]	 = m_arrayQueue[child];

		parent	 = child;
		child	<<= 1;
	}
	m_arrayQueue[parent]	 = value;

	// Return) 
	return	iReturn;
}

template <int ISIZE>
void identity_priority<ISIZE>::free_identity(int p_iSeat)
{
	// 1) ���� Stack�� ��ġ�� ���Ѵ�.
	int	child	 = m_iQueued++;

	// 2) Up Heap
	int	parent	 = (child>>1);
	while(parent && m_arrayQueue[parent]>p_iSeat)
	{
		m_arrayQueue[child]	 = m_arrayQueue[parent];

		child = parent;
		parent>>=1;
	}
	m_arrayQueue[child]	 = p_iSeat;
}

template <int ISIZE>
void identity_priority<ISIZE>::reset()
{
	// 1) �ϴ� clear�Ѵ�.
	m_iQueued	 = ISIZE+1;

	// 2) Seat���� 0���� SIZE-1���� ������ �ִ´�.
	int*	pStack	 = m_arrayQueue+1;
	for(int i=0; i<ISIZE;++i, ++pStack)
	{
		*pStack	 = i;
	}
}


}