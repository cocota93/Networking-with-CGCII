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

template <typename TDATA, size_t TSIZE>
class static_vector
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

	// Standard 5) Iterators
	class iterator;
	class const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// Self) 자기자신(표준 아님.)
	typedef	static_vector<TDATA, TSIZE>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA, size_t TOTHER_SIZE>
	struct rebind
	{
		typedef static_vector<TOTHER_DATA, TOTHER_SIZE> other;
	};


// ****************************************************************************
// Common Container Standard)
//
//  * Common Container Requirement
//     1) X();			Default Constructor
//     2) X(a);			Copy Constrctor.(소요시간은 선형적)
//		  X u(a);
//     3) (&a)->~X();	Destructor.(소요시간은 선형적)
//     4) a.begin(); 	Container 순회에 사용할 시작과 끝 iterator 
//		  a.end();
//     5) a==b; a!=b;	Container 모든 원소 같으면 true.(소요시간 선형적)
//     6) a.size();		Container에 담김 원소의 갯수를 리턴한다.
//     7) a.max_size();	Container가 담을 수 있는 최대 원소 개수를 리턴한다.
//     8) a.empty();	Container가 비어 있는 경우라면 true를 리턴한다.
//     9) a<b; a>b; 	비교 연산(소요시간 선형적)
//		  a<=b; a>=b;
//    10) r=a;			Container 대입연산(소요시간 선형적)
//    11) a.swap(b);	동일한 타입의 두 커테이너를 서로 맞바꾼다.
//
//  * Reversible Requirement
//     1) a.rbegin(); 	반대방향 순회에 사용될 시작과 끝 iterator
//		  a.rend();
//
// ----------------------------------------------------------------------------
public:
	static_vector();
	static_vector(const _mytype& _Right);
	~static_vector();

public:
	// Common Standard 1) Status Function
	size_type				size() const								{	return m_ptrLast-(TDATA*)m_ptrFirst;}
	size_type				max_size() const							{	return TSIZE;}
	bool					empty() const								{	return (size()==0);}

	// Common Standard 2) 
	iterator				begin()										{	return iterator((TDATA*)m_ptrFirst);}
	const_iterator			begin() const								{	return const_iterator((TDATA*)m_ptrFirst);}
	const_iterator			cbegin() const								{	return const_iterator((TDATA*)m_ptrFirst);}
	iterator				end()										{	return iterator(m_ptrLast);}
	const_iterator			end() const									{	return const_iterator(m_ptrLast);}
	const_iterator			cend() const								{	return const_iterator(m_ptrLast);}
	reverse_iterator		rbegin()									{	return reverse_iterator(iterator(m_ptrLast-1));}
	const_reverse_iterator	rbegin() const								{	return const_reverse_iterator(const_iterator(m_ptrLast-1));}
	const_reverse_iterator	crbegin() const								{	return const_reverse_iterator(const_iterator(m_ptrLast-1));}
	reverse_iterator		rend()										{	return reverse_iterator(iterator(((TDATA*)m_ptrFirst)-1));}
	const_reverse_iterator	rend() const								{	return const_reverse_iterator(const_iterator(((TDATA*)m_ptrFirst)-1));}
	const_reverse_iterator	crend() const								{	return const_reverse_iterator(const_iterator(((TDATA*)m_ptrFirst)-1));}

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
	_mytype&				operator=(_mytype&& _Right);


