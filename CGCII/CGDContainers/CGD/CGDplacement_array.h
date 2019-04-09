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
//-----------------------------------------------------------------------------
//
// CGD::placement_vector<T>
//
// 1. CGD::placement_vector란!
//     CGD::placement_vector는 기본적인 형태는 모두 vector와 동일하지만 이미 할당된
//    메모리에 vector를 구현하는 것을 의미한다.
//
//    - allocator가 존재하지 않는다.
//    - reserve 등을 통해 조절할 수 없고 단지 선언 시 설정해야 한다.
//    - 따라서 자동으로 크기가 커지는(auto expend)도 없다.
//    - 전반적인 성능은 vector보다 훨씬 우수하며 지역변수로 사용해도 부하가 거의
//      없다. (동적할당을 하지 않기 때문)
//    - 동작은 vector와 동일하다.
//
//
// 2. CGD::placement_vector의 표준 준수 사항
//    1) (o) Common Container Standard 
//    2) (o) Reversible Standard 
//    3) (o) Sequence Container Standard 
//    4) (x) Assosiative Container Standard 
//
//    (*) placement_vector는 list와 다르게 random access operator를 제공해 준다.
//
//
// 3. exception-safe level.
//    1) Strong guarantee.
//       - 아무런 Option이 주어지지 않으면 기본적으로 strong exception safe
//         guarantee를 제공해준다.
//      -  걱 Operation을 수행할 때 exception safe확보를 위한 if문장들이 추가
//         된다.
//
//    2) No guarantee (With _CGD_NO_EXCEPTION_GUARANTEE flag)
//       - flag를 설정하면 No Execption safe guarantee를 제공해줄수 있다.
//       - 추가적으로 exception처리를 하지 않거나 혹은 안정성보다 빠른 속도를
//         원할 경우 Exception Guarantee를 제거할 경우 안전을 위한 추가적인
//         if문들이 제거되어 조금 더 빠른 code를 제공해 줄수 있다.
//       - 이를 통해 inline처리되는 확률이 늘어나는 것이 속도향상의 핵심이다.
//
//
// 4. Option) CGD::placement_vector의 주요 옵션.
// 
//	  1) 없음...
//
// *주의: 이런 주석문들은 comiler에게 쓸모없는 부하를 줄수 있습니다. 따라서...
//        컴파일 시간이 느리면 이런 주석들을 모조리 지워주시기 바랍니다.
//
//
//-----------------------------------------------------------------------------
#include "CGDDefinitions.h"
#include <stdexcept>

namespace CGD
{

template <typename TDATA>
class placement_vector
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
	typedef	placement_vector<TDATA>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA, int TOTHER_SIZE>
	struct rebind
	{
		typedef placement_vector<TOTHER_DATA> other;
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
	placement_vector(void* p_ptr, int _maxsize, int _size=0);
	placement_vector(const _mytype& _Right);
	~placement_vector();

public:
	void					placement(void* p_ptr, int _maxsize, int _size=0);
	void					unplacement();

public:
	// Common Standard 1) Status Function
	size_type				size() const								{	return m_ptrLast-m_ptrFirst;}
	size_type				max_size() const							{	return m_iMaxSize;}
	bool					empty() const								{	return (size()==0);}

	// Common Standard 2) 
	iterator				begin()										{	return iterator(m_ptrFirst);}
	const_iterator			begin() const								{	return const_iterator(m_ptrFirst);}
	iterator				end()										{	return iterator(m_ptrLast);}
	const_iterator			end() const									{	return const_iterator(m_ptrLast);}
	reverse_iterator		rbegin()									{	return reverse_iterator(iterator(m_ptrLast-1));}
	const_reverse_iterator	rbegin() const								{	return const_reverse_iterator(const_iterator(m_ptrLast-1));}
	reverse_iterator		rend()										{	return reverse_iterator(iterator((m_ptrFirst)-1));}
	const_reverse_iterator	rend() const								{	return const_reverse_iterator(const_iterator((m_ptrFirst)-1));}

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
	placement_vector();
	placement_vector(size_type _Count);
	placement_vector(size_type _Count, const TDATA& _Val);
	template<typename TITERATOR>
	placement_vector(TITERATOR _First, TITERATOR _Last);

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
// placement_vector Member)
//
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const							{	return m_sizeMax;}
	size_type				remained() const							{	return m_sizeMax-size();}

