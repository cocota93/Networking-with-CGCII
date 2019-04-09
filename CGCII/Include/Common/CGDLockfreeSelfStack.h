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
// CGD::lockfree_self_stack<T>
//
// 1. CGD::lockfree_self_stack<T>란!
//    1) CAS atomic함수를 사용하여 제작한 Lock-Free stack이다.
//    2) ABA문제 해결을 위해 64Bit CAS를 사용하였다.
//    3) head의 내용 중 wDepth는 Stack된 Item의 갯수를 의미한다.
//    4) head의 내용 중 wSequence는 ABA문제 해결을 위해 Operation마다 증가한다.
//    5) 파라메터로 받는 T의 형은 반드시 포인터형이여만 한다.
//       포인터가 아니면 절대로 동작하지 않을 수 있다.
//    6) 자체적인 node를 생성하지 않고 객체를 직접 node로 사용한다.
//       따라서 포인터 이외에 다른 형태는 stack되지 않으면 또 같은 객체를 
//       동시에 2개의 lockfree_self_stack에 넣을 수 없다.
//
// 2. 특징
//
//    1) 장점
//       - 매우 빠르다.
//       - Lock Fee의 특성상 Dead lock의 염려를 줄일 수 있다.
//
//    2) 단점
//       - Lock Free는 순차 운행을 하거나 검색을 할수 없다.
//       - 단지 push와 pop을 수행할 때 Thread-safe할 뿐이다. Thread-safe한
//         운행(Traverse)가 필요할 경우 ciriticalsection을 사용한 queue를 
//         사용할 것을 권한다.
//       - node를 따로 생성하지 않기 때문에 동시에 두개의 lockfree_self_stack에
//         넣을 수 없다.
//       - data는 반드시 volatile long형의 Next 변수가 필요로 한다.
//
//
//-----------------------------------------------------------------------------
namespace CGD
{

template<class TDATA, unsigned IBYTES=sizeof(TDATA*)>
class lockfree_self_stack	{};

template <class TDATA>
class lockfree_self_stack<TDATA, 4>
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type			Contain에 담긴 값들의 형.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:iterator			순회할 때 사용되는 반복자.
//     5) X:const_iterator		순회할 때 사용되는 반복자(const형)
//     6) X:difference_type		두 iterator에 담김 값의 거리를 나타내는 타입.
//     7) X:size_type			X의 크기를 나타낼때 사용되는 형.
//
// ----------------------------------------------------------------------------
public:
	// Standard 1) value type.
	typedef TDATA				value_type;

	// Standard 2) Pointer.
	typedef TDATA*				pointer;
	typedef const TDATA*		const_pointer;

	// Standard 3) Reference.
	typedef TDATA&				reference;
	typedef const TDATA&		const_reference;

	// Standard 4) size of type & difference type.
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;

	// Self) 자기자신(표준 아님.)
	typedef	lockfree_self_stack<TDATA>		_mytype;

	// Rebinder) 
	template <class TOTHER_DATA>	
	struct rebind
	{
		typedef lockfree_self_stack<TOTHER_DATA> other;
	};


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			lockfree_self_stack()											{	clear();}
			~lockfree_self_stack()											{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 상태 Function
			size_t				size() const;

	// 2) stack을 모조리 비우는 함수.
			void				clear();

	// 3) 동작 Function
			void				push(TDATA _pData);
			TDATA				pop();
			TDATA				pop_all();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			union CGSLIST_HEAD
			{
				int64_t			alligned;

				struct
				{
				TDATA			pHead;
				unsigned short	wDepth;
				unsigned short	wSequence;
				} partial;
			};

	volatile CGSLIST_HEAD 		m_Head;
};


template <class TDATA>
size_t lockfree_self_stack<TDATA, 4>::size() const
{
	return	m_Head.partial.wDepth;
}

template <class TDATA>
void lockfree_self_stack<TDATA, 4>::clear()
{
	pop_all();
}

template <class TDATA>
void lockfree_self_stack<TDATA, 4>::push(TDATA _pData)
{
#pragma warning(disable:26494)
	// Check) 
	CGASSERT_ERROR(m_Head.partial.pHead!=_pData);

	// Declare)
	CGSLIST_HEAD	tempHead;
	CGSLIST_HEAD	tempNewHead;

	do
	{
		// 1) 기존 head를 얻어놓는다.
		tempHead.alligned		 = m_Head.alligned;

		// 2) Next를 미리 맞춰놓느다.
		_pData->Next			 = m_Head.partial.pHead;

		// 3) _pData의 Next를 지금의 head로 설정해놓는다.
		tempNewHead.partial.pHead		 = _pData;
		tempNewHead.partial.wDepth		 = tempHead.partial.wDepth+1;
		tempNewHead.partial.wSequence	 = tempHead.partial.wSequence+1;

		// 4) head랑 바꾼다.(바뀔 때까지..)
	} while(_InterlockedCompareExchange64(&m_Head.alligned, tempNewHead.alligned, tempHead.alligned)!=tempHead.alligned);
#pragma warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 4>::pop()
{
#pragma warning(disable:26494)
	//-----------------------------------------------------------------
	// 1. Pop한다.
	//-----------------------------------------------------------------
	// Declare) 
	CGSLIST_HEAD	tempHead;
	CGSLIST_HEAD	tempNewHead;

	// 1) CAS로 제거한다.
	do
	{
		// 1) 일단 head를 얻어놓는다.(Return해줄 것이다.)
		tempHead.alligned		 = m_Head.alligned;

		// Check)
		if(tempHead.partial.pHead==0)
		{
			return	0;
		}

		// 2) 얻은 head의 Next가 새로운 head가 될 것이다.
		tempNewHead.partial.pHead		 = tempHead.partial.pHead->Next;
		tempNewHead.partial.wDepth		 = tempHead.partial.wDepth-1;
		tempNewHead.partial.wSequence	 = tempHead.partial.wSequence+1;

		// 3) head랑 바꾼다.(바뀔 때까지..)
	} while(_InterlockedCompareExchange64(&m_Head.alligned, tempNewHead.alligned, tempHead.alligned)!=tempHead.alligned);

	// Return) 되돌린다#

	return	tempHead.partial.pHead;
#pragma warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 4>::pop_all()
{
#pragma warning(disable:26494)
	CGSLIST_HEAD	tempHead;
	CGSLIST_HEAD	tempNewHead;

	// 1) CAS로 전체를 떼낸다.
	do
	{
		// - 일단 head를 얻어놓는다.
		tempHead.alligned		 = m_Head.alligned;

		tempNewHead.partial.pHead		 = 0;
		tempNewHead.partial.wDepth		 = 0;
		tempNewHead.partial.wSequence	 = tempHead.partial.wSequence+1;

	} while(_InterlockedCompareExchange64(&m_Head.alligned, tempNewHead.alligned, tempHead.alligned)!=tempHead.alligned);

	// Return) head를 되돌린다.
	return	tempHead.partial.pHead;
#pragma warning(default:26494)
}


}
