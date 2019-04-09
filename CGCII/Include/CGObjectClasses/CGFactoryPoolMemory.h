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

 @class		CPoolMemory
 @brief		������ ũ���� �޸𸮸� �Ҵ����ִ� Ǯ�̴�.
 @todo		
 @ref		CGFactory::CPoolObject<TOBJECT>, CGFactory::CPoolMemoryBlock
 @details	\n
 �⺻���� ������ CGFactory::CPoolObject<TOBJECT>�� �����ϴ� �ٸ� ������ ũ���� �޸� ��ü�� �Ҵ翡 Ưȭ�� Ǯ�̶� �͸��� �ٸ���.
 �Ϲ������� ���� ũ���� �޸𸮸� �Ҵ��ϰ��� �Ѵٸ� CGFactory::CPoolMemoryBlock�� ����ϸ� ������ �޸��� ���� ���ݵȴ�.
 ������ �� Ǯ�� �� ������ ũ���� �޸� ��ϸ��� Ǯ�� ����ϱ� ������ ȿ������ �� �ִ�.

 �� Ǯ�� ����ϱ� ���ؼ��� ������ �� �ݵ�� �Ҵ��� �޸��� ũ�⸦ ������ �־�� �Ѵ�.
 �� ����� �Ҵ��� �޸��� ũ�⸦ �������� ���Ѵ�.

 �� Ǯ ���� CGFactory::CPoolObject<TOBJECT>�� ���� Prepare(), Shrink() ���� �Լ��� ��� �����ϸ�
 Alloc()�� �Ҵ��ϰ� Free()�� �Ҵ������Ѵ�.

*/
//-----------------------------------------------------------------------------
template <class TCONTAINER=LOCKFREE_SELF_STACK<void*>>
class CPoolMemory : 
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
	typedef	std::function<void(void*)>	TFUNCTION;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPoolMemory(_In_ size_t _sizeAlloc, _In_z_ const _CHAR* _strName=0, _In_ bool _bSustain=true, _In_ eFACTORY_TYPE _eFactoryType=eFACTORY_TYPE::POOL_USER);
	virtual	~CPoolMemory();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief Ǯ ��ü�� �ı��Ѵ�. @return true ���� @return false ���� 
	virtual	bool				Destroy() override;

	//! @brief _iAmount��ŭ�� ��ü�� �̸� �غ��� ���´�. @param _iAmount �غ��� ���� @return ���� �غ�� ��
	virtual	size_t				Prepare(_In_ size_t _iAmount);
	//! @brief _iAmount��ŭ�� ��� ��ü�� �����Ѵ�. @param _iAmount ������ ���� @return ���� ������ ��
	virtual	size_t				Shrink(_In_ size_t _iAmount);
	//! @brief ������ ����� ����� ����� �Ѿ�� ���� ���ؼ��� ���� ó���ϴ� ������ �ݷ��� ó���� �Ѵ�. @param _Level ���������� ���� @return ���� ������ ��
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL);

	//! @brief Ǯ���� ��ü�� �Ҵ��� ��û�Ѵ�. @return �Ҵ�� ��ü
			void*				Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief Ǯ�� ��ü�� ��ȯ�Ѵ�. @param _pMemory ��ȯ�� ��ü
			void				Free(_In_ void* _pMemory);

	//! @brief ��ü �� �޸� ũ�⸦ ��´�. @return ��ü �� �޸� ũ��
	virtual	size_t				GetFactoryObjectSize() const			{	return m_sizeAlloc;}
	//! @brief ����� ��´�. @return ���
	virtual	size_t				GetFactoryStackedCount() const			{	return m_stackObject.size();}
	//! @brief �ִ� ����� ��´�. @return �ִ� ���
	virtual	int64_t				GetFactoryExistingLimits() const		{	return m_statisticsObject.iExistingLimits;}

	//! @brief Ǯ�� ���¸� ��´�. @return Ǯ�� ����
	virtual	eFACTORY_TYPE			GetFactoryType() const				{	return m_statisticsObject.eFactoryType;}
	//! @brief Ǯ�� ID�� ��´�. @return Ǯ�� ID.
	virtual	int					GetFactoryID() const					{	return m_statisticsObject.iFactoryID;}

	//! @brief �������ݷ����� ����ϴ��� Ȯ���Ѵ�. @return true �������ݷ��� ��� @return false �������ݷ��� ������� �ʴ´�.
	virtual	bool				IsEnableSustain() const					{	return m_bEnableSustain;}
	//! @brief �����ݷ��� ���� ���θ� �����Ѵ�. @param _bStatus �������ݷ��� ���� ����
	virtual	void				EnableSustain(_In_ bool _bStatus=true);

	//! @brief ���ο� ��ü�� �Ҵ��� �� ȣ��� �Լ��� �����Ѵ�. @param _pFunction ���ο� ��ü�� �Ҵ��� �� ȣ��� �Լ�
			void				SetOnCreateNewFunction(_In_ const TFUNCTION& _pFunction);

	//! @brief ���Կ�����(Assignment�� ���� ���� �ʴ´�.)
			void				operator=(const CPoolMemory<TCONTAINER>& /*_rhs*/) _DELETE;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
