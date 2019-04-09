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

template <typename TDATA, typename TALLOCATOR=allocator<TDATA> >
class circular
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

	// Standard 5) Iterators.
	class iterator;
	class const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// Allocator) 
	typedef TALLOCATOR	allocator_type;

	// Self) 자기자신(표준 아님.)
	typedef	circular<TDATA, TALLOCATOR>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA, typename TOTHER_ALLOCATOR=TALLOCATOR>
	struct rebind
	{
		typedef circular<TOTHER_DATA, TOTHER_ALLOCATOR> other;
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
	circular();
	circular(const _mytype& _Right);
	~circular();

public:
	// Common Standard 1) Status Function
	size_type				size() const							{	return m_posTail-m_posHead;}
	size_type				max_size() const						{	return CONTAINER_MAX;}
	bool					empty() const							{	return m_posHead==m_posTail;}

	// Common Standard 2) 
	iterator				begin()									{	return iterator(m_ptr, m_posHead, m_mask);}
	const_iterator			begin() const							{	return const_iterator(m_ptr, m_posHead, m_mask);}
	iterator				end()									{	return iterator(m_ptr, m_posTail, m_mask);}
	const_iterator			end() const								{	return const_iterator(m_ptr, m_posTail, m_mask);}
	reverse_iterator		rbegin()								{	return reverse_iterator(iterator(m_ptr, m_posTail-1, m_mask));}
	const_reverse_iterator	rbegin() const							{	return const_reverse_iterator(const_iterator(m_ptr, m_posTail-1, m_mask));}
	reverse_iterator		rend()									{	return reverse_iterator(iterator(m_ptr, m_posHead-1, m_mask));}
	const_reverse_iterator	rend() const							{	return const_reverse_iterator(const_iterator(m_ptr, m_posHead-1, m_mask));}

	// Common Standard 3) 
	void					swap(_mytype& _Right);

	// Common Standard 5) Operators
	bool					operator==(const _mytype& _Right) const	{	return true;}
	bool					operator!=(const _mytype& _Right) const	{	return true;}
	bool					operator<(const _mytype& _Right) const	{	return true;}
	bool					operator>=(const _mytype& _Right) const	{	return true;}
	bool					operator>(const _mytype& _Right) const	{	return true;}
	void					operator=(const _mytype& _Right) const	{	;}


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
	circular(size_type _Count);
	circular(size_type _Count, const TDATA& _Val);
	circular(size_type _Count, const TDATA& _Val, const TALLOCATOR& _Al);
	template<typename TITERATOR>
	circular(TITERATOR _First, TITERATOR _Last);
	template<typename TITERATOR>
	circular(TITERATOR _First, TITERATOR _Last, const TALLOCATOR& _Al);

public:
	// Sequence Standard 1) insert member function
	template<typename TITERATOR>
	void					insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last);
	iterator				insert(const_iterator _Where, const TDATA& _Val);
	void					insert(const_iterator _Where, size_type _Count, const TDATA& _Val);

	// Sequence Standard 2) erase member function
	iterator				erase(const_iterator _Where);
	iterator				erase(const_iterator _First, const_iterator _Last);

	// Sequence Standard 3) clear
	void					clear();


// ****************************************************************************
// circular Member)
//
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const						{	return m_capacity;}
	size_type				remained() const						{	return m_capacity-size();}

	// 2) Data
	reference				front()									{	return *(m_ptr+(m_posHead & m_mask));}
	const_reference			front() const							{	return *(m_ptr+(m_posHead & m_mask));}

	reference				back()									{	return *(m_ptr+((m_posTail-1) & m_mask));}
	const_reference			back() const							{	return *(m_ptr+((m_posTail-1) & m_mask));}

	reference				at(size_type _posNow);
	const_reference			at(size_type _posNow) const;

	reference				operator [] (size_type _posNow);
	const_reference			operator [] (size_type _posNow) const;

	// 3) push/pop
	void					push_front(const TDATA& _Val);
	void					push_front();
	void					pop_front();

	void					push_back(const TDATA& _Val);
	void					push_back();
	void					pop_back();

	// 4) Assign
	void					assign(size_type p_Count, const TDATA& _Val);
	void					assign(const_iterator _First, const_iterator _Last);

	// 5) Reserve
	void					reserve(size_type _Count);

	// 6) Resize
	void					resize(size_type _Newsize);

	// 7) Allocation
	allocator_type			get_allocator() const					{	return m_allocVal;}


// ****************************************************************************
// Member Variable) 
// ----------------------------------------------------------------------------
private:
	// 1) Array
	TDATA*					m_ptr;			// Array의 처음 위치...

	unsigned				m_posHead;		// Head의 Index
	unsigned				m_posTail;		// Tail의 Index

	unsigned				m_mask;			// pos의 Index를 위한 Mask
	unsigned				m_capacity;		// 용량(무조건 2의 배수임.)

	// 2) Allocator
	allocator_type			m_allocVal;


