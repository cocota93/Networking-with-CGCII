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

 @class		CPoolMemoryBlock
 @brief		���� ũ���� �޸� ��ü��  �Ҵ����ִ� Ǯ�̴�.
 @todo		
 @ref		CGFactory::CPoolObject<TOBJECT>, CGFactory::CPoolMemory
 @details	\n
 ���� ũ���� �޸� ��ü�� �Ҵ��� �ִ� Ǯ�̴�.
 
 ������ ũ�⸦ �Ҵ� �䱸�ϰ� �Ǹ� �ּ��� �䱸�� ũ�⺸�� ũ�ų� �ּ��� ���� �޸� ��ü�� �Ҵ����ش�.
 �޸� ��� Ǯ�� �پ��� ũ�� ��üǮ(CGFactory::CPoolObject<T>)�� ���� Ǯ�� �����Ǿ� �ִ�.
 1K, 2K, 3K, 4K, ..., 64K  �� ���� ũ���� �޸� ��ü�� �Ҵ����ִ� Ǯ�� ���� ������ ũ���� �޸� ��ü�� �Ҵ� �䱸�� ���
 �䱸�� ũ�⸦ �����ϴ� Ǯ���� �޸� ��ü�� �Ҵ��ؼ� �����ش�.
 �� 3.5k�� �޸𸮸� �䱸�� ��� 4k �޸�Ǯ���� �Ҵ��� �شٴ� ���̴�.
 ���� �ʿ� �̻��� �޸𸮰� �Ҵ�� �� �ִ�.(4~7% ����)

 �޸� ��� ũ��� ����
 �޸𸮺��Ǯ�� �Ҵ��ϴ� �޸��� �Ѱ谡 �ִ�. �޸𸮸� � ������ ��� Ǯ�� �����ϴ� ���� ���� �Ҵ��� �� �ִ� �ִ� �޸� ũ�Ⱑ �����ȴ�.
 ���� ��Ȳ�� ���� �޸� ����� ũ�⳪ ���� ���� ���� �ٸ��� �Ʒ��� ���� ������ �� �ִ�.
 (�ڼ��� ���� 'CGDefinitionsPoolMemoryBlock.h'������ �����ٶ�.)

 // - ������ ������ �޸� Ǯ
 * MEMORYPOOLTYPE_UNIFORM_TINY		- 256Byte x64, Max 16KByte
 * MEMORYPOOLTYPE_UNIFORM_NORMAL	- 1KByte x64, Max 64KByte
 * MEMORYPOOLTYPE_UNIFORM_LARGE		- 4KByte x64, Max 256KByte
 * MEMORYPOOLTYPE_UNIFORM_HUGE		- 16KByte x64, Max 1MByte
 
 // - ���� ũ�� �޸� Ǯ
 * MEMORYPOOLTYPE_SCALED_TINY		- 128Bytex8, 1KByte x7, Max 8KByte
 * MEMORYPOOLTYPE_SCALED_NORMAL		- TINY   +  4KByte x14, Max 64KByte
 * MEMORYPOOLTYPE_SCALED_LARGE		- NORMAL + 16KByte x12, Max 256KByte
 * MEMORYPOOLTYPE_SCALED_HUGE		- LARGE  + 16KByte x12, Max 1MByte
 
 ���� �Ҵ��� �� �ִ� �ִ� ũ�⺸�� �� ū �޸𸮸� �䱸�Ѵٸ� Ǯ�� ������� �ʰ� �׳� �ٷ� �����Ҵ��ؼ� �ش�.

 Ǯ���� �޸𸮸� �Ҵ��ϱ� ���ؼ��� Alloc('�Ҵ��û ũ��')�� ȣ���ϸ� �ǰ� �Ҵ������Ϸ��� Free('�޸� ��ü ������')�� ȣ���� �ָ� �ȴ�.

