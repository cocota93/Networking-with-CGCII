//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 6.1 / Release 2012.05.28                        *
//*                                                                           *
//*                           Data Template Classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangducks@gmail.com          *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                           http://www.CGDK.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

#define  CGD_USE_SAFE_ITERATOR

namespace CGD
{

template <class TDATA, class TALLOCATOR=allocator_pool<TDATA> >
class circular_list
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type		Contain�� ��� ������ ��.
//     2) X:reference		X:value_type&.
//     3) X:const_reference	const X:value_type&.
//     4) X:iterator		��ȸ�� �� ���Ǵ� �ݺ���.
//     5) X:const_iterator	��ȸ�� �� ���Ǵ� �ݺ���(const����)
//     6) X:difference_type	�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     7) X:size_type		X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
//
//  * Reversible Requirement
//     1) X::reverse_iterator ����ȯ �� ���Ǵ� �ݺ���.
//     2) X::const_reverse_iterator	����ȯ �� ���Ǵ� �ݺ���.(const����)
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

	// Standard 5) Iterators
	class iterator;
	class const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// Allocator)
	typedef TALLOCATOR		allocator_type;

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
	typedef	circular_list<TDATA, TALLOCATOR>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA, typename TOTHER_ALLOCATOR=TALLOCATOR>
	struct rebind
	{
		typedef circular_list<TOTHER_DATA, TOTHER_ALLOCATOR> other;
	};


// ****************************************************************************
// Common Container Standard)
//
//  * Common Container Requirement
//     1) X();				Default Constructor
//     2) X(a);				Copy Constrctor.(�ҿ�ð��� ������)
//		  X u(a);
//     3) (&a)->~X();		Destructor.(�ҿ�ð��� ������)
//     4) a.begin(); 		Container ��ȸ�� ����� ���۰� �� iterator 
//		  a.end();
//     5) a==b; a!=b;		Container ��� ���� ������ true.(�ҿ�ð� ������)
//     6) a.size();			Container�� ��� ������ ������ �����Ѵ�.
//     7) a.max_size();		Container�� ���� �� �ִ� �ִ� ���� ������ �����Ѵ�.
//     8) a.empty();		Container�� ��� �ִ� ����� true�� �����Ѵ�.
//     9) a<b; a>b; 		�� ����(�ҿ�ð� ������)
//		  a<=b; a>=b;
//    10) r=a;				Container ���Կ���(�ҿ�ð� ������)
//    11) a.swap(b);		������ Ÿ���� �� Ŀ���̳ʸ� ���� �¹ٲ۴�.
//
//  * Reversible Requirement
//     1) a.rbegin();		�ݴ���� ��ȸ�� ���� ���۰� �� iterator
//		  a.rend();
//
// ----------------------------------------------------------------------------
public:
	circular_list();
	circular_list(const _mytype& _Right);
	~circular_list();

public:
	// Common Standard 1) Status Function
	size_type				size() const							{	return m_size;}
	size_type				max_size() const						{	return INT_MAX;}
	bool					empty() const							{	return m_size==0;}

	// Common Standard 2) 
	iterator				begin()									{	return iterator(m_head);}
	const_iterator			begin() const							{	return const_iterator(m_head);}
	const_iterator			cbegin() const							{	return const_iterator(m_head);}
	iterator				end()									{	return iterator(m_tail);}
	const_iterator			end() const								{	return const_iterator(m_tail);}
	const_iterator			cend() const							{	return const_iterator(m_tail);}
	reverse_iterator		rbegin()								{	return reverse_iterator(iterator(m_tail->_pre));}
	const_reverse_iterator	rbegin() const							{	return const_reverse_iterator(const_iterator(m_tail->_pre));}
	const_reverse_iterator	crbegin() const							{	return const_reverse_iterator(const_iterator(m_tail->_pre));}
	reverse_iterator		rend()									{	return reverse_iterator(iterator(m_head->_pre));}
	const_reverse_iterator	rend() const							{	return const_reverse_iterator(const_iterator(m_head->_pre));}
	const_reverse_iterator	crend() const							{	return const_reverse_iterator(const_iterator(m_head->_pre));}

	// Common Standard 3) 
	void					swap(_mytype& _Right);

	// Common Standard 5) Operators
	bool					operator==(const _mytype& _Right) const;
	bool					operator!=(const _mytype& _Right) const;
	bool					operator<(const _mytype& _Right) const;
	bool					operator>(const _mytype& _Right) const;
	bool					operator<=(const _mytype& _Right) const;
	bool					operator>=(const _mytype& _Right) const;
	_mytype&				operator=(const _mytype& _Right);


// ****************************************************************************
// Sequence Container Standard)
//
//  * Sequence Container Requirement
//    1) X(n, t);		t�� ���纻 n���� ������ Sequence�� �����Ѵ�.
//		 X a(n, t);	
//    2) X(i, j); 		����[i,j]�� ����� ������ Sequence�� �����Ѵ�.
//		 X a(i, j);
//    3) a.insert(p,t);	p�տ� t�� ���纻�� �����Ѵ�. ���ϰ��� ���Ե�
//						���Ҹ� ����Ű�� �ݺ����̴�.
//    4) a.insert(p,n,t);p�տ� t�� ���纻 n���� �����Ѵ�.
//    5) a.insert(p,i,j);p�տ� [i,j]�� ��� ���ҵ��� ���纻�� �����Ѵ�.
//						i,j�� �ݺ���
//    6) a.erase(q);	q�� ����Ű�� ���Ҹ� �����Ѵ�. ���ϰ��� �����Ǳ�
//						���� q������ ��ġ�ߴ� ���Ҹ� ����Ű�� �ݺ���
//    7) a.erase(q1,q2);����[q1,q2]�� ���Ե� ���ҵ��� �����Ѵ�. ���ϰ���
//						�����Ǳ� ���� q2������ ��ġ�ߴ� ���Ҹ� ����Ű��
//						�ݺ���.
//    8) a.clear();		�����̳ʿ� ��� ���� ���Ҹ� �����Ѵ�. 
//						a.erase(a.begin(), a.end())�� �����ϴ�.
//
// ----------------------------------------------------------------------------
public:
	circular_list(size_type _Count);
	circular_list(size_type _Count, const_reference _Val);
	circular_list(size_type _Count, const_reference _Val, const TALLOCATOR& _Al);
	template<class TITERATOR>
	circular_list(TITERATOR _First, TITERATOR _Last);
	template<class TITERATOR>
	circular_list(TITERATOR _First, TITERATOR _Last, const TALLOCATOR& _Al);

public:
	// Sequence Standard 1) insert member function
	template<class TITERATOR>
	void					insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last);
	iterator				insert(const_iterator _Where, const_reference _Val);
	void					insert(const_iterator _Where, int _Count, const_reference _Val);

	// Sequence Standard 2) erase member function
	iterator				erase(const_iterator _Where);
	iterator				erase(const_iterator _First, const_iterator _Last);

	// Sequence Standard 3) clear
	void					clear();

	// CGD Native) attach/detach function
	void					attach(const_iterator _Where, const_iterator _Node);
	void					detach(const_iterator _Where);


// ****************************************************************************
// List Member)
//
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const						{	return m_capacity;}

	// 2) Data
	reference				front()									{	return m_head->_data;}
	const_reference			front() const							{	return m_head->_data;}

	reference				back()									{	return m_tail->_pre->_data;}
	const_reference			back() const							{	return m_tail->_pre->_data;}
	
	// 3) Unique
	template<typename _Pr2>
	void					unique(_Pr2 _Pred);
	void					unique();

	// 4) Push & Pop Front
	void					push_front(const_reference _Val);
	reference				push_front();
	void					pop_front();

	void					push_back(const_reference _Val);
	reference				push_back();
	void					pop_back();

	// 5) remove
	template<typename _Pr1>
	void					remove_if(_Pr1 _Pred);
	void					remove(const_reference p_pData);

	// 6) Reserve & Resize
	void					reserve(size_type _Count);
	void					resize(size_type _Newsize)				{	resize(_Newsize, TDATA());}
	void					resize(size_type _Newsize, TDATA _Val);

	// 7) splice
	void					splice(const_iterator _Where, _mytype& _Right);
	void					splice(const_iterator _Where, _mytype& _Right, const_iterator _First);
	void					splice(const_iterator _Where, _mytype& _Right, const_iterator _First, const_iterator _Last);

	// 8) Assign.
	template<class ITERATOR>
	void					assign(ITERATOR _First, ITERATOR _Last);
	void					assign(size_type _Count, const_reference _Val);

	// 9) merge(�ΰ��� circular_list�� ��ġ�� �Լ�.)
	template<typename _Pr3>
	void					merge(_mytype& _Right, _Pr3 _Pred);;
	void					merge(_mytype& _Right);

	// 10) sort
	template<typename _Pr3>
	void					sort(_Pr3 _Pred);
	void					sort();

	// 11) shrink(List�� size�� �°� ���̴� �Լ�.)
	void					shrink();

	// 12) Allocation
	allocator_type			get_allocator() const					{	return m_allocVal;}

	#ifdef CGD_USE_SAFE_ITERATOR
	// 13) Safe Iterator
	iterator&				get_safe_iterator()						{	return m_safe_iterator;}
	#endif


// ****************************************************************************
// 2. List
// ----------------------------------------------------------------------------
public:
	// Node Structure)
	struct _node
	{
		_node*				_pre;
		_node*				_next;
		TDATA				_data;

		_node()				{}
		_node(const TDATA& p_data) : _data(p_data)	{}
	};

protected:
	// 1) Head & Tail Pointer
	_node*					m_head;					// Linked List�� Head�� �ٷ� ��~
	_node*					m_tail;					// Linked List�� Tail�� �ٷ� ��~

	// 2) Size & Capacity
	size_type				m_size;					// ���� ������� Node��.
	size_type				m_capacity;				// ��ü Node��.

	// 3) Allocator
	allocator_type			m_allocVal;
	typename TALLOCATOR::template rebind<_node>::other	m_allocNode;

private:
	void					_init();
	_node*					_newNode(const TDATA& _Val);
	_node*					_newNode();
	void					_merge_for_sort(_node& tempList, _node& nowList);
	template<typename _Pr3>
	void					_merge_for_sort(_node& tempList, _node& nowList, _Pr3 _Pred);
	void					_slice_for_sort(_node& tempList, _node*& nodeNow);




// ****************************************************************************
// Iterator Definitions.
// 
// 1. Bi-Directional Iterator Standard Requirement
//    1) Cousturctors(Xu; X(); X(a); X u(a); X u=a;)
//    2) a==b; a!=b;
//    3) r=a; *a; a->m; 
//    4) ++r; r++; *r++;
//    5) --r; r--; *r--;
// ----------------------------------------------------------------------------
public:
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	circular_list<TDATA, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;

		friend			iterator;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		const_iterator() : _Ptr(nullptr)							{}
		explicit const_iterator(_node* _now) : _Ptr(_now)			{}

		// 2) ����
		const_iterator&		operator=(const const_iterator& _Right)	{	_Ptr=_Right._Ptr; return *this;}
		const_iterator&		operator=(_node* _Right)				{	_Ptr=_Right; return *this;}
		pointer				operator->()								{	return &**this;}

		// 3) �ݺ�
		reference			operator*() const						{	return _Ptr->_data;}
		const_iterator&		operator++()							{	_Ptr=_Ptr->_next; return *this;}
		const_iterator		operator++(int)							{	const_iterator tIter(_Ptr); _Ptr=_Ptr->_next; return tIter;}
		const_iterator&		operator--()								{	_Ptr=_Ptr->_pre; return *this;}
		const_iterator		operator--(int)							{	const_iterator tIter(_Ptr); _Ptr=_Ptr->_pre; return tIter;}
		const_iterator		operator+(difference_type _Right) const	{	const_iterator temp(_Ptr); temp+=_Right; return temp;}
		void				operator+=(difference_type _Right)		{	while(_Right){_Ptr=_Ptr->_next;--_Right;}}
		const_iterator		operator-(difference_type _Right) const	{	const_iterator temp(_Ptr); temp-=_Right; return temp;}
		void				operator-=(difference_type _Right)		{	while(_Right){_Ptr=_Ptr->_pre;--_Right;}}

		// 4) ��
		bool				operator==(const iterator& _Right) const{	return _Ptr==_Right._Ptr;}
		bool				operator!=(const iterator& _Right) const{	return _Ptr!=_Right._Ptr;}

		bool				operator==(const const_iterator& _Right) const{	return _Ptr==_Right._Ptr;}
		bool				operator!=(const const_iterator& _Right) const{	return _Ptr!=_Right._Ptr;}

	public:
		_node*				_Ptr;
	};


	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	circular_list<TDATA, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;

		friend			const_iterator;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		iterator() : _Ptr(nullptr)									{}
		iterator(const iterator& _Copy) : _Ptr(_Copy._Ptr){}
		explicit iterator(_node* _now) : _Ptr(_now)					{}

		// 2) ����
		iterator&			operator=(const iterator& _Right)		{	_Ptr=_Right._Ptr; return *this;}
		iterator&			operator=(const const_iterator& _Right)	{	_Ptr=_Right._Ptr; return *this;}
		void				operator=(_node* _Right)				{	_Ptr=_Right;}
		pointer				operator->()								{	return &**this;}
							operator const_iterator()				{	return const_iterator(_Ptr);}

		// 3) �ݺ�
		reference			operator*() const						{	return _Ptr->_data;}
		iterator&			operator++()							{	_Ptr=_Ptr->_next; return *this;}
		iterator			operator++(int)							{	iterator tIter(_Ptr); _Ptr=_Ptr->_next; return tIter;}
		iterator&			operator--()								{	_Ptr=_Ptr->_pre; return *this;}
		iterator			operator--(int)							{	iterator tIter(_Ptr); _Ptr=_Ptr->_pre; return tIter;}
		iterator			operator+(difference_type _Right) const	{	iterator temp(_Ptr); temp+=_Right; return temp;}
		void				operator+=(difference_type _Right)		{	while(_Right){_Ptr=_Ptr->_next;--_Right;}}
		iterator			operator-(difference_type _Right) const	{	iterator temp(_Ptr); temp-=_Right; return temp;}
		void				operator-=(difference_type _Right)		{	while(_Right){_Ptr=_Ptr->_pre;--_Right;}}

		// 4) ��
		bool				operator==(const iterator& _Right) const{	return _Ptr==_Right._Ptr;}
		bool				operator!=(const iterator& _Right) const{	return _Ptr!=_Right._Ptr;}

		bool				operator==(const const_iterator& _Right) const{	return _Ptr==_Right._Ptr;}
		bool				operator!=(const const_iterator& _Right) const{	return _Ptr!=_Right._Ptr;}

	public:
		_node*				_Ptr;
	};

	// 4) safe Iter now
	#ifdef CGD_USE_SAFE_ITERATOR
	iterator				m_safe_iterator;
	#endif
};