// ****************************************************************************
// Iterator) 
// ----------------------------------------------------------------------------
public:
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	circular<TDATA, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;
	// ----------------------------------------------------------------
	public:
		// 1) 생성자
		const_iterator()											{}
		explicit const_iterator(TDATA* ptr, unsigned pos, unsigned mask)	{	m_ptr=ptr; m_posNow=pos; m_mask=mask;}

		// 2) 대입
		const_iterator&		operator=(const  const_iterator& _Right){	m_ptr=_Right.m_ptr; m_posNow=_Right.m_posNow;m_mask=_Right.m_mask; return *this;}
		const_reference		operator->()							{	return *(m_ptr+(m_posNow & m_mask));}

		// 3) 반복
		const_reference		operator*() const						{	return *(m_ptr+(m_posNow & m_mask));}
		const_iterator&		operator++()							{	++m_posNow; return *this;}
		const_iterator		operator++(int)							{	iterator iter(*this); m_posNow++; return iter;}
		const_iterator&		operator--()							{	--m_posNow; return *this;}
		const_iterator		operator--(int)							{	iterator iter(*this); m_posNow++; return iter;}
		const_iterator		operator+(difference_type _Right)		{	m_posNow+=_Right; return iterator(*this);}
		void				operator+=(difference_type _Right)		{	m_posNow+=_Right;}
		const_iterator		operator-(difference_type _Right)		{	m_posNow-=_Right; return iterator(*this);}
		void				operator-=(difference_type _Right)		{	m_posNow-=_Right;}

		// 4) 비교
		bool				operator==(const const_iterator& _Right) const{	CGDASSERT_ERROR(m_ptr==_Right.m_ptr); return m_posNow==_Right.m_posNow;}
		bool				operator!=(const const_iterator& _Right) const{	CGDASSERT_ERROR(m_ptr==_Right.m_ptr); return m_posNow!=_Right.m_posNow;}

	private:
		const TDATA*		m_ptr;
		unsigned			m_posNow;
		unsigned			m_mask;
	};


	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	circular<TDATA, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;
	// ----------------------------------------------------------------
	public:
		// 1) 생성자
		iterator()													{}
		explicit iterator(TDATA* ptr, unsigned pos, unsigned mask)	{	m_ptr=ptr; m_posNow=pos; m_mask=mask;}

		// 2) 대입(Assignment)
		iterator&			operator=(const iterator& _Right)		{	m_ptr=_Right.m_ptr; m_posNow=_Right.m_posNow;m_mask=_Right.m_mask; return *this;}
		iterator&			operator=(const const_iterator& _Right)	{	m_ptr=_Right.m_ptr; m_posNow=_Right.m_posNow;m_mask=_Right.m_mask; return *this;}
							operator const_iterator()				{	return const_iterator(m_ptr, m_posNow, m_mask);}

		// 3) ...
		reference			operator->()							{	return *(m_ptr+(m_posNow & m_mask));}

		// 4) Iteration
		reference			operator*() const						{	return *(m_ptr+(m_posNow & m_mask));}
		iterator&			operator++()							{	++m_posNow; return *this;}
		iterator			operator++(int)							{	iterator iter(*this); m_posNow++; return iter;}
		iterator&			operator--()							{	--m_posNow; return *this;}
		iterator			operator--(int)							{	iterator iter(*this); m_posNow++; return iter;}
		iterator			operator+(difference_type _Right)		{	m_posNow+=_Right; return iterator(*this);}
		void				operator+=(difference_type _Right)		{	m_posNow+=_Right;}
		iterator			operator-(difference_type _Right)		{	m_posNow-=_Right; return iterator(*this);}
		void				operator-=(difference_type _Right)		{	m_posNow-=_Right;}

		// 4) Compare
		bool				operator==(const iterator& _Right) const{	CGDASSERT_ERROR(m_ptr==_Right.m_ptr); return m_posNow==_Right.m_posNow;}
		bool				operator!=(const iterator& _Right) const{	CGDASSERT_ERROR(m_ptr==_Right.m_ptr); return m_posNow!=_Right.m_posNow;}

		bool				operator==(const const_iterator& _Right) const{	CGDASSERT_ERROR(m_ptr==_Right.m_ptr); return m_posNow==_Right.m_posNow;}
		bool				operator!=(const const_iterator& _Right) const{	CGDASSERT_ERROR(m_ptr==_Right.m_ptr); return m_posNow!=_Right.m_posNow;}

	private:
		TDATA*				m_ptr;
		unsigned			m_posNow;
		unsigned			m_mask;
	};
};




