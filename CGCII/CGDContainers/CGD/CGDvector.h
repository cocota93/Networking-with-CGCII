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

namespace CGD
{

template <typename TDATA, typename TALLOCATOR=std::allocator<TDATA> >
class vector
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type		Contain�� ��� ������ ��.
//     2) X:reference		X:value_type&.
//     3) X:const_reference	const X:value_type&.
//     4) X:iterator		��ȸ�� �� ���Ǵ� �ݺ���.
//     5) X:const_iterator	��ȸ�� �� ���Ǵ� �ݺ���(const��)
//     6) X:difference_type	�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     7) X:size_type		X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
//
//  * Reversible Requirement
//     1) X::reverse_iterator ����ȯ �� ���Ǵ� �ݺ���.
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

	// Standard 5) Iterators
	class iterator;
	class const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// Allocator)
	typedef TALLOCATOR		allocator_type;

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
	typedef	vector<TDATA, TALLOCATOR>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA, typename TOTHER_ALLOCATOR=TALLOCATOR>
	struct rebind
	{
		typedef vector<TOTHER_DATA, TOTHER_ALLOCATOR> other;
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
//     1) a.rbegin(); 		�ݴ���� ��ȸ�� ���� ���۰� �� iterator
//		  a.rend();
//
// ----------------------------------------------------------------------------
public:
	vector();
	vector(const _mytype& _Right);
	~vector();

public:
	// Common Standard 1) Status Function
	size_type				size() const						{	return (m_ptrLast-m_ptrFirst);}
	size_type				max_size() const					{	return 0x7fffffff;}
	bool					empty() const						{	return (m_ptrLast==m_ptrFirst);}

	// Common Standard 2) 
	iterator				begin()								{	return iterator(m_ptrFirst);}
	const_iterator			begin() const						{	return const_iterator(m_ptrFirst);}
	const_iterator			cbegin() const						{	return const_iterator(m_ptrFirst);}
	iterator				end()								{	return iterator(m_ptrLast);}
	const_iterator			end() const							{	return const_iterator(m_ptrLast);}
	const_iterator			cend() const						{	return const_iterator(m_ptrLast);}
	reverse_iterator		rbegin()							{	return reverse_iterator(iterator(m_ptrLast-1));}
	const_reverse_iterator	rbegin() const						{	return const_iterator(m_ptrLast-1);}
	const_reverse_iterator	crbegin() const						{	return const_iterator(m_ptrLast-1);}
	reverse_iterator		rend()								{	return reverse_iterator(iterator(m_ptrFirst-1));}
	const_reverse_iterator	rend() const						{	return const_iterator(m_ptrFirst-1);}
	const_reverse_iterator	crend() const						{	return const_iterator(m_ptrFirst-1);}

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
//    1) X(n, t);			t�� ���纻 n���� ������ Sequence�� �����Ѵ�.
//		 X a(n, t);	
//    2) X(i, j); 			����[i,j]�� ����� ������ Sequence�� �����Ѵ�.
//		 X a(i, j);
//    3) a.insert(p,t);		p�տ� t�� ���纻�� �����Ѵ�. ���ϰ��� ���Ե�
//							���Ҹ� ����Ű�� �ݺ����̴�.
//    4) a.insert(p,n,t);	p�տ� t�� ���纻 n���� �����Ѵ�.
//    5) a.insert(p,i,j);	p�տ� [i,j]�� ��� ���ҵ��� ���纻�� �����Ѵ�.
//							i,j�� �ݺ���
//    6) a.erase(q);		q�� ����Ű�� ���Ҹ� �����Ѵ�. ���ϰ��� �����Ǳ�
//							���� q������ ��ġ�ߴ� ���Ҹ� ����Ű�� �ݺ���
//    7) a.erase(q1,q2);	����[q1,q2]�� ���Ե� ���ҵ��� �����Ѵ�. ���ϰ���
//							�����Ǳ� ���� q2������ ��ġ�ߴ� ���Ҹ� ����Ű��
//							�ݺ���.
//    8) a.clear();			�����̳ʿ� ��� ���� ���Ҹ� �����Ѵ�. 
//							a.erase(a.begin(), a.end())�� �����ϴ�.
//
// ----------------------------------------------------------------------------
public:
	vector(size_type _Count);
	vector(size_type _Count, const TDATA& _Val);
	vector(size_type _Count, const TDATA& _Val, const TALLOCATOR& _Al);
	template<typename TITERATOR>
	vector(TITERATOR _First, TITERATOR _Last);
	template<typename TITERATOR>
	vector(TITERATOR _First, TITERATOR _Last, const TALLOCATOR& _Al);

public:
	// Sequence Standard 1) insert member function
	template<typename TITERATOR>
	void					insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last);
	iterator				insert(const_iterator _Where, const TDATA& _Val);
	void					insert(const_iterator _Where, int _Count, const_reference _Val);

	// Sequence Standard 2) erase member function
	iterator				erase(const_iterator _Where);
	iterator				erase(const_iterator _First, const_iterator _Last);

	// Sequence Standard 3) clear
	void					clear();

	// Added) Find (No Stantard)
	iterator				find(const_reference _Val);



// ****************************************************************************
// Vector Member)
// 
// 
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const						{	return (m_ptrEnd-m_ptrFirst);}
	size_type				remained() const						{	return (m_ptrEnd-m_ptrLast);}

	// 2) Data
	reference				front()		 							{	return *m_ptrFirst;}
	const_reference			front() const 							{	return *m_ptrFirst;}

	reference				back()									{	return *(m_ptrLast-1);}
	const_reference			back() const							{	return *(m_ptrLast-1);}

	reference				at(size_type _Pos);
	const_reference			at(size_type _Pos) const;

	reference				operator [] (size_type _Pos);
	const_reference			operator [] (size_type _Pos) const;

	// 3) push/pop back
	void					push_back(const TDATA& _Val);
	void					push_back();
	void					pop_back();

	// 4) Assign
	template <typename ITERATOR>
	void					assign(ITERATOR _First, ITERATOR _Last);
	void					assign(size_type p_Count, const TDATA& _Val);

	// 5) Reserve
	void					reserve(size_type _Count);

