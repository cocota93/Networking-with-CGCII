/**
 @file	C:\ProejctA\CGDK8(for C++)\Include\CGObjectClasses\CGNEW.h

 @brief	Declares the cgnew class.
 */

#pragma once
 //-----------------------------------------------------------------------------
 //
 // 
 //
 //-----------------------------------------------------------------------------
#if defined(_USE_CREATE_FACTORY_FOR_ALL_OBJECT)
	#define		REFERENCEABLE_RELEASER				NCGReferenceable<TOBJECT>
	#define		REFERENCEABLE_RELEASER_INIT(param)	,NCGReferenceable<TOBJECT>(param)
#else
	#define		REFERENCEABLE_RELEASER		ICGReferenceable::Delete
	#define		REFERENCEABLE_RELEASER_INIT(param)
#endif


//-----------------------------------------------------------------------------
//
// 
//
//-----------------------------------------------------------------------------
#include <type_traits>

template <class TOBJECT, class... TARGS>
std::tuple<TOBJECT*, TARGS...> MAKE_CREATE_PARAMETERS(TARGS&&... _args)
{
	return std::tuple<TOBJECT*, TARGS...>(nullptr, std::forward<TARGS>(_args)...);
}

template<class TOBJECT, class T>
CGPTR<TOBJECT> _CGNEW_TUPLE_BEGIN(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA _In_ const std::tuple<T>& /*_Tuple*/) 
{
	return	_CGNEW<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}

template<class TOBJECT, class T, class... TREST>
CGPTR<TOBJECT> _CGNEW_TUPLE_BEGIN(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA _In_ const std::tuple<T, TREST...>& _Tuple) 
{
	return	_CGNEW_TUPLE<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA (const std::tuple<TREST...>&)_Tuple);
}

template<class TOBJECT, class T, class... TREST>
CGPTR<TOBJECT> _CGNEW_TUPLE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA _In_ const std::tuple<T, TREST...>& _Tuple) 
{
	return	_CGNEW_TUPLE<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA (const std::tuple<TREST...>&)_Tuple, std::get<0>(_Tuple));
}

template<class TOBJECT, class T, class... TREST, class... TARGS>
CGPTR<TOBJECT> _CGNEW_TUPLE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA _In_ const std::tuple<T, TREST...>& _Tuple, TARGS&&... _args) 
{
	return	_CGNEW_TUPLE<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA (const std::tuple<TREST...>&)_Tuple, std::forward<TARGS>(_args)..., std::get<0>(_Tuple));
}

template<class TOBJECT, class T, class... TARGS>
CGPTR<TOBJECT> _CGNEW_TUPLE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA _In_ const std::tuple<T>& _Tuple, TARGS&&... _args) 
{
	return	_CGNEW<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_args)..., std::get<0>(_Tuple));
}

class DEBUG_INFO_SETTER
{
public:
	DEBUG_INFO_SETTER(const char* _DebugInfo_Filename, int _DebugInfo_Line) : m_DebugInfo_Filename(_DebugInfo_Filename), m_DebugInfo_Line(_DebugInfo_Line) {}

	template <class TOBJECT>
	CGPTR<TOBJECT>	operator =(CGPTR<TOBJECT>& _rhs) const NOEXCEPT					{ CGNEW_DEBUG_INFO_SET(_rhs, m_DebugInfo_Filename, m_DebugInfo_Line);return _rhs; }

	template <class TOBJECT>
	TOBJECT*		operator =(TOBJECT* _rhs) const NOEXCEPT						{ CGNEW_DEBUG_INFO_SET(_rhs,m_DebugInfo_Filename, m_DebugInfo_Line); return _rhs; }

	template <class TOBJECT, class... TARGS>
	CGPTR<TOBJECT>	operator =(std::tuple<TOBJECT*, TARGS...> _rhs) const NOEXCEPT	{	return	_CGNEW_TUPLE_BEGIN<TOBJECT>(m_DebugInfo_Filename, m_DebugInfo_Line, _rhs);}

public:
	const char*		m_DebugInfo_Filename;
	int				m_DebugInfo_Line;
};


//-----------------------------------------------------------------------------
//
// CGPTR<TOBJECT> NEW_CREATE<TOBJECT>(TOBJECT* p)
//
//-----------------------------------------------------------------------------
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER

template <class TOBJECT, class... TARGS>
TOBJECT* NEW_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _Args)
{
	class OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _Nested_Args) : TOBJECT(std::forward<TARGS>(_Nested_Args)...) REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING)	{}
		virtual ~OBJECT_CREATE()	{}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_Args)...);
	#else
		pObject	 = new OBJECT_CREATE(std::forward<TARGS>(_Args)...);
	#endif
	#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line); 

	// Return)
	return	pObject;
}

#else

