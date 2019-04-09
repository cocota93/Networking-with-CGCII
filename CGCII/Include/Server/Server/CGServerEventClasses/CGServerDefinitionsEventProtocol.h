//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Event Classes                            *
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
//----------------------------------------------------------------------------
//
//
//  Definitions for Event Classes
//
//
//----------------------------------------------------------------------------
namespace CGMESSAGE
{
	namespace SERVER
	{
		namespace EVENT
		{
			const uint32_t	ADD_EVENT		 = BASE   +1;
			const uint32_t	REMOVE_EVENT	 = BASE   +2;
			const uint32_t	EXECUTE_EVENT	 = BASE   +3;
			const uint32_t	UPDATE_EVENT	 = BASE   +4;
			const uint32_t	EVENT_LIS		 = BASE   +5;
		}
	}
}