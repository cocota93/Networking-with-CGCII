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

namespace CGFactory
{

//-----------------------------------------------------------------------------
/**

 @class		ICGObjectIdentifiable
 @brief		TLS를 사용하는 객체 풀 클래스이다.
 @todo		
 @ref		CGFatory::CPoolObject<T>, ICGPoolable
 @details	\n
 TLS를 사용한 객체 풀로 모든 기능은 CGFactory::CPool`Object<T>과 동일한다.
 다만 내부적으로 TLS를 사용해 다중 쓰레드에서 락을 최소화해 할당과 해제의 속도가 더 뛰어나다.
 하지만 더 많은 메모리를 소모하므로 용량에 민감할 경우 사용을 피하는 것이 좋다.

*/
//-----------------------------------------------------------------------------
template <class TOBJECT, class TCREATE=TOBJECT>
class CPoolObjectTLS : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGFactory,
	public						CGNameable::NString
{
// ****************************************************************************
// Definition)
// ----------------------------------------------------------------------------
public:
	typedef	std::function<void(TCREATE*)>	TFUNCTION;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CPoolObjectTLS(_In_opt_z_ const _CHAR* _strName=nullptr, _In_ int p_iTLSCacheSize=DEFAULT_POOL_TLS_CACH_SIZE, _In_ bool _bSustain=true, _In_ eFACTORY_TYPE _eFactoryType=eFACTORY_TYPE::POOL_USER);
	virtual	~CPoolObjectTLS();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief 풀 객체를 파괴한다. @return true 성공 @return false 실패 
	virtual	bool				Destroy() override;

	//! @brief _iAmount만큼의 객체를 미리 준비해 놓는다. @param _iAmount 준비할 수량 @return 실제 준비된 량
	virtual	size_t				Prepare(_In_ size_t _iAmount);
	//! @brief _iAmount만큼의 재고 객체를 해제한다. @param _iAmount 해제할 수량 @return 실제 해제된 량
	virtual	size_t				Shrink(_In_ size_t _iAmount);
	//! @brief 적절한 재고량을 계산해 재고량을 넘어서는 량에 대해서는 해제 처리하는 가비지 콜렉션 처리를 한다. @param _Level 레벨해제할 수량 @return 실제 해제된 량
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL);

	//! @brief 풀에서 객체를 할당을 요청한다. @return 할당된 객체
			TOBJECT*			Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief 풀에 객체를 반환한다. @param _Object 반환할 객체
			void				Free(_In_ TOBJECT* _Object);

	//! @brief 객체 당 메모리 크기를 얻는다. @return 객체 당 메모리 크기
	virtual	size_t				GetObjectSize() const override			{	return sizeof(TCREATE);}
	//! @brief 재고량을 얻는다. @return 재고량
	virtual	size_t				GetStackedCount() const override;
	//! @brief 최대 재고량을 얻는다. @return 최대 재고량
	virtual	int64_t				GetExistingLimits() const override		{	return m_statisticsObject.iExistingLimits;}

	//! @brief 풀의 형태를 얻는다. @return 풀의 형태
	virtual	eFACTORY_TYPE			GetFactoryType() const override		{	return m_statisticsObject.eFactoryType;}
	//! @brief 풀의 ID를 얻는다. @return 풀의 ID.
	virtual	int					GetFactoryID() const override			{	return m_statisticsObject.iFactoryID;}

	//! @brief 가비지콜렉션을 사용하는지 확인한다. @return true 가비지콜렉션 사용 @return false 가비지콜렉션 사용하지 않는다.
	virtual	bool				IsEnableSustain() const override		{	return m_bEnableSustain;}
	//! @brief 가비콜렉션 가능 여부를 설정한다. @param _bStatus 가비지콜렉션 동작 여부
	virtual	void				EnableSustain(_In_ bool _bStatus=true) override;

	//! @brief 새로운 객체를 할당할 때 호출될 함수를 설정한다. @param _pFunction 새로운 객체를 할당할 때 호출될 함수
			void				SetOnCreateNewFunction(_In_ const TFUNCTION& _pFunction);

	//! @brief 대입연산자(Assignment는 절때 쓰지 않는다.)
			void				operator=(const CPoolObjectTLS<TOBJECT, TCREATE>& /*_rhs*/) _DELETE;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// Definitions)
			struct STATISTICS_POOL;
			struct TLS_CACHE;
			struct STACK_BALANCE;

	//! @brief 객체를 생성하는 과정을 정의한다. @return 생성된 객체
	template <class TTOBJECT>
	typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
								ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS);
	template <class TTOBJECT>
	typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
								ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS);

	//! @brief 객체를 파괴시키는 과정을 정의한다. @param _Object 파괴할 객체
	template <class TTOBJECT>
	typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
								ProcessDestroyObject(_In_ TCREATE* _Object);
	template <class TTOBJECT>
	typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
								ProcessDestroyObject(_In_ TCREATE* _Object);

	//! @brief 객체의 생성을 요청한다. @return 생성된 객체
	virtual	TCREATE*			CreateObject(CGNEW_DEBUG_INFO_PARAMETERS);

	// 2) Chunk Create/Destroy
			TCREATE*			ProcessCreateChunk();
			void				ProcessDestroyChunk(_In_ TCREATE* p_rChunk);

	// 3) Chunk Pop/Push
			TCREATE*			ProcessPopChunk();
			void				ProcessPushChunk(_In_ TCREATE* p_pChunk);

	//! @brief 객체를 생성할 때 호출하는 함수 @param _Object 새로 생성한 객체
	virtual	void				OnCreateNew(TCREATE* /*_Object*/)	{}
	//! @brief 객체를 소멸할할 때 호출하는 함수 @param _Object 소멸할 객체
	virtual	void				OnDestroy(TCREATE* /*_Object*/)	{}

private:
	// 5) 재고 저장고들 (Garbage Stack)
			size_t				m_TLSIndex;
			size_t				m_sizeTLSCache;
			LOCKABLE<list<TLS_CACHE>>	m_listStackTLS;
			Interlocked_self_stack<TCREATE*>	m_stackCHUNK;

	// 6) Pool Sustainment를 위한 변수들
			int64_t				m_iAllocatedSmoothedAverage;
			int64_t				m_iAllocatedVariation;

	// 7) Hook Function
			TFUNCTION			m_fOnCreateNew;

	// 8) Enable Sustain
			bool				m_bEnableSustain;
};


}

#include "CGObjectClasses/CGFactoryPoolObjectTLS.inl"