// ****************************************************************************
// Sequence Container Standard)
//
//  * Sequence Container Requirement
//    1) X(n, t);		t의 복사본 n개로 구성된 Sequence를 생성한다.
//		 X a(n, t);	
//    2) X(i, j); 		구간[i,j]의 내용과 동일한 Sequence를 생성한다.
//		 X a(i, j);
//    3) a.insert(p,t);	p앞에 t의 복사본을 삽입한다. 리턴값은 삽입된
//						원소를 가리키는 반복자이다.
//    4) a.insert(p,n,t);p앞에 t의 복사본 n개를 삽입한다.
//    5) a.insert(p,i,j);p앞에 [i,j]에 담긴 원소들의 복사본을 삽입한다.
//						i,j는 반복자
//    6) a.erase(q);	q가 가리키는 원소를 삭제한다. 리턴값은 삭제되기
//						전에 q다음에 위치했던 원소를 가리키는 반복자
//    7) a.erase(q1,q2);구간[q1,q2]에 포함된 원소들을 삭제한다. 리턴값은
//						삭제되기 전에 q2다음에 위치했던 원소를 가리키는
//						반복자.
//    8) a.clear();		컨테이너에 담긴 뭐든 원소를 삭제한다. 
//						a.erase(a.begin(), a.end())와 동일하다.
//
// ----------------------------------------------------------------------------
public:
	static_vector(size_type _Count);
	static_vector(size_type _Count, const TDATA& _Val);
	template<typename TITERATOR>
	static_vector(TITERATOR _First, TITERATOR _Last);

public:
	// Sequence Standard 1) insert member function
	template<typename TITERATOR>
	void				insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last);
	iterator			insert(const_iterator _Where, const TDATA& _Val);
	void				insert(const_iterator _Where, size_type _Count, const TDATA& _Val);

	// Sequence Standard 2) erase member function
	iterator			erase(const_iterator _Where);
	iterator			erase(const_iterator _First, const_iterator _Last);

	// Sequence Standard 3) clear
	void				clear();


// ****************************************************************************
// static_vector Member)
//
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const							{	return TSIZE;}
	size_type				remained() const							{	return TSIZE-size();}

	// 2) Data
	reference				front()		 								{	return *(TDATA*)m_ptrFirst;}
	const_reference			front() const 								{	return *(TDATA*)m_ptrFirst;}

	reference				back()										{	return *(m_ptrLast-1);}
	const_reference			back() const								{	return *(m_ptrLast-1);}

	reference				at(size_type _Pos);
	const_reference			at(size_type _Pos) const;

	reference				operator [] (size_type _Pos);
	const_reference			operator [] (size_type _Pos) const;

	// 3) push/pop
	void					push_front(const TDATA& _Val);
	void					pop_front();
	void					push_back(const TDATA& _Val);
	void					push_back();
	void					pop_back();

	// 4) Assign
	template <typename ITERATOR>
	void					assign(ITERATOR _First, ITERATOR _Last);
	void					assign(size_type p_Count, const TDATA& _Val);

	// 5) Resize
	void					resize(size_type _Newsize);


// ****************************************************************************
// Member Variable) 
// ----------------------------------------------------------------------------
private:
	// 1) Array
	char					m_ptrFirst[sizeof(TDATA)*TSIZE];			// Array의 처음 위치...
	TDATA*					m_ptrLast;