	// 6) Resize
	void					resize(size_type _Newsize);
	void					resize(size_type _Newsize, TDATA _Val);

	// 7) Shrink
	void					shrink_to_fit();

	// 8) Allocation
	allocator_type			get_allocator() const					{	return m_allocVal;}


// ****************************************************************************
// Member Variable) 
// ----------------------------------------------------------------------------
private:
	// 1) Array
	TDATA*					m_ptrFirst;		// Array�� ó�� ��ġ...
	TDATA*					m_ptrLast;		// Array���� ���ǰ� �ִ� ���� ��~()
	TDATA*					m_ptrEnd;		// Array�Ҵ���� ���� ��~(reserved)

	// 2) Allocator
	allocator_type			m_allocVal;

private:
	void					_Expand(size_type _Count, const_iterator _Where, size_type _Room);


// ****************************************************************************
// Iterator) 
// ----------------------------------------------------------------------------
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	vector<TDATA, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef	typename _mytype::pointer			data_pointer;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;

		friend			iterator;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		const_iterator()												{}
		explicit const_iterator(data_pointer p_pNow) : m_ptrLast(p_pNow) {}

		// 2) ����
		const_iterator&	operator=(const const_iterator& _Right)			{	m_ptrLast=_Right.m_ptrLast; return *this;}
		pointer			operator->()										{	return &**this;}

		// 3) �ݺ�
		reference		operator*() const								{	return *this->m_ptrLast;}
		const_iterator&	operator++()									{	++m_ptrLast; return *this;}
		const_iterator	operator++(int)									{	return const_iterator(m_ptrLast++);}
		const_iterator&	operator--()										{	--m_ptrLast; return *this;}
		const_iterator	operator--(int)									{	return const_iterator(m_ptrLast--);}
		const_iterator	operator+(difference_type _Right) const			{	return const_iterator(m_ptrLast+_Right);}
		void			operator+=(difference_type _Right)				{	m_ptrLast+=_Right;}
		const_iterator	operator-(difference_type _Right) const			{	return const_iterator(m_ptrLast-_Right);}
		void			operator-=(difference_type _Right)				{	m_ptrLast-=_Right;}
		size_type		operator-(const const_iterator& _Right) const	{	return m_ptrLast-_Right.m_ptrLast;}
		size_type		operator-(const iterator& _Right) const			{	return m_ptrLast-_Right.m_ptrLast;}

		// 4) ��
		bool			operator==(const const_iterator& _Right) const	{	return m_ptrLast==_Right.m_ptrLast;}
		bool			operator!=(const const_iterator& _Right) const	{	return m_ptrLast!=_Right.m_ptrLast;}

		bool			operator>(const const_iterator&  _Right) const	{	return m_ptrLast>_Right.m_ptrLast;}
		bool			operator>=(const const_iterator&  _Right)		{	return m_ptrLast>=_Right.m_ptrLast;}
		bool			operator<(const const_iterator&  _Right) const	{	return m_ptrLast<_Right.m_ptrLast;}
		bool			operator<=(const const_iterator&  _Right)		{	return m_ptrLast<=_Right.m_ptrLast;}

		bool			operator>(const iterator&  _Right) const		{	return m_ptrLast>_Right.m_ptrLast;}
		bool			operator>=(const iterator&  _Right)				{	return m_ptrLast>=_Right.m_ptrLast;}
		bool			operator<(const iterator&  _Right) const		{	return m_ptrLast<_Right.m_ptrLast;}
		bool			operator<=(const iterator&  _Right)				{	return m_ptrLast<=_Right.m_ptrLast;}

	private:
		data_pointer	m_ptrLast;
	};

	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	vector<TDATA, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef	typename _mytype::pointer			data_pointer;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;

		friend			const_iterator;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		iterator()														{}
		iterator(const const_iterator& _Copy) : m_ptrLast(_Copy.m_ptrLast){}
		explicit iterator(pointer _now) : m_ptrLast(_now)				{}

		// 2) ����
		iterator&		operator=(const iterator& _Right)				{	m_ptrLast=_Right.m_ptrLast; return *this;}
		iterator&		operator=(const const_iterator& _Right)			{	m_ptrLast=_Right.m_ptrLast; return *this;}
		pointer			operator->()										{	return &**this;}
						operator const_iterator()						{	return const_iterator(m_ptrLast);}

		// 3) �ݺ�
		reference		operator*() const								{	return *m_ptrLast;}
		iterator&		operator++()									{	++m_ptrLast; return *this;}
		iterator		operator++(int)									{	return iterator(m_ptrLast++);}
		iterator&		operator--()										{	--m_ptrLast; return *this;}
		iterator		operator--(int)									{	return iterator(m_ptrLast--);}
		iterator		operator+(difference_type _Right) const			{	return iterator(m_ptrLast+_Right);}
		void			operator+=(difference_type _Right)				{	m_ptrLast+=_Right;}
		iterator		operator-(difference_type _Right) const			{	return iterator(m_ptrLast-_Right);}
		void			operator-=(difference_type _Right)				{	m_ptrLast-=_Right;}
		size_type		operator-(const const_iterator& _Right) const	{	return m_ptrLast-_Right.m_ptrLast;}
		size_type		operator-(const iterator& _Right) const			{	return m_ptrLast-_Right.m_ptrLast;}

		// 4) ��
		bool			operator==(const iterator& _Right) const		{	return m_ptrLast==_Right.m_ptrLast;}
		bool			operator!=(const iterator& _Right) const		{	return m_ptrLast!=_Right.m_ptrLast;}

		bool			operator==(const const_iterator& _Right) const	{	return m_ptrLast==_Right.m_ptrLast;}
		bool			operator!=(const const_iterator& _Right) const	{	return m_ptrLast!=_Right.m_ptrLast;}
		
		bool			operator>(const const_iterator& _Right) const	{	return m_ptrLast>_Right.m_ptrLast;}
		bool			operator>=(const const_iterator& _Right) const	{	return m_ptrLast>=_Right.m_ptrLast;}
		bool			operator<(const const_iterator& _Right) const	{	return m_ptrLast<_Right.m_ptrLast;}
		bool			operator<=(const const_iterator& _Right) const	{	return m_ptrLast<=_Right.m_ptrLast;}

		bool			operator>(const iterator& _Right) const			{	return m_ptrLast>_Right.m_ptrLast;}
		bool			operator>=(const iterator& _Right) const		{	return m_ptrLast>=_Right.m_ptrLast;}
		bool			operator<(const iterator& _Right) const			{	return m_ptrLast<_Right.m_ptrLast;}
		bool			operator<=(const iterator& _Right) const		{	return m_ptrLast<=_Right.m_ptrLast;}

	private:
		data_pointer	m_ptrLast;
	};
};





