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

namespace CGSchedulable
{
namespace System
{

//-----------------------------------------------------------------------------
/**

 @class		CExceptionObserver
 @brief		Exception 관리자를 일정시간마다 실행해준다.
 @todo		
 @ref		
 @details	\n
 Exception 관리자에서는 쓰레드를 감시하며 데드락 같은 것이 발생하면 강제예외를 던저
 데드락을 푸는 일과 같은 작업을 수행한다.

*///-----------------------------------------------------------------------------
class CExceptionObserver:
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NCGSchedulable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			CExceptionObserver();
	virtual ~CExceptionObserver();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) OnRegister/OnUnregister
	virtual	void				ProcessOnRegister() override;
	virtual	void				ProcessOnUnregister() override;

	// 2) Execute함수임...
	virtual	void				ProcessSchedule() override;

	// 3) ...
			LOCKABLE<CGPTR<CGException::Manager>>	m_pmanagerException;
};


}
}