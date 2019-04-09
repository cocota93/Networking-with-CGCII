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
// CGD::lockfree_self_stack<TDATA, 8>
//
// 1. CGD::lockfree_self_stack<TDATA, 8>란!
//    1) 64Bit 포인터를 위한 CAS atomic함수를 사용하여 제작한 Lock-Free stack이다.
//    2) 기본적인 기능은 CGD::lockfree_self_stack와 동일하다. 다만 64bit 포인터를 
//       지원하는것만이 차이점이다.
//
//-----------------------------------------------------------------------------
namespace CGD {

#if defined(_MSC_VER) // || defined (_M_X64)  _GCC_HAVE_SYNC_COMPARE_AND_SWAP_16==1

template <class TDATA>
class lockfree_self_stack<TDATA, 8>
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type			Contain에 담긴 값들의 형.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:difference_type		두 iterator에 담김 값의 거리를 나타내는 타입.
//     5) X:size_type			X의 크기를 나타낼때 사용되는 형.
//
// ----------------------------------------------------------------------------
public:
// Standard 1) value type.
	typedef TDATA value_type;

	// Standard 2) Pointer.
	typedef TDATA* pointer;
	typedef const TDATA* const_pointer;

	// Standard 3) Reference.
	typedef TDATA& reference;
	typedef const TDATA& const_reference;

	// Standard 4) size of type & difference type.
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	// Self) 자기자신(표준 아님.)
	typedef lockfree_self_stack<TDATA> _mytype;

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
			lockfree_self_stack() {clear();}
			~lockfree_self_stack() {}

// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 상태 Function
			size_type			size() const							{return (size_type)m_Head.Header.dwDepth;}

	// 2) stack을 모조리 비우는 함수.
			void				clear();

	// 3) 동작 Function
	void push(TDATA _pData);
	TDATA pop();
	TDATA pop_all();

// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	union DECLSPEC_ALIGN(16) CGSLIST_HEAD
	{
		struct
		{
			int64_t lLow;
			int64_t lHigh;
		}alligned;

		struct
		{
			uint32_t dwDepth;
			uint32_t dwSequence;
			TDATA pHead;
		}Header;
	};

	volatile CGSLIST_HEAD m_Head;
};

template <class TDATA>
void lockfree_self_stack<TDATA, 8>::clear()
{
	pop_all();
}

