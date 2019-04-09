//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Factory Classes                              *
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
//
// CGBuffer
//
// 1. CGBuffer는...
//    1) 버퍼를 ICGBuffer객체로 할당받아 활용하는 Buffer이다.
//    2) ICGBuffer를 가지고 있음으로써 할당받은 메모리 버퍼를 참조계수로 관리한다.
//    3) CGPool으로 부터 
//
// 2. CGBuffer의 핵심!
//    1) 
//    2) 
//    3) 
//
//
//-----------------------------------------------------------------------------
class CCGBuffer : public CGD::buffer
{
public:
			CCGBuffer()													{}
			CCGBuffer(_In_opt_ void* _buf, _In_ uint32_t _Len=0, _In_opt_ ICGBuffer* _Reference=nullptr) : CGD::buffer(_buf, _Len), m_reference(_Reference) {}
			CCGBuffer(_In_ const CGD::buffer& _Buffer, _In_opt_ ICGBuffer* _Ref=nullptr) : CGD::buffer(_Buffer), m_reference(_Ref) {}
			CCGBuffer(_In_opt_ ICGBuffer* _Ref) : CGD::buffer(_Ref!=nullptr ? _Ref->buf : nullptr, 0), m_reference(_Ref) {}
			CCGBuffer(_In_ const CGPTR<ICGBuffer>& _Ref) : CGD::buffer(_Ref->buf != nullptr ? _Ref->buf : nullptr, 0), m_reference(_Ref) {}
			CCGBuffer(_In_ ICGBuffer* _Ref, _In_ uint32_t _Len) : CGD::buffer(_Ref->buf, (_Len < _Ref->len) ? _Len : _Ref->len), m_reference(_Ref) { CGASSERT_ERROR(_Ref != nullptr);}
			CCGBuffer(_In_ const CGPTR<ICGBuffer>& _Ref, _In_ uint32_t _Len) : CGD::buffer(_Ref->buf, (_Len<_Ref->len) ? _Len : _Ref->len), m_reference(_Ref) {}
			CCGBuffer(_In_ const CCGBuffer& _value) : CGD::buffer(_value), m_reference(_value.get_reference()) {}
			~CCGBuffer()												{}
public:
	// 1) Alloc & Free
			size_t				capacity() const						{	if(m_reference.exist()) { char* p=m_reference->buf+m_reference->size(); return (buf<p) ? (p-buf) : 0;} else return 0;}
			void				clear()									{	CGD::buffer::clear(); m_reference.reset();}

