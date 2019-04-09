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
namespace CGFactory
{

template <class TOBJECT, class TCREATE>
struct CPoolObjectTLS<TOBJECT, TCREATE>::STATISTICS_POOL
{
public:
			STATISTICS_POOL();
public:
			int64_t				statistics_Alloc;
			int64_t				statistics_Free;
			int64_t				iExistingLimits;
			int64_t				iExisting;
			int64_t				iUsing;
			int64_t				iAllocatedTermMax;

			void				operator+=(const STATISTICS_POOL& p_rhs);
};

template <class TOBJECT, class TCREATE>
CPoolObjectTLS<TOBJECT, TCREATE>::STATISTICS_POOL::STATISTICS_POOL() : 
	ICGFactory(),
	statistics_Alloc(0),
	statistics_Free(0),
	iExistingLimits(INT64_MAX),
	iExisting(0),
	iUsing(0),
	iAllocatedTermMax(0)
{
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::STATISTICS_POOL::operator+=(const STATISTICS_POOL& p_rhs)
{

	statistics_Alloc			+= p_rhs.statistics_Alloc;
	statistics_Free				+= p_rhs.statistics_Free;
	iExistingLimits				+= p_rhs.iExistingLimits;
	iExisting					+= p_rhs.iExisting;
	iUsing						+= p_rhs.iUsing;
	iAllocatedTermMax			+= p_rhs.iAllocatedTermMax;
}

template <class TOBJECT, class TCREATE>
struct CPoolObjectTLS<TOBJECT, TCREATE>::TLS_CACHE
{
public:
			TLS_CACHE();
public:
			void				push_local_chunk()				{	m_pChunk->m_pNext2=m_stackChunk;m_stackChunk=m_pChunk; reset();}
			TCREATE*			pop_local_chunk()				{	TCREATE* pChunk=m_stackChunk; m_stackChunk=pChunk->m_pNext2; return pChunk;}
			bool				is_exist_local_chunk() const	{	return m_stackChunk!=nullptr;}
			bool				is_empty_local_chunk() const	{	return m_stackChunk==nullptr;}
			bool				is_room_local_chunk() const		{	return m_statisticsPOOL.iExisting<m_statisticsPOOL.iExistingLimits;}
			bool				is_overflow_local_chunk() const	{	return m_statisticsPOOL.iExisting>m_statisticsPOOL.iExistingLimits;}
			void				reset()							{	m_pChunk=nullptr; m_iStacked=0;}
public:
			TCREATE*			m_pChunk;
			TCREATE*			m_stackChunk;

			int					m_iStacked;
			STATISTICS_POOL		m_statisticsPOOL;
};

template <class TOBJECT, class TCREATE>
CPoolObjectTLS<TOBJECT, TCREATE>::TLS_CACHE::TLS_CACHE() : 
	m_pChunk(nullptr),
	m_iStacked(0),
	m_stackChunk(nullptr)
{
}

template <class TOBJECT, class TCREATE>
CPoolObjectTLS<TOBJECT, TCREATE>::CPoolObjectTLS(_In_opt_z_ const _CHAR* _strName, int p_iTLSCacheSize, bool _bSustain, eFACTORY_TYPE _eFactoryType) : 
	ICGFactory(),
	CGNameable::NString(_strName),
	m_iAllocatedSmoothedAverage(0),
	m_iAllocatedVariation(0),
	m_sizeTLSCache(p_iTLSCacheSize),
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
			_CHAR	temp[MAX_NAME_LENGTH];

			// - 기본 이름 문자열을 만든다.
			CGSNPRINTF_S(temp, _TRUNCATE, _CGTEXT("%hs"), typeid(TCREATE).name());

			// - 기본 이름을 설정한다.
			SetName(temp);

	#if defined(_MSC_VER)
		}
	#endif
	}

	// 2) Factory Type을 설정한다.
	m_statisticsObject.eFactoryType	 = _eFactoryType;

	// 3) TLS를 할당한다.
	m_TLSIndex	 = TlsAlloc();

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: TLS pool(%s) is created ") _CGFUNCTION, GetName());

	// 5) Factory Manager에 등록한다.
	RegisterFactory();
}

