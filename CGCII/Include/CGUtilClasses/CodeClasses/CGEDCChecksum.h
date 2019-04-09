//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Utility Classes                              *
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
// CGEDC
//
// 1. CGEDC
//    1) Error Detecting Code에 관련된...
//
//
//-----------------------------------------------------------------------------
namespace CGEDC
{

uint32_t	GetCheckSum8(uint8_t* p_pbtData, uint32_t _dwByte);
uint32_t	GetCheckSum16(uint16_t* p_pwData, uint32_t _dwByte);
uint32_t	GetCheckSum32(uint32_t* p_pdwData, uint32_t _dwByte);


}