//-----------------------------------------------------------------
// Constructor/Destructor �Լ���.
//
// - �پ��� ������ constructor�� destructor�Լ����̴�.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::vector() : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::vector(const _mytype& _Right) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		insert(begin(), _Right.begin(), _Right.end());
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::vector(size_type _Count) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) ũ�⸦ �����Ѵ�.
		resize(_Count);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::vector(size_type _Count, const TDATA& _Val) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::vector(size_type _Count, const TDATA& _Val, const TALLOCATOR& _Al) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
template<typename TITERATOR>
vector<TDATA, TALLOCATOR>::vector(TITERATOR _First, TITERATOR _Last) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
template<typename TITERATOR>
vector<TDATA, TALLOCATOR>::vector(TITERATOR _First, TITERATOR _Last, const TALLOCATOR& _Al) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::~vector()
{
	// 1) ��� �����.
	clear();

	// 2) Deallocate�Ѵ�.
	m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);
}

template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::_mytype& vector<TDATA, TALLOCATOR>::operator=(const _mytype& _Right)
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


// ���Լ���
template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator==(const _mytype& _Right) const
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

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator!=(const _mytype& _Right) const	
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

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator<(const _mytype& _Right) const	
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

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator>(const _mytype& _Right) const	
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

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator<=(const _mytype& _Right) const	
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

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator>=(const _mytype& _Right) const	
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



//-----------------------------------------------------------------
// Random access �Լ���.
//
// - random access�� �����ϴ� �Լ��� operator��...
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::reference vector<TDATA, TALLOCATOR>::at(size_type _Pos)
{
	// Check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: ������ �Ѿ �����Դϴ�.(" __FUNCTION__ ")\n"))

	// 1) ���� �о �ǵ�����.
	return m_ptrFirst[_Pos];
}

template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::const_reference vector<TDATA, TALLOCATOR>::at(size_type _Pos) const
{
	// Check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: ������ �Ѿ �����Դϴ�.(" __FUNCTION__ ")\n"))

	// 1) ���� �о �ǵ�����.
	return m_ptrFirst[_Pos];
}


template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::reference vector<TDATA, TALLOCATOR>::operator [] (size_type _Pos)
{
	return	at(_Pos);
}

template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::const_reference vector<TDATA, TALLOCATOR>::operator [] (size_type _Pos) const
{
	return	at(_Pos);
}




//-----------------------------------------------------------------
// reserve() �Լ�.
//
// _Count��ŭ buffer�� �̸� Ȯ���ϴ� �Լ��̴�.
//  ����, _Count�� ���� reserve�� ũ�⺸�� ���� ��� �ƹ��� ������
// �������� ���� ���̴�.
//  _Count�� ���� Reserve�� �������� Ŭ ��� _Count��ŭ���� Ȯ��
// �Ѵ�.
// �� �Լ� ������ size()�� ��ȭ��  ������ max_size()�� ���Ҽ� �ִ�.
//
//  �̶�, ���ο� ũ���� ���ο� buffer�� allocator�κ��� �Ҵ���
// ������ ������ buffer�� deallocate�Ѵ�. 
// ������ ����Ǿ� �ִ� data���� ���� �Ҵ���� buffer�� ���� ��ġ�� 
// ���簡 ��������.(�� constructor�� ȣ����� �ʴ´�.)
//
//  ���� �ִ� ������ �˰� �� ��� �̸� reserve�� ������ �ٽ� �Ҵ� 
// ������ ���� �߰������� ���� ���ϸ� ���� �� �ִ�.
//  std::vector�� ��� �� ���� for_loop���� ���� �����Ͽ����� ���⼭
// �� memcpy�� ���� ����ȴ�.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::reserve(size_type _Count)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) capacity�� �̹� _Count���� ũ�� �׳� �ǵ�����.
	if(_Count<=capacity())
	{
		return;
	}

	//-----------------------------------------------------------------
	// 1. ���ο� array�� �Ҵ�޴´�.
	//-----------------------------------------------------------------
	// 1) Array�� �����Ѵ�.
	TDATA*	tempArray	 = m_allocVal.allocate(_Count); 


	//-----------------------------------------------------------------
	// 2. ���� array�� �Ҵ������Ѵ�.
	//-----------------------------------------------------------------
	// 1) ���ο� ũ�⸦ ��´�.
	size_type	nowSize	 = size();

	// 2) size�� 0�̸� ���� ���� ������ �ʿ�� ����.
	if(nowSize != 0 && tempArray !=m_ptrFirst)
	{
		// - �޸𸮸� �����Ѵ�.
		memcpy(tempArray, m_ptrFirst, (unsigned long)sizeof(TDATA)*nowSize);

		// - ������ data�� �����.(Destroy�� ȣ������ �ʴ´�.)
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);
	}


	//-----------------------------------------------------------------
	// 3. ���� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) �����Ѵ�.
	m_ptrFirst	 = tempArray;
	m_ptrLast	 = tempArray+nowSize;
	m_ptrEnd	 = tempArray+_Count;
}

