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
// CGD::lockfree_queue<T>
//
// 1. CGD::lockfree_queue은?
//     CAS를 이용한 Lock Free로 Thread-Safe한 queue를 구현한 것이다.
//    Queue에 대한 기본적인 Lock-Free는 기존과 큰 차이가 없고 다만 추가 혹은 삭제
//    를 수행할 때 new나 delete를 하지 않고 stack으로 만들어진 Pool을 사용한다는
//    것이 특이하다.
//     기본적으로 Lock Free인데다가 new나 delete같은 동적할당을 하지 않기 때문에
//    기존의 Critical Section을 사용한 queue보다 월등하게 빠른 속도를 자랑한다.
//
// 2. CGD::lockfree_queue의 동작설명!!
//    1) 일반적인 Push/Pop을 수행하는 Queue이다.
//    2) 장점
//       - 엄청 빠르다는 장점이 있다.
//    3) 단점
//       - 기본적으로 Lock Free는 순차 운행을 하거나 검색을 할수 없다.
//         그런 것을 안전하게 하려면 Critical Section을 사용한 queue나 stack을
//         사용하는 것이 맞을 것이다. 
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
	// 1) pop함수)
			TDATA			pop();
			bool			pop(TDATA& _data);

	// 2) push함수.
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


	// 1) Item을 저장할 Array
	static 	LOCKFREE_SELF_STACK<SNode*>	m_stackNode;

	// 2) Queue의 시작과 끝을 나타내는 위치...
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
	// 1. 할당한다.
	//-----------------------------------------------------------------
	// Declare) 임시 변수.
	SNode*	tempHead;
	SNode*	tempNext;

	// 1) 뽑아낼 때까지 돌린다.
	do
	{
		// - head와 head의 Next를 얻어놓는다.
		tempHead	 = (SNode*)m_pHead;
		tempNext	 = (SNode*)tempHead->Next;

		// Check) tempNext(m_pHead->Next)가 0이면 더이상 queuing된
		//        것이 없다는 뜻이므로 그냥 끝낸다.
		if(tempNext==0)
		{
			return	0;
		}

	} while(InterlockedCompareExchangePointer((volatile PVOID*)&m_pHead, tempNext, tempHead)!=tempHead);

	// 2) 앞 Node를 Stack에 다시 넣는다.
	m_stackNode.push(tempHead);


	// Return) 성공!!
	return	tempNext->_data;
#pragma  warning(default:26494)
}

template <class TDATA>
bool lockfree_queue<TDATA>::pop(TDATA& _data)
{
#pragma warning(disable:26494)
	//-----------------------------------------------------------------
	// 1. 할당한다.
	//-----------------------------------------------------------------
	// Declare) 임시 변수.
	SNode*	tempHead;
	SNode*	tempNext;

	// 1) 뽑아낼 때까지 돌린다.
	do
	{
		// - head와 head의 Next를 얻어놓는다.
		tempHead	 = (SNode*)m_pHead;
		tempNext	 = (SNode*)tempHead->Next;

		// Check) tempNext(m_pHead->Next)가 0이면 더이상 queuing된
		//        것이 없다는 뜻이므로 그냥 끝낸다.
		if(tempNext==0)
		{
			return	false;
		}

	} while(InterlockedCompareExchangePointer((volatile PVOID*)&m_pHead, tempNext, tempHead)!=tempHead);

	// 2) 앞 Node를 Stack에 다시 넣는다.
	m_stackNode.push(tempHead);

	// 3) 값을 복사한다.
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
	// 1. 삽입할 Node를 준비한다.
	//-----------------------------------------------------------------
	// 1) 빈 Node를 하나 얻는다.
	SNode*	tempNode	 = getNewNode();

	// 2) 빈 Node에 값을 써을 넣고 Next를 0로 설정한다.
	tempNode->_data	 = _pData;
	tempNode->Next	 = 0;


	//-----------------------------------------------------------------
	// 2. Node를 삽입한다.
	//-----------------------------------------------------------------
	// Declare) back값...(임시로 쓸거..)
	SNode*	ptempTailNode;

	// 1) 넣을 때까지 돌린다.(m_pTail이 m_pTail일때만 바꾼다.)
	do
	{
		ptempTailNode	 = (SNode*)m_pTail;
	}while(InterlockedCompareExchangePointer((volatile PVOID*)&m_pTail, tempNode, ptempTailNode)!=ptempTailNode);

	// 2) back에 붙이기를 성공했다면 기존 tail의 Next를 tempNode로 설정함.
	ptempTailNode->Next	 = tempNode;
#pragma  warning(default:26494)
}


template <class TDATA>
void lockfree_queue<TDATA>::clear()
{
#pragma warning(disable:26494)
	for(;;)
	{
		// Declare) 임시 변수.
		SNode*	tempHead;
		SNode*	tempNext;

		do
		{
			// - head와 head의 Next를 얻어놓는다.
			tempHead	 = (SNode*)m_pHead;
			tempNext	 = (SNode*)tempHead->Next;

			// Check) tempNext(m_pHead->Next)가 0이면 더이상 queuing된
			//        것이 없다는 뜻이므로 그냥 끝낸다.
			if(tempNext==0)
			{
				return;
			}

		} while(InterlockedCompareExchangePointer((volatile PVOID*)&m_pHead, tempNext, tempHead)!=tempHead);

		// 2) 앞 Node를 Stack에 다시 넣는다.
		m_stackNode.push(tempHead);

		// 3) 값을 Destroy한다.
		tempNext->_data.~TDATA();
	}
#pragma  warning(default:26494)
}


}