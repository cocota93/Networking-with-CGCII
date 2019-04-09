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
// 1. CGD::placement_vector��!
//     CGD::placement_vector�� �⺻���� ���´� ��� vector�� ���������� �̹� �Ҵ��
//    �޸𸮿� vector�� �����ϴ� ���� �ǹ��Ѵ�.
//
//    - allocator�� �������� �ʴ´�.
//    - reserve ���� ���� ������ �� ���� ���� ���� �� �����ؾ� �Ѵ�.
//    - ���� �ڵ����� ũ�Ⱑ Ŀ����(auto expend)�� ����.
//    - �������� ������ vector���� �ξ� ����ϸ� ���������� ����ص� ���ϰ� ����
//      ����. (�����Ҵ��� ���� �ʱ� ����)
//    - ������ vector�� �����ϴ�.
//
//
// 2. CGD::placement_vector�� ǥ�� �ؼ� ����
//    1) (o) Common Container Standard 
//    2) (o) Reversible Standard 
//    3) (o) Sequence Container Standard 
//    4) (x) Assosiative Container Standard 
//
//    (*) placement_vector�� list�� �ٸ��� random access operator�� ������ �ش�.
//
//
// 3. exception-safe level.
//    1) Strong guarantee.
//       - �ƹ��� Option�� �־����� ������ �⺻������ strong exception safe
//         guarantee�� �������ش�.
//      -  �� Operation�� ������ �� exception safeȮ���� ���� if������� �߰�
//         �ȴ�.
//
//    2) No guarantee (With _CGD_NO_EXCEPTION_GUARANTEE flag)
//       - flag�� �����ϸ� No Execption safe guarantee�� �������ټ� �ִ�.
//       - �߰������� exceptionó���� ���� �ʰų� Ȥ�� ���������� ���� �ӵ���
//         ���� ��� Exception Guarantee�� ������ ��� ������ ���� �߰�����
//         if������ ���ŵǾ� ���� �� ���� code�� ������ �ټ� �ִ�.
//       - �̸� ���� inlineó���Ǵ� Ȯ���� �þ�� ���� �ӵ������ �ٽ��̴�.
//
//
// 4. Option) CGD::placement_vector�� �ֿ� �ɼ�.
// 
//	  1) ����...
//
// *����: �̷� �ּ������� comiler���� ������� ���ϸ� �ټ� �ֽ��ϴ�. ����...
//        ������ �ð��� ������ �̷� �ּ����� ������ �����ֽñ� �ٶ��ϴ�.
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
//     1) X:value_type			Contain�� ��� ������ ��.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:iterator			��ȸ�� �� ���Ǵ� �ݺ���.
//     5) X:const_iterator		��ȸ�� �� ���Ǵ� �ݺ���(const��)
//     6) X:difference_type		�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     7) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
//
//  * Reversible Requirement
//     1) X::reverse_iterator	����ȯ �� ���Ǵ� �ݺ���.
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

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
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
//     2) X(a);			Copy Constrctor.(�ҿ�ð��� ������)
//		  X u(a);
//     3) (&a)->~X();	Destructor.(�ҿ�ð��� ������)
//     4) a.begin(); 	Container ��ȸ�� ����� ���۰� �� iterator 
//		  a.end();
//     5) a==b; a!=b;	Container ��� ���� ������ true.(�ҿ�ð� ������)
//     6) a.size();		Container�� ��� ������ ������ �����Ѵ�.
//     7) a.max_size();	Container�� ���� �� �ִ� �ִ� ���� ������ �����Ѵ�.
//     8) a.empty();	Container�� ��� �ִ� ����� true�� �����Ѵ�.
//     9) a<b; a>b; 	�� ����(�ҿ�ð� ������)
//		  a<=b; a>=b;
//    10) r=a;			Container ���Կ���(�ҿ�ð� ������)
//    11) a.swap(b);	������ Ÿ���� �� Ŀ���̳ʸ� ���� �¹ٲ۴�.
//
//  * Reversible Requirement
//     1) a.rbegin(); 	�ݴ���� ��ȸ�� ���� ���۰� �� iterator
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
		// 1) ������
		const_iterator()												{}
		explicit const_iterator(pointer p_pNow)							{	m_ptrLast=p_pNow;}

		// 2) ����
		const_iterator&		operator=(const const_iterator& _Right)		{	m_ptrLast=_Right.m_ptrLast; return *this;}
		pointer				operator->()									{	return &**this;}

		// 3) �ݺ�
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

		// 4) ��
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
		// 1) ������
		iterator()														{}
		explicit iterator(pointer p_pNow)								{	m_ptrLast=p_pNow;}

		// 2) ����
		iterator&			operator=(const iterator& _Right)			{	m_ptrLast=_Right.m_ptrLast; return *this;}
		iterator&			operator=(const const_iterator& _Right)		{	m_ptrLast=_Right.m_ptrLast; return *this;}
		pointer				operator->()									{	return &**this;}
							operator const_iterator()					{	return const_iterator(m_ptrLast);}

		// 3) �ݺ�
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

		// 4) ��
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
// Constructor/Destructor �Լ���.
//
// - �پ��� ������ constructor�� destructor�Լ����̴�.
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
	// Check) vector���� �ڷῩ������ �ȴ�.
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

	// Check) vector���� �ڷῩ������ �ȴ�.
	CGDASSERT_ERROR((m_ptrFirst+1)==*(_First+1));
}

