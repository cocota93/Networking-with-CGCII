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
//     1) X:value_type		Contain에 담긴 값들의 형.
//     2) X:reference		X:value_type&.
//     3) X:const_reference	const X:value_type&.
//     4) X:iterator		순회할 때 사용되는 반복자.
//     5) X:const_iterator	순회할 때 사용되는 반복자(const형)
//     6) X:difference_type	두 iterator에 담김 값의 거리를 나타내는 타입.
//     7) X:size_type		X의 크기를 나타낼때 사용되는 형.
//
//  * Reversible Requirement
//     1) X::reverse_iterator 역순환 때 사용되는 반복자.
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

	// Standard 5) Iterators
	class iterator;
	class const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// Allocator)
	typedef TALLOCATOR		allocator_type;

	// Self) 자기자신(표준 아님.)
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
//     2) X(a);				Copy Constrctor.(소요시간은 선형적)
//		  X u(a);
//     3) (&a)->~X();		Destructor.(소요시간은 선형적)
//     4) a.begin(); 		Container 순회에 사용할 시작과 끝 iterator 
//		  a.end();
//     5) a==b; a!=b;		Container 모든 원소 같으면 true.(소요시간 선형적)
//     6) a.size();			Container에 담김 원소의 갯수를 리턴한다.
//     7) a.max_size();		Container가 담을 수 있는 최대 원소 개수를 리턴한다.
//     8) a.empty();		Container가 비어 있는 경우라면 true를 리턴한다.
//     9) a<b; a>b; 		비교 연산(소요시간 선형적)
//		  a<=b; a>=b;
//    10) r=a;				Container 대입연산(소요시간 선형적)
//    11) a.swap(b);		동일한 타입의 두 커테이너를 서로 맞바꾼다.
//
//  * Reversible Requirement
//     1) a.rbegin(); 		반대방향 순회에 사용될 시작과 끝 iterator
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
//    1) X(n, t);			t의 복사본 n개로 구성된 Sequence를 생성한다.
//		 X a(n, t);	
//    2) X(i, j); 			구간[i,j]의 내용과 동일한 Sequence를 생성한다.
//		 X a(i, j);
//    3) a.insert(p,t);		p앞에 t의 복사본을 삽입한다. 리턴값은 삽입된
//							원소를 가리키는 반복자이다.
//    4) a.insert(p,n,t);	p앞에 t의 복사본 n개를 삽입한다.
//    5) a.insert(p,i,j);	p앞에 [i,j]에 담긴 원소들의 복사본을 삽입한다.
//							i,j는 반복자
//    6) a.erase(q);		q가 가리키는 원소를 삭제한다. 리턴값은 삭제되기
//							전에 q다음에 위치했던 원소를 가리키는 반복자
//    7) a.erase(q1,q2);	구간[q1,q2]에 포함된 원소들을 삭제한다. 리턴값은
//							삭제되기 전에 q2다음에 위치했던 원소를 가리키는
//							반복자.
//    8) a.clear();			컨테이너에 담긴 뭐든 원소를 삭제한다. 
//							a.erase(a.begin(), a.end())와 동일하다.
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
	TDATA*					m_ptrFirst;		// Array의 처음 위치...
	TDATA*					m_ptrLast;		// Array에서 사용되고 있는 제일 끝~()
	TDATA*					m_ptrEnd;		// Array할당받은 제일 끝~(reserved)

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
		// 1) 생성자
		const_iterator()												{}
		explicit const_iterator(data_pointer p_pNow) : m_ptrLast(p_pNow) {}

		// 2) 대입
		const_iterator&	operator=(const const_iterator& _Right)			{	m_ptrLast=_Right.m_ptrLast; return *this;}
		pointer			operator->()										{	return &**this;}

		// 3) 반복
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

		// 4) 비교
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
		// 1) 생성자
		iterator()														{}
		iterator(const const_iterator& _Copy) : m_ptrLast(_Copy.m_ptrLast){}
		explicit iterator(pointer _now) : m_ptrLast(_now)				{}

		// 2) 대입
		iterator&		operator=(const iterator& _Right)				{	m_ptrLast=_Right.m_ptrLast; return *this;}
		iterator&		operator=(const const_iterator& _Right)			{	m_ptrLast=_Right.m_ptrLast; return *this;}
		pointer			operator->()										{	return &**this;}
						operator const_iterator()						{	return const_iterator(m_ptrLast);}

		// 3) 반복
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

		// 4) 비교
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
// Constructor/Destructor 함수들.
//
// - 다양한 종류의 constructor와 destructor함수들이다.
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
		// 1) 삽입해넣는다.
		insert(begin(), _Right.begin(), _Right.end());
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::vector(size_type _Count) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) 크기를 조절한다.
		resize(_Count);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::vector(size_type _Count, const TDATA& _Val) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::vector(size_type _Count, const TDATA& _Val, const TALLOCATOR& _Al) : 
m_ptrFirst(0), m_ptrLast(0), m_ptrEnd(0)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) 다시 Thread!!!
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
		// 1) 삽입해넣는다.
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) 다시 Thread!!!
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
		// 1) 삽입해넣는다.
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
vector<TDATA, TALLOCATOR>::~vector()
{
	// 1) 모두 지운다.
	clear();

	// 2) Deallocate한다.
	m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);
}

