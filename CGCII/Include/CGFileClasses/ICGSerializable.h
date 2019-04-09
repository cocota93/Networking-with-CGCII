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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. ICGSerializable��!
//    1) Serialization�� ���� Interface class��.
//    2) SerializationIn()�Լ��� �о �ִ� �Լ�.
//    3) SerializationOut()�Լ��� �о ������ �Լ�.
//
//-----------------------------------------------------------------------------
class ICGSerializable : virtual public ICGReferenceable
{
public:
	virtual	size_t				Serialize(_In_ ICGArchive& p_pArchive) PURE;	// 1) Load�� �ϴ� �Լ�.
};
