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
	// Check) �䱸�ϴ� ũ�Ⱑ 0�̰ų� MAX_SIZE_OF_MEMORY_BLOCK���� ũ�� �ȉ´�.(Debug������ ������ ���̴�.)
	CGASSERT(_Index>=0 && _Index<static_cast<int>(m_iMax), nullptr);

	// Check) �ش� Block�� Pool�� �������� �ʴ´ٸ� �߸��� ���̴�!
	CGASSERT(m_vectorMemoryBlockPool[_Index].exist(), nullptr);

	// Check) ���� ���� �������� �˻��Ѵ�.(Release������ ������ ���̴�.)
	ERROR_THROW_IF(_Index<0 || _Index>=static_cast<int>(m_iMax), CGException::CThrow_RangeError(_CGTEXT("out of memory block pool's block index range. ") _CGFUNCTION), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Excp) CGFactory: Out of Range ") _CGFUNCTION));

	// Return) �Ҵ���� �޸𸮸� �����Ѵ�.
	return	m_vectorMemoryBlockPool[_Index]->Alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}

inline void CGFactory::CPoolMemoryBlock::Free(_In_ int _Index, _In_ TBLOCK* _pBlock)
{
	// Check) �䱸�ϴ� ũ�Ⱑ 0�̰ų� MAX_SIZE_OF_MEMORY_BLOCK���� ũ�� �ȉ´�.(Debug������ ������ ���̴�.)
	CGASSERT(_Index>=0 && _Index<static_cast<int>(m_iMax), );

	// Check) �ش� Block�� Pool�� �������� �ʴ´ٸ� �߸��� ���̴�!
	CGASSERT(m_vectorMemoryBlockPool[_Index].exist(), );

	// Check) ���� ���� �������� �˻��Ѵ�.(Release������ ������ ���̴�.)
	ERROR_THROW_IF(_Index<0 || _Index>=static_cast<int>(m_iMax), CGException::CThrow_RangeError(_CGTEXT("out of memory block pool's block index range. ") _CGFUNCTION), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Excp) CGFactory: Out of Range ") _CGFUNCTION));

	// Return) �Ҵ���� �޸𸮸� �����Ѵ�.
	return	m_vectorMemoryBlockPool[_Index]->Free(_pBlock);
}
