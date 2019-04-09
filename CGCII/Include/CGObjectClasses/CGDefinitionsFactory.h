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
//-----------------------------------------------------------------------------
//
// FACTORY_ID
//
// 1. FACTORY_ID란?
//     Product ID는 Factory에서 생산한 객체에 부여되는 공유번호라고 할 수
//    있습니다.
//     따라서 하나의 Server내에서는 Product ID만으로 해당 객체의 포인터를 얻을
//    수 있습니다.
//
//	  1) iProductSerial		
//       생산된다고 할 때 
//
//	  2) siFactorySerial	
//	     생산된 Factory의 ID입니다. 이것으로 생산된 Factory의 포인터를 얻을 있습니다.
//
//	  3) wShipmentSerial	
//       Factory에서 한번 할당을 할 때마다 증가를 시키는 값입니다. 이 값은
//       실질적으로 객체를 재활용할 때 중복을 방지하기 위한 것이라 할 수
//       있습니다.
//
//-----------------------------------------------------------------------------
#define	TOTAL_STATISTICS_INFO			1440*7

enum class eFACTORY_TYPE : int32_t
{
	DEFAULT				 = 0,	// 기본값
	POOL_MEMORYBLOCK	 = 1,	// 메모리 블럭 풀
	POOL_SYSTEM			 = 2,	// 시스템에서 내부 동작을 위해 사용된 풀
	POOL_USER			 = 3,	// 사용자가 필요에 따라 생성한 풀
	ALLOCATOR_SYSTEM	 = 4,	// Allocator in System
	ALLOCATOR_USER		 = 5,	// Allocator by User
	MAX
};

enum class eFACTORY_SUSTAIN_TYPE : int32_t
{
	NORMAL		 = 0,
	HEAVY		 = 1,
	EXCESS_ALL	 = 2,
	STACKED_ALL	 = 3
};

namespace CGStatistics
{
	struct FACTORY
	{
		int					iFactoryID;			// Factory의 ID
		eFACTORY_TYPE		eFactoryType;		// Factory의 형태

		TICK::time_point	tickCapture;		// 저장된 시간(tick으로..)

		ATOMIC<int64_t>		qwAlloc_Stacked;	// 할당시 Stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		ATOMIC<int64_t>		qwAlloc_Create;		// 할당시 새로 생성해 할당해 준 횟수(적을 수록 좋다.)
		ATOMIC<int64_t>		qwFree_Stacked;		// 할당해제 시 Stack에 저장된 횟수. (비율이 높을 수록 좋다.)
		ATOMIC<int64_t>		qwFree_Delete;		// 할당해제 시 즉시 지워진 횟수.(적을 수록 좋다.)
		ATOMIC<int64_t>		qwFree_Disuse;		// 폐기를 통해 지워진 갯수
		ATOMIC<int64_t>		iExistingLimits;	// 할당되는 최대 객체의 제한 ( 이제 한 값 이상의 객체가 생산되어 있을 경우 Free시 바로 delete를 하게 된다.)
		ATOMIC<int64_t>		iExisting;			// 현재 생성되어 있는 총 갯수 (할당된 갯수+스택된 갯수)
		ATOMIC<int64_t>		iInUsing;			// 현재 할당 된 총 객체의 갯수

		void	Set(const FACTORY& rhs)
		{
			iFactoryID		 = rhs.iFactoryID;
			eFactoryType	 = rhs.eFactoryType;
			tickCapture		 = rhs.tickCapture;
			qwAlloc_Stacked.store(rhs.qwAlloc_Stacked);
			qwAlloc_Create.store(rhs.qwAlloc_Create);
			qwFree_Stacked.store(rhs.qwFree_Stacked);
			qwFree_Delete.store(rhs.qwFree_Delete);
			qwFree_Disuse.store(rhs.qwFree_Disuse);
			iExistingLimits.store(rhs.iExistingLimits);
			iExisting.store(rhs.iExisting);
			iInUsing.store(rhs.iInUsing);
		}

		FACTORY() {}
		FACTORY(const FACTORY& rhs) { Set(rhs); }
		FACTORY&	operator=(const FACTORY& rhs) { Set(rhs); return *this; }
	};
}


