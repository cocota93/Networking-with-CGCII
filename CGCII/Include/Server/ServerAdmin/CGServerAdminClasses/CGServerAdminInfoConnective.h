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

class CConnective
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CConnective();
	virtual ~CConnective();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			int					GetConnectionCount() const				{	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			CONNECTIVE_INFO		m_ConnectiveInfo;
			CONNECTIVE_STATUS	m_ConnectiveStatus;
};


}
