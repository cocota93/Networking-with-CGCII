//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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
//-----------------------------------------------------------------------------
// is_enable ...
//-----------------------------------------------------------------------------
// Is Poolable Type)
template <class A> class NCGPoolable;

#if defined(_MSC_VER)
	#pragma warning(disable:4250)
#endif

//-----------------------------------------------------------------------------
/**

 @class		CGOBJ
 @brief		ICGReferenceable�� ��ӹ��� ��ü�� ���������� ���������� ���� ���� ��ü�� �����ϵ��� ���ִ� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ICGReferenceable�� ��ӹ��� ��ü�� ���������� ���������� ���� ���� ��ü�� �����ϵ��� ���ִ� Ŭ�����̴�.
 ProcessDispose�Լ��� �ƹ��� �۾��� ���� �ʵ��� ������ ���Ҵ�.

*/
//-----------------------------------------------------------------------------
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template <class TOBJECT>
class CGOBJ :
	public	TOBJECT
{
public:
	CGOBJ()	{}
	//! @brief ���ڸ� ���� ������
	template <class T, class... TARGS>
	CGOBJ(T _First, TARGS... _Args) : TOBJECT(_First, _Args...)	{}

public:
	virtual	void	ProcessDispose() override {}
};
#else

template <class TOBJECT>
class CGOBJ :
	public	TOBJECT
{
public:
	CGOBJ()	{}
	//! @brief ���� ������
	CGOBJ(const TOBJECT& p_rObject) : TOBJECT(p_rObject) {}

	//! @brief ���ڰ� 1���� ������
	template <typename TA>	
	CGOBJ(TA a) : TOBJECT(a) {}
	//! @brief ���ڰ� 2���� ������
	template <typename TA, typename TB>
	CGOBJ(TA a, TB b) : TOBJECT(a, b) {}
	//! @brief ���ڰ� 3���� ������
	template <typename TA, typename TB, typename TC>
	CGOBJ(TA a, TB b, TC c) : TOBJECT(a, b, c) {}
	//! @brief ���ڰ� 4���� ������
	template <typename TA, typename TB, typename TC, typename TD>
	CGOBJ(TA a, TB b, TC c, TD d) : TOBJECT(a, b, c, d)	{}
	//! @brief ���ڰ� 5���� ������
	template <typename TA, typename TB, typename TC, typename TD, typename TE>
	CGOBJ(TA a, TB b, TC c, TD d, TE e) : TOBJECT(a, b, c, d, e) {}
	//! @brief ���ڰ� 6���� ������
	template <typename TA, typename TB, typename TC, typename TD, typename TE, typename TF>
	CGOBJ(TA a, TB b, TC c, TD d, TE e, TF f) : TOBJECT(a, b, c, d, e, f) {}
	//! @brief ���ڰ� 7���� ������
	template <typename TA, typename TB, typename TC, typename TD, typename TE, typename TF, typename TG>
	CGOBJ(TA a, TB b, TC c, TD d, TE e, TF f, TG g) : TOBJECT(a, b, c, d, e, f, g) {}
	//! @brief ���ڰ� 8���� ������
	template <typename TA, typename TB, typename TC, typename TD, typename TE, typename TF, typename TG, typename TH>
	CGOBJ(TA a, TB b, TC c, TD d, TE e, TF f, TG g, TH h) : TOBJECT(a, b, c, d, e, f, g, h) {}

public:
	virtual	void	ProcessDispose() override {}

};
#endif