template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::_mytype& vector<TDATA, TALLOCATOR>::operator=(const _mytype& _Right)
{
	// 1) 일단 모조리 다 지운다.
	clear();

	// 2) 삽입해넣는다.
	CGD_TRY
	{
		insert(begin(), _Right.begin(), _Right.end());
	}
	CGD_CATCH_ALL
	{
		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// Return) 자기 자신 Return
	return	*this;
}


// 비교함수들
template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator==(const _mytype& _Right) const
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Src가 끝인가???
		if(iterSrc==end())
		{
			return	(iterDst==_Right.end());
		}

		// Check) Dst가 끝인가?
		if(iterDst==end())
		{
			return	false;
		}

		// 2) 만약 Src와 Dst가 같지 않으면 바로 false리턴!
		if(*iterSrc!=*iterDst)
		{
			return	false;
		}

		// 3) 다음값~
		++iterSrc;
		++iterDst;
	}
}

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator!=(const _mytype& _Right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Src가 끝인가???
		if(iterSrc==end())
		{
			return	(iterDst!=_Right.end());
		}

		// Check) Dst가 끝인가?
		if(iterDst==end())
		{
			return	true;
		}

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iterSrc!=*iterDst)
		{
			return	true;
		}

		// 3) 다음값~
		++iterSrc;
		++iterDst;
	}
}

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator<(const _mytype& _Right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Dst가 끝인가?
		if(iterDst==end())
		{
			return	false;
		}

		// Check) Src가 끝인가???
		if(iterSrc==end())
		{
			return	true;
		}


		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iterSrc!=*iterDst)
		{
			return	(*iterSrc<*iterDst);
		}

		// 3) 다음값~
		++iterSrc;
		++iterDst;
	}
}

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator>(const _mytype& _Right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Src가 끝인가???
		if(iterSrc==end())
		{
			return	false;
		}

		// Check) Dst가 끝인가?
		if(iterDst==end())
		{
			return	true;
		}

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iterSrc!=*iterDst)
		{
			return	(*iterSrc>*iterDst);
		}

		// 3) 다음값~
		++iterSrc;
		++iterDst;
	}
}

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator<=(const _mytype& _Right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Src가 끝인가???
		if(iterSrc==end())
		{
			return	true;
		}

		// Check) Dst가 끝인가?
		if(iterDst==end())
		{
			return	false;
		}

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iterSrc!=*iterDst)
		{
			return	(*iterSrc<*iterDst);
		}

		// 3) 다음값~
		++iterSrc;
		++iterDst;
	}
}

template <typename TDATA, typename TALLOCATOR>
bool vector<TDATA, TALLOCATOR>::operator>=(const _mytype& _Right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iterSrc=begin();
	typename _mytype::iterator	iterDst	 = _Right.begin();

	for(;;)
	{
		// Check) Dst가 끝인가?
		if(iterDst==end())
		{
			return	true;
		}

		// Check) Src가 끝인가???
		if(iterSrc==end())
		{
			return	false;
		}


		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iterSrc!=*iterDst)
		{
			return	(*iterSrc>*iterDst);
		}

		// 3) 다음값~
		++iterSrc;
		++iterDst;
	}
}



//-----------------------------------------------------------------
// Random access 함수들.
//
// - random access를 지원하는 함수와 operator들...
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::reference vector<TDATA, TALLOCATOR>::at(size_type _Pos)
{
	// Check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: 범위를 넘어선 참조입니다.(" __FUNCTION__ ")\n"))

	// 1) 값을 읽어서 되돌린다.
	return m_ptrFirst[_Pos];
}

template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::const_reference vector<TDATA, TALLOCATOR>::at(size_type _Pos) const
{
	// Check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: 범위를 넘어선 참조입니다.(" __FUNCTION__ ")\n"))

	// 1) 값을 읽어서 되돌린다.
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
// reserve() 함수.
//
// _Count만큼 buffer를 미리 확보하는 함수이다.
//  만약, _Count가 현재 reserve된 크기보다 작을 경우 아무런 동작을
// 수행하지 않을 것이다.
//  _Count가 현재 Reserve된 공간보다 클 경우 _Count만큼으로 확장
// 한다.
// 이 함수 수행해 size()는 변화가  없지만 max_size()는 변할수 있다.
//
//  이때, 새로운 크기의 새로운 buffer를 allocator로부터 할당을
// 받으며 기존의 buffer는 deallocate한다. 
// 기존에 저장되어 있던 data들은 새로 할당받은 buffer의 같은 위치로 
// 복사가 행해진다.(단 constructor는 호출되지 않는다.)
//
//  사용될 최대 갯수를 알게 될 경우 미리 reserve해 놓으면 다시 할당 
// 함으로 인한 추가적으로 들어가는 부하를 줄일 수 있다.
//  std::vector의 경우 이 것을 for_loop문을 통해 복사하였지면 여기서
// 는 memcpy를 통해 수행된다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::reserve(size_type _Count)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) capacity가 이미 _Count보다 크면 그냥 되돌린다.
	if(_Count<=capacity())
	{
		return;
	}

	//-----------------------------------------------------------------
	// 1. 새로운 array를 할당받는다.
	//-----------------------------------------------------------------
	// 1) Array를 설정한다.
	TDATA*	tempArray	 = m_allocVal.allocate(_Count); 


	//-----------------------------------------------------------------
	// 2. 기존 array를 할당해제한다.
	//-----------------------------------------------------------------
	// 1) 새로운 크기를 얻는다.
	size_type	nowSize	 = size();

	// 2) size가 0이면 이전 값을 복사할 필요는 없다.
	if(nowSize != 0 && tempArray !=m_ptrFirst)
	{
		// - 메모리를 복사한다.
		memcpy(tempArray, m_ptrFirst, (unsigned long)sizeof(TDATA)*nowSize);

		// - 기존의 data를 지운다.(Destroy는 호출하지 않는다.)
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);
	}


	//-----------------------------------------------------------------
	// 3. 새로 설정한다.
	//-----------------------------------------------------------------
	// 1) 설정한다.
	m_ptrFirst	 = tempArray;
	m_ptrLast	 = tempArray+nowSize;
	m_ptrEnd	 = tempArray+_Count;
}