// 1. Memory Block Pool�� atomic�� �̿��� Lock-Free�� ������.
//     Memory Block Pool�� Lock Free�� �����ϱ� ���� lockfreePush/Pop�� �̿� 
//    �Ͽ� �����Ͽ���.
//     ���� ���ο� Memory Block�� �Ҵ��ϰ� �����ϴ��� CriticalSection��
//    ���� Lock�� ������� �ʾ� ���� Allock�� Free�� �����ص� �پ �ӵ���
//    �����Ѵ�.
//
// 2. �ſ� ���� ������ Alloc()�� Free()�Լ�
//    - Alloc()�� Free()�Լ��� �ſ� ���� ������ �ڵ�� �ۼ��� �Ǿ� �ִ�.
//    - Alloc()�� Free()�� new�� delete�� �Ҹ�Ǵ� ����� �ּ�ȭ �ϰ� �ϱ� ����
//      ���� ��ŭ ����� �ּ����� code���� ����Ǵ� ���� �����ؼ� ���۵Ǿ���.
//    - Alloc�� Free��� Loop���� �������� ������ Alloc�� ���� 3~4���� if����
//      �� ������ ���ุ���� ����Ǹ� Free�Լ��� ���� ��� ���θ�����
//      ����ȴ�. 
// 
// 3. �پ��� ������ Memory Block ũ��
// 
// 4. Memory Block Pool�� ���ۼ���!!
//     Memory Block Pool�� Alloc()�Լ��� ����Ͽ� �ʿ��� ũ�⸦ �����ϸ� �ش�
//    ũ�⺸�� ū Memory Block�� �Ҵ����ش�. ���� ��� 1024Byte������ Block��
//    �����Ǿ� �ִٸ� 1500Byte�� �Ҵ�䱸�� ��� 2048Byte¥�� Memory Block��
//    �Ҵ��� �شٴ� ���̴�.
//
// 5. Memory Block Pool�� ���ۼ���!!
//    1) Alloc() - Memory Block�� �Ҵ����ִ� �Լ��̴�.
//       - �䱸�ϴ� ũ�⺸�� �ణ ū Block Size�� ����� �Ѵ�!
//       - �ش��ϴ� ũ���� Memory Block�� ����Ǿ� �ִ��� Ȯ���Ѵ�.
//          Case A) �� ����� Size�� Block�� Stack�� ������ ��!
//                  -> �װ� �׳� �Ҵ��� �ش�.
//          Case B) �������� ���� ���!
//                  -> ���, ���� ���� �Ҵ��� �ش�.
//          * TLS Cache�� ����� ��� TLS Cache�� ���� ����Ѵ�.
//
//    2) Free() - Memory Block�� ��ȯ�ϴ� �Լ��̴�.
//       - ������ Memory Block�� Size�� �´� ����Ҹ� Ȯ���Ѵ�.
//          Case A) �ִ� ���ġ�� m_nExistingLimits���� ������ Memory Block�� ���ٸ�
//                  -> �׳� Free()�Ѵ�.
//          Case B) �׷��� �ʴٸ� 
//                  -> ����ҿ� �״´�.
// 
//    3) Prepare() - �̸� Memory Block�� �Ҵ��� ���´�.
//       - �̸� �ش� Block�� �Ҵ缭 Pool�� ���� �־� ���� �Լ��̴�.
//       - �Ϲ������� Pool�� ó�� ����� �� Pool���� ����� Memory Block��
//         �������� �ʴ´�. ���� �̸� ���� Memory Block�� ������ �뷫 �
//         ���������� ���� ������ �����Ѵٸ� Server�� �������� �̸� �Ҵ���
//         ���� ���� Server�� �����ϵ��� �ϱ����� ���ȴ�.
//    
//    4) Shrink() - ����� Memory Block�� �Ҵ�������.
//       - �ʹ� ���� Block�� ����Ǿ� �ִ� ��� ���� �޸� ���� �ҷ�������
//         Stack�� Block�� �������� �� ���ȴ�.
//       - �Ϲ������� �����ʱ����� ���������� ������ ������ ��� Block��
//         ���䰡 �����ߴٰ� �ٽ� �Ҵ������� ��� �ʹ� ���� Block�� �׿�����
//         ���� �ִ�. �̷� �� �׿��ִ� Block�� ������ �ִµ� ���ȴ�.
//         �Ϲ������� �̷� ���� ���ġ�� ���ؼ� ����ϰ� �ȴ�.
//       - �ڵ����� ��꿡 ���� ������ ���差���������Ͽ� �����ϹǷ� Ư���� 
//         ȣ���� ���� �ʾƵ� �ȴ�.
//
//
*/
//-----------------------------------------------------------------------------
class CPoolMemoryBlock
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			CPoolMemoryBlock();
	virtual ~CPoolMemoryBlock();


