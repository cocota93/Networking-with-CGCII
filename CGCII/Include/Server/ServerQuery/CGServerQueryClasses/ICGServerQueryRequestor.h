//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Query Classes                            *
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
// ICGServerQueryRequestor
//
// 1. ICGServerQuery��!
//    1) Query�� ó�� ������ ���޹ޱ� ���� �������̽� Ŭ����
//
//-----------------------------------------------------------------------------
class ICGServerQueryRequestor : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						//     Reference Count
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGServerQueryRequestor()									{}
	virtual ~ICGServerQueryRequestor()									{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual	void				ProcessNotifyCompleteQuery(ICGServerQuery* _pQuery) PURE;
};