//-----------------------------------------------------------------
// Constructor/Destructor �Լ���.
//
// - �پ��� ������ constructor�� destructor�Լ����̴�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list()
{
	// 1) Head�� �Ҵ��Ѵ�.
	m_head		 = m_allocNode.allocate(1);

	// 2) Head�� Tail�� ����~(head�� head�� link~)
	LINK_NODE(m_head, m_head);

	// 3) Tail�� Head���� ����.(�̻��°� empty����)
	m_tail	 = m_head;

	// 4) �������� Reset
	m_size			 = 0;
	m_capacity		 = 0;
	m_safe_iterator	 = 0;
}


template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(const _mytype& _Right)
{
	// 1) List�� �ʱ�ȭ�Ѵ�.
	_init();

	// 2) �����سִ´�.
	CGD_TRY
	{
		insert(begin(), _Right.begin(), _Right.end());
	}
	CGD_CATCH_ALL
	{
		m_allocNode.deallocate(m_head, 1);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::_mytype& circular_list<TDATA, TALLOCATOR>::operator=(const _mytype& _Right)
{
	// 1) �ϴ� ������ �� �����.
	clear();

	// 2) �����سִ´�.
	CGD_TRY
	{
		insert(begin(), _Right.begin(), _Right.end());
	}
	CGD_CATCH_ALL
	{
		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// Return) �ڱ� �ڽ� Return
	return	*this;
}


template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(size_type _Count)
{
	// 1) List�� �ʱ�ȭ�Ѵ�.
	_init();

	// 2) �����سִ´�.

	// 2) �Ҵ���� ���ο� Node�� Construct�� �����Ѵ�.
	CGD_TRY
	{
		for(;_Count>0;--_Count)
		{
			push_back();
		}
	}
	CGD_CATCH_ALL
	{
		m_allocNode.deallocate(m_head, 1);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}


template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(size_type _Count, const_reference _Val)
{
	// 1) List�� �ʱ�ȭ�Ѵ�.
	_init();

	// 2) �����سִ´�.
	CGD_TRY
	{
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		m_allocNode.deallocate(m_head, 1);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}


template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(size_type _Count, const_reference _Val, const TALLOCATOR& _Al)
{
	// 1) List�� �ʱ�ȭ�Ѵ�.
	_init();

	// 2) �����سִ´�.
	CGD_TRY
	{
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		m_allocNode.deallocate(m_head, 1);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}


template <class TDATA, class TALLOCATOR>
template<class TITERATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(TITERATOR _First, TITERATOR _Last)
{
	// 1) List�� �ʱ�ȭ�Ѵ�.
	_init();

	// 2) �����سִ´�.
	CGD_TRY
	{
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		m_allocNode.deallocate(m_head, 1);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}


template <class TDATA, class TALLOCATOR>
template<class TITERATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(TITERATOR _First, TITERATOR _Last, const TALLOCATOR& _Al)
{
	// 1) List�� �ʱ�ȭ�Ѵ�.
	_init();

	// 2) �����سִ´�.
	CGD_TRY
	{
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		m_allocNode.deallocate(m_head, 1);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::~circular_list()
{
	//-----------------------------------------------------------------
	// 1. ���� clear�� �ؼ� item���� destory�� ȣ���Ѵ�.
	//-----------------------------------------------------------------
	clear();

	//-----------------------------------------------------------------
	// 2. ��� Node���� �����.
	//-----------------------------------------------------------------
	_node*	temp = m_head;
	do
	{
		// - Next node�� �� ������ ���´�.
		_node*	tempNext	 = temp->_next;

		// - Destruct�� ȣ���ϰ� tempNode�� �����.
		//   (Destroy�� ȣ������ �ʴ´�.)
		m_allocNode.deallocate(temp, 1);

		// - ���� Node
		temp	 = tempNext;
	}while(temp != m_head);
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::_init()
{
	// 1) Head�� �Ҵ��Ѵ�.
	m_head		 = m_allocNode.allocate(1);

	// 2) Head�� Tail�� ����~(head�� head�� link~)
	LINK_NODE(m_head, m_head);

	// 3) Tail�� Head���� ����.(�̻��°� empty����)
	m_tail	 = m_head;

	// 4) �������� Reset
	m_size			 = 0;
	m_capacity		 = 0;
	m_safe_iterator	 = 0;
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::_node* circular_list<TDATA, TALLOCATOR>::_newNode(const TDATA& _Val)
{
	// 1) ���ο� Node�� Allocator�κ��� �Ҵ� �޴´�.
	_node*	newNode = m_allocNode.allocate(1);

	// 2) �Ҵ���� ���ο� Node�� Construct�� �����Ѵ�.
	CGD_TRY
	{
		m_allocVal.construct(&newNode->_data, _Val);
	}
	// Exception) Exception�� �߻����� ���!!!
	CGD_CATCH_ALL
	{
		// - deallocate�� �����Ѵ�.
		m_allocNode.deallocate(newNode, 1);

		// Re-Throw�� �Ѵ�.
		CGD_RETHROW;
	}

	// Return) ���ο� Node�� Return�Ѵ�.
	return	newNode;
}

template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::_node* circular_list<TDATA, TALLOCATOR>::_newNode()
{
	// 1) ���ο� Node�� Allocator�κ��� �Ҵ� �޴´�.
	_node*	newNode = m_allocNode.allocate(1);

	// 2) �Ҵ���� ���ο� Node�� Construct�� �����Ѵ�.
	CGD_TRY
	{
		m_allocVal.construct(&newNode->_data);
	}
	// Exception) Exception�� �߻����� ���!!!
	CGD_CATCH_ALL
	{
		// - deallocate�� �����Ѵ�.
		m_allocNode.deallocate(newNode, 1);

		// Re-Throw�� �Ѵ�.
		CGD_RETHROW;
	}

	// Return) ���ο� Node�� Return�Ѵ�.
	return	newNode;
}

// ���Լ���
template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator==(const _mytype& _Right) const
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Src�� ���ΰ�???
		if(iterSrc==end())
		{
			return	(iterDst==_Right.end());
		}

		// Check) Dst�� ���ΰ�?
		if(iterDst==end())
		{
			return	false;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� false����!
		if(*iterSrc!=*iterDst)
		{
			return	false;
		}

		// 3) ������~
		++iterSrc;
		++iterDst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator!=(const _mytype& _Right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Src�� ���ΰ�???
		if(iterSrc==end())
		{
			return	(iterDst!=_Right.end());
		}

		// Check) Dst�� ���ΰ�?
		if(iterDst==end())
		{
			return	true;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iterSrc!=*iterDst)
		{
			return	true;
		}

		// 3) ������~
		++iterSrc;
		++iterDst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator<(const _mytype& _Right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Dst�� ���ΰ�?
		if(iterDst==end())
		{
			return	false;
		}

		// Check) Src�� ���ΰ�???
		if(iterSrc==end())
		{
			return	true;
		}


		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iterSrc!=*iterDst)
		{
			return	(*iterSrc<*iterDst);
		}

		// 3) ������~
		++iterSrc;
		++iterDst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator>(const _mytype& _Right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Src�� ���ΰ�???
		if(iterSrc==end())
		{
			return	false;
		}

		// Check) Dst�� ���ΰ�?
		if(iterDst==end())
		{
			return	true;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iterSrc!=*iterDst)
		{
			return	(*iterSrc>*iterDst);
		}

		// 3) ������~
		++iterSrc;
		++iterDst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator<=(const _mytype& _Right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Src�� ���ΰ�???
		if(iterSrc==end())
		{
			return	true;
		}

		// Check) Dst�� ���ΰ�?
		if(iterDst==end())
		{
			return	false;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iterSrc!=*iterDst)
		{
			return	(*iterSrc<*iterDst);
		}

		// 3) ������~
		++iterSrc;
		++iterDst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator>=(const _mytype& _Right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Dst�� ���ΰ�?
		if(iterDst==end())
		{
			return	true;
		}

		// Check) Src�� ���ΰ�???
		if(iterSrc==end())
		{
			return	false;
		}


		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iterSrc!=*iterDst)
		{
			return	(*iterSrc>*iterDst);
		}

		// 3) ������~
		++iterSrc;
		++iterDst;
	}
}



template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::reserve(size_type _Count)
{
	//-----------------------------------------------------------------
	// 1. �߰��� Ȯ���� Node������ ����Ѵ�.
	//-----------------------------------------------------------------
	// Check) �߰��� item�� ������ 0�� ���϶�� �׳� ������.
	CGD_RETURN_IF(_Count<=m_capacity,);

	//-----------------------------------------------------------------
	// 2. �߰��� Node����ŭ �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) ���� �߰��� item�� ������ ����Ѵ�.
	size_type	added	 = _Count-m_capacity;

	// 1) ������ ��ü�� ���� Node�� ��´�.
	_node*		end		 = m_head->_pre;
	CGD_TRY
	{
		// 2) �߰��� item�� ������ŭ node�� ����� ������.
		for(; added>0; --added)
		{
			// - Node�� ���� �����Ѵ�.
			_node*	pNewNode = m_allocNode.allocate(1);

			// - ������ Node�� end�� ������.
			LINK_NODE(end, pNewNode);

			// - ���� Node�� ���ο� end�� �����Ѵ�.
			end				 = pNewNode;
		}
	}
	CGD_CATCH_ALL
	{
		// 1) Roll back�� ù��° Node�� ��´�.
		_node*	nodeDealloc = m_head->_pre->_next;

		// 2) Loop�� ���� ������ ��� Node�� �����Ѵ�.
		while(nodeDealloc != end)
		{
			// - �ӽ÷� ���� Node�� ��� ���´�.
			_node*	tempNext	 = nodeDealloc->_next;

			// �Ҵ��ߴ� pNewNode�� �����Ѵ�.
			m_allocNode.deallocate(nodeDealloc, 1);

			// - ���� Node��~
			nodeDealloc	 = tempNext;
		}

		// 3) m_head�� pre�� Next�� �ٽ� m_head�� �ǵ�����.
		m_head->_pre->_next	 = m_head;

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	//-----------------------------------------------------------------
	// 3. Head�� �ʿ��ٰ� ������.
	//-----------------------------------------------------------------
	// 1) ���� node�� head�� ���ʿ� ������.
	LINK_NODE(end, m_head);

	//-----------------------------------------------------------------
	// 4. �����Ͽ� �߰��Ѹ�ŭ ����node�� ���� ������Ų��.
	//-----------------------------------------------------------------
	m_capacity		 = _Count;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::resize(size_type _Newsize, TDATA _Val)
{
	// ũ�� ���� ����.
	int	differ	 = _Newsize - m_size;

	//-----------------------------------------------------------------
	// CaseA) ũ�⸦ �ø���.
	//-----------------------------------------------------------------
	// ���� ���� ũ�Ⱑ NewSize���� ������ _Val�� �� ���̸�ŭ �����Ѵ�.
	if (differ>0)
	{
		insert(end(), differ, _Val);
	}
	//-----------------------------------------------------------------
	// CaseB) ũ�⸦ ���δ�.
	//-----------------------------------------------------------------
	//  ���� ���� ũ�Ⱑ NewSize���� ũ�� ���� Item���� �����Ѵ�.
	else
	{
		// 1) ����ó differ��ŭ ���ʿ������� �����Ѵ�.
		while (differ!=0)
		{
			// - Tail�� ��ĭ �����.
			m_tail	 = m_tail->_pre;

			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&m_tail->_data);

			differ++;
		}

		// 2) ũ��� ������ _NewSize�Ǵ� �Ŵ�.
		m_size	 = _Newsize;
	}
}

template <class TDATA, class TALLOCATOR>
template<class ITERATOR>
void circular_list<TDATA, TALLOCATOR>::assign(ITERATOR _First, ITERATOR _Last)
{
	// 1) ���� List�� ��� �����.
	clear();

	// 2) �����Ѵ�.
	for(; _First != _Last; ++_First)
	{
		push_back(*_First);
	}
}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::assign(size_type _Count, const_reference _Val)
{
	// 1) ���� �����.
	clear();

	// 2) _Val���� _Count��ŭ �����Ѵ�.
	for (; 0 < _Count; --_Count)
	{
		push_back(_Val);
	}
}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::clear()
{
	//-----------------------------------------------------------------
	// 1. destory�Լ��� ȣ���Ѵ�.
	//-----------------------------------------------------------------
	// Iterator�� �����鼭 ������ �����.
	for(iterator iter=begin(); iter != end(); ++iter)
	{
		// - Destruct�� ȣ���Ѵ�.
		m_allocVal.destroy(&(*iter));
	}


	//-----------------------------------------------------------------
	// 2. Clear�Ѵ�.
	//-----------------------------------------------------------------
	// 1) head�� next�� �����Ѵ�.
	m_tail		 = m_head;

	// 2) Clear�Ѵ�.
	#ifdef CGD_USE_SAFE_ITERATOR
	m_safe_iterator._Ptr	 = m_head->_pre;
	#endif

	// 3) ũ�⸦ 0����..
	m_size		 = 0;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::push_front(const_reference _Val)
{
	//-----------------------------------------------------------------
	// 1. ���� �����ؼ� �߰��Ѵ�.
	//
	// - ���� node�� ����(m_size�� allocated������ ���� Node�� ���� ���̴�.)
	//   ������ ���� ����� �߰��Ѵ�.
	//   (�̰��� ������� �ʵ��� �ִ��� reserve�� �̷� �صѰ��� ���Ѵ�.)
	//-----------------------------------------------------------------
	if(m_size==m_capacity)
	{
		// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node*	pNewNode	 = _newNode(_Val);

		// 2) Node�� Head�� �����Ѵ�.
		LINK_NODE(m_head->_pre, pNewNode);
		LINK_NODE(pNewNode, m_head);

		// 3) ���� �Ҵ���� pNodeNode�� ���ο� Head���ȴ�.
		m_head	 = pNewNode;

		// 4) �Ҵ���� ���� ũ�⸦ 1 �ø���.
		++m_size;
		++m_capacity;

		// Return) 
		return;
	}

	//-----------------------------------------------------------------
	// 2. Node�� �о �߰��Ѵ�.
	//
	// - Circulare List�� �ٱ��ʿ� ���� Node�� �ִ� ����.
	// - �׳� �ϳ� �а� �ű⿡�ٰ� ���� �߰��� �ϸ� �ȴ�.
	//
	// ����) 1)�׿��� pre�� ���� ���� ���� construct�� ó���ϰ� 3)�׿���
	//       m_head�� ������ _pre�� ���� ������ Exception-safeó����
	//       ���ؼ��̴�. construct�������� exception�� �߻��Ҽ� �ְ�
	//       ���� m_head�� �̸� ���ܳ������� exception�� �߻����� �� �ٽ�
	//       roll-back�� ����� �Ѵ�. �׷��� construct�� ���� ���Ŀ� 
	//       m_head ���� �ٲٴ� ó���� �� ���̴�.
	//       (�� �� ó���� code�� �ӵ��� ���� ������ ����.)
	//-----------------------------------------------------------------

	// 1) ���ο� Head�� �� Node�� ��´�.
	_node*	pNow	 = m_head->_pre;

	// 2) Constructor�� ȣ���Ѵ�.(Copy constructor�� ȣ��)
	m_allocVal.construct(&pNow->_data, _Val);

	// 3) �׳� �ϳ� �����.
	m_head			 = pNow;

	// 4) ũ��(size)�� 1 ���δ�.
	++m_size;
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::reference circular_list<TDATA, TALLOCATOR>::push_front()
{
	//-----------------------------------------------------------------
	// 1. ���� �����ؼ� �߰��Ѵ�.
	//
	// - ���� node(m_size�� allocated������ ���� Node�� ���� ���̴�.)��
	//   ������ ���� ����� �߰��Ѵ�.
	//   (�̰��� ������� �ʵ��� �ִ��� reserve�� �̷� �صѰ��� ���Ѵ�.)
	//-----------------------------------------------------------------
	if(m_size==m_capacity)
	{
		// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node*	pNewNode	 = _newNode();

		// 2) Node�� Head�� �����Ѵ�.
		LINK_NODE(m_head->_pre, pNewNode);
		LINK_NODE(pNewNode, m_head);

		// 3) ���� �Ҵ���� pNodeNode�� ���ο� Head�� �ȴ�.
		m_head	 = pNewNode;

		// 4) �Ҵ���� ���� ũ�⸦ 1�� �ø���.
		++m_size;
		++m_capacity;

		// Return) Data�� Reference�� �ǵ�����.
		return	pNewNode->_data;
	}

	//-----------------------------------------------------------------
	// 2. Node�� �о �߰��Ѵ�.
	//
	// - Circulare List�� �ٱ��ʿ� ���� Node�� �ִ� ����.
	// - �׳� �ϳ� �а� �ű⿡�ٰ� ���� �߰��� �ϸ� �ȴ�.
	//
	// ����) 1)�׿��� pre�� ���� ���� ���� construct�� ó���ϰ� 3)�׿���
	//       m_head�� ������ _pre�� ���� ������ Exception-safe�� ó����
	//       ���ؼ��̴�. construct�������� exception�� �߻��Ҽ� �ְ�
	//       ���� m_head�� �̸� ���ܳ������� exception�� �߻����� �� �ٽ�
	//       roll-back�� ����� �Ѵ�. �׷��� construct�� ���� ���Ŀ� 
	//       m_head ���� �ٲٴ� ó���� �� ���̴�.
	//       (�� �� ó���� code�� �ӵ��� ���� ������ ����.)
	//-----------------------------------------------------------------
	// 1) ���ο� Head�� �� Node�� ��´�.
	_node*	pNow	 = m_head->_pre;

	// 2) ��ġ�� ��´�.
	TDATA&	tempData = pNow->_data;

	// 3) Constructor�� ȣ���Ѵ�.
	m_allocVal.construct(&pNow->_data);

	// 4) �׳� �ϳ� �����.
	m_head			 = pNow;

	// 5) ũ��(size)�� 1 ���δ�.
	++m_size;


	// Return) 
	return	tempData;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::push_back(const_reference _Val)
{
	//-----------------------------------------------------------------
	// 1. Node�� �о �߰��Ѵ�.
	//
	// - Circulare List�� �ٱ��ʿ� ���� Node�� �ִ� ����.
	// - �׳� �ϳ� �а� �ű⿡�ٰ� ���� �߰��� �ϸ� �ȴ�.
	//-----------------------------------------------------------------
	// 1) Constructor�� ȣ���Ѵ�.(Copy constructor�� ȣ��)
	m_allocVal.construct(&m_tail->_data, _Val);


	//-----------------------------------------------------------------
	// 2. ���� Node�� ��� ���� ����� ���� ���.
	//-----------------------------------------------------------------
	// Check) ���� node�� 0�̸� ���� ����� �߰��Ѵ�.
	//        (�̰��� ������� �ȵ��� �ִ��� reserve�� �̷� �ص� ���� ���Ѵ�.)
	if(m_size==m_capacity)
	{
		// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node*	pNewNode	 = m_allocNode.allocate(1);

		// 2) �Ҵ���� ���ο� Node�� ���� �ִ´�.
		LINK_NODE(pNewNode, m_tail->_next);
		LINK_NODE(m_tail, pNewNode);

		// 3) m_tail���� �����Ѵ�.
		m_tail	 = pNewNode;

		// 4) �Ҵ���� ���� ũ�⸦ 1 �ø���.
		++m_size;
		++m_capacity;

		// Return) 
		return;
	}

	//-----------------------------------------------------------------
	// 3. �׳� ���� ���.
	//-----------------------------------------------------------------
	// 1) �׳� �ϳ� �����.
	m_tail		 = m_tail->_next;

	// 2) ũ��(size)�� 1 ���δ�.
	++m_size;
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::reference circular_list<TDATA, TALLOCATOR>::push_back()
{
	//-----------------------------------------------------------------
	// 1. Node�� �о �߰��Ѵ�.
	//
	// - Circulare List�� �ٱ��ʿ� ���� Node�� �ִ� ����.
	// - �׳� �ϳ� �а� �ű⿡�ٰ� ���� �߰��� �ϸ� �ȴ�.
	//-----------------------------------------------------------------
	// 1) ��(value)�� ��ġ�� �����س��´�.
	TDATA&	tempData = m_tail->_data;


	//-----------------------------------------------------------------
	// 2. ���� Node�� ���� ���.
	//-----------------------------------------------------------------
	if(m_size!=m_capacity)
	{
		// 1) �׳� �ϳ� �����.
		m_tail		 = m_tail->_next;

		// 2) ũ��(size)�� 1 ���δ�.
		++m_size;
	}
	//-----------------------------------------------------------------
	// 3. ���� Node�� ���� ���.
	//-----------------------------------------------------------------
	// Check) ���� node�� 0�̸� ���� ����� �߰��Ѵ�.
	//        (�̰��� ������� �ȵ��� �ִ��� reserve�� �̷� �ص� ���� ���Ѵ�.)
	else
	{
		// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node*	pNewNode	 = m_allocNode.allocate(1);

		// 2) �Ҵ���� ���ο� Node�� ���� �ִ´�.
		LINK_NODE(pNewNode, m_tail->_next);
		LINK_NODE(m_tail, pNewNode);

		// 3) m_tail���� �����Ѵ�.
		m_tail	 = pNewNode;

		// 4) �Ҵ���� ���� ũ�⸦ 1 �ø���.
		++m_size;
		++m_capacity;
	}

	// Return) 
	return	tempData;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::pop_front()
{
	//-----------------------------------------------------------------
	// Check) Empty�˻�.
	//-----------------------------------------------------------------
	// 1) ��� �ִµ� pop�� �ϸ� �ȵǻ�.
	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ��������� �ʰ� �׳� ������.
	if(empty())
	{
		return;
	}
	#endif


	//-----------------------------------------------------------------
	// 1. Pop�Ѵ�.
	//-----------------------------------------------------------------
	// 1) Destroy�� ȣ���Ѵ�.
	m_allocVal.destroy(&m_head->_data);

	// 2) Head�� ��ĭ �����.
	m_head	 = m_head->_next;

	// 3) ũ��(size)�� 1 ���δ�.
	--m_size;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::pop_back()
{
	//-----------------------------------------------------------------
	// Check) Empty�˻�.
	//-----------------------------------------------------------------
	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ��������� �ʰ� �׳� ������.
	CGD_RETURN_IF(empty(),);
	#endif


	//-----------------------------------------------------------------
	// 1. Pop�Ѵ�.
	//-----------------------------------------------------------------
	// 1) Tail�� ��ĭ �����.
	m_tail	 = m_tail->_pre;

	// 2) Safe Iteratoró��
	#ifdef CGD_USE_SAFE_ITERATOR
	if(m_safe_iterator._Ptr==m_tail)
	{
		m_safe_iterator._Ptr=m_tail->_pre;
	}
	#endif

	// 3) Destroy�� ȣ���Ѵ�.
	m_allocVal.destroy(&m_tail->_data);

	// 4) ũ��(size)�� 1 ���δ�.
	--m_size;
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::iterator circular_list<TDATA, TALLOCATOR>::insert(const_iterator _Where, const_reference _Val)
{
	//-----------------------------------------------------------------
	// 1. Head�� ���.
	//-----------------------------------------------------------------
	// - Head�� ��� push_front�� ��.
	if(_Where==begin())
	{
		// - push_front�� ��.
		push_front(_Val);

		// - begin()�� return��~
		return	begin();
	}

	//-----------------------------------------------------------------
	// 2. ���� node�� �����ϰ� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
	_node*	pNewNode;

	if(m_size==m_capacity)
	{
		// - ���ο� Node�� �Ҵ�޴´�.
		pNewNode	 = _newNode(_Val);

		// - Capacity�� �����Ѵ�.(���� �Ҵ�޴� �Ŵϱ�...)
		++m_capacity;
	}
	else
	{
		// - ��� Node�� ����.
		pNewNode	 = m_tail->_next;

		// - �ʱ�ȭ�Ѵ�.
		m_allocVal.construct(&pNewNode->_data, _Val);

		// - �� Node�� �����Ѵ�. List���� �����Ѵ�.
		LINK_NODE(m_tail, pNewNode->_next);
	}

	// 2) ������ �� Node
	_node*	pNode		 = _Where._Ptr;

	// 3) Link�� �Ǵ�.
	LINK_NODE(pNode->_pre, pNewNode);
	LINK_NODE(pNewNode, pNode);

	// 4) �Ҵ���� ����(allocated)�� ũ��(size)�� 1 �ø���.
	++m_size;

	// Return) 
	return iterator(pNewNode);
}


//-----------------------------------------------------------------
// CGD::circular_list)
//
//  insert: _Val���� circular_list���� �����Ѵ�.
//
// ����)
//  Iist Insert ���� ������ �ٽ��� �ٷ� circular�� backside�� ������
//  Node���� �̹� circular_list�� ����Ǿ��� ���̹Ƿ� �̰Ϳ��ٰ� ���ʷ� 
//  ���� ������ �� Insert�Ҹ�ŭ�� ����� Insert�� ���ϴ� ��(_Where)�� 
//  ����ִ� �ٴ� ���̴�.
//   ���⼭ ���� ������ Node�� ������ ��쿡�� ���� �����Ͽ� Node��
//  ����ó���� �Ѵ�.
//   ó�� �˰��� ���� �׿� ���� �ۼ��Ǿ��� �ִ�.
//  �Ѳ����� �����Ϸ��� node�� ������ ���� ���� ������ std::list��
//  insert�� ���� �������̸� ����.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::insert(const_iterator _Where, int _Count, const_reference _Val)
{
	// Check) _Count�� 0�̰ų� ���� ������ �ٷ� �����Ѵ�.
	CGD_RETURN_IF(_Count<=0,);


	//-----------------------------------------------------------------
	// 1. ���鼭 �����Ѵ�.
	//-----------------------------------------------------------------
	// Declare) 
	iterator	iterInsert;
	iterator	iterEnd;
	int			count;
	size_type	capacityInc	 = 0;

	CGD_TRY
	{
		// 1) �߰��� �ϱ� ���� ���� Node�� ��´�.
		//    (tail�� next���Ͱ� ���� Node�̴�.)
		iterInsert	 = ++end();	// m_tail�� _next.

		// 2) ���� Node�� ���� Insert�ϱ� �����Ѵ�.
		for (count=_Count; (count >0) && (iterInsert!=begin()); --count, ++iterInsert)
		{
			// - Construct�Ѵ�.
			m_allocVal.construct(&(*iterInsert), _Val);
		}

		// 3) ����� ������ Node�� �����Ѵ�.(��� Node�� �������� ����...)
		//    (iterInsert�� ���� Node�� �̾ ������ �Ѵ�.)
		iterEnd		 = iterInsert--;

		// 4) �߰��Ҵ� �Ǵ� Node ������ �����Ѵ�.
		//    (���� count�� �߰��ؾ��� Node���̴�.)
		capacityInc	 = count;

		// 5) �����ؼ� ������ Node���� �߰��Ѵ�.
		for (; count >0; --count)
		{
			// - Node�� ���� �����Ѵ�.
			_node*	nodeNew	 = _newNode(_Val);

			// - Node�� �߰��Ѵ�.
			LINK_NODE(iterInsert._Ptr, nodeNew);

			// - iterInsert�� nodeNew�� �Ѵ�.
			iterInsert	 = nodeNew;
		}
	}
	// Exception) Roll back�Ѵ�.
	CGD_CATCH_ALL
	{
		// 1) �� Node��..
		iterator	nodeRollback = ++end();

		// 2) Role back�ϸ� destroy�Ѵ�.
		while(nodeRollback!=iterInsert)
		{
			// - node�� destroy�Ѵ�.
			m_allocVal.destroy(&(*nodeRollback));

			// - ���� Node�� �����Ѵ�.
			--nodeRollback;
		}

		// 3) �߰��Ҵ��ߴ� Node���� ��� Deallocate�Ѵ�.
		while(iterEnd!=iterInsert)
		{
			// - ��������� �̸� Next�� �����´�.
			iterator	temp = iterEnd++;

			// - node�� destroy�Ѵ�.
			m_allocVal.destroy(&(*temp));
		}

		// Throw) �ٽ� Throw!!!
		CGD_RETHROW;
	}


	//-----------------------------------------------------------------
	// 2. Link�߰��ϱ�.
	//-----------------------------------------------------------------
	// 1) ������ ù��° Node�� ���.
	_node*	nodeStart	 = m_tail->_next;

	// 2) _Where�� Head�� ��� Head�� �ٲٱ�.
	if(_Where._Ptr == m_head)
	{
		m_head	 = nodeStart;
	}

	// 3) �߰��� List�� �ϴ� ������ Circular List�� �ݴ´�.
	LINK_NODE(m_tail, iterEnd._Ptr);

	// 4) _Where�� ����ֱ�
	LINK_NODE(_Where._Ptr->_pre, nodeStart);
	LINK_NODE(iterInsert._Ptr, _Where._Ptr);


	//-----------------------------------------------------------------
	// 3. Node������ ����Ѵ�.
	//-----------------------------------------------------------------
	// 1) �Ҵ���� ����(allocated)�� ũ��(size)�� _Count��ŭ �ø���.
	m_size		+= _Count;

	// 2) capacity�� �����Ѵ�.
	m_capacity	+= capacityInc;
}


template <class TDATA, class TALLOCATOR>
template <class TITERATOR>
void circular_list<TDATA, TALLOCATOR>::insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last)
{
	// Check) �ϳ��� ���ٸ� �ٷ� ����...
	CGD_RETURN_IF(_First==_Last, );


	//-----------------------------------------------------------------
	// 1. ���鼭 �����Ѵ�.
	//-----------------------------------------------------------------
	// Declare) 
	iterator	iterInsert;
	iterator	iterEnd;
	int			count	 = 0;
	size_type	capacityInc	 = 0;

	CGD_TRY
	{
		// 1) �߰��� �ϱ� ���� ���� Node�� ��´�.
		//    (tail�� next���Ͱ� ���� Node�̴�.)
		iterInsert	 = ++end();	// m_tail�� _next.

		// 2) ���� Node�� ���� Insert�ϱ� �����Ѵ�.
		for (count=0; (_First != _Last) && (iterInsert!=begin()); ++_First, ++iterInsert, ++count)
		{
			// - Construct�Ѵ�.
			m_allocVal.construct(&(*iterInsert), *_First);
		}

		// 3) ����� ������ Node�� �����Ѵ�.(��� Node�� �������� ����...)
		//    (iterInsert�� ���� Node�� �̾ ������ �Ѵ�.)
		iterEnd		 = iterInsert--;

		// 4) �����ؼ� ������ Node���� �߰��Ѵ�.
		for (capacityInc=0; _First != _Last; ++_First, ++capacityInc)
		{
			// - Node�� ���� �����Ѵ�.
			_node*	nodeNew	 = _newNode(*_First);

			// - Node�� �߰��Ѵ�.
			LINK_NODE(iterInsert._Ptr, nodeNew);

			// - iterInsert�� nodeNew�� �Ѵ�.
			iterInsert	 = nodeNew;
		}
	}
	// Exception) Roll back�Ѵ�.
	CGD_CATCH_ALL
	{
		// 1) �� Node��..
		iterator	nodeRollback = ++end();

		// 2) Role back�ϸ� destroy�Ѵ�.
		while(nodeRollback!=iterInsert)
		{
			// - node�� destroy�Ѵ�.
			m_allocVal.destroy(&(*nodeRollback));

			// - ���� Node�� �����Ѵ�.
			--nodeRollback;
		}

		// 3) �߰��Ҵ��ߴ� Node���� ��� Deallocate�Ѵ�.
		while(iterEnd!=iterInsert)
		{
			// - ��������� �̸� Next�� �����´�.
			iterator	temp = iterEnd++;

			// - node�� destroy�Ѵ�.
			m_allocVal.destroy(&(*temp));
		}

		// Throw) �ٽ� Throw!!!
		CGD_RETHROW;
	}


	//-----------------------------------------------------------------
	// 2. Link�߰��ϱ�.
	//-----------------------------------------------------------------
	// 1) ������ ù��° Node�� ���.
	_node*	nodeStart	 = m_tail->_next;

	// 2) _Where�� Head�� ��� Head�� �ٲٱ�.
	if(_Where._Ptr == m_head)
	{
		m_head	 = nodeStart;
	}

	// 3) �߰��� List�� �ϴ� ������ Circular List�� �ݴ´�.
	LINK_NODE(m_tail, iterEnd._Ptr);

	// 4) _Where�� ����ֱ�
	LINK_NODE(_Where._Ptr->_pre, nodeStart);
	LINK_NODE(iterInsert._Ptr, _Where._Ptr);


	//-----------------------------------------------------------------
	// 3. Node������ ����Ѵ�.
	//-----------------------------------------------------------------
	// 1) �Ҵ���� ����(allocated)�� ũ��(size)�� _Count��ŭ �ø���.
	m_size		+= (count+capacityInc);

	// 2) capacity�� �����Ѵ�.
	m_capacity	+= capacityInc;
}



//-----------------------------------------------------------------
// CGD::circular_list)
//
//  erase: ���õ� node���� �����Ѵ�.
//
// ����)
//   erase�Լ��� _Where�� ���ؼ� ������ ��ġ�� Ȥ�� ������ ������
//  node�� �����ϴ� �Լ��̴�. 
//   erase�Լ��� �ش��ϴ� �κ��� node���� ���Ÿ� ������ �ش� node
//  ���� deallocate��Ű���� �ʴ´�. ���ŵ� node���� tail�� ������
//  ������ node�� ������ ���� insert�� push ���� �� �� ��Ȱ��ȴ�.
//  ���� deallocate�� �ɸ��� �ð� ��ŭ �ð��� ������ �� �ִ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::iterator circular_list<TDATA, TALLOCATOR>::erase(const_iterator _Where)
{
	//-----------------------------------------------------------------
	// ChecK)
	//-----------------------------------------------------------------
	// 1) _Wherer�� tail�̸� �ȵȴ�.
	CGDASSERT_ERROR(_Where != end());

	// 2) �̰� ��.. �翬�ϴ�~
	CGDASSERT(_Where._Ptr!=0, iterator());


	//-----------------------------------------------------------------
	// 1. Head�� ��� pop_front�� ��.
	//-----------------------------------------------------------------
	// - Head�� ��� push_front�� ��.
	if(_Where==begin())
	{
		// - push_front�� ��.
		pop_front();

		// - begin()�� return��.
		return	begin();
	}


	//-----------------------------------------------------------------
	// 2. List���� ����
	//-----------------------------------------------------------------
	// 1) ���� Node
	_node*	tempNode	 = _Where._Ptr;

	// 2) ���� Node���� ������.
	_node*	pnodePre	 = tempNode->_pre;
	_node*	pnodeNext	 = tempNode->_next;

	// 3) Link�Ѵ�.
	LINK_NODE(pnodePre, pnodeNext);

	// 4) Safe Iteratoró��
	#ifdef CGD_USE_SAFE_ITERATOR
	if(m_safe_iterator._Ptr==tempNode)
	{
		m_safe_iterator._Ptr=pnodePre;
	}
	#endif


	//-----------------------------------------------------------------
	// 3. ���� Node�� �Ҵ������Ѵ�.
	//-----------------------------------------------------------------
	// 1) Destruct�� ȣ���Ѵ�.
	m_allocNode.destroy(tempNode);

	// 2) �����.
	LINK_NODE(tempNode, m_tail->_next); 
	LINK_NODE(m_tail, tempNode);


	//-----------------------------------------------------------------
	// 4. Node���� ó��
	//-----------------------------------------------------------------
	// 1) ũ�⸦ 1 ���δ�.
	--m_size;


	// Return) Next Node�� Iterator�� �ǵ����ش�.
	return	iterator(pnodeNext);
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::iterator circular_list<TDATA, TALLOCATOR>::erase(const_iterator _First, const_iterator _Last)
{
	//-----------------------------------------------------------------
	// 1. Destroy�ϸ� ���� ���Ƹ���...
	//-----------------------------------------------------------------
	// 1) First Node�� PreNode�� �̸� ���س��´�.
	_node*			tempNodeFirst	 = _First._Ptr->_pre;

	// 2) ����... �پ��� ���ڸ� Ȯ���ϱ� ���� ������.
	size_type		count	 = 0;
	const_iterator	temp	 = _First;
	while(temp != _Last)
	{
		// Check) temp�� end���� ���� �ȵȴ�.
		CGDASSERT_ERROR(temp!=end());

		// Declare) ���� Node�� ������ ����.
		iterator	tempDel;

		// - Delete�� Node�� �ް� ���� Node��...
		tempDel	 = temp++;

		// - Safe Iteratoró��
		#ifdef CGD_USE_SAFE_ITERATOR
		if(m_safe_iterator._Ptr==tempDel._Ptr)
		{
			m_safe_iterator._Ptr=tempNodeFirst;
		}
		#endif

		// - Destruct�� ȣ���Ѵ�.
		m_allocVal.destroy(&(*tempDel));

		// - ���ڸ� ���Ѵ�.
		++count;
	}

	// Check) ���࿡ ������ 0����� �׳� return
	CGD_RETURN_IF(count==0, iterator(temp._Ptr));


	//-----------------------------------------------------------------
	// 2. ���� �����ϱ�.
	//-----------------------------------------------------------------
	// 1) erase�� ��ŭ ũ�⸦ ���δ�.
	m_size		-= count;

	// 2) ó���� ��� Head�� �����.
	if(_First==begin())
	{
		// - Head�� �����...
		m_head	 = _Last._Ptr;
		
		// Return) �ǵ�����..
		return	iterator(temp._Ptr);;
	}

	// 3) ���� ��� Tail�� �����.
	if(_Last==end())
	{
		// - Tail�� �����...
		m_tail	 = temp._Ptr;
		
		// Return) �ǵ�����..
		return	iterator(temp._Ptr);
	}

	// 4) Tail�ڿ� ���̱�.
	LINK_NODE(temp._Ptr->_pre, m_tail->_next); 
	LINK_NODE(m_tail, _First._Ptr);

	// 5) ���� List�� ������.
	LINK_NODE(tempNodeFirst, temp._Ptr);


	// Return) 
	return	iterator(temp._Ptr);
}



//-----------------------------------------------------------------
// CGD::circular_list)
//
//  attach: _Where�� _node�� node ��ä�� ���δ�.
//  detach : _Where�� _node�� node ��ä�� ������.
//
// ����)
//  insert�� erase�� ���� ����� �Լ��̴�. �׷��� attach�� detach��
//  node ��ä�� ����� �Լ��̴�.
//  splice�� �� ����� ���� circular_list��� �Ѵٸ� �� �Լ��� �׳� �ش� node
//  ���� ������� �Ѵ�. �� node��ü�� �����Ҵٰ� node��ü�� ���δ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::attach(const_iterator _Where, const_iterator _Node)
{
	//-----------------------------------------------------------------
	// ChecK)
	//-----------------------------------------------------------------
	// 1) _Wherer�� tail�̸� �ȵȴ�.
	CGDASSERT_ERROR(_Where != end());

	// 2) �̰� ��.. �翬�ϴ�~
	CGDASSERT(_Where._Ptr!=0,);


	//-----------------------------------------------------------------
	// 2. �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) ������ �� Node
	_node*	pNode		 = _Where._Ptr;
	_node*	pNewNode	 = _Node._Ptr;

	// 2) Link�� �Ǵ�.
	LINK_NODE(pNode->_pre, pNewNode);
	LINK_NODE(pNewNode, pNode);

	// 3) _Wherer�� Head�� ��� m_head�� _Node�� �����.
	if(_Where==begin())
	{
		m_head	 = pNewNode;
	}

	// 4) �Ҵ���� ����(allocated)�� ũ��(size)�� 1 �ø���.
	++m_size;
	++m_capacity;
}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::detach(const_iterator _Where)
{
	//-----------------------------------------------------------------
	// ChecK)
	//-----------------------------------------------------------------
	// 1) _Wherer�� tail�̸� �ȵȴ�.
	CGDASSERT_ERROR(_Where != end());

	// 2) �̰� ��.. �翬�ϴ�~
	CGDASSERT(_Where._Ptr!=0,);


	//-----------------------------------------------------------------
	// 1. Head�� ��� Head�� ��ĭ �δ�.
	//-----------------------------------------------------------------
	// - Head�� ��� push_front�� ��.
	if(_Where==begin())
	{
		// - Head�� ��ĭ �����.
		m_head	 = m_head->_next;
	}


	//-----------------------------------------------------------------
	// 2. List���� ����
	//-----------------------------------------------------------------
	// 1) ���� Node
	_node*	tempNode	 = _Where._Ptr;

	// 2) ���� Node���� ������.
	_node*	pnodePre	 = tempNode->_pre;
	_node*	pnodeNext	 = tempNode->_next;

	LINK_NODE(pnodePre, pnodeNext);

	// 3) ũ�⸦ 1 ���δ�.
	--m_size;
	--m_capacity;
}


//-----------------------------------------------------------------
// CGD::circular_list)
//
//  remove: _Val���� circular_list���� �����Ѵ�.
//
// ����)
//  �Ϲ������� vector���� ��� remove�� �����ϰ� �Ǹ� ������ ����
//  ������ ������ circular_list�� ��� remove�� �� ���Ŀ� size�� ���δ�.
//  �˰���� ������ std::list�� unique�� ���̰� ����.
//  (�� erase��ü�� ó���ӵ��� ���� �ణ�� ��������� ���� �� �ִ�.)
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::remove(const_reference _Val)
{
	//-----------------------------------------------------------------
	// 1. ������... �ش��ϴ� ���� �����Ѵ�.
	//-----------------------------------------------------------------
	int			count	 = 0;
	iterator	iterEnd	 = end();
	for(iterator iter=begin();iter!=iterEnd;)
	{
		if(*iter == _Val)
		{
			// - iterator�� ������ ����Ű���ϰ� ���� iterator�� �޾� ���´�.
			iterator	nodeRemove	 = iter++;

			// - Destruct�� ȣ���ϰ� tempNode�� �����.
			m_allocVal.destroy(&(*nodeRemove));

			// - ���� Node �� ���.
			++count;

			// Check) ó���� ��� Head�� �����.
			if(nodeRemove==begin())
			{
				// - Head�� �����...
				m_head	 = m_head->_next;
				continue;
			}

			// - safe iterator ó��
			#ifdef CGD_USE_SAFE_ITERATOR
			if(m_safe_iterator._Ptr==nodeRemove._Ptr)
			{
				--m_safe_iterator;
			}
			#endif

			// Check) ���� ��� Tail�� �����.
			if(iter==end())
			{
				// - Tail�� �����...
				m_tail	 = m_tail->_pre;
				continue;
			}

			// - ���� Node���� ������.
			LINK_NODE(nodeRemove._Ptr->_pre, nodeRemove._Ptr->_next);

			// - Node�� Deallocate�Ѵ�.
			LINK_NODE(nodeRemove._Ptr, m_tail->_next); 
			LINK_NODE(m_tail, nodeRemove._Ptr);

			// ����~
			continue;
		}

		// - ����...
		++iter;
	}


	//-----------------------------------------------------------------
	// 2. ���ŵ� ������ŭ ���δ�.
	//-----------------------------------------------------------------
	// ���ŭ ũ�⸦ ���δ�.
	m_size		-= count;
	m_capacity	-= count;
}


//-----------------------------------------------------------------
//
//  remove_if: _Pred�Լ��� ����� TRUE�� �Լ��� �����Ѵ�.
//
// ����)
//  �������� �˻��ϴ� �κ��� _Pred�Լ��� ȣ���ϵ��� ��ü�Ͽ� �ش�
//  �Լ��� ����� TRUE�� ��� �ش� node�� ����� remove�Լ��̴�.
//  Ư�� ���ǿ� �����ϴ� node�� �����ϰ� ���� �� ����ϸ� �ȴ�.
//  _Pred�Լ����� �ش� node�� iterator�� �����Ǹ� return�Ǵ� ����
//  true�̸� �ش� node�� �����Ѵ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
template<typename _Pr1>
void circular_list<TDATA, TALLOCATOR>::remove_if(_Pr1 _Pred)
{
	//-----------------------------------------------------------------
	// 1. ������... �ش��ϴ� ���� �����Ѵ�.
	//-----------------------------------------------------------------
	int			count	 = 0;
	iterator	iterEnd	 = end();
	for(iterator iter=begin();iter!=iterEnd;)
	{
		if(_Pred(*iter))
		{
			// - iterator�� ������ ����Ű���ϰ� ���� iterator�� �޾� ���´�.
			iterator	nodeRemove	 = iter++;

			// - Destruct�� ȣ���ϰ� tempNode�� �����.
			m_allocVal.destroy(&(*nodeRemove));

			// - ���� Node �� ���.
			++count;

			// Check) ó���� ��� Head�� �����.
			if(nodeRemove==begin())
			{
				// - Head�� �����...
				m_head	 = m_head->_next;
				continue;
			}

			// - safe iterator ó��
#ifdef CGD_USE_SAFE_ITERATOR
			if(m_safe_iterator._Ptr==nodeRemove._Ptr)
			{
				--m_safe_iterator;
			}
#endif

			// Check) ���� ��� Tail�� �����.
			if(iter==end())
			{
				// - Tail�� �����...
				m_tail	 = m_tail->_pre;
				continue;
			}

			// - ���� Node���� ������.
			LINK_NODE(nodeRemove._Ptr->_pre, nodeRemove._Ptr->_next);

			// - Node�� Deallocate�Ѵ�.
			LINK_NODE(nodeRemove._Ptr, m_tail->_next); 
			LINK_NODE(m_tail, nodeRemove._Ptr);

			// ����~
			continue;
		}

		// - ����...
		++iter;
	}


	//-----------------------------------------------------------------
	// 2. ���ŵ� ������ŭ ���δ�.
	//-----------------------------------------------------------------
	// ���ŭ ũ�⸦ ���δ�.
	m_size		-= count;
	m_capacity	-= count;
}




template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::swap(_mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) ���� Container�� ��� �׳� �ǵ�����.
	CGD_RETURN_IF(&_Right==this,);


	//-----------------------------------------------------------------
	// 1. Swap�Ѵ�.
	//-----------------------------------------------------------------
	// CaseA) Allocator�� ������...
	if (m_allocVal == _Right.m_allocVal)
	{
		// �ٲ۴�~(������~)
		CGD_SWAP(m_head,	_Right.m_head);
		CGD_SWAP(m_tail,	_Right.m_tail);
		CGD_SWAP(m_size,	_Right.m_size);
		CGD_SWAP(m_capacity,_Right.m_capacity);
	}
	// CaseB) Allocator�� �ٸ���...
	else
	{
		iterator _Where = begin();
		splice(_Where, _Right);
		_Right.splice(_Right.begin(), *this, _Where, end());
	}
}


//-----------------------------------------------------------------
// CGD::circular_list)
//
//  unique: List���� ���������� ���� ���� ������ Node�� �����Ѵ�.
//
// ����)
//  List���� ���������� ���� ���� ������ node�� �����ϴ� �Լ���
//  sort�� �� ���Ŀ� ����ؾ� ��Ȯ�� unique�� ���鸸 ���� �� �ִ�.
//  �˰���� ������ std::list�� unique�� ���̰� ����.
//  (�� erase��ü�� ó���ӵ��� ���� �ణ�� ��������� ���� �� �ִ�.)
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::unique()
{
	//-----------------------------------------------------------------
	// ����) Unique�Լ�.
	//   Unique�Լ��� �������� �ߺ������� �����ϴ� �Լ��̴�.
	//   ���� ������ ó������ ������ iteration�� ���鼭 ������ ����
	//   �� �����. ��~
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	// Check) ũ�Ⱑ 2���� ������ �׳� �ǵ�����.
	//-----------------------------------------------------------------
	CGD_RETURN_IF(m_size<2,);


	//-----------------------------------------------------------------
	// 1. ���� ���� �����Ѵ�.
	//-----------------------------------------------------------------
	// Declare) 
	iterator _First = begin();
	iterator _After = _First;

	// 1) Iteration�� ����.
	for (++_After; _After != end(); )
	{
		// Check) _First�� _After�� ������ _After�� �����.
		if (_Pred(*_First, *_After))
		{
			_After = erase(_After);
			continue;
		}

		// - ����~(_After�� _First�� �ִ´�.)
		_First = _After++;
	}
}

template <class TDATA, class TALLOCATOR>
template<typename _Pr2>
void circular_list<TDATA, TALLOCATOR>::unique(_Pr2 _Pred)
{
	//-----------------------------------------------------------------
	// Check) ũ�Ⱑ 2���� ������ �׳� �ǵ�����.
	//-----------------------------------------------------------------
	CGD_RETURN_IF(m_size<2,);


	//-----------------------------------------------------------------
	// 1. ���� ���� �����Ѵ�.
	//-----------------------------------------------------------------
	iterator _First = begin();
	iterator _After = _First;

	for (++_After; _After != end();)
	{
		// Check) _First�� _After�� ������ _After�� �����.
		if (*_First == *_After)
		{
			_After = erase(_After);
			continue;
		}

		// - ����~(_After�� _First�� �ִ´�.)
		_First = _After++;
	}
}



//-----------------------------------------------------------------
// CGD::circular_list)
//
//  splice: ������ node���� ��ä�� �ű��.
//
// ����)
//   circular_list�� ���� node����� container�� ���� ���� �߿� �ϳ��� 
//  Ư�� node�� move�Ҷ� �ش��ϴ� node�� ���Ḹ �� ���� ���� ���ϴ� ������
//  �̵��� �����ϴ�. splice�� �ٷ� �̷� ������ �ϴ� �Լ��̴�.
//  std::list������ sort������ ���� ���ȴ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::splice(const_iterator _Where, _mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	CGD_RETURN_IF(this == &_Right || _Right.empty(),);


	//-----------------------------------------------------------------
	// 1. Right���� ������.
	//-----------------------------------------------------------------
	_node*	rightFirst	 = _Right.m_head;
	_node*	rightLast	 = _Right.m_tail->_pre;

	// List�� 0��...
	LINK_NODE(_Right.m_tail, _Right.m_tail);
	_Right.m_head	 = _Right.m_tail;

	// Size�� Capasity�� ����Ѵ�.
	_Right.m_capacity	-= _Right.m_size;
	m_size				+= _Right.m_size;	// ���� ���ϱ�~
	m_capacity			+= _Right.m_size;

	// Right�� Size�� 0����..
	_Right.m_size		 = 0;


	//-----------------------------------------------------------------
	// 2. Right���� ���� �� ���̱�.
	//-----------------------------------------------------------------
	// 1) �����ų �հ� �� Node
	_node*	pNext	 = _Where._Ptr;
	_node*	pPre	 = pNext->_pre;

	// 2) right First�� pPre�� ����
	LINK_NODE(pPre, rightFirst);

	// 3) right Last�� pNext�� ����
	LINK_NODE(rightLast, pNext);

	// 4) _Where�� Head�� ���...
	if(_Where._Ptr==m_head)
	{
		m_head	 = rightFirst;
	}
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::splice(const_iterator _Where, _mytype& _Right, const_iterator _First)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) ���� _Right�� ������ ���� �ϳ��� ������ Return
	CGD_RETURN_IF(_First == _Right.end(),);

	// 2) _Right�� this�̸鼭 ó���̳� ���̸� Return~
	CGD_RETURN_IF(this == &_Right && (_Where == _First || _Where == end()), );


	//-----------------------------------------------------------------
	// 1. Right���� ������.
	//-----------------------------------------------------------------
	// 1) ���Ŀ� ó���� ���� ��� �κ��� �����س��´�.
	_node*	rightFirst	 = _First._Ptr;
	_node*	rightLast	 = _Right.m_tail->_pre;

	// 2) ���� ��ü�� ������ ���Ƹ���.
	int		count		 = 0;
	for(; _First!=_Right.end(); ++_First)
	{
		++count;
	}


	//-----------------------------------------------------------------
	// 1. Right���� ������.
	//-----------------------------------------------------------------
	// 1) Right�� List���� �ش� �κ��� ����� �� �յڸ�����~
	LINK_NODE(_First._pre, _Right.m_tail);

	// 2) Size�� Capasity�� ����Ѵ�.
	_Right.m_capacity	-= count;
	_Right.m_size		-= count;
	m_size				+= count;	// ���� ���ϱ�~
	m_capacity			+= count;


	//-----------------------------------------------------------------
	// 2. Right���� ���� �� ���̱�.
	//-----------------------------------------------------------------
	// 1) �����ų �հ� �� Node
	_node*	pNext	 = _Where._Ptr;
	_node*	pPre	 = pNext->_pre;

	// 2) right First�� pPre�� ����
	LINK_NODE(pPre, rightFirst);

	// 3) right Last�� pNext�� ����
	LINK_NODE(rightLast, pNext);
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::splice(const_iterator _Where, _mytype& _Right, const_iterator _First, const_iterator _Last)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	CGD_RETURN_IF(_First == _Last || (this == &_Right && _Where == _Last),);


	//-----------------------------------------------------------------
	// 1. Right���� ������.
	//-----------------------------------------------------------------
	// 1) ���Ŀ� ó���� ���� ��� �κ��� �����س��´�.
	_node*	rightFirst	 = _First._Ptr;
	_node*	rightLast	 = _Last._Ptr->_pre;

	// 2) ���� ��ü�� ������ ���Ƹ���.
	size_type	count		 = 0;

	// 3-1) ���� Container��� ������ȭ�� ����! ���� ���Ƹ� �ʿ����.
	if (this == &_Right)
	{
		;	
	}
	// 3-2) ��ä�ζ� ���Ƹ� �ʿ����.
	else if (_First == _Right.begin() && _Last == _Right.end())
	{
		count = _Right.m_size;	
	}
	else
	{
		for(; _First!=_Last; ++_First)
		{
			++count;
		}
	}


	//-----------------------------------------------------------------
	// 1. Right���� ������.
	//-----------------------------------------------------------------
	// 1) Right�� List���� �ش� �κ��� ����� �� �յڸ�����~
	LINK_NODE(_First._Ptr->_pre, _Last._Ptr);

	// 2) Size�� Capasity�� ����Ѵ�.
	_Right.m_capacity	-= count;
	_Right.m_size		-= count;
	m_size				+= count;	// ���� ���ϱ�~
	m_capacity			+= count;


	//-----------------------------------------------------------------
	// 2. Right���� ���� �� ���̱�.
	//-----------------------------------------------------------------
	// 1) �����ų �հ� �� Node
	_node*	pNext	 = _Where._Ptr;
	_node*	pPre	 = pNext->_pre;

	// 2) right First�� pPre�� ����
	LINK_NODE(pPre, rightFirst);

	// 3) right Last�� pNext�� ����
	LINK_NODE(rightLast, pNext);
}




//-----------------------------------------------------------------
// CGD::circular_list)
//
//  merge: _Right list�� _Pred���ǿ� ���� ���� list�� ��ģ��.
//
// ����)
//   _Right list�� _Pred ���ǿ� ���� ���� list�� ��ģ��. 
//  �� list�� ��� sort�� �Ǿ� �־�� ���ϴ� ������ ��Ȯ�� ������ 
//  ����.
//  �⺻���� �˰����� std::list�� �����ϴ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
template<typename _Pr3>
void circular_list<TDATA, TALLOCATOR>::merge(_mytype& _Right, _Pr3 _Pred)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) ���� list��� Merge�� �� �ʿ� ����.
	CGD_RETURN_IF(&_Right == this,);


	//-----------------------------------------------------------------
	// 1. Merge�� ��Ų��.
	//-----------------------------------------------------------------
	// 1) ������������ Ȯ���Ѵ�.
	if(front() >= _Right.back())
	{
		// - Right�� m_head �տ� ��ä�� ���̱�.
		LINK_NODE(m_head->_pre, _Right.m_head)
		LINK_NODE(_Right.m_tail->pre, m_head)
	}
	// 2) ������������ Ȯ���Ѵ�.
	else if(back() <= _Right.front())
	{
		// - _Right�� m_tail �ڿ� ��ä�� ���̱�
		LINK_NODE(m_tail->_pre, _Right.m_head)
		LINK_NODE(_Right.m_tail->_pre, m_tail)
	}
	// 3) ���ʷ� ���̱�...(tempList�� Main�̰� binList�� ���⿡ �ٴ� ����.)				
	else
	{
		// NodeA�� NodeB�� �����Ѵ�.
		_node*	nodeA		 = m_head;
		nodeA->_pre			 = m_head->_pre;
		_node*	nodeB		 = _Right.m_head;

		for(;;)
		{
			// B�� Next��(B�� A�տ� ���� �ִ´�.)
			if(_Pred(nodeA->_data, nodeB->_data))
			{
				// - nodeB�� ��� ��� ���´�.
				_node*	tempBNext	 = nodeB->_next;

				// - nodeB�� NodeA�տ� ���δ�.
				LINK_NODE(nodeA->_pre, nodeB);
				LINK_NODE(nodeB, nodeA);

				// - nodeB�� �������� �ű��.
				nodeB	 = tempBNext;

				// - nodeB�� ������ Ȯ���Ѵ�.
				CGD_BREAK_IF(tempBNext==_Right.m_tail);
			}
			// A�� Next��(�׳� �ѱ��.)
			else
			{
				// nodeA�� �������� �ű��.
				_node*	tempANext	 = nodeA->_next;

				// nodeA�� ������ Ȯ���Ѵ�.
				if(tempANext==m_tail)
				{
					// nodeA�ڿ� nodeB�� ���δ�.
					LINK_NODE(nodeA, nodeB);
					LINK_NODE(nodeB, m_tail);

					break;
				}

				nodeA		 = tempANext;
			}
		}
	}


	//-----------------------------------------------------------------
	// 2. �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) _Right.m_size�� �ӽ÷� ������ ���´�.
	size_type	tempSize	 = _Right.m_size;

	// 1) List�� Size�� Count�� �����Ѵ�.
	m_size	+= tempSize;
	m_size	+= tempSize;

	// 2) Right List�� Size�� Count�� �����Ѵ�.
	_Right.m_size	 = 0;
	_Right.m_size	-= tempSize;

	// 3) Right List�� �����Ѵ�.
	LINK_NODE(_Right.m_head, _Right.m_head);
	_Right.m_tail	 = _Right.m_head;

}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::merge(_mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) ���� list��� Merge�� �� �ʿ� ����.
	CGD_RETURN_IF(&_Right == this,);


	//-----------------------------------------------------------------
	// 1. Merge�� ��Ų��.
	//-----------------------------------------------------------------
	// 1) ������������ Ȯ���Ѵ�.
	if(front() >= _Right.back())
	{
		// - Right�� m_head �տ� ��ä�� ���̱�.
		LINK_NODE(m_head->_pre, _Right.m_head)
		LINK_NODE(_Right.m_tail->pre, m_head)
	}
	// 2) ������������ Ȯ���Ѵ�.
	else if(back() <= _Right.front())
	{
		// - _Right�� m_tail �ڿ� ��ä�� ���̱�
		LINK_NODE(m_tail->_pre, _Right.m_head)
		LINK_NODE(_Right.m_tail->_pre, m_tail)
	}
	// 3) ���ʷ� ���̱�...(tempList�� Main�̰� binList�� ���⿡ �ٴ� ����.)				
	else
	{
		// NodeA�� NodeB�� �����Ѵ�.
		_node*	nodeA		 = m_head;
		nodeA->_pre			 = m_head->_pre;
		_node*	nodeB		 = _Right.m_head;

		for(;;)
		{
			// B�� �������� B�� Next��...
			if(nodeA->_data > nodeB->_data)
			{
				// - nodeB�� ��� ��� ���´�.
				_node*	tempBNext	 = nodeB->_next;

				// - nodeB�� NodeA�տ� ���δ�.
				LINK_NODE(nodeA->_pre, nodeB);
				LINK_NODE(nodeB, nodeA);

				// - nodeB�� �������� �ű��.
				nodeB	 = tempBNext;

				// - nodeB�� ������ Ȯ���Ѵ�.
				CGD_BREAK_IF(tempBNext==_Right.m_tail);
			}
			// A�� Next��(�׳� �ѱ��.)
			else
			{
				// nodeA�� �������� �ű��.
				_node*	tempANext	 = nodeA->_next;

				// nodeA�� ������ Ȯ���Ѵ�.
				if(tempANext==m_tail)
				{
					// nodeA�ڿ� nodeB�� ���δ�.
					LINK_NODE(nodeA, nodeB);
					LINK_NODE(nodeB, m_tail);

					break;
				}

				nodeA		 = tempANext;
			}
		}
	}


	//-----------------------------------------------------------------
	// 2. �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) _Right.m_size�� �ӽ÷� ������ ���´�.
	size_type	tempSize	 = _Right.m_size;

	// 1) List�� Size�� Count�� �����Ѵ�.
	m_size	+= tempSize;
	m_size	+= tempSize;

	// 2) Right List�� Size�� Count�� �����Ѵ�.
	_Right.m_size	 = 0;
	_Right.m_size	-= tempSize;

	// 3) Right List�� �����Ѵ�.
	LINK_NODE(_Right.m_head, _Right.m_head);
	_Right.m_tail	 = _Right.m_head;
}

#ifdef _CGD_LIST_FAST_SORT
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::_slice_for_sort(_node& tempList, _node*& nodeNow)
{
	//-----------------------------------------------------------------
	// ����)
	//  merge sort�� ���� list�� ���� ������ ���� ������ �ϴ� �� �Լ��̴�.
	//  �� �Լ��� 4���� �����ؼ� �����ִ� �Լ��̴�.
	//  �Ѳ����� 4���� node�� �������� ���� sort�� �Ͽ� �����ֱ� ������
	//  2���� ���� �Լ��� ���� �뷫 10%~20%���� �ӵ������ ������ �ش�.
	//  ������ code�� ����ġ�� ����� ���� �����Ƿ� code�� ���� �߿���
	//  ��� 2���� ���� �Լ��� ����ϱ⸦ ���Ѵ�.
	//  (std::list�� ��� 1���� ��� ó���ϵ��� �ؼ� �ӵ����� ���ذ�
	//  �ִ�.)
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	// 1. ù���� ������
	//-----------------------------------------------------------------
	// 1) ù��° Node�� ��´�.
	tempList._next	 = nodeNow;

	// 2) ���� Node
	nodeNow	 = nodeNow->_next;

	// 3) 1�� ���� ��� ������.
	if(nodeNow==0)
	{
		_node*	temp	 = tempList._next;

		tempList._pre	 = temp;
		temp->_next		 = 0;

		return;
	}


	//-----------------------------------------------------------------
	// 2. �ι�° ������
	//-----------------------------------------------------------------
	// 1) 2��° Node�� ��´�.
	_node*	nodeSecond	 = nodeNow;

	// 2) ���� Node
	nodeNow	 = nodeNow->_next;

	// 3) 2���� Sort�Ѵ�.
	if(tempList._next->_data > nodeSecond->_data)
	{
		LINK_NODE(nodeSecond, tempList._next)

		// Check) 2�� ���� ��� ������.
		if(nodeNow==0)
		{
			_node*	temp	 = tempList._next;

			tempList._pre	 = temp;
			temp->_next		 = 0;
			tempList._next	 = nodeSecond;

			return;
		}

		LINK_NODE(tempList._next, nodeNow)
		CGD_SWAP(nodeSecond, tempList._next);
	}

	// Check) 2�� ���� ��� ������.
	if(nodeNow==0)
	{
		tempList._pre		 = nodeSecond;
		nodeSecond->_next	 = 0;
		return;
	}


	//-----------------------------------------------------------------
	// 3. ����° ������
	//-----------------------------------------------------------------
	// 1) 3��° Node�� ��´�.
	_node*	nodeThird	 = nodeNow;

	// 2) ���� Node
	nodeNow	 = nodeNow->_next;

	// 3) 3���� Sort�Ѵ�.
	if(nodeSecond->_data > nodeThird->_data)
	{
		CGD_SWAP(nodeThird, nodeSecond);

		if(tempList._next->_data > nodeSecond->_data)
		{
			LINK_NODE(nodeSecond, tempList._next)
			LINK_NODE(tempList._next, nodeThird)

			CGD_SWAP(nodeSecond, tempList._next);
		}
		else
		{
			LINK_NODE(tempList._next, nodeSecond);
			LINK_NODE(nodeSecond, nodeThird);
		}
	}

	// 4) 3�� ���� ��� ������.
	if(nodeNow!=0)
	{
		LINK_NODE(nodeThird, nodeNow)
	}
	else
	{
		tempList._pre	 = nodeThird;
		nodeThird->_next = 0;
		return;
	}


	//-----------------------------------------------------------------
	// 3. �׹�° ������
	//-----------------------------------------------------------------
	// 1) nodwNow�� 4��°���̴�.
	_node*	nodeForth	 = nodeNow;

	// 2) ���� Node
	nodeNow	 = nodeNow->_next;

	// Sort 4) 4���� Sort�Ѵ�.
	if(nodeThird->_data > nodeForth->_data)
	{
		tempList._pre		 = nodeThird;
		nodeThird->_next	 = 0;

		if(nodeSecond->_data > nodeForth->_data)
		{
			if(tempList._next->_data > nodeForth->_data)
			{
				LINK_NODE(nodeForth, tempList._next);
				tempList._next	 = nodeForth;
			}
			else
			{
				LINK_NODE(tempList._next, nodeForth);
				LINK_NODE(nodeForth, nodeSecond);
			}
		}
		else
		{
			LINK_NODE(nodeSecond, nodeForth);
			LINK_NODE(nodeForth, nodeThird);
		}
	}
	else
	{
		tempList._pre		 = nodeForth;
		nodeForth->_next	 = 0;
	}
}
#else

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::_slice_for_sort(_node& tempList, _node*& nodeNow)
{
	//-----------------------------------------------------------------
	// ����)
	//  merge sort�� ���� list�� ���� ������ ���� ������ �ϴ� �� �Լ��̴�.
	//  �� �Լ��� 2���� �����ؼ� �����ִ� �Լ��̴�.
	//  ���� �Լ��� 4���� �����ִ� �Լ����� ������� ������ �ڵ尡 Ŀ����
	//  �ֱ� ������ ������ code�� ���� ��� �� �Լ��� ����ϱ⸦ ���Ѵ�.
	//  �ӵ��� 10~20%���� �������� code�� ���� 1/3�� ���� �ʴ´�.
	//-----------------------------------------------------------------

	// 1) �ΰ��� Node�� �о���δ�.
	_node*	nodeFirst	 = nodeNow;
	_node*	nodeSecond	 = nodeNow->_next;

	// ChecK) 1�����ΰ��� �˻��Ѵ�.
	if(nodeSecond == 0)
	{
		tempList._next	 = nodeFirst;
		tempList._pre	 = nodeFirst;
		nodeFirst->_next = 0;

		return;
	}

	// 2) ���� Node~
	nodeNow	 = nodeSecond->_next;

	// Case A) First�� �� ũ�� �ٲ۴�.
	if(nodeFirst->_data > nodeSecond->_data)
	{
		LINK_NODE(nodeSecond, nodeFirst);

		tempList._next	 = nodeSecond;
		tempList._pre	 = nodeFirst;
		nodeFirst->_next = 0;
	}
	// Case B) Second�� �� ũ�ų� ������ �״�� �д�.
	else
	{
		tempList._next	 = nodeFirst;
		tempList._pre	 = nodeSecond;
		nodeSecond->_next = 0;
	}
}
#endif

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::_merge_for_sort(_node& tempList, _node& nowList)
{
	//-----------------------------------------------------------------
	// ����)
	//   merge sort�� ���� �ΰ��� �������� list�� �����ִ� �Լ��̴�.
	//  �ϳ��� list�� �������� �ٸ� �ϳ��� list������ ������ �Ǵ� list
	//  ���̿� �����ִ� ���·� code�� �����ȴ�.
	//   ������ lstd::list�� ���ؼ� 0�񱳸� �ϰ� �����ν� ���� �񱳿�
	//  �� ���� �ӵ� ����� ���Ͽ��� ���������� ���� list�� �ٸ� ��
	//  list�� ���� ������ ũ�ų� ���� node�ΰ��� �˻��ϴ� �κ��� �־�
	//  ���� ���� ���ĵ� ��� �ſ� ���� sort�� �����ϵ��� �˰�����
	//  �����Ǿ���. �� �� �κ��� ������ ������ ���� �ʴ� data�� ������
	//  node�� ���� ���� ��� hit�Ǵ� Ȯ���� ���� sort�� ������ ����
	//  ������ �ش�.
	//-----------------------------------------------------------------

	// ChecK) ������������ Ȯ���Ѵ�.
	if(tempList._next->_data >= nowList._pre->_data)
	{
		// - Link~
		LINK_NODE(nowList._pre, tempList._next)

		// - Tail ����~
		tempList._next	 = nowList._next;

		// - Merge������ binlist�� Reset�Ѵ�.
		nowList._next	 = 0;

		// - binList Clear
		return;
	}

	// ChecK) 
	if(tempList._pre->_data <= nowList._next->_data)
	{
		// - Link~
		LINK_NODE(tempList._pre, nowList._next)

		// - Tail ����~
		tempList._pre	 = nowList._pre;

		// - Merge������ binlist�� Reset�Ѵ�.
		nowList._next	 = 0;

		// - binList Clear
		return;
	}

	// 3) ���ʷ� ���̱�...(tempList�� Main�̰� binList�� ���⿡ �ٴ� ����.)				
	_node*	nodeA		 = tempList._next;
	nodeA->_pre			 = &tempList;
	_node*	nodeB		 = nowList._next;
	for(;;)
	{
		// - B�� A���̿� �������� B�� Next��...
		if(nodeA->_data > nodeB->_data)
		{
			// Declare) 
			_node*	nodeBPre;

			// - nodeB�� NodeA�տ� ���δ�.
			LINK_NODE(nodeA->_pre, nodeB);

			// - ���� B��...
			nodeBPre = nodeB;
			nodeB	 = nodeB->_next;

			// - B�� Ŭ������... ������..
			HERE:

			if(nodeB==0)
			{
				// - Node�� �����Ѵ�.
				LINK_NODE(nodeBPre, nodeA);

				// - Merge������ binlist�� Reset�Ѵ�.
				nowList._next	 = 0;

				return;
			}

			if(nodeA->_data > nodeB->_data)
			{
				// ����~
				nodeBPre = nodeB;
				nodeB	 = nodeB->_next;

				goto HERE;
			}

			// - Node�� �����Ѵ�.
			LINK_NODE(nodeBPre, nodeA);
		}

		// - A�� ��������...
		_node*	tempANext	 = nodeA->_next;

		// nodeA�� ������ Ȯ���Ѵ�.
		if(tempANext==0)
		{
			// nodeA�ڿ� nodeB�� ���δ�.
			LINK_NODE(nodeA, nodeB);
			tempList._pre	 = nowList._pre;

			// - Merge������ binlist�� Reset�Ѵ�.
			nowList._next	 = 0;

			return;
		}

		nodeA		 = tempANext;
	}
}


template <class TDATA, class TALLOCATOR>
template <typename _Pr3>
void circular_list<TDATA, TALLOCATOR>::_merge_for_sort(_node& tempList, _node& nowList, _Pr3 _Pred)
{
	//-----------------------------------------------------------------
	// ����)
	//   merge sort�� ���� �ΰ��� �������� list�� �����ִ� �Լ��̴�.
	//  �ϳ��� list�� �������� �ٸ� �ϳ��� list������ ������ �Ǵ� list
	//  ���̿� �����ִ� ���·� code�� �����ȴ�.
	//   ������ lstd::list�� ���ؼ� 0�񱳸� �ϰ� �����ν� ���� �񱳿�
	//  �� ���� �ӵ� ����� ���Ͽ��� ���������� ���� list�� �ٸ� ��
	//  list�� ���� ������ ũ�ų� ���� node�ΰ��� �˻��ϴ� �κ��� �־�
	//  ���� ���� ���ĵ� ��� �ſ� ���� sort�� �����ϵ��� �˰�����
	//  �����Ǿ���. �� �� �κ��� ������ ������ ���� �ʴ� data�� ������
	//  node�� ���� ���� ��� hit�Ǵ� Ȯ���� ���� sort�� ������ ����
	//  ������ �ش�.
	//-----------------------------------------------------------------

	// ChecK) ������������ Ȯ���Ѵ�.
	if(!_Pred(tempList._next->_data, nowList._pre->_data))	// if(tempList._next->_data >= nowList._pre->_data)
	{
		// - Link~
		LINK_NODE(nowList._pre, tempList._next)

		// - Tail ����~
		tempList._next	 = nowList._next;

		// - Merge������ binlist�� Reset�Ѵ�.
		nowList._next	 = 0;

		// - binList Clear
		return;
	}

	// ChecK) 
	if(!_Pred(nowList._next->_data, tempList._pre->_data))	// if(tempList._pre->_data <= nowList._next->_data)
	{
		// - Link~
		LINK_NODE(tempList._pre, nowList._next)

		// - Tail ����~
		tempList._pre	 = nowList._pre;

		// - Merge������ binlist�� Reset�Ѵ�.
		nowList._next	 = 0;

		// - binList Clear
		return;
	}

	// 3) ���ʷ� ���̱�...(tempList�� Main�̰� binList�� ���⿡ �ٴ� ����.)				
	_node*	nodeA		 = tempList._next;
	nodeA->_pre			 = &tempList;
	_node*	nodeB		 = nowList._next;
	for(;;)
	{
		// - B�� A���̿� �������� B�� Next��...
		if(_Pred(nodeB->_data, nodeA->_data))	// if(nodeA->_data > nodeB->_data)
		{
			// Declare) 
			_node*	nodeBPre;

			// - nodeB�� NodeA�տ� ���δ�.
			LINK_NODE(nodeA->_pre, nodeB);

			// - ���� B��...
			nodeBPre = nodeB;
			nodeB	 = nodeB->_next;

			// - B�� Ŭ������... ������..
			HERE:

			if(nodeB==0)
			{
				// - Node�� �����Ѵ�.
				LINK_NODE(nodeBPre, nodeA);

				// - Merge������ binlist�� Reset�Ѵ�.
				nowList._next	 = 0;

				return;
			}

			if(_Pred(nodeB->_data, nodeA->_data))	// if(nodeA->_data > nodeB->_data)
			{
				// ����~
				nodeBPre = nodeB;
				nodeB	 = nodeB->_next;

				goto HERE;
			}

			// - Node�� �����Ѵ�.
			LINK_NODE(nodeBPre, nodeA);
		}

		// - A�� ��������...
		_node*	tempANext	 = nodeA->_next;

		// nodeA�� ������ Ȯ���Ѵ�.
		if(tempANext==0)
		{
			// nodeA�ڿ� nodeB�� ���δ�.
			LINK_NODE(nodeA, nodeB);
			tempList._pre	 = nowList._pre;

			// - Merge������ binlist�� Reset�Ѵ�.
			nowList._next	 = 0;

			return;
		}

		nodeA		 = tempANext;
	}
}

//-----------------------------------------------------------------
// CGD::circular_list)
//
//  sort: ������ �����Ѵ�.
//
// ����)
//  vector�� ���� ���������� ������ ��� standard algorithm�� ���
//  �Ͽ� sort�� ����ϸ� ȿ�������� ����ȴ�. �׷��� list�� ���
//  �ſ� ��ȿ�������� �����ϱ� ������ ���������� ��ü���� sort��
//  ������ �ִ�.
// 
//  * �˰��� ���� ����
//   - �⺻�� �˰����� Merge Sort�� ����ϸ�  std::list�� sort��
//     �����ϴ�. ������ �������� �˰����� �������� �����Ǿ���.
//   - �־��� ��� O(N) = NlogN�� �ؼ��Ѵ�.(std::list�� ����.)
//   - �ּ��� ��� �ð����⵵�� ȹ�������� �ٿ���.
//     (�ּ��� ��� N/2+logN�����̴�.)
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::sort()
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) ũ�Ⱑ 2������ ��� �׳� �ǵ�����.
	CGD_RETURN_IF(m_size < 2,);


	//-----------------------------------------------------------------
	// 1. Sort�� �����Ѵ�.
	//-----------------------------------------------------------------
	size_type		_Maxbin	 = 0;
	_node			binlist[32];

	// Declare) Sliced Node.
	_node			tempList;
	//size_type		bin;

	// 1) ���� Size
	size_type	nowSize		 = m_size;

	// 2) ���� ó��~
	_node*		nodeHeadPre	 = m_head->_pre;
	_node*		nodeNow		 = m_head;
	size_type	LastBin;

	if(nowSize>=4)
	{
		for(;;)	// 4���� merge�Ѵ�.
		{
			//-------------------------------------
			// Step1. 4���� �߶󳽴�.
			//-------------------------------------
			// 1) Now Node
			tempList._next	 = nodeNow;	nodeNow=nodeNow->_next;

			// 2) First�� Second�� ���Ѵ�.
			_node*	pSecond	 = nodeNow;	nodeNow=nodeNow->_next;
			if(tempList._next->_data>pSecond->_data)
			{
				LINK_NODE(pSecond, tempList._next);
				LINK_NODE(tempList._next, nodeNow);
				CGD_SWAP(tempList._next, pSecond);
			}

			// 3) Second�� Third�� ���Ѵ�.
			_node*	pThird	 = nodeNow;	nodeNow=nodeNow->_next;
			if(pSecond->_data>pThird->_data)
			{
				// - Third<First<Second
				if(tempList._next->_data>=pThird->_data)
				{
					LINK_NODE(pThird, tempList._next);

					_node*	temp	 = pSecond;
					pSecond			 = tempList._next;
					tempList._next	 = pThird;
					pThird			 = temp;
				}
				// - First<Third<Second
				else
				{
					LINK_NODE(tempList._next, pThird);
					LINK_NODE(pThird, pSecond);
					CGD_SWAP(pSecond, pThird);
				}

				LINK_NODE(pThird, nodeNow);
			}

			// 4) Third�� Forth�� ���Ѵ�.
			tempList._pre	 = nodeNow;	nodeNow=nodeNow->_next;
			if(pThird->_data>tempList._pre->_data)
			{
				// - First<Second<=Forth<Third
				if(pSecond->_data<=tempList._pre->_data)
				{
					LINK_NODE(pSecond, tempList._pre);
					LINK_NODE(tempList._pre, pThird);
				}
				// - First<Forth<Second<Third
				else if(tempList._next->_data<tempList._pre->_data)
				{
					LINK_NODE(tempList._next, tempList._pre);
					LINK_NODE(tempList._pre, pSecond);
				}
				// - Forth<=First<Second<Third
				else
				{
					LINK_NODE(tempList._pre, tempList._next);
					tempList._next	 = tempList._pre;
				}

				tempList._pre	 = pThird;
			}

			tempList._pre->_next = 0;


			//-------------------------------------
			// Step2. Merge�� �Ѵ�.
			//-------------------------------------
			size_type bin=0;
			for(; binlist[bin]._next!=0; ++bin)
			{
				// ChecK) MaxBin���� ������ Loop�� Ż���Ѵ�.(�̶� Max Bin���� ������Ų��.)
				if(bin==_Maxbin)
				{
					_Maxbin	 = bin+1;
					break;
				}

				// 1) tempList�� Merge~
				_merge_for_sort(tempList, binlist[bin]);
			}

			// 1) 
			binlist[bin]	 = tempList;

			//-------------------------------------
			// Step3. Merge����� binList�� �����Ѵ�.
			//-------------------------------------
			// 1) Size�� ���δ�.
			nowSize		-=4;

			// Check) ������ �ƴ��� Ȯ��
			if(nowSize<4)
			{
				LastBin	 = bin+1;
				break;
			}
		}
	}
	else
	{
	}

	// 3�� ���� Merge
	if(nowSize!=0)
	{
		//-------------------------------------
		// Step1. Node�� �����.
		//-------------------------------------
		for(;;)
		{
			// 1) 1�� ���� ���...
			tempList._next	 = nodeNow;

			if(nowSize==1)
			{
				tempList._pre	 = nodeNow;
				break;
			}

			// 2) 2���� ���...
			nodeNow	 = nodeNow->_next; tempList._pre = nodeNow->_next;
			if(tempList._next->_data>nodeNow->_data)
			{
				LINK_NODE(nodeNow, tempList._next);
				LINK_NODE(tempList._next, tempList._pre);
				CGD_SWAP(tempList._next, nodeNow);
			}

			if(nowSize==2)
			{
				tempList._pre	 = nodeNow;
				break;
			}

			// 3) 3���� ���...
			if(nodeNow->_data>tempList._pre->_data)
			{
				// third<first<second
				if(tempList._next->_data>tempList._pre->_data)
				{
					LINK_NODE(tempList._pre, tempList._next);
					tempList._next	 = tempList._pre;
				}
				// first<third<second
				else
				{
					LINK_NODE(tempList._next, tempList._pre);
					LINK_NODE(tempList._pre, nodeNow);
				}

				tempList._pre	 = nodeNow;
			}
			break;
		}
		tempList._pre->_next = 0;

		//-------------------------------------
		// Step2. Merge�� �Ѵ�.
		//-------------------------------------
		size_type bin=0;
		for(; binlist[bin]._next!=0; ++bin)
		{
			// ChecK) MaxBin���� ������ Loop�� Ż���Ѵ�.(�̶� Max Bin���� ������Ų��.)
			if(bin==_Maxbin)
			{
				_Maxbin	 = bin+1;
				break;
			}

			// 1) tempList�� Merge~
			_merge_for_sort(tempList, binlist[bin]);
		}

		LastBin	 = bin+1;
	}

	//-------------------------------------
	// Step4. ������ Merge�ؼ� ���Ѵ�.
	//-------------------------------------
	// 2) ��ġ��~
	for(; LastBin<_Maxbin; ++LastBin)
	{
		// 1) Check binlist�� ��� ������ ����~
		CGD_CONTINUE_IF(binlist[LastBin]._next==0);

		// 2) tempList�� Merge~
		_merge_for_sort(tempList, binlist[LastBin]);
	}

	//-------------------------------------
	// Step5. ���������� List�� �����ϱ�.
	//-------------------------------------
	// 1) Sort�Ϸ�� List Link�� �Ǵ�.
	LINK_NODE(nodeHeadPre, tempList._next);
	LINK_NODE(tempList._pre, m_tail);

	// 2) Head�� ���� �����Ѵ�.
	m_head	 = tempList._next;
}


template <class TDATA, class TALLOCATOR>
template<typename _Pr3>
void circular_list<TDATA, TALLOCATOR>::sort(_Pr3 _Pred)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) ũ�Ⱑ 2������ ��� �׳� �ǵ�����.
	CGD_RETURN_IF(m_size < 2,);


	//-----------------------------------------------------------------
	// 1. Sort�� �����Ѵ�.
	//-----------------------------------------------------------------
	size_type		_Maxbin	 = 0;
	_node			binlist[32];

	// Declare) Sliced Node.
	_node			tempList;
	//size_type		bin;

	// 1) ���� Size
	size_type	nowSize		 = m_size;

	// 2) ���� ó��~
	_node*		nodeHeadPre	 = m_head->_pre;
	_node*		nodeNow		 = m_head;
	size_type	LastBin;

	if(nowSize>=4)
	{
		for(;;)	// 4���� merge�Ѵ�.
		{
			//-------------------------------------
			// Step1. 4���� �߶󳽴�.
			//-------------------------------------
			// 1) Now Node
			tempList._next	 = nodeNow;	nodeNow=nodeNow->_next;

			// 2) First�� Second�� ���Ѵ�.
			_node*	pSecond	 = nodeNow;	nodeNow=nodeNow->_next;
			if(_Pred(pSecond->_data, tempList._next->_data)) //if(tempList._next->_data>pSecond->_data)
			{
				LINK_NODE(pSecond, tempList._next);
				LINK_NODE(tempList._next, nodeNow);
				CGD_SWAP(tempList._next, pSecond);
			}

			// 3) Second�� Third�� ���Ѵ�.
			_node*	pThird	 = nodeNow;	nodeNow=nodeNow->_next;
			if(_Pred(pThird->_data, pSecond->_data)) // if(pSecond->_data>pThird->_data)
			{
				// - Third<First<Second
				if(!_Pred(tempList._next->_data, pThird->_data))	// if(tempList._next->_data>=pThird->_data)
				{
					LINK_NODE(pThird, tempList._next);

					_node*	temp	 = pSecond;
					pSecond			 = tempList._next;
					tempList._next	 = pThird;
					pThird			 = temp;
				}
				// - First<Third<Second
				else
				{
					LINK_NODE(tempList._next, pThird);
					LINK_NODE(pThird, pSecond);
					CGD_SWAP(pSecond, pThird);
				}

				LINK_NODE(pThird, nodeNow);
			}

			// 4) Third�� Forth�� ���Ѵ�.
			tempList._pre	 = nodeNow;	nodeNow=nodeNow->_next;
			if(_Pred(tempList._pre->_data, pThird->_data))	// if(pThird->_data>tempList._pre->_data)
			{
				// - First<Second<=Forth<Third
				if(!_Pred(pSecond->_data, tempList._pre->_data))	// if(pSecond->_data<=tempList._pre->_data)
				{
					LINK_NODE(pSecond, tempList._pre);
					LINK_NODE(tempList._pre, pThird);
				}
				// - First<Forth<Second<Third
				else if(_Pred(tempList._next->_data, tempList._pre->_data))	// else if(tempList._next->_data<tempList._pre->_data)
				{
					LINK_NODE(tempList._next, tempList._pre);
					LINK_NODE(tempList._pre, pSecond);
				}
				// - Forth<=First<Second<Third
				else
				{
					LINK_NODE(tempList._pre, tempList._next);
					tempList._next	 = tempList._pre;
				}

				tempList._pre	 = pThird;
			}

			tempList._pre->_next = 0;


			//-------------------------------------
			// Step2. Merge�� �Ѵ�.
			//-------------------------------------
			size_type bin=0;
			for(; binlist[bin]._next!=0; ++bin)
			{
				// ChecK) MaxBin���� ������ Loop�� Ż���Ѵ�.(�̶� Max Bin���� ������Ų��.)
				if(bin==_Maxbin)
				{
					_Maxbin	 = bin+1;
					break;
				}

				// 1) tempList�� Merge~
				_merge_for_sort(tempList, binlist[bin], _Pred);
			}

			// 1) 
			binlist[bin]	 = tempList;

			//-------------------------------------
			// Step3. Merge����� binList�� �����Ѵ�.
			//-------------------------------------
			// 1) Size�� ���δ�.
			nowSize		-=4;

			// Check) ������ �ƴ��� Ȯ��
			if(nowSize<4)
			{
				LastBin	 = bin+1;
				break;
			}
		}
	}
	else
	{
	}

	// 3�� ���� Merge
	if(nowSize!=0)
	{
		//-------------------------------------
		// Step1. Node�� �����.
		//-------------------------------------
		for(;;)
		{
			// 1) 1�� ���� ���...
			tempList._next	 = nodeNow;

			if(nowSize==1)
			{
				tempList._pre	 = nodeNow;
				break;
			}

			// 2) 2���� ���...
			nodeNow	 = nodeNow->_next; tempList._pre = nodeNow->_next;
			if(_Pred(nodeNow->_data, tempList._next->_data))	// if(tempList._next->_data>nodeNow->_data)
			{
				LINK_NODE(nodeNow, tempList._next);
				LINK_NODE(tempList._next, tempList._pre);
				CGD_SWAP(tempList._next, nodeNow);
			}

			if(nowSize==2)
			{
				tempList._pre	 = nodeNow;
				break;
			}

			// 3) 3���� ���...
			if(_Pred(tempList._pre->_data, nodeNow->_data))	// if(nodeNow->_data>tempList._pre->_data)
			{
				// third<first<second
				if(_Pred(tempList._pre->_data, tempList._next->_data))	// if(tempList._next->_data>tempList._pre->_data)
				{
					LINK_NODE(tempList._pre, tempList._next);
					tempList._next	 = tempList._pre;
				}
				// first<third<second
				else
				{
					LINK_NODE(tempList._next, tempList._pre);
					LINK_NODE(tempList._pre, nodeNow);
				}

				tempList._pre	 = nodeNow;
			}
			break;
		}
		tempList._pre->_next = 0;


		//-------------------------------------
		// Step2. Merge�� �Ѵ�.
		//-------------------------------------
		size_type bin=0;
		for(; binlist[bin]._next!=0; ++bin)
		{
			// ChecK) MaxBin���� ������ Loop�� Ż���Ѵ�.(�̶� Max Bin���� ������Ų��.)
			if(bin==_Maxbin)
			{
				_Maxbin	 = bin+1;
				break;
			}

			// 1) tempList�� Merge~
			_merge_for_sort(tempList, binlist[bin], _Pred);
		}

		LastBin	 = bin+1;
	}

	//-------------------------------------
	// Step4. ������ Merge�ؼ� ���Ѵ�.
	//-------------------------------------
	for(; LastBin<_Maxbin; ++LastBin)
	{
		// 1) Check binlist�� ��� ������ ����~
		CGD_CONTINUE_IF(binlist[LastBin]._next==0);

		// 2) tempList�� Merge~
		_merge_for_sort(tempList, binlist[LastBin], _Pred);
	}

	//-------------------------------------
	// Step5. ���������� List�� �����ϱ�.
	//-------------------------------------
	// 1) Sort�Ϸ�� List Link�� �Ǵ�.
	LINK_NODE(nodeHeadPre, tempList._next);
	LINK_NODE(tempList._pre, m_tail);

	// 2) Head�� ���� �����Ѵ�.
	m_head	 = tempList._next;
}




//-----------------------------------------------------------------
// CGD::circular_list)
//
//  shrink: ������ node�� �����Ѵ�.
//
// ����)
//  CGD::circular_list�� ��� pop�̳� clear, erase Ȥ�� remove�� ������ ��  
//  ���� node�� �������� �ʰ� �ű�⸸ �Ѵ�. ���� �ѹ� ������ node�� 
//  container�� �ı��ϱ� ������ �������� �ʴ´�.
//   shrink�� ������ node�� �����ϴ� �Լ��̴�. ������ node�� ������
//  �ʿ䰡 ������ �� �Լ��� ����ϸ� size��ŭ�� node�� �����ϰ��
//  ��� �����Ѵ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::shrink()
{
	//-----------------------------------------------------------------
	// 1. ���鼭 ���� node���� ��� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) ����... �پ��� ���ڸ� Ȯ���ϱ� ���� ������.
	size_type	count	 = 0;

	// 2) ���� head�� tail�� ����.
	_node*	tempFirst	 = m_tail->_next;
	_node*	tempLast	 = m_head;
	while(tempFirst != tempLast)
	{
		// - Destruct�� ȣ���Ѵ�.
		m_allocVal.destroy(&tempFirst->_data);

		// - Destruct�� ȣ���ϰ� tempNode�� �����.
		//   (Destroy�� ȣ������ �ʴ´�.)
		m_allocNode.deallocate(tempFirst, 1);

		// - ���ڸ� ���Ѵ�.
		++count;

		// - ����...
		tempFirst	= tempFirst->_next;
	}


	//-----------------------------------------------------------------
	// 2. Node�� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) m_head�� m_tail�� �ڷ� ���̱�.
	LINK_NODE(m_tail, m_head);

	// 2) �Ҵ���� ���� ũ�⸦ 1 ���δ�.
	m_size		-= count;
}


}
