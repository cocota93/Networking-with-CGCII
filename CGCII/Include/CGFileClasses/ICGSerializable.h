//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               File Classes                                *
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
// 1. ICGSerializable란!
//    1) Serialization을 위한 Interface class임.
//    2) SerializationIn()함수는 읽어서 넣는 함수.
//    3) SerializationOut()함수는 읽어서 빼내는 함수.
//
//-----------------------------------------------------------------------------
class ICGSerializable : virtual public ICGReferenceable
{
public:
	virtual	size_t				Serialize(_In_ ICGArchive& p_pArchive) PURE;	// 1) Load를 하는 함수.
};
