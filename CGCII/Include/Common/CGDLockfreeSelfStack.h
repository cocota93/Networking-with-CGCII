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
// CGD::lockfree_self_stack<T>
//
// 1. CGD::lockfree_self_stack<T>��!
//    1) CAS atomic�Լ��� ����Ͽ� ������ Lock-Free stack�̴�.
//    2) ABA���� �ذ��� ���� 64Bit CAS�� ����Ͽ���.
//    3) head�� ���� �� wDepth�� Stack�� Item�� ������ �ǹ��Ѵ�.
//    4) head�� ���� �� wSequence�� ABA���� �ذ��� ���� Operation���� �����Ѵ�.
//    5) �Ķ���ͷ� �޴� T�� ���� �ݵ�� ���������̿��� �Ѵ�.
//       �����Ͱ� �ƴϸ� ����� �������� ���� �� �ִ�.
//    6) ��ü���� node�� �������� �ʰ� ��ü�� ���� node�� ����Ѵ�.
//       ���� ������ �̿ܿ� �ٸ� ���´� stack���� ������ �� ���� ��ü�� 
//       ���ÿ� 2���� lockfree_self_stack�� ���� �� ����.
//
// 2. Ư¡
//
//    1) ����
//       - �ſ� ������.
//       - Lock Fee�� Ư���� Dead lock�� ������ ���� �� �ִ�.
//
//    2) ����
//       - Lock Free�� ���� ������ �ϰų� �˻��� �Ҽ� ����.
//       - ���� push�� pop�� ������ �� Thread-safe�� ���̴�. Thread-safe��
//         ����(Traverse)�� �ʿ��� ��� ciriticalsection�� ����� queue�� 
//         ����� ���� ���Ѵ�.
//       - node�� ���� �������� �ʱ� ������ ���ÿ� �ΰ��� lockfree_self_stack��
//         ���� �� ����.
//       - data�� �ݵ�� volatile long���� Next ������ �ʿ�� �Ѵ�.
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
//     1) X:value_type			Contain�� ��� ������ ��.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:iterator			��ȸ�� �� ���Ǵ� �ݺ���.
//     5) X:const_iterator		��ȸ�� �� ���Ǵ� �ݺ���(const��)
//     6) X:difference_type		�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     7) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
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

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
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
	// 1) ���� Function
			size_t				size() const;

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
		// 1) ���� head�� �����´�.
		tempHead.alligned		 = m_Head.alligned;

		// 2) Next�� �̸� ���������.
		_pData->Next			 = m_Head.partial.pHead;

		// 3) _pData�� Next�� ������ head�� �����س��´�.
		tempNewHead.partial.pHead		 = _pData;
		tempNewHead.partial.wDepth		 = tempHead.partial.wDepth+1;
		tempNewHead.partial.wSequence	 = tempHead.partial.wSequence+1;

		// 4) head�� �ٲ۴�.(�ٲ� ������..)
	} while(_InterlockedCompareExchange64(&m_Head.alligned, tempNewHead.alligned, tempHead.alligned)!=tempHead.alligned);
#pragma warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 4>::pop()
{
#pragma warning(disable:26494)
	//-----------------------------------------------------------------
	// 1. Pop�Ѵ�.
	//-----------------------------------------------------------------
	// Declare) 
	CGSLIST_HEAD	tempHead;
	CGSLIST_HEAD	tempNewHead;

	// 1) CAS�� �����Ѵ�.
	do
	{
		// 1) �ϴ� head�� �����´�.(Return���� ���̴�.)
		tempHead.alligned		 = m_Head.alligned;

		// Check)
		if(tempHead.partial.pHead==0)
		{
			return	0;
		}

		// 2) ���� head�� Next�� ���ο� head�� �� ���̴�.
		tempNewHead.partial.pHead		 = tempHead.partial.pHead->Next;
		tempNewHead.partial.wDepth		 = tempHead.partial.wDepth-1;
		tempNewHead.partial.wSequence	 = tempHead.partial.wSequence+1;

		// 3) head�� �ٲ۴�.(�ٲ� ������..)
	} while(_InterlockedCompareExchange64(&m_Head.alligned, tempNewHead.alligned, tempHead.alligned)!=tempHead.alligned);

	// Return) �ǵ�����#

	return	tempHead.partial.pHead;
#pragma warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 4>::pop_all()
{
#pragma warning(disable:26494)
	CGSLIST_HEAD	tempHead;
	CGSLIST_HEAD	tempNewHead;

	// 1) CAS�� ��ü�� ������.
	do
	{
		// - �ϴ� head�� �����´�.
		tempHead.alligned		 = m_Head.alligned;

		tempNewHead.partial.pHead		 = 0;
		tempNewHead.partial.wDepth		 = 0;
		tempNewHead.partial.wSequence	 = tempHead.partial.wSequence+1;

	} while(_InterlockedCompareExchange64(&m_Head.alligned, tempNewHead.alligned, tempHead.alligned)!=tempHead.alligned);

	// Return) head�� �ǵ�����.
	return	tempHead.partial.pHead;
#pragma warning(default:26494)
}


}
