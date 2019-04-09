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

 @class		CPoolMemory
 @brief		정해진 크기의 메모리를 할당해주는 풀이다.
 @todo		
 @ref		CGFactory::CPoolObject<TOBJECT>, CGFactory::CPoolMemoryBlock
 @details	\n
 기본적인 동작은 CGFactory::CPoolObject<TOBJECT>와 동일하다 다만 정해진 크기의 메모리 객체의 할당에 특화된 풀이란 것만이 다르다.
 일반적으로 임의 크기의 메모리를 할당하고자 한다면 CGFactory::CPoolMemoryBlock을 사용하면 된지만 메모리의 낭비가 수반된다.
 하지만 이 풀은 딱 정해진 크기의 메모리 블록만을 풀로 사용하기 때문에 효율적일 수 있다.

 이 풀을 사용하기 위해서는 생성할 때 반드시 할당할 메모리의 크기를 설정해 주어야 한다.
 또 사용중 할당할 메모리의 크기를 변경하지 못한다.

 이 풀 역시 CGFactory::CPoolObject<TOBJECT>와 같이 Prepare(), Shrink() 등의 함수도 사용 가능하며
 Alloc()로 할당하고 Free()로 할당해제한다.

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
	//! @brief 풀 객체를 파괴한다. @return true 성공 @return false 실패 
	virtual	bool				Destroy() override;

	//! @brief _iAmount만큼의 객체를 미리 준비해 놓는다. @param _iAmount 준비할 수량 @return 실제 준비된 량
	virtual	size_t				Prepare(_In_ size_t _iAmount);
	//! @brief _iAmount만큼의 재고 객체를 해제한다. @param _iAmount 해제할 수량 @return 실제 해제된 량
	virtual	size_t				Shrink(_In_ size_t _iAmount);
	//! @brief 적절한 재고량을 계산해 재고량을 넘어서는 량에 대해서는 해제 처리하는 가비지 콜렉션 처리를 한다. @param _Level 레벨해제할 수량 @return 실제 해제된 량
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL);

	//! @brief 풀에서 객체를 할당을 요청한다. @return 할당된 객체
			void*				Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief 풀에 객체를 반환한다. @param _pMemory 반환할 객체
			void				Free(_In_ void* _pMemory);

	//! @brief 객체 당 메모리 크기를 얻는다. @return 객체 당 메모리 크기
	virtual	size_t				GetFactoryObjectSize() const			{	return m_sizeAlloc;}
	//! @brief 재고량을 얻는다. @return 재고량
	virtual	size_t				GetFactoryStackedCount() const			{	return m_stackObject.size();}
	//! @brief 최대 재고량을 얻는다. @return 최대 재고량
	virtual	int64_t				GetFactoryExistingLimits() const		{	return m_statisticsObject.iExistingLimits;}

	//! @brief 풀의 형태를 얻는다. @return 풀의 형태
	virtual	eFACTORY_TYPE			GetFactoryType() const				{	return m_statisticsObject.eFactoryType;}
	//! @brief 풀의 ID를 얻는다. @return 풀의 ID.
	virtual	int					GetFactoryID() const					{	return m_statisticsObject.iFactoryID;}

	//! @brief 가비지콜렉션을 사용하는지 확인한다. @return true 가비지콜렉션 사용 @return false 가비지콜렉션 사용하지 않는다.
	virtual	bool				IsEnableSustain() const					{	return m_bEnableSustain;}
	//! @brief 가비콜렉션 가능 여부를 설정한다. @param _bStatus 가비지콜렉션 동작 여부
	virtual	void				EnableSustain(_In_ bool _bStatus=true);

	//! @brief 새로운 객체를 할당할 때 호출될 함수를 설정한다. @param _pFunction 새로운 객체를 할당할 때 호출될 함수
			void				SetOnCreateNewFunction(_In_ const TFUNCTION& _pFunction);

	//! @brief 대입연산자(Assignment는 절때 쓰지 않는다.)
			void				operator=(const CPoolMemory<TCONTAINER>& /*_rhs*/) _DELETE;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
