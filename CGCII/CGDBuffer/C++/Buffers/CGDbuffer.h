//*****************************************************************************
//*                                                                           *
//*                                CGD::buffer                                *
//*                      Ver 2.0pre / Release 2015.01.05                      *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.com           *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGBuffer
//
// 1. CGD::buffer��...
//    1) buf, len�� ���� buffer�̴�.
//    2) prepend/pushback�� ����� buffer�� �����͸� �߰��Ҽ� �ְ�
//    3) extract/subtract�� ����� buffer�� �����͸� ������ �� �� �ִ�.
//    4) front/back�Լ��� ����� �����͸� �о�� �� �ִ�.
//    5) WIN32�� WSABUF�� ������ ��ü�� �� �ֵ��� ���۵Ǿ���.
//
// ����) CGD:buffer�� debug ����� ������ Bound Check ����� �ִ�.
//       Release ��忡���� �� ����� ���ŵǵ��� �����Ǿ� �ִ�. Bounding Check
//       ������ �߰��� ���ϸ� ������ �� �����Ƿ� Release��忧�� ������� �ʴ´�.
//
//-----------------------------------------------------------------------------
namespace CGD
{

class  buffer
{
public:
	// 1) Costructor
			buffer() : len(0), buf(nullptr) {}
			buffer(_In_opt_ void* _Ptr, _In_ uint32_t _Len=0) : len(_Len), buf((char*)_Ptr) {}
			buffer(_In_ const buffer& _Buffer) : len(_Buffer.len), buf(_Buffer.buf) {}
public:
	// 2) exist/empty
			char*				get_ptr() const							{	return buf;}
			bool				exist() const							{	return buf!=nullptr;}
			bool				empty() const							{	return buf==nullptr;}
			size_t				size() const							{	return (size_t)len;}
			size_t				length() const							{	return (size_t)len;}
			char*				clear()									{	char* p=buf; buf=nullptr; len=0; return p;}
			void				set_buffer(_In_opt_ void* _Ptr, _In_ uint32_t _Len=0) {	buf=(char*)_Ptr; len=_Len;}

			void				swap(buffer& _Rhs)						{	char* a=buf;uint32_t b=len; buf=_Rhs.buf; len=_Rhs.len; _Rhs.buf=a; _Rhs.len=b;}
			void				copy(const buffer& _Source)				{	memcpy(buf, _Source.buf, _Source.len); len=_Source.len;}
			buffer				clone()									{	buffer a((char*)CGMALLOC(len), len); memcpy(a.buf, buf, len); return a; }
			buffer				split(uint32_t _Offset)					{	if(len<_Offset) _Offset=len; uint32_t newSize=len-_Offset; len=_Offset; return buffer(buf+_Offset, newSize);}