template <class TOBJECT>
TOBJECT* NEW_CREATE(CGNEW_DEBUG_INFO_PARAMETERS)
{
	class OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS) : TOBJECT() REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING) 	{}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
	#else
		pObject	 = new OBJECT_CREATE();
	#endif
	#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line); 

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA>
TOBJECT* NEW_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a)
{
	class OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& _a) : TOBJECT(std::forward<TA>(_a)) REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING)	{}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA a);
	#else
		pObject	 = new OBJECT_CREATE(std::forward<TA>(a));
	#endif
	#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line); 

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB>
TOBJECT* NEW_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b)
{
	class OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& _a, TB&& _b) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b)) REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING)	{}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b));
	#else
		pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b));
	#endif
	#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line); 

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB, typename TC>
TOBJECT* NEW_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c)
{
	class OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& _a, TB&& _b, TC&& _c) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b), std::forward<TC>(_c)) REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING)	{}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c));
	#else
		pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c));
	#endif
	#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line); 

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD>
TOBJECT* NEW_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d)
{
	class OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& _a, TB&& _b, TC&& _c, TD&& _d) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b), std::forward<TC>(_c), std::forward<TD>(_d)) REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING)	{}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d));
	#else
		pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d));
	#endif
	#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line); 

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD, typename TE>
TOBJECT* NEW_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d, TE&& e)
{
	class OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& _a, TB&& _b, TC&& _c, TD&& _d, TE&& _e) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b), std::forward<TC>(_c), std::forward<TD>(_d), std::forward<TE>(_e)) REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING)	{}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e));
	#else
		pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e));
	#endif
	#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line); 

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD, typename TE, typename TF>
TOBJECT* NEW_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d, TE&& e, TF&& f)
{
	class OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& _a, TB&& _b, TC&& _c, TD&& _d, TE&& _e, TF&& _f) : TOBJECT(std::forward<TA>(_a), std::forward<TA>(_b), std::forward<TA>(_c), std::forward<TA>(_d), std::forward<TA>(_e), std::forward<TA>(_f)) REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING)	{}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e), std::forward<TF>(f));
	#else
		pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e), std::forward<TF>(f));
	#endif
	#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line); 

	// Return)
	return	pObject;
}
#endif


//-----------------------------------------------------------------------------
//
// void FREE<TOBJECT>(TOBJECT* p)
//
//-----------------------------------------------------------------------------
// Prototype)
template <class TOBJECT> class NCGPoolable;

template <class TOBJECT>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, void>::type
	FREE(TOBJECT* p)
{
	TOBJECT::Free(p);
}

template <class TOBJECT>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, void>::type 
	FREE(TOBJECT* p)
{
	delete	p;
}


//-----------------------------------------------------------------------------
//
// void _CGNEW_RAW<TOBJECT, TARGS...>(_Args...)
//
//-----------------------------------------------------------------------------
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER

template <class TOBJECT, class... TARGS>
CGPTR<TOBJECT> _CGNEW_RAW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _Args)
{
	class OBJECT_CREATE : public TOBJECT, public ICGReferenceable::Delete
	{
	public:
				OBJECT_CREATE(TARGS&&... _Nested_Args) : TOBJECT(std::forward<TARGS>(_Nested_Args)...) {}
		virtual ~OBJECT_CREATE()	{}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

#pragma push_macro("new")
#undef new
#ifdef _USE_DEBUG_NEW
	pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(std::forward<TARGS>(_Args)...);
#else
	pObject	 = new OBJECT_CREATE(std::forward<TARGS>(_Args)...);
#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Return)
	return	pObject;
}

#else

template <class TOBJECT>
CGPTR<TOBJECT> _CGNEW_RAW(CGNEW_DEBUG_INFO_PARAMETERS)
{
	class OBJECT_CREATE : public TOBJECT, public ICGReferenceable::Delete
	{
	public:
				OBJECT_CREATE() : TOBJECT() {}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

#pragma push_macro("new")
#undef new
#ifdef _USE_DEBUG_NEW
	pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE();
#else
	pObject	 = new OBJECT_CREATE();
#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA>
CGPTR<TOBJECT> _CGNEW_RAW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a)
{
	class OBJECT_CREATE : public TOBJECT, public ICGReferenceable::Delete
	{
	public:
				OBJECT_CREATE(TA&& _a) : TOBJECT(std::forward<TA>(_a)) {}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

#pragma push_macro("new")
#undef new
#ifdef _USE_DEBUG_NEW
	pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(std::forward<TA>(a));
#else
	pObject	 = new OBJECT_CREATE(std::forward<TA>(a));
#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB>
CGPTR<TOBJECT> _CGNEW_RAW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b)
{
	class OBJECT_CREATE : public TOBJECT, public ICGReferenceable::Delete
	{
	public:
				OBJECT_CREATE(TA&& _a, TB&& _b) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b)) {}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

#pragma push_macro("new")
#undef new
#ifdef _USE_DEBUG_NEW
	pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b));
#else
	pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b));
#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB, typename TC>
CGPTR<TOBJECT> _CGNEW_RAW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c)
{
	class OBJECT_CREATE : public TOBJECT, public ICGReferenceable::Delete
	{
	public:
				OBJECT_CREATE(TA&& _a, TB&& _b, TC&& _c) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b), std::forward<TC>(_c)) {}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

