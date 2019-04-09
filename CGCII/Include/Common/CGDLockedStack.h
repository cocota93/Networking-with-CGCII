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
// CGD::Lock::stack<T>
//
// 1. CGD::Lock::stack��!
//     InterlockedPush/Pop�� ����Ͽ� ������ stack�̴�.
//    Thread Safe�ϰ� ���������� ������ Lock�� ���� �ʴ´�.
//
// 2. CGD::Lock::stack�� �ٽ�! Function�� ��� ����.
//    1) push		Data�� stack�� push�ϴ� �Լ�.
//    2) pop		stack���� Data�� �ϳ� ������ �Լ�.
//    3) pop_all()	stack�� ��� data�� �Ѳ����� ������ �Լ�. �����ʹ� list���ַ�
//                  ������ ���´�.
//
// 3. CGD::Lock::stack�� ���ǻ���
//    data�� �ݵ�� SLIST_ENTRY�� ��ӹ��� ��ü������ �ȴ�.
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
	typedef ptrdiff_t	difference_type;

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
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
	// 1) ���� Function
			size_t				size() const;

	// 2) stack�� ������ ���� �Լ�.
			void				clear();

	// 3) ���� Function
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
	// 1) head�� �ʱ�ȭ�Ѵ�.
	LOCK(m_listStack)
	{
		m_listStack.clear();
	}
}

template <class TDATA>
void locked_stack<TDATA>::push(const TDATA& _pData)
{
	//-----------------------------------------------------------------
	// 1. Push�Ѵ�.
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