template <typename TDATA>
placement_vector<TDATA>::~placement_vector()
{
	// 1) ��� �����.
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
// Operator overriding �Լ���.
//

//-----------------------------------------------------------------
template <typename TDATA>
typename placement_vector<TDATA>::_mytype& placement_vector<TDATA>::operator=(const _mytype& _Right)
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
template <typename TDATA>
bool placement_vector<TDATA>::operator==(const _mytype& _Right) const
{
	// Check) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator!=(const _mytype& _Right) const	
{
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator<(const _mytype& _Right) const	
{
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator>(const _mytype& _Right) const	
{
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator<=(const _mytype& _Right) const	
{
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
bool placement_vector<TDATA>::operator>=(const _mytype& _Right) const	
{
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto	iterSrc	 = begin();
	auto	iterDst	 = _Right.begin();

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

template <typename TDATA>
TDATA& placement_vector<TDATA>::at(size_type _Pos)
{
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: ������ �Ѿ �����Դϴ�.("__FUNCTION__")\n"))

	// 1) ���� �о �ǵ�����.
	return m_ptrFirst[_Pos];
}

template <typename TDATA>
const TDATA& placement_vector<TDATA>::at(size_type _Pos) const
{
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_Pos<0 || _Pos>=size(), std::out_of_range("CGD Exception: ������ �Ѿ �����Դϴ�.("__FUNCTION__")\n"))

	// 1) ���� �о �ǵ�����.
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
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) max_size()���� ���� ũ�⿩������ �ȴ�.
	CGD_THROW_IF(_Newsize>max_size(), std::length_error("CGD Exception: �߸��� ũ���Դϴ�.("__FUNCTION__")\n"));

	// 1) 
	auto	iter=end();
	auto	newEnd(begin()+_Newsize);

	CGD_TRY
	{
		// 2) �þ �κб��� Reset�� �Ѵ�.
		for(; iter < newEnd(); ++iter)
		{
			new (&(*iter)) TDATA();
		}

		// 3) �پ���???(������)
	}
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			_Alval.destroy(&(*iterRoll), 1);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 2) Size�� ���� �����Ѵ�.
	m_ptrLast	 = newEnd;
}


template <typename TDATA>
void placement_vector<TDATA>::clear()
{
	// Check) m_ptrFirst�� nullptr�̸� ������.
	CGD_RETURN_IF(m_ptrFirst==nullptr,)


	//-----------------------------------------------------------------
	// 1. �����...
	//-----------------------------------------------------------------
	// 1) ��� Item�� Destructor�� ȣ���Ѵ�.
	for(iterator iter=begin(); iter != end(); ++iter)
	{
		(*iter).~TDATA();
	}

	// 2) Last�� First�� ����� 0�� �����.
	m_ptrLast	 = m_ptrFirst;
}


template <typename TDATA>
void placement_vector<TDATA>::push_back(const TDATA& _Val)
{
	// Check) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct�� ȣ���Ѵ�.
	new (m_ptrLast) TDATA(_Val);
	
	// 2) Last ������ ������Ŵ
	++m_ptrLast;
}

template <typename TDATA>
void placement_vector<TDATA>::push_back()
{
	// Check) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// Check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct�� ȣ���Ѵ�.
	new (m_ptrLast) TDATA();
	
	// 2) Last ������ ������Ŵ
	++m_ptrLast;
}

template <typename TDATA>
void placement_vector<TDATA>::pop_back()
{
	//-----------------------------------------------------------------
	// Check) Empty�˻�.
	//-----------------------------------------------------------------
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

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
	// 1) ũ�⸦ ���δ�.
	--m_ptrLast;

	// 2) Destructor�� ȣ���Ѵ�.
	m_ptrLast->~TDATA();
}

template <typename TDATA>
void placement_vector<TDATA>::assign(size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) �ִ� �������� ũ�� ������!
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: ũ�Ⱑ �߸��Ǿ����ϴ�.("__FUNCTION__")\n"));


	//-----------------------------------------------------------------
	// 1. ���� �ִ´�.
	//-----------------------------------------------------------------
	// 1) ������� First�� Last�� ����Ű�� Iterator
	TDATA*	first	 = m_ptrLast;

	// 2) End�� ���Ѵ�.
	TDATA*	newEnd	 = m_ptrLast+_Count;

	CGD_TRY
	{
		// 3) ���� �ִ´�.
		for(; first != newEnd; ++first)
		{
			new (first) TDATA(_Val);
		}
	}
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(TDATA* pRoll=m_ptrLast; pRoll!=first; ++pRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*pRoll).~TDATA();
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 4) �Ϸ������� m_ptrLast�� newEnd�� �ٲ۴�.
	m_ptrLast	+= newEnd;
}

template <typename TDATA>
template <typename ITERATOR>
void placement_vector<TDATA>::assign(ITERATOR _First, ITERATOR _Last)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGD_THROW_IF(m_ptrFirst==nullptr, std::length_error("CGD Exception: placement���� �ʾҽ��ϴ�.("__FUNCTION__")\n"))


	//-----------------------------------------------------------------
	// 1. ���� �ִ´�.
	//-----------------------------------------------------------------
	// 1) ������� First�� Last�� ����Ű�� Iterator
	TDATA*	first	 = m_ptrLast;

	CGD_TRY
	{
		// 2) ���� �ִ´�.
		for(; _First != _Last; ++_First, ++first)
		{
			// Check) Remained�� 0�̸� �ȉ´�.
			CGD_THROW_IF(remained()!=0, std::length_error("CGD Exception: �߸��� ũ���Դϴ�.("__FUNCTION__")\n"));

			new (first) TDATA(*_First);
		}
	}
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(TDATA* pRoll=m_ptrLast; pRoll!=first; ++pRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*pRoll).~TDATA();
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 3) �Ϸ������� m_ptrLast�� newEnd�� �ٲ۴�.
	m_ptrLast	+= newEnd;
}

