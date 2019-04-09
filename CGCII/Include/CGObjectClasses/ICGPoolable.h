//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               Pool Classes                                *
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
/**

 @class		ICGPoolable
 @brief		풀의 대생 객체가 될수 있는 인터페이스 클래스
 @todo		
 @ref		NCGPoolable, CGFactory::CPoolObject<T>
 @details	\n
 CGFactory:CPoolObject<TOBJECT> 풀의 대상 객체가 되려면 반드시 ICGPoolable<T> 인터페이스 클래스를 상속받아야 한다.

*/
//-----------------------------------------------------------------------------
template <class TOBJECT>
class ICGPoolable : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CGD::SCGLIST_ENTRY<TOBJECT>,			// (@) SList
	virtual public				ICGReferenceable						//     Reference Counter.
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			ICGPoolable() : m_pNext(nullptr), m_pNext2(nullptr)			 {}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			TOBJECT*			m_pNext;
			TOBJECT*			m_pNext2;
};

#define	DEFAULT_POOLNAME(name)		static const _CHAR*	_GetStaticPoolName()	{	return _CGTEXT(#name);}
