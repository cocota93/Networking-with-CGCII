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

 @class		CPoolObject
 @brief		객체의 할당과 해제의 효율을 향상시키기 위한 객체 풀
 @todo		
 @ref		ICGPoolable, NCGPoolable
 @details	\n
 객체의 동적 할당과 해제의 효율성을 높이기 위한 풀 객체이다.
 내부적으로 락프리로 동작하기 때문에 매우 고성능을 제공한다.

 풀의 대상 객체가 되려면 반드시 ICGPoolable<TOBJECT>를 상속받은 클래스어야한다.

 풀에 할당을 요구하면 먼저 가비지 스택를 먼저 검사한다. 만약 스택에 객체가 있을 경우 그것을 할당해준다.
 만약 스택에 객체가 하나도 없다면 새로 생성해서 할당해준다.
 할당해준 객체가 다시 돌아오게 되면 가비지 스택에 저장해 놓았다가 다음 할당 요구때 할당해준다.
 다만 너무 많은 객체가 가비지 스택에 존재할 경우 일정량을 해제해 적절한 수량을 유지한다.

 풀에서 객체를 할당하기 위해서는 Alloc()함수를 호출하며 할당 했던 객체를 해제하기 위해서는 Free()함수를 사용한다.
 Prepare()함수를 사용하면 미리 객체를 생성해놓을 수도 있다.
 Shrink()함수를 사용하면 쌓여있는 가비지들을 할당 해제할 수도 있다.

*/
//-----------------------------------------------------------------------------
template <class TOBJECT, class TCREATE=TOBJECT>
class CPoolObject : 
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
			CPoolObject(_In_opt_z_ const _CHAR* _strName=nullptr, _In_ bool _bSustain=true, _In_ eFACTORY_TYPE _eFactoryType=eFACTORY_TYPE::POOL_USER);
	virtual	~CPoolObject();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief 풀 객체를 파괴한다. @return true 성공 @return false 실패 
	virtual	bool				Destroy() override;

	//! @brief _iAmount만큼의 객체를 미리 준비해 놓는다. @param _iAmount 준비할 수량 @return 실제 준비된 량
	virtual	size_t				Prepare(_In_ size_t _iAmount) override;
	//! @brief _iAmount만큼의 재고 객체를 해제한다. @param _iAmount 해제할 수량 @return 실제 해제된 량
	virtual	size_t				Shrink(_In_ size_t _iAmount) override;
	//! @brief 적절한 재고량을 계산해 재고량을 넘어서는 량에 대해서는 해제 처리하는 가비지 콜렉션 처리를 한다. @param _Level 레벨해제할 수량 @return 실제 해제된 량
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL) override;

	//! @brief 풀에서 객체를 할당을 요청한다. @return 할당된 객체
			TOBJECT*			Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief 풀에 객체를 반환한다. @param _Object 반환할 객체
			void				Free(_In_ TOBJECT* _Object);

	//! @brief 객체 당 메모리 크기를 얻는다. @return 객체 당 메모리 크기
	virtual	size_t				GetObjectSize() const override			{	return sizeof(TCREATE);}
	//! @brief 재고량을 얻는다. @return 재고량
	virtual	size_t				GetStackedCount() const override		{	return m_stackObject.size();}
	//! @brief 최대 재고량을 얻는다. @return 최대 재고량
	virtual	int64_t				GetExistingLimits() const override		{	return m_statisticsObject.iExistingLimits;}

	//! @brief 풀의 형태를 얻는다. @return 풀의 형태
	virtual	eFACTORY_TYPE		GetFactoryType() const override			{	return m_statisticsObject.eFactoryType;}
	//! @brief 풀의 ID를 얻는다. @return 풀의 ID.
	virtual	int					GetFactoryID() const override			{	return m_statisticsObject.iFactoryID;}

	//! @brief 가비지콜렉션을 사용하는지 확인한다. @return true 가비지콜렉션 사용 @return false 가비지콜렉션 사용하지 않는다.
	virtual	bool				IsEnableSustain() const override		{	return m_bEnableSustain;}
	//! @brief 가비콜렉션 가능 여부를 설정한다. @param _bStatus 가비지콜렉션 동작 여부
	virtual	void				EnableSustain(_In_ bool _bStatus=true) override;

	//! @brief 새로운 객체를 할당할 때 호출될 함수를 설정한다. @param _pFunction 새로운 객체를 할당할 때 호출될 함수
			void				SetOnCreateNewFunction(_In_ const TFUNCTION& _pFunction);

