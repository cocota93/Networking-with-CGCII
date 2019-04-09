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

 @class		CFactoryGarbageCollection
 @brief		풀 유지를 위한 실행을 호출해준다.
 @todo		
 @ref		
 @details	\n
 Factory 매니저의 유지(Sustain)함수를 호출해 풀의 가비지 콜렉션 처리 등과 같은 유지활동을 처리한다.

*///-----------------------------------------------------------------------------
class CFactoryGarbageCollection:
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NCGSchedulable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			CFactoryGarbageCollection();
	virtual ~CFactoryGarbageCollection();


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
			LOCKABLE<CGPTR<CGFactory::Manager>>	m_pmanagerFactory;
};


}
}