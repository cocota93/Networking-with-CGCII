//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		CGPTR
 @brief		자동 참조 계수(ARC, Auto Reference Counting) 클래스이다.
 @todo		
 @ref		CGOBJ, ICGReferenceable
 @details	\n
 참조계수를 가진 객체(ICGReferenceable를 상속받은 객체)의 참조계수를 자동적으로 증감시켜주는 클래스이다.
 참조계수를 가진 객체의 포인터가 설정될 때 AddRef()함수를 호출해 참조계수를 증가시켜준다.
 또 설정이 해제될 때 Release()함수를 호출해 참조계수를 감소 시켜준다.
 대입, 복사생성 등등 일반적인 조작에 의해 참조가 추가되거나 감소될 때 자동적으로 참조계수가 계산되도록 설계되었다.

*/
//-----------------------------------------------------------------------------
template <class TREF> class CGOWN;

template <class TREF>
class CGPTR
{
// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:	
			typedef	CGPTR<TREF>	_mytype;
			typedef	TREF		_pointer_type;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CGPTR() : m_ref(nullptr)									{}
			template <class T>
			CGPTR(T* _ref) NOEXCEPT : m_ref(_ref)						{	if(_ref!=nullptr) _ref->AddRef();;}
			CGPTR(const _mytype& _ref) NOEXCEPT : m_ref(_ref.get())		{	if(m_ref!=nullptr) _ref->AddRef();;}
			CGPTR(_mytype&& _rref) NOEXCEPT : m_ref(_rref.get())		{	_rref.m_ref=nullptr;}
			template <class T>
			CGPTR(const CGPTR<T>& _ref) NOEXCEPT : m_ref(_ref.get())	{	if(m_ref!=nullptr) m_ref->AddRef();;}
			~CGPTR() NOEXCEPT											{	if(m_ref!=nullptr) m_ref->Release();;}


// ****************************************************************************
// Members)
// ----------------------------------------------------------------------------
protected:
			TREF*				m_ref;


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) basic operating functions
			void				reset() NOEXCEPT						{	_reset();}
			template <class T>
			void				reset(T* _ref) NOEXCEPT					{	_reset(_ref);}
			template <class T>
			void				reset(const CGPTR<T>& _ref) NOEXCEPT	{	_reset(_ref.get());}
			template <class T>
			void				swap(CGPTR<T>& _ref) NOEXCEPT			{	TREF* temp=m_ref; m_ref=_ref.m_ref; _ref.m_ref=temp;}

			void				move(CGPTR<TREF>& _ref) NOEXCEPT		{	auto p=_ref.get(); auto old=m_ref; if(p==old) return; m_ref=p; _ref._clear(); if(old!=nullptr) old->Release();}
			template <class T>
			void				move(CGPTR<T>& _ref) NOEXCEPT			{	auto p=_ref.get(); auto old=m_ref; if(p==old) return; m_ref=p; _ref._clear(); if(old!=nullptr) old->Release();}
			template <class T>
			void				move(CGOWN<T>& _ref) NOEXCEPT;
			void				move(CGPTR<TREF>&& _rrhs) NOEXCEPT		{	move(_rrhs); }
			template <class T>
			void				move(CGPTR<T>&& _rrhs) NOEXCEPT			{	move(_rrhs); }
			template <class T>
			void				move(CGOWN<T>&& _rrhs) NOEXCEPT	{	move(_rrhs);}

			TREF*				get() const NOEXCEPT					{	return m_ref;}
			TREF**				get_ptr() NOEXCEPT						{	return &m_ref;}
			bool				exist() const NOEXCEPT					{	return m_ref!=nullptr;}
			bool				empty() const NOEXCEPT					{	return m_ref==nullptr;}

	// 2) operator- Assignment-A
			_mytype&			operator=(TREF* _rhs) NOEXCEPT			{	_reset(_rhs); return (*this);}
			template <class T>
			_mytype&			operator=(T* _rhs) NOEXCEPT				{	_reset(_rhs); return (*this);}
			_mytype&			operator=(const _mytype& _rhs) NOEXCEPT	{	_reset(_rhs.get()); return (*this);}
			_mytype&			operator=(_mytype&& _rrhs) NOEXCEPT		{	move(_rrhs); return (*this);}
			_mytype&			operator=(CGOWN<TREF>&& _rrhs) NOEXCEPT;

	// 3) operator- Assignment-B
			template <class T>
			_mytype&			operator=(const CGPTR<T>& _rhs) NOEXCEPT{	_reset(_rhs.get()); return (*this);}
			template <class T>
			_mytype&			operator=(CGPTR<T>&& _rrhs) NOEXCEPT	{	move(_rrhs); return (*this);}
			template <class T>
			_mytype&			operator=(CGOWN<T>&& _rrhs) NOEXCEPT;

	// 4) operator- Assignment-C
	#if defined(_CGD_BUFFER)
			_mytype&			operator=(const CGD::_PASS& _Rhs) NOEXCEPT {	if(m_ref!=nullptr) m_ref->ProcessSerializeIn(*_Rhs.m_pbuffer); return *this;}
	#endif

	// 5) Operator- 
			TREF*				operator->() const NOEXCEPT				{	return m_ref;}
			TREF&				operator*() NOEXCEPT					{	return *m_ref;}
			const TREF&			operator*()	const NOEXCEPT				{	return *m_ref;}

			TREF&				operator[](int _index)					{	return m_ref[_index];}
			const TREF&			operator[](int _index) const			{	return m_ref[_index];}

	// 7) operator- Conversion
								operator	const TREF*() const NOEXCEPT{	return m_ref;}
								operator	TREF*() NOEXCEPT			{	return m_ref;}
	// 6) operator- Compare
			bool				operator==(const _mytype& _rhs) const NOEXCEPT	{	return m_ref==_rhs.m_ref;}
			bool				operator!=(const _mytype& _rhs) const NOEXCEPT	{	return m_ref!=_rhs.m_ref;}
			bool				operator>=(const _mytype& _rhs) const NOEXCEPT	{	return m_ref>=_rhs.m_ref;}
			bool				operator> (const _mytype& _rhs) const NOEXCEPT	{	return m_ref> _rhs.m_ref;}
			bool				operator<=(const _mytype& _rhs) const NOEXCEPT	{	return m_ref<=_rhs.m_ref;}
			bool				operator< (const _mytype& _rhs) const NOEXCEPT	{	return m_ref< _rhs.m_ref;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
			void				_clear() NOEXCEPT						{	m_ref=nullptr;}
protected:
			void				_reset() NOEXCEPT						{	TREF* refOld=m_ref; if(refOld==nullptr) return; m_ref=nullptr; refOld->Release();}
			void				_reset(TREF* _ref) NOEXCEPT				{	TREF* refOld=m_ref; if(_ref==refOld) return; m_ref=_ref; if(_ref!=nullptr) _ref->AddRef(); if(refOld!=nullptr) refOld->Release();}

protected:
	#if defined(_MSC_VER)
			friend class CGPTR<TREF>;
			friend class CGOWN<TREF>;
#endif
};