//-----------------------------------------------------------------
// _Expand �Լ�.
//
// �� �Լ��� ���ο����� ���Ǵ� �Լ��̴�.
// reserve�� ���������� �Ȱ��� ũ�⸦ Ȯ���ϴ� �Լ����� �ٸ� ����  
// Ȯ���ϴ� �������� ������ data�� ������ ���� �� _Where�κ���
// _Room��ŭ�� ���ڸ��� ����ٴ� ���̴�. 
// �ַ� Insert�� �����ϴ� �� Expand�� �Ͼ ��� ���ȴ�.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::_Expand(size_type _Count, const_iterator _Where, size_type _Room)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) capacity�� �̹� _Count���� ũ�� �׳� �ǵ�����.
	CGD_RETURN_IF(_Count<=capacity(),);


	//-----------------------------------------------------------------
	// 1. ���ο� array�� �Ҵ�޴´�.
	//-----------------------------------------------------------------
	// 1) Array�� �����Ѵ�.
	TDATA*	tempArray	 = m_allocVal.allocate(_Count); 

	// Check) Succeded in allocation?
	CGDASSERT_ERROR(tempArray!=nullptr);

	// Check) if fail to allocation, throw exception 
	CGD_THROW_IF(tempArray==nullptr, std::bad_alloc());


	//-----------------------------------------------------------------
	// 2. ���� array�� �Ҵ������Ѵ�.
	//-----------------------------------------------------------------
	size_type	nowSize	 = size();

	// 1) size�� 0�̸� ���� ���� ������ �ʿ�� ����.
	if(nowSize != 0)
	{
		// Check) m_ptrFirst�� 0�̾�� �ȵȴ�.
		CGDASSERT_ERROR(m_ptrFirst!=0);

		// Check) m_ptrFirst�� 0�̾�� �ȵȴ�.
		CGDASSERT_ERROR(_Where.m_ptrLast >= m_ptrFirst && _Where.m_ptrLast <= m_ptrLast);

		// - ������ ũ�⸦ ���Ѵ�.
		size_type	sizeFront	 = _Where.m_ptrLast-m_ptrFirst;
		size_type	sizeRear	 = m_ptrLast-_Where.m_ptrLast;

		// - �պκ��� ������ �ű��.
		if(tempArray !=m_ptrFirst)
		{
			memcpy(tempArray, m_ptrFirst, (unsigned long)sizeof(TDATA)*sizeFront);
		}

		// - �޺κ��� ������ �ű��.
		memcpy(tempArray+sizeFront+_Room, _Where.m_ptrLast, (unsigned long)sizeof(TDATA)*sizeRear);

		// - ������ �Ҵ���� Memory Chunk�� deallocate�Ѵ�.(Destroy�� ȣ������ �ʴ´�.)
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);
	}


	//-----------------------------------------------------------------
	// 3. ���� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) �����Ѵ�.
	m_ptrFirst	 = tempArray;
	m_ptrLast	 = tempArray+nowSize+_Room;
	m_ptrEnd	 = tempArray+_Count;
}



template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::resize(size_type _Newsize)
{
	resize(_Newsize, TDATA());
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::resize(size_type _Newsize, TDATA _Val)
{
	//-----------------------------------------------------------------
	// 1. Reserve�� ũ�� Ȯ��.
	//-----------------------------------------------------------------
	// 1) �ִ�ũ�⺸�� ũ�� ũ�⸦ �ø���.
	if(_Newsize > capacity())
	{
		reserve(_Newsize);
	}


	//-----------------------------------------------------------------
	// 2. ũ�� �����ϱ�.
	//-----------------------------------------------------------------
	// 1) 
	iterator	iter=end();
	iterator	newEnd(begin()+_Newsize);

	if(newEnd>iter)
	{
		CGD_TRY
		{
			// 2) �þ �κб��� Reset�� �Ѵ�.
			for(; iter < newEnd; ++iter)
			{
				m_allocVal.construct(&(*iter), _Val);
			}
		}
		CGD_CATCH_ALL
		{
			// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
			for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
			{
				// - Destroy�� ȣ���Ѵ�.
				m_allocVal.destroy(&(*iterRoll));
			}

			// Throw) �ٽ� Thread!!!
			CGD_RETHROW;
		}
	}
	else
	{
		for(; newEnd < iter ; ++newEnd)
		{
			m_allocVal.destroy(&(*newEnd));
		}
	}

	// 2) Size�� ���� �����Ѵ�.
	m_ptrLast	 = m_ptrFirst+_Newsize;
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::clear()
{
	//-----------------------------------------------------------------
	// 1. Destruct�� �Ѵ�.
	//-----------------------------------------------------------------
	for(iterator iter=begin(); iter!=end(); ++iter)
	{
		m_allocVal.destroy(&(*iter));
	}


	//-----------------------------------------------------------------
	// 2. Size�� 0���� �Ѵ�.
	//-----------------------------------------------------------------
	// 1) Last�� First�� ����� �װ� 0���� ����� ���̴�.
	m_ptrLast	 = m_ptrFirst;
}

template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::iterator vector<TDATA, TALLOCATOR>::find(const_reference _Val)
{
	// 1) ó������ �������� ����Ÿ�� ã�´�.
	iterator iter=begin();
	for(; iter!=end(); ++iter)
	{
		CGD_BREAK_IF(*iter==_Val);
	}

	// Return) ����� return�Ѵ�.
	return	iter;
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::push_back(const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check) Buffer�˻�.
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) ��á���� �ø���.
	if(m_ptrLast==m_ptrEnd)
	{
		// - ���� ũ�⸦ ���Ѵ�.
		size_type	newCapacity	 = capacity();

		// - ũ�⸦ 2��� �ø���.
		newCapacity	 = newCapacity*2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		newCapacity	 = (newCapacity>CONTAINER_MIN) ? newCapacity : CONTAINER_MIN;

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		reserve(newCapacity);
	}
	#else
	// Error) NO_AUTOEXPAND�� �س��� �ʿ��� ������ŭ reserve�� ���� �ʾҳ�?
	//  (���⼭ Assert�� �ɸ��� NO_AUTOEXPAND �ɼ��� �����ϰų� reserve()
	//  �Լ��� ����� max_size()�� Ȯ���ϸ� �ȴ�.)
	CGD_THROW_IF(m_ptrLast==m_ptrEnd, std::length_error("CGD Exception: ���̻� ������ �����ϴ�.("__FUNCTION__")\n"));
	#endif


	//-----------------------------------------------------------------
	// 1. Push�ϱ�.
	//-----------------------------------------------------------------
	// 1) Construct�� ȣ���Ѵ�.
	m_allocVal.construct(m_ptrLast, _Val);

	// 2) Last ������ ������Ŵ.
	++m_ptrLast;
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::push_back()
{
	//-----------------------------------------------------------------
	// Check) Buffer�˻�.
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) ��á���� �ø���.
	if(m_ptrLast==m_ptrEnd)
	{
		// - ���� ũ�⸦ ���Ѵ�.
		size_type	newCapacity	 = capacity();

		// - ũ�⸦ 2��� �ø���.
		newCapacity	 = newCapacity*2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		newCapacity	 = CGD_MAX(newCapacity, CONTAINER_MIN);

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		reserve(newCapacity);
	}
	#else
	// Error) NO_AUTOEXPAND�� �س��� �ʿ��� ������ŭ reserve�� ���� �ʾҳ�?
	//  (���⼭ Assert�� �ɸ��� NO_AUTOEXPAND �ɼ��� �����ϰų� reserve()
	//  �Լ��� ����� max_size()�� Ȯ���ϸ� �ȴ�.)
	CGD_THROW_IF(m_ptrLast==m_ptrEnd, std::length_error("CGD Exception: ���̻� ������ �����ϴ�.("__FUNCTION__")\n"));
	#endif


	//-----------------------------------------------------------------
	// 1. Push�ϱ�.
	//-----------------------------------------------------------------
	// 1) Construct�� ȣ���Ѵ�.
	m_allocVal.construct(m_ptrLast, TDATA());

	// 2) Last ������ ������Ŵ.
	++m_ptrLast;
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::pop_back()
{
	//-----------------------------------------------------------------
	// Check) Empty�˻�.
	//-----------------------------------------------------------------
	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ� �������� �ʰ� �׳� ������.
	if(empty())
	{
		return;
	}
	#endif


	//-----------------------------------------------------------------
	// 1. Pop�ϱ�.
	//-----------------------------------------------------------------
	// 1) ũ�⸦ ���δ�.
	--m_ptrLast;

	// 2) Destroy�� ȣ���Ѵ�.
	m_allocVal.destroy(m_ptrLast);
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::assign(size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// ����) CGD::Vector���� max_size()�˻�� �������� �ʽ��ϴ�.
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	// 1. ���� ���� �˻�.(���԰����� ������ ������ ���� �ֳ�?)
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) _size�� _capacity���� ũ�ų� ������ vector�� ũ�⸦ ���δ�.
	if(remained()<_Count)
	{
		// - ���� ũ�⸦ ���Ѵ�.
		size_type	newcapacity	 = capacity()+_Count;

		// - ũ�⸦ 2��� �ø���.
		newcapacity	 = newcapacity*2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		newcapacity	 = CGD_MAX(newcapacity, CONTAINER_MIN);

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		reserve(newcapacity);
	}
	#else
	// Error) NO_AUTOEXPAND�� �س��� �ʿ��� ������ŭ reserve�� ���� �ʾҳ�?
	//  (���⼭ Assert�� �ɸ��� NO_AUTOEXPAND �ɼ��� �����ϰų� reserve()
	//  �Լ��� ����� max_size()�� Ȯ���ϸ� �ȴ�.)
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: �߰��� ������ �����մϴ�.("__FUNCTION__")\n"));
	#endif


	//-----------------------------------------------------------------
	// 2. ���� �ִ´�.
	//-----------------------------------------------------------------
	// 1) ������� First�� Last�� ����Ű�� Iterator
	iterator	iter=end();
	iterator	newEnd(end()+_Count);

	CGD_TRY
	{
		// 2) ���� ������ Construct�Լ��� �����Ѵ�.
		for(; iter != newEnd; ++iter)
		{
			m_allocVal.construct(&(*iter), _Val);
		}
	}
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&(*iterRoll));
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 3) Last���� �ٲ۴�.
	m_ptrLast	+= _Count;
}