private:
	// Definition) 
			struct _node		{ _node* Next;};

	// 1) Alloc/Free
	//    - ���ο� Object�� �����ϴ� ������ ������ Process�Լ�.
			void*				ProcessAllocMemory();
			void				ProcessFreeMemory(_In_ void* _pMemory);

	// 2) Hook�Լ�
	virtual	void				OnAllocNew(void* /*_pMemory*/)			{}
	virtual	void				OnFree(void* /*_pMemory*/)				{}

private:
	// 3) Memory Size(�� ���� const���̶� ó�� ������ �� ������ �� ����� �ٲ��� ���Ѵ�.)
			const size_t		m_sizeAlloc;

	// 4) Garbage Stack
	//    * ������ ��ü���� ����� stack�̴�.
	//    * Alloc�� ��� ���⼭ �ϳ� �̾Ƽ� �Ҵ����ش�.
	//    * Free�� ��� ����ٰ� �ٽ� ������ ���´�.
			typename TCONTAINER::template rebind<_node*>::other	m_stackObject;

			bool				m_bEnableSustain;
			int64_t				m_iAllocatedTermMax;
			int64_t				m_iAllocatedSmoothedAverage;
			int64_t				m_iAllocatedVariation;

	// 5) Hook Function
			TFUNCTION			m_fOnCreateNew;
};


template <class TCONTAINER>
CPoolMemory<TCONTAINER>::CPoolMemory(size_t _sizeAlloc, _In_z_ const _CHAR* _strName, bool _bSustain, eFACTORY_TYPE _eFactoryType) : 
	ICGFactory(),
	CGNameable::NString(_strName),
	m_sizeAlloc(_sizeAlloc),
	m_bEnableSustain(_bSustain),
	m_iAllocatedTermMax(INT64_MIN),
	m_iAllocatedSmoothedAverage(0),
	m_iAllocatedVariation(0),
	m_fOnCreateNew(nullptr)
{
	// 1) Name�� ������ �ʾ��� ��� Object Factory�� Name�� �⺻���� �����Ѵ�.
	if(_strName==nullptr)
	{
		// Declare) 
		_CHAR	temp[MAX_NAME_LENGTH];

		// - �⺻ �̸� ���ڿ��� �����.
		CGSNPRINTF_S(temp, _TRUNCATE, _CGTEXT("memory[%dBytes]"), _sizeAlloc);

		// - �⺻ �̸��� �����Ѵ�.
		SetName(temp);
	}

	// 2) ���� �ʱ�ȭ.
	m_statisticsObject.iExistingLimits = INT64_MAX;

	// 3) Factory Type�� �����Ѵ�.
	m_statisticsObject.eFactoryType	 = _eFactoryType;

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Memory Pool(%s) is created ") _CGFUNCTION, GetName());

	// 4) Factory Manager�� ����Ѵ�.
	RegisterFactory();
}