//-----------------------------------------------------------------
// _Expand 함수.
//
// 이 함수는 내부에서만 사용되는 함수이다.
// reserve의 변형판으로 똑같이 크기를 확장하는 함수지만 다른 점은  
// 확장하는 과정에서 기존의 data를 복사해 놓을 때 _Where로부터
// _Room만큼의 빈자리를 만든다는 것이다. 
// 주로 Insert를 수행하는 중 Expand가 일어날 경우 사용된다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::_Expand(size_type _Count, const_iterator _Where, size_type _Room)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) capacity가 이미 _Count보다 크면 그냥 되돌린다.
	CGD_RETURN_IF(_Count<=capacity(),);


	//-----------------------------------------------------------------
	// 1. 새로운 array를 할당받는다.
	//-----------------------------------------------------------------
	// 1) Array를 설정한다.
	TDATA*	tempArray	 = m_allocVal.allocate(_Count); 

	// Check) Succeded in allocation?
	CGDASSERT_ERROR(tempArray!=nullptr);

	// Check) if fail to allocation, throw exception 
	CGD_THROW_IF(tempArray==nullptr, std::bad_alloc());


	//-----------------------------------------------------------------
	// 2. 기존 array를 할당해제한다.
	//-----------------------------------------------------------------
	size_type	nowSize	 = size();

	// 1) size가 0이면 이전 값을 복사할 필요는 없다.
	if(nowSize != 0)
	{
		// Check) m_ptrFirst가 0이어서는 안된다.
		CGDASSERT_ERROR(m_ptrFirst!=0);

		// Check) m_ptrFirst가 0이어서는 안된다.
		CGDASSERT_ERROR(_Where.m_ptrLast >= m_ptrFirst && _Where.m_ptrLast <= m_ptrLast);

		// - 전송할 크기를 구한다.
		size_type	sizeFront	 = _Where.m_ptrLast-m_ptrFirst;
		size_type	sizeRear	 = m_ptrLast-_Where.m_ptrLast;

		// - 앞부분을 복사해 옮긴다.
		if(tempArray !=m_ptrFirst)
		{
			memcpy(tempArray, m_ptrFirst, (unsigned long)sizeof(TDATA)*sizeFront);
		}

		// - 뒷부분을 복사해 옮긴다.
		memcpy(tempArray+sizeFront+_Room, _Where.m_ptrLast, (unsigned long)sizeof(TDATA)*sizeRear);

		// - 기존의 할당받은 Memory Chunk를 deallocate한다.(Destroy는 호출하지 않는다.)
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);
	}


	//-----------------------------------------------------------------
	// 3. 새로 설정한다.
	//-----------------------------------------------------------------
	// 1) 설정한다.
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
	// 1. Reserve된 크기 확인.
	//-----------------------------------------------------------------
	// 1) 최대크기보다 크면 크기를 늘린다.
	if(_Newsize > capacity())
	{
		reserve(_Newsize);
	}


	//-----------------------------------------------------------------
	// 2. 크기 조정하기.
	//-----------------------------------------------------------------
	// 1) 
	iterator	iter=end();
	iterator	newEnd(begin()+_Newsize);

	if(newEnd>iter)
	{
		CGD_TRY
		{
			// 2) 늘어난 부분까지 Reset을 한다.
			for(; iter < newEnd; ++iter)
			{
				m_allocVal.construct(&(*iter), _Val);
			}
		}
		CGD_CATCH_ALL
		{
			// - 생성했던 것을 다시 다 Destroy한다.
			for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
			{
				// - Destroy를 호출한다.
				m_allocVal.destroy(&(*iterRoll));
			}

			// Throw) 다시 Thread!!!
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

	// 2) Size를 새로 설정한다.
	m_ptrLast	 = m_ptrFirst+_Newsize;
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::clear()
{
	//-----------------------------------------------------------------
	// 1. Destruct를 한다.
	//-----------------------------------------------------------------
	for(iterator iter=begin(); iter!=end(); ++iter)
	{
		m_allocVal.destroy(&(*iter));
	}


	//-----------------------------------------------------------------
	// 2. Size를 0으로 한다.
	//-----------------------------------------------------------------
	// 1) Last를 First로 만들면 그게 0으로 만드는 것이다.
	m_ptrLast	 = m_ptrFirst;
}

template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::iterator vector<TDATA, TALLOCATOR>::find(const_reference _Val)
{
	// 1) 처음부터 돌려가며 데이타를 찾는다.
	iterator iter=begin();
	for(; iter!=end(); ++iter)
	{
		CGD_BREAK_IF(*iter==_Val);
	}

	// Return) 결과를 return한다.
	return	iter;
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::push_back(const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check) Buffer검사.
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) 꽉찼으면 늘린다.
	if(m_ptrLast==m_ptrEnd)
	{
		// - 현재 크기를 구한다.
		size_type	newCapacity	 = capacity();

		// - 크기를 2배로 늘린다.
		newCapacity	 = newCapacity*2;

		// - 최하보다 작으면 최하로 맞춘다.
		newCapacity	 = (newCapacity>CONTAINER_MIN) ? newCapacity : CONTAINER_MIN;

		// - 새로운 Capacity를 크기를 예약한다.
		reserve(newCapacity);
	}
	#else
	// Error) NO_AUTOEXPAND를 해놓고 필요한 갯수만큼 reserve를 하지 않았나?
	//  (여기서 Assert가 걸리면 NO_AUTOEXPAND 옵션을 제거하거나 reserve()
	//  함수로 충분한 max_size()를 확보하면 된다.)
	CGD_THROW_IF(m_ptrLast==m_ptrEnd, std::length_error("CGD Exception: 더이상 공간이 없습니다.("__FUNCTION__")\n"));
	#endif


	//-----------------------------------------------------------------
	// 1. Push하기.
	//-----------------------------------------------------------------
	// 1) Construct를 호출한다.
	m_allocVal.construct(m_ptrLast, _Val);

	// 2) Last 포인터 증가시킴.
	++m_ptrLast;
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::push_back()
{
	//-----------------------------------------------------------------
	// Check) Buffer검사.
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) 꽉찼으면 늘린다.
	if(m_ptrLast==m_ptrEnd)
	{
		// - 현재 크기를 구한다.
		size_type	newCapacity	 = capacity();

		// - 크기를 2배로 늘린다.
		newCapacity	 = newCapacity*2;

		// - 최하보다 작으면 최하로 맞춘다.
		newCapacity	 = CGD_MAX(newCapacity, CONTAINER_MIN);

		// - 새로운 Capacity를 크기를 예약한다.
		reserve(newCapacity);
	}
	#else
	// Error) NO_AUTOEXPAND를 해놓고 필요한 갯수만큼 reserve를 하지 않았나?
	//  (여기서 Assert가 걸리면 NO_AUTOEXPAND 옵션을 제거하거나 reserve()
	//  함수로 충분한 max_size()를 확보하면 된다.)
	CGD_THROW_IF(m_ptrLast==m_ptrEnd, std::length_error("CGD Exception: 더이상 공간이 없습니다.("__FUNCTION__")\n"));
	#endif


	//-----------------------------------------------------------------
	// 1. Push하기.
	//-----------------------------------------------------------------
	// 1) Construct를 호출한다.
	m_allocVal.construct(m_ptrLast, TDATA());

	// 2) Last 포인터 증가시킴.
	++m_ptrLast;
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::pop_back()
{
	//-----------------------------------------------------------------
	// Check) Empty검사.
	//-----------------------------------------------------------------
	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty를 Check를 하지 않을 경우에 Debug 모드일때 Assert를 띄워준다.
	//   (Release Mode일 때는 아무일도 동작하지 않는다.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty를 Check를 할 경우 Empty를 Check하고 비어 있을 경우 아무 동작하지 않고 그냥 끝낸다.
	if(empty())
	{
		return;
	}
	#endif


	//-----------------------------------------------------------------
	// 1. Pop하기.
	//-----------------------------------------------------------------
	// 1) 크기를 줄인다.
	--m_ptrLast;

	// 2) Destroy를 호출한다.
	m_allocVal.destroy(m_ptrLast);
}

template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::assign(size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// 주의) CGD::Vector에는 max_size()검사는 존재하지 않습니다.
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	// 1. 남은 공간 검사.(삽입가능할 정도의 공간이 남아 있나?)
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) _size가 _capacity보다 크거나 같으면 vector의 크기를 늘인다.
	if(remained()<_Count)
	{
		// - 현재 크기를 구한다.
		size_type	newcapacity	 = capacity()+_Count;

		// - 크기를 2배로 늘린다.
		newcapacity	 = newcapacity*2;

		// - 최하보다 작으면 최하로 맞춘다.
		newcapacity	 = CGD_MAX(newcapacity, CONTAINER_MIN);

		// - 새로운 Capacity를 크기를 예약한다.
		reserve(newcapacity);
	}
	#else
	// Error) NO_AUTOEXPAND를 해놓고 필요한 갯수만큼 reserve를 하지 않았나?
	//  (여기서 Assert가 걸리면 NO_AUTOEXPAND 옵션을 제거하거나 reserve()
	//  함수로 충분한 max_size()를 확보하면 된다.)
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: 추가할 공간이 부족합니다.("__FUNCTION__")\n"));
	#endif


	//-----------------------------------------------------------------
	// 2. 값을 넣는다.
	//-----------------------------------------------------------------
	// 1) 집어넣을 First와 Last를 가리키는 Iterator
	iterator	iter=end();
	iterator	newEnd(end()+_Count);

	CGD_TRY
	{
		// 2) 값을 넣으며 Construct함수를 수행한다.
		for(; iter != newEnd; ++iter)
		{
			m_allocVal.construct(&(*iter), _Val);
		}
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&(*iterRoll));
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 3) Last값을 바꾼다.
	m_ptrLast	+= _Count;
}

