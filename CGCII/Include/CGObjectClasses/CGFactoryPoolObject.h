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

namespace CGFactory
{

//-----------------------------------------------------------------------------
/**

 @class		CPoolObject
 @brief		��ü�� �Ҵ�� ������ ȿ���� ����Ű�� ���� ��ü Ǯ
 @todo		
 @ref		ICGPoolable, NCGPoolable
 @details	\n
 ��ü�� ���� �Ҵ�� ������ ȿ������ ���̱� ���� Ǯ ��ü�̴�.
 ���������� �������� �����ϱ� ������ �ſ� ������ �����Ѵ�.

 Ǯ�� ��� ��ü�� �Ƿ��� �ݵ�� ICGPoolable<TOBJECT>�� ��ӹ��� Ŭ��������Ѵ�.

 Ǯ�� �Ҵ��� �䱸�ϸ� ���� ������ ���ø� ���� �˻��Ѵ�. ���� ���ÿ� ��ü�� ���� ��� �װ��� �Ҵ����ش�.
 ���� ���ÿ� ��ü�� �ϳ��� ���ٸ� ���� �����ؼ� �Ҵ����ش�.
 �Ҵ����� ��ü�� �ٽ� ���ƿ��� �Ǹ� ������ ���ÿ� ������ ���Ҵٰ� ���� �Ҵ� �䱸�� �Ҵ����ش�.
 �ٸ� �ʹ� ���� ��ü�� ������ ���ÿ� ������ ��� �������� ������ ������ ������ �����Ѵ�.

 Ǯ���� ��ü�� �Ҵ��ϱ� ���ؼ��� Alloc()�Լ��� ȣ���ϸ� �Ҵ� �ߴ� ��ü�� �����ϱ� ���ؼ��� Free()�Լ��� ����Ѵ�.
 Prepare()�Լ��� ����ϸ� �̸� ��ü�� �����س��� ���� �ִ�.
 Shrink()�Լ��� ����ϸ� �׿��ִ� ���������� �Ҵ� ������ ���� �ִ�.

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
	//! @brief Ǯ ��ü�� �ı��Ѵ�. @return true ���� @return false ���� 
	virtual	bool				Destroy() override;

	//! @brief _iAmount��ŭ�� ��ü�� �̸� �غ��� ���´�. @param _iAmount �غ��� ���� @return ���� �غ�� ��
	virtual	size_t				Prepare(_In_ size_t _iAmount) override;
	//! @brief _iAmount��ŭ�� ��� ��ü�� �����Ѵ�. @param _iAmount ������ ���� @return ���� ������ ��
	virtual	size_t				Shrink(_In_ size_t _iAmount) override;
	//! @brief ������ ����� ����� ����� �Ѿ�� ���� ���ؼ��� ���� ó���ϴ� ������ �ݷ��� ó���� �Ѵ�. @param _Level ���������� ���� @return ���� ������ ��
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL) override;

	//! @brief Ǯ���� ��ü�� �Ҵ��� ��û�Ѵ�. @return �Ҵ�� ��ü
			TOBJECT*			Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief Ǯ�� ��ü�� ��ȯ�Ѵ�. @param _Object ��ȯ�� ��ü
			void				Free(_In_ TOBJECT* _Object);

	//! @brief ��ü �� �޸� ũ�⸦ ��´�. @return ��ü �� �޸� ũ��
	virtual	size_t				GetObjectSize() const override			{	return sizeof(TCREATE);}
	//! @brief ����� ��´�. @return ���
	virtual	size_t				GetStackedCount() const override		{	return m_stackObject.size();}
	//! @brief �ִ� ����� ��´�. @return �ִ� ���
	virtual	int64_t				GetExistingLimits() const override		{	return m_statisticsObject.iExistingLimits;}

	//! @brief Ǯ�� ���¸� ��´�. @return Ǯ�� ����
	virtual	eFACTORY_TYPE		GetFactoryType() const override			{	return m_statisticsObject.eFactoryType;}
	//! @brief Ǯ�� ID�� ��´�. @return Ǯ�� ID.
	virtual	int					GetFactoryID() const override			{	return m_statisticsObject.iFactoryID;}

	//! @brief �������ݷ����� ����ϴ��� Ȯ���Ѵ�. @return true �������ݷ��� ��� @return false �������ݷ��� ������� �ʴ´�.
	virtual	bool				IsEnableSustain() const override		{	return m_bEnableSustain;}
	//! @brief �����ݷ��� ���� ���θ� �����Ѵ�. @param _bStatus �������ݷ��� ���� ����
	virtual	void				EnableSustain(_In_ bool _bStatus=true) override;

	//! @brief ���ο� ��ü�� �Ҵ��� �� ȣ��� �Լ��� �����Ѵ�. @param _pFunction ���ο� ��ü�� �Ҵ��� �� ȣ��� �Լ�
			void				SetOnCreateNewFunction(_In_ const TFUNCTION& _pFunction);

private:
	//! @brief ���Կ�����(Assignment�� ���� ���� �ʴ´�.)
	#if defined(_MSC_VER)
			void				operator=(const CPoolObject<TOBJECT, TCREATE>& /*_rhs*/) {	CGASSERT_ERROR(false);}
	#endif


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief ��ü�� �����ϴ� ������ �����Ѵ�. @return ������ ��ü
	template <class TTOBJECT>
	typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
								ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS);
	template <class TTOBJECT>
	typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
								ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS);

	//! @brief ��ü�� �ı���Ű�� ������ �����Ѵ�. @param _Object �ı���ų ��ü
	template <class TTOBJECT>
	typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
								ProcessDestroyObject(_In_ TCREATE* _Object);
	template <class TTOBJECT>
	typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
								ProcessDestroyObject(_In_ TCREATE* _Object);

	//! @brief ��ü�� ������ ��û�Ѵ�. @return ������ ��ü
	virtual	TCREATE*			CreateObject(CGNEW_DEBUG_INFO_PARAMETERS);

	//! @brief ��ü�� ������ �� ȣ���ϴ� �Լ� @param _Object ���� ������ ��ü
	virtual	void				OnCreateNew(_In_ TCREATE* /*_Object*/){}
	//! @brief ��ü�� �Ҹ����� �� ȣ���ϴ� �Լ� @param _Object �Ҹ��� ��ü
	virtual	void				OnDestroy(_In_ TCREATE* /*_Object*/)	{}
	
