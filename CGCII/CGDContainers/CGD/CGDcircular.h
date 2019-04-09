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

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
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
	TDATA*					m_ptr;			// Array�� ó�� ��ġ...

	unsigned				m_posHead;		// Head�� Index
	unsigned				m_posTail;		// Tail�� Index

	unsigned				m_mask;			// pos�� Index�� ���� Mask
	unsigned				m_capacity;		// �뷮(������ 2�� �����.)

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
		// 1) ������
		const_iterator()											{}
		explicit const_iterator(TDATA* ptr, unsigned pos, unsigned mask)	{	m_ptr=ptr; m_posNow=pos; m_mask=mask;}

		// 2) ����
		const_iterator&		operator=(const  const_iterator& _Right){	m_ptr=_Right.m_ptr; m_posNow=_Right.m_posNow;m_mask=_Right.m_mask; return *this;}
		const_reference		operator->()							{	return *(m_ptr+(m_posNow & m_mask));}

		// 3) �ݺ�
		const_reference		operator*() const						{	return *(m_ptr+(m_posNow & m_mask));}
		const_iterator&		operator++()							{	++m_posNow; return *this;}
		const_iterator		operator++(int)							{	iterator iter(*this); m_posNow++; return iter;}
		const_iterator&		operator--()							{	--m_posNow; return *this;}
		const_iterator		operator--(int)							{	iterator iter(*this); m_posNow++; return iter;}
		const_iterator		operator+(difference_type _Right)		{	m_posNow+=_Right; return iterator(*this);}
		void				operator+=(difference_type _Right)		{	m_posNow+=_Right;}
		const_iterator		operator-(difference_type _Right)		{	m_posNow-=_Right; return iterator(*this);}
		void				operator-=(difference_type _Right)		{	m_posNow-=_Right;}

		// 4) ��
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
		// 1) ������
		iterator()													{}
		explicit iterator(TDATA* ptr, unsigned pos, unsigned mask)	{	m_ptr=ptr; m_posNow=pos; m_mask=mask;}

		// 2) ����(Assignment)
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
// Constructor/Destructor �Լ���.
//
// - �پ��� ������ constructor�� destructor�Լ����̴�.
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular() : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	// 1) �⺻ Reserve�Ѵ�.
	reserve(16);
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular(const _mytype& _Right) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		insert(begin(), _Right.begin(), _Right.end());
	}
	CGD_CATCH_ALL
	{
		// - Ŭ�����Ѵ�.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular(size_type _Count) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) �ϴ� _Count��ŭ Reserve�Ѵ�.
		reserve(_Count);

		// 1) �����سִ´�.
		for(;_Count>0; --_Count)
		{
			// 1) Construct�� ȣ���Ѵ�.
			m_allocVal.construct(m_ptr+(m_posTail & m_mask));

			// 2) Tail Pointer�� ������Ų��.
			++m_posTail;
		}
	}
	CGD_CATCH_ALL
	{
		// - Ŭ�����Ѵ�.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular(size_type _Count, const TDATA& _Val) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		// - Ŭ�����Ѵ�.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::circular(size_type _Count, const TDATA& _Val, const TALLOCATOR& _Al) : 
m_ptr(0), m_posHead(0), m_posTail(0), m_mask(0), m_capacity(0)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		insert(begin(), _Count, _Val);
	}
	CGD_CATCH_ALL
	{
		// - Ŭ�����Ѵ�.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) �ٽ� Thread!!!
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
		// 1) �����سִ´�.
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		// - Ŭ�����Ѵ�.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) �ٽ� Thread!!!
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
		// 1) �����سִ´�.
		insert(begin(), _First, _Last);
	}
	CGD_CATCH_ALL
	{
		// - Ŭ�����Ѵ�.
		clear();

		// - Deallocate�Ѵ�.
		m_allocVal.deallocate(m_ptr, m_capacity);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <typename TDATA, typename TALLOCATOR>
circular<TDATA, TALLOCATOR>::~circular()
{
	// 1) ��� �����.
	clear();

	// 2) Deallocate�Ѵ�.
	m_allocVal.deallocate(m_ptr, m_capacity);
}




//-----------------------------------------------------------------
// Random access �Լ���.
//
// - random access�� �����ϴ� �Լ��� operator��...
//-----------------------------------------------------------------
template <typename TDATA, typename TALLOCATOR>
TDATA& circular<TDATA, TALLOCATOR>::at(size_type _posNow)
{
	// Check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_posNow<0 || _posNow>=size(), std::out_of_range("CGD Exception: ������ �Ѿ �����Դϴ�.(CGD::circular<TDATA, TALLOCATOR>::at(size_type _posNow))\n"))

	// 1) ���� �о �ǵ�����.
	unsigned	position	 = ((m_posHead+_posNow) & m_mask);

	// 2) ���� Return�Ѵ�.
	return m_ptr[position];
}

template <typename TDATA, typename TALLOCATOR>
const TDATA& circular<TDATA, TALLOCATOR>::at(size_type _posNow) const
{
	// Check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_posNow<0 || _posNow>=size(), std::out_of_range("CGD Exception: ������ �Ѿ �����Դϴ�.(CGD::circular<TDATA, TALLOCATOR>::at(size_type _posNow))\n"))

	// 1) ���� �о �ǵ�����.
	unsigned	position	 = ((m_posHead+_posNow) & m_mask);

	// 2) ���� Return�Ѵ�.
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
	// Check) �ּ� 16 �̻��� �Ǿ� �ȴ�.(4Bit)
	CGDASSERT_ERROR(_Count >=16);

	// Check) �ʹ�ũ�� �ȵȴ�!!
	CGDASSERT_ERROR(max_size() <=CONTAINER_MAX);


	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// 1) capacity�� �̹� _Count���� ũ�� �׳� �ǵ�����.
	CGD_RETURN_IF(_Count<=capacity(),);


	//-----------------------------------------------------------------
	// 1. ũ��� Mask�� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) Mask�� ���Ѵ�.
	unsigned	tMask	 = 0;

	while(_Count)
	{
		_Count	>>= 1;
		tMask	 = (tMask<<1) | 1;
	}


	//-----------------------------------------------------------------
	// 2. ���ο� array�� �Ҵ�޴´�.
	//-----------------------------------------------------------------
	// 1) Array�� �����Ѵ�.
	TDATA*	tempArray	 = m_allocVal.allocate(tMask+1); 

	// Check) tempArray�� 0�̾�� �ȵȴ�.
	CGDASSERT_ERROR(tempArray!=0);


	//-----------------------------------------------------------------
	// 3. ���� array�� �Ҵ������Ѵ�.
	//-----------------------------------------------------------------
	size_type	preSize	 = size();

	// 1) size�� 0�̸� ���� ���� ������ �ʿ�� ����.
	if(preSize != 0)
	{
		// Check) m_ptr�� 0�̾�� �ȵȴ�.
		CGDASSERT_ERROR(m_ptr!=0);

		if(m_posHead<m_posTail)
		{
			// - �޸𸮸� �����Ѵ�.
			memcpy(tempArray, m_ptr, sizeof(TDATA)*(m_posTail-m_posHead));
		}
		else
		{
			// �� ���� Item���� ����Ǿ� ���� �ʰ� �ݴ������� ���� �ִ�
			// ����̴�. �̷� �� ��¿�� ����. �ι� �����ϴ� �� �ۿ�...

			// - �պκ� ����.(posHead~END)
			memcpy(tempArray, m_ptr+m_posHead, sizeof(TDATA)*(m_posTail-m_posHead));

			// - �޺κ� ����.(HEAD~posTail)
			memcpy(tempArray+m_posHead, m_ptr, sizeof(TDATA)*(m_posTail));
		}

		// - ������ data�� �����.(Destroy�� ȣ������ �ʴ´�.)
		m_allocVal.deallocate(m_ptr, capacity());
	}


	//-----------------------------------------------------------------
	// 4. ���� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) �����Ѵ�.
	m_ptr		 = tempArray;
	m_posHead	 = 0;
	m_posTail	 = preSize;
	m_mask		 = tMask;
	m_capacity	 = tMask+1;
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::resize(size_type _Newsize)
{
	// 1) �ִ�ũ�⺸�� ũ�� ũ�⸦ �ø���.
	if(_Newsize > capacity())
	{
		reserve(_Newsize);
	}

	// 2) �޸𸮿� Constructor�� ȣ�����ش�.
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
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 2) Size�� ���� �����Ѵ�.
	m_posTail	 = m_posHead+_Newsize;
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::clear()
{
	//-----------------------------------------------------------------
	// 1. Destruct�� �Ѵ�.
	//-----------------------------------------------------------------
	// 1) First�� Last�� Pos�� ���Ѵ�.
	unsigned	posFirst	 = m_posHead & m_mask;
	unsigned	posLast		 = m_posTail & m_mask;

	// 2) Erase�κ��� ���ӵ� ���.
	if(posFirst>posLast)
	{
		TDATA*	ptr		 = m_ptr+posFirst;
		TDATA*	ptrEnd	 = m_ptr+posLast;
		for(; ptr<ptrEnd; ++ptr)
		{
			m_allocVal.destroy(ptr);
		}
	}
	// 3) Erase�κ��� ���ӵ��� ���� ���.
	else
	{
		// (2�ܰ�� ó���� ����� �Ѵ�.)
		// 1) First~m_posTail���� Destructor�� �ҷ��ش�.
		{
			TDATA*	ptr		 = m_ptr+posFirst;
			TDATA*	ptrEnd	 = m_ptr+(m_posTail & m_mask);
			for(; ptr<ptrEnd; ++ptr)
			{
				m_allocVal.destroy(ptr);
			}
		}
		// 2) m_posHead~Last���� Destructor�� �ҷ��ش�.
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
	// 2. Size�� 0���� �Ѵ�.
	//-----------------------------------------------------------------
	// 1) Last�� First�� ����� �װ� 0���� ����� ���̴�.
	m_posHead	 = m_posTail=0;
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::push_front(const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check) Buffer�˻�.
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// Check) ������ circular�� ũ�⸦ ���δ�.(2���)
	if(size()==capacity())
	{
		// - ���� ũ���� 2��� �ø���.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 1. Push�Ѵ�.
	//-----------------------------------------------------------------
	// 1) Tail Pointer�� ������Ų��.
	--m_posHead;

	// 2) Construct�� ȣ���Ѵ�.
	m_allocVal.construct(m_ptr+(m_posHead & m_mask), _Val);
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::push_front()
{
	//-----------------------------------------------------------------
	// Check) Buffer�˻�.
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// Check) ������ circular�� ũ�⸦ ���δ�.(2���)
	if(size()==capacity())
	{
		// - ���� ũ���� 2��� �ø���.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 1. Push�Ѵ�.
	//-----------------------------------------------------------------
	// 1) Tail Pointer�� ������Ų��.
	--m_posHead;

	// 2) Construct�� ȣ���Ѵ�.
	m_allocVal.construct(m_ptr+(m_posHead & m_mask));
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::pop_front()
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
	CGD_RETURN_IF(empty(),);
	#endif


	//-----------------------------------------------------------------
	// 1. Pop�ϱ�.
	//-----------------------------------------------------------------
	// 1) Destroy�� ȣ���Ѵ�.
	m_allocVal.destroy(m_ptr+(m_posHead & m_mask));

	// 2) Tail Pointer�� ������Ų��.
	++m_posHead;
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::push_back(const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check) Buffer�˻�.
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// 1) ������ circular�� ũ�⸦ ���δ�.(2���)
	if(size()==capacity())
	{
		// - ���� ũ���� 2��� �ø���.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 1. Push�Ѵ�.
	//-----------------------------------------------------------------
	// 1) Construct�� ȣ���Ѵ�.
	m_allocVal.construct(m_ptr+(m_posTail & m_mask), _Val);

	// 2) Tail Pointer�� ������Ų��.
	++m_posTail;
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::push_back()
{
	//-----------------------------------------------------------------
	// Check) Buffer�˻�.
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// 1) ������ circular�� ũ�⸦ ���δ�.(2���)
	if(size()==capacity())
	{
		// - ���� ũ���� 2��� �ø���.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 1. Push�Ѵ�.
	//-----------------------------------------------------------------
	// 1) Construct�� ȣ���Ѵ�.
	m_allocVal.construct(m_ptr+(m_posTail & m_mask));

	// 2) Tail Pointer�� ������Ų��.
	++m_posTail;
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::pop_back()
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
	CGD_RETURN_IF(empty(),);
	#endif


	//-----------------------------------------------------------------
	// 1. Pop�ϱ�.
	//-----------------------------------------------------------------
	// 1) Tail Pointer�� ������Ų��.
	--m_posTail;

	// 2) Destroy�� ȣ���Ѵ�.
	m_allocVal.destroy(m_ptr+(m_posTail & m_mask));
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::assign(size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// ����) CGD::circular���� max_size()�˻�� �������� �ʽ��ϴ�.
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	// 1. ���� ���� �˻�.(���԰����� ������ ������ ���� �ֳ�?)
	//-----------------------------------------------------------------
	// 1) _size�� m_capacity���� ũ�ų� ������ circular�� ũ�⸦ ���δ�.
	if(remained()<_Count)
	{
		// - ���� ũ���� 1.5��� �ø���.
		reserve(m_capacity+_Count);
	}


	//-----------------------------------------------------------------
	// 2. ���� �ִ´�.
	//-----------------------------------------------------------------
	// 1) First Iterator�� ���Ѵ�.(Exception�߻��� Roll back���� ���δ�.)
	iterator iter	 = end();

	CGD_TRY
	{
		// 2) ���� �ִ´�.
		iterator	newEnd(end()+_Count);
		for(; iter != newEnd(); ++iter)
		{
			m_allocVal.construct(&(*iter), _Val);
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 3) Last���� �ٲ۴�.
	m_posTail	+= _Count;
}

template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::assign(const_iterator _First, const_iterator _Last)
{
	//-----------------------------------------------------------------
	// ����) CGD::circular���� max_size()�˻�� �������� �ʽ��ϴ�.
	//-----------------------------------------------------------------

	// Check) 
	CGDASSERT_ERROR(_Last.m_posNow > _First.m_posNow);

	// 1) Size�� ���Ѵ�.
	size_type	count	 = _Last.m_posNow-_First.m_posNow;

	// Check) count�� 0���̸� �׳� ������.
	CGD_RETURN_IF(count == 0,);


	//-----------------------------------------------------------------
	// 1. ���� ���� �˻�.(���԰����� ������ ������ ���� �ֳ�?)
	//-----------------------------------------------------------------
	// 1) _size�� m_capacity���� ũ�ų� ������ circular�� ũ�⸦ ���δ�.
	if(remained()<count)
	{
		// - ���� ũ���� �ø���.
		reserve(m_capacity+count);
	}


	//-----------------------------------------------------------------
	// 2. ���� �ִ´�.
	//-----------------------------------------------------------------
	// 1) First Iterator�� ���Ѵ�.(Exception�߻��� Roll back���� ���δ�.)
	iterator iter=end();

	CGD_TRY
	{
		// 2) ���� �ִ´�.
		iterator	newEnd(end()+count);
		for(; iter != newEnd(); ++iter)
		{
			m_allocVal.construct(&(*iter));
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 3) Last���� �ٲ۴�.
	m_posTail	+= count;
}





template <typename TDATA, typename TALLOCATOR>
template<typename TITERATOR>
void circular<TDATA, TALLOCATOR>::insert(const_iterator _Where, TITERATOR _First, TITERATOR _Last)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::circular���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead>=m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Where.m_posNow>=m_posHead && _Where.m_posNow<=m_posTail));

	// 2) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead<m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Where.m_posNow<=m_posTail || _Where.m_posNow>=m_posHead));


	//-----------------------------------------------------------------
	// 1. ������ ����.
	//-----------------------------------------------------------------
	int	count	 = 0;
	for(TITERATOR iter=_First; iter!=_Last; ++iter)
	{
		++count;
	}


	//-----------------------------------------------------------------
	// 2. ���� ���� �˻�.(���� ������ ������ ������ ���� �ֳ�?)
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// 1) _size�� m_capacity���� ũ�ų� ������ circular�� ũ�⸦ ���δ�.
	if(remained()<count)
	{
		// - ���� ũ���� 2��� �ø���.
		reserve(m_capacity+count);
	}
	#else
	CGDASSERT_ERROR(remained()>=count);
	#endif


	//-----------------------------------------------------------------
	// 2. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	// 1) Where�� Tail���ϱ�.
	unsigned	posWhere	 = _Where.m_posNow & m_mask;
	unsigned	posTail		 = m_posTail & m_mask;

	// 2) Where�ڿ� Tail�� ���� ���.
	if(posWhere<posTail)
	{
		unsigned	remainTail	 = m_capacity-posTail;
		unsigned	tempSize	 = m_capacity-posWhere;

		// - Tail���� ������ count���� Ŭ ���(�ѹ��� ����� ������.)
		if(remainTail >= count)
		{
			memmove((void*)(m_ptr+posWhere+count), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
		}
		// - ���� ������ ������ �Ѿ�� ���...
		else if(tempSize <= count)
		{
			memmove((void*)(m_ptr+(count -tempSize)), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
		}
		// - Tail�� ���� ������ count���� �۾Ƽ� �ι� ������ �����ؾ� �Ѵ�.
		else
		{
			memcpy((void*)(m_ptr), (void*)(m_ptr+(m_capacity- count)), (count -remainTail)*sizeof(TDATA));
			memmove((void*)(m_ptr+(posWhere+ count)), (void*)(m_ptr+(tempSize- count)), (count -remainTail)*sizeof(TDATA));
		}
	}
	// 3) �ι��� ���簡 �ʿ�.
	else if(posWhere>posTail)
	{
		// - Head�κ� �б�..
		memmove ((void*)(m_ptr+ count), (void*)m_ptr, (posTail)*sizeof(TDATA));

		unsigned	tempSize	 = m_capacity-posWhere;

		// - �ѹ��� ����� ������.
		if(tempSize <= count)
		{
			memmove ((void*)(m_ptr+(count -tempSize)), (void*)(m_ptr+posWhere), tempSize*sizeof(TDATA));
		}
		// - �ٽ� �ι����� ������ �����ؾ� �Ѵ�.
		else
		{
			// - Tail�κ� �������� �����ϱ�.
			memcpy ((void*)m_ptr, (void*)(m_ptr+(m_capacity- count)), (tempSize- count)*sizeof(TDATA));

			// - Tail�κ� �о� �����ϱ�..
			memmove ((void*)(m_ptr+(posWhere+ count)), (void*)(m_ptr+posWhere), (count +posTail-m_capacity)*sizeof(TDATA));
		}
	}


	//-----------------------------------------------------------------
	// 2. Insert�Ѵ�.
	//-----------------------------------------------------------------
	#ifndef _CGD_NO_EXCEPTION_GUARANTEE
	// For Exception) ���� Roll back�� ���� ������ ���´�.
	iterator	iterRoll = _Where;
	#endif

	// 1) ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
	CGD_TRY
	{
		// 2) ���� �ִ´�.
		for(;_First!=_Last; ++_First, ++_Where)
		{
			// - Construct�� ȣ���Ѵ�.
			m_allocVal.construct((TDATA*)&(*_Where), *_First);
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(; iterRoll!=_Where; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// - �����ش�.
		if(posWhere<posTail)
		{
			unsigned	remainTail	 = m_capacity-posTail;
			unsigned	tempSize	 = m_capacity-posWhere;

			// - Tail���� ������ count���� Ŭ ���(�ѹ��� ����� ������.)
			if(remainTail >= count)
			{
				memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+ count), (posTail-posWhere)*sizeof(TDATA));
			}
			// - ���� ������ ������ �Ѿ�� ���...
			else if(tempSize <= count)
			{
				memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+(count -tempSize)), (posTail-posWhere)*sizeof(TDATA));
			}
			// - Tail�� ���� ������ count���� �۾Ƽ� �ι� ������ �����ؾ� �Ѵ�.
			else
			{
				memcpy((void*)(m_ptr+(tempSize- count)), (void*)(m_ptr+(posWhere+ count)), (count -remainTail)*sizeof(TDATA));
				memcpy((void*)(m_ptr+(m_capacity- count)), (void*)(m_ptr), (count -remainTail)*sizeof(TDATA));
			}
		}
		// 3) �ι��� ���簡 �ʿ�.
		else if(posWhere>posTail)
		{
			unsigned	tempSize	 = m_capacity-posWhere;

			// - �ѹ��� ����� ������.
			if(tempSize <= count)
			{
				memcpy ((void*)(m_ptr+posWhere), (void*)(m_ptr+(count -tempSize)), tempSize*sizeof(TDATA));
			}
			// - �ٽ� �ι����� ������ �����ؾ� �Ѵ�.
			else
			{
				// - Tail�κ� �о� �����ϱ�..
				memcpy ((void*)(m_ptr+posWhere), (void*)(m_ptr+(posWhere+ count)), (count +posTail-m_capacity)*sizeof(TDATA));

				// - Tail�κ� �������� �����ϱ�.
				memcpy ((void*)(m_ptr+(m_capacity- count)), (void*)m_ptr, (tempSize- count)*sizeof(TDATA));
			}

			// - Head�κ� �б�..
			memcpy ((void*)m_ptr, (void*)(m_ptr+ count), (posTail)*sizeof(TDATA));
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 2) _PtrLast�� ������Ų��.
	m_posTail	+= count;
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::insert(const_iterator _Where, size_type _Count, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::circular���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead>=m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Where.m_posNow>=m_posHead && _Where.m_posNow<=m_posTail));

	// 2) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead<m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Where.m_posNow<=m_posTail || _Where.m_posNow>=m_posHead));


	//-----------------------------------------------------------------
	// 1. ���� ���� �˻�.(���� ������ ������ ������ ���� �ֳ�?)
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// 1) _size�� m_capacity���� ũ�ų� ������ circular�� ũ�⸦ ���δ�.
	if(remained()<_Count)
	{
		// - ���� ũ���� 2��� �ø���.
		reserve(m_capacity+_Count);
	}
	#else
	CGDASSERT_ERROR(remained()>=_Count);
	#endif



	//-----------------------------------------------------------------
	// 2. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	// 1) Where�� Tail���ϱ�.
	unsigned	posWhere	 = _Where.m_posNow & m_mask;
	unsigned	posTail		 = m_posTail & m_mask;

	// 2) Where�ڿ� Tail�� ���� ���.
	if(posWhere<posTail)
	{
		unsigned	remainTail	 = m_capacity-posTail;
		unsigned	tempSize	 = m_capacity-posWhere;

		// - Tail���� ������ _Count���� Ŭ ���(�ѹ��� ����� ������.)
		if(remainTail >= _Count)
		{
			memmove((void*)(m_ptr+posWhere+_Count), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
		}
		// - ���� ������ ������ �Ѿ�� ���...
		else if(tempSize <=_Count)
		{
			memmove((void*)(m_ptr+(_Count-tempSize)), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
		}
		// - Tail�� ���� ������ _Count���� �۾Ƽ� �ι� ������ �����ؾ� �Ѵ�.
		else
		{
			memcpy((void*)(m_ptr), (void*)(m_ptr+(m_capacity-_Count)), (_Count-remainTail)*sizeof(TDATA));
			memmove((void*)(m_ptr+(posWhere+_Count)), (void*)(m_ptr+(tempSize-_Count)), (_Count-remainTail)*sizeof(TDATA));
		}
	}
	// 3) �ι��� ���簡 �ʿ�.
	else if(posWhere>posTail)
	{
		// - Head�κ� �б�..
		memmove ((void*)(m_ptr+_Count), (void*)m_ptr, (posTail)*sizeof(TDATA));

		unsigned	tempSize	 = m_capacity-posWhere;

		// - �ѹ��� ����� ������.
		if(tempSize <= _Count)
		{
			memmove ((void*)(m_ptr+(_Count-tempSize)), (void*)(m_ptr+posWhere), tempSize*sizeof(TDATA));
		}
		// - �ٽ� �ι����� ������ �����ؾ� �Ѵ�.
		else
		{
			// - Tail�κ� �������� �����ϱ�.
			memcpy ((void*)m_ptr, (void*)(m_ptr+(m_capacity-_Count)), (tempSize-_Count)*sizeof(TDATA));

			// - Tail�κ� �о� �����ϱ�..
			memmove ((void*)(m_ptr+(posWhere+_Count)), (void*)(m_ptr+posWhere), (_Count+posTail-m_capacity)*sizeof(TDATA));
		}
	}


	//-----------------------------------------------------------------
	// 2. Insert�Ѵ�.
	//-----------------------------------------------------------------
	#ifndef _CGD_NO_EXCEPTION_GUARANTEE
	// For Exception) ���� Roll back�� ���� ������ ���´�.
	iterator	iterRoll = _Where;
	#endif

	// 1) ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
	CGD_TRY
	{
		// 2) ���� �ִ´�.
		iterator	iterEnd	 = _Where+_Count;
		for(;_Where!= iterEnd; ++_Where)
		{
			// - Construct�� ȣ���Ѵ�.
			m_allocVal.construct((TDATA*)&(*_Where), _Val);
		}
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(; iterRoll!=_Where; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			m_allocVal.destroy(&(*iterRoll), 1);
		}

		// - �����ش�.
		if(posWhere<posTail)
		{
			unsigned	remainTail	 = m_capacity-posTail;
			unsigned	tempSize	 = m_capacity-posWhere;

			// - Tail���� ������ _Count���� Ŭ ���(�ѹ��� ����� ������.)
			if(remainTail >= _Count)
			{
				memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+_Count), (posTail-posWhere)*sizeof(TDATA));
			}
			// - ���� ������ ������ �Ѿ�� ���...
			else if(tempSize <=_Count)
			{
				memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+(_Count-tempSize)), (posTail-posWhere)*sizeof(TDATA));
			}
			// - Tail�� ���� ������ _Count���� �۾Ƽ� �ι� ������ �����ؾ� �Ѵ�.
			else
			{
				memcpy((void*)(m_ptr+(tempSize-_Count)), (void*)(m_ptr+(posWhere+_Count)), (_Count-remainTail)*sizeof(TDATA));
				memcpy((void*)(m_ptr+(m_capacity-_Count)), (void*)(m_ptr), (_Count-remainTail)*sizeof(TDATA));
			}
		}
		// 3) �ι��� ���簡 �ʿ�.
		else if(posWhere>posTail)
		{
			unsigned	tempSize	 = m_capacity-posWhere;

			// - �ѹ��� ����� ������.
			if(tempSize <= _Count)
			{
				memcpy ((void*)(m_ptr+posWhere), (void*)(m_ptr+(_Count-tempSize)), tempSize*sizeof(TDATA));
			}
			// - �ٽ� �ι����� ������ �����ؾ� �Ѵ�.
			else
			{
				// - Tail�κ� �о� �����ϱ�..
				memcpy ((void*)(m_ptr+posWhere), (void*)(m_ptr+(posWhere+_Count)), (_Count+posTail-m_capacity)*sizeof(TDATA));

				// - Tail�κ� �������� �����ϱ�.
				memcpy ((void*)(m_ptr+(m_capacity-_Count)), (void*)m_ptr, (tempSize-_Count)*sizeof(TDATA));
			}

			// - Head�κ� �б�..
			memcpy ((void*)m_ptr, (void*)(m_ptr+_Count), (posTail)*sizeof(TDATA));
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 2) _PtrLast�� ������Ų��.
	m_posTail	+= _Count;
}

template <typename TDATA, typename TALLOCATOR>
typename circular<TDATA, TALLOCATOR>::iterator circular<TDATA, TALLOCATOR>::insert(const_iterator _Where, const TDATA& _Val)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::circular���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead>=m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Where.m_posNow>=m_posHead && _Where.m_posNow<=m_posTail));

	// 2) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead<m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Where.m_posNow<=m_posTail || _Where.m_posNow>=m_posHead));


	//-----------------------------------------------------------------
	// 1. ���� ���� �˻�.(���԰����� ������ ������ ���� �ֳ�?)
	//-----------------------------------------------------------------
	#ifndef _CGD_CIRCULAR_NO_AUTOEXPAND
	// Check) ������ circular�� ũ�⸦ ���δ�.(2���)
	if(size()==capacity())
	{
		// - ���� ũ���� 2��� �ø���.
		reserve(m_capacity<<1);
	}
	#else
	CGDASSERT_ERROR(size()<capacity());
	#endif


	//-----------------------------------------------------------------
	// 2. Insert�� �����ϱ� ���� ������ ������ ����.
	//-----------------------------------------------------------------
	// 1) Where�� Tail���ϱ�.
	unsigned	posWhere	 = _Where.m_posNow & m_mask;
	unsigned	posTail		 = m_posTail & m_mask;

	// 2) �ѹ��� ����� ����.
	if(posWhere<posTail)
	{
		memmove((void*)(m_ptr+posWhere+1), (void*)(m_ptr+posWhere), (posTail-posWhere)*sizeof(TDATA));
	}
	// 3) �ι��� ���簡 �ʿ�.
	else if(posWhere>posTail)
	{
		// - Head�κ� �б�..(posTail�� 0�� �ɼ��� �ִ�.)
		memmove ((void*)(m_ptr+1), (void*)m_ptr, (posTail)*sizeof(TDATA));

		// - ���� ������ �κ��� ���� ������ �ű��.(assignment�� �ҷ����� �ʰ� �ϱ� ���� �޸� ������.)
		memcpy((void*)m_ptr, (void*)(m_ptr+m_mask), sizeof(TDATA));	// m_mask�� capacity()-1�� ����.

		// - Tail�κ� �б�.(�̰͵� 0�� �ɼ� �ִ�.)
		memmove ((void*)(m_ptr+posWhere+1), (void*)(m_ptr+posWhere), (m_mask-posWhere)*sizeof(TDATA));
	}


	//-----------------------------------------------------------------
	// 3. Insert�Ѵ�.
	//-----------------------------------------------------------------
	CGD_TRY
	{
		// 1) ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		m_allocVal.construct((TDATA*)(m_ptr+posWhere), _Val);
	}
	// Exception) Roll back~
	CGD_CATCH_ALL
	{
		// - �ٽ� ������ �����.(�ΰͰ� �ݴ� ����� ������ �����ش�.)
		if(posWhere<posTail)
		{
			memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+1), (posTail-posWhere)*sizeof(TDATA));
		}
		else if(posWhere>posTail)
		{
			// - Tail�κ� �����.(�̰͵� 0�� �ɼ� �ִ�.)
			memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+1), (m_mask-posWhere)*sizeof(TDATA));

			// - �պκп� �����ߴ� �� �ٽ� �޺κ����� �Űܺ��̱�.(assignment�� �ҷ����� �ʰ� �ϱ� ���� �޸� ������.)
			memcpy((void*)(m_ptr+m_mask), (void*)m_ptr, sizeof(TDATA));	// m_mask�� capacity()-1�� ����.

			// - Head�κ� �����..(posTail�� 0�� �ɼ��� �ִ�.)
			memmove ((void*)m_ptr, (void*)(m_ptr+1), (posTail)*sizeof(TDATA));
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 2) _PtrLast�� ������Ų��.
	++m_posTail;

	// Return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return	iterator((TDATA*)m_ptr, _Where.m_posNow, _Where.m_mask);
}


template <typename TDATA, typename TALLOCATOR>
typename circular<TDATA, TALLOCATOR>::iterator circular<TDATA, TALLOCATOR>::erase(const_iterator _Where)
{
	//-----------------------------------------------------------------
	// Check)
	//-----------------------------------------------------------------
	// ����) CGD::circular���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead>=m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Where.m_posNow>=m_posHead && _Where.m_posNow<m_posTail));

	// 2) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead<m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Where.m_posNow<m_posTail || _Where.m_posNow>=m_posHead));

	// 3) ��� ������ �����Ҽ� ����.
	CGDASSERT_ERROR(!empty());


	//-----------------------------------------------------------------
	// 2. �����~
	//-----------------------------------------------------------------
	unsigned	posWhere	 = _Where.m_posNow & m_mask;

	// 1) �ش���ġ�� Destroy�� ȣ���� �ش�.
	m_allocVal.destroy((TDATA*)(m_ptr+posWhere));


	//-----------------------------------------------------------------
	// 3. �����ؼ� ���ܿ���.
	//-----------------------------------------------------------------
	// 1) Where�� Tail���ϱ�.
	unsigned	posTail		 = m_posTail & m_mask;

	// 2) �ѹ������ ����.
	if(posWhere<=posTail)
	{
		memcpy((void*)(m_ptr+posWhere), (void*)(m_ptr+posWhere+1), (posTail-posWhere-1)*sizeof(TDATA));
	}
	// 3) �ι��� ���簡 �ʿ�.
	else
	{
		// - Tail�κ� �����.
		memcpy((void*)(m_ptr+posTail), (void*)(m_ptr+posTail+1), (m_mask-posWhere)*sizeof(TDATA));

		// - ���� �պκ��� �޺κٿ� �ű��.(assignment�� �ҷ����� �ʰ� �ϱ� ���� �޸� ������.)
		memcpy((void*)(m_ptr+m_mask), (void*)m_ptr, sizeof(TDATA));	// m_mask�� capacity()-1�� ����.

		// - Head�κ� �����.
		memcpy((void*)m_ptr, (void*)(m_ptr+1), (posTail-1)*sizeof(TDATA));
	}

	// 4) Last�� ���δ�.
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
	// ����) CGD::circular���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead>=m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_First.m_posNow>=m_posHead && _First.m_posNow<=m_posTail));

	// 2) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead<m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_First.m_posNow<=m_posTail || _First.m_posNow>=m_posHead));

	// 3) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead>=m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead>=m_posTail && (_Last.m_posNow>=m_posHead && _Last.m_posNow<=m_posTail));

	// 4) _Where�� ��ȿ�� ���������� �˻��Ѵ�.(m_posHead<m_posTail�� ���)
	CGDASSERT_ERROR(m_posHead<m_posTail && (_Last.m_posNow<=m_posTail || _Last.m_posNow>=m_posHead));

	// 5) ��� ������ �����Ҽ� ����.
	CGDASSERT_ERROR(!empty());

	// Check) First�� Last�� ���ٸ� �׳� �ǵ���.
	CGD_RETURN_IF(_First.m_posNow == _Last.m_posNow,);


	//-----------------------------------------------------------------
	// 1. �غ�~
	//-----------------------------------------------------------------
	// 1) First�� Last�� Pos�� ���Ѵ�.
	unsigned	posFirst	 = _First.m_posNow & m_mask;
	unsigned	posLast		 = _Last.m_posNow & m_mask;


	//-----------------------------------------------------------------
	// 2. Erase�κ��� ���ӵ� ���.
	//-----------------------------------------------------------------
	if(posFirst>posLast)
	{
		//----------------------
		// X. Destroy���ֱ�
		//----------------------
		TDATA*	ptr		 = m_ptr+posFirst;
		TDATA*	ptrEnd	 = m_ptr+posLast;
		for(; ptr<ptrEnd; ++ptr)
		{
			m_allocVal.destroy(ptr);
		}


		//-----------------------------------------------------------------
		// X. ���� �����ϱ�...
		//-----------------------------------------------------------------
		unsigned	posTail		 = m_posTail & m_mask;

		// case A) Tail�� Last���� ū���(�׳� �ѹ��� ����� ������.)
		if(posTail>=posLast)
		{
			memcpy((void*)(m_ptr+posFirst), (void*)(m_ptr+posLast), (posTail-posLast)*sizeof(TDATA));
		}
		// case B) Tail�� Last���� ���� ���.(�ι����� ������ �ִٴ� ���̴�.)
		else
		{
			unsigned	remainedTail	 = m_capacity-posLast;

			// 1) �ϴ� Tail�κа��� �����ϰ�...
			memcpy((void*)(m_ptr+posFirst), (void*)(m_ptr+posLast), remainedTail*sizeof(TDATA));

			unsigned	remainedTransfer	 = posLast-posFirst;

			// CaseA) �޺κ��� �ѹ��� �����Ҽ� �ִ�.
			if(remained>=posTail)
			{
				memcpy((void*)(m_ptr+posFirst), (void*)m_ptr, posTail*sizeof(TDATA));
			}
			// CaseB) �ٽ� �� �κκ����� ������ �����ؾ��Ѵ�.
			else
			{
				memcpy((void*)(m_ptr+posFirst), (void*)m_ptr, remainedTransfer*sizeof(TDATA));
				memcpy((void*)(m_ptr), (void*)(m_ptr+remainedTransfer), (posTail-remainedTransfer)*sizeof(TDATA));
			}
		}

		// ������~
		m_posTail	-= (_Last.m_posNow-_First.m_posNow);
	}
	//-----------------------------------------------------------------
	// 3. Erase�κ��� ���ӵ��� ���� ���.
	//-----------------------------------------------------------------
	else
	{
		//----------------------
		// X. Destroy���ֱ�
		//----------------------
		// (2�ܰ�� ó���� ����� �Ѵ�.)
		// 1) First~m_posTail���� Destructor�� �ҷ��ش�.
		{
			TDATA*	ptr		 = m_ptr+posFirst;
			TDATA*	ptrEnd	 = m_ptr+(m_posTail & m_mask);
			for(; ptr<ptrEnd; ++ptr)
			{
				m_allocVal.destroy(ptr);
			}
		}
		// 2) m_posHead~Last���� Destructor�� �ҷ��ش�.
		{
			TDATA*	ptr		 = m_ptr+(m_posHead & m_mask);
			TDATA*	ptrEnd	 = m_ptr+posLast;
			for(; ptr<ptrEnd; ++ptr)
			{
				m_allocVal.destroy(ptr);
			}
		}


		//----------------------
		// X. ���� �����ϱ�...
		//----------------------
		unsigned	posTail		 = m_posTail & m_mask;

		// 1) Total Transfer Size.
		//    (���⼭�� m_posTail�� dwLast���� �����ʿ� ����. ������ Tail�� Last�� ����Ǿ� �����Ƿ�...)
		unsigned	totalTransfer	 = posTail-posLast;

		// 2) Tail�κ��� ���̸� ���Ѵ�.(��ü����-posFirst�� �ǰڴ�.)
		unsigned	remaineTail = m_capacity-posFirst;

		// Case A) �ѹ��� ����� ������.
		if(remaineTail>=totalTransfer)
		{
			memcpy((void*)(m_ptr+posFirst), (void*)(m_ptr+posLast), (posTail-posLast)*sizeof(TDATA));
		}
		//  Case B) Tail�κ��� �����ϰ� �պκ��� �����.
		else
		{
			memcpy((void*)(m_ptr+posFirst), (void*)(m_ptr+posLast), remaineTail*sizeof(TDATA));
			memcpy((void*)m_ptr, (void*)(m_ptr+remaineTail), (totalTransfer-remaineTail)*sizeof(TDATA));
		}

		// ������~
		m_posTail	-= totalTransfer;
	}
}


template <typename TDATA, typename TALLOCATOR>
void circular<TDATA, TALLOCATOR>::swap(_mytype& _Right)
{
	//-----------------------------------------------------------------
	// Check) ���� container�� �׳� return�Ѵ�.
	//-----------------------------------------------------------------
	// 1) ���� �Ŷ�� �׳� �ǵ�����.
	CGD_RETURN_IF(this == &_Right,);


	//-----------------------------------------------------------------
	// CaseA) Allocator�� ������...
	//-----------------------------------------------------------------
	if (m_allocVal == _Right.m_allocVal)
	{
		// �ٲ۴�~
		CGD_SWAP(m_ptr,		_Right.m_ptr);

		CGD_SWAP(m_posHead,	_Right.m_posHead);
		CGD_SWAP(m_posTail,	_Right.m_posTail);

		CGD_SWAP(m_mask,	_Right.m_mask);
		CGD_SWAP(m_capacity,_Right.m_capacity);

		CGD_SWAP(m_allocVal, _Right.m_allocVal);

	}
	//-----------------------------------------------------------------
	// CaseB) Allocator�� �ٸ���...
	//-----------------------------------------------------------------
	else
	{
		// ��ä�� �ٲ۴�.(�ѽθ�...��ü�� �ٲ�.)
		CGD_SWAP(*this, _Right);
	}
}





}


