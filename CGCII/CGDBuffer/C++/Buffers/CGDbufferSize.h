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
// Size Of Objects
//
//-----------------------------------------------------------------------------
#if defined(_SUPPORT_SIZE_OF)

namespace CGD
{


template <typename T> struct is_basic_type 
{
	static const bool value	 = !std::is_base_of<CGD::IBufferSerializable, T>::value
							&& !is_linear_container<T>::value
							&& !is_linear_container_with_reserve<T>::value
							&& !is_set_container<T>::value
							&& !is_associative_container<T>::value
							&& !is_associative_container<T>::value
							&& !std::is_pointer<T>::value
							&& !std::is_base_of<T, CGD::buffer>::value
							;
};

// 1) Base Types
template<class T> 
typename std::enable_if<is_basic_type<T>::value, size_t>::type
SizeOf(const T& /*_Object*/)
{
	return sizeof(T);
}

template<class T>
typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value, size_t>::type
SizeOf(const T& _Object)
{
	return	_Object.ProcessSerializeSizeOf();
}

template<class T>
typename std::enable_if<!std::is_base_of<CGD::IBufferSerializable, T>::value, size_t>::type
SizeOf(const std::basic_string<T>& _Object)
{
	return	sizeof(COUNT_T) + (_Object.size()+1) * sizeof(T);
}

// 2) Array Types
template<class T, size_t X>
typename std::enable_if<!is_string_type<T>::value, size_t>::type
SizeOf(const T(&_Object)[X])
{
	if(_Object!=nullptr)
	{
		size_t	size = 0;
		
		size		+= sizeof(COUNT_T);

		auto* iter	 = _Object;
		auto* iterEnd = _Object + X;

		for(;iter!=iterEnd; ++iter)
		{
			size	+= SizeOf(*iter);
		}

		return	size;
	}
	else
	{
		return sizeof(COUNT_T);
	}
}

template<>
inline size_t SizeOf<tm>(const tm& /*_Object*/)
{
	return sizeof(DATETIME);
}


#if defined(_SYSTEMTIME_) || defined(_MINWINBASE_)
template<>
inline size_t SizeOf<SYSTEMTIME>(const SYSTEMTIME& /*_Object*/)
{
	return sizeof(DATETIME);
}
#endif

#ifdef _CGD_TIME
template<>
inline size_t SizeOf<TIME::LOCAL::time_point>(const TIME::LOCAL::time_point& /*_Object*/)
{
	return sizeof(DATETIME);
}

template<>
inline size_t SizeOf<TIME::SYSTEM::time_point>(const TIME::SYSTEM::time_point& /*_Object*/)
{
	return sizeof(DATETIME);
}

template<>
inline size_t SizeOf<TIME::_POINT>(const TIME::_POINT& /*_Object*/)
{
	return sizeof(DATETIME);
}
#endif

template<class T>
inline size_t SizeOf(const CGD::text<T>& _Object)
{
	if (_Object.p != nullptr)
	{
		const T* object = _Object.p;
		for (; *object != NULL; ++object);

		return (reinterpret_cast<const char*>(object) - reinterpret_cast<const char*>(_Object.p));
	}
	else
	{
		return	0;
	}
}

// 3) Pointer Type
template<class T>
typename std::enable_if<is_string_type<T>::value, size_t>::type
SizeOf(const T* _Object)
{
	if (_Object != nullptr)
	{
		const T* object = _Object;
		for(; *object!=NULL; ++object);

		return sizeof(COUNT_T) + (reinterpret_cast<const char*>(object) - reinterpret_cast<const char*>(_Object)) + sizeof(T);
	}
	else
	{
		return	sizeof(COUNT_T);
	}
}

template<class T>
typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value, size_t>::type
SizeOf(const T* _Object)
{
	if (_Object!=nullptr)
	{
		return	_Object->ProcessSerializeSizeOf();
	}
	else
	{
		return	sizeof(COUNT_T);
	}
}

template<class T>
typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value, size_t>::type
SizeOf(const CGPTR<T>& _Object)
{
	if(_Object.exist())
	{
		return	_Object->ProcessSerializeSizeOf();
	}
	else
	{
		return	sizeof(COUNT_T);
	}
}

template<class T>
typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value, size_t>::type
SizeOf(const CGOWN<T>& _Object)
{
	if (_Object.exist())
	{
		return	_Object->ProcessSerializeSizeOf();
	}
	else
	{
		return	sizeof(COUNT_T);
	}
}

template<class T>
typename std::enable_if<!std::is_base_of<CGD::IBufferSerializable, T>::value && std::is_base_of<CGD::buffer, T>::value, size_t>::type
SizeOf(const T& _Object)
{
	if (_Object.buf!=nullptr)
	{
		return	sizeof(uint32_t) + _Object.len;
	}
	else
	{
		return	sizeof(uint32_t);
	}
}

template<class T>
typename std::enable_if<std::is_base_of<CGD::IBufferSerializable, T>::value, size_t>::type
SizeOf(const CGD::SKIP& _Object)
{
	return	_Object.m_skip;
}

template<class T>
typename std::enable_if<!std::is_base_of<CGD::IBufferSerializable, T>::value && is_linear_container<T>::value, size_t>::type
SizeOf(const T& _Object)
{
	size_t	size = 0;

	size += sizeof(COUNT_T);

	for (const auto& iter : _Object)
	{
		size += SizeOf(iter);
	}

	return	size;
}

template<class T>
typename std::enable_if<!std::is_base_of<CGD::IBufferSerializable, T>::value && is_linear_container_with_reserve<T>::value, size_t>::type
SizeOf(const T& _Object)
{
	size_t	size = 0;

	size += sizeof(COUNT_T);

	for (const auto& iter : _Object)
	{
		size += SizeOf(iter);
	}

	return	size;
}

template<class T>
typename std::enable_if<!std::is_base_of<CGD::IBufferSerializable, T>::value && is_set_container<T>::value, size_t>::type
SizeOf(const T& _Object)
{
	size_t	size = 0;

	size += sizeof(COUNT_T);

	for (const auto& iter : _Object)
	{
		size += SizeOf(iter);
	}

	return	size;
}

template<class T>
typename std::enable_if<!std::is_base_of<CGD::IBufferSerializable, T>::value && is_associative_container<T>::value, size_t>::type
SizeOf(const T& _Object)
{
	size_t	size = 0;

	size += sizeof(COUNT_T);

	for (const auto& iter : _Object)
	{
		size += SizeOf(iter.first);
		size += SizeOf(iter.second);
	}

	return	size;
}

// 4) Tuple
template<class T>
inline size_t SizeOf(const std::tuple<T>& _Tuple)
{
	return SizeOf(std::get<0>(_Tuple));
}
template<class T, class... TREST>
inline size_t SizeOf(const std::tuple<T, TREST...>& _Tuple)
{
	size_t	size	 = 0;

	size	+= SizeOf(std::get<0>(_Tuple));
	size	+= SizeOf((const std::tuple<TREST...>&)_Tuple);

	return	size;
}


}

#endif
