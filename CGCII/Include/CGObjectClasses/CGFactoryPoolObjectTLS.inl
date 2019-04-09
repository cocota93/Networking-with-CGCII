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
	// 1) Name�� ������ �ʾ��� ��� Object Factory�� Name�� �⺻���� �����Ѵ�.
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

			// - �⺻ �̸� ���ڿ��� �����.
			CGSNPRINTF_S(temp, _TRUNCATE, _CGTEXT("%hs"), typeid(TCREATE).name());

			// - �⺻ �̸��� �����Ѵ�.
			SetName(temp);

	#if defined(_MSC_VER)
		}
	#endif
	}

	// 2) Factory Type�� �����Ѵ�.
	m_statisticsObject.eFactoryType	 = _eFactoryType;

	// 3) TLS�� �Ҵ��Ѵ�.
	m_TLSIndex	 = TlsAlloc();

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: TLS pool(%s) is created ") _CGFUNCTION, GetName());

	// 5) Factory Manager�� ����Ѵ�.
	RegisterFactory();
}

template <class TOBJECT, class TCREATE>
CPoolObjectTLS<TOBJECT, TCREATE>::~CPoolObjectTLS()
{
	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: TLS pool(%s:%I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// Check) ��� ���� ��ü�� ���� 0���̿��� �Ѵ�.
	CGASSERT_ERROR(m_statisticsObject.iExisting==0);

	// 1) TLS�� �Ҵ������Ѵ�.
	TlsFree(m_TLSIndex);

	// 2) Factory Manager�� ��������Ѵ�.
	UnregisterFactory();
}

template <class TOBJECT, class TCREATE>
bool CPoolObjectTLS<TOBJECT, TCREATE>::Destroy()
{
	// 1) Hold�Ѵ�.
	CGPTR<CPoolObjectTLS<TOBJECT, TCREATE>>	pHold(this);

	// 2) �ִ� ���� ������ -1�� �Ѵ�.
	m_statisticsObject.iExistingLimits	 = -1;

	// 3) Stack�Ǿ� �ִ� ��ü���� ��� �����.
	{
		// Declare) ù��°..
		TCREATE*	pChunk;

		// - ��� Chunk ����
		while((pChunk=m_stackCHUNK.pop())!=nullptr)
		{
			ProcessDestroyChunk(pChunk);
		}
	}

	// 4) TLS Cache�� ����� ��ü���� ��� �����.
	LOCK(m_listStackTLS)
	{
		for(auto& iter:m_listStackTLS)
		{
			// - TLS Cache�� ������ �Ҹ��Ų��.
			ProcessDestroyChunk(iter->m_pChunk);

			// - TLS Stack�� Chunk�� ��� �����Ѵ�.
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
	// Check) Prepare�� ���� 0���ٴ� Ŀ���Ѵ�.
	CGASSERT(_iAmount > 0, 0);

	// Check) 0���� �۰ų� ������ Prepare�Ҳ� ������ �׳� ������.
	RETURN_IF(_iAmount <= 0, 0);

	// 1) ũ�⸦ �ּ�ũ���� ����� �Ѵ�.
	_iAmount	 = (_iAmount%m_sizeTLSCache)+1;

	// 2) �ӽ÷� ����� List�� �Ҵ�޴´�.
	vector<TCREATE*>	vectorCreated;

	// 3) Reserve�Ѵ�.
	vectorCreated.reserve(_iAmount);

	try
	{
		// 3) Prepare ����ŭ Loop�� ���鼭 �����Ѵ�.
		for(; _iAmount>0; --_iAmount)
		{
			// Declare) ���� �����Ѵ�.
			TCREATE*	pCreate = ProcessCreateChunk();

			// - ������ ��ü�� �ӽ� ���ۿ� ¤�� �ִ´�.
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
			// - Free���� �ʰ� ���� �͵��� �����.
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
	
	// 4) ������ Object�� stack�Ѵ�.
	for(auto& iter:vectorCreated)
	{
		m_stackCHUNK.push(iter);
	}

	// Statistics) ��հ��� �����Ѵ�.
	m_iAllocatedSmoothedAverage	+= static_cast<int>(vectorCreated.size())*m_sizeTLSCache;
	
	// Return) ����!!
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

	// Check) _iAmount�� 1���� ������ �׳� ������.
	RETURN_IF(_iAmount<1, 0);

	// 1) Hold�Ѵ�.
	CGPTR<CPoolObjectTLS<TOBJECT, TCREATE>>	pHold(this);

	// 2) Shrink ����...
	int64_t	iShrink	 = 0;

	// 3) Stack�Ǿ� �ִ� Object�� tempShrink��ŭ �����.
	for(; iShrink<_iAmount; ++iShrink)
	{
		// - Pop�� �����Ѵ�.
		TCREATE* pChunk	 = m_stackCHUNK.pop();

		// Check) pObject�� nullptr�̸� �ȵȴ�.
		BREAK_IF(pChunk==nullptr);

		// - Object�� Destroy�Ѵ�.
		ProcessDestroyChunk(pChunk);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d(%I64d Requested) Stacked Objects are shrinked in TLS pool[%s] ") _CGFUNCTION, static_cast<int64_t>(iShrink*m_sizeTLSCache), (int64_t)_iAmount*m_sizeTLSCache, GetName());

	// 4) ��հ��� ����.
	m_iAllocatedSmoothedAverage	-= (iShrink*m_sizeTLSCache);
	
	// Return) ����!!
	return	iShrink;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level)
{
	// Check) No Systain�� true�� Sustain�� �������� �ʴ´�.
	RETURN_IF(m_bEnableSustain==false,);

	// Declare)
	STATISTICS_POOL	statisticsTotal;

	// 1) ��� ���ġ�� �� ���Ѵ�.
	LOCK(m_listStackTLS)
	{
		for(const auto& iter:m_listStackTLS)
		{
			statisticsTotal	+= iter->m_statisticsPOOL;
		}
	}

	// 2) ���ó��
	m_statisticsObject.qwAlloc_Stacked = statisticsTotal.statistics_Alloc-m_statisticsObject.qwAlloc_Create;
	m_statisticsObject.qwFree_Stacked	 = statisticsTotal.statistics_Free-m_statisticsObject.qwFree_Delete;
	m_statisticsObject.iInUsing		 = statisticsTotal.iUsing;
	
	// 3) MaxStack�� ����Ѵ�.
	int64_t	iAllocatedMax	 = ((statisticsTotal.iAllocatedTermMax*9)>>3)+8;

	// 4) Stacked�� ����� ���Ѵ�.
	int64_t	iAllocatedSmoothedAverage	 = ((m_iAllocatedSmoothedAverage*896 + iAllocatedMax*128)>>10);

	// 5) Stacked�� ǥ�������� ���Ѵ�.
	int64_t	iAllocatedVariation			 = ((m_iAllocatedVariation*768+256*((iAllocatedSmoothedAverage>iAllocatedMax) ? (iAllocatedSmoothedAverage-iAllocatedMax) : (iAllocatedMax-iAllocatedSmoothedAverage))+1)>>10);

	// 6) Max Stack�� ���Ѵ�.
	if(m_statisticsObject.iExistingLimits>=0)
	{
		// - ExistingLimits�� ����Ѵ�.
		m_statisticsObject.iExistingLimits = iAllocatedSmoothedAverage+(iAllocatedVariation<<2);

		// - ��� TLS Stack�� Thread hold�� ������.
		LOCK(m_listStackTLS)
		{
			for(auto& iter:m_listStackTLS)
			{
				// - Max Stack�� ���Ѵ�.
				iter->m_statisticsPOOL.iExistingLimits = (iAllocatedMax>0) ? iter->m_statisticsPOOL.iAllocatedTermMax*statisticsTotal.iExistingLimits/iAllocatedMax : 0;

				// - �ִ�ġ�� �ѱ����� ���ϰ� �Ѵ�.
				SATURATE(iter->m_statisticsPOOL.iExistingLimits, m_sizeTLSCache, statisticsTotal.iExistingLimits);

				// - iAllocatedTermMax�� Reset�Ѵ�.
				iter->m_statisticsPOOL.iAllocatedTermMax	 = iter->m_statisticsPOOL.iUsing;
			}
		}
	}

	// 7) ���� �ִ´�.
	m_iAllocatedSmoothedAverage	 = iAllocatedSmoothedAverage;
	m_iAllocatedVariation		 = iAllocatedVariation;

	// Declare) 
	size_t	iShrinkAmount		 = 0;

	// 8) Shrink�� ������ ��´�.
	switch(_Level)
	{
	// - �ִ밹���� �ʰ��ϴ� ��ü���� 1/8���� ��� �����Ѵ�.
	case	eFACTORY_SUSTAIN_TYPE::NORMAL:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>4);
			}
			break;
				
	// - �ִ밹���� �ʰ��ϴ� ��ü���� 1/2���� ��� �����Ѵ�.
	case	eFACTORY_SUSTAIN_TYPE::HEAVY:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>2);
			}
			break;

	// - �ִ밹���� �ʰ��ϴ� ��ü ���� ��� ��ŭ�� �����Ѵ�.
	case	eFACTORY_SUSTAIN_TYPE::EXCESS_ALL:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>(m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits);
			}
			break;

	// - Stack�� ���� ������ �����Ѵ�.
	case	eFACTORY_SUSTAIN_TYPE::STACKED_ALL:
			{
				iShrinkAmount	 = m_stackCHUNK.size()*m_sizeTLSCache;
			}
			break;
	};

	// 9) ������ŭ Shrink�Ѵ�.
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
	// 1) �ϴ� ���� �����ȴ�.
	TCREATE*	pObject	 = CreateObject(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);	// (���⼭ Exception�߻� ����.)

	// 2) Factory�� Setting�Ѵ�. (���⼭ Factory�� Reference Counting�� 1������Ű�� �ȴ�.)
	pObject->m_pPool	 = this;

	try
	{
		// 3) �ʱ�ȭ
		if(m_fOnCreateNew!=nullptr)
		{
			m_fOnCreateNew(pObject);
		}

		// 4) Hook �Լ� ȣ��
		OnCreateNew(pObject);
	}
	catch(...)
	{
		// - ��ü�� �����.
		NO_EXCEPTION_BEGIN
		{
			delete	pObject;
		}
		NO_EXCEPTION_END

		// Reraise) 
		throw;
	}

	// Statistics) ���� �����ϴ� ��ü�� ���� ������Ų��.
	++m_statisticsObject.iExisting;

	// Return) ����!!
	return	pObject;
}

template <class TOBJECT, class TCREATE>
template <class TTOBJECT>
typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
CPoolObjectTLS<TOBJECT, TCREATE>::ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// 1) �ϴ� ���� �����ȴ�.
	TCREATE*	pObject	 = CreateObject(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);	// (���⼭ Exception�߻� ����.)

	// 2) Reference Count�� 1������Ų��. 
	//      (m_pPool�� Setting���� ������ ��ü������ ������Ų��.)
	AddRef();

	try
	{
		// 3) �ʱ�ȭ
		if(m_fOnCreateNew!=nullptr)
		{
			m_fOnCreateNew(pObject);
		}

		// 4) Hook �Լ� ȣ��
		OnCreateNew(pObject);
	}
	catch(...)
	{
		// - ��ü�� �����.
		NO_EXCEPTION_BEGIN
		{
			delete	pObject;
		}
		NO_EXCEPTION_END

		// Reraise) 
		throw;
	}

	// Statistics) ���� �����ϴ� ��ü�� ���� ������Ų��.
	++m_statisticsObject.iExisting;

	// Return) ����!!
	return	pObject;
}