	// 2) Data
	reference				front()		 								{	return *m_ptrFirst;}
	const_reference			front() const 								{	return *m_ptrFirst;}

	reference				back()										{	return *(m_ptrLast-1);}
	const_reference			back() const								{	return *(m_ptrLast-1);}

	reference				at(size_type _Pos);
	const_reference			at(size_type _Pos) const;

	reference				operator [] (size_type _Pos);
	const_reference			operator [] (size_type _Pos) const;

	// 3) push/pop
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
	// 1) placement_vector
		TDATA*				m_ptrFirst;
		TDATA*				m_ptrLast;
		int					m_sizeMax;


// ****************************************************************************
// Iterator) 
// ----------------------------------------------------------------------------
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	placement_vector<TDATA>;

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
		pointer				operator->()									{	return &**this;}

		// 3) 반복
		const_reference		operator*() const							{	return *m_ptrLast;}
		const_iterator&		operator++()								{	++m_ptrLast; return *this;}
		const_iterator		operator++(int)								{	return const_iterator(m_ptrLast++);}
		const_iterator&		operator--()									{	--m_ptrLast; return *this;}
		const_iterator		operator--(int)								{	return const_iterator(m_ptrLast--);}
		const_iterator		operator+(difference_type _Right) const		{	return const_iterator(m_ptrLast+_Right);}
		void				operator+=(difference_type _Right)			{	m_posNow+=_Right;}
		const_iterator		operator-(difference_type _Right) const		{	return const_iterator(m_ptrLast-_Right);}
		void				operator-=(difference_type _Right)			{	m_posNow-=_Right;}
		size_type			operator-(const const_iterator& _Right) const {	return m_ptrLast-_Right.m_ptrLast;}
		size_type			operator-(const iterator& _Right) const		{	return m_ptrLast-_Right.m_ptrLast;}

		// 4) 비교
		bool				operator==(const const_iterator& _Right) const {	return m_ptrLast==_Right.m_ptrLast;}
		bool				operator!=(const const_iterator& _Right) const {	return m_ptrLast!=_Right.m_ptrLast;}

		bool				operator>(const const_iterator&  _Right) const {	return m_ptrLast>_Right.m_ptrLast;}
		bool				operator>=(const const_iterator&  _Right)	{	return m_ptrLast>=_Right.m_ptrLast;}
		bool				operator<(const const_iterator&  _Right) const {	return m_ptrLast<_Right.m_ptrLast;}
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
		friend	placement_vector<TDATA>;

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
		iterator&			operator--()									{	--m_ptrLast; return *this;}
		iterator			operator--(int)								{	return iterator(m_ptrLast--);}
		iterator			operator+(difference_type _Right) const		{	return iterator(m_ptrLast+_Right);}
		void				operator+=(difference_type _Right)			{	m_posNow+=_Right;}
		iterator			operator-(difference_type _Right) const		{	return iterator(m_ptrLast-_Right);}
		void				operator-=(difference_type _Right)			{	m_posNow-=_Right;}
		size_type			operator-(const const_iterator& _Right) const {	return m_ptrLast-_Right.m_ptrLast;}
		size_type			operator-(const iterator& _Right) const		{	return m_ptrLast-_Right.m_ptrLast;}

		// 4) 비교
		bool				operator==(const iterator& _Right) const	{	return m_ptrLast==_Right.m_ptrLast;}
		bool				operator!=(const iterator& _Right) const	{	return m_ptrLast!=_Right.m_ptrLast;}

		bool				operator==(const const_iterator& _Right) const {	return m_ptrLast==_Right.m_ptrLast;}
		bool				operator!=(const const_iterator& _Right) const {	return m_ptrLast!=_Right.m_ptrLast;}
		