// ****************************************************************************
// Definition)
// ----------------------------------------------------------------------------
public:
	// 1) 
	class						CMemory;
	typedef	CMemory				TBLOCK;
	template <class TTYPE>		class MEMORYBLOCK_POOL;

	// 2) Container
	#ifdef USE_TLS_MEMORY_BLOCK_POOL
			typedef CPoolObjectTLS<TBLOCK>	TPOOL;
	#else
			typedef CPoolObject<TBLOCK>		TPOOL;
	#endif


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief _iAmount��ŭ�� ��ü�� �̸� �غ��� ���´�. @param _iAmount �غ��� ���� @return ���� �غ�� ��
			size_t				Prepare(_In_ int _Index, _In_ size_t _iAmount);
	//! @brief _iAmount��ŭ�� ��� ��ü�� �����Ѵ�. @param _iAmount ������ ���� @return ���� ������ ��
			size_t				Shrink(_In_ int _Index, _In_ size_t _iAmount);

	//! @brief Ǯ���� ��ü�� �Ҵ��� ��û�Ѵ�. @return �Ҵ�� ��ü
			TBLOCK*				Alloc(_In_ int _Index CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief Ǯ�� ��ü�� ��ȯ�Ѵ�. @param _Index Ǯ �ε��� @param ��ȯ�� ��ü
			void				Free(_In_ int _Index, _In_ TBLOCK* _pBlock);

	//! @brief ��ü �� �޸� ũ�⸦ ��´�. @param _Index Ǯ �ε��� @return ��ü �� �޸� ũ��
			size_t				GetObjectSize(_In_ int _Index) const;
	//! @brief ����� ��´�. @param _Index Ǯ �ε��� @return ���
			size_t				GetStackedCount(_In_ int _Index) const;
	//! @brief �ִ� ����� ��´�. @param _Index Ǯ �ε��� @return �ִ� ���
			int64_t				GetExistingLimits(_In_ int _Index) const;

	//! @brief [�������] ��Ȱ���� �Ҵ�� ��������� ��´�. @param _Index Ǯ �ε��� @return ��谪
			int64_t				Statistics_GetAllocatedStack(_In_ int _Index) const;
	//! @brief [�������] ������ �Ҵ�� ��������� ��´�. @param _Index Ǯ �ε��� @return ��谪
			int64_t				Statistics_GetAllocatedCreate(_In_ int _Index) const;
	//! @brief [�������] �� �Ҵ�� ��������� ��´�. @param _Index Ǯ �ε��� @return ��谪
			int64_t				Statistics_GetAllocated(_In_ int _Index) const;
	//! @brief [�������] ��ȯ�Ǿ� ���õ� ���� ��´�. @param _Index Ǯ �ε��� @return ��谪
			int64_t				Statistics_GetFreedStack(_In_ int _Index) const;
	//! @brief [�������] ��ȯ�Ǿ� �Ҵ������� ���� ��´�. @param _Index Ǯ �ε��� @return ��谪
			int64_t				Statistics_GetFreedDelete(_In_ int _Index) const;
	//! @brief [�������] ��ȯ�� �� ���� ��´�. @param _Index Ǯ �ε��� @return ��谪
			int64_t				Statistics_GetFreed(_In_ int _Index) const;
	//! @brief [�������] ���� ������ �� ��ü ���� ��´�. @param _Index Ǯ �ε��� @return ��谪
			int64_t				Statistics_GetExisting(_In_ int _Index) const;
	//! @brief [�������] ���� �Ҵ�Ǿ� �ִ� ��ü ���� ��´�. @param _Index Ǯ �ε��� @return ��谪
			int64_t				Statistics_GetInUsing(_In_ int _Index) const;

	//! @brief �̱��� �޸� ��� Ǯ ��ü�� ��´�. @return �޸� ��� Ǯ ��ü
	static	CPoolMemoryBlock&	GetInstance()							{	return m_InstancePool;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	//! @brief �ʱ�ȭ�Ѵ�. @param _Type Ǯ�� ���� @param _Type Ǯ�� �ִ� ���� @param _Size Ǯ�� ũ��   @return true ���� @return false ���� 
	static	bool				Initialize(_In_ int _Type=MEMORYPOOL_MEMORYPOOL_TYPE, _In_ size_t _Max=MEMORYPOOL_NUMBER_OF_BLOCK, _In_ size_t _Size=MEMORYPOOL_SIZE_OF_BLOCK);

	//! @brief Ǯ ��ü�� �ı��Ѵ�. @return true ���� @return false ���� 
	virtual	bool				Destroy();

	//! @brief ������ ũ��� Ǯ�� �����Ѵ�.
			void				CreateAsUniform(_In_ size_t _Max, _In_ size_t _Size);
	//! @brief ���� ������� Ǯ�� �����Ѵ�.
			void				CreateAsScaledTiny();
	//! @brief �Ϲ� ������� Ǯ�� �����Ѵ�.
			void				CreateAsScaledNormal();
	//! @brief ū ������� Ǯ�� �����Ѵ�.
			void				CreateAsScaledLarge();
	//! @brief �ſ� ū ������� Ǯ�� �����Ѵ�.
			void				CreateAsScaledHuge();

private:
			CGOWN<TPOOL>		m_vectorMemoryBlockPool[128];
			size_t				m_iMax;

	// Static)
	static	CPoolMemoryBlock	m_InstancePool;
};


}

#include "CGObjectClasses/CGFactoryPoolMemoryBlock.inl"