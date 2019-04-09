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
// CGD::Interlocked_self_stack<T>
//
// 1. CGD::Interlocked_self_stack��!
//     InterlockedPush/Pop�� ����Ͽ� ������ stack�̴�.
//    LockFree�ϸ鼭 Thread Safe�ϰ� �����Ѵ�.
//
// 2. CGD::Interlocked_self_stack�� �ٽ�! Function�� ��� ����.
//    1) push		Data�� stack�� push�ϴ� �Լ�.
//    2) pop		stack���� Data�� �ϳ� ������ �Լ�.
//    3) pop_all()	stack�� ��� data�� �Ѳ����� ������ �Լ�. �����ʹ� list���ַ�
//                  ������ ���´�.
//
// 3. CGD::Interlocked_self_stack�� ���ǻ���
//    data�� �ݵ�� SLIST_ENTRY�� ��ӹ��� ��ü������ �ȴ�.
//
//
//-----------------------------------------------------------------------------
namespace CGD
{

template <class TTYPE>
struct SCGLIST_ENTRY
{
public:
			TTYPE*		Next;
};

template <class TDATA>
class Interlocked_self_stack
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
	typedef TDATA		value_type;

	// Standard 2) Pointer.
	typedef TDATA*		pointer;
	typedef const TDATA* const_pointer;

	// Standard 3) Reference.
	typedef TDATA&		reference;
	typedef const TDATA& const_reference;

	// Standard 4) size of type & difference type.
	typedef size_t		size_type;
	typedef int64_t		difference_type;

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
	typedef	Interlocked_self_stack<TDATA>	_mytype;

	// Rebinder) 
	template <class TOTHER_DATA>	
	struct rebind
	{
		typedef Interlocked_self_stack<TOTHER_DATA> other;
	};


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			Interlocked_self_stack()	{	InitializeSListHead(&m_slistHead);}
			~Interlocked_self_stack()	{}


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
			SLIST_HEADER		m_slistHead;
};


template <class TDATA>
size_t Interlocked_self_stack<TDATA>::size() const
{
	return static_cast<size_t>(QueryDepthSList(&m_slistHead));
}

template <class TDATA>
void Interlocked_self_stack<TDATA>::clear()
{
	// 1) head�� �ʱ�ȭ�Ѵ�.
	InterlockedFlushSList(&m_slistHead);	
}

template <class TDATA>
void Interlocked_self_stack<TDATA>::push(TDATA _pData)
{
#if defined(_M_IX86)
	CGASSERT_ERROR(m_slistHead.Next.Next!=(PSLIST_ENTRY)_pData);
#endif

	// 1) Push�Ѵ�.
	InterlockedPushEntrySList(&m_slistHead, (PSLIST_ENTRY)_pData);
}

template <class TDATA>
TDATA Interlocked_self_stack<TDATA>::pop()
{
	// Return) Pop�ؼ� �����Ѵ�.
	return (TDATA)InterlockedPopEntrySList(&m_slistHead);
}

template <class TDATA>
TDATA Interlocked_self_stack<TDATA>::pop_all()
{
	// Return) ��ü�� �� Pop�ؼ� ���� ó�� �����͸� �����Ѵ�.
	return	(TDATA)InterlockedFlushSList(&m_slistHead);
}


}
