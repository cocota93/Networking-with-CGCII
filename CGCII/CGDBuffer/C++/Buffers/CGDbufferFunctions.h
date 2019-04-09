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
// Common Functions
//
//-----------------------------------------------------------------------------
template <class F, class... TREST>
size_t _Xsprintf(_In_ char* _Dest, _In_ const char* _Format, F&& _First, TREST&&... _Rest)
{
	#if defined(_MSC_VER)
	#pragma warning(disable:4996)
	#endif

	return	sprintf(_Dest, _Format, std::forward<F>(_First), std::forward<TREST>(_Rest)...);

	#if defined(_MSC_VER)
	#pragma warning(default:4996)
	#endif
}

template <class F, class... TREST>
size_t _Xsprintf(_In_ wchar_t* _Dest, _In_ const wchar_t* _Format, F&& _First, TREST&&... _Rest)
{
	#if defined(_MSC_VER)
	#pragma warning(disable:4996)
	#endif

	return	swprintf(_Dest, _Format, std::forward<F>(_First), std::forward<TREST>(_Rest)...);

	#if defined(_MSC_VER)
	#pragma warning(default:4996)
	#endif
}

inline size_t _Xvsprintf(_Inout_z_ char* _Dest, _In_z_ const char* _Format, _In_ va_list _Args)
{
	#if defined(_MSC_VER)
	#pragma warning(disable:4996)
	#endif

	return	vsprintf(_Dest, _Format, _Args);

	#if defined(_MSC_VER)
	#pragma warning(default:4996)
	#endif
}

inline size_t _Xvsprintf(_Inout_z_ wchar_t* _Dest, _In_z_ const wchar_t* _Format, _In_ va_list _Args)
{
	#if defined(_MSC_VER)
	#pragma warning(disable:4996)
	#endif

#ifdef _WIN32
	return	vswprintf(_Dest, _Format, _Args);
#else
	return	vswprintf(_Dest, 65536, _Format, _Args);
#endif

	#if defined(_MSC_VER)
	#pragma warning(default:4996)
	#endif
}

template <class T>
size_t _Xappend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_z_count_(_StringLength) const T* _String, _In_ size_t _StringLength)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [0] (" __FUNCTION__ ")"));

	// Check) _Buffer_Size�� 0���ϸ� �ȵȴ�.
	CGD_ASSERT(_StringLength>=0, throw std::invalid_argument("_Buffer_Size is invalid [0] (" __FUNCTION__ ")"));

	// 1) [����_����]�� ���Ѵ�.(NULL���̱��� �����ϹǷ� +sizeof(T)�Ѵ�.)
	const size_t	lengthString = _StringLength+1;	// strnlen(, _Buffer_Size)
	const size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Lower and Upper Bound
	_CGD_BUFFER_BOUND_CHECK((_Dest)>=_bound.bound_lower && ((char*)_Dest+sizeString+sizeof(COUNT_T))<=_bound.bound_upper);

	// 5) [���ڿ�]�� [����_����_������] ��ġ�� �����Ѵ�.
	memcpy(_Dest, _String, sizeString);

	// Return) [����_����]�� ������
	return	lengthString;
}

template <class T>
size_t _Xappend_string(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_ const T* _String)
{
	// Check) _String�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_String!=nullptr, throw std::invalid_argument("_String is nullptr [0] (" __FUNCTION__ ")"));

	// Check) Lower Bound
	_CGD_BUFFER_BOUND_CHECK((_Dest)>=_bound.bound_lower);

	// 1) [����_����]�� ���Ѵ�.(NULL���̱��� �����ϹǷ� +sizeof(T)�Ѵ�.)
	size_t	lengthString = std::char_traits<T>::length(_String)+1;	// strnlen(, _Buffer_Size)
	size_t	sizeString	 = lengthString*sizeof(T);

	// Check) Upper Bound
	_CGD_BUFFER_BOUND_CHECK((reinterpret_cast<const char*>(_Dest)+sizeString)<=_bound.bound_upper);

	// 5) [���ڿ�]�� [����_����_������] ��ġ�� �����Ѵ�.
	memcpy(const_cast<void*>(reinterpret_cast<const void*>(_Dest)), reinterpret_cast<const void*>(_String), sizeString);

	// Return) [����_����]�� ������
	return	lengthString;
}