private:
	//! @brief 대입연산자(Assignment는 절때 쓰지 않는다.)
	#if defined(_MSC_VER)
			void				operator=(const CPoolObject<TOBJECT, TCREATE>& /*_rhs*/) {	CGASSERT_ERROR(false);}
	#endif


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 객체를 생성하는 과정을 정의한다. @return 생성된 객체
	template <class TTOBJECT>
	typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
								ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS);
	template <class TTOBJECT>
	typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
								ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS);

	//! @brief 객체를 파괴시키는 과정을 정의한다. @param _Object 파괴시킬 객체
	template <class TTOBJECT>
	typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
								ProcessDestroyObject(_In_ TCREATE* _Object);
	template <class TTOBJECT>
	typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
								ProcessDestroyObject(_In_ TCREATE* _Object);

	//! @brief 객체의 생성을 요청한다. @return 생성된 객체
	virtual	TCREATE*			CreateObject(CGNEW_DEBUG_INFO_PARAMETERS);

	//! @brief 객체를 생성할 때 호출하는 함수 @param _Object 새로 생성한 객체
	virtual	void				OnCreateNew(_In_ TCREATE* /*_Object*/){}
	//! @brief 객체를 소멸할할 때 호출하는 함수 @param _Object 소멸할 객체
	virtual	void				OnDestroy(_In_ TCREATE* /*_Object*/)	{}
	
private:
	// 3) 재고 객체 Stack
			LOCKFREE_SELF_STACK<TCREATE*>	m_stackObject;

	// 4) Pool Sustainment를 위한 변수들
			int64_t				m_iAllocatedTermMax;
			int64_t				m_iAllocatedSmoothedAverage;
			int64_t				m_iAllocatedVariation;

	// 5) Hook Function
			TFUNCTION			m_fOnCreateNew;

	// 6) Enable Sustain
			bool				m_bEnableSustain;
};


template <class TOBJECT, class TCREATE>
CPoolObject<TOBJECT, TCREATE>::CPoolObject(_In_opt_z_ const _CHAR* _strName, bool _bSustain, eFACTORY_TYPE _eFactoryType) : 
	ICGFactory(),
	CGNameable::NString(_strName),
	m_iAllocatedTermMax(0),
	m_iAllocatedSmoothedAverage(0),
	m_iAllocatedVariation(0),
	m_fOnCreateNew(nullptr),
	m_bEnableSustain(_bSustain)
{
	// 1) Name을 정하지 않았을 경우 Object Factory의 Name을 기본으로 설정한다.
	if(_strName==nullptr)
	{
	#if defined(_MSC_VER)
		__if_exists(TCREATE::_GetStaticFactoryName)
		{
			SetName(TCREATE::_GetStaticFactoryName());
		}
		__if_not_exists(TCREATE::_GetStaticFactoryName)
		{
	#endif
			// Declare) 
			_CHAR	temp[MAX_NAME_LENGTH] = { 0 };

			// - 기본 이름 문자열을 만든다.
			CGSNPRINTF_S(temp, _TRUNCATE, _CGTEXT("%hs"), typeid(TCREATE).name());

			// - 기본 이름을 설정한다.
			SetName(temp);
	#if defined(_MSC_VER)
		}
	#endif
	}

	// 2) Factory Type이 Default로 설정할 경우 Factory Class에 따라 자동 설정한다.
	if(_eFactoryType==eFACTORY_TYPE::DEFAULT)
	{
		m_statisticsObject.eFactoryType = CGPool::_get_default_factory_type<TOBJECT>();
	}

	// 3) Factory Type을 설정한다.
	m_statisticsObject.eFactoryType = _eFactoryType;


	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Pool(%s) is created ") _CGFUNCTION, GetName());

	// 4) Factory Manager에 등록한다.
	RegisterFactory();
}

