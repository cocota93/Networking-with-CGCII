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
// Defintion) Memory Object for Memory Block Pool
class CGFactory::CPoolMemoryBlock::CMemory : public ICGPoolable<CMemory>, public ICGBuffer, public CGPool::_traits_has_pool
{
public:
			CMemory(size_t _Size);
			CMemory() : ICGBuffer(nullptr, 0) {}
	virtual	~CMemory();
private:
	virtual	void	ProcessDispose() override	{	m_pPool->Free(this);}
public:
	#ifdef USE_TLS_MEMORY_BLOCK_POOL
			CGPTR<TPOOL>		m_pPool;
	#else
			CGPTR<TPOOL>		m_pPool;
	#endif
};

inline CGFactory::CPoolMemoryBlock::TBLOCK* CGFactory::CPoolMemoryBlock::Alloc(_In_ int _Index CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Check) 요구하는 크기가 0이거나 MAX_SIZE_OF_MEMORY_BLOCK보다 크면 안됀다.(Debug에서만 동작할 것이다.)
	CGASSERT(_Index>=0 && _Index<static_cast<int>(m_iMax), nullptr);

	// Check) 해당 Block에 Pool이 존재하지 않는다면 잘못된 것이다!
	CGASSERT(m_vectorMemoryBlockPool[_Index].exist(), nullptr);

	// Check) 위와 같은 조건으로 검사한다.(Release에서도 동작할 것이다.)
	ERROR_THROW_IF(_Index<0 || _Index>=static_cast<int>(m_iMax), CGException::CThrow_RangeError(_CGTEXT("out of memory block pool's block index range. ") _CGFUNCTION), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Excp) CGFactory: Out of Range ") _CGFUNCTION));

	// Return) 할당받은 메모리를 리턴한다.
	return	m_vectorMemoryBlockPool[_Index]->Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}

inline void CGFactory::CPoolMemoryBlock::Free(_In_ int _Index, _In_ TBLOCK* _pBlock)
{
	// Check) 요구하는 크기가 0이거나 MAX_SIZE_OF_MEMORY_BLOCK보다 크면 안됀다.(Debug에서만 동작할 것이다.)
	CGASSERT(_Index>=0 && _Index<static_cast<int>(m_iMax), );

	// Check) 해당 Block에 Pool이 존재하지 않는다면 잘못된 것이다!
	CGASSERT(m_vectorMemoryBlockPool[_Index].exist(), );

	// Check) 위와 같은 조건으로 검사한다.(Release에서도 동작할 것이다.)
	ERROR_THROW_IF(_Index<0 || _Index>=static_cast<int>(m_iMax), CGException::CThrow_RangeError(_CGTEXT("out of memory block pool's block index range. ") _CGFUNCTION), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Excp) CGFactory: Out of Range ") _CGFUNCTION));

	// Return) 할당받은 메모리를 리턴한다.
	return	m_vectorMemoryBlockPool[_Index]->Free(_pBlock);
}