template <class T, class F, class... TREST>
size_t _Xappend_string_format(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_ const T* _Format, F&& _First, TREST&&... _Rest)
{
	// Check) _Format�� nullptr�̸� �ȵȴ�.
	CGD_ASSERT(_Format!=nullptr, throw std::invalid_argument("_Format is nullptr [0] (" __FUNCTION__ ")"));

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((_Dest)>=_bound.bound_lower);

	// 1) String ����!!!
	size_t	lengthString = _Xsprintf(_Dest, _Format, std::forward<F>(_First), std::forward<TREST>(_Rest)...)+1;

	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK(((char*)_Dest+ lengthString*sizeof(T))<=_bound.bound_upper);

	// Return) 
	return	lengthString;
}

#ifdef _SUPPORT_SYSTEMTIME
template <class T>
void _Xappend_systemtime(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_ const SYSTEMTIME& _Datetime)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((_Dest)>=_bound.bound_lower && ((char*)_Dest+sizeof(uint64_t)*2)<=_bound.bound_upper);

	// 1)
	uint64_t	tempA	  = static_cast<uint64_t>(_Datetime.wYear);
				tempA	| = static_cast<uint64_t>(_Datetime.wMonth) << 16;
				tempA	| = static_cast<uint64_t>(_Datetime.wDay) << 16;
				tempA	| = static_cast<uint64_t>(_Datetime.wHour) << 16;

	uint64_t	tempB	 = static_cast<uint64_t>(_Datetime.wMinute);
				tempB	|= static_cast<uint64_t>(_Datetime.wSecond) << 16;
				tempB	|= static_cast<uint64_t>(_Datetime.wMilliseconds) << 32;

	// 1) String ����!!!
	_Dest->TEMPLATE _append_general<uint64_t>(tempA);
	_Dest->TEMPLATE _append_general<uint64_t>(tempB);
}

template <class S>
SYSTEMTIME _Xextract_systemtime(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	uint64_t	Year_Month_Day_wHour		 = _Source->TEMPLATE _extract_general<uint64_t>(_CGD_BOUND_INFO_PASS);
	uint64_t	Minute_seconds_millisecond	 = _Source->TEMPLATE _extract_general<uint64_t>(_CGD_BOUND_INFO_PASS);

	SYSTEMTIME	tempTime;

	tempTime.wYear			 = static_cast<uint16_t>((Year_Month_Day_wHour    ) & 0xffff);
	tempTime.wMonth			 = static_cast<uint16_t>((Year_Month_Day_wHour>>16) & 0xffff);
	tempTime.wDay			 = static_cast<uint16_t>((Year_Month_Day_wHour>>32) & 0xffff);
	tempTime.wDayOfWeek		 = static_cast<uint16_t>(GetDayOfWeek(tempTime.wYear, tempTime.wMonth, tempTime.wDay));
	tempTime.wHour			 = static_cast<uint16_t>((Year_Month_Day_wHour>>48) & 0xffff);
	tempTime.wMinute		 = static_cast<uint16_t>((Minute_seconds_millisecond     ) & 0xffff);
	tempTime.wSecond		 = static_cast<uint16_t>((Minute_seconds_millisecond >>16) & 0xffff);
	tempTime.wMilliseconds	 = static_cast<uint16_t>((Minute_seconds_millisecond >>32) & 0xffffffff);

	return	tempTime;
}
#endif

