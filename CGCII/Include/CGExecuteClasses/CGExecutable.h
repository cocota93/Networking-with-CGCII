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

namespace CGExecutable
{

//-----------------------------------------------------------------------------
/**

 @class		NBatch
 @brief		�Ѳ����� ���� ���� Executable ��ü�� ť���� �ɾ��ִ� Executable�̴�. 
 @todo		
 @ref		CList<TEXECUTABLE>
 @details	\n
 ���� ���� Executable ��ü�� ť���� �������ش�. 
 ���� ������ �ɾ��ְ� �Ǹ� ť�׵� Executable ��ü���� ���ŵȴ�.

*///-----------------------------------------------------------------------------
class CExecutable :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CExecutable()												{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_EXECUTABLE);}
	virtual ~CExecutable()												{}
	

// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//!	@brief �ϰ�ó���� �Ϸ�Ǿ��� �� ó���� ������ �����Ѵ�.
	virtual	void				OnExecute() PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	virtual intptr_t			ProcessExecute(_In_ intptr_t /*_Return*/, _In_ size_t /*_Param*/) override { OnExecute(); return 0;}
};


}
