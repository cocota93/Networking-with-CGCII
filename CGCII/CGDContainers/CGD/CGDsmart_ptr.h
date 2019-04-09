//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 6.1 / Release 2012.05.28                        *
//*                                                                           *
//*                           Data Template Classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangducks@gmail.com          *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                           http://www.CGDK.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGD::smart_ptr
// 
// 1. CGD::smart_ptr란..
//    1) 기본적인 동작은 STL의 tr1::shared_ptr과 동일하다.
//    2) 다만 tr1의 shared_ptr은 weak_ptr, auto_ptr과 연동되게 되어 있지만
//       이것은 그런 기능이 없다.
//    3) 만약 tr1::shared_ptr<T>을 쓸수 있다면 굳이 이것을 쓸 필요가 없을 것이다.
//    4) 이것은 단지 이전 버전에서 tr1을 기본으로 제공해 주지 않는 곳에서도
//       컴파일이 가능하도록 하기 위해서 지원해 주는 것이다.
//
//
//-----------------------------------------------------------------------------
#include "CGD/CGDDefinitions.h"

namespace CGD
{

template <typename TREF>
class smart_ptr
{
// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:	
			typedef	smart_ptr<TREF>	_mytype;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			smart_ptr()													{	m_ref=0;}
			smart_ptr(TREF* _Ref)										{	m_ref=_Ref; m_count=new int(1);}
			~smart_ptr()												{	reset();}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) 기본적인 조작함수들
			void				reset()									{	if(m_ref==0) return; int value=--(*m_count);if(value==0) { delete m_ref; delete m_count;} m_ref=0;}
			void				reset(const _mytype& _Right)			{	reset(); m_ref=_Right.m_ref; m_count=_Right.m_count; ++(*m_count);}
			void				reset(TREF* _Ref)						{	reset(); m_ref=_Ref; m_count=new int(1);}

			bool				present() const							{	return m_ref!=0;}
			bool				empty() const							{	return m_ref==0;}
			int					use_count() const						{	if(empty()) return 0; return *m_count;}

	// 3) 연산자 Overriding
			_mytype&			operator=(const _mytype& _Right)		{	reset(_Right); return *this;}

			bool				operator==(const _mytype& _Right) const	{	return m_ref==_Right.m_ref;}
			bool				operator==(const TREF* _Right) const	{	return m_ref==_Right;}
			bool				operator!=(const _mytype& _Right) const	{	return m_ref!=_Right.m_ref;}
			bool				operator!=(const TREF* _Right) const	{	return m_ref!=_Right;}
			bool				operator>(const _mytype& _Right) const	{	return m_ref>_Right.m_ref;}
			bool				operator>(const TREF* _Right) const		{	return m_ref>_Right;}
			bool				operator>=(const _mytype& _Right) const	{	return m_ref>=_Right.m_ref;}
			bool				operator>=(const TREF* _Right) const	{	return m_ref>=_Right;}
			bool				operator<(const _mytype& _Right) const	{	return m_ref<_Right.m_ref;}
			bool				operator<(const TREF* _Right) const		{	return m_ref<_Right;}
			bool				operator<=(const _mytype& _Right) const	{	return m_ref<=_Right.m_ref;}
			bool				operator<=(const TREF* _Right) const	{	return m_ref<=_Right;}

			TREF*				operator->()							{	return m_ref;}
			TREF*				operator*()								{	return m_ref;}
			TREF*				operator*() const						{	return m_ref;}

								operator	TREF*() 					{	return m_ref;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			TREF*				m_ref;
			int*				m_count;

		#if defined(_MSC_VER)
			friend				smart_ptr<TREF>;
		#endif
};


}