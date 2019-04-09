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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		CGOWN
 @brief		�ڵ� ���� ���(ARC, Auto Reference Counting) Ŭ������ �Ҹ�� Destroy()�Լ��� ȣ���� �ش�.
 @todo		
 @ref		CGPTR, ICGReferenceable
 @details	\n
 �Ϲ����� ������ �ڵ� �������(ARC) Ŭ������ CGPTR<T>�� ����� �����Ǿ���.
 �ٸ� �������� �Ҹ�ÿ� �����Ǿ� �ִ� �����ʹ� Release()�Լ��� ȣ���� ��������� ���̱� ���� Destroy()�Լ��� ȣ���� �ش�.
 �ܼ��� �����Ǿ��� ��� ��ü�� �����Ͱ� ������ ������ Destroy()�Լ��� ȣ������ �ʴ´�. �ݵ�� �Ҹ��ڿ����� Destroy()�Լ��� ȣ��ȴ�.
 �翬�� �� ��� ��ü�� ICGReferenceable Ŭ������ ��ӹ޾ƾ��ϰ� ICGDestroyable�� ��ӹ޾Ұų� Ȥ�� Destroy()�Լ��� ������ �־���Ѵ�.

*/
//-----------------------------------------------------------------------------
template <class TREF>
class CGOWN : public CGPTR<TREF>
{
// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:	
			typedef	CGOWN<TREF>	_mytype;


// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:	
			CGOWN()												{}
			template <class T>
			CGOWN(T* _ref) NOEXCEPT :CGPTR<TREF>(_ref) 			{}
			CGOWN(const _mytype& _ref) NOEXCEPT : CGPTR<TREF>(_ref) {}
			CGOWN(_mytype&& _ref) NOEXCEPT : CGPTR<TREF>(std::forward(_ref)) {}
			CGOWN(CGPTR<TREF>&& _ref) NOEXCEPT : CGPTR<TREF>(std::forward<CGPTR<TREF>>(_ref)) {}
			template <class T>
			CGOWN(const CGOWN<T>& _ref) NOEXCEPT : CGPTR<TREF>(_ref) {}
			template <class T>
			CGOWN(const CGPTR<T>& _ref) NOEXCEPT : CGPTR<TREF>(_ref) {}
			~CGOWN()											{	ICGDestroyable* ptr=dynamic_cast<ICGDestroyable*>(CGPTR<TREF>::get()); if(ptr!= nullptr) ptr->Destroy();}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) basic operating functions
			CGPTR<TREF>			Destroy()								{	CGPTR<TREF> ptr=*this; ICGDestroyable* p=dynamic_cast<ICGDestroyable*>(ptr.get()); if(p!=nullptr) p->Destroy(); CGPTR<TREF>::_reset(); return ptr;}

	// 2) operator- Assignment-A
			_mytype&			operator=(TREF* _rhs) NOEXCEPT			{	CGPTR<TREF>::_reset(_rhs); return (*this);}
			template <class T>
			_mytype&			operator=(T* _rhs) NOEXCEPT				{	CGPTR<TREF>::_reset(_rhs); return (*this);}
			_mytype&			operator=(const _mytype& _rhs) NOEXCEPT	{	CGPTR<TREF>::_reset(_rhs.get()); return (*this);}
			_mytype&			operator=(const CGOWN<TREF>&& _rrhs) NOEXCEPT{	move(_rrhs); return (*this);}
			_mytype&			operator=(_mytype&& _rrhs) NOEXCEPT		{	move(_rrhs); return (*this);}

	// 3) operator- Assignment-B
			template <class T>
			_mytype&			operator=(const CGPTR<T>& _rhs) NOEXCEPT{	reset(_rhs.get()); return (*this);}
			template <class T>
			_mytype&			operator=(const CGOWN<T>& _rhs) NOEXCEPT {	reset(_rhs.get()); return (*this);}
			template <class T>
			_mytype&			operator=(CGPTR<T>&& _rrhs) NOEXCEPT	{	CGPTR<TREF>::move(_rrhs); return (*this);}
			template <class T>
			_mytype&			operator=(CGOWN<T>&& _rrhs) NOEXCEPT {	move(_rrhs); return (*this);}

	// 4) operator- Assignment-C
	#if defined(_CGD_BUFFER)
			_mytype&			operator=(const CGD::_PASS& _Rhs) NOEXCEPT	{	if(CGPTR<TREF>::m_ref!=nullptr) CGPTR<TREF>::m_ref->ProcessSerializeIn(*_Rhs.m_pbuffer); return *this;}
	#endif

	// 5) Operator- 
			TREF*				operator->() const NOEXCEPT				{	return CGPTR<TREF>::m_ref;}
			TREF&				operator*() NOEXCEPT					{	return *CGPTR<TREF>::m_ref;}
			const TREF&			operator*()	const NOEXCEPT				{	return *CGPTR<TREF>::m_ref;}

			TREF&				operator[](int _index)					{	return CGPTR<TREF>::m_ref[_index];}
			const TREF&			operator[](int _index) const			{	return CGPTR<TREF>::m_ref[_index];}

	// 6) operator- Conversion
			operator	const TREF*() const NOEXCEPT					{	return CGPTR<TREF>::m_ref;}
			operator	TREF*() NOEXCEPT								{	return CGPTR<TREF>::m_ref;}

	// 7) operator- Compare
			bool				operator==(const _mytype& _rhs) const NOEXCEPT	{	return CGPTR<TREF>::m_ref==_rhs.m_ref;}
			bool				operator!=(const _mytype& _rhs) const NOEXCEPT	{	return CGPTR<TREF>::m_ref!=_rhs.m_ref;}
			bool				operator>=(const _mytype& _rhs) const NOEXCEPT	{	return CGPTR<TREF>::m_ref>=_rhs.m_ref;}
			bool				operator> (const _mytype& _rhs) const NOEXCEPT	{	return CGPTR<TREF>::m_ref> _rhs.m_ref;}
			bool				operator<=(const _mytype& _rhs) const NOEXCEPT	{	return CGPTR<TREF>::m_ref<=_rhs.m_ref;}
			bool				operator< (const _mytype& _rhs) const NOEXCEPT	{	return CGPTR<TREF>::m_ref< _rhs.m_ref;}
};

template <class TREF>
template <class T>
void CGPTR<TREF>::move(CGOWN<T>& _rhs) NOEXCEPT 
{
	// Check) ���� ���̸� �׳� ������.
	if (m_ref != nullptr)
		m_ref->Release();;

	// 1) ���� �ִ´�.
	m_ref = _rhs.get();
	
	// 2) _rhs�� nullptr�� �Ѵ�.
	((_mytype&)_rhs).m_ref = nullptr;
}

template <class TREF>
typename CGPTR<TREF>::_mytype& CGPTR<TREF>::operator=(CGOWN<TREF>&& _rrhs) NOEXCEPT 
{
	move(std::move(_rrhs)); return (*this); 
}

template <class TREF>
template <class T>
typename CGPTR<TREF>::_mytype& CGPTR<TREF>::operator=(CGOWN<T>&& _rrhs) NOEXCEPT
{
	move(_rrhs); return (*this); 
}

// Definitions) ���� ������ ȣȯ�� ����
#define	CGPTR_DESTROY	CGOWN