template <typename TDATA>
template<typename TITERATOR>
void placement_vector<TDATA>::insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. ������ ���Ѵ�.
	//-----------------------------------------------------------------
	// 1) Insert Count�� ��´�.
	size_type	Insertcount	 = _Last-_First;

	// 2) �� ������ �����ϴ��� �˻��Ѵ�.
	CGD_THROW_IF(remained()<Insertcount, std::length_error("CGD Exception: ������ �����մϴ�.("__FUNCTION__")\n"));


	//-----------------------------------------------------------------
	// 1. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	// 1) ���� �ִ´�.(size�� �ڵ� ����...)
	TDATA*		pSource	 = const_cast<TDATA*>(_Where.m_ptrLast);
	TDATA*		pDest	 = const_cast<TDATA*>(_Where.m_ptrLast+Insertcount);
	size_type	nCount	 = m_ptrLast-pSource;

	// 2) placement_vector�� ��ĭ�� �ڷ� �̷��.
	memmove(pDest, pSource, sizeof(TDATA)*nCount);


	//-----------------------------------------------------------------
	// 2. Insert�Ѵ�.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		for(;_First!=_Last; ++_First, ++pSource)
		{
			// - Construct�� ȣ���Ѵ�.
			new (pSource) TDATA(*_First);
		}
	}
	CGD_CATCH_ALL
	{
		// - �ٽ� ����� ���� �ּҿ� ������ ����Ѵ�.
		TDATA* pBgn = const_cast<TDATA*>(_Where.m_ptrLast);

		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(;pBgn<pSource; ++pBgn)
		{
			// - Destroy�� ȣ���Ѵ�.
			pBgn->~TDATA();
		}

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy((void*)_Where.m_ptrLast, pDest, sizeof(TDATA)*nCount);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 3) size�� ������Ų��.
	m_ptrLast		+= Insertcount;
}



template <typename TDATA>
void placement_vector<TDATA>::insert(const_iterator _Where, size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);

	// 3) �� ������ �����ϴ��� �˻��Ѵ�.
	CGD_THROW_IF(remained()<_Count, std::length_error("CGD Exception: ������ �����մϴ�.("__FUNCTION__")\n"));


	//-----------------------------------------------------------------
	// 1. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	// 1) ���� �ִ´�.(size�� �ڵ� ����...)
	TDATA*		pSource	 = const_cast<TDATA*>(_Where.m_ptrLast);
	TDATA*		pDest	 = const_cast<TDATA*>(_Where.m_ptrLast+_Count);
	size_type	nCount	 = m_ptrLast-pSource;

	// 2) placement_vector�� ��ĭ�� �ڷ� �̷��.
	memmove(pDest, pSource, sizeof(TDATA)*nCount);


	//-----------------------------------------------------------------
	// 2. Insert�Ѵ�.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		for(;pSource<pDest; ++pSource)
		{
			// - Construct�� ȣ���Ѵ�.
			new (pSource) TDATA(_Val);
		}
	}
	CGD_CATCH_ALL
	{
		// - �ٽ� ����� ���� �ּҿ� ������ ����Ѵ�.
		TDATA*		pBgn		 = const_cast<TDATA*>(_Where.m_ptrLast);
		TDATA*		pEnd		 = pDest-1;

		// �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(pBgn;pBgn<pSource; ++pBgn)
		{
			// - Destroy�� ȣ���Ѵ�.
			pBgn->~TDATA();
		}

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy((void*)_Where.m_ptrLast, pDest, sizeof(TDATA)*nCount);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 2) size�� ������Ų��.
	m_ptrLast		+= _Count;
}