template <typename TDATA, typename TALLOCATOR>
template <typename ITERATOR>
void vector<TDATA, TALLOCATOR>::assign(ITERATOR _First, ITERATOR _Last)
{
	//-----------------------------------------------------------------
	// ����) CGD::Vector���� max_size()�˻�� �������� �ʽ��ϴ�.
	//-----------------------------------------------------------------
	// Check) 
	__if_exists(ITERATOR::m_ptrLast)
	{
		CGDASSERT_ERROR(_Last.m_ptrLast > _First.m_ptrLast);
	}

	// 1) Size�� ���Ѵ�.
	size_type	count	 = _Last-_First;

	// Check) count�� 0���̸� �׳� ������.
	CGD_RETURN_IF(count == 0,);


	//-----------------------------------------------------------------
	// 1. ���� ���� �˻�.(���԰����� ������ ������ ���� �ֳ�?)
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) _size�� _capacity���� ũ�ų� ������ vector�� ũ�⸦ ���δ�.
	if(remained()<count)
	{
		// - ���� ũ�⸦ ���Ѵ�.
		size_type	newcapacity	 = capacity()+count;

		// - ũ�⸦ 2��� �ø���.
		newcapacity	 = newcapacity*2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		newcapacity	 = CGD_MAX(newcapacity, CONTAINER_MIN);

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		reserve(newcapacity);
	}
	#else
	// Error) NO_AUTOEXPAND�� �س��� �ʿ��� ������ŭ reserve�� ���� �ʾҳ�?
	//  (���⼭ Assert�� �ɸ��� NO_AUTOEXPAND �ɼ��� �����ϰų� reserve()
	//  �Լ��� ����� max_size()�� Ȯ���ϸ� �ȴ�.)
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: �߰��� ������ �����մϴ�.("__FUNCTION__")\n"));
	#endif


	//-----------------------------------------------------------------
	// 2. ���� �ִ´�.
	//-----------------------------------------------------------------
	// 1) ������� First�� Last�� ����Ű�� Iterator
	iterator	iter	 = end();

	CGD_TRY
	{
		// 2) ���� ������ Construct�Լ��� �����Ѵ�.
		for(; _First != _Last; ++_First,++iter)
		{
			m_allocVal.construct(&(*iter), *_First);
		}
	}
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&(*iterRoll));
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 3) Last���� �ٲ۴�.
	m_ptrLast	+= count;
}


//-----------------------------------------------------------------
// ����) CGD::vector::Insert
//
//  _Where�� ���ʿ� _Val �ϳ��� �����ϴ� �Լ��̴�.
// 
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
template<typename TITERATOR>
void vector<TDATA, TALLOCATOR>::insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::Vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrEnd);

	// 2) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	// 1) Count�� ���Ѵ�.
	size_type	nCount	 = _Last-_First;

