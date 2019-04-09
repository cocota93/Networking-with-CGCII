//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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
// Definitions for String
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <string>
#include <cwchar>
#include <locale>
#include <codecvt>
#include "Shlwapi.h"
#if defined(_MSC_VER)
	#pragma warning(disable:28313)
	#include <tchar.h>
	#pragma warning(default:28131)
#endif

typedef	char		CHAR8_T;
typedef	wchar_t		CHAR16_T;

typedef	std::basic_string<CHAR8_T, std::char_traits<CHAR8_T>, std::allocator<CHAR8_T>>		_STRING8;
typedef	std::basic_string<CHAR16_T, std::char_traits<CHAR16_T>, std::allocator<CHAR16_T>>	_STRING16;


#if !defined(_MSC_VER)

#define _TRUNCATE	((size_t)-1)

#define _wcsicmp(_String1, _String2)									wcsicmp(_String1, _String2)
#define wcscpy_s(_Destination, _SizeInWords, _Source)					wcscpy(_Destination, _Source)

#define sprintf_s(_Buffer, _BufferCount, _Format, ...)					sprintf(_Buffer, _Format, __VA_ARGS__)
#define	swprintf_s(_Buffer, _BufferCount, _Format, ...)					swprintf(_Buffer, _Format, __VA_ARGS__)

#define	_snwprintf_s(_Buffer, _BufferCount, _Format, ...)				swprintf(_Buffer, _Format, __VA_ARGS__)

inline int _vsnprintf_s(char* const _Buffer, size_t const _BufferCount, size_t const _MaxCount, char const* const _Format, va_list _ArgList)
{
	return vsprintf(_Buffer, _Format, _ArgList);
}
inline int _vsnwprintf_s(wchar_t* const _Buffer, size_t const _BufferCount, size_t const _MaxCount, wchar_t const* const _Format, va_list _ArgList)
{
	return vswprintf(_Buffer, _Format, _ArgList);
}

// 임시
inline int wcstombs_s(
	size_t*			_PtNumOfCharConverted,
	CHAR8_T*		_Dst,
	size_t			_DstSizeInBytes,
	CHAR16_T const* _Src,
	size_t			_MaxCountInBytes
	)
{
	return	0;
}

inline int mbstowcs_s(
	size_t*			_PtNumOfCharConverted,
	CHAR16_T*		_DstBuf,
	size_t			_SizeInWords,
	CHAR8_T const*	_SrcBuf,
	size_t			_MaxCount
	)
{
	return	0;
}

#endif


#if !defined(_USE_CHAR_STRING) && !defined(_USE_WCHAR_STRING)
	#define	_USE_WCHAR_STRING
#endif

#if defined(_USE_CHAR_STRING)
	typedef	CHAR8_T				_CHAR;
	typedef	CHAR16_T			_CHAR_SUB;
	#define _STD_TO_STRING		std::to_string

	#define	__CGTEXT(quote)		quote
	#define	__CGTEXT_SUB(quote)	L##quote

	#define CGSPRINTF			wsprintfA
	#define CGSPRINTF_S			sprintf_s
	#define CGSNPRINTF_S		_snprintf_s
	#define	CGSTRCPY			strcpy
	#define	CGSTRCPY_S			strcpy_s
	#define	CGSTRCMP			strcmp
	#define	CGSTRCMP_S			strcmp_s
	#define	CGSTRICMP			_stricmp
	#define	CGSTRICMP_S			_strnicmp
	#define	CGSTRLEN			strlen
	#define	CGSTRLEN_S			strnlen
	#define	CGSTRCAT			strcat
	#define	CGSTRCAT_S			strcat_s
	#define	CGVSPRINTF_S		_vsnprintf_s

	#define CGSPRINTF_SUB		wsprintfW
	#define CGSPRINTF_S_SUB		swprintf_s
	#define CGSNPRINTF_S_SUB	_snwprintf_s 
	#define	CGSTRCPY_SUB		wcscpy
	#define	CGSTRCPY_S_SUB		wcscpy_s
	#define	CGSTRCMP_SUB		wcscmp
	#define	CGSTRCMP_S_SUB		wcsncmp
	#define	CGSTRICMP_SUB		_wcsicmp
	#define	CGSTRICMP_S_SUB		_wcsnicmp
	#define	CGSTRLEN_SUB		wcslen
	#define	CGSTRLEN_S_SUB		wcsnlen
	#define	CGSTRCAT_SUB		wcscat
	#define	CGSTRCAT_S_SUB		wcscat_s
	#define	CGVSPRINTF_S_SUB	_vsnwprintf_s

	#define	CGITOSTR			_itos
	#define	CGITOSTR_S			_itos_s
	#define	CGI64TOSTR			_i64tos
	#define	CGI64TOSTR_S		_i64tos_s
	#define	CGUI64TOSTR			_ui64tos
	#define	CGUI64TOSTR_S		_ui64tos_s
	#define	CGITOSTR_SUB		_itow
	#define	CGITOSTR_S_SUB		_itow_s
	#define	CGI64TOSTR_SUB		_i64tow
	#define	CGI64TOSTR_S_SUB	_i64tow_s
	#define	CGUI64TOSTR_SUB		_ui64tow
	#define	CGUI64TOSTR_S_SUB	_ui64tos_s

	#define	CGATOI				atoi
	#define	CGATOI64			_atoi64
	#define	CGATOI_SUB			_wtoi
	#define	CGATOI64_SUB		_wtoi64


	#define	CGOUTPUTDEBUGSTRING	OutputDebugStringA
