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
// CGD::lockfree_queue<T>
//
// 1. CGD::lockfree_queue��?
//     CAS�� �̿��� Lock Free�� Thread-Safe�� queue�� ������ ���̴�.
//    Queue�� ���� �⺻���� Lock-Free�� ������ ū ���̰� ���� �ٸ� �߰� Ȥ�� ����
//    �� ������ �� new�� delete�� ���� �ʰ� stack���� ������� Pool�� ����Ѵٴ�
//    ���� Ư���ϴ�.
//     �⺻������ Lock Free�ε��ٰ� new�� delete���� �����Ҵ��� ���� �ʱ� ������
//    ������ Critical Section�� ����� queue���� �����ϰ� ���� �ӵ��� �ڶ��Ѵ�.
//
// 2. CGD::lockfree_queue�� ���ۼ���!!
//    1) �Ϲ����� Push/Pop�� �����ϴ� Queue�̴�.
//    2) ����
//       - ��û �����ٴ� ������ �ִ�.
//    3) ����
//       - �⺻������ Lock Free�� ���� ������ �ϰų� �˻��� �Ҽ� ����.
//         �׷� ���� �����ϰ� �Ϸ��� Critical Section�� ����� queue�� stack��
//         ����ϴ� ���� ���� ���̴�. 
//
//
//-----------------------------------------------------------------------------
namespace CGD
{

template <class TDATA>
class lockfree_queue
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			lockfree_queue();
	virtual	~lockfree_queue();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) pop�Լ�)
			TDATA			pop();
			bool			pop(TDATA& _data);

	// 2) push�Լ�.
			void			push(const TDATA& _pData);

	// 3) clear
			void			clear();



// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	struct SNode
	{
		TDATA	_data;
		SNode*	Next;
	};


	// 1) Item�� ������ Array
	static 	LOCKFREE_SELF_STACK<SNode*>	m_stackNode;

	// 2) Queue�� ���۰� ���� ��Ÿ���� ��ġ...
	volatile void*			m_pHead;
	volatile void*			m_pTail;

private:
			SNode*			getNewNode();
};


// Static Member>
template <class TDATA>
LOCKFREE_SELF_STACK<typename lockfree_queue<TDATA>::SNode*>	lockfree_queue<TDATA>::m_stackNode;

template <class TDATA>
lockfree_queue<TDATA>::lockfree_queue()
{
#pragma warning(disable:26494)
	SNode*	ptempNoe	 = getNewNode();
	ptempNoe->Next		 = 0;

	m_pHead	 = ptempNoe;
	m_pTail	 = ptempNoe;
#pragma warning(disable:26494)
}

template <class TDATA>
lockfree_queue<TDATA>::~lockfree_queue()
{
	try
	{
		clear();
	}
	catch (...)
	{
	}
}


template <class TDATA>
typename lockfree_queue<TDATA>::SNode* lockfree_queue<TDATA>::getNewNode()
{
#pragma warning(disable:26494)
	SNode*	tempNode	 = m_stackNode.pop();

	if(tempNode==0)
	{
		tempNode	 = new SNode;
	}

	return	tempNode;
#pragma  warning(default:26494)
}


template <class TDATA>
TDATA lockfree_queue<TDATA>::pop()
{
#pragma warning(disable:26494)
	//-----------------------------------------------------------------
	// 1. �Ҵ��Ѵ�.
	//-----------------------------------------------------------------
	// Declare) �ӽ� ����.
	SNode*	tempHead;
	SNode*	tempNext;

	// 1) �̾Ƴ� ������ ������.
	do
	{
		// - head�� head�� Next�� �����´�.
		tempHead	 = (SNode*)m_pHead;
		tempNext	 = (SNode*)tempHead->Next;

		// Check) tempNext(m_pHead->Next)�� 0�̸� ���̻� queuing��
		//        ���� ���ٴ� ���̹Ƿ� �׳� ������.
		if(tempNext==0)
		{
			return	0;
		}

	} while(InterlockedCompareExchangePointer((volatile PVOID*)&m_pHead, tempNext, tempHead)!=tempHead);

	// 2) �� Node�� Stack�� �ٽ� �ִ´�.
	m_stackNode.push(tempHead);


	// Return) ����!!
	return	tempNext->_data;
#pragma  warning(default:26494)
}