template <class TOBJECT, class TCREATE>
template <class TTOBJECT>
typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
CPoolObjectTLS<TOBJECT, TCREATE>::ProcessDestroyObject(TCREATE* _Object)
{
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_Object != nullptr,);

	// Statistics) ���� �����ϴ� ��ü�� ���� ���ҽ�Ų��.
	--m_statisticsObject.iExisting;

	// 1) Hook �Լ� ȣ��
	NO_EXCEPTION_BEGIN
	{
		OnDestroy(_Object);
	}
	NO_EXCEPTION_END

	// 2) DestroyObject�Լ��� ȣ���Ͽ� Object�� �����.
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
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_Object != nullptr, );

	// Statistics) ���� �����ϴ� ��ü�� ���� ���ҽ�Ų��.
	--m_statisticsObject.iExisting;

	// 1) Hook �Լ� ȣ��
	try
	{
		OnDestroy(_Object);
	}
	catch (...)
	{
	}

	// 2) DestroyObject�Լ��� ȣ���Ͽ� Object�� �����.
	try
	{
		delete	_Object;
	}
	catch (...)
	{
	}

	// 3) Reference Count�� 1���ҽ�Ų��.
	//      (m_pPool�� Setting�Ǿ� ���� �ʾҴٸ� ��ü������ ���ҽ�Ų��.)
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
		// 1) ù��° ��ü�� �����Ѵ�.
		pChunk			 = ProcessCreateObject<TCREATE>();
		pChunk->m_pNext	 = nullptr;

		// 2) �ι�°���� m_sizeTLSCache������ ��ü�� �����Ѵ�.
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

				// �Ҹ��Ų��.
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

	// 3) �ִ��Ҵ���� ���� �ִ�ġ�� �Ѿ ��� ���� �ִ���� �����Ѵ�.
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

		// �Ҹ��Ų��.
		ProcessDestroyObject<TCREATE>(pData);

		++iDestroyed;
	}

	// Statistics) 
	m_statisticsObject.qwFree_Delete	+= iDestroyed;
}

