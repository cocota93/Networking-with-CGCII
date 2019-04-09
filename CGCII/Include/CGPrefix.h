//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                             CG Object Classes                             *
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


//----------------------------------------------------------------------------
// CGCII afxwin Prefix
// 
// �� ������ MFC�� ����� �� stdafx.h ������ "afxwin.h"�� include �ϱ�����
// Include ����� �Ѵ�.
// �� ������ include�� Microsof C++ Core Guide lines�� �������� �ʿ��� �����̴�.
// 
// afxwin.h�� ��ũ���� min()�� max()�� ��ø���� ���� ������ �ذ��ϱ� ���� ���̴�. 
// 
//    1) NOMINMAX�� afxwin.h�� Include �Ǳ� ���� ������ afxwin.h�� min()�� 
//       max()�� ����ȭ�Ѵ�.
//    2) ���� ��ũ�� min()/max()�� ��ü�� �Լ��� �� min()�� max()�� �����Ѵ�.
// 
//----------------------------------------------------------------------------
// Debug)
#if defined(_MSC_VER)
	#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC
		#define _INC_MALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif
#endif

#ifndef NOMINMAX
	#define NOMINMAX
#endif

#if !defined(min) & !defined(_FUNCTION_MIN)
	#define	_FUNCTION_MIN

	template<class VALUE>
	const VALUE& min(const VALUE& _a, const VALUE& _b)
	{
		return	(_a>_b) ? _b : _a;
	}
#endif

#if !defined(max) & !defined(_FUNCTION_MAX)
	#define	_FUNCTION_MAX

	template<class VALUE>
	const VALUE& max(const VALUE& _a, const VALUE& _b)
	{
		return	(_a>_b) ? _a : _b;
	}
#endif