template <class T>
void _Xappend_tm(_CGD_BOUND_INFO_PARAM _CGD_COMMA _Inout_ T* _Dest, _In_ const tm& _tm)
{
	// Check) ���� �߰��Ǵ� ũ��� Upper Bound�� �Ѿ�� �ȉ´�.
	_CGD_BUFFER_BOUND_CHECK((_Dest->get_back_ptr())>=_bound.bound_lower && ((char*)_Dest->get_back_ptr()+sizeof(uint32_t)*3)<=_bound.bound_upper);

	// 2)
	uint64_t	tempA	 = static_cast<uint64_t>(_tm.tm_year);
				tempA	|= static_cast<uint64_t>(_tm.tm_mon)  << 16;
				tempA	|= static_cast<uint64_t>(_tm.tm_mday) << 32;
				tempA	|= static_cast<uint64_t>(_tm.tm_hour) << 48;

	uint64_t	tempB	 = static_cast<uint64_t>(_tm.tm_min);
				tempB	|= static_cast<uint64_t>(_tm.tm_sec) << 16;
				//tempB	|= static_cast<uint64_t>(_tm.tm.millisecond) << 32;

	// 1) String ����!!!
	_Dest->TEMPLATE _append_general<uint64_t>(tempA);
	_Dest->TEMPLATE _append_general<uint64_t>(tempB);
}

template <class S>
tm _Xextract_tm(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	uint64_t	Year_Month_Day_wHour		 = _Source->TEMPLATE _extract_general<uint64_t>(_CGD_BOUND_INFO_PASS);
	uint64_t	Minute_seconds_millisecond	 = _Source->TEMPLATE _extract_general<uint64_t>(_CGD_BOUND_INFO_PASS);

	int	year			 = static_cast<int>((Year_Month_Day_wHour) & 0xffff);

	tm	tempTime;
	tempTime.tm_year	 = year -1900;
	tempTime.tm_mon		 = static_cast<int>((Year_Month_Day_wHour >> 16) & 0xffff);
	tempTime.tm_mday	 = static_cast<int>((Year_Month_Day_wHour >> 32) & 0xffff);
	tempTime.tm_yday	 = static_cast<int>(DATETIME::_get_day_of_year(year, tempTime.tm_mon, tempTime.tm_mday));
	tempTime.tm_wday	 = static_cast<int>(DATETIME::_get_day_of_week(year, tempTime.tm_mon, tempTime.tm_mday));
	tempTime.tm_hour	 = static_cast<int>((Year_Month_Day_wHour >> 48) & 0xffff);
	tempTime.tm_min		 = static_cast<int>((Minute_seconds_millisecond) & 0xffff);
	tempTime.tm_sec		 = static_cast<int>((Minute_seconds_millisecond >> 16) & 0xffff);
	//tempTime.tm.tm_millisecond	 = static_cast<int>((Minute_seconds_millisecond >> 32) & 0xffffffff);
	tempTime.tm_isdst	 = 0;

	return	tempTime;
}

template <class S, class T>
typename T::value_type* _Xprepend_container_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) Begin/End Iterator
	auto	riter	 = _container.rbegin();
	auto	riterEnd = _container.rend();

	// 2) [������]���� ��ִ´�.
	for(; riter!=riterEnd; ++riter)
	{
		_Source->TEMPLATE _prepend<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *riter);
	}

	// 3) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(COUNT_T)_container.size());

	// Return) 
	return	(typename T::value_type*)_Source->get_ptr();
}

template <class S, class T>
typename std::enable_if<is_memcopy_able<typename T::value_type>::value, typename T::value_type*>::type
 _Xprepend_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [������]���� �ٷ� memcopy�Ѵ�.
	_Source->TEMPLATE _prepend_bytes(_CGD_BOUND_INFO_PASS _CGD_COMMA _container.size()*sizeof(T::value_type), &_container.front());

	// 2) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(COUNT_T)_container.size());

	// Return) 
	return	(typename T::value_type*)_Source->get_ptr();
}

template <class S, class T>
typename std::enable_if<!is_memcopy_able<typename T::value_type>::value, typename T::value_type*>::type
 _Xprepend_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) Begin/End Iterator
	auto	riter	 = _container.rbegin();
	auto	riterEnd = _container.rend();

	// 2) [������]���� ��ִ´�.
	for(; riter!=riterEnd; ++riter)
	{
		_Source->TEMPLATE _prepend<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *riter);
	}

	// 3) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(COUNT_T)_container.size());

	// Return) 
	return	(typename T::value_type*)_Source->get_ptr();
}