private:
	// 3) ��� ��ü Stack
			LOCKFREE_SELF_STACK<TCREATE*>	m_stackObject;

	// 4) Pool Sustainment�� ���� ������
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
			_CHAR	temp[MAX_NAME_LENGTH] = { 0 };

			// - �⺻ �̸� ���ڿ��� �����.
			CGSNPRINTF_S(temp, _TRUNCATE, _CGTEXT("%hs"), typeid(TCREATE).name());

			// - �⺻ �̸��� �����Ѵ�.
			SetName(temp);
	#if defined(_MSC_VER)
		}
	#endif
	}

	// 2) Factory Type�� Default�� ������ ��� Factory Class�� ���� �ڵ� �����Ѵ�.
	if(_eFactoryType==eFACTORY_TYPE::DEFAULT)
	{
		m_statisticsObject.eFactoryType = CGPool::_get_default_factory_type<TOBJECT>();
	}

	// 3) Factory Type�� �����Ѵ�.
	m_statisticsObject.eFactoryType = _eFactoryType;


	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Pool(%s) is created ") _CGFUNCTION, GetName());

	// 4) Factory Manager�� ����Ѵ�.
	RegisterFactory();
}

template <class TOBJECT, class TCREATE>
CPoolObject<TOBJECT, TCREATE>::~CPoolObject()
{
	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Pool(%s:%I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// Check) �����ϴ� ��ü�� ������ 0������ �Ѵ�.
	CGASSERT_ERROR(m_statisticsObject.iExisting==0);

	// Check) ��� ���� ��ü�� ���� 0���̿��� �Ѵ�.
	CGASSERT_ERROR(m_statisticsObject.iInUsing==0);

	// 1) Factory Manager�� ��������Ѵ�.
	UnregisterFactory();
}

template <class TOBJECT, class TCREATE>
bool CPoolObject<TOBJECT, TCREATE>::Destroy()
{
	// 1) Hold�Ѵ�.
	CGPTR<CPoolObject<TOBJECT, TCREATE>>	pHold(this);

	// 2) �ִ� ���� ������ -1�� �Ѵ�.
	m_statisticsObject.iExistingLimits	 = -1;

	// 3) Stack�Ǿ� �ִ� Object�� ��� �����.
	TCREATE*	pObject;
	while((pObject = m_stackObject.pop()) != nullptr)
	{
		// - ��ü�� �ı��Ѵ�.
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
	// Check) Prepare�� ���� 0���ٴ� Ŀ���Ѵ�.
	CGASSERT(_iAmount > 0, 0);

	// Check) 0���� �۰ų� ������ Prepare�Ҳ� ������ �׳� ������.
	RETURN_IF(_iAmount <= 0, 0);

	// 1) �ӽ÷� ����� List�� �Ҵ�޴´�.
	vector<TCREATE*>	vectorCreated;

	// 2) Reserve�Ѵ�.
	vectorCreated.reserve(_iAmount);

	try
	{
		// 3) Prepare ����ŭ Loop�� ���鼭 �����Ѵ�.
		for(; _iAmount>0; --_iAmount)
		{
			// Declare) ���� �����Ѵ�.
			TCREATE*	pCreate = ProcessCreateObject<TCREATE>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL);

			// - ������ ��ü�� �ӽ� ���ۿ� ¤�� �ִ´�.
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
			// - Free���� �ʰ� ���� �͵��� �����.
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

	// 4) ��հ��� �����Ѵ�.
	m_iAllocatedSmoothedAverage	+= static_cast<int>(vectorCreated.size());

	// Statistics) In-Using���� ���������ش�.
	m_statisticsObject.iInUsing	+= static_cast<int64_t>(vectorCreated.size());

	// Statistics) �Ҵ��� ��ü�� ������ ������Ų��.
	m_statisticsObject.qwAlloc_Create	+= static_cast<int64_t>(vectorCreated.size());

	// 5) Free()�Լ��� ����ؼ� stack�Ѵ�.
	for(auto& iter:vectorCreated)
	{
		Free(iter);
	}
	
	// Return) ����!!
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

	// Check) _iAmount�� 1���� ������ �׳� ������.
	RETURN_IF(_iAmount<1, 0);

	// 1) Hold�Ѵ�.
	CGPTR<CPoolObject<TOBJECT, TCREATE>>	pHold(this);

	// 2) Shrink ����...
	size_t	iShrink	 = 0;

	// 3) Stack�Ǿ� �ִ� Object�� tempShrink��ŭ �����.
	for(; iShrink<_iAmount; ++iShrink)
	{
		// - Pop�� �����Ѵ�.
		TCREATE* pObject=m_stackObject.pop();

		// Check) pObject�� nullptr�̸� �ȵȴ�.
		BREAK_IF(pObject==nullptr);

		// Statistics) �ı��� Block�� �ϳ� �ø���.
		++m_statisticsObject.qwFree_Delete;

		// - Object�� Destroy�Ѵ�.
		ProcessDestroyObject<TCREATE>(pObject);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d(%I64d Requested) Stacked Objects are shrinked in pool(%s) ") _CGFUNCTION, static_cast<int64_t>(iShrink), (int64_t)_iAmount, GetName());

	// 4) ��հ��� ����.
	m_iAllocatedSmoothedAverage	-= iShrink;
	
	// Return) ����!!
	return	iShrink;
}

template <class TOBJECT, class TCREATE>
void CPoolObject<TOBJECT, TCREATE>::Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level)
{
	// Check) No Systain�� true�� Sustain�� �������� �ʴ´�.
	RETURN_IF(m_bEnableSustain==false,);

	// Check) Destroy�Ǿ����� Sustain�� �������� �ʴ´�.
	RETURN_IF(m_statisticsObject.iExistingLimits<0,);

	// 1) MaxStack�� ����Ѵ�.
	int64_t	iAllocatedMax	 = ((m_iAllocatedTermMax*9)>>3)+8;

	// 2) Stacked�� ����� ���Ѵ�.
	int64_t	iAllocatedSmoothedAverage	 = ((m_iAllocatedSmoothedAverage*896 + iAllocatedMax*128)>>10);

	// 3) Stacked�� ǥ�������� ���Ѵ�.
	int64_t	iAllocatedVariation			 = ((m_iAllocatedVariation*768+256*((iAllocatedSmoothedAverage>iAllocatedMax) ? (iAllocatedSmoothedAverage-iAllocatedMax) : (iAllocatedMax-iAllocatedSmoothedAverage))+1)>>10);

	// 4) Max Stack�� ���Ѵ�.
	if(m_statisticsObject.iExistingLimits>=0)
	{
		m_statisticsObject.iExistingLimits = (iAllocatedSmoothedAverage+(iAllocatedVariation<<2));
	}

	// 5) ���� �ִ´�.
	m_iAllocatedSmoothedAverage		 = iAllocatedSmoothedAverage;
	m_iAllocatedVariation			 = iAllocatedVariation;
	m_iAllocatedTermMax				 = m_statisticsObject.iInUsing;

	// Declare) 
	size_t	iShrinkAmount	 = 0;

	// 6) Shrink�� ������ ��´�.
	switch(_Level)
	{
	// - �ִ밹���� �ʰ��ϴ� ��ü���� 1/16���� ��� �����Ѵ�.
	case	eFACTORY_SUSTAIN_TYPE::NORMAL:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>4);
			}
			break;
				
	// - �ִ밹���� �ʰ��ϴ� ��ü���� 1/4���� ��� �����Ѵ�.
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
				iShrinkAmount	 = GetStackedCount();
			}
			break;
	};


	// - ������ŭ Shrink�Ѵ�.
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
	// 1) �ϴ� ���� �����ȴ�.
	TCREATE*	pObject	 = CreateObject(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);	// (���⼭ Exception�߻� ����.)

	// 2) Pool�� Setting�Ѵ�. (���⼭ Pool�� Reference Counting�� 1������Ű�� �ȴ�.)
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
		NO_EXCEPTION_BEGIN
		{
			// - ��ü�� �����.
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
CPoolObject<TOBJECT, TCREATE>::ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS)
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
		NO_EXCEPTION_BEGIN
		{
			// - ��ü�� �����.
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
CPoolObject<TOBJECT, TCREATE>::ProcessDestroyObject(_In_ TCREATE* _Object)
{
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_Object != nullptr, );

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
CPoolObject<TOBJECT, TCREATE>::ProcessDestroyObject(_In_ TCREATE* _Object)
{
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_Object != nullptr, );

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

	// 3) Reference Count�� 1���ҽ�Ų��.
	//    (m_pPool�� Setting�Ǿ� ���� �ʾҴٸ� ��ü������ ���ҽ�Ų��.)
	Release();
}

template <class TOBJECT, class TCREATE>
TOBJECT* CPoolObject<TOBJECT, TCREATE>::Alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Declare) 
	TCREATE*	pObject;

	// 1) �ϴ� head�� nullptr�̸� ���� �����ؼ� �����ش�.
	pObject	 = m_stackObject.pop();

	// 2) Stack�� ���� ���ٸ� ���� ���� ������.
	if(pObject != reinterpret_cast<TCREATE*>(nullptr))
	{
		// Statistics) Stack�� ���� �Ҵ�� �� ������Ų��.
		++m_statisticsObject.qwAlloc_Stacked;
	}
	else
	{
		// - ���� Object�� �����.
		pObject	 = ProcessCreateObject<TCREATE>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

		// Statistics) �Ҵ��� ��ü�� ������ ������Ų��.
		++m_statisticsObject.qwAlloc_Create;
	}

	// 3) OnPoolAlloc()�Լ��� ȣ���Ѵ�.
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

	// Statistics) ��� ���� ��ü�� ���� ������Ų��.
	int64_t	countUsing	 = ++m_statisticsObject.iInUsing;

	// Sustain) �ִ� �Ҵ� ���� ���Ѵ�.
	if(countUsing>m_iAllocatedTermMax)
	{
		// - �ִ� �Ҵ����  �����Ѵ�.
		m_iAllocatedTermMax	 = countUsing;

		// - ������� ������ �ִ��Ҵ�ġ�� �Ѿ ��� �����Ѵ�.
		if(countUsing>m_statisticsObject.iExistingLimits && m_statisticsObject.iExistingLimits>=0)
		{
			m_statisticsObject.iExistingLimits	 = static_cast<size_t>(((countUsing*9)>>3)+8);
		}
	} 

	// Check) ó�� �Ҵ�޾��� �� Disuse�� �ݵ�� false���� �Ѵ�.
	CGASSERT_ERROR(pObject->IsDisuse() == false);

	// Return) ����!!
	return	pObject;
}

