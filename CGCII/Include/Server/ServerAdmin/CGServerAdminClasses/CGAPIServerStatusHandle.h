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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGAPI::ManagerPerfornamceQuery
//
// 1. CGAPI::ManagerPerfornamceQuery란!
//    1) Process등 각종 System 정보를 알아보기 위한 class임
//
//
//-----------------------------------------------------------------------------
namespace CGAPI
{

class CServerStatusHandle :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CServerStatusHandle();
	virtual	~CServerStatusHandle();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Register
			uint32_t			RegisterServiceCtrlHandle(_In_z_ const _CHAR* p_lpServiceName, _In_ __callback LPHANDLER_FUNCTION_EX _lpHandlerProc, _In_opt_ void* _lpContext = nullptr);
			uint32_t			RegisterServiceCtrlHandle(_In_z_ const _CHAR_SUB* p_lpServiceName, _In_ __callback LPHANDLER_FUNCTION_EX _lpHandlerProc, _In_opt_ void* _lpContext = nullptr);

	// 2) Status
			bool				SetServiceStatus(_In_ LPSERVICE_STATUS p_lpServiceStatus);
			eOBJECT_STATE		SetServiceStatus(_In_ eOBJECT_STATE p_dwServiceStatus, _In_ eOBJECT_STATE p_dwControlAccept = eOBJECT_STATE::DEFAULT);

			bool				IsReady() const	{	return	m_hServiceStatus!=NULL;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			SERVICE_STATUS_HANDLE	m_hServiceStatus;
};


}