	// 3) prepend
			template <size_t ISIZE>
			void*				prepend()								{	return _prepend_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			template <class T>
			T&					prepend()								{	return *(T*)_prepend_skip(_CGD_BOUND_INFO_GET _CGD_COMMA sizeof(T));}
			template <class T>
			typename _AF<T>::t	prepend(const T& _Data)					{	return _prepend(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T, size_t N>
			typename _AF<T[N]>::t prepend(const T (&_Data)[N])			{	return _prepend(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T> 
			T*					prepend(_In_reads_(_Count) const T* _Data, _In_ size_t _Count) {	return _prepend_array(_CGD_BOUND_INFO_GET _CGD_COMMA _Data, _Count);}
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T> 
			void*				prepend(_In_ const std::initializer_list<T>& _list){	_prepend_initializer_list<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _list); return get_front_ptr();}
		#endif
			template<class I> 
			typename std::enable_if<is_iterator<I>::value, size_t>::type
								prepend(I _First, I _Last)														{ return _Xprepend_iterator(_CGD_BOUND_INFO_GET _CGD_COMMA this, _First, _Last);}
			void*				prepend(_In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)			{ return _prepend_bytes(_CGD_BOUND_INFO_GET _CGD_COMMA _Size, _Buffer);}

			template <class T>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								prepend_string(const T* _Text)													{ return _prepend_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								prepend_string(const const_string<T,N>& _Text)									{ return _prepend_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								prepend_string(const T* _Format, F&& _First, TREST&&... _Rest)					{ return _prepend_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}
			template <class T, size_t N, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								prepend_string(const const_string<T,N>& _Format, F&& _First, TREST&&... _Rest)	{ return _prepend_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}
			template <class T>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								prepend_text(const T* _Text)													{ return _prepend_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								prepend_text(const const_string<T,N>& _Text)									{ return _prepend_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								prepend_text(const T* _Format, F&& _First, TREST&&... _Rest)					{ return _prepend_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}
			template <class T, size_t N, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								prepend_text(const const_string<T,N>& _Format, F&& _First, TREST&&... _Rest)	{ return _prepend_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}

	// 4) append
			template <size_t ISIZE>
			void*				append()								{	return _append_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			template <class T>
			T&					append()								{	return _append_emplace<T>(_CGD_BOUND_INFO_GET);}
			template <class T>
			typename _AB<T>::t	append(const T& _Data)					{	return _append(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T, size_t N>
			typename _AB<T[N]>::t append(const T(&_Data)[N])			{	return _append(_CGD_BOUND_INFO_GET _CGD_COMMA _Data);}
			template <class T>
			void*				append(_In_reads_(_Count) const T* _Data, _In_ size_t _Count) {	return _append_array(_CGD_BOUND_INFO_GET _CGD_COMMA _Data, _Count);}
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			void*				append(const std::initializer_list<T>& _List){	void* p=get_back_ptr(); _append_initializer_list<T>(_CGD_BOUND_INFO_GET _CGD_COMMA _List); return p;}
		#endif
			template<class I> 
			typename std::enable_if<is_iterator<I>::value, size_t>::type
								append(I _First, I _Last)				{	return _Xappend_iterator(_CGD_BOUND_INFO_GET _CGD_COMMA this, _First, _Last);}
			void*				append(_In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer)			{	return _append_bytes(_CGD_BOUND_INFO_GET _CGD_COMMA _Size, _Buffer);}

			template <class T>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const T* _String)			{ return _append_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _String);}
			template <class T, size_t N>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const const_string<T,N>& _String) { return _append_string_pointer(_CGD_BOUND_INFO_GET _CGD_COMMA _String.p);}
			template <class T, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const T* _Format, F&& _First, TREST&&... _Rest)					{ return _append_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}
			template <class T, size_t N, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								append_string(const const_string<T,N>& _Format, F&& _First, TREST&&... _Rest)	{ return _append_string_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}
			template <class T>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const T* _Text)														{ return _append_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text);}
			template <class T, size_t N>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const const_string<T,N>& _Text)										{ return _append_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Text.p);}
			template <class T, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const T* _Format, F&& _First, TREST&&... _Rest)						{ return _append_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}
			template <class T, size_t N, class F, class... TREST>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								append_text(const const_string<T,N>& _Format, F&& _First, TREST&&... _Rest)		{ return _append_text_format(_CGD_BOUND_INFO_GET _CGD_COMMA _Format.p, std::forward<F>(_First), std::forward<TREST>(_Rest)...);}

	// 5) extract/subtract
			template <size_t ISIZE>
			void*				extract()								{	return _extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA ISIZE);}
			void*				extract(_In_ size_t _Length)			{	return _extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Length);}
			void*				extract(_In_ const SKIP& _Skip)			{	return _extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Skip.m_skip); }
			template <class T>
			typename _BF<T>::t	extract()								{	return _extract<T>(_CGD_BOUND_INFO_GET);}
			template <class T>
			size_t				extract(__out_ecount(_Length_in_words) T* _String, _In_ size_t _Length_in_words=(size_t(0)-1))	{	return _extract_string_copy(_String, _Length_in_words);}
			template<class... T>
			size_t				extract(const std::tuple<T...>& _Tuple)	{	auto temp=len; _extract_tuple(_CGD_BOUND_INFO_GET _CGD_COMMA _Tuple); return len-temp;}
			char*				extract_web_modify()					{	return _extract_web_modify(_CGD_BOUND_INFO_GET);}
			template <class T>
			std::basic_string<T> extract_text(T _Terminal=NULL)			{	return _extract_text(_CGD_BOUND_INFO_GET _CGD_COMMA _Terminal);}
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
			buffer				begin(_In_ int _Offset=0) const			{	return _begin(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}
			buffer				end(_In_ int _Offset=0) const			{	return _end(_CGD_BOUND_INFO_GET _CGD_COMMA _Offset);}

	// 8) Operator Overloading
			// [operator] Overloading ++/--
			buffer&				operator++()							{	++buf; --len; return *this;}
			buffer				operator++(int)							{	return buffer(buf++, len--);}
			buffer&				operator--()								{	--buf; ++len; return *this;}
			buffer				operator--(int)							{	return buffer(buf--, len++);}
			// [operator] +/-
			buffer				operator+(size_t _Rhs) const			{	return buffer(buf+_Rhs, (len>static_cast<uint32_t>(_Rhs)) ? (len- static_cast<uint32_t>(_Rhs)) : 0);}
			buffer				operator+(const SKIP& _Rhs) const		{	return buffer(buf+_Rhs.m_skip, (len>static_cast<uint32_t>(_Rhs.m_skip)) ? (len- static_cast<uint32_t>(_Rhs.m_skip)) : 0);}
			buffer				operator-(size_t _Rhs) const				{	return buffer(buf-_Rhs, len+ static_cast<uint32_t>(_Rhs));}
			// [operator] +=/-=
			buffer&				operator+=(size_t _Rhs)					{	buf+=_Rhs; len-= static_cast<uint32_t>(_Rhs); return *this;}
			buffer&				operator+=(const SKIP& _Rhs)			{	buf+=_Rhs.m_skip; len-=static_cast<uint32_t>(_Rhs.m_skip); return *this;}
			buffer&				operator+=(const buffer& _Rhs)			{	_append_bytes(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs.len, _Rhs.buf); return *this;}
			buffer&				operator-=(size_t _Rhs)					{	buf-=_Rhs; len+= static_cast<uint32_t>(_Rhs); return *this;}
			// [operator] =
			buffer&				operator=(const buffer& _Rhs)			{	buf=_Rhs.buf; len=_Rhs.len; return *this;}
			// [operator] >> - extract
			template <class T>
			buffer&				operator>>(T& _Rhs)						{	_Rhs=_extract<T>(_CGD_BOUND_INFO_GET); return *this;}
			buffer&				operator>>(const SKIP& _Rhs)			{	_extract_skip(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs.m_skip); return *this; }
			// - Operator << - append
			template <class T>
			buffer&				operator<<(const T& _Rhs)				{	_append(_CGD_BOUND_INFO_GET _CGD_COMMA _Rhs); return *this;}
			// [operator] Conversion
public:
	// Push Front) 
			template <class T>
			typename _AF<T>::t	_prepend(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T& _Data) {	return _AF<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			template <class T, size_t N>
			typename _AF<T[N]>::t	_prepend(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T (&_Data)[N]) {	return _AF<T[N]>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			void*				_prepend_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size);
			template <class T>
			T&					_prepend_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data);
			template <class T> 
			typename std::enable_if<is_memcopy_able<T>::value, void*>::type
								_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count);
			template <class T> 
			typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
								_prepend_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count);
			template <class T>
			void*				_prepend_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_z_(_Buffer_Size) const T* _String, _In_ size_t _Buffer_Size=INT32_MAX);
			template <class T>
			void*				_prepend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& p_str);
			template <class T>
			void*				_prepend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String, _In_ size_t _Length);
			template <class T, size_t N>
			void*				_prepend_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::const_string<T,N>& _constString);
			template <class T, class... TREST>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								_prepend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, TREST&&... _Rest);
			template <class T>
			size_t				_prepend_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String);
			template <class T, size_t N>
			size_t				_prepend_const_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_text<T, N>& _constText);
			template <class T, class... TREST>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								_prepend_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, TREST&&... _Rest);
			void*				_prepend_bytes(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer);
			void*				_prepend_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer);
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			size_t				_prepend_initializer_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::initializer_list<T>& _list) {	int i=0;for(auto& iter:_list){ _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter); ++i;} return i;}
		#endif
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template <class T>
			void*				_prepend_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T>& _Data) { _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Data)); return buf; }
			template <class T, class... TREST>
			void*				_prepend_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T, TREST...>& _Tupple) {	_prepend_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA (const std::tuple<TREST...>&)_Tupple); _prepend<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Tupple));; return buf;}
		#endif

	// Push Back) 
			template <class T>
			typename _AB<T>::t	_append(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T& _Data) {	return _AB<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			template <class T, size_t N>
			typename _AB<T[N]>::t	_append(_CGD_BOUND_INFO_PARAM _CGD_COMMA const T (&_Data)[N]) {	return _AB<T[N]>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Data);}
			template <class T>
			typename _AB<T>::t	_append(_CGD_BOUND_INFO_PARAM _CGD_COMMA const CGPTR<T>& _Data) {	return _AB<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, *_Data);}
		#ifdef _SUPPORT_INITIALIZER_LIST
			template <class T>
			size_t				_append_initializer_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::initializer_list<T>& _list) {	int i=0;for(auto& iter:_list){ _append<T>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter); ++i;} return i;}
		#endif
			void*				_append_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length);
			template <class T>
			T&					_append_emplace(_CGD_BOUND_INFO_PARAM);
			template <class T>
			T&					_append_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T& _Data);
			template <class T> 
			typename std::enable_if<is_memcopy_able<T>::value, void*>::type
								_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count);
			template <class T> 
			typename std::enable_if<!is_memcopy_able<T>::value, void*>::type
								_append_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_reads_(_Count) const T* _Data, _In_ size_t _Count);
			template <class T>
			void*				_append_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_z_ const T* _String);
			template <class T>
			void*				_append_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::basic_string<T>& p_str);
			template <class T>
			void*				_append_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String, _In_ size_t _Length);
			template <class T, size_t N>
			void*				_append_const_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_string<T,N>& _constString);
			template <class T, class... TREST>
			typename std::enable_if<is_string_type<T>::value, void*>::type
								_append_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, TREST&&... _Rest);
			template <class T>
			size_t				_append_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _String);
			template <class T, size_t N>
			size_t				_append_const_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const const_text<T, N>& _constText);
			template <class T, class... TREST>
			typename std::enable_if<is_string_type<T>::value, size_t>::type
								_append_text_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const T* _Format, TREST&&... _Rest);
			void*				_append_bytes(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_reads_bytes_(_Size) const void* _Buffer);
			void*				_append_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const buffer& _Buffer);
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template<class T>
			void*				_append_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T>& _Tupple)
			{
				void* p = buf + len;
				_append<std::decay<T>::type>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Tupple));
				return p;
			}
			template<class T, class... TREST>
			void*				_append_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T, TREST...>& _Tupple) 
			{ 
				void* p = buf + len;
				_append<std::decay<T>::type>(_CGD_BOUND_INFO_PASS _CGD_COMMA std::get<0>(_Tupple));
				_append_tuple<const std::tuple<TREST...>>(_CGD_BOUND_INFO_PASS _CGD_COMMA (const std::tuple<TREST...>&)_Tupple);
				return p;
			}
		#endif

	// extract) 
			template <class T>
			typename _BF<T>::t	_extract(_CGD_BOUND_INFO_PARAM)								{	return _BF<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this);}
			void*				_extract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length);
			template <class T>
			T*					_extract_string_pointer(_CGD_BOUND_INFO_PARAM);
			template <class T>
			std::basic_string<T> _extract_string(_CGD_BOUND_INFO_PARAM);
			template <class T>
			COUNT_T				_extract_string_copy(_CGD_BOUND_INFO_PARAM _CGD_COMMA __out_ecount(_Length_in_words) T* _String, _In_ size_t _Length_in_words=(size_t(0)-1));
		#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
			template<class T>
			void				_extract_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T>& _Tupple)			{ std::get<0>(_Tupple) = _extract<std::decay<T>::type>(_CGD_BOUND_INFO_PASS); }
			template<class T, class... TREST>
			void				_extract_tuple(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const std::tuple<T, TREST...>& _Tupple){ std::get<0>(_Tupple)=_extract<std::decay<T>::type>(_CGD_BOUND_INFO_PASS); _extract_tuple(_CGD_BOUND_INFO_PASS _CGD_COMMA (const std::tuple<TREST...>&)_Tupple);}
		#endif
			template <class T>
			std::basic_string<T> _extract_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ T _CharTerminal);
			template <class T>
			T*					_extract_text(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ T _CharTerminal,  _In_ T _CharChange);
			char*				_extract_web_modify(_CGD_BOUND_INFO_PARAM);
			std::string			_extract_web(_CGD_BOUND_INFO_PARAM);
			char*				_extract_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Out_writes_(_Buffer_Size) char* p_pstrBuffer, _In_ size_t _Buffer_Size=(size_t(0)-1));
			void*				_extract_bytes(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Size, _In_ void* _Buffer);

	// subtract) 
			template <class T>
			T&					_subtract_general(_CGD_BOUND_INFO_PARAM);
			void*				_subtract_skip(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ size_t _Length);
	// front) 
			char*				_front(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
			template <class T>
			typename _RH<T>::t	_front(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const	{	return _RH<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _Offset);}
			template <class T>
			T&					_front_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
			template <class T>
			T*					_front_string_pointer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
			template <class T>
			std::basic_string<T> _front_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
			char*				_front_web(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
	// back)
			char*				_back(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
			template <class T>
			typename _RH<T>::t	_back(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const	{	int _temp=len+_Offset;return _RH<T>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA this, _temp);}
			template <class T>
			T&					_back_general(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ int& _Offset) const;
	// begin)
			buffer				_begin(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
			buffer				_end(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const;
	// Etc)
			template <class T>
			COUNT_T				_get_front_string_length(_CGD_BOUND_INFO_PARAM);
			void				_copy_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ size_t _Offset, _In_ size_t _Size, _In_ void* _Buffer) const;

	// tm
			void*				_prepend_tm(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const tm& _Data)	{ DATETIME temp(_Data); void* p = get_front_ptr(); _prepend<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p; }
			void*				_append_tm(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const tm& _Data)	{ DATETIME temp(_Data); void* p = get_front_ptr(); _append<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p; }
			tm					_extract_tm(_CGD_BOUND_INFO_PARAM)									{ DATETIME temp = _extract<DATETIME>(_CGD_BOUND_INFO_PASS); return temp.get_tm(); }
			tm					_front_tm(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const	{ DATETIME temp = _front<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset); return temp.get_tm(); }

	// SYSTEMTIME
	#if defined(_SYSTEMTIME_) || defined(_MINWINBASE_)
			void*				_prepend_SYSTEMTIME(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const SYSTEMTIME& _Data)	{ DATETIME temp(_Data); void* p = get_front_ptr(); _prepend<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p; }
			void*				_append_SYSTEMTIME(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const SYSTEMTIME& _Data)	{ DATETIME temp(_Data); void* p = get_front_ptr(); _append<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p; }
			SYSTEMTIME			_extract_SYSTEMTIME(_CGD_BOUND_INFO_PARAM)											{ DATETIME temp = _extract<DATETIME>(_CGD_BOUND_INFO_PASS); return temp.get_SYSTEMTIME(); }
			SYSTEMTIME			_front_SYSTEMTIME(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const			{ DATETIME temp = _front<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset); return temp.get_SYSTEMTIME(); }
	#endif

	// CGD::Time
		#ifdef _CGD_TIME
			void*				_prepend_timepoint(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::TIME::time_point& _Data)				{ DATETIME temp(_Data); void* p=get_front_ptr(); _prepend<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p;}
			void*				_prepend_timepoint_system(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::TIME::SYSTEM::time_point& _Data)	{ DATETIME temp(_Data); void* p=get_front_ptr(); _prepend<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p;}
			void*				_prepend_timepoint_local(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::TIME::LOCAL::time_point& _Data)	{ DATETIME temp(_Data); void* p=get_front_ptr(); _prepend<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p;}

			void*				_append_timepoint(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::TIME::time_point& _Data)					{ DATETIME temp(_Data); void* p=get_front_ptr(); _append<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p;}
			void*				_append_timepoint_system(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::TIME::SYSTEM::time_point& _Data)	{ DATETIME temp(_Data); void* p=get_front_ptr(); _append<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p;}
			void*				_append_timepoint_local(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::TIME::LOCAL::time_point& _Data)	{ DATETIME temp(_Data); void* p=get_front_ptr(); _append<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA temp); return p;}

			CGD::TIME::time_point			_extract_timepoint(_CGD_BOUND_INFO_PARAM)														{ DATETIME temp=_extract<DATETIME>(_CGD_BOUND_INFO_PASS); return temp.get_CGDTIME();}
			CGD::TIME::SYSTEM::time_point	_extract_timepoint_system(_CGD_BOUND_INFO_PARAM)												{ DATETIME temp=_extract<DATETIME>(_CGD_BOUND_INFO_PASS); return temp.get_CGDSYSTEMTIME(); }
			CGD::TIME::LOCAL::time_point	_extract_timepoint_local(_CGD_BOUND_INFO_PARAM)													{ DATETIME temp=_extract<DATETIME>(_CGD_BOUND_INFO_PASS); return temp.get_CGDLOCALTIME(); }

			CGD::TIME::time_point			_front_timepoint(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const						{ DATETIME temp=_front<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset); return temp.get_CGDTIME(); }
			CGD::TIME::SYSTEM::time_point	_front_timepoint_system(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const				{ DATETIME temp=_front<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset); return temp.get_CGDSYSTEMTIME(); }
			CGD::TIME::LOCAL::time_point	_front_timepoint_local(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ int _Offset) const					{ DATETIME temp=_front<DATETIME>(_CGD_BOUND_INFO_PASS _CGD_COMMA _Offset); return temp.get_CGDLOCALTIME(); }
		#endif

public:
			char*				get_front_ptr() const					{	return buf;}
			char*				get_back_ptr() const					{	return buf+len;}

	// Check Bound) 
		#ifdef _CGD_ENABLE_BUFFER_BOUND_CHECK
			CGD_CHECK_BOUND		_get_check_bound() const	{	return CGD_CHECK_BOUND();}
		#endif
public:
			uint32_t			len;
			_Field_size_bytes_(len) char*	buf;
};

}

#include "CGDbuffer.inl"
