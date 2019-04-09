//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Query Classes                            *
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
//  Query Classes
//
//
//----------------------------------------------------------------------------
namespace CGMESSAGE
{
	namespace SERVER
	{
		namespace QUERY
		{
			const uint32_t	REGISTER		 = BASE |   1;
			const uint32_t	UNREGISTER		 = BASE |   2;
			const uint32_t	OPENNING		 = BASE |   3;
			const uint32_t	OPEN			 = BASE |   4;
			const uint32_t	CLOSING			 = BASE |   5;
			const uint32_t	CLOSE			 = BASE |   6;
			const uint32_t	FAILURE			 = BASE |   7;
		}
	}
}

