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
// CGD::queue<T>
//
// 1. CGD::queue��!
//     CGD::array�� �⺻���� ���´� ��� vector�� ���������� ũ�Ⱑ �������̴�
//    �� ���� �������̶�� ���Ҽ� �ִ�. �� ������ vector�� ��� �������� �߻�
//    �ϴµ� �װ��� ������ ����.
//
//    - allocator�� �������� �ʴ´�.
//    - ������ ������������(stack)�� �����Ǿ� ��� �� �����Ҵ��� ���� �ʴ´�.
//    - reserve ���� ���� ������ �� ���� ���� ���� �� �����ؾ� �Ѵ�.
//    - ���� �ڵ����� ũ�Ⱑ Ŀ����(auto expend)�� ����.
//    - �������� ������ vector���� �ξ� ����ϸ� ���������� ����ص� ���ϰ� ����
//      ����. (�����Ҵ��� ���� �ʱ� ����)
//    - ������ vector�� �����ϴ�.
//
//
// 2. CGD::array�� ǥ�� �ؼ� ����
//    1) (o) Common Container Standard 
//    2) (o) Reversible Standard 
//    3) (o) Sequence Container Standard 
//    4) (x) Assosiative Container Standard 
//
//    (*) array�� list�� �ٸ��� random access operator�� ������ �ش�.
//
//
// 3. exception-safe level.
//    1) Strong guarantee.
//       - �ƹ��� Option�� �־����� ������ �⺻������ strong exception safe
//         guarantee�� �������ش�.
//      -  �� Operation�� ������ �� exception safeȮ���� ���� if������� �߰�
//         �ȴ�.
//
//    2) No guarantee (With _CGD_NO_EXCEPTION_GUARANTEE flag)
//       - flag�� �����ϸ� No Execption safe guarantee�� �������ټ� �ִ�.
//       - �߰������� exceptionó���� ���� �ʰų� Ȥ�� ���������� ���� �ӵ���
//         ���� ��� Exception Guarantee�� ������ ��� ������ ���� �߰�����
//         if������ ���ŵǾ� ���� �� ���� code�� ������ �ټ� �ִ�.
//       - �̸� ���� inlineó���Ǵ� Ȯ���� �þ�� ���� �ӵ������ �ٽ��̴�.
//
//
// 4. Option) CGD::array�� �ֿ� �ɼ�.
// 
//	  1) ����...
//
//    *����: �̷� �ּ������� comiler���� ������� ���ϸ� �ټ� �ֽ��ϴ�. ����...
//           ������ �ð��� ������ �̷� �ּ����� ������ �����ֽñ� �ٶ��ϴ�.
//
//
//-----------------------------------------------------------------------------
#include "CGD/CGDDefinitions.h"
#include <stdexcept>

namespace CGD
{

template <typename TDATA, typename TCONTAINER=circular<TDATA> >
class queue
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type			Contain�� ��� ������ ��.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
//
// ----------------------------------------------------------------------------
public:
	typedef TCONTAINER								container_type;
	typedef typename TCONTAINER::value_type			value_type;
	typedef typename TCONTAINER::size_type			size_type;
	typedef typename TCONTAINER::reference			reference;
	typedef typename TCONTAINER::const_reference	const_reference;

	// Rebinder) 
	template<typename TOTHER_DATA, typename TOTHER_CONTAINER>
	struct rebind
	{
		typedef queue<TOTHER_DATA, TOTHER_CONTAINER> other;
	};


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			queue()		{}
	explicit queue(const TCONTAINER& _Container) : m_container(_Container)	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Push/Pop (���� �ٽ�)
			void		push(const value_type& _Val)			{	m_container.push_back(_Val);}
			void		pop()									{	m_container.pop_front();}

	// 2) ���� ��� �Լ�.
			reference	front()									{	return m_container.front();}
			const_reference	front() const						{	return m_container.front();}

	// 3) State�Լ�.
			bool		empty() const							{	return m_container.empty();}
			size_type	size() const							{	return m_container.size();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			TCONTAINER	m_container;

};


}