template <class TDATA>
bool lockfree_queue<TDATA>::pop(TDATA& _data)
{
#pragma warning(disable:26494)
	//-----------------------------------------------------------------
	// 1. �Ҵ��Ѵ�.
	//-----------------------------------------------------------------
	// Declare) �ӽ� ����.
	SNode*	tempHead;
	SNode*	tempNext;

	// 1) �̾Ƴ� ������ ������.
	do
	{
		// - head�� head�� Next�� �����´�.
		tempHead	 = (SNode*)m_pHead;
		tempNext	 = (SNode*)tempHead->Next;

		// Check) tempNext(m_pHead->Next)�� 0�̸� ���̻� queuing��
		//        ���� ���ٴ� ���̹Ƿ� �׳� ������.
		if(tempNext==0)
		{
			return	false;
		}

	} while(InterlockedCompareExchangePointer((volatile PVOID*)&m_pHead, tempNext, tempHead)!=tempHead);

	// 2) �� Node�� Stack�� �ٽ� �ִ´�.
	m_stackNode.push(tempHead);

	// 3) ���� �����Ѵ�.
	_data	 = tempNext->_data;

	// Return) 
	return	true;
#pragma  warning(default:26494)
}


template <class TDATA>
void lockfree_queue<TDATA>::push(const TDATA& _pData)
{
#pragma warning(disable:26494)
	//-----------------------------------------------------------------
	// 1. ������ Node�� �غ��Ѵ�.
	//-----------------------------------------------------------------
	// 1) �� Node�� �ϳ� ��´�.
	SNode*	tempNode	 = getNewNode();

	// 2) �� Node�� ���� ���� �ְ� Next�� 0�� �����Ѵ�.
	tempNode->_data	 = _pData;
	tempNode->Next	 = 0;


	//-----------------------------------------------------------------
	// 2. Node�� �����Ѵ�.
	//-----------------------------------------------------------------
	// Declare) back��...(�ӽ÷� ����..)
	SNode*	ptempTailNode;

	// 1) ���� ������ ������.(m_pTail�� m_pTail�϶��� �ٲ۴�.)
	do
	{
		ptempTailNode	 = (SNode*)m_pTail;
	}while(InterlockedCompareExchangePointer((volatile PVOID*)&m_pTail, tempNode, ptempTailNode)!=ptempTailNode);

	// 2) back�� ���̱⸦ �����ߴٸ� ���� tail�� Next�� tempNode�� ������.
	ptempTailNode->Next	 = tempNode;
#pragma  warning(default:26494)
}


template <class TDATA>
void lockfree_queue<TDATA>::clear()
{
#pragma warning(disable:26494)
	for(;;)
	{
		// Declare) �ӽ� ����.
		SNode*	tempHead;
		SNode*	tempNext;

		do
		{
			// - head�� head�� Next�� �����´�.
			tempHead	 = (SNode*)m_pHead;
			tempNext	 = (SNode*)tempHead->Next;

			// Check) tempNext(m_pHead->Next)�� 0�̸� ���̻� queuing��
			//        ���� ���ٴ� ���̹Ƿ� �׳� ������.
			if(tempNext==0)
			{
				return;
			}

		} while(InterlockedCompareExchangePointer((volatile PVOID*)&m_pHead, tempNext, tempHead)!=tempHead);

		// 2) �� Node�� Stack�� �ٽ� �ִ´�.
		m_stackNode.push(tempHead);

		// 3) ���� Destroy�Ѵ�.
		tempNext->_data.~TDATA();
	}
#pragma  warning(default:26494)
}


}