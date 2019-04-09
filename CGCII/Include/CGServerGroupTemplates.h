//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Group Template Classes                           *
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
// Definitions
// ----------------------------------------------------------------------------
#define	CGNET_GROUP_TEMPLATES


// ----------------------------------------------------------------------------
// head Fileµé                                                               
// ----------------------------------------------------------------------------
// 1) Non-Standard Warning (nonstandard extension used : 'default argument' : conversion)
#if defined(_MSC_VER)
	#pragma warning(disable:4239)
#endif

// 2) Base Classes
#include "CGNetSocketClasses.h"


// ----------------------------------------------------------------------------
//                                                             
// ----------------------------------------------------------------------------
// Definitions) 
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupDefinitions.h"

// 1) Group
#include "Server/ServerSystem/CGServerGroupTemplate/ICGServerGroup.h"

// 2) Member Containerable
#include "Server/ServerSystem/CGServerGroupTemplate/ICGServerMemberContainerable.h"

// 3) Member Data
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupMemberData.h"

// 4) Memberable
#include "Server/ServerSystem/CGServerGroupTemplate/ICGServerGroupable.h"


// 5) Group
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupNoManage.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupNoManageDispatchable.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupCount.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupCountDispatchable.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupList.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupListDispatchable.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupListSender.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupListSenderDispatchable.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArray.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArrayDispatchable.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArraySender.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArraySenderDispatchable.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArraySeat.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArraySeatDispatchable.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArraySeatSender.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArraySeatSenderDispatchable.h"

// 6) Observers
#include "Server/ServerSystem/CGServerGroupTemplate/ICGServerObserver.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerObserverList.h"
#include "Server/ServerSystem/CGServerGroupTemplate/CGServerObserverListSender.h"
