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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGRenderer::CPoints
//
// 1. CGCrypt::CCSP��!
//    1) Windows���� �������ִ� ��ȣȭ API�� ������� Crypto class�Դϴ�. 
//
//
//-----------------------------------------------------------------------------
#include "Wincrypt.h"

namespace CGCrypt
{

_STRING8	EncodeBase64(const uint8_t* _Source, uint32_t _Length);
_STRING8	DecodeBase64(const _STRING8& _Encoded);

}