private:
	// Definition) 
			struct _node		{ _node* Next;};

	// 1) Alloc/Free
	//    - 새로운 Object을 생성하는 절차를 정의한 Process함수.
			void*				ProcessAllocMemory();
			void				ProcessFreeMemory(_In_ void* _pMemory);

	// 2) Hook함수
	virtual	void				OnAllocNew(void* /*_pMemory*/)			{}
	virtual	void				OnFree(void* /*_pMemory*/)				{}

private:
	// 3) Memory Size(이 값은 const값이라 처음 생성할 때 설정한 후 절대로 바꾸지 못한다.)
			const size_t		m_sizeAlloc;

	// 4) Garbage Stack
	//    * 생성된 객체들이 저장될 stack이다.
	//    * Alloc할 경우 여기서 하나 뽑아서 할당해준다.
	//    * Free할 경우 여기다가 다시 저장해 놓는다.
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
	// 1) Name을 정하지 않았을 경우 Object Factory의 Name을 기본으로 설정한다.
	if(_strName==nullptr)
	{
		// Declare) 
		_CHAR	temp[MAX_NAME_LENGTH];

		// - 기본 이름 문자열을 만든다.
		CGSNPRINTF_S(temp, _TRUNCATE, _CGTEXT("memory[%dBytes]"), _sizeAlloc);

		// - 기본 이름을 설정한다.
		SetName(temp);
	}

	// 2) 변수 초기화.
	m_statisticsObject.iExistingLimits = INT64_MAX;

	// 3) Factory Type을 설정한다.
	m_statisticsObject.eFactoryType	 = _eFactoryType;

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Memory Pool(%s) is created ") _CGFUNCTION, GetName());

	// 4) Factory Manager에 등록한다.
	RegisterFactory();
}