// ****************************************************************************
// Iterator) 
// ----------------------------------------------------------------------------
public:
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	static_vector<TDATA, TSIZE>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;
	// ----------------------------------------------------------------
	public:
		// 1) 생성자
		const_iterator()												{}
		explicit const_iterator(pointer p_pNow)							{	m_ptrLast=p_pNow;}

		// 2) 대입
		const_iterator&		operator=(const const_iterator& _Right)		{	m_ptrLast=_Right.m_ptrLast; return *this;}
		pointer				operator->()								{	return &**this;}

		// 3) 반복
		const_reference		operator*() const							{	return *m_ptrLast;}
		const_iterator&		operator++()								{	++m_ptrLast; return *this;}
		const_iterator		operator++(int)								{	return const_iterator(m_ptrLast++);}
		const_iterator&		operator--()								{	--m_ptrLast; return *this;}
		const_iterator		operator--(int)								{	return const_iterator(m_ptrLast--);}
		const_iterator		operator+(difference_type _Right) const		{	return const_iterator(m_ptrLast+_Right);}
		void				operator+=(difference_type _Right)			{	m_ptrLast +=_Right;}
		const_iterator		operator-(difference_type _Right) const		{	return const_iterator(m_ptrLast-_Right);}
		void				operator-=(difference_type _Right)			{	m_ptrLast -=_Right;}
		size_type			operator-(const const_iterator& _Right) const{	return m_ptrLast-_Right.m_ptrLast;}
		size_type			operator-(const iterator& _Right) const		{	return m_ptrLast-_Right.m_ptrLast;}

		// 4) 비교
		bool				operator==(const const_iterator& _Right) const	{	return m_ptrLast==_Right.m_ptrLast;}
		bool				operator!=(const const_iterator& _Right) const	{	return m_ptrLast!=_Right.m_ptrLast;}

		bool				operator>(const const_iterator&  _Right) const	{	return m_ptrLast>_Right.m_ptrLast;}
		bool				operator>=(const const_iterator&  _Right)	{	return m_ptrLast>=_Right.m_ptrLast;}
		bool				operator<(const const_iterator&  _Right) const	{	return m_ptrLast<_Right.m_ptrLast;}
		bool				operator<=(const const_iterator&  _Right)	{	return m_ptrLast<=_Right.m_ptrLast;}

		bool				operator>(const iterator&  _Right) const	{	return m_ptrLast>_Right.m_ptrLast;}
		bool				operator>=(const iterator&  _Right)			{	return m_ptrLast>=_Right.m_ptrLast;}
		bool				operator<(const iterator&  _Right) const	{	return m_ptrLast<_Right.m_ptrLast;}
		bool				operator<=(const iterator&  _Right)			{	return m_ptrLast<=_Right.m_ptrLast;}

	private:
		pointer				m_ptrLast;
	};

	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	static_vector<TDATA, TSIZE>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;
	// ----------------------------------------------------------------
	public:
		// 1) 생성자
		iterator()														{}
		explicit iterator(pointer p_pNow)								{	m_ptrLast=p_pNow;}

		// 2) 대입
		iterator&			operator=(const iterator& _Right)			{	m_ptrLast=_Right.m_ptrLast; return *this;}
		iterator&			operator=(const const_iterator& _Right)		{	m_ptrLast=_Right.m_ptrLast; return *this;}
		pointer				operator->()									{	return &**this;}
							operator const_iterator()					{	return const_iterator(m_ptrLast);}

		// 3) 반복
		reference			operator*() const							{	return *m_ptrLast;}
		iterator&			operator++()								{	++m_ptrLast; return *this;}
		iterator			operator++(int)								{	return iterator(m_ptrLast++);}
		iterator&			operator--()								{	--m_ptrLast; return *this;}
		iterator			operator--(int)								{	return iterator(m_ptrLast--);}
		iterator			operator+(difference_type _Right) const		{	return iterator(m_ptrLast+_Right);}
		void				operator+=(difference_type _Right)			{	m_ptrLast +=_Right;}
		iterator			operator-(difference_type _Right) const		{	return iterator(m_ptrLast-_Right);}
		void				operator-=(difference_type _Right)			{	m_ptrLast -=_Right;}
		size_type			operator-(const const_iterator& _Right) const	{	return m_ptrLast-_Right.m_ptrLast;}
		size_type			operator-(const iterator& _Right) const		{	return m_ptrLast-_Right.m_ptrLast;}

		// 4) 비교
		bool				operator==(const iterator& _Right) const	{	return m_ptrLast==_Right.m_ptrLast;}
		bool				operator!=(const iterator& _Right) const	{	return m_ptrLast!=_Right.m_ptrLast;}

		bool				operator==(const const_iterator& _Right) const	{	return m_ptrLast==_Right.m_ptrLast;}
		bool				operator!=(const const_iterator& _Right) const	{	return m_ptrLast!=_Right.m_ptrLast;}
		
		bool				operator>(const const_iterator&  _Right) const	{	return m_ptrLast>_Right.m_ptrLast;}
		bool				operator>=(const const_iterator&  _Right)	{	return m_ptrLast>=_Right.m_ptrLast;}
		bool				operator<(const const_iterator&  _Right) const	{	return m_ptrLast<_Right.m_ptrLast;}
		bool				operator<=(const const_iterator&  _Right)	{	return m_ptrLast<=_Right.m_ptrLast;}

		bool				operator>(const iterator&  _Right) const	{	return m_ptrLast>_Right.m_ptrLast;}
		bool				operator>=(const iterator&  _Right)			{	return m_ptrLast>=_Right.m_ptrLast;}
		bool				operator<(const iterator&  _Right) const	{	return m_ptrLast<_Right.m_ptrLast;}
		bool				operator<=(const iterator&  _Right)			{	return m_ptrLast<=_Right.m_ptrLast;}

	private:
		pointer				m_ptrLast;
	};
};

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector() : m_ptrLast((TDATA*)m_ptrFirst)
{
}

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector(const _mytype& _Right) : m_ptrLast((TDATA*)m_ptrFirst)
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

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector(size_type _Count) : m_ptrLast((TDATA*)m_ptrFirst)
{
	CGD_TRY
	{
		// 1) _Count만큼 초기화한다.
		for(iterator iter=begin(); _Count>0; ++iter, --_Count)
		{
		#pragma push_macro("new")
		#undef new
			new (&(*iter)) TDATA();
		#pragma pop_macro("new")
		}
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		clear();

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector(size_type _Count, const TDATA& _Val) : m_ptrLast((TDATA*)m_ptrFirst)
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

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, size_t TSIZE>
template<typename TITERATOR>
static_vector<TDATA, TSIZE>::static_vector(TITERATOR _First, TITERATOR _Last) : m_ptrLast((TDATA*)m_ptrFirst)
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

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::~static_vector()
{
	// 1) 모두 지운다.
	clear();
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::_mytype& static_vector<TDATA, TSIZE>::operator=(const _mytype& _Right)
{
	// 1) clear all
	clear();

	// 2) Preparing move
	TDATA* _IterSrc=(TDATA*)_Right.m_ptrFirst;
	TDATA* _IterSrcEnd=_Right.m_ptrLast;
	TDATA* _IterDst=(TDATA*)m_ptrFirst;

	// 2) move all by move-constructor
	for(;_IterSrc!=_IterSrcEnd; ++_IterSrc, ++_IterDst)
	{
	#pragma push_macro("new")
	#undef new
		new ((TDATA*)_IterDst) TDATA(*_IterSrc);
	#pragma pop_macro("new")
	}

	// 3) store m_ptrLast
	m_ptrLast		 = _IterDst;

	// Return)
	return	*this;
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::_mytype& static_vector<TDATA, TSIZE>::operator=(_mytype&& _Right)
{
	// 1) clear all
	clear();

	// 2) Preparing move
	TDATA* _IterSrc=(TDATA*)_Right.m_ptrFirst;
	TDATA* _IterSrcEnd=_Right.m_ptrLast;
	TDATA* _IterDst=(TDATA*)m_ptrFirst;

	// 2) move all by move-constructor
	for(;_IterSrc!=_IterSrcEnd; ++_IterSrc, ++_IterDst)
	{
	#pragma push_macro("new")
	#undef new
		new ((TDATA*)_IterDst) TDATA(std::move(*_IterSrc));
	#pragma pop_macro("new")
	}

	// 3) store m_ptrLast
	m_ptrLast		 = _IterDst;

	// 4) clear r-value container
	_Right.m_ptrLast	 = (TDATA*)_Right.m_ptrFirst;

	// Return) 
	return	*this;
}


// 비교함수들
template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator==(const _mytype& _Right) const
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

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator!=(const _mytype& _Right) const	
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

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator<(const _mytype& _Right) const	
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

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator>(const _mytype& _Right) const	
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

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator<=(const _mytype& _Right) const	
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

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator>=(const _mytype& _Right) const	
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

template <typename TDATA, size_t TSIZE>
TDATA& static_vector<TDATA, TSIZE>::at(size_type _Pos)
{
	// Check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: 범위를 넘어선 참조입니다.(" __FUNCTION__ ")\n"))

	// 1) 값을 읽어서 되돌린다.
	return ((TDATA*)m_ptrFirst)[_Pos];
}

template <typename TDATA, size_t TSIZE>
const TDATA& static_vector<TDATA, TSIZE>::at(size_type _Pos) const
{
	// Check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: 범위를 넘어선 참조입니다.(" __FUNCTION__ ")\n"))

	// 1) 값을 읽어서 되돌린다.
	return ((TDATA*)m_ptrFirst)[_Pos];
}

template <typename TDATA, size_t TSIZE>
TDATA& static_vector<TDATA, TSIZE>::operator [] (size_type _Pos)
{
	return	at(_Pos);
}

template <typename TDATA, size_t TSIZE>
const TDATA& static_vector<TDATA, TSIZE>::operator [] (size_type _Pos) const
{
	return	at(_Pos);
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::resize(size_type _Newsize)
{
	// Check) TSIZE보다 작은 크기여야지만 된다.
	CGD_THROW_IF(_Newsize>TSIZE, std::length_error("CGD Exception: 잘못된 크기입니다.(" __FUNCTION__ ")\n"));

	// 1) 
	iterator	iter=end();
	iterator	newEnd(begin()+_Newsize);

	CGD_TRY
	{
		// 2) 늘어난 부분까지 Reset을 한다.
		for(; iter < newEnd(); ++iter)
		{
		#pragma push_macro("new")
		#undef new
			new (&(*iter)) TDATA();
		#pragma pop_macro("new")
		}

		// 3) 줄어들면???(수정요)
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy를 호출한다.
			(*iterRoll).~TDATA();
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) Size를 새로 설정한다.
	m_ptrLast	 = newEnd;
}


template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::clear()
{
	// 1) 모든 Item의 Destructor를 호출한다.
	for(iterator iter=begin(); iter != end(); ++iter)
	{
		(*iter).~TDATA();
	}

	// 2) Last를 First로 만들어 0을 만든다.
	m_ptrLast	 = (TDATA*)m_ptrFirst;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::push_front(const TDATA& _Val)
{
	// CASE-A) if container is empty, just push_back
	if((TDATA*)m_ptrFirst==m_ptrLast)
	{
		// - Push Back
		push_back(_Val);

		// Return) 
		return;
	}

	// 1) get size
	void*	ptrFirst = m_ptrFirst;
	TDATA*	_Iter	 = m_ptrLast;
	size_t	iSize	 = _Iter -(TDATA*)ptrFirst;

	// Check) There is no room for insert! Throw Exception
	CGD_THROW_IF(iSize==TSIZE, std::length_error("CGD Exception: It's Full!(" __FUNCTION__ ")\n"));

	// 3) shift back last one by copy-constructing
#pragma push_macro("new")
#undef new
	new ((TDATA*)_Iter) TDATA(std::move(*(_Iter-1)));
#pragma pop_macro("new")

	// 4) Others do Moving
	for(--_Iter; _Iter>(TDATA*)ptrFirst; --_Iter)
	{
		*_Iter	 = std::move(*(_Iter-1));
	}

	// 5) Assignment _Val in front
	*(TDATA*)ptrFirst = _Val;

	// 6) Increase Size
	++m_ptrLast;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::pop_front()
{
	// 1) get size
	size_t	iSize	 = m_ptrLast-(TDATA*)m_ptrFirst;

	// Check) There is no room for insert! Throw Exception
	CGD_THROW_IF(iSize==0, std::length_error("CGD Exception: It's Full!(" __FUNCTION__ ")\n"));

	// 2) Decrease Size
	--m_ptrLast;

	// 3) Destroy First
	((TDATA*)m_ptrFirst)->~TDATA();

	// 4) Moveing...
	for(TDATA* _Iter=(TDATA*)m_ptrFirst; _Iter<m_ptrLast; ++_Iter)
	{
		*_Iter	 = std::move(*(_Iter+1));
	}
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::push_back(const TDATA& _Val)
{
	// Check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct를 호출한다.
#pragma push_macro("new")
#undef new
	new (m_ptrLast) TDATA(_Val);
#pragma pop_macro("new")
	
	// 2) Last 포인터 증가시킴
	++m_ptrLast;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::push_back()
{
	// Check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct를 호출한다.
#pragma push_macro("new")
#undef new
	new (m_ptrLast) TDATA();
#pragma pop_macro("new")
	
	// 2) Last 포인터 증가시킴
	++m_ptrLast;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::pop_back()
{
	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty를 Check를 하지 않을 경우에 Debug 모드일때 Assert를 띄워준다.
	//   (Release Mode일 때는 아무일도 동작하지 않는다.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty를 Check를 할 경우 Empty를 Check하고 비어 있을 경우 아무동작하지 않고 그냥 끝낸다.
	CGD_RETURN_IF(empty(),);
	#endif

	// 1) 크기를 줄인다.
	--m_ptrLast;

	// 2) Destructor를 호출한다.
	m_ptrLast->~TDATA();
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::assign(size_type _Count, const TDATA& _Val)
{
	// Check) 
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: 크기가 잘못되었습니다.(" __FUNCTION__ ")\n"));

	// 1) 집어넣을 First와 Last를 가리키는 Iterator
	TDATA*	first	 = m_ptrLast;

	// 2) End를 구한다.
	TDATA*	newEnd	 = m_ptrLast+_Count;

	CGD_TRY
	{
		// 3) 값을 넣는다.
		for(; first != newEnd; ++first)
		{
		#pragma push_macro("new")
		#undef new
			new (first) TDATA(_Val);
		#pragma pop_macro("new")
		}
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(TDATA* pRoll=m_ptrLast; pRoll!=first; ++pRoll)
		{
			// - Destroy를 호출한다.
			(*pRoll).~TDATA();
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 4) 완료했으면 m_ptrLast를 newEnd로 바꾼다.
	m_ptrLast	 = newEnd;
}

template <typename TDATA, size_t TSIZE>
template <typename ITERATOR>
void static_vector<TDATA, TSIZE>::assign(ITERATOR _First, ITERATOR _Last)
{
	// 1) 집어넣을 First와 Last를 가리키는 Iterator
	TDATA*	first	 = m_ptrLast;

	CGD_TRY
	{
		// 2) 값을 넣는다.
		for(; _First != _Last; ++_First, ++first)
		{
			// Check) Remained가 0이면 안됀다.
			CGD_THROW_IF(remained()!=0, std::length_error("CGD Exception: 잘못된 크기입니다.(" __FUNCTION__ ")\n"));

		#pragma push_macro("new")
		#undef new
			new (first) TDATA(*_First);
		#pragma pop_macro("new")
		}
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(TDATA* pRoll=m_ptrLast; pRoll!=first; ++pRoll)
		{
			// - Destroy를 호출한다.
			(*pRoll).~TDATA();
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 3) 완료했으면 m_ptrLast를 newEnd로 바꾼다.
	m_ptrLast	 = first;
}

template <typename TDATA, size_t TSIZE>
template<typename TITERATOR>
void static_vector<TDATA, TSIZE>::insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last)
{
	// Check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=(TDATA*)m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);

	// 1) Insert Count를 얻는다.
	size_type	Insertcount	 = _Last-_First;

	// 2) 들어갈 공간이 존재하는지 검사한다.
	CGD_THROW_IF(remained()<Insertcount, std::length_error("CGD Exception: Full!(" __FUNCTION__ ")\n"));

	// 3) source pointer and destination pointer for moving
	TDATA*	_IterSrc	 = m_ptrLast;
	TDATA*	_IterDst	 = _IterSrc+Insertcount;

	// 4) shift back data by move-constructing
	while(_IterDst!=m_ptrLast && _IterSrc>_Where.m_ptrLast)
	{
		--_IterSrc;
		--_IterDst;

	#pragma push_macro("new")
	#undef new
		new (_IterDst) TDATA(std::move(*_IterSrc));
	#pragma pop_macro("new")
	}

	// 5) shift back others by moving
	while(_IterSrc>_Where.m_ptrLast)
	{
		--_IterSrc;
		--_IterDst;

		*_IterDst	 = std::move(*_IterSrc);
	}

	CGD_TRY
	{
		// 6) copy data to _Where
		for(; _First!=_Last; ++_First, ++_IterSrc)
		{
			// - Construct를 호출한다.
		#pragma push_macro("new")
		#undef new
			new (_IterSrc) TDATA(*const_cast<TDATA*>(_First.m_ptrLast));
		#pragma pop_macro("new")
		}
	}
	CGD_CATCH_ALL
	{
		TDATA*	_IterRbDst = const_cast<TDATA*>(_Where.m_ptrLast);
		TDATA*	_IterRbSrc = _IterRbDst+Insertcount;

		// - shift front 
		while(_IterRbDst!=m_ptrLast)
		{
			*_IterRbDst	 = std::move(*_IterRbSrc);
		}

		// - destroy remained
		while(_IterRbDst<_IterSrc)
		{
			_IterRbDst->~TDATA();
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 5) size를 증가시킨다.
	m_ptrLast		+= Insertcount;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::insert(const_iterator _Where, size_type _Count, const TDATA& _Val)
{
	// Check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=(TDATA*)m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);

	// Check) 들어갈 공간이 존재하는지 검사한다.
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: 공간이 부족합니다.(" __FUNCTION__ ")\n"));

	// 1) source pointer and destination pointer for moving
	TDATA*	_IterSrc	 = m_ptrLast;
	TDATA*	_IterDst	 = _IterSrc+_Count;

	// 2) shift back data by move-constructing
	while(_IterDst!=m_ptrLast && _IterSrc>_Where.m_ptrLast)
	{
		--_IterSrc;
		--_IterDst;

	#pragma push_macro("new")
	#undef new
		new (_IterDst) TDATA(std::move(*_IterSrc));
	#pragma pop_macro("new")
	}

	// 3) shift back others by moving
	while(_IterSrc>_Where.m_ptrLast)
	{
		--_IterSrc;
		--_IterDst;

		*_IterDst	 = std::move(*_IterSrc);
	}

	CGD_TRY
	{
		// 4) copy data to _Where
		for(; _IterSrc!=_IterDst; ++_IterSrc)
		{
			// - Construct를 호출한다.
		#pragma push_macro("new")
		#undef new
			new (_IterSrc) TDATA(_Val);
		#pragma pop_macro("new")
		}
	}
	CGD_CATCH_ALL
	{
		TDATA*	_IterRbDst = const_cast<TDATA*>(_Where.m_ptrLast);
		TDATA*	_IterRbSrc = _IterRbDst+_Count;

		// - shift front 
		while(_IterRbDst!=m_ptrLast)
		{
			*_IterRbDst	 = std::move(*_IterRbSrc);
		}

		// - destroy remained
		while(_IterRbDst<_IterSrc)
		{
			_IterRbDst->~TDATA();
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) size를 증가시킨다.
	m_ptrLast		+= _Count;
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::iterator static_vector<TDATA, TSIZE>::insert(const_iterator _Where, const TDATA& _Val)
{
	// 주의) CGD::static_vector에는 max_size()검사는 존재하지 않습니다.

	// Check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=(TDATA*)m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);

	// Check) 남은 공간이 있는지 확인한다.
	CGD_THROW_IF(remained()<=0, std::length_error("CGD Exception: Full!(" __FUNCTION__ ")\n"));
	
	if(_Where.m_ptrLast!=m_ptrLast)
	{
		// 1) set iterator
		TDATA*	_Iter	 = m_ptrLast;

		// 2) move constructing last one
	#pragma push_macro("new")
	#undef new
		new (_Iter) TDATA(std::move(*(_Iter-1)));
	#pragma pop_macro("new")

		// 3) Shift back others by Moving
		for(--_Iter;_Iter!=_Where.m_ptrLast;--_Iter)
		{
			*_Iter	 = std::move(*(_Iter-1));
		}
	}

	CGD_TRY
	{
		// 2) 비운 자리에 Constructor를 호출해 값을 복사한다.
	#pragma push_macro("new")
	#undef new
		new ((TDATA*)_Where.m_ptrLast) TDATA(_Val);
	#pragma pop_macro("new")
	}
	CGD_CATCH_ALL
	{
		// - shift front 
		for(TDATA* _Iter=const_cast<TDATA*>(_Where.m_ptrLast);_Iter!=m_ptrLast;++_Iter)
		{
			*_Iter	 = std::move(*(_Iter+1));
		}

		// Throw) Reraise
		CGD_RETHROW;
	}

	// 3) size를 증가시킨다.
	++m_ptrLast;

	// Return) 되돌린다.(Insert한 위치의 Iterator를 돌려준다.)
	return	iterator((TDATA*)_Where.m_ptrLast);
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::iterator  static_vector<TDATA, TSIZE>::erase(const_iterator _Where)
{
	// Attention) There is no checking of max_size() in CGD::static_vector

	// Check) Iterator is invalid (is within m_ptrLast)
	CGDASSERT_ERROR(_Where.m_ptrLast>=(TDATA*)m_ptrFirst && _Where.m_ptrLast<m_ptrLast);

	// Check) Is empty?
	CGDASSERT_ERROR(size()>0);

	// 1) Call destructor on _Where
	(_Where.m_ptrLast)->~TDATA();

	// 2) Decrease Last pointer
	--m_ptrLast;

	// 3) Moveing forward after _Where
	if(_Where.m_ptrLast!=m_ptrLast)
	{
		// - move-constructing 
	#pragma push_macro("new")
	#undef new
		new (const_cast<TDATA*>(_Where.m_ptrLast)) TDATA(std::move(*const_cast<TDATA*>(_Where.m_ptrLast+1)));
	#pragma pop_macro("new")

		for(++_Where.m_ptrLast; _Where.m_ptrLast<(TDATA*)m_ptrLast; ++_Where)
		{
			*const_cast<TDATA*>(_Where.m_ptrLast)	 = std::move(*const_cast<TDATA*>(_Where.m_ptrLast+1));
		}
	}

	// Return)
	return	iterator((TDATA*)_Where.m_ptrLast);
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::iterator static_vector<TDATA, TSIZE>::erase(const_iterator _First, const_iterator _Last)
{
	// 주의) CGD::static_vector에는 max_size()검사는 존재하지 않습니다.

	// Check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_First.m_ptrLast>=(TDATA*)m_ptrFirst && _First.m_ptrLast<=m_ptrLast);

	// Check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Last.m_ptrLast>=(TDATA*)m_ptrFirst && _Last.m_ptrLast<=m_ptrLast);

	// 1) First와 Last가 같다면 그냥 되돌림.
	size_type	itemCount	 = _Last-_First;

	// Check) ItemCount가 0이면 그냥 끝낸다.
	CGD_RETURN_IF(itemCount==0, iterator(const_cast<TDATA*>(_Last.m_ptrLast)));

	// 2) Destroying 
	for(const_iterator iter=_First; iter!=_Last; ++iter)
	{
		(*iter).~TDATA();
	}

	// 3) move Data to _First
	for(; _Last.m_ptrLast<m_ptrLast; ++_Last.m_ptrLast, ++_First.m_ptrLast)
	{
		// - move construction
	#pragma push_macro("new")
	#undef new
		new (const_cast<TDATA*>(_First.m_ptrLast)) TDATA(std::move(*const_cast<TDATA*>(_Last.m_ptrLast)));
	#pragma pop_macro("new")
	}

	// 4) Size를 줄인다.
	m_ptrLast	-= itemCount;

	// Return)
	return	iterator(const_cast<TDATA*>(_Last.m_ptrLast));
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::swap(_mytype& _Right)
{
	// Check) 같은 거라면 그냥 되돌린다.
	CGD_RETURN_IF(this == &_Right,);

	// 1) 무조건 통채로 바꾼다.(Allocator란 존재치 않는다. 단지 복사...)
	CGD_SWAP(*this, _Right);
}


}