template<class S, class RI> 
typename std::enable_if<is_iterator<RI>::value, int>::type _Xprepend_iterator(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ RI _Reverse_first, _In_ RI _Reverse_last)
{
	// Declare)
	COUNT_T iCount	 = 0;

	// 1) �����͵��� �����Ѵ�.
	for(; _Reverse_first!=_Reverse_last; ++_Reverse_first, ++iCount)
	{
		_Source->TEMPLATE _prepend<typename RI::value_type>(_CGD_BOUND_INFO_PASS *_Reverse_first);
	}

	// 2) ũ�⸦ ����� ��ġ ����
	_Source->TEMPLATE _prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA iCount);

	// Return) 
	return	iCount;
}

template <class S, class T>
typename T::value_type* _Xappend_container_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_container.size());

	// 2) [����_����_��_������]�� �����´�.
	typename T::value_type*	pret = (typename T::value_type*)_Source->get_front_ptr();

	// 3) [������]���� ��ִ´�.
	auto iter=_container.begin();
	auto iterEnd=_container.end();

	for(; iter!=iterEnd; ++iter)
	{
		_Source->TEMPLATE _append<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *iter);
	}

	// Return) [������]���� ó�� �����͸� �����Ѵ�.
	return	pret;
}

template <class S, class T>
typename T::value_type* _Xappend_container_CGPTR_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(COUNT_T)_container.size());

	// 2) [����_����_��_������]�� �����´�.
	typename T::value_type*	pret = (typename T::value_type*)_Source->get_front_ptr();

	// 3) [������]���� ��ִ´�.
	auto iter	 = _container.begin();
	auto iterEnd = _container.end();

	for (; iter != iterEnd; ++iter)
	{
		if(iter->empty()==false)
		{
			_Source->TEMPLATE _append<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *iter);
		}
		else
		{
			_Source->TEMPLATE _append<COUNT_T>(COUNT_T(0)-1);
		}
	}

	// Return) [������]���� ó�� �����͸� �����Ѵ�.
	return	pret;
}

template <class S, class T>
typename T::value_type* _Xappend_container_CGOWN_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA(COUNT_T)_container.size());

	// 2) [����_����_��_������]�� �����´�.
	typename T::value_type*	pret = (typename T::value_type*)_Source->get_front_ptr();

	// 3) [������]���� ��ִ´�.
	auto iter	 = _container.begin();
	auto iterEnd = _container.end();

	for (; iter != iterEnd; ++iter)
	{
		if(iter->empty()==false)
		{
			_Source->TEMPLATE _append<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *iter);
		}
		else
		{
			_Source->TEMPLATE _append<COUNT_T>(COUNT_T(0)-1);
		}
	}

	// Return) [������]���� ó�� �����͸� �����Ѵ�.
	return	pret;
}


template <class S, class T>
typename std::enable_if<is_memcopy_able<typename T::value_type>::value, void*>::type
 _Xappend_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// Declare)
	auto	count = _container.size();

	// 1) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)count);

	// 2) [����_����_��_������]�� �����´�.
	typename T::value_type*	pret = (typename T::value_type*)_Source->get_front_ptr();

	// 3) [������]���� ��ִ´�.
	if (count != 0)
	{
		_Source->TEMPLATE _append_bytes(_CGD_BOUND_INFO_PASS _CGD_COMMA count*sizeof(typename T::value_type), &_container.front());
	}

	// Return) [������]���� ó�� �����͸� �����Ѵ�.
	return	pret;
}

template <class S, class T>
typename std::enable_if<!is_memcopy_able<typename T::value_type>::value, void*>::type
_Xappend_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _container)
{
	// 1) [����_����_��_������]�� �����´�.
	void*	pret = (void*)_Source->get_back_ptr();

	// 2) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_container.size());

	// 3) [������]���� ��ִ´�.
	auto iter=_container.begin();
	auto iterEnd=_container.end();

	for(; iter!=iterEnd; ++iter)
	{
		_Source->TEMPLATE _append<typename T::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *iter);
	}

	// Return) [������]���� ó�� �����͸� �����Ѵ�.
	return	pret;
}

