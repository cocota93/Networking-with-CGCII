//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                      Network Socket Template Classes                      *
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
//* Definitions
//-----------------------------------------------------------------------------
#define	CGNET_SOCKET_TEMPLATES


//-----------------------------------------------------------------------------
//* head Fileµé                                                               *
//-----------------------------------------------------------------------------
// 1) Base Classes
#include "CGNetSocketClasses.h"

// 2) Definitions
#include "Network/Socket/CGNetSocketTemplate/CGNetDefinitionSocketTemplates.h"

// 3) TCP Socket
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCP.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPDispatchable.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPRIO.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPNoGather.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPQueue.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPServer.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPServerNoGather.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPFixed.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPFixedNoGather.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPFixedQueue.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPClient.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketTCPClientReconnect.h"

// 4) UDP Socket
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketUDP.h"
#include "Network/Socket/CGNetSocketTemplate/CGNetSocketUDPResend.h"

// 5) Acceptor
#include "Network/Socket/CGNetSocketTemplate/CGNetAcceptor.h"

// 6) Connector
#include "Network/Socket/CGNetSocketTemplate/CGNetConnector.h"