template <typename TDATA, typename TALLOCATOR>
template <typename ITERATOR>
void vector<TDATA, TALLOCATOR>::assign(ITERATOR _First, ITERATOR _Last)
{
	//-----------------------------------------------------------------
	// 주의) CGD::Vector에는 max_size()검사는 존재하지 않습니다.
	//-----------------------------------------------------------------
	// Check) 
	__if_exists(ITERATOR::m_ptrLast)
	{
		CGDASSERT_ERROR(_Last.m_ptrLast > _First.m_ptrLast);
	}

	// 1) Size를 구한다.
	size_type	count	 = _Last-_First;

	// Check) count가 0개이면 그냥 끝낸다.
	CGD_RETURN_IF(count == 0,);


	//-----------------------------------------------------------------
	// 1. 남은 공간 검사.(삽입가능할 정도의 공간이 남아 있나?)
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) _size가 _capacity보다 크거나 같으면 vector의 크기를 늘인다.
	if(remained()<count)
	{
		// - 현재 크기를 구한다.
		size_type	newcapacity	 = capacity()+count;

		// - 크기를 2배로 늘린다.
		newcapacity	 = newcapacity*2;

		// - 최하보다 작으면 최하로 맞춘다.
		newcapacity	 = CGD_MAX(newcapacity, CONTAINER_MIN);

		// - 새로운 Capacity를 크기를 예약한다.
		reserve(newcapacity);
	}
	#else
	// Error) NO_AUTOEXPAND를 해놓고 필요한 갯수만큼 reserve를 하지 않았나?
	//  (여기서 Assert가 걸리면 NO_AUTOEXPAND 옵션을 제거하거나 reserve()
	//  함수로 충분한 max_size()를 확보하면 된다.)
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: 추가할 공간이 부족합니다.("__FUNCTION__")\n"));
	#endif


	//-----------------------------------------------------------------
	// 2. 값을 넣는다.
	//-----------------------------------------------------------------
	// 1) 집어넣을 First와 Last를 가리키는 Iterator
	iterator	iter	 = end();

	CGD_TRY
	{
		// 2) 값을 넣으며 Construct함수를 수행한다.
		for(; _First != _Last; ++_First,++iter)
		{
			m_allocVal.construct(&(*iter), *_First);
		}
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&(*iterRoll));
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 3) Last값을 바꾼다.
	m_ptrLast	+= count;
}


