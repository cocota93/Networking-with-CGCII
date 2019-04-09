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
// 1. CGD::smart_ptr��..
//    1) �⺻���� ������ STL�� tr1::shared_ptr�� �����ϴ�.
//    2) �ٸ� tr1�� shared_ptr�� weak_ptr, auto_ptr�� �����ǰ� �Ǿ� ������
//       �̰��� �׷� ����� ����.
//    3) ���� tr1::shared_ptr<T>�� ���� �ִٸ� ���� �̰��� �� �ʿ䰡 ���� ���̴�.
//    4) �̰��� ���� ���� �������� tr1�� �⺻���� ������ ���� �ʴ� ��������
//       �������� �����ϵ��� �ϱ� ���ؼ� ������ �ִ� ���̴�.
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
	// 1) �⺻���� �����Լ���
			void				reset()									{	if(m_ref==0) return; int value=--(*m_count);if(value==0) { delete m_ref; delete m_count;} m_ref=0;}
			void				reset(const _mytype& _Right)			{	reset(); m_ref=_Right.m_ref; m_count=_Right.m_count; ++(*m_count);}
			void				reset(TREF* _Ref)						{	reset(); m_ref=_Ref; m_count=new int(1);}

			bool				present() const							{	return m_ref!=0;}
			bool				empty() const							{	return m_ref==0;}
			int					use_count() const						{	if(empty()) return 0; return *m_count;}

	// 3) ������ Overriding
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