template <class TCONTAINER>
CPoolMemory<TCONTAINER>::~CPoolMemory()
{
	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Memory Pool(%s:%I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// Check) �� Factory���� ������ ��ü�� �ϳ��� ����� �Ѵ�.
	CGASSERT_ERROR(m_statisticsObject.iExisting==0);

	// Check) ��� ���� ��ü�� ���� 0���̿��� �Ѵ�.
	CGASSERT_ERROR(m_statisticsObject.iInUsing==0);

	// 1) ���� �Ҵ�� ���� 0���� �Ǿ��ٸ� ���� Release�� ���̴�.
	UnregisterFactory();
}

template <class TCONTAINER>
bool CPoolMemory<TCONTAINER>::Destroy()
{
	// 1) Hold�Ѵ�.
	CGPTR<CPoolMemory<TCONTAINER>>	pHold(this);

	// 2) �ִ� ���� ������ -1�� �Ѵ�.
	m_statisticsObject.iExistingLimits	 = -1;

	// 3) Stack�Ǿ� �ִ� Object�� ��� �����.
	_node*	pObject;
	while((pObject = m_stackObject.pop()) != 0)
	{
		// - ��ü�� �ı��Ѵ�.
		ProcessFreeMemory(reinterpret_cast<void*>(pObject));
	}

	// Return)
	return	true;
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::SetOnCreateNewFunction(const TFUNCTION& _pFunction)
{
	m_fOnCreateNew = _pFunction;
}

template <class TCONTAINER>
size_t CPoolMemory<TCONTAINER>::Prepare(size_t _iAmount)
{
	// Check) Prepare�� ���� 0���ٴ� Ŀ���Ѵ�.
	CGASSERT(_iAmount > 0, 0);

	// Check) 0���� �۰ų� ������ Prepare�Ҳ� ������ �׳� ������.
	RETURN_IF(_iAmount <= 0, 0);

	// 1) �ӽ÷� ����� List�� �Ҵ�޴´�.
	vector<void*>	vectorCreated;

	// 2) Reserve�Ѵ�.
	vectorCreated.reserve(_iAmount);

	try
	{
		// 3) Prepare ����ŭ Loop�� ���鼭 �����Ѵ�.
		for(; _iAmount>0; --_iAmount)
		{
			// Declare) ���� �����Ѵ�.
			void*	pCreate = ProcessAllocMemory();

			// - ������ ��ü�� �ӽ� ���ۿ� ¤�� �ִ´�.
			vectorCreated.push_back(pCreate);
		}

		// Trace) 
		CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d Objects is prepared on memory pool[%s] ") _CGFUNCTION, static_cast<int64_t>(vectorCreated.size()), GetName());
	}
	// Exception) 
	catch(...)
	{
		// Trace) 
		CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d objects is prepared on memory pool(%s) [%I64d is failed] ") _CGFUNCTION, static_cast<int64_t>(vectorCreated.size()), GetName(), (int64_t)_iAmount);

		NO_EXCEPTION_BEGIN
		{
			// - Free���� �ʰ� ���� �͵��� �����.
			for (auto& iter : vectorCreated)
			{
				NO_EXCEPTION_BEGIN
				{
					ProcessFreeMemory(iter);
				}
				NO_EXCEPTION_END
			}
		}
		NO_EXCEPTION_END
	}

	// 3) ��հ��� �����Ѵ�.
	m_iAllocatedSmoothedAverage	+= static_cast<int>(vectorCreated.size());

	// ���) In-Using���� ���������ش�.
	m_statisticsObject.iInUsing	+= vectorCreated.size();

	// ���) �Ҵ��� ��ü�� ������ ������Ų��.
	m_statisticsObject.qwAlloc_Create	+= static_cast<int64_t>(vectorCreated.size());

	// 4) Free()�Լ��� ����ؼ� stack�Ѵ�.
	for(auto& iter:vectorCreated)
	{
		Free(iter);
	}

	// Return) ����!!
	return	static_cast<int64_t>(vectorCreated.size());
}

template <class TCONTAINER>
size_t CPoolMemory<TCONTAINER>::Shrink(size_t _iAmount)
{
	// Case) Shrink Exceed
	if(_iAmount==-1)
	{
		_iAmount	 = static_cast<size_t>(m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits);
	}
	// Case) Shrink All
	else if(_iAmount==-2)
	{
		_iAmount	 = m_stackObject.size();
	}

	// Check) _iAmount�� 1���� ������ �׳� ������.
	RETURN_IF(_iAmount<1, 0);

	// 1) Hold�Ѵ�.
	CGPTR<CPoolMemory<TCONTAINER>>	pHold(this);

	// 2) Shrink ����...
	size_t	iShrink	 = 0;

	// 3) Stack�Ǿ� �ִ� Object�� tempShrink��ŭ �����.
	for(; iShrink<_iAmount; ++iShrink)
	{
		// - Pop�� �����Ѵ�.
		_node* pObject	 = m_stackObject.pop();

		// Check) pObject�� nullptr�̸� �ȵȴ�.
		BREAK_IF(pObject==nullptr);

		// Statistics) �ı��� Block�� �ϳ� �ø���.
		++m_statisticsObject.qwFree_Delete;

		// - Object�� Destroy�Ѵ�.
		ProcessFreeMemory(static_cast<void*>(pObject));
	}

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d(%I64d Requested) Stacked memory objects are shrinked in Buffer pool[%s] ") _CGFUNCTION, static_cast<int64_t>(iShrink), static_cast<int64_t>(_iAmount), GetName());

	// 4) ��հ��� ����.
	m_iAllocatedSmoothedAverage	-= iShrink;

	// Return) ����!!
	return	iShrink;
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level)
{
	// Check) No Systain�� true�� Sustain�� �������� �ʴ´�.
	RETURN_IF(m_bEnableSustain==false,);

	// Check) Destroy�Ǿ����� Sustain�� �������� �ʴ´�.
	RETURN_IF(m_statisticsObject.iExistingLimits<0,);

	// Check) 
	if(m_iAllocatedTermMax<0)
	{
		m_iAllocatedTermMax	 = m_statisticsObject.iInUsing;
	}

	// 3) Allocate Max�� ����Ѵ�.
	int64_t	iAllocatedMax	 = ((m_iAllocatedTermMax*9)>>3)+8;

	// 4) Stacked�� ����� ���Ѵ�.
	int64_t	iAllocatedSmoothedAverage	 = ((m_iAllocatedSmoothedAverage*896 + iAllocatedMax*128)>>10);

	// 5) Stacked�� ǥ�������� ���Ѵ�.
	int64_t	iAllocatedVariation			 = ((m_iAllocatedVariation*768+256*((iAllocatedSmoothedAverage>iAllocatedMax) ? (iAllocatedSmoothedAverage-iAllocatedMax) : (iAllocatedMax-iAllocatedSmoothedAverage))+1)>>10);

	// 6) Max Stack�� ���Ѵ�.
	if(m_statisticsObject.iExistingLimits>=0)
	{
		m_statisticsObject.iExistingLimits = iAllocatedSmoothedAverage+(iAllocatedVariation<<2);
	}

	// 5) ���� �ִ´�.
	m_iAllocatedSmoothedAverage		 = iAllocatedSmoothedAverage;
	m_iAllocatedVariation			 = iAllocatedVariation;
	m_iAllocatedTermMax				 = INT_MIN;

	// Declare) 
	size_t	iShrinkAmount	 = 0;

	// 6) Shrink�� ������ ��´�.
	switch(_Level)
	{
	// - �ִ밹���� �ʰ��ϴ� ��ü���� 1/16���� ��� �����Ѵ�.
	case	eFACTORY_SUSTAIN_TYPE::NORMAL:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>3);
			}
			break;
				
	// - �ִ밹���� �ʰ��ϴ� ��ü���� 1/4���� ��� �����Ѵ�.
	case	eFACTORY_SUSTAIN_TYPE::HEAVY:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>1);
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

	// 7) ������ŭ Shrink�Ѵ�.
	Shrink(iShrinkAmount);
}

