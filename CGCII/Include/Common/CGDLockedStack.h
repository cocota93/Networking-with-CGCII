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
// CGD::Lock::stack<T>
//
// 1. CGD::Lock::stack란!
//     InterlockedPush/Pop을 사용하여 구현한 stack이다.
//    Thread Safe하게 동작하지만 동작중 Lock을 걸지 않는다.
//
// 2. CGD::Lock::stack의 핵심! Function의 기능 설명.
//    1) push		Data를 stack에 push하는 함수.
//    2) pop		stack에서 Data를 하나 빼내는 함수.
//    3) pop_all()	stack의 모든 data를 한꺼번에 빼내는 함수. 데이터는 list혀애로
//                  뽛혀져 나온다.
//
// 3. CGD::Lock::stack의 주의사항
//    data는 반드시 SLIST_ENTRY를 상속받은 객체여야지 된다.
//
//
//-----------------------------------------------------------------------------
namespace CGD
{

template <class TDATA>
class locked_stack
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
	typedef	locked_stack<TDATA>	_mytype;

	// Rebinder) 
	template <class TOTHER_DATA>	
	struct rebind
	{
		typedef locked_stack<TOTHER_DATA> other;
	};


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			locked_stack()		{	clear();}
			~locked_stack()		{}


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
			void				Lock()									{	m_listStack.Enter();}
			void				Unlock()								{	m_listStack.Leave();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			LOCKABLE<list<TDATA>>	m_listStack;
};


template <class TDATA>
size_t locked_stack<TDATA>::size() const
{
	return	m_listStack.size();
}

template <class TDATA>
void locked_stack<TDATA>::clear()
{
	// 1) head를 초기화한다.
	LOCK(m_listStack)
	{
		m_listStack.clear();
	}
}

template <class TDATA>
void locked_stack<TDATA>::push(const TDATA& _pData)
{
	//-----------------------------------------------------------------
	// 1. Push한다.
	//-----------------------------------------------------------------
	LOCK(m_listStack)
	{
		m_listStack.push_front(_pData);
	}
}

template <class TDATA>
TDATA locked_stack<TDATA>::pop()
{
	LOCK(m_listStack)
	{
		TDATA	tempData	 = m_listStack.front();

		m_listStack.pop_front();

		return	tempData;
	}
}


}