template <class TOBJECT, class TCREATE>
CPoolObject<TOBJECT, TCREATE>::~CPoolObject()
{
	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Pool(%s:%I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// Check) 존재하는 객체의 갯수는 0개여야 한다.
	CGASSERT_ERROR(m_statisticsObject.iExisting==0);

	// Check) 사용 중인 객체의 수가 0개이여야 한다.
	CGASSERT_ERROR(m_statisticsObject.iInUsing==0);

	// 1) Factory Manager에 등록해제한다.
	UnregisterFactory();
}

template <class TOBJECT, class TCREATE>
bool CPoolObject<TOBJECT, TCREATE>::Destroy()
{
	// 1) Hold한다.
	CGPTR<CPoolObject<TOBJECT, TCREATE>>	pHold(this);

	// 2) 최대 유지 갯수를 -1로 한다.
	m_statisticsObject.iExistingLimits	 = -1;

	// 3) Stack되어 있는 Object을 모두 지운다.
	TCREATE*	pObject;
	while((pObject = m_stackObject.pop()) != nullptr)
	{
		// - 객체를 파괴한다.
		ProcessDestroyObject<TCREATE>(pObject);
	}

	// Return)
	return	true;
}

template <class TOBJECT, class TCREATE>
void CPoolObject<TOBJECT, TCREATE>::SetOnCreateNewFunction(const TFUNCTION& _pFunction)
{
	m_fOnCreateNew	 = _pFunction;
}

template <class TOBJECT, class TCREATE>
size_t CPoolObject<TOBJECT, TCREATE>::Prepare(_In_ size_t _iAmount)
{
	// Check) Prepare할 수가 0보다는 커야한다.
	CGASSERT(_iAmount > 0, 0);

	// Check) 0보다 작거나 같으면 Prepare할꺼 같으면 그냥 끝낸다.
	RETURN_IF(_iAmount <= 0, 0);

	// 1) 임시로 사용할 List를 할당받는다.
	vector<TCREATE*>	vectorCreated;

	// 2) Reserve한다.
	vectorCreated.reserve(_iAmount);

	try
	{
		// 3) Prepare 수만큼 Loop를 돌면서 생성한다.
		for(; _iAmount>0; --_iAmount)
		{
			// Declare) 새로 생성한다.
			TCREATE*	pCreate = ProcessCreateObject<TCREATE>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL);

			// - 생성된 객체를 임시 버퍼에 짚어 넣는다.
			vectorCreated.push_back(pCreate);
		}

		// Trace) 
		CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d Objects is prepared on pool(%s) ") _CGFUNCTION, static_cast<int64_t>(vectorCreated.size()), GetName());
	}
	// Exception) 
	catch(...)
	{
		// Trace) 
		CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d objects is prepared on pool(%s)  [%I64d is failed]") _CGFUNCTION, static_cast<int64_t>(vectorCreated.size()), GetName(), static_cast<int64_t>(_iAmount));

		NO_EXCEPTION_BEGIN
		{
			// - Free되지 않고 남은 것들을 지운다.
			for (auto& iter : vectorCreated)
			{
				NO_EXCEPTION_BEGIN
				{
					ProcessDestroyObject<TCREATE>(iter);
				}
				NO_EXCEPTION_END
			}
		}
		NO_EXCEPTION_END
	}

	// 4) 평균값을 수정한다.
	m_iAllocatedSmoothedAverage	+= static_cast<int>(vectorCreated.size());

	// Statistics) In-Using수도 증가시켜준다.
	m_statisticsObject.iInUsing	+= static_cast<int64_t>(vectorCreated.size());

	// Statistics) 할당한 객체의 개수를 증가시킨다.
	m_statisticsObject.qwAlloc_Create	+= static_cast<int64_t>(vectorCreated.size());

	// 5) Free()함수를 사용해서 stack한다.
	for(auto& iter:vectorCreated)
	{
		Free(iter);
	}
	
	// Return) 성공!!
	return	vectorCreated.size();
}