template <class TOBJECT, class TCREATE>
CPoolObjectTLS<TOBJECT, TCREATE>::~CPoolObjectTLS()
{
	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: TLS pool(%s:%I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// Check) 사용 중인 객체의 수가 0개이여야 한다.
	CGASSERT_ERROR(m_statisticsObject.iExisting==0);

	// 1) TLS를 할당해제한다.
	TlsFree(m_TLSIndex);

	// 2) Factory Manager에 등록해제한다.
	UnregisterFactory();
}

template <class TOBJECT, class TCREATE>
bool CPoolObjectTLS<TOBJECT, TCREATE>::Destroy()
{
	// 1) Hold한다.
	CGPTR<CPoolObjectTLS<TOBJECT, TCREATE>>	pHold(this);

	// 2) 최대 유지 갯수를 -1로 한다.
	m_statisticsObject.iExistingLimits	 = -1;

	// 3) Stack되어 있는 객체들을 모두 지운다.
	{
		// Declare) 첫번째..
		TCREATE*	pChunk;

		// - 모든 Chunk 제거
		while((pChunk=m_stackCHUNK.pop())!=nullptr)
		{
			ProcessDestroyChunk(pChunk);
		}
	}

	// 4) TLS Cache에 저장된 객체들을 모두 지운다.
	LOCK(m_listStackTLS)
	{
		for(auto& iter:m_listStackTLS)
		{
			// - TLS Cache의 내용을 소멸시킨다.
			ProcessDestroyChunk(iter->m_pChunk);

			// - TLS Stack의 Chunk를 모두 제거한다.
			while(iter->is_exist_local_chunk())
			{
				ProcessDestroyChunk(iter->pop_local_chunk());
			}
		}

		m_listStackTLS.clear();
	}

	// Return)
	return	true;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::SetOnCreateNewFunction(_In_ const TFUNCTION& _pFunction)
{
	m_fOnCreateNew = _pFunction;
}

template <class TOBJECT, class TCREATE>
size_t CPoolObjectTLS<TOBJECT, TCREATE>::Prepare(_In_ size_t _iAmount)
{
	// Check) Prepare할 수가 0보다는 커야한다.
	CGASSERT(_iAmount > 0, 0);

	// Check) 0보다 작거나 같으면 Prepare할꺼 같으면 그냥 끝낸다.
	RETURN_IF(_iAmount <= 0, 0);

	// 1) 크기를 최소크기의 배수로 한다.
	_iAmount	 = (_iAmount%m_sizeTLSCache)+1;

	// 2) 임시로 사용할 List를 할당받는다.
	vector<TCREATE*>	vectorCreated;

	// 3) Reserve한다.
	vectorCreated.reserve(_iAmount);

	try
	{
		// 3) Prepare 수만큼 Loop를 돌면서 생성한다.
		for(; _iAmount>0; --_iAmount)
		{
			// Declare) 새로 생성한다.
			TCREATE*	pCreate = ProcessCreateChunk();

			// - 생성된 객체를 임시 버퍼에 짚어 넣는다.
			vectorCreated.push_back(pCreate);
		}

		// Trace) 
		CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d Objects is prepared on TLS pool(%s) ") _CGFUNCTION, static_cast<int64_t>(vectorCreated.size()), GetName());
	}
	// Exception) 
	catch(...)
	{
		// Trace) 
		CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d objects is prepared on TLS pool(%s)  [%I64d is failed] ") _CGFUNCTION, static_cast<int64_t>(vectorCreated.size()), GetName(), _iAmount);

		NO_EXCEPTION_BEGIN
		{
			// - Free되지 않고 남은 것들을 지운다.
			for(auto& iter:vectorCreated)
			{
				NO_EXCEPTION_BEGIN
				{
					ProcessDestroyChunk(*iter);
				}
				NO_EXCEPTION_END
			}
		}
		NO_EXCEPTION_END
	}
	
	// 4) 생성된 Object를 stack한다.
	for(auto& iter:vectorCreated)
	{
		m_stackCHUNK.push(iter);
	}

	// Statistics) 평균값을 수정한다.
	m_iAllocatedSmoothedAverage	+= static_cast<int>(vectorCreated.size())*m_sizeTLSCache;
	
	// Return) 성공!!
	return	vectorCreated.size()*m_sizeTLSCache;
}

template <class TOBJECT, class TCREATE>
size_t CPoolObjectTLS<TOBJECT, TCREATE>::Shrink(_In_ size_t _iAmount)
{
	// Case) Shrink Exceed
	if(_iAmount==-1)
	{
		_iAmount	 = (m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)%m_sizeTLSCache;
	}
	// Case) Shrink All
	else if(_iAmount==-2)
	{
		_iAmount	 = m_stackCHUNK.size();
	}

	// Check) _iAmount가 1보다 작으면 그냥 끝낸다.
	RETURN_IF(_iAmount<1, 0);

	// 1) Hold한다.
	CGPTR<CPoolObjectTLS<TOBJECT, TCREATE>>	pHold(this);

	// 2) Shrink 갯수...
	int64_t	iShrink	 = 0;

	// 3) Stack되어 있는 Object을 tempShrink만큼 지운다.
	for(; iShrink<_iAmount; ++iShrink)
	{
		// - Pop을 먼저한다.
		TCREATE* pChunk	 = m_stackCHUNK.pop();

		// Check) pObject가 nullptr이면 안된다.
		BREAK_IF(pChunk==nullptr);

		// - Object를 Destroy한다.
		ProcessDestroyChunk(pChunk);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d(%I64d Requested) Stacked Objects are shrinked in TLS pool[%s] ") _CGFUNCTION, static_cast<int64_t>(iShrink*m_sizeTLSCache), (int64_t)_iAmount*m_sizeTLSCache, GetName());

	// 4) 평균값을 수정.
	m_iAllocatedSmoothedAverage	-= (iShrink*m_sizeTLSCache);
	
	// Return) 성공!!
	return	iShrink;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level)
{
	// Check) No Systain이 true면 Sustain은 수행하지 않는다.
	RETURN_IF(m_bEnableSustain==false,);

	// Declare)
	STATISTICS_POOL	statisticsTotal;

	// 1) 모든 통계치를 다 더한다.
	LOCK(m_listStackTLS)
	{
		for(const auto& iter:m_listStackTLS)
		{
			statisticsTotal	+= iter->m_statisticsPOOL;
		}
	}

	// 2) 통계처리
	m_statisticsObject.qwAlloc_Stacked = statisticsTotal.statistics_Alloc-m_statisticsObject.qwAlloc_Create;
	m_statisticsObject.qwFree_Stacked	 = statisticsTotal.statistics_Free-m_statisticsObject.qwFree_Delete;
	m_statisticsObject.iInUsing		 = statisticsTotal.iUsing;
	
	// 3) MaxStack을 계산한다.
	int64_t	iAllocatedMax	 = ((statisticsTotal.iAllocatedTermMax*9)>>3)+8;

	// 4) Stacked의 평균을 구한다.
	int64_t	iAllocatedSmoothedAverage	 = ((m_iAllocatedSmoothedAverage*896 + iAllocatedMax*128)>>10);

	// 5) Stacked의 표준편차를 구한다.
	int64_t	iAllocatedVariation			 = ((m_iAllocatedVariation*768+256*((iAllocatedSmoothedAverage>iAllocatedMax) ? (iAllocatedSmoothedAverage-iAllocatedMax) : (iAllocatedMax-iAllocatedSmoothedAverage))+1)>>10);

	// 6) Max Stack을 구한다.
	if(m_statisticsObject.iExistingLimits>=0)
	{
		// - ExistingLimits를 계산한다.
		m_statisticsObject.iExistingLimits = iAllocatedSmoothedAverage+(iAllocatedVariation<<2);

		// - 모든 TLS Stack의 Thread hold를 설정함.
		LOCK(m_listStackTLS)
		{
			for(auto& iter:m_listStackTLS)
			{
				// - Max Stack을 구한다.
				iter->m_statisticsPOOL.iExistingLimits = (iAllocatedMax>0) ? iter->m_statisticsPOOL.iAllocatedTermMax*statisticsTotal.iExistingLimits/iAllocatedMax : 0;

				// - 최대치를 넘기지는 못하게 한다.
				SATURATE(iter->m_statisticsPOOL.iExistingLimits, m_sizeTLSCache, statisticsTotal.iExistingLimits);

				// - iAllocatedTermMax를 Reset한다.
				iter->m_statisticsPOOL.iAllocatedTermMax	 = iter->m_statisticsPOOL.iUsing;
			}
		}
	}

	// 7) 값을 넣는다.
	m_iAllocatedSmoothedAverage	 = iAllocatedSmoothedAverage;
	m_iAllocatedVariation		 = iAllocatedVariation;

	// Declare) 
	size_t	iShrinkAmount		 = 0;

	// 8) Shrink할 갯수를 얻는다.
	switch(_Level)
	{
	// - 최대갯수를 초과하는 객체수의 1/8만을 모두 제거한다.
	case	eFACTORY_SUSTAIN_TYPE::NORMAL:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>4);
			}
			break;
				
	// - 최대갯수를 초과하는 객체수의 1/2만을 모두 제거한다.
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
				iShrinkAmount	 = m_stackCHUNK.size()*m_sizeTLSCache;
			}
			break;
	};

	// 9) 갯수만큼 Shrink한다.
	Shrink(iShrinkAmount);
}

