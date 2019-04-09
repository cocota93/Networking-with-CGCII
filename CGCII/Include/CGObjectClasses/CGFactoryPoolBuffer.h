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

 @class		CPoolBuffer
 @brief		메시지용 메모리풀
 @todo		
 @ref		CGFactory::CPoolBuffer
 @details	\n
 메모리 객체 풀로 기본적인 것은 CGFactory::CPoolMemory와 동일하다.
 CGFactory::CPoolMemory의 경우 메모리의 내용을 초기화할수 는 없었지만 이것은 초기화를 해준다는 것만 다르다.
 따라서 메모리 객체를 신규로 생성해 할당해줄 때 해당 메모리를 초기화해주기 위한 함수를 설정할 수 있다.

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
	//! @brief 풀 객체를 파괴한다. @return true 성공 @return false 실패 
	virtual	bool				Destroy() override;

	//! @brief _iAmount만큼의 객체를 미리 준비해 놓는다. @param _iAmount 준비할 수량 @return 실제 준비된 량
	virtual	size_t				Prepare(_In_ size_t _iAmount);
	//! @brief _iAmount만큼의 재고 객체를 해제한다. @param _iAmount 해제할 수량 @return 실제 해제된 량
	virtual	size_t				Shrink(_In_ size_t _iAmount);
	//! @brief 적절한 재고량을 계산해 재고량을 넘어서는 량에 대해서는 해제 처리하는 가비지 콜렉션 처리를 한다. @param _Level 레벨해제할 수량 @return 실제 해제된 량
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL);

	//! @brief 풀에서 객체를 할당을 요청한다. @return 할당된 객체
			CCGBuffer			Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief 풀에 객체를 반환한다. @param _pMemory 반환할 객체
			void				Free(_In_ MEMORY* _pMemory);

	//! @brief 객체 당 메모리 크기를 얻는다. @return 객체 당 메모리 크기
	virtual	size_t				GetObjectSize() const					{	return ISIZE;}
	//! @brief 재고량을 얻는다. @return 재고량
	virtual	size_t				GetStackedCount() const					{	return m_stackMemory.size();}
	//! @brief 최대 재고량을 얻는다. @return 최대 재고량
	virtual	int64_t				GetExistingLimits() const				{	return m_statisticsObject.iExistingLimits;}

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
	//! @brief 메모리 버퍼를 할당하는 과정을 정의한다. @return 생성된 객체
			MEMORY*				ProcessCreateBuffer();
	//! @brief 메모리 버퍼를 파괴시키는 과정을 정의한다. @param _Object 파괴시킬 객체
			void				ProcessDestroyBuffer(_In_ MEMORY* _pMemory);
	//! @brief 메모리 버퍼의 할당을 요청한다. @return 생성된 객체
	virtual	MEMORY*				CreateBuffer();

	//! @brief 메모리 버퍼를 할당할 때 호출하는 함수 @param _Object 새로 생성한 객체
	virtual	void				OnCreateNew(MEMORY* /*_pMemory*/)		{}
	//! @brief 메모리 버퍼를 할당해제할 때 호출하는 함수 @param _Object 새로 생성한 객체
	virtual	void				OnDestroy(MEMORY* /*_pMemory*/)		{}

protected:
	// 3) 재고 객체 Stack
			LOCKFREE_SELF_STACK<MEMORY*>	m_stackMemory;

	// 4) Lambda function
			uint32_t			m_iBufferLen;
			TFUNCTION			m_fOnCreateNew;

	// 5) Pool Sustainment를 위한 변수들
			bool				m_bEnableSustain;
			int64_t				m_iAllocatedTermMax;
			int64_t				m_iAllocatedSmoothedAverage;
			int64_t				m_iAllocatedVariation;
};

template <size_t ISIZE>
CPoolBuffer<ISIZE>::MEMORY::MEMORY()
{
	// 1) 메모리를 생성합니다.(Aligned된 Memory로 할당받는다.)
	buf		 = reinterpret_cast<char*>(CGMALLOC(ISIZE));

	// Check) 할당에 실패했으면 던진다.
	ERROR_THROW_IF(buf==nullptr, CGException::CThrow_BadAlloc(), );

	// 2) Len을 설정한다.
	len		 = ISIZE;
}