template <class TCONTAINER>
CPoolMemory<TCONTAINER>::~CPoolMemory()
{
	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Memory Pool(%s:%I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// Check) 이 Factory에서 생성된 객체는 하나도 없어야 한다.
	CGASSERT_ERROR(m_statisticsObject.iExisting==0);

	// Check) 사용 중인 객체의 수가 0개이여야 한다.
	CGASSERT_ERROR(m_statisticsObject.iInUsing==0);

	// 1) 만약 할당된 것이 0개가 되었다면 완전 Release된 것이다.
	UnregisterFactory();
}

template <class TCONTAINER>
bool CPoolMemory<TCONTAINER>::Destroy()
{
	// 1) Hold한다.
	CGPTR<CPoolMemory<TCONTAINER>>	pHold(this);

	// 2) 최대 유지 갯수를 -1로 한다.
	m_statisticsObject.iExistingLimits	 = -1;

	// 3) Stack되어 있는 Object을 모두 지운다.
	_node*	pObject;
	while((pObject = m_stackObject.pop()) != 0)
	{
		// - 객체를 파괴한다.
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
	// Check) Prepare할 수가 0보다는 커야한다.
	CGASSERT(_iAmount > 0, 0);

	// Check) 0보다 작거나 같으면 Prepare할꺼 같으면 그냥 끝낸다.
	RETURN_IF(_iAmount <= 0, 0);

	// 1) 임시로 사용할 List를 할당받는다.
	vector<void*>	vectorCreated;

	// 2) Reserve한다.
	vectorCreated.reserve(_iAmount);

	try
	{
		// 3) Prepare 수만큼 Loop를 돌면서 생성한다.
		for(; _iAmount>0; --_iAmount)
		{
			// Declare) 새로 생성한다.
			void*	pCreate = ProcessAllocMemory();

			// - 생성된 객체를 임시 버퍼에 짚어 넣는다.
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
			// - Free되지 않고 남은 것들을 지운다.
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

	// 3) 평균값을 수정한다.
	m_iAllocatedSmoothedAverage	+= static_cast<int>(vectorCreated.size());

	// 통계) In-Using수도 증가시켜준다.
	m_statisticsObject.iInUsing	+= vectorCreated.size();

	// 통계) 할당한 객체의 개수를 증가시킨다.
	m_statisticsObject.qwAlloc_Create	+= static_cast<int64_t>(vectorCreated.size());

	// 4) Free()함수를 사용해서 stack한다.
	for(auto& iter:vectorCreated)
	{
		Free(iter);
	}

	// Return) 성공!!
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

	// Check) _iAmount가 1보다 작으면 그냥 끝낸다.
	RETURN_IF(_iAmount<1, 0);

	// 1) Hold한다.
	CGPTR<CPoolMemory<TCONTAINER>>	pHold(this);

	// 2) Shrink 갯수...
	size_t	iShrink	 = 0;

	// 3) Stack되어 있는 Object을 tempShrink만큼 지운다.
	for(; iShrink<_iAmount; ++iShrink)
	{
		// - Pop을 먼저한다.
		_node* pObject	 = m_stackObject.pop();

		// Check) pObject가 nullptr이면 안된다.
		BREAK_IF(pObject==nullptr);

		// Statistics) 파괴된 Block을 하나 늘린다.
		++m_statisticsObject.qwFree_Delete;

		// - Object를 Destroy한다.
		ProcessFreeMemory(static_cast<void*>(pObject));
	}

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d(%I64d Requested) Stacked memory objects are shrinked in Buffer pool[%s] ") _CGFUNCTION, static_cast<int64_t>(iShrink), static_cast<int64_t>(_iAmount), GetName());

	// 4) 평균값을 수정.
	m_iAllocatedSmoothedAverage	-= iShrink;

	// Return) 성공!!
	return	iShrink;
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level)
{
	// Check) No Systain이 true면 Sustain은 수행하지 않는다.
	RETURN_IF(m_bEnableSustain==false,);

	// Check) Destroy되었으면 Sustain을 수행하지 않는다.
	RETURN_IF(m_statisticsObject.iExistingLimits<0,);

	// Check) 
	if(m_iAllocatedTermMax<0)
	{
		m_iAllocatedTermMax	 = m_statisticsObject.iInUsing;
	}

	// 3) Allocate Max을 계산한다.
	int64_t	iAllocatedMax	 = ((m_iAllocatedTermMax*9)>>3)+8;

	// 4) Stacked의 평균을 구한다.
	int64_t	iAllocatedSmoothedAverage	 = ((m_iAllocatedSmoothedAverage*896 + iAllocatedMax*128)>>10);

	// 5) Stacked의 표준편차를 구한다.
	int64_t	iAllocatedVariation			 = ((m_iAllocatedVariation*768+256*((iAllocatedSmoothedAverage>iAllocatedMax) ? (iAllocatedSmoothedAverage-iAllocatedMax) : (iAllocatedMax-iAllocatedSmoothedAverage))+1)>>10);

	// 6) Max Stack을 구한다.
	if(m_statisticsObject.iExistingLimits>=0)
	{
		m_statisticsObject.iExistingLimits = iAllocatedSmoothedAverage+(iAllocatedVariation<<2);
	}

	// 5) 값을 넣는다.
	m_iAllocatedSmoothedAverage		 = iAllocatedSmoothedAverage;
	m_iAllocatedVariation			 = iAllocatedVariation;
	m_iAllocatedTermMax				 = INT_MIN;

	// Declare) 
	size_t	iShrinkAmount	 = 0;

	// 6) Shrink할 갯수를 얻는다.
	switch(_Level)
	{
	// - 최대갯수를 초과하는 객체수의 1/16만을 모두 제거한다.
	case	eFACTORY_SUSTAIN_TYPE::NORMAL:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>3);
			}
			break;
				
	// - 최대갯수를 초과하는 객체수의 1/4만을 모두 제거한다.
	case	eFACTORY_SUSTAIN_TYPE::HEAVY:
			if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
			{
				iShrinkAmount	 = static_cast<size_t>((m_statisticsObject.iExisting-m_statisticsObject.iExistingLimits)>>1);
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

	// 7) 갯수만큼 Shrink한다.
	Shrink(iShrinkAmount);
}

template <class TCONTAINER>
void* CPoolMemory<TCONTAINER>::ProcessAllocMemory()
{
	// 1) 일단 새로 생성된다.
	void*	pMemory	 = CGMALLOC(GetObjectSize());

	// Check) 할당에 실패했으면 던진다.
	ERROR_THROW_IF(pMemory==nullptr, CGException::CThrow_BadAlloc(), );

	try
	{
		// 2) 초기화
		if(m_fOnCreateNew !=nullptr)
		{
			m_fOnCreateNew(pMemory);
		}

		// 3) 초기화 함수가 있으면 초기화한다.
		OnAllocNew(pMemory);
	}
	catch(...)
	{
		// - 객체를 지운다.
		CGFREE(pMemory);

		// Reraise)
		throw;
	}

	// Statistics) 현재 존재하는 객체의 수를 증가시킨다.
	++m_statisticsObject.iExisting;

	// 4) 객체를 생성할 때마다 Add Reference한다.
	AddRef();

	// Return) 성공!!
	return	pMemory;
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::ProcessFreeMemory(void* _pMemory)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_pMemory != 0,);

	// 통계) 현재 존재하는 객체의 수를 감소시킨다.
	--m_statisticsObject.iExisting;

	// 1) Hook함수
	NO_EXCEPTION_BEGIN
	{
		OnFree(_pMemory);
	}
	NO_EXCEPTION_END

	// 2) Memory Block을 해제한다.
	CGFREE(_pMemory);

	// 3) 객체를 소멸시킬 때마다 Release한다.
	Release();
}

template <class TCONTAINER>
void* CPoolMemory<TCONTAINER>::Alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Declare) 
	_node*	pObject;

	// 1) 일단 head이 nullptr이면 새로 생성해서 보내준다.
	pObject	 = m_stackObject.pop();

	// 2) Stack된 것이 없다면 새로 만들어서 보낸다.
	if(pObject != nullptr)
	{
		// 통계) Stack된 것을 할당된 량 증가시킨다.
		++m_statisticsObject.qwAlloc_Stacked;
	}
	else
	{
		// - 새로 Object을 만든다.
		pObject	 = reinterpret_cast<_node*>(ProcessAllocMemory());

		// 통계) 할당한 객체의 개수를 증가시킨다.
		++m_statisticsObject.qwAlloc_Create;
	}

	// 통계) 사용 중인 객체의 수를 증가시킨다.
	int64_t	countUsing	 = ++m_statisticsObject.iInUsing;

	// Sustain) 최대 할당 수를 구한다.
	if(countUsing>m_iAllocatedTermMax)
	{
		// - 최대 할당수를  갱신한다.
		m_iAllocatedTermMax	 = countUsing;

		// - 최대할당수가 생성 최대치를 넘어설 경우 생성 최대수를 수정한다.
		if(countUsing>m_statisticsObject.iExistingLimits && m_statisticsObject.iExistingLimits>=0)
		{
			m_statisticsObject.iExistingLimits	 = ((countUsing*9)>>3)+8;
		}
	} 

	// Check) 처음 할당받았을 때 Disuse는 반드시 false여야 한다.
	CGASSERT_ERROR(pObject->IsDisuse() == false);

	// Return) 성공!!
	return	pObject;
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::Free(void* _pMemory)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_pMemory!=nullptr,);

	// 통계) 사용 중인 객체의 수를 줄인다.
	--m_statisticsObject.iInUsing;

	// 1) 먼저 Casting한다.
	_node*	pObject	 = reinterpret_cast<_node*>(_pMemory);

	// Check) 최대 한계 Stack수보다 Stack된 Memory Block갯수가 많으면 할당해제한다.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits)
	{
		// Statistics) 파괴된 Block을 하나 늘린다.
		++m_statisticsObject.qwFree_Delete;

		// - 객체를 바로 지운다.
		ProcessFreeMemory(pObject);

		// Return) 끝낸다.
		return;
	}

	// 2) List에 추가한다.
	m_stackObject.push(pObject);

	// 통계) Free;
	++m_statisticsObject.qwFree_Stacked;

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: memory Object is freed in Buffer pool(%s) [Remained:%I64d] ") _CGFUNCTION, GetName(), static_cast<int64_t>(m_stackObject.size()));
}

template <class TCONTAINER>
void CPoolMemory<TCONTAINER>::EnableSustain(_In_ bool _bStatus)
{
	// Check) 
	RETURN_IF(_bStatus==m_bEnableSustain,);

	// 1) 상태를 바꾼다.
	m_bEnableSustain	 = _bStatus;
}


}
