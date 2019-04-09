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
// OBJECT_ID
//
// 1. OBJECT_ID란?
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
namespace CGMESSAGE
{
	namespace FACTORY
	{
		const uint32_t	BASE						 = CGMESSAGE::SYSTEM::FACTORY |  1;

		const uint32_t	ENABLE_SUSTAIN				 = BASE |  1;
		const uint32_t	DISABLE_SUSTAIN				 = BASE |  2;
		const uint32_t	IS_ALL_RELEASED				 = BASE |  3;
		const uint32_t	IS_SUSTAIN_ENABLE			 = BASE |  4;

		const uint32_t	FACTORY_PREPARE				 = BASE |  5;
		const uint32_t	FACTORY_SHRINK				 = BASE |  6;
		const uint32_t	FACTORY_SUSTAIN				 = BASE |  7;
		const uint32_t	FACTORY_IS_ENABLE_SUSTAIN	 = BASE |  8;
		const uint32_t	FACTORY_ENABLE_SUSTAIN		 = BASE |  9;

		const uint32_t	REGISTER_FACTORY			 = BASE | 10;
		const uint32_t	UNREGISTER_FACTORY			 = BASE | 11;
		const uint32_t	UPDATE_FACTORYMANAGER		 = BASE | 12;
		const uint32_t	UPDATE_FACTORY				 = BASE | 13;

		namespace ATTRIBUTE
		{
			const uint32_t	BASE					 = CGMESSAGE::ATTRIBUTE::BASE | CODE_TYPE::TAIL_SUB_1;

			const uint32_t	ALL_FACTORY_NAME		 = BASE |  1;
			const uint32_t	ALL_FACTORY_INFO		 = BASE |  2;
			const uint32_t	FACTORY_INFO			 = BASE |  3;
			const uint32_t	ADD_FACTORY_INFO		 = BASE |  4;
			const uint32_t	REMOVE_FACTORY_INFO		 = BASE |  5;
		}
	}
}

#define	CGATTRIBUTE_TYPE_NAME						101
#define	CGATTRIBUTE_TYPE_ID							102
#define	CGATTRIBUTE_OBJECT_NAME						103
#define	CGATTRIBUTE_OBJECT_ID						104

#define	CGATTRIBUTE_FACTORY_COUNT					502
#define	CGATTRIBUTE_FACTORY_OBJECT_SIZE				503
#define	CGATTRIBUTE_FACTORY_STACKED_COUNT			504
#define	CGATTRIBUTE_FACTORY_EXISTING_LIMITS			505
#define	CGATTRIBUTE_FACTORY_STATISTICS				506
#define	CGATTRIBUTE_FACTORY_STATISTICS_CREATED		507
#define	CGATTRIBUTE_FACTORY_STATISTICS_DELETED		508
#define	CGATTRIBUTE_FACTORY_STATISTICS_ALLOCATED	509
#define	CGATTRIBUTE_FACTORY_STATISTICS_FREED		510
#define	CGATTRIBUTE_FACTORY_STATISTICS_EXISTING		511
#define	CGATTRIBUTE_FACTORY_STATISTICS_INUSING		512
