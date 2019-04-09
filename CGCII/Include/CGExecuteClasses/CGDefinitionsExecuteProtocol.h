//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// Messsage Definitions
//
//-----------------------------------------------------------------------------
namespace CGMESSAGE
{
	// 1) ...
	const uint32_t	DUMP						 = CGMESSAGE::SYSTEM::EXECUTE;
	const uint32_t	REGISTER_THREAD				 = CGMESSAGE::SYSTEM::EXECUTE+1;
	const uint32_t	UNREGISTER_THREAD			 = CGMESSAGE::SYSTEM::EXECUTE+2;

	// 2) 
	const uint32_t	INIT_EXECUTOR_COMPLETIONPORT_THREAD	 = (CODE_TYPE::INIT | CODE_TYPE::TAIL_0 | 1);
}



#define	CGATTRIBUTE_THREAD_STATISTICS		701
