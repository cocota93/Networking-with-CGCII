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

 @class		NCGPoolable
 @brief		정적 멤버 변수로 자체적인 풀을 가진 풀 대상 객체 클래스이다.
 @todo		
 @ref		
 @details	\n
 IPoolable<TOBJECT>를 상속받아 풀의 대상이 됨과 동시에 자신의 풀을 자체적으로 정적 멤버 변수로 가진 것이다.
 따라서 풀에서 할당을 받을 때 자체적으로 가진 풀에서 할당받을 수 있고 할당이 해제되면 그 풀로 다시 돌아간다.
 또 이 NCGPoolable<T>을 상속받으면 NEW<T>()를 사용해 간단히 풀에서 할당받을 수 있다.

 NCGPoolable<T>을 상속받으면 참조계수가 0이 되어 OnFinalRelease/ProcessDispose
 함수가 호출되면 할당받은 풀로 자동적으로 돌아가도록 제작되어 있다.

 은 다음과 같이 사용할 수 있다.가장 간단하게는 NET<T>()를 사용해 할당을 받을 수 있다.
 또 정적 멤버 함수인 Alloc()함수를 사용해 할당할 수 있다.

 NCGPoolable<T>의 사용법은 다음과 같다.
 
 일단 아래와 같이 상속받아 foo클래스를 정의했다면

 <pre>
 // foo객체를 NCGPoolable을 상속받아 정의한다.
 class foo: public NCGPoolable<foo>
 {
 };
 </pre>

 아래와 같이 foo의 정적 멤버함수인 Alloc()함수를 사용해 풀에서 할당받을 수 있다.
 <pre>
 // foo객체를 Pool에서 할당한다.
 CGPTR<foo>  a = foo::Alloc();
 ...
 </pre>

 하지만 더 간단한 방법은 그냥 NEW<T>()함수를 사용하는 것이다.
 <pre>
 // foo객체를 Pool에서 할당한다.
 CGPTR<foo>  a = NEW<foo>();

 // Reference Count를 통한 자연스러운 할당해제를 수행한다.
 a.reset();
 </pre>

 참조계수가 0이 되면 자동적으로 풀로 되돌아가기 때문에 foo::Free()함수를 호출할 필요는 없다.

 NCGPoolable을 상속받으면 OnFinalRelease가 이미 정의되어 있기 때문에 OnFinalReleass()를 재정의할 필요가 없다. 
 만약 재정의를 하게 된다면 반드시 Free()함수를 호출하여 생성된 객체가 Pool로 되돌아가도록 해주어야 한다.

*/
//-----------------------------------------------------------------------------
template <class TOBJECT>
class NCGPoolable :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						ICGPoolable<TOBJECT>,					// (I) IPoolable
	public						CGPool::_traits_has_pool				// (T) Traits
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			NCGPoolable();
	virtual	~NCGPoolable();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief 풀 객체를 얻는다. @return 풀 객체 포인터
	static	CGPTR<CGFactory::CPoolObject<TOBJECT>> GetFactory()			{	return m_pPoolObject;}

	//! @brief 풀에서 객체를 할당한다. @return 할당된 객체
	static	CGPTR<TOBJECT>		Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT)	{	return GetFactory()->Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);}
	//! @brief 객체를 다시 풀로 반납한다. @param _pItem 반환할 객체
	static	void				Free(_In_ TOBJECT* _pItem)				{	CGASSERT(_pItem!=0,); GetFactory()->Free(_pItem);}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 참조계수가 0이 될 때 호출되는 함수.
	virtual	void				ProcessDispose() override				{	Free((TOBJECT*)this);}


// ****************************************************************************
// Implementations) 
// ----------------------------------------------------------------------------
private:
	// 1) Static Instance
	static	CGOWN<CGFactory::CPoolObject<TOBJECT>> m_pPoolObject;

	// 2) Object
			CGPTR<CGFactory::CPoolObject<TOBJECT>>	m_pPool;

	// 3) Friend
			friend	CGFactory::CPoolObject<TOBJECT>;
};

template <class TOBJECT>
CGOWN<CGFactory::CPoolObject<TOBJECT>> NCGPoolable<TOBJECT>::m_pPoolObject	 = _CGNEW_RAW<CGFactory::CPoolObject<TOBJECT>>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL CGNEW_DEBUG_INFO_COMMA reinterpret_cast<const _CHAR*>(nullptr), true, eFACTORY_TYPE::DEFAULT);

template <class TOBJECT>
NCGPoolable<TOBJECT>::NCGPoolable()
{
}

template <class TOBJECT>
NCGPoolable<TOBJECT>::~NCGPoolable()
{
}

// Poolable template
template <class TOBJECT>
class POOLABLE : public TOBJECT, public NCGPoolable<POOLABLE<TOBJECT>>
{
};

// Case) 'NCGPoolable<T>' inherited
template <class TOBJECT>
typename std::enable_if<std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>&&>::type 
_CGPOOL_ALLOC()	
{
	return TOBJECT::Alloc();
}

// Case) No 'NCGPoolable<T>' inherited
template <class TOBJECT>
typename std::enable_if<!std::is_base_of<NCGPoolable<TOBJECT>, TOBJECT>::value, CGPTR<TOBJECT>>::type 
_CGPOOL_ALLOC()	
{
	// Check) TOBJECT must inherite class'ICGReferenceable'
	static_assert(std::is_base_of<ICGReferenceable, TOBJECT>::value, "CGObj: TOBJECT must inherite 'ICGReferenceable' class");

	return POOLABLE<TOBJECT>::Alloc();
}
