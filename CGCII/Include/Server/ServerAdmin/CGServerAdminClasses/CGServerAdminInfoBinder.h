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

class CBinder
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CBinder();
	virtual ~CBinder();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			CGServerAdmin::SOCKET_INFO		m_SocketInfo;
			CGServerAdmin::SOCKET_STATUS	m_SocketStatus;
};


}