#elif defined(_USE_WCHAR_STRING)
	typedef	CHAR16_T			_CHAR;
	typedef	CHAR8_T				_CHAR_SUB;
	#define _STD_TO_STRING		std::to_wstring

	#define	__CGTEXT(quote)		L##quote
	#define	__CGTEXT_SUB(quote)	quote

	#define CGSPRINTF			wsprintfW
	#define CGSPRINTF_S			swprintf_s
	#define CGSNPRINTF_S		_snwprintf_s 
	#define	CGSTRCPY			wcscpy
	#define	CGSTRCPY_S			wcscpy_s
	#define	CGSTRCMP			wcscmp
	#define	CGSTRCMP_S			wcsncmp
	#define	CGSTRICMP			_wcsicmp
	#define	CGSTRICMP_S			_wcsnicmp
	#define	CGSTRLEN			wcslen
	#define	CGSTRLEN_S			wcsnlen
	#define	CGSTRCAT			wcscat
	#define	CGSTRCAT_S			wcscat_s
	#define	CGVSPRINTF_S		_vsnwprintf_s

	#define CGSPRINTF_SUB		wsprintfA
	#define CGSPRINTF_S_SUB		sprintf_s
	#define CGSNPRINTF_S		_snwprintf_s 
	#define CGSNPRINTF_S_SUB	_snprintf_s
	#define	CGSTRCPY_SUB		strcpy
	#define	CGSTRCPY_S_SUB		strcpy_s
	#define	CGSTRCMP_SUB		strcmp
	#define	CGSTRCMP_S_SUB		strcmp_s
	#define	CGSTRICMP_SUB		_stricmp
	#define	CGSTRICMP_S_SUB		_strnicmp
	#define	CGSTRLEN_SUB		strlen
	#define	CGSTRLEN_S_SUB		strnlen
	#define	CGSTRCAT_SUB		strcat
	#define	CGSTRCAT_S_SUB		strcat_s
	#define	CGVSPRINTF_S_SUB	_vsnprintf_s

	#define	CGITOSTR			_itow
	#define	CGITOSTR_S			_itow_s
	#define	CGI64TOSTR			_i64tow
	#define	CGI64TOSTR_S		_i64tow_s
	#define	CGUI64TOSTR			_ui64tow
	#define	CGUI64TOSTR_S		_ui64tow_s
	#define	CGITOSTR_SUB		_itos
	#define	CGITOSTR_S_SUB		_itos_s
	#define	CGI64TOSTR_SUB		_i64tos
	#define	CGI64TOSTR_S_SUB	_i64tos_s
	#define	CGUI64TOSTR_SUB		_ui64tos
	#define	CGUI64TOSTR_S_SUB	_ui64tos_s

	#define	CGATOI				_wtoi
	#define	CGATOI64			_wtoi64
	#define	CGATOI_SUB			atoi
	#define	CGATOI64_SUB		_atoi64


	#define	CGOUTPUTDEBUGSTRING	OutputDebugStringW