			void				swap(CCGBuffer& _Rhs)					{	CGD::buffer::swap(_Rhs); auto p=_Rhs.get_reference(); _Rhs.set_reference(m_reference); m_reference=p;}
			void				copy(const buffer& _Source)				{	memcpy(buf, _Source.buf, _Source.len); len=_Source.len;}
			CCGBuffer			clone(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
			CCGBuffer			split_head(const CGD::buffer& _Source)	{	_CGD_BUFFER_BOUND_CHECK(len>=_Source.len); char* p=buf; memcpy(buf, _Source.buf, _Source.len); buf+= _Source.len; len-=_Source.len; return CCGBuffer(p, _Source.len, m_reference);}
			CCGBuffer			split_tail(const CGD::buffer& _Source)	{	_CGD_BUFFER_BOUND_CHECK(len>=_Source.len); memcpy(buf+len-_Source.len, _Source.buf, _Source.len); len-=_Source.len; return CCGBuffer(buf+len, _Source.len, m_reference);}

	// 3) prepend
			template <size_t ISIZE>
			void*				prepend()								{	return _prepend_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			template <class T>
			T&					prepend()								{	return *reinterpret_cast<T*>(_prepend_skip(_CGD_BOUND_INFO_GET _CGD_COMMA sizeof(T)));}
			template <class T>
			typename _AF<T>::t	prepend(const T& _Data)					{	return _prepend(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T, size_t N>
			typename _AF<T[N]>::t prepend(const T (&_Data)[N])			{	return _prepend(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T> 
			T*					prepend(_In_reads_(_Count) const T* _Data, _In_ size_t _Count)	{	return _prepend_array(_CGD_BOUND_INFO_GET _CGD_COMMA _Data, _Count);}
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T> 
			void*				prepend(_In_ const std::initializer_list<T>& _list){	_prepend_initializer_list<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _list); return get_front_ptr();}
		#endif
			template<class I> 
			typename std::enable_if<CGD::is_iterator<I>::value, size_t>::type
								prepend(I _First, I _Last)				{	return _Xprepend_iterator(_CGD_BOUND_INFO_GET _CGD_COMMA this, _First, _Last);}
			void*				prepend(_In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)	{	return _prepend_bytes(_CGD_BOUND_INFO_GET _CGD_COMMA _Size, _Buffer);}

			template <class T>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								prepend_string(const T* _Text)			{ return _prepend_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								prepend_string(const const_string<T,N>& _Text) { return _prepend_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								prepend_string(const T* _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_prepend_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class T, size_t N, class F>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								prepend_string(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_prepend_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}
			template <class T>
			typename std::enable_if<CGD::is_string_type<T>::value, size_t>::type
								prepend_text(const T* _Text)			{ return _prepend_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<CGD::is_string_type<T>::value, size_t>::type
								prepend_text(const const_string<T,N>& _Text) { return _prepend_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F>
			typename std::enable_if<CGD::is_string_type<T>::value, size_t>::type
								prepend_text(const T* _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_prepend_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class T, size_t N, class F>
			typename std::enable_if<CGD::is_string_type<T>::value, size_t>::type
								prepend_text(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_prepend_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}

	// 4) append
			template <size_t ISIZE>
			void*				append()								{	return _append_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			template <class T>
			T&					append()								{	return _append_emplace<T>(_CGD_BOUND_INFO_GET);}
			template <class T>
			typename _AB<T>::t	append(const T& _Data)					{	return _append(_CGD_BOUND_INFO_GET _CGD_COMMA _Data); }
			template <class T, size_t N>
			typename _AB<T[N]>::t append(const T(&_Data)[N])			{	return _append(_CGD_BOUND_INFO_GET _CGD_COMMA _Data); }
			template <class T>
			void*				append(_In_reads_(_Count) const T* _Data, _In_ size_t _Count) {	return _append_array(_CGD_BOUND_INFO_GET _CGD_COMMA _Data, _Count);}
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T> 
			void*				append(const std::initializer_list<T>& _List){	void* p=get_back_ptr(); _append_initializer_list<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _List); return p;}
		#endif
			template<class I> 
			typename std::enable_if<CGD::is_iterator<I>::value, size_t>::type
								append(I _First, I _Last)				{	return _Xappend_iterator(_CGD_BOUND_INFO_GET _CGD_COMMA this, _First, _Last);}
			void*				append(_In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer) { return _append_bytes(_CGD_BOUND_INFO_GET _CGD_COMMA _Size, _Buffer); }

			template <class T>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								append_string(const T* _String)			{ return _append_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _String);}
			template <class T, size_t N>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								append_string(const const_string<T,N>& _String) { return _append_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _String.p);}
			template <class T, class F>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const T* _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_append_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class T, size_t N, class F>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								append_string(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_append_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}

			template <class T, class F>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								append(const T* _Format, F, ...)		{ va_list templist; va_start(templist, _Format); auto p=_append_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class T, size_t N, class F>
			typename std::enable_if<CGD::is_string_type<T>::value, void*>::type
								append(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_append_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}

			template <class T>
			typename std::enable_if<CGD::is_string_type<T>::value, size_t>::type
								append_text(const T* _Text)				{ return _append_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<CGD::is_string_type<T>::value, size_t>::type
								append_text(const const_string<T,N>& _Text) { return _append_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const T* _Format, F _First, TREST... _Rest)				{ return _append_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}
			template <class T, size_t N, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const const_string<T,N>& _Format, F _First, TREST... _Rest)	{ return _append_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}

			template <class K, class T, class F>
			typename std::enable_if<std::is_base_of<text<T>, K>::value && CGD::is_string_type<T>::value, size_t>::type
								append(const T* _Format, F, ...)		{ va_list templist; va_start(templist, _Format); auto p=_append_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, templist); va_end(templist); return p;}
			template <class K, class T, size_t N, class F>
			typename std::enable_if<std::is_base_of<text<T>, K>::value && CGD::is_string_type<T>::value, size_t>::type
								append(const const_string<T,N>& _Format, F, ...) { va_list templist; va_start(templist, _Format); auto p=_append_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, templist); va_end(templist); return p;}

	// 5) extract/subtract
			template <size_t ISIZE>
			void*				extract()								{	return _extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			void*				extract(_In_ size_t _Length)			{	return _extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Length);}
			void*				extract(_In_ const SKIP& _Skip)			{	return _extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Skip.m_skip); }
			template <class T>
			typename _BF<T>::t	extract()								{	return _extract<T>(_CGD_BOUND_INFO_GET);}
			template <class T>
			size_t				extract(__out_ecount(_Length_in_words) T* _String, _In_ size_t _Length_in_words= SIZE_T_MAX)	{	return _extract_string_copy(_String, _Length_in_words);}
			char*				extract_web_modify()					{	return _extract_web_modify(_CGD_BOUND_INFO_GET);}
			template <class T>
			std::basic_string<T> extract_text(T _Terminal=nullptr)		{	return _extract_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Terminal);}
			template <class T>
			T*					extract_text(T _Terminal, T _Modify)	{	return _extract_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Terminal, _Modify);}
			template <class T>
			T&					subtract()								{	return _subtract_general<T>(_CGD_BOUND_INFO_GET);}
			void*				subtract(_In_ size_t _Length)			{	return _subtract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Length);}

	// 6) front/back
			char*				front(_In_ int _Offset=0) const			{	return _front(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	front(_In_ int _Offset=0) const			{	return _front<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	front(_In_ POS& _Pos) const				{	return _front<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Pos.offset);}
			char*				back(_In_ int _Offset=0) const			{	return _back(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	back(_In_ int _Offset=0) const			{	return _back<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			template <class T>
			typename _RH<T>::t	back(_In_ POS& _Pos) const				{	return _back<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _Pos.offset);}

	// 7) begin/end
			CCGBuffer			begin(_In_ int _Offset=0) const			{	return _begin(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			CCGBuffer			end(_In_ int _Offset=0) const			{	return _end(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}

	// 7) Reference
			void				set_reference(ICGBuffer* _Buffer)		{	m_reference=_Buffer;}
			CGPTR<ICGBuffer>	get_reference() const					{	return m_reference.get();}
			size_t				get_remained_size() const				{	if(m_reference.empty()) return SIZE_T_MAX; return (m_reference->size()-len);}

	// 8) Operator Overloading
			// [operator] Overloading ++/--
			CCGBuffer&			operator++() 							{	CGD::buffer::operator++(); return *this;}
			CCGBuffer			operator++(int _Rhs)					{	return CCGBuffer(CGD::buffer::operator++(_Rhs), m_reference.get());}
			CCGBuffer&			operator--()							{	CGD::buffer::operator--(); return *this;}
			CCGBuffer			operator--(int _Rhs)					{	return CCGBuffer(CGD::buffer::operator--(_Rhs), m_reference.get());}
			// [operator] +/-
			CCGBuffer			operator+(size_t _Rhs) const			{	return CCGBuffer(CGD::buffer::operator+(_Rhs), m_reference.get());}
			CCGBuffer			operator+(const SKIP& _Rhs) const		{	return CCGBuffer(CGD::buffer::operator+(_Rhs.m_skip), m_reference.get());}
			CCGBuffer			operator+(const CCGBuffer& _Rhs) const;
			CCGBuffer			operator-(size_t _Rhs) const			{	return CCGBuffer(CGD::buffer::operator-(_Rhs), m_reference.get());}
			// [operator] +=/-=
			CCGBuffer&			operator+=(size_t _Rhs)					{	CGD::buffer::operator+=(_Rhs); return *this;}
			CCGBuffer&			operator+=(const SKIP& _Rhs)			{	CGD::buffer::operator+=(_Rhs.m_skip); return *this;}
			CCGBuffer&			operator+=(const buffer& _Rhs)			{	append(_Rhs); return *this;}
			CCGBuffer&			operator+=(const CCGBuffer& _Rhs)		{	append(_Rhs); return *this;}
			CCGBuffer&			operator-=(size_t _Rhs)					{	CGD::buffer::operator-=(_Rhs); return *this;}
			// [operator] =
			CCGBuffer&			operator=(const buffer& _Rhs)			{	CGD::buffer::operator=(_Rhs); return *this;}
			CCGBuffer&			operator=(const CCGBuffer& _Rhs)		{	CGD::buffer::operator=(_Rhs); m_reference=_Rhs.get_reference(); return *this;}
			CCGBuffer&			operator=(ICGBuffer* _Rhs)				{ buf = _Rhs->buf; len = 0; m_reference = _Rhs; return *this; }
			CCGBuffer&			operator=(const CGPTR<ICGBuffer>& _Rhs)	{	buf=_Rhs->buf; len=0; m_reference=_Rhs; return *this;}
			CCGBuffer&			operator=(const CGPTR<ICGBuffer>&& _Rhs) noexcept {	buf=_Rhs->buf; len=0; m_reference=_Rhs; return *this;}
			// [operator] >> - extract
			template <class T>
			CCGBuffer&			operator>>(T& _Rhs)						{	_Rhs=_extract<T>(_CGD_BOUND_INFO_GET); return *this;}
			CCGBuffer&			operator>>(const SKIP& _Rhs)			{	_extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs.m_skip); return *this; }
			CCGBuffer&			operator>>(const SEND& _Rhs);
			CCGBuffer&			operator>>(const SEND_TO& _Rhs);
			// - Operator << - append
			template <class T>
			CCGBuffer&			operator<<(const T& _Rhs)				{	_append(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs); return *this;}

			bool				operator==(const CCGBuffer& _rhs) const noexcept	{ return buf==_rhs.buf && len==_rhs.len; }
			bool				operator==(const CGD::buffer& _rhs) const noexcept	{ return buf==_rhs.buf && len==_rhs.len; }
			bool				operator!=(const CCGBuffer& _rhs) const noexcept	{ return buf!=_rhs.buf || len!=_rhs.len; }
			bool				operator!=(const CGD::buffer& _rhs) const noexcept	{ return buf!=_rhs.buf || len!=_rhs.len; }


	// 9) Others
			uint32_t			get_CRC() const;
			uint32_t			get_CRC(_In_ const CGEDC::CCRC* _CRC) const;
public:
	// 10) begin/end)
			CCGBuffer			_begin(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const	{	return CCGBuffer(CGD::buffer::_begin(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset), get_reference());}
			CCGBuffer			_end(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const	{	return CCGBuffer(CGD::buffer::_end(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset), get_reference());}

	// 11) append/extarct
	static	CCGBuffer			_extract_CCGBuffer(CGD::buffer* _Buffer _CGD_COMMA _CGD_BOUND_INFO_PARAM);
	static	CCGBuffer			_extract_CCGBuffer(CGD::ptr* _Buffer _CGD_COMMA _CGD_BOUND_INFO_PARAM);
	static	CCGBuffer			_extract_CCGBuffer(CCGBuffer* _Buffer _CGD_COMMA _CGD_BOUND_INFO_PARAM);

	// Check Bound) 
			CGD_CHECK_BOUND		_get_check_bound() const				{	return (m_reference.exist()) ? CGD_CHECK_BOUND(m_reference->buf, m_reference->buf+m_reference->len) : CGD_CHECK_BOUND();}

	// 12) Packet front에 SizeOfPacket에 쓰여진 크기와 len의 길이와 맞는지를 검사하는 함수.
			bool				_validate_message() const;
			bool				_is_buffer_overflow() const;

private:
	// 11) Reference
			CGPTR<ICGBuffer>	m_reference;
};


#include "CGObjectClasses/CGBuffer.inl"
