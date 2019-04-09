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
// locked_queue<T>
//
// 1. CGD::locked_queue은?
//
//    1) Criticalsection을 사용하여 Thread-safe하게 제작된 Queue이다.
//    2) Criticalsection을 사용하기 때문에 Interlocked을 사용한 것들에 비해 
//       속도는 떨어지지만 Lock을 건 상태에서 find나 운행 같은 여러 작업을
//       수행할 수 있다.
//    3) 내부적으로는 spin을 사용한 Criticalsection을 사용하므로 그 성능에서
//       크게 떨어지지는 않는다.
//
// 2. 특징.
//
//    1) 장점
//       - 비교적 빠르다. 
//       - Lock을 건 상태에서 운행과 같은 작업들도 가능하다.
//
//    2) 단점
//       - Interlocked에 비해서는 조금 느리다.
//       - 항상 Dead Lock에 대한 주의가 필요하다.
//
//    연관) Interlocked_self_stack, lockfree_self_stack
//
//
//-----------------------------------------------------------------------------
namespace CGD
{

template <class TDATA>
class locked_queue
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
	typedef TDATA		value_type;

	// Standard 2) Pointer.
	typedef TDATA*		pointer;
	typedef const TDATA* const_pointer;

	// Standard 3) Reference.
	typedef TDATA&		reference;
	typedef const TDATA& const_reference;

	// Standard 4) size of type & difference type.
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	// Self) 자기자신(표준 아님.)
	typedef	locked_queue<TDATA>	_mytype;

	// Rebinder) 
	template <class TOTHER_DATA>	
	struct rebind
	{
		typedef locked_queue<TOTHER_DATA> other;
	};


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			locked_queue()		{	clear();}
			~locked_queue()		{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 상태 Function
			size_t				size() const;

	// 2) stack을 모조리 비우는 함수.
			void				clear();

	// 3) 동작 Function
			void				push(const TDATA& _pData);
			TDATA				pop();

	// 4) Lock/Unlock
			void				Lock()									{	m_listQueue.Enter();}
			void				Unlock()								{	m_listQueue.Leave();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			LOCKABLE<list<TDATA>>	m_listQueue;
};


template <class TDATA>
size_t locked_queue<TDATA>::size() const
{
	return	m_listQueue.size();
}

template <class TDATA>
void locked_queue<TDATA>::clear()
{
	// 1) head를 초기화한다.
	LOCK(m_listQueue)
	{
		m_listQueue.clear();
	}
}

template <class TDATA>
void locked_queue<TDATA>::push(const TDATA& _pData)
{
	//-----------------------------------------------------------------
	// 1. Push한다.
	//-----------------------------------------------------------------
	LOCK(m_listQueue)
	{
		m_listQueue.push_back(_pData);
	}
}

template <class TDATA>
TDATA locked_queue<TDATA>::pop()
{
	LOCK(m_listQueue)
	{
		TDATA	tempData	 = m_listQueue.front();

		m_listQueue.pop_front();

		return	tempData;
	}
}


}