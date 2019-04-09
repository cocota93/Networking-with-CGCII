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
// CGD::tls_stack<T>
//
// 1. CGD::tls_stack��?
//     CAS�� �̿��� Lock Free�� Thread-Safe�� queue�� ������ ���̴�.
//    Queue�� ���� �⺻���� Lock-Free�� ������ ū ���̰� ���� �ٸ� �߰� Ȥ�� ����
//    �� ������ �� new�� delete�� ���� �ʰ� stack���� ������� Pool�� ����Ѵٴ�
//    ���� Ư���ϴ�.
//     �⺻������ Lock Free�ε��ٰ� new�� delete���� �����Ҵ��� ���� �ʱ� ������
//    ������ Critical Section�� ����� queue���� �����ϰ� ���� �ӵ��� �ڶ��Ѵ�.
//
// 2. CGD::tls_stack�� ���ۼ���!!
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
#include "CGD/CGDDefinitions.h"

namespace CGD
{

template <class TDATA, class TALLOCATOR >
class tls_stack
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
//  * Reversible Requirement
//     1) X::reverse_iterator	����ȯ �� ���Ǵ� �ݺ���.
//     2) X::const_reverse_iterator	����ȯ �� ���Ǵ� �ݺ���.(const��)
// ----------------------------------------------------------------------------
public:
	// Standard 1) value type
	typedef TDATA			value_type;

	// Standard 2) Pointer
	typedef TDATA*			pointer;
	typedef const TDATA*	const_pointer;

	// Standard 3) Reference
	typedef TDATA&			reference;
	typedef const TDATA&	const_reference;

	// Standard 4) size of type & difference type
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
	typedef	tls_stack<TDATA, TALLOCATOR>	_mytype;

	// Rebinder) 
	template <class TOTHER_DATA, class TOTHER_ALLOCATOR>
	struct rebind
	{
		typedef tls_stack<TOTHER_DATA, TOTHER_ALLOCATOR> other;
	};


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			tls_stack(size_t p_iLSL=32)	{	SetLocalStackLimit(p_iLSL); clear();}
			~tls_stack()		{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) ���� Function
			size_t			size() const;

	// 2) stack�� ������ ���� �Լ�.
			void			clear();

	// 3) ���� Function
			void			push(const TDATA& _pData);
			TDATA			pop();
			TDATA			pop_all();

	// 4) Limite����
			size_t			GetLocalStackLimit() const			{	return m_iLocalStackLimit;}
			void			SetLocalStackLimit(size_t p_iLSL)	{	m_iLocalStackLimit=p_iLSL;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	static	TLS size_t		m_iStacked;
	static	TLS TDATA		m_pHead;

			LOCKFREE_SELF_STACK<TDATA>	m_poolBalance;

			size_t			m_iLocalStackLimit;
};


template <class TDATA, class TALLOCATOR>
TLS TDATA tls_stack<TDATA, TALLOCATOR>::m_pHead;

template <class TDATA, class TALLOCATOR>
TLS size_t tls_stack<TDATA, TALLOCATOR>::m_iStacked;

template <class TDATA, class TALLOCATOR>
size_t tls_stack<TDATA, TALLOCATOR>::size() const
{
	return	m_iStacked;
}

template <class TDATA, class TALLOCATOR>
void tls_stack<TDATA, TALLOCATOR>::clear()
{
	m_pHead	 = 0;
}

template <class TDATA, class TALLOCATOR>
void tls_stack<TDATA, TALLOCATOR>::push(const TDATA& _pData)
{
	//-----------------------------------------------------------------
	// Check) ABA �˻�.
	//-----------------------------------------------------------------
	// �߿�!  �̷� ���� �ѹ� Stack�� ���� �� Stack�ϴ� ����. �̷� ��찡 �߻��ϸ�
	// ©���� ����ǹǷ� Debug �� �ݵ�� üũ�ؾ� �Ѵ�. ���α׷� ©�� �̷� ���״� ����
	// �߻��� �� �ִ�.
	//CGDASSERT(_pData != m_pHead->Next,);


	//-----------------------------------------------------------------
	// 1. Local Pool�� ��á������ Ȯ���Ѵ�.
	//-----------------------------------------------------------------
	if(m_iStacked > m_iLocalStackLimit)
	{
		// 1) Balance Pool�� �ִ´�.
		m_poolBalance.push(_pData);

		// Return) 
		return;
	}


	//-----------------------------------------------------------------
	// 2. Local Pool�� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) _pData�� Next�� ������ head�� �����س��´�.
	_pData->Next		 = m_pHead;

	// 2) head�� ���� ������ ������ �����Ѵ�.
	m_pHead	 = _pData;
}

template <class TDATA, class TALLOCATOR>
TDATA tls_stack<TDATA, TALLOCATOR>::pop()
{
	//-----------------------------------------------------------------
	// 1. Local Pool�� ������� Balance Pool���� �̾Ƽ� �����ش�.
	//-----------------------------------------------------------------
	if(m_pHead==0)
	{
		// 1) Balance Pool���� ���� Return�Ѵ�.
		return	m_poolBalance.pop();
	}


	//-----------------------------------------------------------------
	// 1. Local Pool�� ������� Balance Pool���� �̾Ƽ� �����ش�.
	//-----------------------------------------------------------------
	// 1) ������ Node�� ������ �д�.
	TDATA	tempHead	 = m_pHead;

	// 2) head�� �����.
	m_pHead	 = m_pHead->Next;

	// Return) �ǵ�����.
	return	tempHead;
}


}