template<class S, class I> 
typename std::enable_if<is_iterator<I>::value, int>::type _Xappend_iterator(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ I _First, _In_ I _Last)
{
	// 1) [������_����]�� ��ִ´�.
	COUNT_T*	pCount = (COUNT_T*)_Source->TEMPLATE _append_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeof(COUNT_T));

	// Declare)
	COUNT_T iCount	 = 0;

	// 3) [������]���� ��ִ´�.
	for(; _First!=_Last; ++_First, ++iCount)
	{
		_Source->TEMPLATE _append<typename I::value_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA *_First);
	}

	// 3) ������ ���� ��ġ�� ������ ��ִ´�.
	*pCount	 = iCount;

	// Return) 
	return	iCount;
}

template <class S, class T>
typename std::enable_if<is_memcopy_able<typename T::value_type>::value, T>::type
_Xextract_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData<=0)
	{
		return	container;
	}

	// 2) [������_����]��ŭ vector�� Resize�� �Ѵ�.
	container.resize(countData);

	// 3) [������_����]��ŭ ��°�� ����
	_Source->TEMPLATE _extract_bytes(_CGD_BOUND_INFO_PASS _CGD_COMMA countData*sizeof(typename T::value_type), &container.front());

	// Return) 
	return	container;
}

template <class S, class T>
typename std::enable_if<!is_memcopy_able<typename T::value_type>::value, T>::type
_Xextract_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData<=0)
	{
		return	container;
	}

	// 2) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.push_back(_Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS));
	}

	// Return) 
	return	container;
}

template <class S, class T>
T _Xextract_container_CGPTR_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData<=0)
	{
		return	container;
	}

	// 2) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS);

		// - �߰�
		container.push_back(std::move(pObject));
	}

	// Return) 
	return	container;
}

template <class S, class T>
T _Xextract_container_CGOWN_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData<=0)
	{
		return	container;
	}

	// 2) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = MAKE_OWN<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS);

		// - �߰�
		container.push_back(std::move(pObject));
	}

	// Return) 
	return	container;
}

template <class S, class T>
T _Xextract_container_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData=_Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		return	container;
	}
	
	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.push_back(_Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS));
	}

	// Return) 
	return	container;
}

template <class S, class T>
T _Xextract_container_CGPTR_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;
	
	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		return	container;
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS);

		// - �߰�
		container.push_back(std::move(pObject));
	}

	// Return) 
	return	container;
}

template <class S, class T>
T _Xextract_container_CGOWN_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;
	
	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		return	container;
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = MAKE_OWN<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS);

		// - �߰�
		container.push_back(std::move(pObject));
	}

	// Return) 
	return	container;
}

template <class S, class T>
T _Xextract_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		return	container;
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.insert(_Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS));
	}

	// Return) 
	return	container;
}

template <class S, class T>
T _Xextract_CGPTR_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T		countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		return	container;
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS);

		// - �߰�
		container.insert(std::move(pObject));
	}

	// Return) 
	return	container;
}

template <class S, class T>
T _Xextract_CGOWN_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T		countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		return	container;
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = MAKE_OWN<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _Source->TEMPLATE _extract<typename T::value_type>(_CGD_BOUND_INFO_PASS);

		// - �߰�
		container.insert(std::move(pObject));
	}

	// Return) 
	return	container;
}

template <class S, class T>
typename std::enable_if<is_memcopy_able<typename T::value_type>::value, T>::type
_Xfront_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ vector�� Resize�Ѵ�.
	container.resize(countData);

	// 4) [������_����]��ŭ ��°�� �о���δ�.
	_Source->_copy_buffer(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset, countData*sizeof(T::value_type), &container.front());

	// 5) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset+countData*sizeof(typename T::value_type);

	// Return) 
	return	container;
}