#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 2) _size�� _capacity���� ũ�ų� ������ vector�� ũ�⸦ ���δ�.
	if(remained()>=nCount)
	{
#else
	// Error) NO_AUTOEXPAND�� �س��� �ʿ��� ������ŭ reserve�� ���� �ʾҳ�?
	//  (���⼭ Assert�� �ɸ��� NO_AUTOEXPAND �ɼ��� �����ϰų� reserve()
	//  �Լ��� ����� max_size()�� Ȯ���ϸ� �ȴ�.)
	CGD_THROW_IF(remained()<nCount, std::length_error("CGD Exception: �ʰ��� ������ �����մϴ�.("__FUNCTION__")\n"));
#endif

	// 3) ���� �ִ´�.(size�� �ڵ� ����...)
	TDATA*		pSource		 = const_cast<TDATA*>(_Where.m_ptrLast);
	TDATA*		pDest		 = const_cast<TDATA*>(_Where.m_ptrLast+nCount);
	size_type	nMovCount	 = m_ptrLast-pSource;

	// 4) Array�� ��ĭ�� �ڷ� �̷��.
	memmove(pDest, pSource, sizeof(TDATA)*nMovCount);

	// 5) m_ptrLast�� ������Ų��.
	m_ptrLast	+= nCount;

#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	}
	else
	{
		// - ���� �Ҵ������ Iterator�� ��ȿȭ�ǹǷ� �׿� ���� ��� �ؾ��Ѵ�.
		size_t	differ	 = _Where.m_ptrLast-m_ptrFirst;

		// - ���� ũ�⸦ ���Ѵ�.
		size_type	newCapacity	 = capacity()+nCount;

		// - ���� ũ���� 1.5��� �ø���.(�ø��鼭 �׸�ŭ�� ������ ����.
		_Expand(newCapacity+(newCapacity/2), _Where, nCount);

		// - Iterator�� ���� �����Ѵ�.
		_Where	 = const_iterator(m_ptrFirst+differ);
	}
#endif


	//-----------------------------------------------------------------
	// 2. Insert�Ѵ�.
	//-----------------------------------------------------------------
#ifndef _CGD_NO_EXCEPTION_GUARANTEE
	// For Exception) ���� Roll back�� ���� ������ ���´�.
	iterator	iterRoll(const_cast<TDATA*>(_Where.m_ptrLast));
#endif
	
	CGD_TRY
	{
		// 2) ���� ������ Construct�Լ��� �����Ѵ�.
		for(; _First != _Last; ++_First,++_Where)
		{
			m_allocVal.construct(const_cast<TDATA*>(_Where.m_ptrLast), *_First);
		}
	}
	CGD_CATCH_ALL
	{
		// - roll back�� ���� �ٽ� PtrLast�� ���δ�.
		m_ptrLast	-= nCount;

		// - �ٽ� ����� ���� �ּҿ� ������ ����Ѵ�.
		TDATA*		pSource		 = &(*(iterRoll+nCount));
		TDATA*		pDest		 = &(*iterRoll);
		size_type	nMovCount	 = m_ptrLast-pDest;

		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(iterator iter=end(); iter!=_Where; ++iter)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&(*iter));
		}

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy(pDest, pSource, (unsigned long)sizeof(TDATA)*nMovCount);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}


//-----------------------------------------------------------------
// CGD::vector::Insert
//
//  _Where�� ���ʿ� _Count��ŭ _Val���� �����ϴ� �Լ��̴�.
// 
//  vector�� Insert�� reserved�� ������ ���ڶ��� std::vector�� �ϴ�
// reserve�� �����Ѵ�. �̶� ���ο� buffer�� ���� ������ �����Ѵ�.
// �׸��� ���� �ٽ� insert�� ���� ���縦 �ؼ� �߰��� �ڸ��� �����
// �� �ڸ��� �����Ѵ�.
//  CGD������ �̷� �κ��� �����Ͽ� ���� insert�� �ٽ� reserve�ϰ� 
// �ȴٸ� reserve�� ���� ���� �Ҵ���� buffer�� insert�� ������
// �̸� ������� ���縦 �Ѵ�. �� �� �� �ڸ��� insert�� ������ 
// ������ �ִ´�.
// �̷��� �ϸ� insert�� �������� ���縦 �ϴ� ������ �ּ�ȭ�Ҽ� �ִ�.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::insert(const_iterator _Where, int _Count, const_reference _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::Vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrEnd);

	// 2) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) _size�� _capacity���� ũ�ų� ������ vector�� ũ�⸦ ���δ�.
	if(remained()>=(size_type)_Count)
	{
	#else
	// Error) NO_AUTOEXPAND�� �س��� �ʿ��� ������ŭ reserve�� ���� �ʾҳ�?
	//  (���⼭ Assert�� �ɸ��� NO_AUTOEXPAND �ɼ��� �����ϰų� reserve()
	//  �Լ��� ����� max_size()�� Ȯ���ϸ� �ȴ�.)
		CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: �ʰ��� ������ �����մϴ�.("__FUNCTION__")\n"));
	#endif

		// 1) ���� �ִ´�.(size�� �ڵ� ����...)
		TDATA*		pSource	 = const_cast<TDATA*>(&(*_Where));
		TDATA*		pDest	 = const_cast<TDATA*>(&(*(_Where+_Count)));
		size_type	nCount	 = m_ptrLast-pSource;

		// 2) Array�� ��ĭ�� �ڷ� �̷��.
		memmove(pDest, pSource, sizeof(TDATA)*nCount);

		// 3) m_ptrLast�� ������Ų��.
		m_ptrLast	+= _Count;

	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	}
	else
	{
		// - ���� �Ҵ������ Iterator�� ��ȿȭ�ǹǷ� �׿� ���� ��� �ؾ��Ѵ�.
		size_t	differ	 = _Where.m_ptrLast-m_ptrFirst;

		// - ���� ũ�⸦ ���Ѵ�.
		size_type	newCapacity	 = capacity()+_Count;

		// - ���� ũ���� 1.5��� �ø���.(�ø��鼭 �׸�ŭ�� ������ ����.
		_Expand(newCapacity+(newCapacity/2), _Where, _Count);

		// - Iterator�� ���� �����Ѵ�.
		_Where	 = const_iterator(m_ptrFirst+differ);
	}
	#endif


	//-----------------------------------------------------------------
	// 2. Insert�Ѵ�.
	//-----------------------------------------------------------------
	#ifndef _CGD_NO_EXCEPTION_GUARANTEE
	// For Exception) ���� Roll back�� ���� ������ ���´�.
	iterator	iterRoll = _Where;
	#endif

	CGD_TRY
	{
		// 1) ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		const_iterator	iterEnd	 = _Where+_Count;
		for(;_Where!=iterEnd; ++_Where)
		{
			// - Construct�� ȣ���Ѵ�.
			m_allocVal.construct(const_cast<TDATA*>(_Where.m_ptrLast), _Val);
		}
	}
	CGD_CATCH_ALL
	{
		// - roll back�� ���� �ٽ� PtrLast�� ���δ�.
		m_ptrLast	-= _Count;

		// - �ٽ� ����� ���� �ּҿ� ������ ����Ѵ�.
		TDATA*		pSource		 = &(*(iterRoll+_Count));
		TDATA*		pDest		 = &(*iterRoll);
		size_type	nMovCount	 = m_ptrLast-pDest;

		// �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(;iterRoll!=_Where; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&*iterRoll);
		}

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy(pDest, pSource, (unsigned long)sizeof(TDATA)*nMovCount);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}