template <class TOBJECT, class TCREATE>
size_t CPoolObject<TOBJECT, TCREATE>::Shrink(_In_ size_t _iAmount)
{
	// Case) Shrink Exceed
	if(_iAmount==-1)
	{
		_iAmount	 = static_cast<size_t>(m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits);
	}
	// Case) Shrink All
	else if(_iAmount==-2)
	{
		_iAmount	 = static_cast<int>(m_stackObject.size());
	}

	// Check) _iAmount가 1보다 작으면 그냥 끝낸다.
	RETURN_IF(_iAmount<1, 0);

	// 1) Hold한다.
	CGPTR<CPoolObject<TOBJECT, TCREATE>>	pHold(this);

	// 2) Shrink 갯수...
	size_t	iShrink	 = 0;

	// 3) Stack되어 있는 Object을 tempShrink만큼 지운다.
	for(; iShrink<_iAmount; ++iShrink)
	{
		// - Pop을 먼저한다.
		TCREATE* pObject=m_stackObject.pop();

		// Check) pObject가 nullptr이면 안된다.
		BREAK_IF(pObject==nullptr);

		// Statistics) 파괴된 Block을 하나 늘린다.
		++m_statisticsObject.qwFree_Delete;

		// - Object를 Destroy한다.
		ProcessDestroyObject<TCREATE>(pObject);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d(%I64d Requested) Stacked Objects are shrinked in pool(%s) ") _CGFUNCTION, static_cast<int64_t>(iShrink), (int64_t)_iAmount, GetName());

	// 4) 평균값을 수정.
	m_iAllocatedSmoothedAverage	-= iShrink;
	
	// Return) 성공!!
	return	iShrink;
}

template <class TOBJECT, class TCREATE>
void CPoolObject<TOBJECT, TCREATE>::Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level)
{
	// Check) No Systain이 true면 Sustain은 수행하지 않는다.
	RETURN_IF(m_bEnableSustain==false,);

	// Check) Destroy되었으면 Sustain을 수행하지 않는다.
	RETURN_IF(m_statisticsObject.iExistingLimits<0,);

	// 1) MaxStack을 계산한다.
	int64_t	iAllocatedMax	 = ((m_iAllocatedTermMax*9)>>3)+8;

	// 2) Stacked의 평균을 구한다.
	int64_t	iAllocatedSmoothedAverage	 = ((m_iAllocatedSmoothedAverage*896 + iAllocatedMax*128)>>10);

	// 3) Stacked의 표준편차를 구한다.
	int64_t	iAllocatedVariation			 = ((m_iAllocatedVariation*768+256*((iAllocatedSmoothedAverage>iAllocatedMax) ? (iAllocatedSmoothedAverage-iAllocatedMax) : (iAllocatedMax-iAllocatedSmoothedAverage))+1)>>10);

	// 4) Max Stack을 구한다.
	if(m_statisticsObject.iExistingLimits>=0)
	{
		m_statisticsObject.iExistingLimits = (iAllocatedSmoothedAverage+(iAllocatedVariation<<2));
	}

	// 5) 값을 넣는다.
	m_iAllocatedSmoothedAverage		 = iAllocatedSmoothedAverage;
	m_iAllocatedVariation			 = iAllocatedVariation;
	m_iAllocatedTermMax				 = m_statisticsObject.iInUsing;

	// Declare) 
	size_t	iShrinkAmount	 = 0;

	// 6) Shrink할 갯수를 얻는다.
	switch(_Level)
	{
	// - 최대갯수를 초과하는 객체수의 1/16만을 모두 제거한다.
	case	eFACTORY_SUSTAIN_TYPE::NORMAL:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>4);
			}
			break;
				
	// - 최대갯수를 초과하는 객체수의 1/4만을 모두 제거한다.
	case	eFACTORY_SUSTAIN_TYPE::HEAVY:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>2);
			}
			break;
				
	// - 최대갯수를 초과하는 객체 갯수 모두 만큼을 제거한다.
	case	eFACTORY_SUSTAIN_TYPE::EXCESS_ALL:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>(m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits);
			}
			break;

	// - Stack된 것은 모조리 제거한다.
	case	eFACTORY_SUSTAIN_TYPE::STACKED_ALL:
			{
				iShrinkAmount	 = GetStackedCount();
			}
			break;
	};


	// - 갯수만큼 Shrink한다.
	Shrink(iShrinkAmount);
}