template <class TCONTAINER>
void* CPoolMemory<TCONTAINER>::ProcessAllocMemory()
{
	// 1) �ϴ� ���� �����ȴ�.
	void*	pMemory	 = CGMALLOC(GetObjectSize());

	// Check) �Ҵ翡 ���������� ������.
	ERROR_THROW_IF(pMemory==nullptr, CGException::CThrow_BadAlloc(), );

	try
	{
		// 2) �ʱ�ȭ
		if(m_fOnCreateNew !=nullptr)
		{
			m_fOnCreateNew(pMemory);
		}

		// 3) �ʱ�ȭ �Լ��� ������ �ʱ�ȭ�Ѵ�.
		OnAllocNew(pMemory);
	}
	catch(...)
	{
		// - ��ü�� �����.
		CGFREE(pMemory);

		// Reraise)
		throw;
	}

	// Statistics) ���� �����ϴ� ��ü�� ���� ������Ų��.
	++m_statisticsObject.iExisting;

	// 4) ��ü�� ������ ������ Add Reference�Ѵ�.
	AddRef();

	// Return) ����!!
	return	pMemory;
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::ProcessFreeMemory(void* _pMemory)
{
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_pMemory != 0,);

	// ���) ���� �����ϴ� ��ü�� ���� ���ҽ�Ų��.
	--m_statisticsObject.iExisting;

	// 1) Hook�Լ�
	NO_EXCEPTION_BEGIN
	{
		OnFree(_pMemory);
	}
	NO_EXCEPTION_END

	// 2) Memory Block�� �����Ѵ�.
	CGFREE(_pMemory);

	// 3) ��ü�� �Ҹ��ų ������ Release�Ѵ�.
	Release();
}