		bool				operator>(const const_iterator&  _Right) const {	return m_ptrLast>_Right.m_ptrLast;}
		bool				operator>=(const const_iterator&  _Right)	{	return m_ptrLast>=_Right.m_ptrLast;}
		bool				operator<(const const_iterator&  _Right) const {	return m_ptrLast<_Right.m_ptrLast;}
		bool				operator<=(const const_iterator&  _Right)	{	return m_ptrLast<=_Right.m_ptrLast;}

		bool				operator>(const iterator&  _Right) const	{	return m_ptrLast>_Right.m_ptrLast;}
		bool				operator>=(const iterator&  _Right)			{	return m_ptrLast>=_Right.m_ptrLast;}
		bool				operator<(const iterator&  _Right) const	{	return m_ptrLast<_Right.m_ptrLast;}
		bool				operator<=(const iterator&  _Right)			{	return m_ptrLast<=_Right.m_ptrLast;}

	private:
		pointer				m_ptrLast;
	};
};




//-----------------------------------------------------------------
// Constructor/Destructor 함수들.
//
// - 다양한 종류의 constructor와 destructor함수들이다.
//-----------------------------------------------------------------
template <typename TDATA>
placement_vector<TDATA>::placement_vector() : m_ptrFirst(nullptr)
{
}

template <typename TDATA>
placement_vector<TDATA>::placement_vector(void* p_ptr, int _maxsize, int _size) : m_ptrFirst(p_ptr), m_ptrLast(p_ptr+_size), m_sizeMax(_maxsize)
{
}

template <typename TDATA>
placement_vector<TDATA>::placement_vector(const _mytype& _Right)
{
	// Check) vector형의 자료여야지만 된다.
	CGDASSERT_ERROR(++_Right.begin()==_Right[1]);

	m_ptrFirst	 = _Right.front();
	m_ptrLast	 = _Right.back()+1;
	m_sizeMax	 = _Right.max_size();
}

template <typename TDATA>
template<typename TITERATOR>
placement_vector<TDATA>::placement_vector(TITERATOR _First, TITERATOR _Last) : m_ptrFirst(nullptr)
{
	m_ptrFirst	 = &*_First;
	m_ptrLast	 = &*_Last;
	m_sizeMax	 = _Last-_First;

	// Check) vector형의 자료여야지만 된다.
	CGDASSERT_ERROR((m_ptrFirst+1)==*(_First+1));
}

template <typename TDATA>
placement_vector<TDATA>::~placement_vector()
{
	// 1) 모두 지운다.
	clear();
}


template <typename TDATA>
void placement_vector<TDATA>::placement(void* p_ptr, int _maxsize, int _size)
{
	m_ptrFirst	 = p_ptr;
	m_ptrLast	 = p_ptr+_size;
	m_sizeMax	 = _maxsize;
}

template <typename TDATA>
void placement_vector<TDATA>::unplacement()
{
	m_ptrFirst	 = nullptr;
	m_ptrLast	 = nullptr;
	m_sizeMax	 = 0;
}


//-----------------------------------------------------------------
// Operator overriding 함수들.
//