template <class TOBJECT, class TCREATE>
TCREATE* CPoolObject<TOBJECT, TCREATE>::CreateObject(CGNEW_DEBUG_INFO_PARAMETERS)
{
	#pragma push_macro("new")
	#undef new
	#ifdef _USE_DEBUG_NEW
		return new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) TCREATE;
	#else
		return new TCREATE;
	#endif
	#pragma pop_macro("new")
}

template <class TOBJECT, class TCREATE>
template <class TTOBJECT>
typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
CPoolObject<TOBJECT, TCREATE>::ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// 1) 일단 새로 생성된다.
	TCREATE*	pObject	 = CreateObject(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);	// (여기서 Exception발생 가능.)

	// 2) Pool에 Setting한다. (여기서 Pool에 Reference Counting를 1증가시키게 된다.)
	pObject->m_pPool	 = this;

	try
	{
		// 3) 초기화
		if(m_fOnCreateNew!=nullptr)
		{
			m_fOnCreateNew(pObject);
		}

		// 4) Hook 함수 호출
		OnCreateNew(pObject);
	}
	catch(...)
	{
		NO_EXCEPTION_BEGIN
		{
			// - 객체를 지운다.
			delete	pObject;
		}
		NO_EXCEPTION_END

		// Reraise) 
		throw;
	}

	// Statistics) 현재 존재하는 객체의 수를 증가시킨다.
	++m_statisticsObject.iExisting;

	// Return) 성공!!
	return	pObject;
}

template <class TOBJECT, class TCREATE>
template <class TTOBJECT>
typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
CPoolObject<TOBJECT, TCREATE>::ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// 1) 일단 새로 생성된다.
	TCREATE*	pObject	 = CreateObject(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);	// (여기서 Exception발생 가능.)

	// 2) Reference Count를 1증가시킨다. 
	//      (m_pPool에 Setting하지 않으면 자체적으로 증가시킨다.)
	AddRef();

	try
	{
		// 3) 초기화
		if(m_fOnCreateNew!=nullptr)
		{
			m_fOnCreateNew(pObject);
		}

		// 4) Hook 함수 호출
		OnCreateNew(pObject);
	}
	catch(...)
	{
		NO_EXCEPTION_BEGIN
		{
			// - 객체를 지운다.
			delete	pObject;
		}
		NO_EXCEPTION_END

		// Reraise) 
		throw;
	}

	// Statistics) 현재 존재하는 객체의 수를 증가시킨다.
	++m_statisticsObject.iExisting;

	// Return) 성공!!
	return	pObject;
}

template <class TOBJECT, class TCREATE>
template <class TTOBJECT>
typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
CPoolObject<TOBJECT, TCREATE>::ProcessDestroyObject(_In_ TCREATE* _Object)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_Object != nullptr, );

	// Statistics) 현재 존재하는 객체의 수를 감소시킨다.
	--m_statisticsObject.iExisting;

	// 1) Hook 함수 호출
	NO_EXCEPTION_BEGIN
	{
		OnDestroy(_Object);
	}
	NO_EXCEPTION_END

	// 2) DestroyObject함수를 호출하여 Object를 지운다.
	NO_EXCEPTION_BEGIN
	{
		delete	_Object;
	}
	NO_EXCEPTION_END
}

template <class TOBJECT, class TCREATE>
template <class TTOBJECT>
typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
CPoolObject<TOBJECT, TCREATE>::ProcessDestroyObject(_In_ TCREATE* _Object)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_Object != nullptr, );

	// Statistics) 현재 존재하는 객체의 수를 감소시킨다.
	--m_statisticsObject.iExisting;

	// 1) Hook 함수 호출
	NO_EXCEPTION_BEGIN
	{
		OnDestroy(_Object);
	}
	NO_EXCEPTION_END

	// 2) DestroyObject함수를 호출하여 Object를 지운다.
	NO_EXCEPTION_BEGIN
	{
		delete	_Object;
	}
	NO_EXCEPTION_END

	// 3) Reference Count를 1감소시킨다.
	//    (m_pPool에 Setting되어 있지 않았다면 자체적으로 감소시킨다.)
	Release();
}

