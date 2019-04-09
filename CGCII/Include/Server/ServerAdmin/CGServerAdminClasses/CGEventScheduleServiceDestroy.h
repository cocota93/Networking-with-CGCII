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
namespace Schedule
{

class CServiceDestroy : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::ISchedule
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			CServiceDestroy(ICGServerService* p_pService=nullptr);
	virtual ~CServiceDestroy();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			void				SetService(ICGServerService* p_pService);
			CGPTR<ICGServerService>	GetService() const					{	return m_pService;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual eOBJECT_RESULT		ProcessExecuteFunction(const TIME::SYSTEM::time_point& p_rTime);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			CGPTR<ICGServerService>	m_pService;
};


}
}