//-----------------------------------------------------------------
// 설명) CGD::vector::Insert
//
//  _Where의 앞쪽에 _Val 하나만 삽입하는 함수이다.
// 
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
template<typename TITERATOR>
void vector<TDATA, TALLOCATOR>::insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::Vector에는 max_size()검사는 존재하지 않습니다.

	// 1) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrEnd);

	// 2) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	// 1) Count를 구한다.
	size_type	nCount	 = _Last-_First;

#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 2) _size가 _capacity보다 크거나 같으면 vector의 크기를 늘인다.
	if(remained()>=nCount)
	{
#else
	// Error) NO_AUTOEXPAND를 해놓고 필요한 갯수만큼 reserve를 하지 않았나?
	//  (여기서 Assert가 걸리면 NO_AUTOEXPAND 옵션을 제거하거나 reserve()
	//  함수로 충분한 max_size()를 확보하면 된다.)
	CGD_THROW_IF(remained()<nCount, std::length_error("CGD Exception: 초가할 공간이 부족합니다.("__FUNCTION__")\n"));
#endif

	// 3) 값을 넣는다.(size도 자동 증가...)
	TDATA*		pSource		 = const_cast<TDATA*>(_Where.m_ptrLast);
	TDATA*		pDest		 = const_cast<TDATA*>(_Where.m_ptrLast+nCount);
	size_type	nMovCount	 = m_ptrLast-pSource;

	// 4) Array를 한칸씩 뒤로 미룬다.
	memmove(pDest, pSource, sizeof(TDATA)*nMovCount);

	// 5) m_ptrLast를 증가시킨다.
	m_ptrLast	+= nCount;

#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	}
	else
	{
		// - 새로 할당받으면 Iterator가 무효화되므로 그에 대한 대비를 해야한다.
		size_t	differ	 = _Where.m_ptrLast-m_ptrFirst;

		// - 현재 크기를 구한다.
		size_type	newCapacity	 = capacity()+nCount;

		// - 현재 크기의 1.5배로 늘린다.(늘리면서 그만큼의 공간을 비운다.
		_Expand(newCapacity+(newCapacity/2), _Where, nCount);

		// - Iterator를 새로 설정한다.
		_Where	 = const_iterator(m_ptrFirst+differ);
	}
#endif


	//-----------------------------------------------------------------
	// 2. Insert한다.
	//-----------------------------------------------------------------
#ifndef _CGD_NO_EXCEPTION_GUARANTEE
	// For Exception) 추후 Roll back을 위해 저장해 놓는다.
	iterator	iterRoll(const_cast<TDATA*>(_Where.m_ptrLast));
#endif
	
	CGD_TRY
	{
		// 2) 값을 넣으며 Construct함수를 수행한다.
		for(; _First != _Last; ++_First,++_Where)
		{
			m_allocVal.construct(const_cast<TDATA*>(_Where.m_ptrLast), *_First);
		}
	}
	CGD_CATCH_ALL
	{
		// - roll back을 위해 다시 PtrLast를 줄인다.
		m_ptrLast	-= nCount;

		// - 다시 땡기기 위해 주소와 갯수를 계산한다.
		TDATA*		pSource		 = &(*(iterRoll+nCount));
		TDATA*		pDest		 = &(*iterRoll);
		size_type	nMovCount	 = m_ptrLast-pDest;

		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iter=end(); iter!=_Where; ++iter)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&(*iter));
		}

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy(pDest, pSource, (unsigned long)sizeof(TDATA)*nMovCount);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}