#pragma push_macro("new")
#undef new
#ifdef _USE_DEBUG_NEW
	pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c));
#else
	pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c));
#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD>
CGPTR<TOBJECT> _CGNEW_RAW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d)
{
	class OBJECT_CREATE : public TOBJECT, public ICGReferenceable::Delete
	{
	public:
				OBJECT_CREATE(TA&& _a, TB&& _b, TC&& _c, TD&& _d) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b), std::forward<TC>(_c), std::forward<TD>(_d)) {}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

#pragma push_macro("new")
#undef new
#ifdef _USE_DEBUG_NEW
	pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d));
#else
	pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d));
#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD, typename TE>
CGPTR<TOBJECT> _CGNEW_RAW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d, TE&& e)
{
	class OBJECT_CREATE : public TOBJECT, public ICGReferenceable::Delete
	{
	public:
				OBJECT_CREATE(TA&& _a, TB&& _b, TC&& _c, TD&& _d, TE&& _e) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b), std::forward<TC>(_c), std::forward<TD>(_d), std::forward<TE>(_e)) {}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

#pragma push_macro("new")
#undef new
#ifdef _USE_DEBUG_NEW
	pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e));
#else
	pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e));
#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Return)
	return	pObject;
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD, typename TE, typename TF>
CGPTR<TOBJECT> _CGNEW_RAW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d, TE&& e, TF&& f)
{
	class OBJECT_CREATE : public TOBJECT, public ICGReferenceable::Delete
	{
	public:
				OBJECT_CREATE(TA&& _a, TB&& _b, TC&& _c, TD&& _d, TE&& _e, TF&& _f) : TOBJECT(std::forward<TA>(_a), std::forward<TB>(_b), std::forward<TC>(_c), std::forward<TD>(_d), std::forward<TE>(_e), std::forward<TF>(_f)) {}
		virtual ~OBJECT_CREATE() {}
	};

	// Declare)
	TOBJECT*	pObject	 = nullptr;

#pragma push_macro("new")
#undef new
#ifdef _USE_DEBUG_NEW
	pObject	 = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e), std::forward<TF>(f));
#else
	pObject	 = new OBJECT_CREATE(std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e), std::forward<TF>(f));
#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Return)
	return	pObject;
}

#endif


//-----------------------------------------------------------------------------
//
// void _CGNEW<TOBJECT, TARGS...>(_Args...)
//
//-----------------------------------------------------------------------------
// Case) 'NCGPoolable<T>' inherited
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER

template <class TOBJECT, class... TARGS>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type 
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _Args)
{
	return	TOBJECT::Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_Args)...);
}

#else

template <class TOBJECT>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS)
{
	return	TOBJECT::Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}

template <class TOBJECT, class TA>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a)
{
	return	TOBJECT::Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a));
}

template <class TOBJECT, class TA, class TB>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b)
{
	return	TOBJECT::Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b));
}

template <class TOBJECT, class TA, class TB, class TC>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c)
{
	return	TOBJECT::Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c));
}

template <class TOBJECT, class TA, class TB, class TC, class TD>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d)
{
	return	TOBJECT::Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d));
}

template <class TOBJECT, class TA, class TB, class TC, class TD, class TE>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d, TE&& e)
{
	return	TOBJECT::Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e));
}

template <class TOBJECT, class TA, class TB, class TC, class TD, class TE, class TF>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d, TE&& e, TF&& f)
{
	return	TOBJECT::Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e), std::forward<TF>(f));
}
#endif


// Case) No 'NCGPoolable<T>' inherited
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER

template <class TOBJECT, class... TARGS>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _Args)
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	// Return) 
	return	NEW_CREATE<TOBJECT, TARGS...>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_Args)...);
}

#else

template <class TOBJECT>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	// Return) 
	return	NEW_CREATE<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}

template <class TOBJECT, typename TA>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a)
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	// Return) 
	return	NEW_CREATE<TOBJECT, TA>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a));
}

template <class TOBJECT, typename TA, typename TB>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b)
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	// Return) 
	return	NEW_CREATE<TOBJECT, TA, TB>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b));
}

template <class TOBJECT, typename TA, typename TB, typename TC>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c)
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	// Return) 
	return	NEW_CREATE<TOBJECT, TA, TB, TC>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c));
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d)
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	// Return) 
	return	NEW_CREATE<TOBJECT, TA, TB, TC, TD>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d));
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD, typename TE>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d, TE&& e)
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	// Return) 
	return	NEW_CREATE<TOBJECT, TA, TB, TC, TD, TE>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e));
}

template <class TOBJECT, typename TA, typename TB, typename TC, typename TD, typename TE, typename TF>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type
_CGNEW(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TA&& a, TB&& b, TC&& c, TD&& d, TE&& e, TF&& f)
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	// Return) 
	return	NEW_CREATE<TOBJECT, TA, TB, TC, TD, TE, TF>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TA>(a), std::forward<TB>(b), std::forward<TC>(c), std::forward<TD>(d), std::forward<TE>(e), std::forward<TF>(f));
}


#endif
