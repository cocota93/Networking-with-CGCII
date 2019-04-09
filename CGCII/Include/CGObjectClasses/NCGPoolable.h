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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		NCGPoolable
 @brief		���� ��� ������ ��ü���� Ǯ�� ���� Ǯ ��� ��ü Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 IPoolable<TOBJECT>�� ��ӹ޾� Ǯ�� ����� �ʰ� ���ÿ� �ڽ��� Ǯ�� ��ü������ ���� ��� ������ ���� ���̴�.
 ���� Ǯ���� �Ҵ��� ���� �� ��ü������ ���� Ǯ���� �Ҵ���� �� �ְ� �Ҵ��� �����Ǹ� �� Ǯ�� �ٽ� ���ư���.
 �� �� NCGPoolable<T>�� ��ӹ����� NEW<T>()�� ����� ������ Ǯ���� �Ҵ���� �� �ִ�.

 NCGPoolable<T>�� ��ӹ����� ��������� 0�� �Ǿ� OnFinalRelease/ProcessDispose
 �Լ��� ȣ��Ǹ� �Ҵ���� Ǯ�� �ڵ������� ���ư����� ���۵Ǿ� �ִ�.

 �� ������ ���� ����� �� �ִ�.���� �����ϰԴ� NET<T>()�� ����� �Ҵ��� ���� �� �ִ�.
 �� ���� ��� �Լ��� Alloc()�Լ��� ����� �Ҵ��� �� �ִ�.

 NCGPoolable<T>�� ������ ������ ����.
 
 �ϴ� �Ʒ��� ���� ��ӹ޾� fooŬ������ �����ߴٸ�

 <pre>
 // foo��ü�� NCGPoolable�� ��ӹ޾� �����Ѵ�.
 class foo: public NCGPoolable<foo>
 {
 };
 </pre>

 �Ʒ��� ���� foo�� ���� ����Լ��� Alloc()�Լ��� ����� Ǯ���� �Ҵ���� �� �ִ�.
 <pre>
 // foo��ü�� Pool���� �Ҵ��Ѵ�.
 CGPTR<foo>  a = foo::Alloc();
 ...
 </pre>

 ������ �� ������ ����� �׳� NEW<T>()�Լ��� ����ϴ� ���̴�.
 <pre>
 // foo��ü�� Pool���� �Ҵ��Ѵ�.
 CGPTR<foo>  a = NEW<foo>();

 // Reference Count�� ���� �ڿ������� �Ҵ������� �����Ѵ�.
 a.reset();
 </pre>

 ��������� 0�� �Ǹ� �ڵ������� Ǯ�� �ǵ��ư��� ������ foo::Free()�Լ��� ȣ���� �ʿ�� ����.

 NCGPoolable�� ��ӹ����� OnFinalRelease�� �̹� ���ǵǾ� �ֱ� ������ OnFinalReleass()�� �������� �ʿ䰡 ����. 
 ���� �����Ǹ� �ϰ� �ȴٸ� �ݵ�� Free()�Լ��� ȣ���Ͽ� ������ ��ü�� Pool�� �ǵ��ư����� ���־�� �Ѵ�.

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
	//! @brief Ǯ ��ü�� ��´�. @return Ǯ ��ü ������
	static	CGPTR<CGFactory::CPoolObject<TOBJECT>> GetFactory()			{	return m_pPoolObject;}

	//! @brief Ǯ���� ��ü�� �Ҵ��Ѵ�. @return �Ҵ�� ��ü
	static	CGPTR<TOBJECT>		Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT)	{	return GetFactory()->Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);}
	//! @brief ��ü�� �ٽ� Ǯ�� �ݳ��Ѵ�. @param _pItem ��ȯ�� ��ü
	static	void				Free(_In_ TOBJECT* _pItem)				{	CGASSERT(_pItem!=0,); GetFactory()->Free(_pItem);}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief ��������� 0�� �� �� ȣ��Ǵ� �Լ�.
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