template <class TDATA>
void lockfree_self_stack<TDATA, 8>::push(TDATA _pData)
{
#pragma warning(disable:26494)
	// Check)
	CGASSERT_ERROR(m_Head.Header.pHead!=_pData);

	// Declare)
	CGSLIST_HEAD tempHead;
	CGSLIST_HEAD tempNewHead;

	do
	{
		// 1) 기존 head를 얻어놓는다.
		tempHead.alligned.lLow			 = m_Head.alligned.lLow;
		tempHead.alligned.lHigh			 = m_Head.alligned.lHigh;

		// 2) Next를 미리 맞춰놓느다.
		_pData->Next = m_Head.Header.pHead;

		// 3) _pData의 Next를 지금의 head로 설정해놓는다.
		tempNewHead.Header.pHead		 = _pData;
		tempNewHead.Header.dwDepth		 = tempHead.Header.dwDepth+1;
		tempNewHead.Header.dwSequence	 = tempHead.Header.dwSequence+1;

		// 4) head랑 바꾼다.(바뀔 때까지..)
	}while(_InterlockedCompareExchange128(&m_Head.alligned.lLow, tempNewHead.alligned.lHigh, tempNewHead.alligned.lLow, &tempHead.alligned.lLow)==0);
#pragma  warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 8>::pop()
{
#pragma warning(disable:26494)

	//-----------------------------------------------------------------
	// 1. Pop한다.
	//-----------------------------------------------------------------
	// Declare)
	CGSLIST_HEAD tempHead;
	CGSLIST_HEAD tempNewHead;

	// 1) CAS로 제거한다.
	do
	{
		// 1) 일단 head를 얻어놓는다.(Return해줄 것이다.)
		tempHead.alligned.lLow = m_Head.alligned.lLow;
		tempHead.alligned.lHigh = m_Head.alligned.lHigh;

		// Check)
		if(tempHead.Header.pHead==0)
		{
			return 0;
		}

		// 2) 얻은 head의 Next가 새로운 head가 될 것이다.
		tempNewHead.Header.dwDepth = tempHead.Header.dwDepth-1;
		tempNewHead.Header.dwSequence = tempHead.Header.dwSequence+1;
		tempNewHead.Header.pHead = tempHead.Header.pHead->Next;

		// 3) head랑 바꾼다.(바뀔 때까지..)
	}while(_InterlockedCompareExchange128(&m_Head.alligned.lLow, tempNewHead.alligned.lHigh, tempNewHead.alligned.lLow, &tempHead.alligned.lLow)==0);

	// Return) 되돌린다.
	return tempHead.Header.pHead;
#pragma  warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 8>::pop_all()
{
#pragma warning(disable:26494)
	CGSLIST_HEAD tempHead;
	CGSLIST_HEAD tempNewHead;

	// 1) CAS로 전체를 떼낸다.
	do
	{
		// - 일단 head를 얻어놓는다.
		tempHead.alligned.lLow = m_Head.alligned.lLow;
		tempHead.alligned.lHigh = m_Head.alligned.lHigh;

		tempNewHead.Header.dwDepth = 0;
		tempNewHead.Header.dwSequence = tempHead.Header.dwSequence+1;
		tempNewHead.Header.pHead = 0;

	}while(_InterlockedCompareExchange128(&m_Head.alligned.lLow, tempNewHead.alligned.lHigh, tempNewHead.alligned.lLow, &tempHead.alligned.lLow)==0);

	// Return) head를 되돌린다.
	return tempHead.Header.pHead;
#pragma  warning(default:26494)
}

#else

template<class TDATA>
class lockfree_self_stack<TDATA, 8> 
{
	// ****************************************************************************
	// Type definitions for Standard)
	//
	//  * Common Container Requirement
	//     1) X:value_type			Contain에 담긴 값들의 형.
	//     2) X:reference			X:value_type&.
	//     3) X:const_reference		const X:value_type&.
	//     4) X:difference_type		두 iterator에 담김 값의 거리를 나타내는 타입.
	//     5) X:size_type			X의 크기를 나타낼때 사용되는 형.
	//
	// ----------------------------------------------------------------------------
public:
	// Standard 1) value type.
	typedef TDATA value_type;

	// Standard 2) Pointer.
	typedef TDATA* pointer;
	typedef const TDATA* const_pointer;

	// Standard 3) Reference.
	typedef TDATA& reference;
	typedef const TDATA& const_reference;

	// Standard 4) size of type & difference type.
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	// Self) 자기자신(표준 아님.)
	typedef lockfree_self_stack<TDATA> _mytype;

	// Rebinder) 
	template<class TOTHER_DATA>
	struct rebind 
	{
		typedef lockfree_self_stack<TOTHER_DATA> other;
	};

	// ****************************************************************************
	// Constructor/Destructor)
	// ----------------------------------------------------------------------------
public:
			lockfree_self_stack() :m_pHead(nullptr), m_count(0) 		{}
			~lockfree_self_stack() 										{}


	// ****************************************************************************
	// Publics)
	// ----------------------------------------------------------------------------
public:
	// 1) 상태 Function
			size_type			size() const 							{ return m_count;}

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
	LOCKABLE<> m_csHead;
	TDATA m_pHead;
	size_type m_count;
};

template<class TDATA>
void lockfree_self_stack<TDATA, 8>::clear() 
{
	pop_all();
}

template<class TDATA>
void lockfree_self_stack<TDATA, 8>::push(TDATA _pData) 
{
#pragma warning(disable:26494)
	// Check) 
	CGASSERT_ERROR(m_pHead != _pData);

	LOCK(m_csHead)
	{
		_pData->Next = m_pHead;
		m_pHead		 = _pData;

		++m_count;
	}
#pragma  warning(default:26494)
}

template<class TDATA>
TDATA lockfree_self_stack<TDATA, 8>::pop() 
{
#pragma warning(disable:26494)
	// Declare) 
	TDATA pData;

	LOCK(m_csHead)
	{
		pData = m_pHead;

		if (pData == nullptr) 
		{
			return nullptr;
		}

		m_pHead = pData->Next;

		--m_count;
	}

	// Return) head를 되돌린다.
	return pData;
#pragma  warning(default:26494)
}

template<class TDATA>
TDATA lockfree_self_stack<TDATA, 8>::pop_all() 
{
#pragma warning(disable:26494)
	// Declare) 
	TDATA pData;

	LOCK(m_csHead)
	{
		pData = m_pHead;
		m_pHead = nullptr;
		m_count = 0;
	}

	// Return) head를 되돌린다.
	return pData;
#pragma  warning(default:26494)
}

#endif

}
