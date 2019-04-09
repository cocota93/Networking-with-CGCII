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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// ICGServerQueryExecutable
//
// 1. ICGServerQueryExecutable란!
//    1) 비동기식 Query를 위해  ICGServerQuery와 ICGExecutable을 동시에 상속받음.
//
//-----------------------------------------------------------------------------
class ICGServerQueryExecutable : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGServerQuery,							// (I) Executable
	virtual public				ICGExecutable							// (I) Executable
{
};

