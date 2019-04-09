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
// CGD::tls_stack<T>
//
// 1. CGD::tls_stack은?
//     CAS를 이용한 Lock Free로 Thread-Safe한 queue를 구현한 것이다.
//    Queue에 대한 기본적인 Lock-Free는 기존과 큰 차이가 없고 다만 추가 혹은 삭제
//    를 수행할 때 new나 delete를 하지 않고 stack으로 만들어진 Pool을 사용한다는
//    것이 특이하다.
//     기본적으로 Lock Free인데다가 new나 delete같은 동적할당을 하지 않기 때문에
//    기존의 Critical Section을 사용한 queue보다 월등하게 빠른 속도를 자랑한다.
//
// 2. CGD::tls_stack의 동작설명!!
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
//     1) X:value_type			Contain에 담긴 값들의 형.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:iterator			순회할 때 사용되는 반복자.
//     5) X:const_iterator		순회할 때 사용되는 반복자(const형)
//     6) X:difference_type		두 iterator에 담김 값의 거리를 나타내는 타입.
//     7) X:size_type			X의 크기를 나타낼때 사용되는 형.
//
//  * Reversible Requirement
//     1) X::reverse_iterator	역순환 때 사용되는 반복자.
//     2) X::const_reverse_iterator	역순환 때 사용되는 반복자.(const형)
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

	// Self) 자기자신(표준 아님.)
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
	// 1) 상태 Function
			size_t			size() const;

	// 2) stack을 모조리 비우는 함수.
			void			clear();

	// 3) 동작 Function
			void			push(const TDATA& _pData);
			TDATA			pop();
			TDATA			pop_all();

	// 4) Limite설정
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
	// Check) ABA 검사.
	//-----------------------------------------------------------------
	// 중요!  이런 경우는 한번 Stack한 것을 또 Stack하는 경우다. 이런 경우가 발생하면
	// 짤없이 따운되므로 Debug 시 반드시 체크해야 한다. 프로그램 짤때 이런 버그는 자주
	// 발생할 수 있다.
	//CGDASSERT(_pData != m_pHead->Next,);


	//-----------------------------------------------------------------
	// 1. Local Pool이 꽉찼는지를 확인한다.
	//-----------------------------------------------------------------
	if(m_iStacked > m_iLocalStackLimit)
	{
		// 1) Balance Pool에 넣는다.
		m_poolBalance.push(_pData);

		// Return) 
		return;
	}


	//-----------------------------------------------------------------
	// 2. Local Pool에 저장한다.
	//-----------------------------------------------------------------
	// 1) _pData의 Next를 지금의 head로 설정해놓는다.
	_pData->Next		 = m_pHead;

	// 2) head를 새로 설정한 놈으로 설정한다.
	m_pHead	 = _pData;
}

template <class TDATA, class TALLOCATOR>
TDATA tls_stack<TDATA, TALLOCATOR>::pop()
{
	//-----------------------------------------------------------------
	// 1. Local Pool이 비었으면 Balance Pool에서 뽑아서 돌려준다.
	//-----------------------------------------------------------------
	if(m_pHead==0)
	{
		// 1) Balance Pool에서 꺼내 Return한다.
		return	m_poolBalance.pop();
	}


	//-----------------------------------------------------------------
	// 1. Local Pool이 비었으면 Balance Pool에서 뽑아서 돌려준다.
	//-----------------------------------------------------------------
	// 1) 돌려준 Node를 저장해 둔다.
	TDATA	tempHead	 = m_pHead;

	// 2) head를 땡긴다.
	m_pHead	 = m_pHead->Next;

	// Return) 되돌린다.
	return	tempHead;
}


}
