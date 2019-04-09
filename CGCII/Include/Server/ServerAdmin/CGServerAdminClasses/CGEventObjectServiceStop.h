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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// CCGEventObjectServiceStart
//
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

class CServiceStop :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::Object::COnce
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CServiceStop(ICGServerService* p_pService=nullptr);
	virtual ~CServiceStop();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetService(ICGServerService* p_pService);
			CGPTR<ICGServerService>	GetService() const					{	return m_pService;}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	virtual	eOBJECT_RESULT		ProcessEvent(_In_ const TIME::SYSTEM::time_point& p_rTime);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			CGPTR<ICGServerService>	m_pService;
};


}
}