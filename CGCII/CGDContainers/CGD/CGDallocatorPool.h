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
// CGD::allocator<T>
//
// 1. CGD::list��!
//    �� �״�� list�̴�. �� list�� Ư¡�� ring������ linked list�� �����Ͽ�
//    push�� pop�� ���ϸ� ���� ���ϼ����̶�� �Ҽ� �ִ�.
//    �ִ� rist�� �Ѿ ��쿡�� list�� ���� ���� �߰��ϴ� ���ϰ� ����
//    �����̴�. 
//    �ִ�ũ���� list�� �ѹ� ����� ���� �״������ʹ� ���ϰ� ���� ���ٰ� ���� �ȴ�.
//    ���� �� linked-list �ְ� ���ɴ� �ְ��� ������ ��Ÿ����.
//    �׷��� list�� ���� �����ϰų� Ȥ�� ����� �Ǹ� ���� ���ϸ� �����ϹǷ� 
//    Temporary�� ���Ǵ� �뵵�δ� �� list�� ����� ��õ���� �ʴ´�. 
//
// 2. CGNetTplHeadArray�� �ٽ�! Function�� ��� ����.
//    1) Add                ������
//    2) Detach             ȣȣȣ
//
// 3. CGNetTplHeadArray�� �ֿ� ��� �뵵
//    ��ȭȭȭȭ
//
//
//-----------------------------------------------------------------------------
namespace CGD
{

template<typename TYPE>
class allocator_pool
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
	// 1) Default type
	typedef TYPE				value_type;
	typedef value_type*			pointer;
	typedef value_type&			reference;
	typedef const value_type*	const_pointer;
	typedef const value_type&	const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;

	// 2) convert an allocator<TYPE> to an allocator <_Other>
	template<typename _Other>
	struct rebind
	{	
		typedef allocator_pool<_Other> other;
	};

	#if defined(_MSC_VER)
		#define	NO_WARNNING(a)	a;
	#else
		#define	NO_WARNNING(a)	
	#endif


// ****************************************************************************
// Constructors)
// ----------------------------------------------------------------------------
public:
	allocator_pool() : _pHead(nullptr)								{}
	allocator_pool(const allocator_pool<TYPE>&) : _pHead(nullptr)	{}
	template<typename _Other>
	allocator_pool(const allocator_pool<_Other>&) : _pHead(nullptr)	{}

	~allocator_pool();

	
// ****************************************************************************
// Allocator�� Opeartion
// ----------------------------------------------------------------------------
public:
	// 1) Address
	pointer				address(reference _Val) const				{	return (&_Val);}
	const_pointer		address(const_reference _Val) const			{	return (&_Val);}

	// 2) Assignment Opeator
	template<typename _Other>
	allocator_pool<TYPE>& operator=(const allocator_pool<_Other>&)	{	return (*this);}	// assign from a related allocator (do nothing)

	// 3) Allocate(�Ҵ��ϴ� �Լ�)
	pointer				allocate(size_type _Count);
	pointer				allocate(size_type _Count, const void*)		{	return allocate(_Count);}

	// 4) Deallocate(�Ҵ� �����ϴ� �Լ�.)
	void				deallocate(const pointer _Ptr, size_type);

	// 5) Construct/Destroy (�ּ����� �����ڿ� �Ҹ��� ȣ��)
	void				construct(pointer _Ptr)
	{
	#pragma push_macro("new")
	#undef new
		new (_Ptr) TYPE();
	#pragma pop_macro("new")

	}
	void				construct(pointer _Ptr, const TYPE& _Val)	
	{
	#pragma push_macro("new")
	#undef new
		new (_Ptr) TYPE(_Val);
	#pragma pop_macro("new")
	}
	void				destroy(pointer _Ptr)						{	(_Ptr)->~TYPE(); NO_WARNNING(_Ptr);}

	// 6) Max Size (�ִ� �Ҵ� ����)
	size_type			max_size() const							{	size_type _Count = (size_type)(-1) / sizeof (TYPE);	return (0 < _Count ? _Count : 1);}	// estimate maximum array size


// ****************************************************************************
// Pool
// ----------------------------------------------------------------------------
private:
				TYPE*	_pHead;

	#undef	NO_WARNNING
};


template<typename TYPE>
allocator_pool<TYPE>::~allocator_pool()
{
	while(_pHead!=0)
	{
		TYPE*	pHead	 = _pHead;
		_pHead	 = *reinterpret_cast<TYPE**>(_pHead);

		::operator delete(pHead);
	}
}
	


template<typename TYPE>
typename allocator_pool<TYPE>::pointer allocator_pool<TYPE>::allocate(size_type /*_Count*/)
{
	if(_pHead==0)
	{
#pragma push_macro("new")
#undef new
		return ((TYPE*)::operator new(sizeof(TYPE)));
#pragma pop_macro("new")
	}

	TYPE*	pHead	 = _pHead;

	_pHead	 = *reinterpret_cast<TYPE**>(_pHead);

	// �����ϰ� �׳�... _Count��ŭ new �� ������ �����ش�.
	return pHead;
}

template<typename TYPE>
void allocator_pool<TYPE>::deallocate(const pointer _Ptr, size_type)
{
	*reinterpret_cast<TYPE**>(_Ptr)	 = _pHead;
	_pHead			 = (TYPE*)_Ptr;
}

template<class TALLOC, class TOTHER>
bool operator==(const allocator_pool<TALLOC>&, const allocator_pool<TOTHER>&) throw()
{
	return true;
}

template<class TALLOC, class TOTHER> 
bool operator!=(const allocator_pool<TALLOC>&, const allocator_pool<TOTHER>&) throw()
{
	return false;
}

}