template <class TONE, class TOTHER>
bool operator==(const CGPTR<TONE>& one, const CGPTR<TOTHER>& other)
{
	return (one.get() == other.get());
}

template <class TONE, class TOTHER>
bool operator!=(const CGPTR<TONE>& one, const CGPTR<TOTHER>& other)
{
	return (one.get() != other.get());
}

template <class TONE, class TOTHER>
bool operator> (const CGPTR<TONE>& one, const CGPTR<TOTHER>& other)
{
	return (one.get() > other.get());
}

template <class TONE, class TOTHER>
bool operator>= (const CGPTR<TONE>& one, const CGPTR<TOTHER>& other)
{
	return (one.get() >= other.get());
}

template <class TONE, class TOTHER>
bool operator< (const CGPTR<TONE>& one, const CGPTR<TOTHER>& other)
{
	return (one.get() < other.get());
}

template <class TONE, class TOTHER>
bool operator<= (const CGPTR<TONE>& one, const CGPTR<TOTHER>& other)
{
	return (one.get() <= other.get());
}


template <class TONE, class TPTR>
bool operator==(const CGPTR<TONE>& one, TPTR* ptr)
{
	return (one.get() == ptr);
}

template <class TONE, class TPTR>
bool operator!=(const CGPTR<TONE>& one, TPTR* ptr)
{
	return (one.get() != ptr);
}

template <class TONE, class TPTR>
bool operator> (const CGPTR<TONE>& one, TPTR* ptr)
{
	return (one.get() > ptr);
}

template <class TONE, class TPTR>
bool operator>= (const CGPTR<TONE>& one, TPTR* ptr)
{
	return (one.get() >= ptr);
}

template <class TONE, class TPTR>
bool operator< (const CGPTR<TONE>& one, TPTR* ptr)
{
	return (one.get() < ptr);
}

template <class TONE, class TPTR>
bool operator<= (const CGPTR<TONE>& one, TPTR* ptr)
{
	return (one.get() <= ptr);
}


template <class TONE, class TOTHER>
void swap_object(CGPTR<TONE>& one, CGPTR<TOTHER>& other)
{
	one.swap(other);
}


template <class TTARGET, class TSOURCE>
CGPTR<TTARGET> static_pointer_cast(const CGPTR<TSOURCE>& source)
{
	return CGPTR<TTARGET>(static_cast<TTARGET*>(source.get()));
}

template <class TTARGET, class TSOURCE>
CGPTR<TTARGET> const_pointer_cast(const CGPTR<TSOURCE>& source)
{
	return CGPTR<TTARGET>(const_cast<TTARGET*>(source.get()));
}

template <class TTARGET, class TSOURCE>
CGPTR<TTARGET> dynamic_pointer_cast(const CGPTR<TSOURCE>& source)
{
	return CGPTR<TTARGET>(dynamic_cast<TTARGET*>(source.get()));
}

template <class TTYPE>
struct hash_CGPTR
{
	size_t operator()(const CGPTR<TTYPE>& rhs) const
	{
		return	static_cast<size_t>(rhs.get());
	}
};

template<class TKEY>
struct _CGPTR_HASH
{
	typedef TKEY *argument_type;
	typedef size_t result_type;

	size_t operator()(const CGPTR<TKEY>& _Keyval) const
	{
		return (std::_Hash_seq(reinterpret_cast<const unsigned char *>(_Keyval.get()), sizeof (TKEY*)));
	}
};
