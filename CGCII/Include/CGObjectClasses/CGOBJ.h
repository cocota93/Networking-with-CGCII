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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
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
 @brief		ICGReferenceable를 상속받은 객체로 지역변수나 전역변수와 같이 정적 객체로 선언하도록 해주는 클래스이다.
 @todo		
 @ref		
 @details	\n
 ICGReferenceable를 상속받은 객체로 지역변수나 전역변수와 같이 정적 객체로 선언하도록 해주는 클래스이다.
 ProcessDispose함수를 아무런 작업을 하지 않도록 정의해 놓았다.

*/
//-----------------------------------------------------------------------------
#ifdef _SUPPORT_VARIODIC_TEMPLATE_PARAMETER
template <class TOBJECT>
class CGOBJ :
	public	TOBJECT
{
public:
	CGOBJ()	{}
	//! @brief 인자를 가진 생성자
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
	//! @brief 복사 생성자
	CGOBJ(const TOBJECT& p_rObject) : TOBJECT(p_rObject) {}

	//! @brief 인자가 1개인 생성자
	template <typename TA>	
	CGOBJ(TA a) : TOBJECT(a) {}
	//! @brief 인자가 2개인 생성자
	template <typename TA, typename TB>
	CGOBJ(TA a, TB b) : TOBJECT(a, b) {}
	//! @brief 인자가 3개인 생성자
	template <typename TA, typename TB, typename TC>
	CGOBJ(TA a, TB b, TC c) : TOBJECT(a, b, c) {}
	//! @brief 인자가 4개인 생성자
	template <typename TA, typename TB, typename TC, typename TD>
	CGOBJ(TA a, TB b, TC c, TD d) : TOBJECT(a, b, c, d)	{}
	//! @brief 인자가 5개인 생성자
	template <typename TA, typename TB, typename TC, typename TD, typename TE>
	CGOBJ(TA a, TB b, TC c, TD d, TE e) : TOBJECT(a, b, c, d, e) {}
	//! @brief 인자가 6개인 생성자
	template <typename TA, typename TB, typename TC, typename TD, typename TE, typename TF>
	CGOBJ(TA a, TB b, TC c, TD d, TE e, TF f) : TOBJECT(a, b, c, d, e, f) {}
	//! @brief 인자가 7개인 생성자
	template <typename TA, typename TB, typename TC, typename TD, typename TE, typename TF, typename TG>
	CGOBJ(TA a, TB b, TC c, TD d, TE e, TF f, TG g) : TOBJECT(a, b, c, d, e, f, g) {}
	//! @brief 인자가 8개인 생성자
	template <typename TA, typename TB, typename TC, typename TD, typename TE, typename TF, typename TG, typename TH>
	CGOBJ(TA a, TB b, TC c, TD d, TE e, TF f, TG g, TH h) : TOBJECT(a, b, c, d, e, f, g, h) {}

public:
	virtual	void	ProcessDispose() override {}

};
#endif