template <class TOBJECT, class TCREATE>
void CPoolObject<TOBJECT, TCREATE>::Free(_In_ TOBJECT* _Object)
{
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_Object!=nullptr,);

	// Statistics) ��� ���� ��ü�� ���� ���δ�.
	--m_statisticsObject.iInUsing;

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
			// Trace)
			CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Excp) CGFactory: Occure exception on delete Object(%s) ") _CGFUNCTION, GetName());

			NO_EXCEPTION_BEGIN
			{
				// Statistics) �ı��� Block�� �ϳ� �ø���.
				++m_statisticsObject.qwFree_Delete;
			}
			NO_EXCEPTION_END

			NO_EXCEPTION_BEGIN
			{
				// - ��ü�� �Ҹ��Ų��.
				ProcessDestroyObject<TCREATE>((TCREATE*)_Object);
			}
			NO_EXCEPTION_END
		}
	}
#endif

	// 2) �ִ� �Ѱ� Stack������ Stack�� Memory Block������ ������ �Ҵ������Ѵ�.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits || _Object->IsDisuse())
	{
		// Statistics) �ı��� Block�� �ϳ� �ø���.
		++m_statisticsObject.qwFree_Delete;
		++m_statisticsObject.qwFree_Disuse;

		// - ��ü�� �ٷ� �����.
		ProcessDestroyObject<TCREATE>(_Object);

		// Return) ������.
		return;
	}

	// 3) List�� �߰��Ѵ�.
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

	// 1) ���¸� �ٲ۴�.
	m_bEnableSustain	 = _bStatus;
}


}
