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

 @class		CPoolBuffer
 @brief		�޽����� �޸�Ǯ
 @todo		
 @ref		CGFactory::CPoolBuffer
 @details	\n
 �޸� ��ü Ǯ�� �⺻���� ���� CGFactory::CPoolMemory�� �����ϴ�.
 CGFactory::CPoolMemory�� ��� �޸��� ������ �ʱ�ȭ�Ҽ� �� �������� �̰��� �ʱ�ȭ�� ���شٴ� �͸� �ٸ���.
 ���� �޸� ��ü�� �űԷ� ������ �Ҵ����� �� �ش� �޸𸮸� �ʱ�ȭ���ֱ� ���� �Լ��� ������ �� �ִ�.

*/
//-----------------------------------------------------------------------------
template <size_t ISIZE>
class CPoolBuffer : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGFactory,								//     ICGFactory
	public						CGNameable::NString						// (@) Nameable
{
// ****************************************************************************
// Definition)
// ----------------------------------------------------------------------------
public:
	class						MEMORY;
	typedef	std::function<void(CCGBuffer&)>	TFUNCTION;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CPoolBuffer(_In_ const TFUNCTION& _pFunction, _In_opt_z_ const _CHAR* _strName=nullptr, _In_ bool _bSustain=true, _In_ eFACTORY_TYPE _eFactoryType=eFACTORY_TYPE::POOL_USER);
			CPoolBuffer(_In_ const TFUNCTION& _pFunction, _In_opt_z_ const _CHAR_SUB* _strName=nullptr, _In_ bool _bSustain=true, _In_ eFACTORY_TYPE _eFactoryType=eFACTORY_TYPE::POOL_USER);
	virtual	~CPoolBuffer();


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
			CCGBuffer			Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief Ǯ�� ��ü�� ��ȯ�Ѵ�. @param _pMemory ��ȯ�� ��ü
			void				Free(_In_ MEMORY* _pMemory);

	//! @brief ��ü �� �޸� ũ�⸦ ��´�. @return ��ü �� �޸� ũ��
	virtual	size_t				GetObjectSize() const					{	return ISIZE;}
	//! @brief ����� ��´�. @return ���
	virtual	size_t				GetStackedCount() const					{	return m_stackMemory.size();}
	//! @brief �ִ� ����� ��´�. @return �ִ� ���
	virtual	int64_t				GetExistingLimits() const				{	return m_statisticsObject.iExistingLimits;}

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
	#if defined(_MSC_VER)
			void				operator=(const CPoolBuffer<ISIZE>& /*_rhs*/) _DELETE
	#endif

// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	// Definitions)
	class MEMORY : public ICGBuffer, public ICGPoolable<MEMORY>
	{
	public:
				MEMORY();
		virtual ~MEMORY();
	private:
		virtual	void			ProcessDispose() override	{	m_pPool->Free(this);}
	public:
				CGPTR<CPoolBuffer>	m_pPool;
	};

protected:
	//! @brief �޸� ���۸� �Ҵ��ϴ� ������ �����Ѵ�. @return ������ ��ü
			MEMORY*				ProcessCreateBuffer();
	//! @brief �޸� ���۸� �ı���Ű�� ������ �����Ѵ�. @param _Object �ı���ų ��ü
			void				ProcessDestroyBuffer(_In_ MEMORY* _pMemory);
	//! @brief �޸� ������ �Ҵ��� ��û�Ѵ�. @return ������ ��ü
	virtual	MEMORY*				CreateBuffer();

	//! @brief �޸� ���۸� �Ҵ��� �� ȣ���ϴ� �Լ� @param _Object ���� ������ ��ü
	virtual	void				OnCreateNew(MEMORY* /*_pMemory*/)		{}
	//! @brief �޸� ���۸� �Ҵ������� �� ȣ���ϴ� �Լ� @param _Object ���� ������ ��ü
	virtual	void				OnDestroy(MEMORY* /*_pMemory*/)		{}

protected:
	// 3) ��� ��ü Stack
			LOCKFREE_SELF_STACK<MEMORY*>	m_stackMemory;

	// 4) Lambda function
			uint32_t			m_iBufferLen;
			TFUNCTION			m_fOnCreateNew;

	// 5) Pool Sustainment�� ���� ������
			bool				m_bEnableSustain;
			int64_t				m_iAllocatedTermMax;
			int64_t				m_iAllocatedSmoothedAverage;
			int64_t				m_iAllocatedVariation;
};