template <class TOBJECT, class TCREATE>
TCREATE* CPoolObjectTLS<TOBJECT, TCREATE>::CreateObject(CGNEW_DEBUG_INFO_PARAMETERS)
{
	return	new TCREATE;
}

template <class TOBJECT, class TCREATE>
template <class TTOBJECT>
typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
CPoolObjectTLS<TOBJECT, TCREATE>::ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// 1) 일단 새로 생성된다.
	TCREATE*	pObject	 = CreateObject(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);	// (여기서 Exception발생 가능.)

	// 2) Factory에 Setting한다. (여기서 Factory에 Reference Counting를 1증가시키게 된다.)
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
		// - 객체를 지운다.
		NO_EXCEPTION_BEGIN
		{
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
CPoolObjectTLS<TOBJECT, TCREATE>::ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS)
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
		// - 객체를 지운다.
		NO_EXCEPTION_BEGIN
		{
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
CPoolObjectTLS<TOBJECT, TCREATE>::ProcessDestroyObject(TCREATE* _Object)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_Object != nullptr,);

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
CPoolObjectTLS<TOBJECT, TCREATE>::ProcessDestroyObject(TCREATE* _Object)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_Object != nullptr, );

	// Statistics) 현재 존재하는 객체의 수를 감소시킨다.
	--m_statisticsObject.iExisting;

	// 1) Hook 함수 호출
	try
	{
		OnDestroy(_Object);
	}
	catch (...)
	{
	}

	// 2) DestroyObject함수를 호출하여 Object를 지운다.
	try
	{
		delete	_Object;
	}
	catch (...)
	{
	}

	// 3) Reference Count를 1감소시킨다.
	//      (m_pPool에 Setting되어 있지 않았다면 자체적으로 감소시킨다.)
	Release();
}