//-----------------------------------------------------------------
// CGD::vector::Insert
//
//  _Where의 앞쪽에 _Count만큼 _Val값을 삽입하는 함수이다.
// 
//  vector의 Insert시 reserved된 공간이 모자랄때 std::vector는 일단
// reserve를 수행한다. 이때 새로운 buffer로 기존 내용을 복사한다.
// 그리고 나서 다시 insert를 위해 복사를 해서 중간에 자리를 비운후
// 그 자리에 복사한다.
//  CGD에서는 이런 부분을 개선하여 만약 insert시 다시 reserve하게 
// 된다면 reserve로 인해 새로 할당받은 buffer에 insert될 공간을
// 미리 비워놓고 복사를 한다. 그 후 그 자리에 insert한 내용을 
// 복사해 넣는다.
// 이렇게 하면 insert시 이중으로 복사를 하는 현상을 최소화할수 있다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::insert(const_iterator _Where, int _Count, const_reference _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::Vector에는 max_size()검사는 존재하지 않습니다.

	// 1) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrEnd);

	// 2) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) _size가 _capacity보다 크거나 같으면 vector의 크기를 늘인다.
	if(remained()>=(size_type)_Count)
	{
	#else
	// Error) NO_AUTOEXPAND를 해놓고 필요한 갯수만큼 reserve를 하지 않았나?
	//  (여기서 Assert가 걸리면 NO_AUTOEXPAND 옵션을 제거하거나 reserve()
	//  함수로 충분한 max_size()를 확보하면 된다.)
		CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: 초가할 공간이 부족합니다.("__FUNCTION__")\n"));
	#endif

		// 1) 값을 넣는다.(size도 자동 증가...)
		TDATA*		pSource	 = const_cast<TDATA*>(&(*_Where));
		TDATA*		pDest	 = const_cast<TDATA*>(&(*(_Where+_Count)));
		size_type	nCount	 = m_ptrLast-pSource;

		// 2) Array를 한칸씩 뒤로 미룬다.
		memmove(pDest, pSource, sizeof(TDATA)*nCount);

		// 3) m_ptrLast를 증가시킨다.
		m_ptrLast	+= _Count;

	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	}
	else
	{
		// - 새로 할당받으면 Iterator가 무효화되므로 그에 대한 대비를 해야한다.
		size_t	differ	 = _Where.m_ptrLast-m_ptrFirst;

		// - 현재 크기를 구한다.
		size_type	newCapacity	 = capacity()+_Count;

		// - 현재 크기의 1.5배로 늘린다.(늘리면서 그만큼의 공간을 비운다.
		_Expand(newCapacity+(newCapacity/2), _Where, _Count);

		// - Iterator를 새로 설정한다.
		_Where	 = const_iterator(m_ptrFirst+differ);
	}
	#endif


	//-----------------------------------------------------------------
	// 2. Insert한다.
	//-----------------------------------------------------------------
	#ifndef _CGD_NO_EXCEPTION_GUARANTEE
	// For Exception) 추후 Roll back을 위해 저장해 놓는다.
	iterator	iterRoll = _Where;
	#endif

	CGD_TRY
	{
		// 1) 비운 자리에 Construct를 호출해 값을 복사한다.
		const_iterator	iterEnd	 = _Where+_Count;
		for(;_Where!=iterEnd; ++_Where)
		{
			// - Construct를 호출한다.
			m_allocVal.construct(const_cast<TDATA*>(_Where.m_ptrLast), _Val);
		}
	}
	CGD_CATCH_ALL
	{
		// - roll back을 위해 다시 PtrLast를 줄인다.
		m_ptrLast	-= _Count;

		// - 다시 땡기기 위해 주소와 갯수를 계산한다.
		TDATA*		pSource		 = &(*(iterRoll+_Count));
		TDATA*		pDest		 = &(*iterRoll);
		size_type	nMovCount	 = m_ptrLast-pDest;

		// 생성했던 것을 다시 다 Destroy한다.
		for(;iterRoll!=_Where; ++iterRoll)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&*iterRoll);
		}

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy(pDest, pSource, (unsigned long)sizeof(TDATA)*nMovCount);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}