template <class TOBJECT, class TCREATE>
TCREATE* CPoolObjectTLS<TOBJECT, TCREATE>::ProcessPopChunk()
{
	// 1) Chunk�� Balance Stack���� �����´�.
	TCREATE*	pChunk	 = m_stackCHUNK.pop();

	// 2) ���� Balance Stack���� Chunk�� ���ٸ� ���� �����Ѵ�.
	if(pChunk==nullptr)
	{
		// - ���ο� Chunk�� �����Ѵ�.
		pChunk	 = ProcessCreateChunk();
	}

	// Return) 
	return	pChunk;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::ProcessPushChunk(TCREATE* p_pChunk)
{
	// Check) Existing�� Existing Limits���� ũ�� �����Ѵ�.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
	{
		// - Chunk�� �ϴ� �Ҹ��Ų��.
		ProcessDestroyChunk(p_pChunk);

		// Return) 
		return;
	}

	// 1) �߾� ���ÿ� �ִ´�.
	m_stackCHUNK.push(p_pChunk);
}

template <class TOBJECT, class TCREATE>
TOBJECT* CPoolObjectTLS<TOBJECT, TCREATE>::Alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	//-----------------------------------------------------------------
	// 1. TLS�Ҵ�
	//-----------------------------------------------------------------
	// 1) TLS cache�� �о�´�.
	TLS_CACHE*	pcacheTLS	 = reinterpret_cast<TLS_CACHE*>(TlsGetValue(m_TLSIndex));

	// Check) TLS cache�� �������� ������ �߰��Ѵ�.
	if(pcacheTLS==0)
	{
		LOCK(m_listStackTLS)
		{
			// - TLS Cache�� �����Ѵ�.
			m_listStackTLS.push_front(TLS_CACHE());
			pcacheTLS	 = &m_listStackTLS.front();
			TlsSetValue(m_TLSIndex, reinterpret_cast<void*>(pcacheTLS));

			// Check) 
			CGASSERT_ERROR(pcacheTLS->m_iStacked==0);
		}
	}


	//-----------------------------------------------------------------
	// 2. ���ο� ��ü�� ���´�.
	//-----------------------------------------------------------------
	// Check) 
	CGASSERT_ERROR(pcacheTLS->m_iStacked>=0);

	// Case) TLS Cache�� ��� �����Ǹ� stack Chunk���� �������� ����
	//       �����ϵ� �ؿ´�.
	if(pcacheTLS->m_pChunk==nullptr)
	{
		if(pcacheTLS->is_exist_local_chunk())
		{
			// - Local Chunk�� �ִ´�.
			pcacheTLS->m_pChunk	 = pcacheTLS->pop_local_chunk();
		}
		else
		{
			// - Chunk�� �߾� Stack���� �����´�.
			pcacheTLS->m_pChunk	 = ProcessPopChunk();

			// - Existing�� �߰��Ѵ�.
			pcacheTLS->m_statisticsPOOL.iExisting += m_sizeTLSCache;
		}

		// - ������ ����..
		pcacheTLS->m_iStacked	 = m_sizeTLSCache;
	}


	//-----------------------------------------------------------------
	// 3. ��ü�� Pop�Ѵ�.
	//-----------------------------------------------------------------
	// 1) ��ü�� Pop�س���.
	TCREATE*	pObject	 = pcacheTLS->m_pChunk;

	// 2) Pop ó���� �Ѵ�.
	pcacheTLS->m_pChunk	 = pObject->m_pNext;

	// 3) Stack�� ������ ���δ�.
	--pcacheTLS->m_iStacked;

	// Check) 
	CGASSERT_ERROR(pcacheTLS->m_iStacked>=0);

	// 5) OnObjectAlloc()�Լ��� ȣ���Ѵ�.
#if defined(_MSC_VER)
	__if_exists(TCREATE::OnObjectAlloc)
	{
		try
		{
			pObject->OnObjectAlloc();
		}
		catch(...)
		{
			// - �Ҹ��Ų��.
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

	// Using�� ������ �����س��´�.
	int64_t	countUsing	 = pcacheTLS->m_statisticsPOOL.iUsing;

	// Sustain) �ִ� �Ҵ� ���� ���Ѵ�.
	if(countUsing > pcacheTLS->m_statisticsPOOL.iAllocatedTermMax)
	{
		// - �ִ� �Ҵ����  �����Ѵ�.
		pcacheTLS->m_statisticsPOOL.iAllocatedTermMax	 = countUsing;

		// - �ִ��Ҵ���� ���� �ִ�ġ�� �Ѿ ��� ���� �ִ���� �����Ѵ�.
		if(countUsing > pcacheTLS->m_statisticsPOOL.iExistingLimits)
		{
			pcacheTLS->m_statisticsPOOL.iExistingLimits	 = ((countUsing*9)>>3)+8;
		}
	} 

	// Check) ó�� �Ҵ�޾��� �� Disuse�� �ݵ�� false���� �Ѵ�.
	CGASSERT_ERROR(pObject->IsDisuse() == false);


	// Return) ����!!
	return	pObject;
}

template <class TOBJECT, class TCREATE>
void CPoolObjectTLS<TOBJECT, TCREATE>::Free(TOBJECT* _Object)
{
	//-----------------------------------------------------------------
	// 1. TLS�Ҵ�
	//-----------------------------------------------------------------
	// 1) TLS cache�� �о�´�.
	TLS_CACHE*	pcacheTLS	 = reinterpret_cast<TLS_CACHE*>(TlsGetValue(m_TLSIndex));

	// Check) TLS cache�� �������� ������ �߰��Ѵ�.
	if(pcacheTLS==nullptr)
	{
		LOCK(m_listStackTLS)
		{
			// - TLS Cache�� �����Ѵ�.
			m_listStackTLS.push_front(TLS_CACHE());
			pcacheTLS	 = &m_listStackTLS.front();
			TlsSetValue(m_TLSIndex, reinterpret_cast<void*>(pcacheTLS));

			// Check) 
			CGASSERT_ERROR(pcacheTLS->m_iStacked==0);
		}
	}


	//-----------------------------------------------------------------
	// 2. OnObjectFree()�Լ� ȣ��
	//-----------------------------------------------------------------
	// Check) 
	CGASSERT_ERROR(pcacheTLS->m_iStacked>=0);

	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_Object!=nullptr,);

	// Statistics)
	++pcacheTLS->m_statisticsPOOL.statistics_Free;
	--pcacheTLS->m_statisticsPOOL.iUsing;

	// 1) OnFree�Լ� ȣ��.
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

			// - ��ü�� �Ҹ��Ų��.
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
	// 3. Disuse�� ��� �ٷ� �����.
	//-----------------------------------------------------------------
	if (_Object->IsDisuse())
	{
		// �Ҹ��Ų��.
		ProcessDestroyObject<TCREATE>(_Object);

		// Statistics) 
		++m_statisticsObject.qwFree_Delete;

		// Return) 
		return;
	}


	//-----------------------------------------------------------------
	// 3. TLS stack�� ��á������ �˻��Ѵ�.
	//-----------------------------------------------------------------
	// Check) TLS Stack�� ��á�� ���. (CHUNK stack�� �ű��.)
	if(pcacheTLS->m_iStacked>=m_sizeTLSCache)
	{
		// Check) 
		CGASSERT_ERROR(pcacheTLS->m_iStacked==m_sizeTLSCache);

		// 1) local stack�� ������ ���� ��� Balance Stack�� �߰��Ѵ�.
		if(pcacheTLS->is_room_local_chunk())
		{
			// - Local Chunk�� �ִ´�.
			pcacheTLS->push_local_chunk();
		}
		// 2) local stack�� �� á�� ���
		else
		{
			// - Chunk�� �����Ѵ�.
			ProcessPushChunk(pcacheTLS->m_pChunk);

			// - Chunk�� Reset�Ѵ�.
			pcacheTLS->reset();

			// - Existing�� ����.
			pcacheTLS->m_statisticsPOOL.iExisting	-= m_sizeTLSCache;
		}
	}

	// Check) Sustain ó��.
	while(pcacheTLS->is_overflow_local_chunk())
	{
		// Check) 
		BREAK_IF(pcacheTLS->is_empty_local_chunk());

		// 1) local chunk�� �ϳ� �̴���.
		TCREATE* pChunk	 = pcacheTLS->pop_local_chunk();

		// Check) pChunk�� ������ ������.
		BREAK_IF(pChunk==nullptr);

		// 2) ������ Chunk�� �ű��.
		ProcessPushChunk(pChunk);

		// 3) Existing�� ����.
		pcacheTLS->m_statisticsPOOL.iExisting	-= m_sizeTLSCache;
	}


	//-----------------------------------------------------------------
	// 4. TLS Cache stack�� �߰��Ѵ�.
	//-----------------------------------------------------------------
	// 1) TLS Cache Stack�� �ִ´�.
	_Object->m_pNext	 = pcacheTLS->m_pChunk;

	// 2) head�� ���� ������ ������ �����Ѵ�.
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

	// 1) ���¸� �ٲ۴�.
	m_bEnableSustain	 = _bStatus;
}


}