//-----------------------------------------------------------------
template <typename TDATA>
typename placement_vector<TDATA>::_mytype& placement_vector<TDATA>::operator=(const _mytype& _Right)
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
template <typename TDATA>
bool placement_vector<TDATA>::operator==(const _mytype& _Right) const
{
	// Check) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator!=(const _mytype& _Right) const	
{
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator<(const _mytype& _Right) const	
{
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator>(const _mytype& _Right) const	
{
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator<=(const _mytype& _Right) const	
{
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator>=(const _mytype& _Right) const	
{
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
TDATA& placement_vector<TDATA>::at(size_type _Pos)
{
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: 범위를 넘어선 참조입니다.("__FUNCTION__")\n"))

	// 1) 값을 읽어서 되돌린다.
	return m_ptrFirst[_Pos];
}

template <typename TDATA>
const TDATA& placement_vector<TDATA>::at(size_type _Pos) const
{
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: 범위를 넘어선 참조입니다.("__FUNCTION__")\n"))

	// 1) 값을 읽어서 되돌린다.
	return m_ptrFirst[_Pos];
}


template <typename TDATA>
TDATA& placement_vector<TDATA>::operator [] (size_type _Pos)
{
	return	at(_Pos);
}

template <typename TDATA>
const TDATA& placement_vector<TDATA>::operator [] (size_type _Pos) const
{
	return	at(_Pos);
}


template <typename TDATA>
void placement_vector<TDATA>::resize(size_type _Newsize)
{
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) max_size()보다 작은 크기여야지만 된다.
	CGD_THROW_IF(_Newsize>max_size(), std::length_error("CGD Exception: 잘못된 크기입니다.("__FUNCTION__")\n"));

	// 1) 
	auto	iter=end();
	auto	newEnd(begin()+_Newsize);

	CGD_TRY
	{
		// 2) 늘어난 부분까지 Reset을 한다.
		for(; iter < newEnd(); ++iter)
		{
			new (&(*iter)) TDATA();
		}

		// 3) 줄어들면???(수정요)
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy를 호출한다.
			_Alval.destroy(&(*iterRoll), 1);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) Size를 새로 설정한다.
	m_ptrLast	 = newEnd;
}


template <typename TDATA>
void placement_vector<TDATA>::clear()
{
	// Check) m_ptrFirst가 nullptr이면 끝낸다.
	CGD_RETURN_IF(m_ptrFirst==nullptr,)


	//-----------------------------------------------------------------
	// 1. 지우기...
	//-----------------------------------------------------------------
	// 1) 모든 Item의 Destructor를 호출한다.
	for(iterator iter=begin(); iter != end(); ++iter)
	{
		(*iter).~TDATA();
	}

	// 2) Last를 First로 만들어 0을 만든다.
	m_ptrLast	 = m_ptrFirst;
}


template <typename TDATA>
void placement_vector<TDATA>::push_back(const TDATA& _Val)
{
	// Check) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct를 호출한다.
	new (m_ptrLast) TDATA(_Val);
	
	// 2) Last 포인터 증가시킴
	++m_ptrLast;
}

template <typename TDATA>
void placement_vector<TDATA>::push_back()
{
	// Check) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct를 호출한다.
	new (m_ptrLast) TDATA();
	
	// 2) Last 포인터 증가시킴
	++m_ptrLast;
}

template <typename TDATA>
void placement_vector<TDATA>::pop_back()
{
	//-----------------------------------------------------------------
	// Check) Empty검사.
	//-----------------------------------------------------------------
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty를 Check를 하지 않을 경우에 Debug 모드일때 Assert를 띄워준다.
	//   (Release Mode일 때는 아무일도 동작하지 않는다.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty를 Check를 할 경우 Empty를 Check하고 비어 있을 경우 아무동작하지 않고 그냥 끝낸다.
	CGD_RETURN_IF(empty(),);
	#endif


	//-----------------------------------------------------------------
	// 1. Pop한다.
	//-----------------------------------------------------------------
	// 1) 크기를 줄인다.
	--m_ptrLast;

	// 2) Destructor를 호출한다.
	m_ptrLast->~TDATA();
}

template <typename TDATA>
void placement_vector<TDATA>::assign(size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) 최대 갯수보다 크면 던진다!
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: 크기가 잘못되었습니다.("__FUNCTION__")\n"));


	//-----------------------------------------------------------------
	// 1. 값을 넣는다.
	//-----------------------------------------------------------------
	// 1) 집어넣을 First와 Last를 가리키는 Iterator
	TDATA*	first	 = m_ptrLast;

	// 2) End를 구한다.
	TDATA*	newEnd	 = m_ptrLast+_Count;

	CGD_TRY
	{
		// 3) 값을 넣는다.
		for(; first != newEnd; ++first)
		{
			new (first) TDATA(_Val);
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
	m_ptrLast	+= newEnd;
}

template <typename TDATA>
template <typename ITERATOR>
void placement_vector<TDATA>::assign(ITERATOR _First, ITERATOR _Last)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGD_THROW_IF(m_ptrFirst==nullptr, std::length_error("CGD Exception: placement되지 않았습니다.("__FUNCTION__")\n"))


	//-----------------------------------------------------------------
	// 1. 값을 넣는다.
	//-----------------------------------------------------------------
	// 1) 집어넣을 First와 Last를 가리키는 Iterator
	TDATA*	first	 = m_ptrLast;

	CGD_TRY
	{
		// 2) 값을 넣는다.
		for(; _First != _Last; ++_First, ++first)
		{
			// Check) Remained가 0이면 안됀다.
			CGD_THROW_IF(remained()!=0, std::length_error("CGD Exception: 잘못된 크기입니다.("__FUNCTION__")\n"));

			new (first) TDATA(*_First);
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
	m_ptrLast	+= newEnd;
}

template <typename TDATA>
template<typename TITERATOR>
void placement_vector<TDATA>::insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. 갯수를 구한다.
	//-----------------------------------------------------------------
	// 1) Insert Count를 얻는다.
	size_type	Insertcount	 = _Last-_First;

	// 2) 들어갈 공간이 존재하는지 검사한다.
	CGD_THROW_IF(remained()<Insertcount, std::length_error("CGD Exception: 공간이 부족합니다.("__FUNCTION__")\n"));


	//-----------------------------------------------------------------
	// 1. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	// 1) 값을 넣는다.(size도 자동 증가...)
	TDATA*		pSource	 = const_cast<TDATA*>(_Where.m_ptrLast);
	TDATA*		pDest	 = const_cast<TDATA*>(_Where.m_ptrLast+Insertcount);
	size_type	nCount	 = m_ptrLast-pSource;

	// 2) placement_vector를 한칸씩 뒤로 미룬다.
	memmove(pDest, pSource, sizeof(TDATA)*nCount);


	//-----------------------------------------------------------------
	// 2. Insert한다.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) 비운 자리에 Construct를 호출해 값을 복사한다.
		for(;_First!=_Last; ++_First, ++pSource)
		{
			// - Construct를 호출한다.
			new (pSource) TDATA(*_First);
		}
	}
	CGD_CATCH_ALL
	{
		// - 다시 땡기기 위해 주소와 갯수를 계산한다.
		TDATA* pBgn = const_cast<TDATA*>(_Where.m_ptrLast);

		// - 생성했던 것을 다시 다 Destroy한다.
		for(;pBgn<pSource; ++pBgn)
		{
			// - Destroy를 호출한다.
			pBgn->~TDATA();
		}

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy((void*)_Where.m_ptrLast, pDest, sizeof(TDATA)*nCount);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 3) size를 증가시킨다.
	m_ptrLast		+= Insertcount;
}



template <typename TDATA>
void placement_vector<TDATA>::insert(const_iterator _Where, size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);

	// 3) 들어갈 공간이 존재하는지 검사한다.
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: 공간이 부족합니다.("__FUNCTION__")\n"));


	//-----------------------------------------------------------------
	// 1. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	// 1) 값을 넣는다.(size도 자동 증가...)
	TDATA*		pSource	 = const_cast<TDATA*>(_Where.m_ptrLast);
	TDATA*		pDest	 = const_cast<TDATA*>(_Where.m_ptrLast+_Count);
	size_type	nCount	 = m_ptrLast-pSource;

	// 2) placement_vector를 한칸씩 뒤로 미룬다.
	memmove(pDest, pSource, sizeof(TDATA)*nCount);


	//-----------------------------------------------------------------
	// 2. Insert한다.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) 비운 자리에 Construct를 호출해 값을 복사한다.
		for(;pSource<pDest; ++pSource)
		{
			// - Construct를 호출한다.
			new (pSource) TDATA(_Val);
		}
	}
	CGD_CATCH_ALL
	{
		// - 다시 땡기기 위해 주소와 갯수를 계산한다.
		TDATA*		pBgn		 = const_cast<TDATA*>(_Where.m_ptrLast);
		TDATA*		pEnd		 = pDest-1;

		// 생성했던 것을 다시 다 Destroy한다.
		for(pBgn;pBgn<pSource; ++pBgn)
		{
			// - Destroy를 호출한다.
			pBgn->~TDATA();
		}

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy((void*)_Where.m_ptrLast, pDest, sizeof(TDATA)*nCount);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) size를 증가시킨다.
	m_ptrLast		+= _Count;
}


template <typename TDATA>
typename placement_vector<TDATA>::iterator placement_vector<TDATA>::insert(const_iterator _Where, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);

	// 3) 남은 공간이 있는지 확인한다.
	CGD_THROW_IF(remained()<=0, std::length_error("CGD Exception: 공간이 부족합니다.("__FUNCTION__")\n"));


	//-----------------------------------------------------------------
	// 1. Insert를 수행하기 위해 삽입할 공간을 비운다.
	//-----------------------------------------------------------------
	// 1) placement_vector를 한칸씩 뒤로 미룬다.
	memmove((void*)(_Where.m_ptrLast+1), (void*)_Where.m_ptrLast, (m_ptrLast-_Where.m_ptrLast)*sizeof(TDATA));


	//-----------------------------------------------------------------
	// 2. Insert한다.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) 비운 자리에 Constructor를 호출해 값을 복사한다.
		new (_Where.m_ptrLast) TDATA(_Val);
	}
	CGD_CATCH_ALL
	{
		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy((void*)_Where.m_ptrLast, (void*)(_Where.m_ptrLast+1), (m_ptrLast-_Where.m_ptrLast)*sizeof(TDATA));

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 2) size를 증가시킨다.
	++m_ptrLast;

	// Return) 되돌린다.(Insert한 위치의 Iterator를 돌려준다.)
	return	iterator(_Where.m_ptrLast);
}



template <typename TDATA>
typename placement_vector<TDATA>::iterator  placement_vector<TDATA>::erase(const_iterator _Where)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<m_ptrLast);

	// 3) _size가 0보다 작거나 같으면 더이상 pop을 할수가 없다!
	CGDASSERT_ERROR(size()>0);


	//-----------------------------------------------------------------
	// 2. 지운다~
	//-----------------------------------------------------------------
	// 1) 해당위치에 Destructor를 호출해 준다.
	(_Where.m_ptrLast)->~TDATA();

	// 2) 해당위치로 지운다.
	memcpy((void*)_Where.m_ptrLast, (void*)(_Where.m_ptrLast+1), (m_ptrLast-_Where.m_ptrLast-1)*sizeof(TDATA));

	// 3) Last를 줄인다.
	--m_ptrLast;


	// Return)
	return	iterator(_Where.m_ptrLast);
}