template <class S, class T>
typename std::enable_if<!is_memcopy_able<typename T::value_type>::value, T>::type
_Xfront_container_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 4) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.push_back(_RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset));
	}

	// 5) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template <class S, class T>
T _Xfront_CGPTR_vector(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 4) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.push_back(std::move(pObject));
	}

	// 5) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template <class S, class T>
T _Xfront_CGOWN_vector(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ vector�� Reserve�Ѵ�.
	container.reserve(countData);

	// 4) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = MAKE_OWN<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.push_back(std::move(pObject));
	}

	// 5) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}


template <class S, class T>
T _Xfront_container_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T		container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.push_back(_RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template <class S, class T>
T _Xfront_container_CGPTR_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T		container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.push_back(std::move(pObject));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template <class S, class T>
T _Xfront_container_CGOWN_list(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T		container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = MAKE_OWN<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.push_back(std::move(pObject));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template <class S, class T>
T _Xfront_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		container.insert(_RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template <class S, class T>
T _Xfront_CGPTR_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = NEW<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.insert(std::move(pObject));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template <class S, class T>
T _Xfront_CGOWN_set(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _Inout_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Create
		auto	pObject	 = MAKE_OWN<typename T::value_type::_pointer_type>();
		
		// - �б�
		pObject	 = _RH<typename T::value_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - �߰�
		container.insert(std::move(pObject));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template<class S, class T>
void* _Xprepend_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _Container)
{
	// 1) Begin/End Iterator
	auto	iter	 = _Container.begin();
	auto	iterEnd = _Container.end();

	// 2) [������]���� ��ִ´�.
	for(; iter!=iterEnd; ++iter)
	{
		// - Value�� ��ִ´�.
		_Source->TEMPLATE _prepend<typename T::mapped_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter->second);
		// _ Key�� ��ִ´�.
		_Source->TEMPLATE _prepend<typename T::key_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter->first);
	}

	// 3) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _prepend_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Container.size());

	// Return) 
	return	(typename T::mapped_type*)_Source->get_ptr();
}

template<class S, class T>
void* _Xappend_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const T& _Container)
{
	// 1) [����_����_��_������]�� �����´�.
	void*	pret = _Source->get_back_ptr();

	// 2) [������_����]�� ��ִ´�.
	_Source->TEMPLATE _append_general<COUNT_T>(_CGD_BOUND_INFO_PASS _CGD_COMMA (COUNT_T)_Container.size());

	// 3) [������]���� ��ִ´�.
	for(auto iter=_Container.begin(); iter!=_Container.end(); ++iter)
	{
		// _ Key�� ��ִ´�.
		_Source->TEMPLATE _append<typename T::key_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter->first);
		// - Value�� ��ִ´�.
		_Source->TEMPLATE _append<typename T::mapped_type>(_CGD_BOUND_INFO_PASS _CGD_COMMA iter->second);
	}

	// Return) 
	return	(typename T::mapped_type*)pret;
}

template<class S, class T, size_t X>
CGD::_RETURN_ARRAY<T,X> _Xextract_array(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	_RETURN_ARRAY<T,X>	arrayTemp;

	// 1) [������_������ ���� �о���δ�.]
	size_t	count	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) [������_����]�� X���� ũ�� Exception�� ������. (Overflow ����!)
	if(count>X) throw std::length_error("Array is too small [0] (" __FUNCTION__ ")");

	// 2) [������_����]��ŭ �о���δ�.
	for(size_t i=0; i<count; ++i)
	{
		arrayTemp.value[i]	 = _Source->TEMPLATE _extract<T>(_CGD_BOUND_INFO_PASS);
	}

	// Return) 
	return	arrayTemp;
}

template<class S>
CGD::buffer _Xextract_buffer(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source);