template <size_t ISIZE>
CPoolBuffer<ISIZE>::MEMORY::~MEMORY()
{
	// 1) 할당해제한다.
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
	// 1) Name을 정하지 않았을 경우 Object Factory의 Name을 기본으로 설정한다.
	if(_strName==nullptr)
	{
		SetName(_CGTEXT("Preset buffer pool"));
	}

	// 2) 값을 초기화한다.
	m_statisticsObject.iExistingLimits = INT64_MAX;

	// 3) Factory Type을 설정한다.
	m_statisticsObject.eFactoryType	 = _eFactoryType;

	// 4) 함수를 설정한다.
	SetOnCreateNewFunction(_pFunction);

	// Trace) 
	CGLOG_INFO(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Buffer pool(%s) is created ") _CGFUNCTION, GetName());

	// 5) Factory Manager에 등록한다.
	RegisterFactory();
}

template <size_t ISIZE>
CPoolBuffer<ISIZE>::CPoolBuffer(const TFUNCTION& _pFunction, _In_opt_z_ const _CHAR_SUB* _strName, bool _bSustain, eFACTORY_TYPE _eFactoryType) : 
	CGNameable::NString(_strName),
	m_fOnCreateNew(nullptr)
{
	// 1) Name을 정하지 않았을 경우 Object Factory의 Name을 기본으로 설정한다.
	if(_strName==nullptr)
	{
		SetName(_CGTEXT("Preset buffer pool"));
	}

	// 2) 값을 초기화한다.
	m_statisticsObject.iExistingLimits = INT64_MAX;

	// 3) Factory Type을 설정한다.
	m_statisticsObject.eFactoryType	 = _eFactoryType;

	// 4) Sustain을 위한 초기값 설장
	m_bEnableSustain			 = _bSustain;
	m_iAllocatedSmoothedAverage	 = 0;
	m_iAllocatedVariation		 = 0;
	m_iAllocatedTermMax			 = INT64_MIN;

	// 5) 함수를 설정한다.
	SetOnCreateNewFunction(_pFunction);

	// Trace) 
	CGLOG_INFO(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Buffer pool(%s) is created ") _CGFUNCTION, GetName());

	// 6) Factory Manager에 등록한다.
	RegisterFactory();
}

template <size_t ISIZE>
CPoolBuffer<ISIZE>::~CPoolBuffer()
{
	// Trace) 
	CGLOG_INFO(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Buffer pool(%s: %I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// Check) 존재하는 객체의 갯수는 0개여야 한다.
	CGASSERT_ERROR(m_statisticsObject.iExisting==0);

	// Check) 사용 중인 객체의 수가 0개이여야 한다.
	CGASSERT_ERROR(m_statisticsObject.iInUsing==0);

	// 1) Factory Manager에 등록해제한다.
	UnregisterFactory();
}

template <size_t ISIZE>
bool CPoolBuffer<ISIZE>::Destroy()
{
	// 1) Hold한다.
	CGPTR<CPoolBuffer<ISIZE>>	pHold(this);

	// 2) 최대 유지 갯수를 -1로 한다.
	m_statisticsObject.iExistingLimits	 = -1;

	// 3) Stack되어 있는 Object을 모두 지운다.
	MEMORY*	pMemory;
	while((pMemory = m_stackMemory.pop()) != nullptr)
	{
		// - 객체를 파괴한다.
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

	// 1) Buffer의 길이를 얻어 저장한다.
	_pFunction(bufferMemory);
	m_iBufferLen	 = bufferMemory.len;

	// Check) 할당받은 Buffer의 크기(SIZE)보다 쓰여진 내용의 길이가 짧아야 한다.
	CGASSERT_ERROR(bufferMemory.len<=ISIZE);

	// 2) Setting
	m_fOnCreateNew = _pFunction;
}

template <size_t ISIZE>
size_t CPoolBuffer<ISIZE>::Prepare(size_t _iAmount)
{
	// Check) Prepare할 수가 0보다는 커야한다.
	CGASSERT(_iAmount > 0, 0);

	// Check) 0보다 작거나 같으면 Prepare할꺼 같으면 그냥 끝낸다.
	RETURN_IF(_iAmount <= 0, 0);

	// 1) 임시로 사용할 List를 할당받는다.
	vector<MEMORY*>	vectorCreated;

	// 2) Reserve한다.
	vectorCreated.reserve(_iAmount);

	try
	{
		// 3) Prepare 수만큼 Loop를 돌면서 생성한다.
		for(; _iAmount>0; --_iAmount)
		{
			// Declare) 새로 생성한다.
			MEMORY*		pMemory = ProcessCreateBuffer();

			// - 생성된 객체를 임시 버퍼에 짚어 넣는다.
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
			// - Free되지 않고 남은 것들을 지운다.
			for (auto iter : vectorCreated)
			{
				// - 할당받았던 Object들을 지운다.
				NO_EXCEPTION_BEGIN
				{
					ProcessDestroyBuffer(iter);
				}
				NO_EXCEPTION_END
			}
		}
		NO_EXCEPTION_END
	}

	// 3) 평균값을 수정한다.
	m_iAllocatedSmoothedAverage	+= vectorCreated.size();

	// 통계) In-Using수도 증가시켜준다.
	m_statisticsObject.iInUsing	+= static_cast<int>(vectorCreated.size());

	// 통계) 할당한 객체의 개수를 증가시킨다.
	m_statisticsObject.qwAlloc_Create	+= static_cast<int64_t>(vectorCreated.size());

	// 2) Free()함수를 사용해서 stack한다.
	for(auto iter:vectorCreated)
	{
		Free(iter);
	}

	// Return) 성공!!
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

	// Check) _iAmount가 1보다 작으면 그냥 끝낸다.
	RETURN_IF(_iAmount<1, 0);

	// 1) Hold한다.
	CGPTR<CPoolBuffer<ISIZE>>	pHold(this);

	// 2) Shrink 갯수...
	size_t	iShrink	 = 0;

	// 3) Stack되어 있는 Object을 tempShrink만큼 지운다.
	for(; iShrink<_iAmount; ++iShrink)
	{
		// - Pop을 먼저한다.
		MEMORY* pMemory	 = m_stackMemory.pop();

		// Check) pMemory가 nullptr이면 안된다.
		BREAK_IF(pMemory==nullptr);

		// Statistics) 파괴된 Block을 하나 늘린다.
		++m_statisticsObject.qwFree_Delete;

		// - Object를 Destroy한다.
		ProcessDestroyBuffer(pMemory);
	}

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: %I64d(%I64d is Requested) bufferes are shrinked in Buffer pool(%s) ") _CGFUNCTION, static_cast<int64_t>(iShrink), (int64_t)_iAmount, GetName());

	// 4) 평균값을 수정.
	m_iAllocatedSmoothedAverage	-= iShrink;
	
	// Return) 성공!!
	return	iShrink;
}

template <size_t ISIZE>
void CPoolBuffer<ISIZE>::Sustain(eFACTORY_SUSTAIN_TYPE _Level)
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

	// 1) MaxStack을 계산한다.
	int64_t	iAllocatedMax	 = ((m_iAllocatedTermMax*9)>>3)+8;

	// 2) Stacked의 평균을 구한다.
	int64_t	iAllocatedSmoothedAverage	 = ((m_iAllocatedSmoothedAverage*896 + iAllocatedMax*128)>>10);

	// 3) Stacked의 표준편차를 구한다.
	int64_t	iAllocatedVariation			 = ((m_iAllocatedVariation*768+256*((iAllocatedSmoothedAverage>iAllocatedMax) ? (iAllocatedSmoothedAverage-iAllocatedMax) : (iAllocatedMax-iAllocatedSmoothedAverage))+1)>>10);

	// 4) Max Stack을 구한다.
	if(m_statisticsObject.iExistingLimits>=0)
	{
		m_statisticsObject.iExistingLimits = static_cast<size_t>(iAllocatedSmoothedAverage+(iAllocatedVariation<<2));
	}

	// 5) 값을 넣는다.
	m_iAllocatedSmoothedAverage		 = iAllocatedSmoothedAverage;
	m_iAllocatedVariation			 = iAllocatedVariation;
	m_iAllocatedTermMax				 = INT64_MIN;

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

template <size_t ISIZE>
typename CPoolBuffer<ISIZE>::MEMORY* CPoolBuffer<ISIZE>::CreateBuffer()
{
	return	new MEMORY;
}

template <size_t ISIZE>
typename CPoolBuffer<ISIZE>::MEMORY* CPoolBuffer<ISIZE>::ProcessCreateBuffer()
{
	// 1) 일단 새로 생성된다.
	MEMORY*	pMemory	 = CreateBuffer();	// (여기서 Exception발생 가능.)

	// Trace)
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Create object on Buffer pool(%s) ") _CGFUNCTION, GetName());

	// 통계) 현재 존재하는 객체의 수를 증가시킨다.
	++m_statisticsObject.iExisting;

	// 2) Factory에 Setting한다. (여기서 Factory에 Reference Counting를 1증가시키게 된다.)
	pMemory->m_pPool	 = this;

	// Declare) 
	CCGBuffer	tempBuffer(CGD::buffer(pMemory->buf, 0));

	// 3) Buffer를 새로 쓴다.
	if (m_fOnCreateNew != nullptr)
	{
		m_fOnCreateNew(tempBuffer);
	}

	// 4) Hook 함수 호출
	OnCreateNew(pMemory);

	// Check)
	CGASSERT_ERROR(tempBuffer.len==m_iBufferLen);

	// Return) 성공!!
	return	pMemory;
}

template <size_t ISIZE>
void CPoolBuffer<ISIZE>::ProcessDestroyBuffer(MEMORY* _pMemory)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_pMemory != nullptr,);

	// 1) Hook 함수 호출
	OnDestroy(_pMemory);

	// Statistics) 현재 존재하는 객체의 수를 감소시킨다.
	--m_statisticsObject.iExisting;

	// 2) DestroyObject함수를 호출하여 Object를 지운다.
	delete	_pMemory;
}

template <size_t ISIZE>
CCGBuffer CPoolBuffer<ISIZE>::Alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Declare) 
	MEMORY*	pMemory;

	// 1) 일단 head이 nullptr이면 새로 생성해서 보내준다.
	pMemory	 = m_stackMemory.pop();

	// 2) Stack된 것이 없다면 새로 만들어서 보낸다.
	if(pMemory != reinterpret_cast<MEMORY*>(nullptr))
	{
		// 통계) Stack된 것을 할당된 량 증가시킨다.
		++m_statisticsObject.qwAlloc_Stacked;

		// Trace)
		CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Object is allocated in Buffer pool(%s) [Remained:%I64d] ") _CGFUNCTION, GetName(), static_cast<int64_t>(m_stackMemory.size()));
	}
	else
	{
		// - 새로 Object을 만든다.
		pMemory	 = ProcessCreateBuffer();

		// 통계) 할당한 객체의 개수를 증가시킨다.
		++m_statisticsObject.qwAlloc_Create;
	}

	// Statistics) 사용 중인 객체의 수를 증가시킨다.
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
	
	// Return) 성공!!
	return	CCGBuffer(CGD::buffer(pMemory->buf, m_iBufferLen), pMemory);
}

template <size_t ISIZE>
void CPoolBuffer<ISIZE>::Free(MEMORY* _pMemory)
{
	// Check) _pMemory가 nullptr이어서는 안된다.
	CGASSERT(_pMemory!=nullptr,);

	// Statistics) 사용 중인 객체의 수를 줄인다.
	--m_statisticsObject.iInUsing;

	// Check) 최대 한계 Stack수보다 Stack된 Memory Block갯수가 많으면 할당해제한다.
	if(m_statisticsObject.iExisting>m_statisticsObject.iExistingLimits || _pMemory->IsDisuse())
	{
		// Statistics) 파괴된 Block을 하나 늘린다.
		++m_statisticsObject.qwFree_Delete;

		// - 객체를 바로 지운다.
		ProcessDestroyBuffer (_pMemory);

		// Return) 끝낸다.
		return;
	}

	// 1) List에 추가한다.
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

	// 1) 상태를 바꾼다.
	m_bEnableSustain	 = _bStatus;
}


}