template <typename TDATA>
typename placement_vector<TDATA>::iterator placement_vector<TDATA>::erase(const_iterator _First, const_iterator _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) m_ptrFirst가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_First.m_ptrLast>=m_ptrFirst && _First.m_ptrLast<=m_ptrLast);

	// 2) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_Last.m_ptrLast>=m_ptrFirst && _Last.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. 
	//-----------------------------------------------------------------
	// 1) First와 Last가 같다면 그냥 되돌림.
	int	itemCount	 = _Last-_First;

	// Check) ItemCount가 0이면 그냥 끝낸다.
	CGD_RETURN_IF(itemCount==0, iterator(_Last.m_ptrLast));


	//-----------------------------------------------------------------
	// 2. Destroy함수를 호출한다.
	//-----------------------------------------------------------------
	for(const_iterator iter=_First; iter!=_Last; ++iter)
	{
		(*iter).~TDATA();
	}


	//-----------------------------------------------------------------
	// 2. 덥어버린다.
	//-----------------------------------------------------------------
	// 1) 해당위치를 지운다.
	memcpy((void*)_First.m_ptrLast, (void*)_Last.m_ptrLast, (_PtrLast-_Last.m_ptrLast)*sizeof(TDATA));

	// 2) Size를 줄인다.
	m_ptrLast	-= itemCount;


	// Return)
	return	iterator(_Last.m_ptrLast);
}


template <typename TDATA>
void placement_vector<TDATA>::swap(_mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) 같은 container면 그냥 return한다.
	//-----------------------------------------------------------------
	// 1) 같은 거라면 그냥 되돌린다.
	CGD_RETURN_IF(this == &_Right,);

	//-----------------------------------------------------------------
	// 1. Swap한다.
	//-----------------------------------------------------------------
	// 무조건 통채로 바꾼다.(Allocator란 존재치 않는다. 단지 복사...)
	CGD_SWAP(*this, _Right);
}


}