template <size_t ISIZE>
CPoolBuffer<ISIZE>::MEMORY::MEMORY()
{
	// 1) �޸𸮸� �����մϴ�.(Aligned�� Memory�� �Ҵ�޴´�.)
	buf		 = reinterpret_cast<char*>(CGMALLOC(ISIZE));

	// Check) �Ҵ翡 ���������� ������.
	ERROR_THROW_IF(buf==nullptr, CGException::CThrow_BadAlloc(), );

	// 2) Len�� �����Ѵ�.
	len		 = ISIZE;
}

template <size_t ISIZE>
CPoolBuffer<ISIZE>::MEMORY::~MEMORY()
{
	// 1) �Ҵ������Ѵ�.
	CGFREE(buf);
}

template <size_t ISIZE>
CPoolBuffer<ISIZE>::CPoolBuffer(const TFUNCTION& _pFunction, _In_opt_z_ const _CHAR* _strName, bool _bSustain, eFACTORY_TYPE _eFactoryType) : 
	CGNameable::NString(_strName),
	m_bEnableSustain(_bSustain),
	m_iAllocatedTermMax(INT64_MIN),
	m_iAllocatedSmoothedAverage(0),
	m_iAllocatedVariation(0),
	m_fOnCreateNew(nullptr)
{
	// 1) Name�� ������ �ʾ��� ��� Object Factory�� Name�� �⺻���� �����Ѵ�.
	if(_strName==nullptr)
	{
		SetName(_CGTEXT("Preset buffer pool"));
	}

	// 2) ���� �ʱ�ȭ�Ѵ�.
	m_statisticsObject.iExistingLimits = INT64_MAX;

	// 3) Factory Type�� �����Ѵ�.
	m_statisticsObject.eFactoryType	 = _eFactoryType;

	// 4) �Լ��� �����Ѵ�.
	SetOnCreateNewFunction(_pFunction);

	// Trace) 
	CGLOG_INFO(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Buffer pool(%s) is created ") _CGFUNCTION, GetName());

	// 5) Factory Manager�� ����Ѵ�.
	RegisterFactory();
}

template <size_t ISIZE>
CPoolBuffer<ISIZE>::CPoolBuffer(const TFUNCTION& _pFunction, _In_opt_z_ const _CHAR_SUB* _strName, bool _bSustain, eFACTORY_TYPE _eFactoryType) : 
	CGNameable::NString(_strName),
	m_fOnCreateNew(nullptr)
{
	// 1) Name�� ������ �ʾ��� ��� Object Factory�� Name�� �⺻���� �����Ѵ�.
	if(_strName==nullptr)
	{
		SetName(_CGTEXT("Preset buffer pool"));
	}

	// 2) ���� �ʱ�ȭ�Ѵ�.
	m_statisticsObject.iExistingLimits = INT64_MAX;

	// 3) Factory Type�� �����Ѵ�.
	m_statisticsObject.eFactoryType	 = _eFactoryType;

	// 4) Sustain�� ���� �ʱⰪ ����
	m_bEnableSustain			 = _bSustain;
	m_iAllocatedSmoothedAverage	 = 0;
	m_iAllocatedVariation		 = 0;
	m_iAllocatedTermMax			 = INT64_MIN;

	// 5) �Լ��� �����Ѵ�.
	SetOnCreateNewFunction(_pFunction);

	// Trace) 
	CGLOG_INFO(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Buffer pool(%s) is created ") _CGFUNCTION, GetName());

	// 6) Factory Manager�� ����Ѵ�.
	RegisterFactory();
}

template <size_t ISIZE>
CPoolBuffer<ISIZE>::~CPoolBuffer()
{
	// Trace) 
	CGLOG_INFO(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Buffer pool(%s: %I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// Check) �����ϴ� ��ü�� ������ 0������ �Ѵ�.
	CGASSERT_ERROR(m_statisticsObject.iExisting==0);

	// Check) ��� ���� ��ü�� ���� 0���̿��� �Ѵ�.
	CGASSERT_ERROR(m_statisticsObject.iInUsing==0);

	// 1) Factory Manager�� ��������Ѵ�.
	UnregisterFactory();
}

template <size_t ISIZE>
bool CPoolBuffer<ISIZE>::Destroy()
{
	// 1) Hold�Ѵ�.
	CGPTR<CPoolBuffer<ISIZE>>	pHold(this);

	// 2) �ִ� ���� ������ -1�� �Ѵ�.
	m_statisticsObject.iExistingLimits	 = -1;

	// 3) Stack�Ǿ� �ִ� Object�� ��� �����.
	MEMORY*	pMemory;
	while((pMemory = m_stackMemory.pop()) != nullptr)
	{
		// - ��ü�� �ı��Ѵ�.
		ProcessDestroyBuffer(pMemory);
	}

	// Return)
	return	true;
}

template <size_t ISIZE>
void CPoolBuffer<ISIZE>::SetOnCreateNewFunction(const TFUNCTION& _pFunction)
{
	// Declare) 
	char		chBuffer[ISIZE]	 = {0, };
	CCGBuffer	bufferMemory(CGD::buffer(chBuffer, 0));

	// 1) Buffer�� ���̸� ��� �����Ѵ�.
	_pFunction(bufferMemory);
	m_iBufferLen	 = bufferMemory.len;

	// Check) �Ҵ���� Buffer�� ũ��(SIZE)���� ������ ������ ���̰� ª�ƾ� �Ѵ�.
	CGASSERT_ERROR(bufferMemory.len<=ISIZE);

	// 2) Setting
	m_fOnCreateNew = _pFunction;
}

template <size_t ISIZE>
size_t CPoolBuffer<ISIZE>::Prepare(size_t _iAmount)
{
	// Check) Prepare�� ���� 0���ٴ� Ŀ���Ѵ�.
	CGASSERT(_iAmount > 0, 0);

	// Check) 0���� �۰ų� ������ Prepare�Ҳ� ������ �׳� ������.
	RETURN_IF(_iAmount <= 0, 0);

	// 1) �ӽ÷� ����� List�� �Ҵ�޴´�.
	vector<MEMORY*>	vectorCreated;

	// 2) Reserve�Ѵ�.
	vectorCreated.reserve(_iAmount);

	try
	{
		// 3) Prepare ����ŭ Loop�� ���鼭 �����Ѵ�.
		for(; _iAmount>0; --_iAmount)
		{
			// Declare) ���� �����Ѵ�.
			MEMORY*		pMemory = ProcessCreateBuffer();

			// - ������ ��ü�� �ӽ� ���ۿ� ¤�� �ִ´�.
			vectorCreated.push_back(pMemory);
		}

		// Trace) 
		CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d Objects is prepared on Buffer pool(%s) ") _CGFUNCTION, static_cast<int64_t>(vectorCreated.size()), GetName());
	}
	// Exception) 
	catch(...)
	{
		// Trace) 
		CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d objects is prepared on Buffer pool(%s)  [%I64d is failed] ") _CGFUNCTION, static_cast<int64_t>(vectorCreated.size()), GetName(), static_cast<int64_t>(_iAmount));

		NO_EXCEPTION_BEGIN
		{
			// - Free���� �ʰ� ���� �͵��� �����.
			for (auto iter : vectorCreated)
			{
				// - �Ҵ�޾Ҵ� Object���� �����.
				NO_EXCEPTION_BEGIN
				{
					ProcessDestroyBuffer(iter);
				}
				NO_EXCEPTION_END
			}
		}
		NO_EXCEPTION_END
	}

	// 3) ��հ��� �����Ѵ�.
	m_iAllocatedSmoothedAverage	+= vectorCreated.size();

	// ���) In-Using���� ���������ش�.
	m_statisticsObject.iInUsing	+= static_cast<int>(vectorCreated.size());

	// ���) �Ҵ��� ��ü�� ������ ������Ų��.
	m_statisticsObject.qwAlloc_Create	+= static_cast<int64_t>(vectorCreated.size());

	// 2) Free()�Լ��� ����ؼ� stack�Ѵ�.
	for(auto iter:vectorCreated)
	{
		Free(iter);
	}

	// Return) ����!!
	return	vectorCreated.size();
}

template <size_t ISIZE>
size_t CPoolBuffer<ISIZE>::Shrink(size_t _iAmount)
{
	// Case) Shrink Exceed
	if(_iAmount==-1)
	{
		_iAmount	 = static_cast<size_t>(m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits);
	}
	// Case) Shrink All
	else if(_iAmount==-2)
	{
		_iAmount	 = m_stackMemory.size();
	}

	// Check) _iAmount�� 1���� ������ �׳� ������.
	RETURN_IF(_iAmount<1, 0);

	// 1) Hold�Ѵ�.
	CGPTR<CPoolBuffer<ISIZE>>	pHold(this);

	// 2) Shrink ����...
	size_t	iShrink	 = 0;

	// 3) Stack�Ǿ� �ִ� Object�� tempShrink��ŭ �����.
	for(; iShrink<_iAmount; ++iShrink)
	{
		// - Pop�� �����Ѵ�.
		MEMORY* pMemory	 = m_stackMemory.pop();

		// Check) pMemory�� nullptr�̸� �ȵȴ�.
		BREAK_IF(pMemory==nullptr);

		// Statistics) �ı��� Block�� �ϳ� �ø���.
		++m_statisticsObject.qwFree_Delete;

		// - Object�� Destroy�Ѵ�.
		ProcessDestroyBuffer(pMemory);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d(%I64d is Requested) bufferes are shrinked in Buffer pool(%s) ") _CGFUNCTION, static_cast<int64_t>(iShrink), (int64_t)_iAmount, GetName());

	// 4) ��հ��� ����.
	m_iAllocatedSmoothedAverage	-= iShrink;
	
	// Return) ����!!
	return	iShrink;
}

template <size_t ISIZE>
void CPoolBuffer<ISIZE>::Sustain(eFACTORY_SUSTAIN_TYPE _Level)
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

	// 1) MaxStack�� ����Ѵ�.
	int64_t	iAllocatedMax	 = ((m_iAllocatedTermMax*9)>>3)+8;

	// 2) Stacked�� ����� ���Ѵ�.
	int64_t	iAllocatedSmoothedAverage	 = ((m_iAllocatedSmoothedAverage*896 + iAllocatedMax*128)>>10);

	// 3) Stacked�� ǥ�������� ���Ѵ�.
	int64_t	iAllocatedVariation			 = ((m_iAllocatedVariation*768+256*((iAllocatedSmoothedAverage>iAllocatedMax) ? (iAllocatedSmoothedAverage-iAllocatedMax) : (iAllocatedMax-iAllocatedSmoothedAverage))+1)>>10);

	// 4) Max Stack�� ���Ѵ�.
	if(m_statisticsObject.iExistingLimits>=0)
	{
		m_statisticsObject.iExistingLimits = static_cast<size_t>(iAllocatedSmoothedAverage+(iAllocatedVariation<<2));
	}

	// 5) ���� �ִ´�.
	m_iAllocatedSmoothedAverage		 = iAllocatedSmoothedAverage;
	m_iAllocatedVariation			 = iAllocatedVariation;
	m_iAllocatedTermMax				 = INT64_MIN;

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

template <size_t ISIZE>
typename CPoolBuffer<ISIZE>::MEMORY* CPoolBuffer<ISIZE>::CreateBuffer()
{
	return	new MEMORY;
}

template <size_t ISIZE>
typename CPoolBuffer<ISIZE>::MEMORY* CPoolBuffer<ISIZE>::ProcessCreateBuffer()
{
	// 1) �ϴ� ���� �����ȴ�.
	MEMORY*	pMemory	 = CreateBuffer();	// (���⼭ Exception�߻� ����.)

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Create object on Buffer pool(%s) ") _CGFUNCTION, GetName());

	// ���) ���� �����ϴ� ��ü�� ���� ������Ų��.
	++m_statisticsObject.iExisting;

	// 2) Factory�� Setting�Ѵ�. (���⼭ Factory�� Reference Counting�� 1������Ű�� �ȴ�.)
	pMemory->m_pPool	 = this;

	// Declare) 
	CCGBuffer	tempBuffer(CGD::buffer(pMemory->buf, 0));

	// 3) Buffer�� ���� ����.
	if (m_fOnCreateNew != nullptr)
	{
		m_fOnCreateNew(tempBuffer);
	}

	// 4) Hook �Լ� ȣ��
	OnCreateNew(pMemory);

	// Check)
	CGASSERT_ERROR(tempBuffer.len==m_iBufferLen);

	// Return) ����!!
	return	pMemory;
}

template <size_t ISIZE>
void CPoolBuffer<ISIZE>::ProcessDestroyBuffer(MEMORY* _pMemory)
{
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_pMemory != nullptr,);

	// 1) Hook �Լ� ȣ��
	OnDestroy(_pMemory);

	// Statistics) ���� �����ϴ� ��ü�� ���� ���ҽ�Ų��.
	--m_statisticsObject.iExisting;

	// 2) DestroyObject�Լ��� ȣ���Ͽ� Object�� �����.
	delete	_pMemory;
}

template <size_t ISIZE>
CCGBuffer CPoolBuffer<ISIZE>::Alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Declare) 
	MEMORY*	pMemory;

	// 1) �ϴ� head�� nullptr�̸� ���� �����ؼ� �����ش�.
	pMemory	 = m_stackMemory.pop();

	// 2) Stack�� ���� ���ٸ� ���� ���� ������.
	if(pMemory != reinterpret_cast<MEMORY*>(nullptr))
	{
		// ���) Stack�� ���� �Ҵ�� �� ������Ų��.
		++m_statisticsObject.qwAlloc_Stacked;

		// Trace)
		CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Object is allocated in Buffer pool(%s) [Remained:%I64d] ") _CGFUNCTION, GetName(), static_cast<int64_t>(m_stackMemory.size()));
	}
	else
	{
		// - ���� Object�� �����.
		pMemory	 = ProcessCreateBuffer();

		// ���) �Ҵ��� ��ü�� ������ ������Ų��.
		++m_statisticsObject.qwAlloc_Create;
	}

	// Statistics) ��� ���� ��ü�� ���� ������Ų��.
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
	
	// Return) ����!!
	return	CCGBuffer(CGD::buffer(pMemory->buf, m_iBufferLen), pMemory);
}

template <size_t ISIZE>
void CPoolBuffer<ISIZE>::Free(MEMORY* _pMemory)
{
	// Check) _pMemory�� nullptr�̾�� �ȵȴ�.
	CGASSERT(_pMemory!=nullptr,);

	// Statistics) ��� ���� ��ü�� ���� ���δ�.
	--m_statisticsObject.iInUsing;

	// Check) �ִ� �Ѱ� Stack������ Stack�� Memory Block������ ������ �Ҵ������Ѵ�.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits || _pMemory->IsDisuse())
	{
		// Statistics) �ı��� Block�� �ϳ� �ø���.
		++m_statisticsObject.qwFree_Delete;

		// - ��ü�� �ٷ� �����.
		ProcessDestroyBuffer (_pMemory);

		// Return) ������.
		return;
	}

	// 1) List�� �߰��Ѵ�.
	m_stackMemory.push(_pMemory);

	// Statistics) Free
	++m_statisticsObject.qwFree_Stacked;

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Object is freed in Buffer pool(%s) [Remained:%I64d] ") _CGFUNCTION, GetName(), static_cast<int64_t>(m_stackMemory.size()));
}

template <size_t ISIZE>
void CPoolBuffer<ISIZE>::EnableSustain(_In_ bool _bStatus)
{
	// Check) 
	RETURN_IF(_bStatus==m_bEnableSustain,);

	// 1) ���¸� �ٲ۴�.
	m_bEnableSustain	 = _bStatus;
}


}
