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
// CGD::lockfree_self_stack<TDATA, 8>
//
// 1. CGD::lockfree_self_stack<TDATA, 8>��!
//    1) 64Bit �����͸� ���� CAS atomic�Լ��� ����Ͽ� ������ Lock-Free stack�̴�.
//    2) �⺻���� ����� CGD::lockfree_self_stack�� �����ϴ�. �ٸ� 64bit �����͸� 
//       �����ϴ°͸��� �������̴�.
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
//     1) X:value_type			Contain�� ��� ������ ��.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:difference_type		�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     5) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
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

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
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
	// 1) ���� Function
			size_type			size() const							{return (size_type)m_Head.Header.dwDepth;}

	// 2) stack�� ������ ���� �Լ�.
			void				clear();

	// 3) ���� Function
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
		// 1) ���� head�� �����´�.
		tempHead.alligned.lLow			 = m_Head.alligned.lLow;
		tempHead.alligned.lHigh			 = m_Head.alligned.lHigh;

		// 2) Next�� �̸� ���������.
		_pData->Next = m_Head.Header.pHead;

		// 3) _pData�� Next�� ������ head�� �����س��´�.
		tempNewHead.Header.pHead		 = _pData;
		tempNewHead.Header.dwDepth		 = tempHead.Header.dwDepth+1;
		tempNewHead.Header.dwSequence	 = tempHead.Header.dwSequence+1;

		// 4) head�� �ٲ۴�.(�ٲ� ������..)
	}while(_InterlockedCompareExchange128(&m_Head.alligned.lLow, tempNewHead.alligned.lHigh, tempNewHead.alligned.lLow, &tempHead.alligned.lLow)==0);
#pragma  warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 8>::pop()
{
#pragma warning(disable:26494)

	//-----------------------------------------------------------------
	// 1. Pop�Ѵ�.
	//-----------------------------------------------------------------
	// Declare)
	CGSLIST_HEAD tempHead;
	CGSLIST_HEAD tempNewHead;

	// 1) CAS�� �����Ѵ�.
	do
	{
		// 1) �ϴ� head�� �����´�.(Return���� ���̴�.)
		tempHead.alligned.lLow = m_Head.alligned.lLow;
		tempHead.alligned.lHigh = m_Head.alligned.lHigh;

		// Check)
		if(tempHead.Header.pHead==0)
		{
			return 0;
		}

		// 2) ���� head�� Next�� ���ο� head�� �� ���̴�.
		tempNewHead.Header.dwDepth = tempHead.Header.dwDepth-1;
		tempNewHead.Header.dwSequence = tempHead.Header.dwSequence+1;
		tempNewHead.Header.pHead = tempHead.Header.pHead->Next;

		// 3) head�� �ٲ۴�.(�ٲ� ������..)
	}while(_InterlockedCompareExchange128(&m_Head.alligned.lLow, tempNewHead.alligned.lHigh, tempNewHead.alligned.lLow, &tempHead.alligned.lLow)==0);

	// Return) �ǵ�����.
	return tempHead.Header.pHead;
#pragma  warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 8>::pop_all()
{
#pragma warning(disable:26494)
	CGSLIST_HEAD tempHead;
	CGSLIST_HEAD tempNewHead;

	// 1) CAS�� ��ü�� ������.
	do
	{
		// - �ϴ� head�� �����´�.
		tempHead.alligned.lLow = m_Head.alligned.lLow;
		tempHead.alligned.lHigh = m_Head.alligned.lHigh;

		tempNewHead.Header.dwDepth = 0;
		tempNewHead.Header.dwSequence = tempHead.Header.dwSequence+1;
		tempNewHead.Header.pHead = 0;

	}while(_InterlockedCompareExchange128(&m_Head.alligned.lLow, tempNewHead.alligned.lHigh, tempNewHead.alligned.lLow, &tempHead.alligned.lLow)==0);

	// Return) head�� �ǵ�����.
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
	//     1) X:value_type			Contain�� ��� ������ ��.
	//     2) X:reference			X:value_type&.
	//     3) X:const_reference		const X:value_type&.
	//     4) X:difference_type		�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
	//     5) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
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

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
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
	// 1) ���� Function
			size_type			size() const 							{ return m_count;}

	// 2) stack�� ������ ���� �Լ�.
			void				clear();

	// 3) ���� Function
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

	// Return) head�� �ǵ�����.
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

	// Return) head�� �ǵ�����.
	return pData;
#pragma  warning(default:26494)
}

#endif

}
