//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Memory Classes                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// Chosanghyun's Game Basic Definitions
//-----------------------------------------------------------------------------
// 1) Assert
#include <cstdarg>
#include <cassert>


// ----------------------------------------------------------------------------
//
// Assert
//
// ----------------------------------------------------------------------------
#ifdef _DEBUG
#define	_USE_CGASSERT
#endif

// 1) ASSERT
#ifdef _USE_CGASSERT
	#define	CGASSERT(equation, value)				assert(equation);	if(!(equation))	{ return value;}
	#define	CGASSERT_TRACE(equation, value, state)	assert(equation);	if(!(equation))	{ state; return value;}
	#define	CGASSERT_ERROR(equation)				assert(equation);
	#define	CGASSERT_ERROR_TRACE(equation, state)	assert(equation);	if(!(equation))	{ state;}
	#define	CGASSERT_ERROR_CRITICAL					assert(false);
#else
	#define	CGASSERT(equation, value)
	#define	CGASSERT_TRACE(equation, value, string)
	#define	CGASSERT_ERROR(equation)
	#define	CGASSERT_ERROR_TRACE(equation, string)
	#define	CGASSERT_ERROR_CRITICAL
#endif