template<class S, class T>
T _Xextract_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		return	container;
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		auto	tempKey		 = _Source->TEMPLATE _extract<typename T::key_type>(_CGD_BOUND_INFO_PASS);
		auto	tempMapped	 = _Source->TEMPLATE _extract<typename T::mapped_type>(_CGD_BOUND_INFO_PASS);

		// _ Key�� ���� ��ִ´�.
		container.insert(std::make_pair(std::move(tempKey), std::move(tempMapped)));
	}

	// Return) 
	return	container;
}

template<class S, class T>
T _Xextract_CGPTR_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData	 = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		return	container;
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		auto	tempKey	 = _Source->TEMPLATE _extract<typename T::key_type>(_CGD_BOUND_INFO_PASS);

		// - Create
		auto	pObject	 = NEW<typename T::mapped_type::_pointer_type>();
		
		// - pop...
		pObject	 = _Source->TEMPLATE _extract<typename T::mapped_type>(_CGD_BOUND_INFO_PASS);

		// _ Key�� ���� ��ִ´�.
		container.insert(std::make_pair(std::move(tempKey), std::move(pObject)));
	}

	// Return) 
	return	container;
}

template<class S, class T>
T _Xextract_CGOWN_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source)
{
	// Declare) 
	T	container;

	// 1) [������_����]�� ����.
	COUNT_T	countData = _Source->TEMPLATE _extract<COUNT_T>(_CGD_BOUND_INFO_PASS);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if (countData==(COUNT_T(0)-1))
	{
		return	container;
	}

	// 2) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for (; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		auto	tempKey = _Source->TEMPLATE _extract<typename T::key_type>(_CGD_BOUND_INFO_PASS);

		// - Create
		auto	pObject = MAKE_OWN<typename T::mapped_type::_pointer_type>();

		// - pop...
		pObject = _Source->TEMPLATE _extract<typename T::mapped_type>(_CGD_BOUND_INFO_PASS);

		// _ Key�� ���� ��ִ´�.
		container.insert(std::make_pair(std::move(tempKey), std::move(pObject)));
	}

	// Return) 
	return	container;
}

template<class S, class T>
T _Xfront_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _In_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		auto	tempKey		 = _RH<typename T::key_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);
		auto	tempMapped	 = _RH<typename T::mapped_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		container.insert(std::make_pair(std::move(tempKey), std::move(tempMapped)));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}


template<class S, class T>
T _Xfront_CGPTR_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _In_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		auto	tempKey		 = _RH<typename T::key_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - Create
		auto	pObject	 = NEW<typename T::mapped_type::_pointer_type>();

		// - pop...
		pObject	 = _RH<typename T::mapped_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - Key�� ���� �߰��Ѵ�.
		container.insert(std::make_pair(std::move(tempKey), std::move(pObject)));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}

template<class S, class T>
T _Xfront_CGOWN_container_associative(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const S* _Source, _In_ int& _Offset)
{
	// 1) �ӽ÷� Offset (Rollback�ø� ���� ������ ���)
	int	tempOffset	 = _Offset;

	// Declare) 
	T	container;

	// 2) [������_����]�� ����.
	COUNT_T		countData	 = *(COUNT_T*)(_Source->get_ptr()+tempOffset);	tempOffset	+= sizeof(COUNT_T);

	// Check) countData�� 0���� ������ �׳� �����Ѵ�.
	if(countData==(COUNT_T(0)-1))
	{
		_Offset		 = tempOffset;
		return	container;
	}

	// 3) [������_����]��ŭ �о� �鿩 �����Ѵ�.
	for(; countData>0; countData--)
	{
		// - Key�� Value���� �о���δ�.
		auto	tempKey	 = _RH<typename T::key_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - Create
		auto	pObject	 = MAKE_OWN<typename T::mapped_type::_pointer_type>();

		// - pop...
		pObject	 = _RH<typename T::mapped_type>::_do(_CGD_BOUND_INFO_PASS _CGD_COMMA _Source, tempOffset);

		// - Key�� ���� �߰��Ѵ�.
		container.insert(std::make_pair(std::move(tempKey), std::move(pObject)));
	}

	// 4) Offset�� ������Ʈ�Ѵ�.
	_Offset	 = tempOffset;

	// Return) 
	return	container;
}