#else
	#error "CGCII String Set is NOT Defined"
#endif

typedef	std::basic_string<_CHAR, std::char_traits<_CHAR>, std::allocator<_CHAR>>				_STRING;
typedef	std::basic_string<_CHAR_SUB, std::char_traits<_CHAR_SUB>, std::allocator<_CHAR_SUB>>	_STRING_SUB;


// String) 
struct STRING_BUFFER
{
	_CHAR	strBuffer[1024];
};

#define	_CGTEXT(quote)		__CGTEXT(quote)
#define	_CGTEXT_SUB(quote)	__CGTEXT_SUB(quote)

#define	STRCMP				_tcscmp
#define	STRLEN				_tcslen

#define	STRCPY				_tcscpy
#define	STRCPY_S			_tcscpy_s
#define	STRCAT				_tcscat
#define	STRCAT_S			_tcscat_s

#define	ITOSTR				_itot
#define	ITOSTR_S			_itot_s

#define	I64TOSTR			_i64tot
#define	I64TOSTR_S			_i64tot_s

#define	UI64TOSTR			_ui64tot
#define	UI64TOSTR_S			_ui64tot_s

#define	SPRINTF				_stprintf
#define	SPRINTF_S			_stprintf_s
#define	VSPRINTF			_vstprintf
#define	VSPRINTF_S			_vstprintf_s

#define	ATOI				_tstoi
#define	ATOI64				_tstoi64

#define	ATOF				_tstof

#ifdef _UNICODE
#define	TSTRING				_STRING16
#else
#define	TSTRING				_STRING8
#endif

#if _MSC_VER>=_MSC_VER_2015
	#define _CGFUNCTION			_CGTEXT("(") __FUNCTION__ _CGTEXT(")")
#else
	#define _CGFUNCTION			_CGTEXT("(") _CGTEXT(__FUNCTION__) _CGTEXT(")")
#endif


#define	_TO_CGSTRING_P(a)	_CGTEXT(#a)
#define	_TO_CGSTRING(a)		_TO_CGSTRING_P(a)

namespace std
{
	typedef	TSTRING		tstring;
}

inline size_t WCS_TO_MBS(_Out_writes_opt_z_(_MaxCountDest) CHAR8_T * _Dest, _In_ size_t _MaxCountDest, _In_z_ const CHAR16_T* _Source, _In_ size_t _MaxCountSource)
{
	//return std::wcstombs(_Dest, _Source, _MaxCountDest); NO_WARNING(_MaxCountSource);

	size_t	tempReturn	 = (size_t)-1;

	wcstombs_s(&tempReturn, _Dest, _MaxCountDest, _Source, _MaxCountSource);

	return	tempReturn;
}

inline size_t MBS_TO_WCS(_Out_writes_opt_z_(_MaxCountDest) CHAR16_T* _Dest, _In_ size_t _MaxCountDest, _In_z_ const CHAR8_T* _Source, _In_ size_t _MaxCountSource)
{
	//return std::mbstowcs(_Dest, _Source, _MaxCountDest);

	size_t	tempReturn	 = 0;

	mbstowcs_s(&tempReturn, _Dest, _MaxCountDest, _Source, _MaxCountSource);

	return	tempReturn;
}

inline _CHAR* CONVERT_STRING(_In_z_ const _CHAR_SUB* _strSource, _CHAR* _strDest, size_t _Size=1024)
{
	// Check) 
	RETURN_IF(_strSource==nullptr, nullptr);

	#if defined(_USE_CHAR_STRING)
	WCS_TO_MBS(_strDest, _Size, _strSource, _Size);
	#elif defined(_USE_WCHAR_STRING)
	MBS_TO_WCS(_strDest, _Size, _strSource, _Size);
	#endif

	// Return) 
	return	_strDest;
}