//-----------------------------------------------------------------
// Constructor/Destructor 함수들.
//
// - 다양한 종류의 constructor와 destructor함수들이다.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular() : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	// 1) 기본 Reserve한다.
	reserve(16);
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular(const _mytype& _Right) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		insert(begin(), _Right.begin(), _Right.end());
	}
	CGD_CATCH_ALL
	{
		// - 클리어한다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular(size_type _Count) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) 일단 _Count만큼 Reserve한다.
		reserve(_Count);

		// 1) 삽입해넣는다.
		for(;_Count>0; --_Count)
		{
			// 1) Construct를 호출한다.
			m_allocVal.construct(m_ptr+(m_posTail & m_mask));

			// 2) Tail Pointer를 증가시킨다.
			++m_posTail;
		}
	}
	CGD_CATCH_ALL
	{
		// - 클리어한다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular(size_type _Count, const TDATA& _Val) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		// - 클리어한다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular(size_type _Count, const TDATA& _Val, const TALLOCATOR& _Al) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		// - 클리어한다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
template<typename TITERATOR>
circular<TDATA, TALLOCATOR>::circular(TITERATOR _First, TITERATOR _Last) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		// - 클리어한다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
template<typename TITERATOR>
circular<TDATA, TALLOCATOR>::circular(TITERATOR _First, TITERATOR _Last, const TALLOCATOR& _Al) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		// - 클리어한다.
		clear();

		// - Deallocate한다.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::~circular()
{
	// 1) 모두 지운다.
	clear();

	// 2) Deallocate한다.
	m_allocVal.deallocate(m_ptr, m_capacity);
}




//-----------------------------------------------------------------
// Random access 함수들.
//
// - random access를 지원하는 함수와 operator들...
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
TDATA& circular<TDATA, TALLOCATOR>::at(size_type _posNow)
{
	// Check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_posNow<0 || _posNow>=size(), std::out_of_range("CGD Exception: 범위를 넘어선 참조입니다.(CGD::circular<TDATA, TALLOCATOR>::at(size_type _posNow))\n"))

	// 1) 값을 읽어서 되돌린다.
	unsigned	position	 = ((m_posHead+_posNow) & m_mask);

	// 2) 값을 Return한다.
	return m_ptr[position];
}

template <typename TDATA, typename TALLOCATOR>
const TDATA& circular<TDATA, TALLOCATOR>::at(size_type _posNow) const
{
	// Check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_posNow<0 || _posNow>=size(), std::out_of_range("CGD Exception: 범위를 넘어선 참조입니다.(CGD::circular<TDATA, TALLOCATOR>::at(size_type _posNow))\n"))

	// 1) 값을 읽어서 되돌린다.
	unsigned	position	 = ((m_posHead+_posNow) & m_mask);

	// 2) 값을 Return한다.
	return m_ptr[position];
}


template <typename TDATA, typename TALLOCATOR>
TDATA& circular<TDATA, TALLOCATOR>::operator [] (size_type _posNow)
{
	return	at(_posNow);
}

template <typename TDATA, typename TALLOCATOR>
const TDATA& circular<TDATA, TALLOCATOR>::operator [] (size_type _posNow) const
{
	return	at(_posNow);
}





template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::reserve(size_type _Count)
{
	//-----------------------------------------------------------------
	// Debug Check)
	//-----------------------------------------------------------------
	// Check) 최소 16 이상은 되야 된다.(4Bit)
	CGDASSERT_ERROR(_Count >=16);

	// Check) 너무크면 안된다!!
	CGDASSERT_ERROR(max_size() <=CONTAINER_MAX);


	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) capacity가 이미 _Count보다 크면 그냥 되돌린다.
	CGD_RETURN_IF(_Count<=capacity(),);


	//-----------------------------------------------------------------
	// 1. 크기와 Mask를 설정한다.
	//-----------------------------------------------------------------
	// 1) Mask를 구한다.
	unsigned	tMask	 = 0;

	while(_Count)
	{
		_Count	>>= 1;
		tMask	 = (tMask<<1) | 1;
	}


	//-----------------------------------------------------------------
	// 2. 새로운 array를 할당받는다.
	//-----------------------------------------------------------------
	// 1) Array를 설정한다.
	TDATA*	tempArray	 = m_allocVal.allocate(tMask+1); 

	// Check) tempArray이 0이어서는 안된다.
	CGDASSERT_ERROR(tempArray!=0);


	//-----------------------------------------------------------------
	// 3. 기존 array를 할당해제한다.
	//-----------------------------------------------------------------
	size_type	preSize	 = size();

	// 1) size가 0이면 이전 값을 복사할 필요는 없다.
	if(preSize != 0)
	{
		// Check) m_ptr가 0이어서는 안된다.
		CGDASSERT_ERROR(m_ptr!=0);

		if(m_posHead<m_posTail)
		{
			// - 메모리를 복사한다.
			memcpy(tempArray, m_ptr, sizeof(TDATA)*(m_posTail-m_posHead));
		}
		else
		{
			// 이 경우는 Item들이 연결되어 있지 않고 반대쪽으로 돌아 있는
			// 경우이다. 이럴 땐 어쩔수 엄따. 두번 복사하는 수 밖에...

			// - 앞부분 복사.(posHead~END)
			memcpy(tempArray, m_ptr+m_posHead, sizeof(TDATA)*(m_posTail-m_posHead));

			// - 뒷부분 복사.(HEAD~posTail)
			memcpy(tempArray+m_posHead, m_ptr, sizeof(TDATA)*(m_posTail));
		}

		// - 기존의 data를 지운다.(Destroy는 호출하지 않는다.)
		m_allocVal.deallocate(m_ptr, capacity());
	}


	//-----------------------------------------------------------------
	// 4. 새로 설정한다.
	//-----------------------------------------------------------------
	// 1) 설정한다.
	m_ptr		 = tempArray;
	m_posHead	 = 0;
	m_posTail	 = preSize;
	m_mask		 = tMask;
	m_capacity	 = tMask+1;
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::resize(size_type _Newsize)
{
	// 1) 최대크기보다 크면 크기를 늘린다.
	if(_Newsize > capacity())
	{
		reserve(_Newsize);
	}

	// 2) 메모리에 Constructor를 호출해준다.
	iterator iter=end();

	CGD_TRY
	{
		iterator	newEnd(begin()+_Newsize);
		for(; iter != newEnd(); ++iter)
		{
			m_allocVal.construct(&(*iter));
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) Size를 새로 설정한다.
	m_posTail	 = m_posHead+_Newsize;
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::clear()
{
	//-----------------------------------------------------------------
	// 1. Destruct를 한다.
	//-----------------------------------------------------------------
	// 1) First와 Last의 Pos를 구한다.
	unsigned	posFirst	 = m_posHead & m_mask;
	unsigned	posLast		 = m_posTail & m_mask;

	// 2) Erase부분이 연속된 경우.
	if(posFirst>posLast)
	{
		TDATA*	ptr		 = m_ptr+posFirst;
		TDATA*	ptrEnd	 = m_ptr+posLast;
		for(; ptr<ptrEnd; ++ptr)
		{
			m_allocVal.destroy(ptr);
		}
	}
	// 3) Erase부분이 연속되지 않은 경우.
	else
	{
		// (2단계로 처리를 해줘야 한다.)
		// 1) First~m_posTail까지 Destructor를 불러준다.
		{
			TDATA*	ptr		 = m_ptr+posFirst;
			TDATA*	ptrEnd	 = m_ptr+(m_posTail & m_mask);
			for(; ptr<ptrEnd; ++ptr)
			{
				m_allocVal.destroy(ptr);
			}
		}
		// 2) m_posHead~Last까지 Destructor를 불러준다.
		{
			TDATA*	ptr		 = m_ptr+(m_posHead & m_mask);
			TDATA*	ptrEnd	 = m_ptr+posLast;
			for(; ptr<ptrEnd; ++ptr)
			{
				m_allocVal.destroy(ptr);
			}
		}
	}


	//-----------------------------------------------------------------
	// 2. Size를 0으로 한다.
	//-----------------------------------------------------------------
	// 1) Last를 First로 만들면 그게 0으로 만드는 것이다.
	m_posHead	 = m_posTail=0;
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::push_front(const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check) Buffer검사.
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// Check) 꽉차면 circular의 크기를 늘인다.(2배로)
	if(size()==capacity())
	{
		// - 현재 크기의 2배로 늘린다.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 1. Push한다.
	//-----------------------------------------------------------------
	// 1) Tail Pointer를 증가시킨다.
	--m_posHead;

	// 2) Construct를 호출한다.
	m_allocVal.construct(m_ptr+(m_posHead & m_mask), _Val);
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::push_front()
{
	//-----------------------------------------------------------------
	// Check) Buffer검사.
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// Check) 꽉차면 circular의 크기를 늘인다.(2배로)
	if(size()==capacity())
	{
		// - 현재 크기의 2배로 늘린다.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 1. Push한다.
	//-----------------------------------------------------------------
	// 1) Tail Pointer를 증가시킨다.
	--m_posHead;

	// 2) Construct를 호출한다.
	m_allocVal.construct(m_ptr+(m_posHead & m_mask));
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::pop_front()
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
	CGD_RETURN_IF(empty(),);
	#endif


	//-----------------------------------------------------------------
	// 1. Pop하기.
	//-----------------------------------------------------------------
	// 1) Destroy를 호출한다.
	m_allocVal.destroy(m_ptr+(m_posHead & m_mask));

	// 2) Tail Pointer를 증가시킨다.
	++m_posHead;
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::push_back(const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check) Buffer검사.
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// 1) 꽉차면 circular의 크기를 늘인다.(2배로)
	if(size()==capacity())
	{
		// - 현재 크기의 2배로 늘린다.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 1. Push한다.
	//-----------------------------------------------------------------
	// 1) Construct를 호출한다.
	m_allocVal.construct(m_ptr+(m_posTail & m_mask), _Val);

	// 2) Tail Pointer를 증가시킨다.
	++m_posTail;
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::push_back()
{
	//-----------------------------------------------------------------
	// Check) Buffer검사.
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// 1) 꽉차면 circular의 크기를 늘인다.(2배로)
	if(size()==capacity())
	{
		// - 현재 크기의 2배로 늘린다.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 1. Push한다.
	//-----------------------------------------------------------------
	// 1) Construct를 호출한다.
	m_allocVal.construct(m_ptr+(m_posTail & m_mask));

	// 2) Tail Pointer를 증가시킨다.
	++m_posTail;
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::pop_back()
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
	CGD_RETURN_IF(empty(),);
	#endif


	//-----------------------------------------------------------------
	// 1. Pop하기.
	//-----------------------------------------------------------------
	// 1) Tail Pointer를 증가시킨다.
	--m_posTail;

	// 2) Destroy를 호출한다.
	m_allocVal.destroy(m_ptr+(m_posTail & m_mask));
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::assign(size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// 주의) CGD::circular에는 max_size()검사는 존재하지 않습니다.
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	// 1. 남은 공간 검사.(삽입가능할 정도의 공간이 남아 있나?)
	//-----------------------------------------------------------------
	// 1) _size가 m_capacity보다 크거나 같으면 circular의 크기를 늘인다.
	if(remained()<_Count)
	{
		// - 현재 크기의 1.5배로 늘린다.
		reserve(m_capacity+_Count);
	}


	//-----------------------------------------------------------------
	// 2. 값을 넣는다.
	//-----------------------------------------------------------------
	// 1) First Iterator를 구한다.(Exception발생시 Roll back에도 쓰인다.)
	iterator iter	 = end();

	CGD_TRY
	{
		// 2) 값을 넣는다.
		iterator	newEnd(end()+_Count);
		for(; iter != newEnd(); ++iter)
		{
			m_allocVal.construct(&(*iter), _Val);
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 3) Last값을 바꾼다.
	m_posTail	+= _Count;
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::assign(const_iterator _First, const_iterator _Last)
{
	//-----------------------------------------------------------------
	// 주의) CGD::circular에는 max_size()검사는 존재하지 않습니다.
	//-----------------------------------------------------------------

	// Check) 
	CGDASSERT_ERROR(_Last.m_posNow > _First.m_posNow);

	// 1) Size를 구한다.
	size_type	count	 = _Last.m_posNow-_First.m_posNow;

	// Check) count가 0개이면 그냥 끝낸다.
	CGD_RETURN_IF(count == 0,);


	//-----------------------------------------------------------------
	// 1. 남은 공간 검사.(삽입가능할 정도의 공간이 남아 있나?)
	//-----------------------------------------------------------------
	// 1) _size가 m_capacity보다 크거나 같으면 circular의 크기를 늘인다.
	if(remained()<count)
	{
		// - 현재 크기의 늘린다.
		reserve(m_capacity+count);
	}


	//-----------------------------------------------------------------
	// 2. 값을 넣는다.
	//-----------------------------------------------------------------
	// 1) First Iterator를 구한다.(Exception발생시 Roll back에도 쓰인다.)
	iterator iter=end();

	CGD_TRY
	{
		// 2) 값을 넣는다.
		iterator	newEnd(end()+count);
		for(; iter != newEnd(); ++iter)
		{
			m_allocVal.construct(&(*iter));
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 3) Last값을 바꾼다.
	m_posTail	+= count;
}





template <typename TDATA, typename TALLOCATOR>
template<typename TITERATOR>
void circular<TDATA, TALLOCATOR>::insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::circular에는 max_size()검사는 존재하지 않습니다.

	// 1) _Where가 유효한 범위인지를 검사한다.(m_posHead>=m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Where.m_posNow>=m_posHead && _Where.m_posNow<=m_posTail));

	// 2) _Where가 유효한 범위인지를 검사한다.(m_posHead<m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Where.m_posNow<=m_posTail || _Where.m_posNow>=m_posHead));


	//-----------------------------------------------------------------
	// 1. 갯수를 샌다.
	//-----------------------------------------------------------------
	int	count	 = 0;
	for(TITERATOR iter=_First; iter!=_Last; ++iter)
	{
		++count;
	}


	//-----------------------------------------------------------------
	// 2. 남은 공간 검사.(삽입 가능할 정도의 공간이 남아 있나?)
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// 1) _size가 m_capacity보다 크거나 같으면 circular의 크기를 늘인다.
	if(remained()<count)
	{
		// - 현재 크기의 2배로 늘린다.
		reserve(m_capacity+count);
	}
	#else
	CGDASSERT_ERROR(remained()>=count);
	#endif


	//-----------------------------------------------------------------
	// 2. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	// 1) Where와 Tail구하기.
	unsigned	posWhere	 = _Where.m_posNow & m_mask;
	unsigned	posTail		 = m_posTail & m_mask;

	// 2) Where뒤에 Tail이 있을 경우.
	if(posWhere<posTail)
	{
		unsigned	remainTail	 = m_capacity-posTail;
		unsigned	tempSize	 = m_capacity-posWhere;

		// - Tail뒷쪽 공간이 count보다 클 경우(한번의 복사로 끝난다.)
		if(remainTail >= count)
		{
			memmove((void*)(m_ptr+posWhere+count), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
		}
		// - 뒷쪽 공간이 완전히 넘어갔을 경우...
		else if(tempSize <= count)
		{
			memmove((void*)(m_ptr+(count -tempSize)), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
		}
		// - Tail의 뒷쪽 공간이 count보다 작아서 두번 나눠서 복사해야 한다.
		else
		{
			memcpy((void*)(m_ptr), (void*)(m_ptr+(m_capacity- count)), (count -remainTail)*sizeof(TDATA));
			memmove((void*)(m_ptr+(posWhere+ count)), (void*)(m_ptr+(tempSize- count)), (count -remainTail)*sizeof(TDATA));
		}
	}
	// 3) 두번의 복사가 필요.
	else if(posWhere>posTail)
	{
		// - Head부분 밀기..
		memmove ((void*)(m_ptr+ count), (void*)m_ptr, (posTail)*sizeof(TDATA));

		unsigned	tempSize	 = m_capacity-posWhere;

		// - 한번의 복사로 끝난다.
		if(tempSize <= count)
		{
			memmove ((void*)(m_ptr+(count -tempSize)), (void*)(m_ptr+posWhere), tempSize*sizeof(TDATA));
		}
		// - 다시 두번으로 나눠서 복사해야 한다.
		else
		{
			// - Tail부분 앞쪽으로 복사하기.
			memcpy ((void*)m_ptr, (void*)(m_ptr+(m_capacity- count)), (tempSize- count)*sizeof(TDATA));

			// - Tail부분 밀어 복사하기..
			memmove ((void*)(m_ptr+(posWhere+ count)), (void*)(m_ptr+posWhere), (count +posTail-m_capacity)*sizeof(TDATA));
		}
	}


	//-----------------------------------------------------------------
	// 2. Insert한다.
	//-----------------------------------------------------------------
	#ifndef _CGD_NO_EXCEPTION_GUARANTEE
	// For Exception) 추후 Roll back을 위해 저장해 놓는다.
	iterator	iterRoll = _Where;
	#endif

	// 1) 비운 자리에 Construct를 호출해 값을 복사한다.
	CGD_TRY
	{
		// 2) 값을 넣는다.
		for(;_First!=_Last; ++_First, ++_Where)
		{
			// - Construct를 호출한다.
			m_allocVal.construct((TDATA*)&(*_Where), *_First);
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(; iterRoll!=_Where; ++iterRoll)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// - 땡겨준다.
		if(posWhere<posTail)
		{
			unsigned	remainTail	 = m_capacity-posTail;
			unsigned	tempSize	 = m_capacity-posWhere;

			// - Tail뒷쪽 공간이 count보다 클 경우(한번의 복사로 끝난다.)
			if(remainTail >= count)
			{
				memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+ count), (posTail-posWhere)*sizeof(TDATA));
			}
			// - 뒷쪽 공간이 완전히 넘어갔을 경우...
			else if(tempSize <= count)
			{
				memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+(count -tempSize)), (posTail-posWhere)*sizeof(TDATA));
			}
			// - Tail의 뒷쪽 공간이 count보다 작아서 두번 나눠서 복사해야 한다.
			else
			{
				memcpy((void*)(m_ptr+(tempSize- count)), (void*)(m_ptr+(posWhere+ count)), (count -remainTail)*sizeof(TDATA));
				memcpy((void*)(m_ptr+(m_capacity- count)), (void*)(m_ptr), (count -remainTail)*sizeof(TDATA));
			}
		}
		// 3) 두번의 복사가 필요.
		else if(posWhere>posTail)
		{
			unsigned	tempSize	 = m_capacity-posWhere;

			// - 한번의 복사로 끝난다.
			if(tempSize <= count)
			{
				memcpy ((void*)(m_ptr+posWhere), (void*)(m_ptr+(count -tempSize)), tempSize*sizeof(TDATA));
			}
			// - 다시 두번으로 나눠서 복사해야 한다.
			else
			{
				// - Tail부분 밀어 복사하기..
				memcpy ((void*)(m_ptr+posWhere), (void*)(m_ptr+(posWhere+ count)), (count +posTail-m_capacity)*sizeof(TDATA));

				// - Tail부분 앞쪽으로 복사하기.
				memcpy ((void*)(m_ptr+(m_capacity- count)), (void*)m_ptr, (tempSize- count)*sizeof(TDATA));
			}

			// - Head부분 밀기..
			memcpy ((void*)m_ptr, (void*)(m_ptr+ count), (posTail)*sizeof(TDATA));
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) _PtrLast를 증가시킨다.
	m_posTail	+= count;
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::insert(const_iterator _Where, size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::circular에는 max_size()검사는 존재하지 않습니다.

	// 1) _Where가 유효한 범위인지를 검사한다.(m_posHead>=m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Where.m_posNow>=m_posHead && _Where.m_posNow<=m_posTail));

	// 2) _Where가 유효한 범위인지를 검사한다.(m_posHead<m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Where.m_posNow<=m_posTail || _Where.m_posNow>=m_posHead));


	//-----------------------------------------------------------------
	// 1. 남은 공간 검사.(삽입 가능할 정도의 공간이 남아 있나?)
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// 1) _size가 m_capacity보다 크거나 같으면 circular의 크기를 늘인다.
	if(remained()<_Count)
	{
		// - 현재 크기의 2배로 늘린다.
		reserve(m_capacity+_Count);
	}
	#else
	CGDASSERT_ERROR(remained()>=_Count);
	#endif



	//-----------------------------------------------------------------
	// 2. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	// 1) Where와 Tail구하기.
	unsigned	posWhere	 = _Where.m_posNow & m_mask;
	unsigned	posTail		 = m_posTail & m_mask;

	// 2) Where뒤에 Tail이 있을 경우.
	if(posWhere<posTail)
	{
		unsigned	remainTail	 = m_capacity-posTail;
		unsigned	tempSize	 = m_capacity-posWhere;

		// - Tail뒷쪽 공간이 _Count보다 클 경우(한번의 복사로 끝난다.)
		if(remainTail >= _Count)
		{
			memmove((void*)(m_ptr+posWhere+_Count), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
		}
		// - 뒷쪽 공간이 완전히 넘어갔을 경우...
		else if(tempSize <=_Count)
		{
			memmove((void*)(m_ptr+(_Count-tempSize)), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
		}
		// - Tail의 뒷쪽 공간이 _Count보다 작아서 두번 나눠서 복사해야 한다.
		else
		{
			memcpy((void*)(m_ptr), (void*)(m_ptr+(m_capacity-_Count)), (_Count-remainTail)*sizeof(TDATA));
			memmove((void*)(m_ptr+(posWhere+_Count)), (void*)(m_ptr+(tempSize-_Count)), (_Count-remainTail)*sizeof(TDATA));
		}
	}
	// 3) 두번의 복사가 필요.
	else if(posWhere>posTail)
	{
		// - Head부분 밀기..
		memmove ((void*)(m_ptr+_Count), (void*)m_ptr, (posTail)*sizeof(TDATA));

		unsigned	tempSize	 = m_capacity-posWhere;

		// - 한번의 복사로 끝난다.
		if(tempSize <= _Count)
		{
			memmove ((void*)(m_ptr+(_Count-tempSize)), (void*)(m_ptr+posWhere), tempSize*sizeof(TDATA));
		}
		// - 다시 두번으로 나눠서 복사해야 한다.
		else
		{
			// - Tail부분 앞쪽으로 복사하기.
			memcpy ((void*)m_ptr, (void*)(m_ptr+(m_capacity-_Count)), (tempSize-_Count)*sizeof(TDATA));

			// - Tail부분 밀어 복사하기..
			memmove ((void*)(m_ptr+(posWhere+_Count)), (void*)(m_ptr+posWhere), (_Count+posTail-m_capacity)*sizeof(TDATA));
		}
	}


	//-----------------------------------------------------------------
	// 2. Insert한다.
	//-----------------------------------------------------------------
	#ifndef _CGD_NO_EXCEPTION_GUARANTEE
	// For Exception) 추후 Roll back을 위해 저장해 놓는다.
	iterator	iterRoll = _Where;
	#endif

	// 1) 비운 자리에 Construct를 호출해 값을 복사한다.
	CGD_TRY
	{
		// 2) 값을 넣는다.
		iterator	iterEnd	 = _Where+_Count;
		for(;_Where!= iterEnd; ++_Where)
		{
			// - Construct를 호출한다.
			m_allocVal.construct((TDATA*)&(*_Where), _Val);
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(; iterRoll!=_Where; ++iterRoll)
		{
			// - Destroy를 호출한다.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// - 땡겨준다.
		if(posWhere<posTail)
		{
			unsigned	remainTail	 = m_capacity-posTail;
			unsigned	tempSize	 = m_capacity-posWhere;

			// - Tail뒷쪽 공간이 _Count보다 클 경우(한번의 복사로 끝난다.)
			if(remainTail >= _Count)
			{
				memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+_Count), (posTail-posWhere)*sizeof(TDATA));
			}
			// - 뒷쪽 공간이 완전히 넘어갔을 경우...
			else if(tempSize <=_Count)
			{
				memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+(_Count-tempSize)), (posTail-posWhere)*sizeof(TDATA));
			}
			// - Tail의 뒷쪽 공간이 _Count보다 작아서 두번 나눠서 복사해야 한다.
			else
			{
				memcpy((void*)(m_ptr+(tempSize-_Count)), (void*)(m_ptr+(posWhere+_Count)), (_Count-remainTail)*sizeof(TDATA));
				memcpy((void*)(m_ptr+(m_capacity-_Count)), (void*)(m_ptr), (_Count-remainTail)*sizeof(TDATA));
			}
		}
		// 3) 두번의 복사가 필요.
		else if(posWhere>posTail)
		{
			unsigned	tempSize	 = m_capacity-posWhere;

			// - 한번의 복사로 끝난다.
			if(tempSize <= _Count)
			{
				memcpy ((void*)(m_ptr+posWhere), (void*)(m_ptr+(_Count-tempSize)), tempSize*sizeof(TDATA));
			}
			// - 다시 두번으로 나눠서 복사해야 한다.
			else
			{
				// - Tail부분 밀어 복사하기..
				memcpy ((void*)(m_ptr+posWhere), (void*)(m_ptr+(posWhere+_Count)), (_Count+posTail-m_capacity)*sizeof(TDATA));

				// - Tail부분 앞쪽으로 복사하기.
				memcpy ((void*)(m_ptr+(m_capacity-_Count)), (void*)m_ptr, (tempSize-_Count)*sizeof(TDATA));
			}

			// - Head부분 밀기..
			memcpy ((void*)m_ptr, (void*)(m_ptr+_Count), (posTail)*sizeof(TDATA));
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) _PtrLast를 증가시킨다.
	m_posTail	+= _Count;
}

template <typename TDATA, typename TALLOCATOR>
typename circular<TDATA, TALLOCATOR>::iterator circular<TDATA, TALLOCATOR>::insert(const_iterator _Where, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::circular에는 max_size()검사는 존재하지 않습니다.

	// 1) _Where가 유효한 범위인지를 검사한다.(m_posHead>=m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Where.m_posNow>=m_posHead && _Where.m_posNow<=m_posTail));

	// 2) _Where가 유효한 범위인지를 검사한다.(m_posHead<m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Where.m_posNow<=m_posTail || _Where.m_posNow>=m_posHead));


	//-----------------------------------------------------------------
	// 1. 남은 공간 검사.(삽입가능할 정도의 공간이 남아 있나?)
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// Check) 꽉차면 circular의 크기를 늘인다.(2배로)
	if(size()==capacity())
	{
		// - 현재 크기의 2배로 늘린다.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 2. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	// 1) Where와 Tail구하기.
	unsigned	posWhere	 = _Where.m_posNow & m_mask;
	unsigned	posTail		 = m_posTail & m_mask;

	// 2) 한번의 복사로 끝남.
	if(posWhere<posTail)
	{
		memmove((void*)(m_ptr+posWhere+1), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
	}
	// 3) 두번의 복사가 필요.
	else if(posWhere>posTail)
	{
		// - Head부분 밀기..(posTail이 0이 될수도 있다.)
		memmove ((void*)(m_ptr+1), (void*)m_ptr, (posTail)*sizeof(TDATA));

		// - 제일 마지막 부분을 제일 앞으로 옮기기.(assignment가 불려지지 않게 하기 위해 메모리 복사함.)
		memcpy((void*)m_ptr, (void*)(m_ptr+m_mask), sizeof(TDATA));	// m_mask가 capacity()-1과 같다.

		// - Tail부분 밀기.(이것도 0이 될수 있다.)
		memmove ((void*)(m_ptr+posWhere+1), (void*)(m_ptr+posWhere), (m_mask-posWhere)*sizeof(TDATA));
	}


	//-----------------------------------------------------------------
	// 3. Insert한다.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) 비운 자리에 Construct를 호출해 값을 복사한다.
		m_allocVal.construct((TDATA*)(m_ptr+posWhere), _Val);
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - 다시 모조리 땡긴다.(민것과 반대 방향과 순서로 땡겨준다.)
		if(posWhere<posTail)
		{
			memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+1), (posTail-posWhere)*sizeof(TDATA));
		}
		else if(posWhere>posTail)
		{
			// - Tail부분 땡기기.(이것도 0이 될수 있다.)
			memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+1), (m_mask-posWhere)*sizeof(TDATA));

			// - 앞부분에 복사했던 것 다시 뒷부분으로 옮겨붙이기.(assignment가 불려지지 않게 하기 위해 메모리 복사함.)
			memcpy((void*)(m_ptr+m_mask), (void*)m_ptr, sizeof(TDATA));	// m_mask가 capacity()-1과 같다.

			// - Head부분 땡기기..(posTail이 0이 될수도 있다.)
			memmove ((void*)m_ptr, (void*)(m_ptr+1), (posTail)*sizeof(TDATA));
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) _PtrLast를 증가시킨다.
	++m_posTail;

	// Return) 되돌린다.(Insert한 위치의 Iterator를 돌려준다.)
	return	iterator((TDATA*)m_ptr, _Where.m_posNow, _Where.m_mask);
}


template <typename TDATA, typename TALLOCATOR>
typename circular<TDATA, TALLOCATOR>::iterator circular<TDATA, TALLOCATOR>::erase(const_iterator _Where)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::circular에는 max_size()검사는 존재하지 않습니다.

	// 1) _Where가 유효한 범위인지를 검사한다.(m_posHead>=m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Where.m_posNow>=m_posHead && _Where.m_posNow<m_posTail));

	// 2) _Where가 유효한 범위인지를 검사한다.(m_posHead<m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Where.m_posNow<m_posTail || _Where.m_posNow>=m_posHead));

	// 3) 비어 있으면 삭제할수 없다.
	CGDASSERT_ERROR(!empty());


	//-----------------------------------------------------------------
	// 2. 지운다~
	//-----------------------------------------------------------------
	unsigned	posWhere	 = _Where.m_posNow & m_mask;

	// 1) 해당위치에 Destroy를 호출해 준다.
	m_allocVal.destroy((TDATA*)(m_ptr+posWhere));


	//-----------------------------------------------------------------
	// 3. 복사해서 땡겨오기.
	//-----------------------------------------------------------------
	// 1) Where와 Tail구하기.
	unsigned	posTail		 = m_posTail & m_mask;

	// 2) 한번땡기고 끝냄.
	if(posWhere<=posTail)
	{
		memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+1), (posTail-posWhere-1)*sizeof(TDATA));
	}
	// 3) 두번의 복사가 필요.
	else
	{
		// - Tail부분 땡기기.
		memcpy((void*)(m_ptr+posTail), (void*)(m_ptr+posTail+1), (m_mask-posWhere)*sizeof(TDATA));

		// - 제일 앞부분을 뒷부붙에 옮긴다.(assignment가 불려지지 않게 하기 위해 메모리 복사함.)
		memcpy((void*)(m_ptr+m_mask), (void*)m_ptr, sizeof(TDATA));	// m_mask가 capacity()-1과 같다.

		// - Head부분 땡기기.
		memcpy((void*)m_ptr, (void*)(m_ptr+1), (posTail-1)*sizeof(TDATA));
	}

	// 4) Last를 줄인다.
	--m_posTail;


	// Return)
	return	iterator();
}

template <typename TDATA, typename TALLOCATOR>
typename circular<TDATA, TALLOCATOR>::iterator circular<TDATA, TALLOCATOR>::erase(const_iterator _First, const_iterator _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 주의) CGD::circular에는 max_size()검사는 존재하지 않습니다.

	// 1) _Where가 유효한 범위인지를 검사한다.(m_posHead>=m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_First.m_posNow>=m_posHead && _First.m_posNow<=m_posTail));

	// 2) _Where가 유효한 범위인지를 검사한다.(m_posHead<m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_First.m_posNow<=m_posTail || _First.m_posNow>=m_posHead));

	// 3) _Where가 유효한 범위인지를 검사한다.(m_posHead>=m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Last.m_posNow>=m_posHead && _Last.m_posNow<=m_posTail));

	// 4) _Where가 유효한 범위인지를 검사한다.(m_posHead<m_posTail인 경우)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Last.m_posNow<=m_posTail || _Last.m_posNow>=m_posHead));

	// 5) 비어 있으면 삭제할수 없다.
	CGDASSERT_ERROR(!empty());

	// Check) First와 Last가 같다면 그냥 되돌림.
	CGD_RETURN_IF(_First.m_posNow == _Last.m_posNow,);


	//-----------------------------------------------------------------
	// 1. 준비~
	//-----------------------------------------------------------------
	// 1) First와 Last의 Pos를 구한다.
	unsigned	posFirst	 = _First.m_posNow & m_mask;
	unsigned	posLast		 = _Last.m_posNow & m_mask;


	//-----------------------------------------------------------------
	// 2. Erase부분이 연속된 경우.
	//-----------------------------------------------------------------
	if(posFirst>posLast)
	{
		//----------------------
		// X. Destroy해주기
		//----------------------
		TDATA*	ptr		 = m_ptr+posFirst;
		TDATA*	ptrEnd	 = m_ptr+posLast;
		for(; ptr<ptrEnd; ++ptr)
		{
			m_allocVal.destroy(ptr);
		}


		//-----------------------------------------------------------------
		// X. 땡겨 복사하기...
		//-----------------------------------------------------------------
		unsigned	posTail		 = m_posTail & m_mask;

		// case A) Tail이 Last보다 큰경우(그냥 한번의 복사로 끝난다.)
		if(posTail>=posLast)
		{
			memcpy((void*)(m_ptr+posFirst), (void*)(m_ptr+posLast), (posTail-posLast)*sizeof(TDATA));
		}
		// case B) Tail이 Last보다 작은 경우.(두번으로 나뉘어 있다는 뜻이다.)
		else
		{
			unsigned	remainedTail	 = m_capacity-posLast;

			// 1) 일단 Tail부분가지 복사하고...
			memcpy((void*)(m_ptr+posFirst), (void*)(m_ptr+posLast), remainedTail*sizeof(TDATA));

			unsigned	remainedTransfer	 = posLast-posFirst;

			// CaseA) 뒷부분을 한번에 복사할수 있다.
			if(remained>=posTail)
			{
				memcpy((void*)(m_ptr+posFirst), (void*)m_ptr, posTail*sizeof(TDATA));
			}
			// CaseB) 다시 또 두부분으로 나뉘서 복사해야한다.
			else
			{
				memcpy((void*)(m_ptr+posFirst), (void*)m_ptr, remainedTransfer*sizeof(TDATA));
				memcpy((void*)(m_ptr), (void*)(m_ptr+remainedTransfer), (posTail-remainedTransfer)*sizeof(TDATA));
			}
		}

		// 마무리~
		m_posTail	-= (_Last.m_posNow-_First.m_posNow);
	}
	//-----------------------------------------------------------------
	// 3. Erase부분이 연속되지 않은 경우.
	//-----------------------------------------------------------------
	else
	{
		//----------------------
		// X. Destroy해주기
		//----------------------
		// (2단계로 처리를 해줘야 한다.)
		// 1) First~m_posTail까지 Destructor를 불러준다.
		{
			TDATA*	ptr		 = m_ptr+posFirst;
			TDATA*	ptrEnd	 = m_ptr+(m_posTail & m_mask);
			for(; ptr<ptrEnd; ++ptr)
			{
				m_allocVal.destroy(ptr);
			}
		}
		// 2) m_posHead~Last까지 Destructor를 불러준다.
		{
			TDATA*	ptr		 = m_ptr+(m_posHead & m_mask);
			TDATA*	ptrEnd	 = m_ptr+posLast;
			for(; ptr<ptrEnd; ++ptr)
			{
				m_allocVal.destroy(ptr);
			}
		}


		//----------------------
		// X. 땡겨 복사하기...
		//----------------------
		unsigned	posTail		 = m_posTail & m_mask;

		// 1) Total Transfer Size.
		//    (여기서는 m_posTail과 dwLast으로 구할필요 없다. 어차피 Tail과 Last는 연결되어 있으므로...)
		unsigned	totalTransfer	 = posTail-posLast;

		// 2) Tail부분의 길이를 구한다.(전체길이-posFirst가 되겠다.)
		unsigned	remaineTail = m_capacity-posFirst;

		// Case A) 한번의 복사로 끝난다.
		if(remaineTail>=totalTransfer)
		{
			memcpy((void*)(m_ptr+posFirst), (void*)(m_ptr+posLast), (posTail-posLast)*sizeof(TDATA));
		}
		//  Case B) Tail부분을 복사하고 앞부분은 땡긴다.
		else
		{
			memcpy((void*)(m_ptr+posFirst), (void*)(m_ptr+posLast), remaineTail*sizeof(TDATA));
			memcpy((void*)m_ptr, (void*)(m_ptr+remaineTail), (totalTransfer-remaineTail)*sizeof(TDATA));
		}

		// 마무리~
		m_posTail	-= totalTransfer;
	}
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::swap(_mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) 같은 container면 그냥 return한다.
	//-----------------------------------------------------------------
	// 1) 같은 거라면 그냥 되돌린다.
	CGD_RETURN_IF(this == &_Right,);


	//-----------------------------------------------------------------
	// CaseA) Allocator가 같으면...
	//-----------------------------------------------------------------
	if (m_allocVal == _Right.m_allocVal)
	{
		// 바꾼다~
		CGD_SWAP(m_ptr,		_Right.m_ptr);

		CGD_SWAP(m_posHead,	_Right.m_posHead);
		CGD_SWAP(m_posTail,	_Right.m_posTail);

		CGD_SWAP(m_mask,	_Right.m_mask);
		CGD_SWAP(m_capacity,_Right.m_capacity);

		CGD_SWAP(m_allocVal, _Right.m_allocVal);

	}
	//-----------------------------------------------------------------
	// CaseB) Allocator가 다르면...
	//-----------------------------------------------------------------
	else
	{
		// 통채로 바꾼다.(앗싸리...통체로 바꿈.)
		CGD_SWAP(*this, _Right);
	}
}





}