template <class TCONTAINER>
void* CPoolMemory<TCONTAINER>::Alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Declare) 
	_node*	pObject;

	// 1) �ϴ� head�� nullptr�̸� ���� �����ؼ� �����ش�.
	pObject	 = m_stackObject.pop();

	// 2) Stack�� ���� ���ٸ� ���� ���� ������.
	if(pObject != nullptr)
	{
		// ���) Stack�� ���� �Ҵ�� �� ������Ų��.
		++m_statisticsObject.qwAlloc_Stacked;
	}
	else
	{
		// - ���� Object�� �����.
		pObject	 = reinterpret_cast<_node*>(ProcessAllocMemory());

		// ���) �Ҵ��� ��ü�� ������ ������Ų��.
		++m_statisticsObject.qwAlloc_Create;
	}

	// ���) ��� ���� ��ü�� ���� ������Ų��.
	int64_t	countUsing	 = ++m_statisticsObject.iInUsing;

	// Sustain) �ִ� �Ҵ� ���� ���Ѵ�.
	if(countUsing>m_iAllocatedTermMax)
	{
		// - �ִ� �Ҵ����  �����Ѵ�.
		m_iAllocatedTermMax	 = countUsing;

		// - �ִ��Ҵ���� ���� �ִ�ġ�� �Ѿ ��� ���� �ִ���� �����Ѵ�.
		if(countUsing>m_statisticsObject.iExistingLimits && m_statisticsObject.iExistingLimits>=0)
		{
			m_statisticsObject.iExistingLimits	 = ((countUsing*9)>>3)+8;
		}
	} 

	// Check) ó�� �Ҵ�޾��� �� Disuse�� �ݵ�� false���� �Ѵ�.
	CGASSERT_ERROR(pObject->IsDisuse() == false);

	// Return) ����!!
	return	pObject;
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::Free(void* _pMemory)
{
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_pMemory!=nullptr,);

	// ���) ��� ���� ��ü�� ���� ���δ�.
	--m_statisticsObject.iInUsing;

	// 1) ���� Casting�Ѵ�.
	_node*	pObject	 = reinterpret_cast<_node*>(_pMemory);

	// Check) �ִ� �Ѱ� Stack������ Stack�� Memory Block������ ������ �Ҵ������Ѵ�.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
	{
		// Statistics) �ı��� Block�� �ϳ� �ø���.
		++m_statisticsObject.qwFree_Delete;

		// - ��ü�� �ٷ� �����.
		ProcessFreeMemory(pObject);

		// Return) ������.
		return;
	}

	// 2) List�� �߰��Ѵ�.
	m_stackObject.push(pObject);

	// ���) Free;
	++m_statisticsObject.qwFree_Stacked;

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: memory Object is freed in Buffer pool(%s) [Remained:%I64d] ") _CGFUNCTION, GetName(), static_cast<int64_t>(m_stackObject.size()));
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::EnableSustain(_In_ bool _bStatus)
{
	// Check) 
	RETURN_IF(_bStatus==m_bEnableSustain,);

	// 1) ���¸� �ٲ۴�.
	m_bEnableSustain	 = _bStatus;
}


}
