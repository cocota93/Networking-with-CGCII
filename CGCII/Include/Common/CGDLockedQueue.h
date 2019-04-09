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
// locked_queue<T>
//
// 1. CGD::locked_queue��?
//
//    1) Criticalsection�� ����Ͽ� Thread-safe�ϰ� ���۵� Queue�̴�.
//    2) Criticalsection�� ����ϱ� ������ Interlocked�� ����� �͵鿡 ���� 
//       �ӵ��� ���������� Lock�� �� ���¿��� find�� ���� ���� ���� �۾���
//       ������ �� �ִ�.
//    3) ���������δ� spin�� ����� Criticalsection�� ����ϹǷ� �� ���ɿ���
//       ũ�� ���������� �ʴ´�.
//
// 2. Ư¡.
//
//    1) ����
//       - ���� ������. 
//       - Lock�� �� ���¿��� ����� ���� �۾��鵵 �����ϴ�.
//
//    2) ����
//       - Interlocked�� ���ؼ��� ���� ������.
//       - �׻� Dead Lock�� ���� ���ǰ� �ʿ��ϴ�.
//
//    ����) Interlocked_self_stack, lockfree_self_stack
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
	// 1) ���� Function
			size_t				size() const;

	// 2) stack�� ������ ���� �Լ�.
			void				clear();

	// 3) ���� Function
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
	// 1) head�� �ʱ�ȭ�Ѵ�.
	LOCK(m_listQueue)
	{
		m_listQueue.clear();
	}
}

template <class TDATA>
void locked_queue<TDATA>::push(const TDATA& _pData)
{
	//-----------------------------------------------------------------
	// 1. Push�Ѵ�.
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