//-----------------------------------------------------------------
// ����) CGD::vector::Insert
//
//  _Where�� ���ʿ� _Val �ϳ��� �����ϴ� �Լ��̴�.
// 
// vector�� Insert�� reserved�� ������ ���ڶ��� std::vector�� �ϴ�
// reserve�� �����Ѵ�. �̶� ���ο� buffer�� ���� ������ �����Ѵ�.
// �׸��� ���� �ٽ� insert�� ���� ���縦 �ؼ� �߰��� �ڸ��� �����
// �� �ڸ��� �����Ѵ�.
//  CGD������ �̷� �κ��� �����Ͽ� ���� insert�� �ٽ� reserve�ϰ� 
// �ȴٸ� reserve�� ���� ���� �Ҵ���� buffer�� insert�� ������
// �̸� ������� ���縦 �Ѵ�. �� �� �� �ڸ��� insert�� ������ 
// ������ �ִ´�.
// �̷��� �ϸ� insert�� �������� ���縦 �ϴ� ������ �ּ�ȭ�Ҽ� �ִ�.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::iterator vector<TDATA, TALLOCATOR>::insert(const_iterator _Where, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::Vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrEnd);

	// 2) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) _size�� _capacity���� ũ�ų� ������ vector�� ũ�⸦ ���δ�.
	if(m_ptrEnd!=m_ptrLast)
	{
	#else
	// Error) NO_AUTOEXPAND�� �س��� �ʿ��� ������ŭ reserve�� ���� �ʾҳ�?
	//  (���⼭ Assert�� �ɸ��� NO_AUTOEXPAND �ɼ��� �����ϰų� reserve()
	//  �Լ��� ����� max_size()�� Ȯ���ϸ� �ȴ�.)
		CGD_THROW_IF(remained()<_Count, std::out_of_range length_error("CGD Exception: �߰��� ������ �����մϴ�.("__FUNCTION__")\n"));
	#endif
		// - Array�� ��ĭ�� �ڷ� �̷��.
		memmove((void*)(_Where.m_ptrLast+1), (void*)_Where.m_ptrLast, (m_ptrLast-_Where.m_ptrLast)*sizeof(TDATA));

		// - m_ptrLast�� ������Ų��.
		++m_ptrLast;

	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	}
	else
	{
		// - ���� �Ҵ������ Iterator�� ��ȿȭ�ǹǷ� �׿� ���� ��� �ؾ��Ѵ�.
		size_t	differ	 = _Where.m_ptrLast-m_ptrFirst;

		// - ���� ũ�⸦ ���Ѵ�.
		size_type	newCapacity	 = capacity();

		// - ���� ũ���� 1.5��� �ø���.(�ø��鼭 �׸�ŭ�� ������ ����.
		_Expand(newCapacity+(newCapacity/2), _Where, 1);

		// - Iterator�� ���� �����Ѵ�.
		_Where	 = const_iterator(m_ptrFirst+differ);
	}
	#endif


	//-----------------------------------------------------------------
	// 2. Insert�Ѵ�.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		m_allocVal.construct((TDATA*)_Where.m_ptrLast, _Val);
	}
	CGD_CATCH_ALL
	{
		// - roll back�� ���� �ٽ� PtrLast�� ���δ�.
		--m_ptrLast;

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy((void*)_Where.m_ptrLast, (void*)(_Where.m_ptrLast+1), (unsigned long)(m_ptrLast-_Where.m_ptrLast)*sizeof(TDATA));

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// Return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return	iterator((TDATA*)_Where.m_ptrLast);
}



//-----------------------------------------------------------------
// CGD::vector::erase
//
//  _Where��ġ�� Item�� ����� �Լ��̴�.
//
// return���� ���� ���� Item�� Iterator�� �����ش�.
// (Loop���� �� ������� erase()�� �� �� return�Ǿ� ���ƿ��� itreator��
// �ٽ� �޾� end()���� ������ ��� ���������� �ȴ�.
// 
//  ������ std::vector�� �������� ����� �� ���Ŀ� buffer�� ���ܾ�
// �ϴµ� �̶� memcpy�� ����Ͽ� �����.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::iterator vector<TDATA, TALLOCATOR>::erase(const_iterator _Where)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::Vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<m_ptrEnd);

	// 2) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast<=m_ptrLast);

	// 3) _size�� 0���� �۰ų� ������ ���̻� pop�� �Ҽ��� ����!
	CGDASSERT_ERROR(size()>0);


	//-----------------------------------------------------------------
	// 2. �����~
	//-----------------------------------------------------------------
	// 1) �ش���ġ�� Destroy�� ȣ���� �ش�.
	m_allocVal.destroy((TDATA*)&(*_Where));

	// 2) �ش���ġ�� �����.
	memcpy((void*)_Where.m_ptrLast, (void*)(_Where.m_ptrLast+1), (unsigned long)(m_ptrLast-_Where.m_ptrLast-1)*sizeof(TDATA));

	// 3) Last�� ���δ�.
	--m_ptrLast;


	// Return)
	return	iterator((TDATA*)_Where.m_ptrLast);
}