inline _CHAR* CONVERT_STRING(_In_z_ const _CHAR_SUB* _strSource, STRING_BUFFER& _strBuffer, size_t _Size=1024)
{
	// Check) 
	RETURN_IF(_strSource==nullptr, nullptr);

	#if defined(_USE_CHAR_STRING)
	WCS_TO_MBS(_strBuffer.strBuffer, _Size, _strSource, _Size);
	#elif defined(_USE_WCHAR_STRING)
	MBS_TO_WCS(_strBuffer.strBuffer, _Size, _strSource, _Size);
	#endif

	// Return) 
	return	_strBuffer.strBuffer;
}

inline _CHAR_SUB* CONVERT_STRING(_In_z_ const _CHAR* _strSource, _CHAR_SUB* _strDest, size_t _Size=1024)
{
	// Check) 
	RETURN_IF(_strSource==nullptr, nullptr);

	#if defined(_USE_CHAR_STRING)
	MBS_TO_WCS(_strDest, _Size, _strSource, _Size);
	#elif defined(_USE_WCHAR_STRING)
	WCS_TO_MBS(_strDest, _Size, _strSource, _Size);
	#endif

	// Return) 
	return	_strDest;
}

inline _STRING CONVERT_STRING(_In_ const _STRING_SUB& _strSource)
{
	static	std::wstring_convert<std::codecvt_utf8<CHAR16_T>> converter;

	// Return) 
	return	converter.from_bytes(_strSource);;
}

inline _STRING_SUB CONVERT_STRING(_In_ const _STRING& _strSource)
{
	static	std::wstring_convert<std::codecvt_utf8<CHAR16_T>> converter;

	// Return) 
	return	converter.to_bytes(_strSource);
}

#define	MAX_FORMAT_STRING_LENGTH	2048

#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
inline _STRING8 CGFormat(_In_z_ const CHAR8_T* _strMessage)
{
	return	_STRING8(_strMessage);
}

inline _STRING16 CGFormat(_In_z_ const CHAR16_T* _strMessage)
{
	return	_STRING16(_strMessage);
}

template <class... TARGS>
_STRING8 CGFormat(_In_z_ const char* _Format, TARGS... _Args)
{
	// Declare) 
	char	strMessage[MAX_FORMAT_STRING_LENGTH] = { 0 };

	// 1) Generate Trace Message
	_snprintf_s(reinterpret_cast<char*>(strMessage), MAX_FORMAT_STRING_LENGTH, _TRUNCATE, _Format, _Args...);

	// 3) Trace를 건다.
	return	_STRING8(strMessage);
}

template <class... TARGS>
_STRING16 CGFormat(_In_z_ const wchar_t* _Format, TARGS... _Args)
{
	// Declare) 
	wchar_t	strMessage[MAX_FORMAT_STRING_LENGTH] = { 0 };

	// 1) Generate Trace Message
	_snwprintf_s(reinterpret_cast<wchar_t*>(strMessage), MAX_FORMAT_STRING_LENGTH, _TRUNCATE, _Format, _Args...);

	// 3) Trace를 건다.
	return	_STRING16(strMessage);
}


#else
inline _STRING8 CGFormat(_In_z_ const char* _Format, ...)
{
	// Declare) 
	va_list	ap;

	// 1) valist 
	va_start(ap, _Format);

	// Declare) 
	char	strMessage[MAX_FORMAT_STRING_LENGTH];

	// 2) Generate Trace Message
	_vsnprintf_s(reinterpret_cast<char*>(strMessage), MAX_FORMAT_STRING_LENGTH, _TRUNCATE, _Format, ap);

	// 3) Va_End
	va_end(ap);

	// Return)
	return	_STRING8(strMessage);
}

inline _STRING16 CGFormat(_In_z_ const wchar_t* _Format, ...)
{
	// Declare) 
	va_list	ap;

	// 1) valist 
	va_start(ap, _Format);

	// Declare) 
	wchar_t	strMessage[MAX_FORMAT_STRING_LENGTH];

	// 2) Generate Trace Message
	_vsnwprintf_s(reinterpret_cast<wchar_t*>(strMessage), MAX_FORMAT_STRING_LENGTH, _TRUNCATE, _Format, ap);

	// 3) Va_End
	va_end(ap);

	// Return)
	return	_STRING16(strMessage);
}
#endif
