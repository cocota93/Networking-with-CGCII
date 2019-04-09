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
//-----------------------------------------------------------------------------
//
// FACTORY_ID
//
// 1. FACTORY_ID��?
//     Product ID�� Factory���� ������ ��ü�� �ο��Ǵ� ������ȣ��� �� ��
//    �ֽ��ϴ�.
//     ���� �ϳ��� Server�������� Product ID������ �ش� ��ü�� �����͸� ����
//    �� �ֽ��ϴ�.
//
//	  1) iProductSerial		
//       ����ȴٰ� �� �� 
//
//	  2) siFactorySerial	
//	     ����� Factory�� ID�Դϴ�. �̰����� ����� Factory�� �����͸� ���� �ֽ��ϴ�.
//
//	  3) wShipmentSerial	
//       Factory���� �ѹ� �Ҵ��� �� ������ ������ ��Ű�� ���Դϴ�. �� ����
//       ���������� ��ü�� ��Ȱ���� �� �ߺ��� �����ϱ� ���� ���̶� �� ��
//       �ֽ��ϴ�.
//
//-----------------------------------------------------------------------------
#define	TOTAL_STATISTICS_INFO			1440*7

enum class eFACTORY_TYPE : int32_t
{
	DEFAULT				 = 0,	// �⺻��
	POOL_MEMORYBLOCK	 = 1,	// �޸� �� Ǯ
	POOL_SYSTEM			 = 2,	// �ý��ۿ��� ���� ������ ���� ���� Ǯ
	POOL_USER			 = 3,	// ����ڰ� �ʿ信 ���� ������ Ǯ
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
		int					iFactoryID;			// Factory�� ID
		eFACTORY_TYPE		eFactoryType;		// Factory�� ����

		TICK::time_point	tickCapture;		// ����� �ð�(tick����..)

		ATOMIC<int64_t>		qwAlloc_Stacked;	// �Ҵ�� Stack�� ����� ��ü�� ��Ȱ���ؼ� �Ҵ��� �� Ƚ�� (������ ���� ���� ����.)
		ATOMIC<int64_t>		qwAlloc_Create;		// �Ҵ�� ���� ������ �Ҵ��� �� Ƚ��(���� ���� ����.)
		ATOMIC<int64_t>		qwFree_Stacked;		// �Ҵ����� �� Stack�� ����� Ƚ��. (������ ���� ���� ����.)
		ATOMIC<int64_t>		qwFree_Delete;		// �Ҵ����� �� ��� ������ Ƚ��.(���� ���� ����.)
		ATOMIC<int64_t>		qwFree_Disuse;		// ��⸦ ���� ������ ����
		ATOMIC<int64_t>		iExistingLimits;	// �Ҵ�Ǵ� �ִ� ��ü�� ���� ( ���� �� �� �̻��� ��ü�� ����Ǿ� ���� ��� Free�� �ٷ� delete�� �ϰ� �ȴ�.)
		ATOMIC<int64_t>		iExisting;			// ���� �����Ǿ� �ִ� �� ���� (�Ҵ�� ����+���õ� ����)
		ATOMIC<int64_t>		iInUsing;			// ���� �Ҵ� �� �� ��ü�� ����

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