template <class TOBJECT, class TCREATE>
TOBJECT* CPoolObject<TOBJECT, TCREATE>::Alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Declare) 
	TCREATE*	pObject;

	// 1) 일단 head이 nullptr이면 새로 생성해서 보내준다.
	pObject	 = m_stackObject.pop();

	// 2) Stack된 것이 없다면 새로 만들어서 보낸다.
	if(pObject != reinterpret_cast<TCREATE*>(nullptr))
	{
		// Statistics) Stack된 것을 할당된 량 증가시킨다.
		++m_statisticsObject.qwAlloc_Stacked;
	}
	else
	{
		// - 새로 Object을 만든다.
		pObject	 = ProcessCreateObject<TCREATE>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

		// Statistics) 할당한 객체의 개수를 증가시킨다.
		++m_statisticsObject.qwAlloc_Create;
	}

	// 3) OnPoolAlloc()함수를 호출한다.
#if defined(_MSC_VER)
	__if_exists(TCREATE::OnObjectAlloc)
	{
		try
		{
			pObject->OnObjectAlloc();
		}
		catch(...)
		{
			NO_EXCEPTION_BEGIN
			{
				// Destroy
				ProcessDestroyObject<TCREATE>(pObject);
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
#endif

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _Filename, _Line);

	// Statistics) 사용 중인 객체의 수를 증가시킨다.
	int64_t	countUsing	 = ++m_statisticsObject.iInUsing;

	// Sustain) 최대 할당 수를 구한다.
	if(countUsing>m_iAllocatedTermMax)
	{
		// - 최대 할당수를  갱신한다.
		m_iAllocatedTermMax	 = countUsing;

		// - 사용중인 갯수가 최대할당치를 넘어설 경우 수정한다.
		if(countUsing>m_statisticsObject.iExistingLimits && m_statisticsObject.iExistingLimits>=0)
		{
			m_statisticsObject.iExistingLimits	 = static_cast<size_t>(((countUsing*9)>>3)+8);
		}
	} 

	// Check) 처음 할당받았을 때 Disuse는 반드시 false여야 한다.
	CGASSERT_ERROR(pObject->IsDisuse() == false);

	// Return) 성공!!
	return	pObject;
}

template <class TOBJECT, class TCREATE>
void CPoolObject<TOBJECT, TCREATE>::Free(_In_ TOBJECT* _Object)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_Object!=nullptr,);

	// Statistics) 사용 중인 객체의 수를 줄인다.
	--m_statisticsObject.iInUsing;

	// 1) OnFree함수 호출.
#if defined(_MSC_VER)
	__if_exists(TCREATE::OnObjectFree)
	{
		try
		{
			((TCREATE*)_Object)->OnObjectFree();
		}
		catch(...)
		{
			// Trace)
			CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Excp) CGFactory: Occure exception on delete Object(%s) ") _CGFUNCTION, GetName());

			NO_EXCEPTION_BEGIN
			{
				// Statistics) 파괴된 Block을 하나 늘린다.
				++m_statisticsObject.qwFree_Delete;
			}
			NO_EXCEPTION_END

			NO_EXCEPTION_BEGIN
			{
				// - 객체를 소멸시킨다.
				ProcessDestroyObject<TCREATE>((TCREATE*)_Object);
			}
			NO_EXCEPTION_END
		}
	}
#endif

	// 2) 최대 한계 Stack수보다 Stack된 Memory Block갯수가 많으면 할당해제한다.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits || _Object->IsDisuse())
	{
		// Statistics) 파괴된 Block을 하나 늘린다.
		++m_statisticsObject.qwFree_Delete;
		++m_statisticsObject.qwFree_Disuse;

		// - 객체를 바로 지운다.
		ProcessDestroyObject<TCREATE>(_Object);

		// Return) 끝낸다.
		return;
	}

	// 3) List에 추가한다.
	m_stackObject.push(_Object);

	// Statistics) Free;
	++m_statisticsObject.qwFree_Stacked;

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Object is freed in pool(%s) [Remained:%I64d] ") _CGFUNCTION, GetName(), static_cast<int64_t>(m_stackObject.size()));
}

template <class TOBJECT, class TCREATE>
void CPoolObject<TOBJECT, TCREATE>::EnableSustain(_In_ bool _bStatus)
{
	// Check) 
	RETURN_IF(_bStatus==m_bEnableSustain,);

	// 1) 상태를 바꾼다.
	m_bEnableSustain	 = _bStatus;
}


}
