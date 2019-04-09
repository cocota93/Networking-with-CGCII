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

 @class		CPoolMemoryBlock
 @brief		임의 크기의 메모리 객체를  할당해주는 풀이다.
 @todo		
 @ref		CGFactory::CPoolObject<TOBJECT>, CGFactory::CPoolMemory
 @details	\n
 임의 크기의 메모리 객체를 할당해 주는 풀이다.
 
 임의의 크기를 할당 요구하게 되면 최소한 요구한 크기보다 크거나 최소한 같은 메모리 객체를 할당해준다.
 메모리 블록 풀은 다양한 크기 객체풀(CGFactory::CPoolObject<T>)를 묶은 풀로 구성되어 있다.
 1K, 2K, 3K, 4K, ..., 64K  등 여러 크기의 메모리 객체를 할당해주는 풀을 묶어 임의의 크기의 메모리 객체를 할당 요구할 경우
 요구한 크기를 만족하는 풀에서 메모리 객체를 할당해서 돌려준다.
 즉 3.5k의 메모리를 요구할 경우 4k 메모리풀에서 할당해 준다는 것이다.
 따라서 필요 이상의 메모리가 할당될 수 있다.(4~7% 정도)

 메모리 블록 크기와 설정
 메모리블록풀은 할당하는 메모리의 한계가 있다. 메모리를 어떤 단위로 몇개의 풀로 구성하는 가에 따라 할당할 수 있는 최대 메모리 크기가 결정된다.
 따라서 상황에 따라 메모리 블록의 크기나 갯수 분포 등을 다르게 아래와 같이 설정할 수 있다.
 (자세한 것은 'CGDefinitionsPoolMemoryBlock.h'파일을 참조바람.)

 // - 단일한 간격의 메모리 풀
 * MEMORYPOOLTYPE_UNIFORM_TINY		- 256Byte x64, Max 16KByte
 * MEMORYPOOLTYPE_UNIFORM_NORMAL	- 1KByte x64, Max 64KByte
 * MEMORYPOOLTYPE_UNIFORM_LARGE		- 4KByte x64, Max 256KByte
 * MEMORYPOOLTYPE_UNIFORM_HUGE		- 16KByte x64, Max 1MByte
 
 // - 가변 크기 메모리 풀
 * MEMORYPOOLTYPE_SCALED_TINY		- 128Bytex8, 1KByte x7, Max 8KByte
 * MEMORYPOOLTYPE_SCALED_NORMAL		- TINY   +  4KByte x14, Max 64KByte
 * MEMORYPOOLTYPE_SCALED_LARGE		- NORMAL + 16KByte x12, Max 256KByte
 * MEMORYPOOLTYPE_SCALED_HUGE		- LARGE  + 16KByte x12, Max 1MByte
 
 만약 할당할 수 있는 최대 크기보다 더 큰 메모리를 요구한다면 풀을 사용하지 않고 그냥 바로 동적할당해서 준다.

 풀에서 메모리를 할당하기 위해서는 Alloc('할당요청 크기')를 호출하면 되고 할당해제하려면 Free('메모리 객체 포인터')를 호출해 주면 된다.

