//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               State Classes                               *
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
#define	CGNET_STATE_TEMPLATES


// ----------------------------------------------------------------------------
// head Fileµé                                                               
// ----------------------------------------------------------------------------
// 1) Definitions
#include "CGObjectClasses.h"


//-----------------------------------------------------------------------------
// Basic
//-----------------------------------------------------------------------------
// 1) Definitions
#include "CGStateClasses/CGDefinitionsStateProtocol.h"
#include "CGStateClasses/CGDefinitionsState.h"

// 2) State
#include "CGStateClasses/ICGState.h"
#include "CGStateClasses/CGStateUpdatable.h"
#include "CGStateClasses/CGStateUpdatableMember.h"
#include "CGStateClasses/CGStateUpdatableMessageable.h"
#include "CGStateClasses/CGStateUpdatableMessageableMember.h"

// 3) State Table
#include "CGStateClasses/ICGStateTable.h"
#include "CGStateClasses/CGStateTable.h"

// 4) State Control
#include "CGStateClasses/ICGStateable.h"
#include "CGStateClasses/CCGStateable.h"
#include "CGStateClasses/ICGStateableControl.h"
#include "CGStateClasses/NCGStateableControl.h"
#include "CGStateClasses/CGStateableControl.h"

// 5) FSM Transition Table
#include "CGStateClasses/ICGFSMTransitionTable.h"
#include "CGStateClasses/CGFSMTransitionTable.h"

// 6) FSM Control
#include "CGStateClasses/ICGFSMControl.h"
#include "CGStateClasses/NCGFSMControl.h"
#include "CGStateClasses/CCGFSMControl.h"