//-----------------------------------------------------------------
// 설명) CGD::vector::Insert
//
//  _Where의 앞쪽에 _Val 하나만 삽입하는 함수이다.
// 
// vector의 Insert시 reserved된 공간이 모자랄때 std::vector는 일단
// reserve를 수행한다. 이때 새로운 buffer로 기존 내용을 복사한다.
// 그리고 나서 다시 insert를 위해 복사를 해서 중간에 자리를 비운후
// 그 자리에 복사한다.
//  CGD에서는 이런 부분을 개선하여 만약 insert시 다시 reserve하게 
// 된다면 reserve로 인해 새로 할당받은 buffer에 insert될 공간을
// 미리 비워놓고 복사를 한다. 그 후 그 자리에 insert한 내용을 
// 복사해 넣는다.
// 이렇게 하면 insert시 이중으로 복사를 하는 현상을 최소화할수 있다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::iterator vector<TDATA, TALLOCATOR>::insert(const_iterator _Where, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::Vector에는 max_size()검사는 존재하지 않습니다.

	// 1) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrEnd);

	// 2) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	// 1) _size가 _capacity보다 크거나 같으면 vector의 크기를 늘인다.
	if(m_ptrEnd!=m_ptrLast)
	{
	#else
	// Error) NO_AUTOEXPAND를 해놓고 필요한 갯수만큼 reserve를 하지 않았나?
	//  (여기서 Assert가 걸리면 NO_AUTOEXPAND 옵션을 제거하거나 reserve()
	//  함수로 충분한 max_size()를 확보하면 된다.)
		CGD_THROW_IF(remained()<_Count, std::out_of_range length_error("CGD Exception: 추가할 공간이 부족합니다.("__FUNCTION__")\n"));
	#endif
		// - Array를 한칸씩 뒤로 미룬다.
		memmove((void*)(_Where.m_ptrLast+1), (void*)_Where.m_ptrLast, (m_ptrLast-_Where.m_ptrLast)*sizeof(TDATA));

		// - m_ptrLast를 증가시킨다.
		++m_ptrLast;

	#ifndef _CGD_VECTOR_NO_AUTOEXPAND
	}
	else
	{
		// - 새로 할당받으면 Iterator가 무효화되므로 그에 대한 대비를 해야한다.
		size_t	differ	 = _Where.m_ptrLast-m_ptrFirst;

		// - 현재 크기를 구한다.
		size_type	newCapacity	 = capacity();

		// - 현재 크기의 1.5배로 늘린다.(늘리면서 그만큼의 공간을 비운다.
		_Expand(newCapacity+(newCapacity/2), _Where, 1);

		// - Iterator를 새로 설정한다.
		_Where	 = const_iterator(m_ptrFirst+differ);
	}
	#endif


	//-----------------------------------------------------------------
	// 2. Insert한다.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) 비운 자리에 Construct를 호출해 값을 복사한다.
		m_allocVal.construct((TDATA*)_Where.m_ptrLast, _Val);
	}
	CGD_CATCH_ALL
	{
		// - roll back을 위해 다시 PtrLast를 줄인다.
		--m_ptrLast;

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy((void*)_Where.m_ptrLast, (void*)(_Where.m_ptrLast+1), (unsigned long)(m_ptrLast-_Where.m_ptrLast)*sizeof(TDATA));

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// Return) 되돌린다.(Insert한 위치의 Iterator를 돌려준다.)
	return	iterator((TDATA*)_Where.m_ptrLast);
}



//-----------------------------------------------------------------
// CGD::vector::erase
//
//  _Where위치의 Item을 지우는 함수이다.
//
// return값은 지운 다음 Item의 Iterator를 돌려준다.
// (Loop돌며 다 지울려면 erase()한 후 그 return되어 돌아오는 itreator를
// 다시 받아 end()나올 때까지 계속 지워나가면 된다.
// 
//  기존의 std::vector와 차이점은 지우고 난 이후에 buffer를 땡겨야
// 하는데 이때 memcpy를 사용하여 땡긴다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::iterator vector<TDATA, TALLOCATOR>::erase(const_iterator _Where)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::Vector에는 max_size()검사는 존재하지 않습니다.

	// 1) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<m_ptrEnd);

	// 2) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast<=m_ptrLast);

	// 3) _size가 0보다 작거나 같으면 더이상 pop을 할수가 없다!
	CGDASSERT_ERROR(size()>0);


	//-----------------------------------------------------------------
	// 2. 지운다~
	//-----------------------------------------------------------------
	// 1) 해당위치에 Destroy를 호출해 준다.
	m_allocVal.destroy((TDATA*)&(*_Where));

	// 2) 해당위치로 지운다.
	memcpy((void*)_Where.m_ptrLast, (void*)(_Where.m_ptrLast+1), (unsigned long)(m_ptrLast-_Where.m_ptrLast-1)*sizeof(TDATA));

	// 3) Last를 줄인다.
	--m_ptrLast;


	// Return)
	return	iterator((TDATA*)_Where.m_ptrLast);
}

