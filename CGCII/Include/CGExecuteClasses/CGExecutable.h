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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGExecutable
{

//-----------------------------------------------------------------------------
/**

 @class		NBatch
 @brief		한꺼번에 여러 개의 Executable 객체를 큐잉해 걸어주는 Executable이다. 
 @todo		
 @ref		CList<TEXECUTABLE>
 @details	\n
 여러 개의 Executable 객체를 큐잉해 실행해준다. 
 따라서 실행을 걸어주게 되면 큐잉된 Executable 객체들은 제거된다.

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
	//!	@brief 일괄처리가 완료되었을 때 처리할 내용을 정의한다.
	virtual	void				OnExecute() PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	virtual intptr_t			ProcessExecute(_In_ intptr_t /*_Return*/, _In_ size_t /*_Param*/) override { OnExecute(); return 0;}
};


}
