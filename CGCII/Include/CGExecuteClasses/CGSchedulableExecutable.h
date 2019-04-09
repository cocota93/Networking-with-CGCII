//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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

namespace CGSchedulable
{

//-----------------------------------------------------------------------------
/**

 @class		NExecutable
 @brief		�����ð����� Executable�� �ɾ��ִ� Schedulable Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 �����ð����� Executor�� ������ �ɷ����� Schedulable ��ü�̴�.
 ���ణ���� SetExecuteInterval()�Լ��� ������ �� �ִ�
 ������ Executor�� SetExecutor()�Լ��� ������ �� �ִ�.
 ���� Executor�� �����Ǿ��� ���� ������ Default Executor���� ����ȴ�.

*///-----------------------------------------------------------------------------
class CExecutable :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public				CGSchedulable::NExecutable,
	public				CGExecutable::CExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
	CExecutable(_In_ TICK::duration _tickdifferExecute=TICK::seconds(1)) : CGSchedulable::NExecutable(_tickdifferExecute), CGExecutable::CExecutable() { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_EXECUTABLE);}
	virtual ~CExecutable()		{}


};


}