template <class TOBJECT, class TCREATE>
TCREATE* CPoolObjectTLS<TOBJECT, TCREATE>::ProcessCreateChunk()
{
	// Declare) 
	TCREATE*	pChunk	 = nullptr;
	int			i		 = 0;

	try
	{
		// 1) 첫번째 객체를 생성한다.
		pChunk			 = ProcessCreateObject<TCREATE>();
		pChunk->m_pNext	 = nullptr;

		// 2) 두번째에서 m_sizeTLSCache까지의 객체를 생성한다.
		for(++i; i<m_sizeTLSCache; ++i)
		{
			TCREATE*	pCreate	 = ProcessCreateObject<TCREATE>();

			pCreate->m_pNext = pChunk;
			pChunk			 = pCreate;
		}
	}
	catch(...)
	{
		// - Object Roll back
		NO_EXCEPTION_BEGIN
		{
			while (pChunk)
			{
				TCREATE* pData = pChunk;

				pChunk = pData->m_pNext;

				// 소멸시킨다.
				NO_EXCEPTION_BEGIN
				{
					ProcessDestroyObject<TCREATE>(pData);
				}
				NO_EXCEPTION_END
			}
		}
		NO_EXCEPTION_END

		// Reraise) 
		throw;
	}

	// Statistics) 
	m_statisticsObject.qwAlloc_Create	+= static_cast<int64_t>(i);

	// 3) 최대할당수가 생성 최대치를 넘어설 경우 생성 최대수를 수정한다.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits && m_statisticsObject.iExistingLimits>=0)
	{
		m_statisticsObject.iExistingLimits	 = m_statisticsObject.iExisting+m_sizeTLSCache;
	}

	// Return) 
	return	pChunk;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::ProcessDestroyChunk(TCREATE* p_pChunk)
{
	int64_t	iDestroyed	 = 0;

	while(p_pChunk)
	{
		TCREATE*	pData	 = p_pChunk;

		p_pChunk = pData->m_pNext;

		// 소멸시킨다.
		ProcessDestroyObject<TCREATE>(pData);

		++iDestroyed;
	}

	// Statistics) 
	m_statisticsObject.qwFree_Delete	+= iDestroyed;
}

template <class TOBJECT, class TCREATE>
TCREATE* CPoolObjectTLS<TOBJECT, TCREATE>::ProcessPopChunk()
{
	// 1) Chunk를 Balance Stack에서 가져온다.
	TCREATE*	pChunk	 = m_stackCHUNK.pop();

	// 2) 만약 Balance Stack에도 Chunk가 없다면 새로 생성한다.
	if(pChunk==nullptr)
	{
		// - 새로운 Chunk를 생성한다.
		pChunk	 = ProcessCreateChunk();
	}

	// Return) 
	return	pChunk;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::ProcessPushChunk(TCREATE* p_pChunk)
{
	// Check) Existing이 Existing Limits보다 크면 제거한다.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
	{
		// - Chunk를 일단 소멸시킨다.
		ProcessDestroyChunk(p_pChunk);

		// Return) 
		return;
	}

	// 1) 중앙 스택에 넣는다.
	m_stackCHUNK.push(p_pChunk);
}

template <class TOBJECT, class TCREATE>
TOBJECT* CPoolObjectTLS<TOBJECT, TCREATE>::Alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	//-----------------------------------------------------------------
	// 1. TLS할당
	//-----------------------------------------------------------------
	// 1) TLS cache를 읽어온다.
	TLS_CACHE*	pcacheTLS	 = reinterpret_cast<TLS_CACHE*>(TlsGetValue(m_TLSIndex));

	// Check) TLS cache가 존재하지 않으면 추가한다.
	if(pcacheTLS==0)
	{
		LOCK(m_listStackTLS)
		{
			// - TLS Cache를 설정한다.
			m_listStackTLS.push_front(TLS_CACHE());
			pcacheTLS	 = &m_listStackTLS.front();
			TlsSetValue(m_TLSIndex, reinterpret_cast<void*>(pcacheTLS));

			// Check) 
			CGASSERT_ERROR(pcacheTLS->m_iStacked==0);
		}
	}


	//-----------------------------------------------------------------
	// 2. 새로운 객체를 얻어온다.
	//-----------------------------------------------------------------
	// Check) 
	CGASSERT_ERROR(pcacheTLS->m_iStacked>=0);

	// Case) TLS Cache가 모두 소진되면 stack Chunk에서 가져오든 새로
	//       생성하든 해온다.
	if(pcacheTLS->m_pChunk==nullptr)
	{
		if(pcacheTLS->is_exist_local_chunk())
		{
			// - Local Chunk에 넣는다.
			pcacheTLS->m_pChunk	 = pcacheTLS->pop_local_chunk();
		}
		else
		{
			// - Chunk를 중앙 Stack에서 가져온다.
			pcacheTLS->m_pChunk	 = ProcessPopChunk();

			// - Existing을 추가한다.
			pcacheTLS->m_statisticsPOOL.iExisting += m_sizeTLSCache;
		}

		// - 갯수를 증가..
		pcacheTLS->m_iStacked	 = m_sizeTLSCache;
	}


	//-----------------------------------------------------------------
	// 3. 객체를 Pop한다.
	//-----------------------------------------------------------------
	// 1) 객체를 Pop해낸다.
	TCREATE*	pObject	 = pcacheTLS->m_pChunk;

	// 2) Pop 처리를 한다.
	pcacheTLS->m_pChunk	 = pObject->m_pNext;

	// 3) Stack된 갯수를 줄인다.
	--pcacheTLS->m_iStacked;

	// Check) 
	CGASSERT_ERROR(pcacheTLS->m_iStacked>=0);

	// 5) OnObjectAlloc()함수를 호출한다.
#if defined(_MSC_VER)
	__if_exists(TCREATE::OnObjectAlloc)
	{
		try
		{
			pObject->OnObjectAlloc();
		}
		catch(...)
		{
			// - 소멸시킨다.
			NO_EXCEPTION_BEGIN
			{
				ProcessDestroyObject<TCREATE>(pObject);
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
#endif

	// Debug)
	CGNEW_DEBUG_INFO_SET(pObject, _FileName, _Line);

	// Statistics) 
	++pcacheTLS->m_statisticsPOOL.statistics_Alloc;
	++pcacheTLS->m_statisticsPOOL.iUsing;

	// Using의 갯수를 저장해놓는다.
	int64_t	countUsing	 = pcacheTLS->m_statisticsPOOL.iUsing;

	// Sustain) 최대 할당 수를 구한다.
	if(countUsing > pcacheTLS->m_statisticsPOOL.iAllocatedTermMax)
	{
		// - 최대 할당수를  갱신한다.
		pcacheTLS->m_statisticsPOOL.iAllocatedTermMax	 = countUsing;

		// - 최대할당수가 생성 최대치를 넘어설 경우 생성 최대수를 수정한다.
		if(countUsing > pcacheTLS->m_statisticsPOOL.iExistingLimits)
		{
			pcacheTLS->m_statisticsPOOL.iExistingLimits	 = ((countUsing*9)>>3)+8;
		}
	} 

	// Check) 처음 할당받았을 때 Disuse는 반드시 false여야 한다.
	CGASSERT_ERROR(pObject->IsDisuse() == false);


	// Return) 성공!!
	return	pObject;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::Free(TOBJECT* _Object)
{
	//-----------------------------------------------------------------
	// 1. TLS할당
	//-----------------------------------------------------------------
	// 1) TLS cache를 읽어온다.
	TLS_CACHE*	pcacheTLS	 = reinterpret_cast<TLS_CACHE*>(TlsGetValue(m_TLSIndex));

	// Check) TLS cache가 존재하지 않으면 추가한다.
	if(pcacheTLS==nullptr)
	{
		LOCK(m_listStackTLS)
		{
			// - TLS Cache를 설정한다.
			m_listStackTLS.push_front(TLS_CACHE());
			pcacheTLS	 = &m_listStackTLS.front();
			TlsSetValue(m_TLSIndex, reinterpret_cast<void*>(pcacheTLS));

			// Check) 
			CGASSERT_ERROR(pcacheTLS->m_iStacked==0);
		}
	}


	//-----------------------------------------------------------------
	// 2. OnObjectFree()함수 호출
	//-----------------------------------------------------------------
	// Check) 
	CGASSERT_ERROR(pcacheTLS->m_iStacked>=0);

	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_Object!=nullptr,);

	// Statistics)
	++pcacheTLS->m_statisticsPOOL.statistics_Free;
	--pcacheTLS->m_statisticsPOOL.iUsing;

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
			NO_EXCEPTION_BEGIN
			{
				// Statistics) 
				++m_statisticsObject.qwFree_Delete;
			}
			NO_EXCEPTION_END

			// - 객체를 소멸시킨다.
			NO_EXCEPTION_BEGIN
			{
				ProcessDestroyObject<TCREATE>((TCREATE*)_Object);
			}
			NO_EXCEPTION_END

			// Trace)
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGPoolTLS: Occure exception on delete Object(%s) ") _CGFUNCTION, GetName());
		}
	}
#endif


	//-----------------------------------------------------------------
	// 3. Disuse일 경우 바로 지운다.
	//-----------------------------------------------------------------
	if (_Object->IsDisuse())
	{
		// 소멸시킨다.
		ProcessDestroyObject<TCREATE>(_Object);

		// Statistics) 
		++m_statisticsObject.qwFree_Delete;

		// Return) 
		return;
	}


	//-----------------------------------------------------------------
	// 3. TLS stack이 꽉찼는지를 검사한다.
	//-----------------------------------------------------------------
	// Check) TLS Stack에 꽉찼을 경우. (CHUNK stack에 옮긴다.)
	if(pcacheTLS->m_iStacked>=m_sizeTLSCache)
	{
		// Check) 
		CGASSERT_ERROR(pcacheTLS->m_iStacked==m_sizeTLSCache);

		// 1) local stack에 여유가 있을 경우 Balance Stack에 추가한다.
		if(pcacheTLS->is_room_local_chunk())
		{
			// - Local Chunk에 넣는다.
			pcacheTLS->push_local_chunk();
		}
		// 2) local stack에 꽉 찼을 경우
		else
		{
			// - Chunk를 제거한다.
			ProcessPushChunk(pcacheTLS->m_pChunk);

			// - Chunk를 Reset한다.
			pcacheTLS->reset();

			// - Existing을 뺀다.
			pcacheTLS->m_statisticsPOOL.iExisting	-= m_sizeTLSCache;
		}
	}

	// Check) Sustain 처리.
	while(pcacheTLS->is_overflow_local_chunk())
	{
		// Check) 
		BREAK_IF(pcacheTLS->is_empty_local_chunk());

		// 1) local chunk를 하나 뽑느다.
		TCREATE* pChunk	 = pcacheTLS->pop_local_chunk();

		// Check) pChunk가 없으면 끝낸다.
		BREAK_IF(pChunk==nullptr);

		// 2) 생성한 Chunk를 옮긴다.
		ProcessPushChunk(pChunk);

		// 3) Existing을 뺀다.
		pcacheTLS->m_statisticsPOOL.iExisting	-= m_sizeTLSCache;
	}


	//-----------------------------------------------------------------
	// 4. TLS Cache stack에 추가한다.
	//-----------------------------------------------------------------
	// 1) TLS Cache Stack에 넣는다.
	_Object->m_pNext	 = pcacheTLS->m_pChunk;

	// 2) head를 새로 설정한 놈으로 설정한다.
	pcacheTLS->m_pChunk	 = _Object;

	// Statistics) 
	++pcacheTLS->m_iStacked;

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Object is freed in TLS pool[%s] ") _CGFUNCTION, GetName());
}

template <class TOBJECT, class TCREATE>
size_t CPoolObjectTLS<TOBJECT, TCREATE>::GetStackedCount() const
{
	return m_stackCHUNK.size()*m_sizeTLSCache;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::EnableSustain(bool _bStatus)
{
	// Check) 
	RETURN_IF(_bStatus==m_bEnableSustain,);

	// 1) 상태를 바꾼다.
	m_bEnableSustain	 = _bStatus;
}


}