template <typename TDATA>
typename placement_vector<TDATA>::iterator placement_vector<TDATA>::insert(const_iterator _Where, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<=m_ptrLast);

	// 3) ���� ������ �ִ��� Ȯ���Ѵ�.
	CGD_THROW_IF(remained()<=0, std::length_error("CGD Exception: ������ �����մϴ�.("__FUNCTION__")\n"));


	//-----------------------------------------------------------------
	// 1. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	// 1) placement_vector�� ��ĭ�� �ڷ� �̷��.
	memmove((void*)(_Where.m_ptrLast+1), (void*)_Where.m_ptrLast, (m_ptrLast-_Where.m_ptrLast)*sizeof(TDATA));


	//-----------------------------------------------------------------
	// 2. Insert�Ѵ�.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) ��� �ڸ��� Constructor�� ȣ���� ���� �����Ѵ�.
		new (_Where.m_ptrLast) TDATA(_Val);
	}
	CGD_CATCH_ALL
	{
		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy((void*)_Where.m_ptrLast, (void*)(_Where.m_ptrLast+1), (m_ptrLast-_Where.m_ptrLast)*sizeof(TDATA));

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 2) size�� ������Ų��.
	++m_ptrLast;

	// Return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return	iterator(_Where.m_ptrLast);
}



template <typename TDATA>
typename placement_vector<TDATA>::iterator  placement_vector<TDATA>::erase(const_iterator _Where)
{
	//-----------------------------------------------------------------
	// Check) 
	//-----------------------------------------------------------------
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 2) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Where.m_ptrLast>=m_ptrFirst && _Where.m_ptrLast<m_ptrLast);

	// 3) _size�� 0���� �۰ų� ������ ���̻� pop�� �Ҽ��� ����!
	CGDASSERT_ERROR(size()>0);


	//-----------------------------------------------------------------
	// 2. �����~
	//-----------------------------------------------------------------
	// 1) �ش���ġ�� Destructor�� ȣ���� �ش�.
	(_Where.m_ptrLast)->~TDATA();

	// 2) �ش���ġ�� �����.
	memcpy((void*)_Where.m_ptrLast, (void*)(_Where.m_ptrLast+1), (m_ptrLast-_Where.m_ptrLast-1)*sizeof(TDATA));

	// 3) Last�� ���δ�.
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
	// 1) m_ptrFirst�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptrFirst!=nullptr);

	// 1) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_First.m_ptrLast>=m_ptrFirst && _First.m_ptrLast<=m_ptrLast);

	// 2) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_Last.m_ptrLast>=m_ptrFirst && _Last.m_ptrLast<=m_ptrLast);


	//-----------------------------------------------------------------
	// 1. 
	//-----------------------------------------------------------------
	// 1) First�� Last�� ���ٸ� �׳� �ǵ���.
	int	itemCount	 = _Last-_First;

	// Check) ItemCount�� 0�̸� �׳� ������.
	CGD_RETURN_IF(itemCount==0, iterator(_Last.m_ptrLast));


	//-----------------------------------------------------------------
	// 2. Destroy�Լ��� ȣ���Ѵ�.
	//-----------------------------------------------------------------
	for(const_iterator iter=_First; iter!=_Last; ++iter)
	{
		(*iter).~TDATA();
	}


	//-----------------------------------------------------------------
	// 2. ���������.
	//-----------------------------------------------------------------
	// 1) �ش���ġ�� �����.
	memcpy((void*)_First.m_ptrLast, (void*)_Last.m_ptrLast, (_PtrLast-_Last.m_ptrLast)*sizeof(TDATA));

	// 2) Size�� ���δ�.
	m_ptrLast	-= itemCount;


	// Return)
	return	iterator(_Last.m_ptrLast);
}


template <typename TDATA>
void placement_vector<TDATA>::swap(_mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) ���� container�� �׳� return�Ѵ�.
	//-----------------------------------------------------------------
	// 1) ���� �Ŷ�� �׳� �ǵ�����.
	CGD_RETURN_IF(this == &_Right,);

	//-----------------------------------------------------------------
	// 1. Swap�Ѵ�.
	//-----------------------------------------------------------------
	// ������ ��ä�� �ٲ۴�.(Allocator�� ����ġ �ʴ´�. ���� ����...)
	CGD_SWAP(*this, _Right);
}


}