//-----------------------------------------------------------------
// CGD::vector::erase
//
//  _First���� ���� �����ؼ� _Last�� ���ʱ��� Item���� �����.
//
// return���� _Last�� Iterator�� ���� ���̴�.
// 
//  ������ std::vector�� �������� ����� �� ���Ŀ� buffer�� ���ܾ�
// �ϴµ� �̶� memcpy�� ����Ͽ� �����.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::iterator vector<TDATA, TALLOCATOR>::erase(const_iterator _First, const_iterator _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::Vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_First.m_ptrLast>=m_ptrFirst && _First.m_ptrLast<=m_ptrEnd);

	// 2) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_First.m_ptrLast<=m_ptrLast);

	// 3) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Last.m_ptrLast>=m_ptrFirst && _Last.m_ptrLast<=m_ptrEnd);

	// 4) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Last.m_ptrLast<=m_ptrLast);

	// 5) _size�� 0���� �۰ų� ������ ���̻� pop�� �Ҽ��� ����!
	CGDASSERT_ERROR(size()>0);



	//-----------------------------------------------------------------
	// 1. First�� Last�� ���ٸ� �װ�.. ���� ���� ���ٴ� �Ŵ�.
	//-----------------------------------------------------------------
	// 1) First�� Last�� ���ٸ� �׳� �ǵ���.
	size_t	itemCount	 = _Last-_First;

	// Check) itemCount�� 0�̸� ��.. ���ʿ� ����.
	CGD_RETURN_IF(itemCount==0, iterator(_Last.m_ptrLast));


	//-----------------------------------------------------------------
	// 2. Destroy�Լ��� ȣ���Ѵ�.
	//-----------------------------------------------------------------
	for(iterator iter=_First; iter!=_Last; ++iter)
	{
		m_allocVal.destroy(&(*iter));
	}


	//-----------------------------------------------------------------
	// 3. �����~
	//-----------------------------------------------------------------
	// 1) �ش���ġ�� �����.
	memcpy((void*)_First.m_ptrLast, (void*)_Last.m_ptrLast, (unsigned long)(m_ptrLast-_Last.m_ptrLast)*sizeof(TDATA));

	// 2) Size�� ���δ�.
	m_ptrLast		-= itemCount;


	// Return)
	return	iterator(_Last.m_ptrLast);
}


//-----------------------------------------------------------------
// CGD::vector::swap
//
//  _Right�� vector�� ��ä�� �ٲ۴�.
//
// allocator�� ���� ������� �׳� �˸��̸� �ٲٰ� ���࿡ �ٸ��ٸ�
// allocator���� ��ä�� �ٲ۴�.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::swap(_mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) ���� container�� �׳� return�Ѵ�.
	//-----------------------------------------------------------------
	// 1) ���� �Ŷ�� �׳� �ǵ�����.
	CGD_RETURN_IF(this == &_Right,);


	//-----------------------------------------------------------------
	// 1. Swap�Ѵ�.
	//-----------------------------------------------------------------
	// CaseA) Allocator�� ������...(�˸��̸� �ٲ۴�. )
	// - ��Ȳ�� ���� allocator�� vector���� �� Ŭ���� �ֱ� ������ ���縦
	//   �ּ�ȭ �ϱ� ���ؼ�...
	if (m_allocVal == _Right.m_allocVal)
	{
		// �ٲ۴�~(Ptr�����鸸 �ٲ۴�.)
		CGD_SWAP(m_ptrFirst,	_Right.m_ptrFirst);
		CGD_SWAP(m_ptrLast,	_Right.m_ptrLast);
		CGD_SWAP(m_ptrEnd,	_Right.m_ptrEnd);
	}
	// CaseB) Allocator�� �ٸ���...(��°��.. allocator���� ������ �ٲ۴�.)
	else
	{
		// ��ä�� �ٲ۴�.(��ü�� �ٲ�.)
		CGD_SWAP(*this, _Right);
	}
}


//-----------------------------------------------------------------
// CGD::vector::shrink_to_fit
//
//  max_size�� ������ size��ŭ�� ũ��� ���̴� �Լ��̴�.
//
// �������� swap()�� ����Ͽ� �����Ͽ����� ���⼭�� �׳� �Լ��� 
// �������ش�.
//
// shrink_to_fit�Լ��� ȣ���ϸ� ���� size()�� �µ��� ���� buffer�� �Ҵ��ϰ�
// �ű⿡ ���� Item���� memcpy�� ����� �����ϰ� ���� buffer��
// deallocate�Ѵ�.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::shrink_to_fit()
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) �̹� size�� capacity�� ������ �׳� �ǵ�����.
	CGD_RETURN_IF(size()==capacity(),);


	//-----------------------------------------------------------------
	// 1. size�� �´� array�� ���� �Ҵ�޴´�.
	//-----------------------------------------------------------------
	// 1) Array�� �����Ѵ�.
	TDATA*	tempArray	 = m_allocVal.allocate(size()); 


	//-----------------------------------------------------------------
	// 2. ���� array�� �Ҵ������Ѵ�.
	//-----------------------------------------------------------------
	// 1) size�� 0�̸� ���� ���� ������ �ʿ�� ����.
	if(size() != 0)
	{
		// Check) m_ptrFirst�� 0�̾�� �ȵȴ�.
		CGDASSERT_ERROR(m_ptrFirst!=0);

		// - �޸𸮸� �����Ѵ�.
		memcpy(tempArray, m_ptrFirst, (unsigned long)sizeof(TDATA)*size());

		// - ������ data�� �����.(Destroy�� ȣ������ �ʴ´�.)
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);
	}


	//-----------------------------------------------------------------
	// 3. ���� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) �����Ѵ�.
	m_ptrFirst	 = tempArray;

	// 2) Last�� End�� �����Ѵ�.
	tempArray	+=size();
	m_ptrLast	 = tempArray;
	m_ptrEnd	 = tempArray;
}




}