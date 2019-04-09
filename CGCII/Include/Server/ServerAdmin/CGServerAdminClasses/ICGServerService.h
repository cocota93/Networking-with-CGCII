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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// ICGServerService
//
// 1. Service�� Server�� ���۽�Ű�� ���� ���񽺸� ��üȭ�� ���̴�.
//    1) 
//    2) 
//
//
// ----------------------------------------------------------------------------
class ICGServerService : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGObjectState,
	virtual	public				ICGInitializable,
	virtual	public				ICGStartable,
	virtual public				ICGMessageable,
	virtual	public				ICGNameable
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGServerService()	{}
};