//-----------------------------------------------------------------
// CGD::vector::erase
//
//  _First에서 부터 시작해서 _Last의 앞쪽까지 Item들을 지운다.
//
// return값은 _Last를 Iterator에 넣은 값이다.
// 
//  기존의 std::vector와 차이점은 지우고 난 이후에 buffer를 땡겨야
// 하는데 이때 memcpy를 사용하여 땡긴다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
typename vector<TDATA, TALLOCATOR>::iterator vector<TDATA, TALLOCATOR>::erase(const_iterator _First, const_iterator _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::Vector에는 max_size()검사는 존재하지 않습니다.

	// 1) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_First.m_ptrLast>=m_ptrFirst && _First.m_ptrLast<=m_ptrEnd);

	// 2) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_First.m_ptrLast<=m_ptrLast);

	// 3) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Last.m_ptrLast>=m_ptrFirst && _Last.m_ptrLast<=m_ptrEnd);

	// 4) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Last.m_ptrLast<=m_ptrLast);

	// 5) _size가 0보다 작거나 같으면 더이상 pop을 할수가 없다!
	CGDASSERT_ERROR(size()>0);



	//-----------------------------------------------------------------
	// 1. First와 Last가 같다면 그건.. 지울 것이 없다는 거다.
	//-----------------------------------------------------------------
	// 1) First와 Last가 같다면 그냥 되돌림.
	size_t	itemCount	 = _Last-_First;

	// Check) itemCount가 0이면 뭐.. 할필요 없다.
	CGD_RETURN_IF(itemCount==0, iterator(_Last.m_ptrLast));


	//-----------------------------------------------------------------
	// 2. Destroy함수를 호출한다.
	//-----------------------------------------------------------------
	for(iterator iter=_First; iter!=_Last; ++iter)
	{
		m_allocVal.destroy(&(*iter));
	}


	//-----------------------------------------------------------------
	// 3. 땡긴다~
	//-----------------------------------------------------------------
	// 1) 해당위치를 지운다.
	memcpy((void*)_First.m_ptrLast, (void*)_Last.m_ptrLast, (unsigned long)(m_ptrLast-_Last.m_ptrLast)*sizeof(TDATA));

	// 2) Size를 줄인다.
	m_ptrLast		-= itemCount;


	// Return)
	return	iterator(_Last.m_ptrLast);
}


//-----------------------------------------------------------------
// CGD::vector::swap
//
//  _Right의 vector와 통채로 바꾼다.
//
// allocator가 같은 종류라면 그냥 알맹이만 바꾸고 만약에 다르다면
// allocator가지 통채로 바꾼다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::swap(_mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) 같은 container면 그냥 return한다.
	//-----------------------------------------------------------------
	// 1) 같은 거라면 그냥 되돌린다.
	CGD_RETURN_IF(this == &_Right,);


	//-----------------------------------------------------------------
	// 1. Swap한다.
	//-----------------------------------------------------------------
	// CaseA) Allocator가 같으면...(알맹이만 바꾼다. )
	// - 상황에 따라 allocator가 vector보다 더 클수도 있기 때문에 복사를
	//   최소화 하기 위해서...
	if (m_allocVal == _Right.m_allocVal)
	{
		// 바꾼다~(Ptr정보들만 바꾼다.)
		CGD_SWAP(m_ptrFirst,	_Right.m_ptrFirst);
		CGD_SWAP(m_ptrLast,	_Right.m_ptrLast);
		CGD_SWAP(m_ptrEnd,	_Right.m_ptrEnd);
	}
	// CaseB) Allocator가 다르면...(통째로.. allocator까지 모조리 바꾼다.)
	else
	{
		// 통채로 바꾼다.(통체로 바꿈.)
		CGD_SWAP(*this, _Right);
	}
}


//-----------------------------------------------------------------
// CGD::vector::shrink_to_fit
//
//  max_size를 현재의 size만큼의 크기로 줄이는 함수이다.
//
// 기존에는 swap()을 사용하여 구현하였지만 여기서는 그냥 함수로 
// 제공해준다.
//
// shrink_to_fit함수를 호출하면 현재 size()에 맞도록 새로 buffer를 할당하고
// 거기에 기존 Item들을 memcpy를 사용해 복사하고 기존 buffer는
// deallocate한다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
void vector<TDATA, TALLOCATOR>::shrink_to_fit()
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) 이미 size와 capacity가 같으면 그냥 되돌린다.
	CGD_RETURN_IF(size()==capacity(),);


	//-----------------------------------------------------------------
	// 1. size에 맞는 array를 새로 할당받는다.
	//-----------------------------------------------------------------
	// 1) Array를 설정한다.
	TDATA*	tempArray	 = m_allocVal.allocate(size()); 


	//-----------------------------------------------------------------
	// 2. 기존 array를 할당해제한다.
	//-----------------------------------------------------------------
	// 1) size가 0이면 이전 값을 복사할 필요는 없다.
	if(size() != 0)
	{
		// Check) m_ptrFirst가 0이어서는 안된다.
		CGDASSERT_ERROR(m_ptrFirst!=0);

		// - 메모리를 복사한다.
		memcpy(tempArray, m_ptrFirst, (unsigned long)sizeof(TDATA)*size());

		// - 기존의 data를 지운다.(Destroy는 호출하지 않는다.)
		m_allocVal.deallocate(m_ptrFirst, m_ptrEnd-m_ptrFirst);
	}


	//-----------------------------------------------------------------
	// 3. 새로 설정한다.
	//-----------------------------------------------------------------
	// 1) 설정한다.
	m_ptrFirst	 = tempArray;

	// 2) Last와 End를 설정한다.
	tempArray	+=size();
	m_ptrLast	 = tempArray;
	m_ptrEnd	 = tempArray;
}




}