// 1. Memory Block Pool은 atomic을 이용한 Lock-Free로 동작함.
//     Memory Block Pool은 Lock Free로 구현하기 위해 lockfreePush/Pop을 이용 
//    하여 구현하였다.
//     따라서 새로운 Memory Block을 할당하고 해지하더라도 CriticalSection과
//    같은 Lock은 수행되지 않아 잦은 Allock와 Free를 수행해도 뛰어난 속도를
//    보장한다.
//
// 2. 매우 작은 부하의 Alloc()와 Free()함수
//    - Alloc()와 Free()함수는 매우 적은 부하의 코드로 작성이 되어 있다.
//    - Alloc()와 Free()가 new나 delete에 소모되는 비용을 최소화 하게 하기 위한
//      것인 만큼 수행상에 최소한의 code만이 수행되는 것을 염두해서 제작되었다.
//    - Alloc와 Free모두 Loop문은 존재하지 않으며 Alloc는 단지 3~4번의 if문과
//      몇 라인의 실행만으로 수행되며 Free함수는 단지 몇개의 라인만으로
//      수행된다. 
// 
// 3. 다양한 형태의 Memory Block 크기
// 
// 4. Memory Block Pool의 동작설명!!
//     Memory Block Pool에 Alloc()함수를 사용하여 필요한 크기를 설정하면 해당
//    크기보다 큰 Memory Block을 할당해준다. 예를 들어 1024Byte단위로 Block이
//    설정되어 있다면 1500Byte를 할당요구할 경우 2048Byte짜리 Memory Block을
//    할당해 준다는 것이다.
//
// 5. Memory Block Pool의 동작설명!!
//    1) Alloc() - Memory Block을 할당해주는 함수이다.
//       - 요구하는 크기보다 약간 큰 Block Size를 계산을 한다!
//       - 해당하는 크기의 Memory Block이 저장되어 있는지 확인한다.
//          Case A) 그 계산한 Size의 Block가 Stack에 존재할 때!
//                  -> 그걸 그냥 할당해 준다.
//          Case B) 존재하지 않을 경우!
//                  -> 즉시, 새로 만들어서 할당해 준다.
//          * TLS Cache를 사용할 경우 TLS Cache를 먼저 사용한다.
//
//    2) Free() - Memory Block을 반환하는 함수이다.
//       - 돌려진 Memory Block의 Size에 맞는 저장소를 확인한다.
//          Case A) 최대 허용치인 m_nExistingLimits보다 생성된 Memory Block이 많다면
//                  -> 그냥 Free()한다.
//          Case B) 그렇지 않다면 
//                  -> 저장소에 쌓는다.
// 
//    3) Prepare() - 미리 Memory Block을 할당해 놓는다.
//       - 미리 해당 Block을 할당서 Pool에 집어 넣어 놓는 함수이다.
//       - 일반적으로 Pool이 처음 실행될 때 Pool에는 저장된 Memory Block이
//         존재하지 않는다. 만약 미리 사용될 Memory Block의 갯수가 대략 몇개
//         정도인지에 대한 정보가 존재한다면 Server의 수행전에 미리 할당해
//         놓은 다음 Server를 수행하도록 하기위해 사용된다.
//    
//    4) Shrink() - 저장된 Memory Block을 할당해제함.
//       - 너무 많은 Block이 저장되어 있는 경우 많은 메모리 낭비를 불러옴으로
//         Stack된 Block을 지워버릴 때 사용된다.
//       - 일반적으로 접속초기라든지 순간적으로 접속이 폭주할 경우 Block의
//         수요가 급증했다가 다시 할당해제될 경우 너무 많은 Block이 쌓여있을
//         수가 있다. 이럴 때 쌓여있는 Block을 제거해 주는데 사용된다.
//         일반적으로 이런 것은 통계치에 의해서 사용하게 된다.
//       - 자동적인 계산에 의해 최적의 저장량만을생성하여 관리하므로 특별히 
//         호출해 주지 않아도 된다.
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
	//! @brief _iAmount만큼의 객체를 미리 준비해 놓는다. @param _iAmount 준비할 수량 @return 실제 준비된 량
			size_t				Prepare(_In_ int _Index, _In_ size_t _iAmount);
	//! @brief _iAmount만큼의 재고 객체를 해제한다. @param _iAmount 해제할 수량 @return 실제 해제된 량
			size_t				Shrink(_In_ int _Index, _In_ size_t _iAmount);

	//! @brief 풀에서 객체를 할당을 요청한다. @return 할당된 객체
			TBLOCK*				Alloc(_In_ int _Index CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief 풀에 객체를 반환한다. @param _Index 풀 인덱스 @param 반환할 객체
			void				Free(_In_ int _Index, _In_ TBLOCK* _pBlock);

	//! @brief 객체 당 메모리 크기를 얻는다. @param _Index 풀 인덱스 @return 객체 당 메모리 크기
			size_t				GetObjectSize(_In_ int _Index) const;
	//! @brief 재고량을 얻는다. @param _Index 풀 인덱스 @return 재고량
			size_t				GetStackedCount(_In_ int _Index) const;
	//! @brief 최대 재고량을 얻는다. @param _Index 풀 인덱스 @return 최대 재고량
			int64_t				GetExistingLimits(_In_ int _Index) const;

	//! @brief [통계정보] 재활용해 할당된 통계정보를 얻는다. @param _Index 풀 인덱스 @return 통계값
			int64_t				Statistics_GetAllocatedStack(_In_ int _Index) const;
	//! @brief [통계정보] 생성해 할당된 통계정보를 얻는다. @param _Index 풀 인덱스 @return 통계값
			int64_t				Statistics_GetAllocatedCreate(_In_ int _Index) const;
	//! @brief [통계정보] 총 할당된 통계정보를 얻는다. @param _Index 풀 인덱스 @return 통계값
			int64_t				Statistics_GetAllocated(_In_ int _Index) const;
	//! @brief [통계정보] 반환되어 스택된 수를 얻는다. @param _Index 풀 인덱스 @return 통계값
			int64_t				Statistics_GetFreedStack(_In_ int _Index) const;
	//! @brief [통계정보] 반환되어 할당해제된 수를 얻는다. @param _Index 풀 인덱스 @return 통계값
			int64_t				Statistics_GetFreedDelete(_In_ int _Index) const;
	//! @brief [통계정보] 반환된 총 수를 얻는다. @param _Index 풀 인덱스 @return 통계값
			int64_t				Statistics_GetFreed(_In_ int _Index) const;
	//! @brief [통계정보] 현재 생성된 총 객체 수를 얻는다. @param _Index 풀 인덱스 @return 통계값
			int64_t				Statistics_GetExisting(_In_ int _Index) const;
	//! @brief [통계정보] 현재 할당되어 있는 객체 수를 얻는다. @param _Index 풀 인덱스 @return 통계값
			int64_t				Statistics_GetInUsing(_In_ int _Index) const;

	//! @brief 싱글턴 메모리 블록 풀 객체를 얻는다. @return 메모리 블록 풀 객체
	static	CPoolMemoryBlock&	GetInstance()							{	return m_InstancePool;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	//! @brief 초기화한다. @param _Type 풀의 형태 @param _Type 풀의 최대 갯수 @param _Size 풀의 크기   @return true 성공 @return false 실패 
	static	bool				Initialize(_In_ int _Type=MEMORYPOOL_MEMORYPOOL_TYPE, _In_ size_t _Max=MEMORYPOOL_NUMBER_OF_BLOCK, _In_ size_t _Size=MEMORYPOOL_SIZE_OF_BLOCK);

	//! @brief 풀 객체를 파괴한다. @return true 성공 @return false 실패 
	virtual	bool				Destroy();

	//! @brief 동일한 크기로 풀을 구성한다.
			void				CreateAsUniform(_In_ size_t _Max, _In_ size_t _Size);
	//! @brief 작은 사이즈로 풀을 구성한다.
			void				CreateAsScaledTiny();
	//! @brief 일반 사이즈로 풀을 구성한다.
			void				CreateAsScaledNormal();
	//! @brief 큰 사이즈로 풀을 구성한다.
			void				CreateAsScaledLarge();
	//! @brief 매우 큰 사이즈로 풀로 구성한다.
			void				CreateAsScaledHuge();

private:
			CGOWN<TPOOL>		m_vectorMemoryBlockPool[128];
			size_t				m_iMax;

	// Static)
	static	CPoolMemoryBlock	m_InstancePool;
};


}

#include "CGObjectClasses/CGFactoryPoolMemoryBlock.inl"