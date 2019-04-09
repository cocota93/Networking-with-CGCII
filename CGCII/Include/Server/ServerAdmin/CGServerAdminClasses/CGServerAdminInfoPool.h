//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// ----------------------------------------------------------------------------
//
// CGServerAdmin
//
// 1. 
//    1) 
//    2) 
//
//
// ----------------------------------------------------------------------------
namespace CGServerAdmin
{

class CPool
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPool();
	virtual ~CPool();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			_CHAR					m_strName[MAX_NAME_LENGTH];
			CGStatistics::FACTORY	m_statisticsFactory;
};


}
