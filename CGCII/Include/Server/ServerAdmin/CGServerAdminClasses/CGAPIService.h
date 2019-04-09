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
// CGAPI ServiceFunctions
//
// 1. CGAPI::ManagerPerfornamceQuery란!
//    1) Process등 각종 System 정보를 알아보기 위한 class임
//
//
//-----------------------------------------------------------------------------
namespace CGAPI
{

// 1) Install/UnInstall
	_Success_(return != false)  bool ServiceInstall(
	_In_z_ const _CHAR*		_pszSvcDispName	 = nullptr,
	_In_z_ const _CHAR*		_pszSvcDesc		 = nullptr,
	_In_ uint32_t			_DesiredAccess	 = SERVICE_ALL_ACCESS,
	_In_ uint32_t			_ServiceType	 = SERVICE_WIN32_OWN_PROCESS,
	_In_ uint32_t			_StartType		 = SERVICE_AUTO_START,
	_In_ uint32_t			_ErrorControl	 = SERVICE_ERROR_NORMAL);
_Success_(return != false)  bool ServiceInstall(
	_In_z_ const _CHAR_SUB*	_pszSvcDispName	 = nullptr,
	_In_z_ const _CHAR_SUB*	_pszSvcDesc		 = nullptr,
	_In_ uint32_t			_DesiredAccess	 = SERVICE_ALL_ACCESS,
	_In_ uint32_t			_ServiceType	 = SERVICE_WIN32_OWN_PROCESS,
	_In_ uint32_t			_StartType		 = SERVICE_AUTO_START,
	_In_ uint32_t			_ErrorControl	 = SERVICE_ERROR_NORMAL);
_Success_(return != false)  bool ServiceUninstall();

// 2) Start/Stop/Pause/Contiune
_Success_(return!=false)  bool ServiceStart(_In_z_ const _CHAR* _strServiceName, _In_ uint32_t p_dwNumServiceArgs, _In_reads_opt_(p_dwNumServiceArgs) const _CHAR** p_lpServiceArgVectors);
_Success_(return!=false)  bool ServiceStart(_In_z_ const _CHAR_SUB* _strServiceName, _In_ uint32_t p_dwNumServiceArgs, _In_reads_opt_(p_dwNumServiceArgs) const _CHAR_SUB** p_lpServiceArgVectors);
_Success_(return!=false)  bool ServiceStop(_In_z_ const _CHAR* _strServiceName);
_Success_(return!=false)  bool ServiceStop(_In_z_ const _CHAR_SUB* _strServiceName);
_Success_(return!=false)  bool ServicePause(_In_z_ const _CHAR* _strServiceName);
_Success_(return!=false)  bool ServicePause(_In_z_ const _CHAR_SUB* _strServiceName);
_Success_(return!=false)  bool ServiceContinue(_In_z_ const _CHAR* _strServiceName);
_Success_(return!=false)  bool ServiceContinue(_In_z_ const _CHAR_SUB* _strServiceName);

// 3) Status
uint32_t GetServiceStatus(_In_z_ const _CHAR* _strServiceName);
uint32_t GetServiceStatus(_In_z_ const _CHAR_SUB* _strServiceName);

// 4) Util..
_Success_(return!=0) uint32_t GetServicePathName(_Out_writes_opt_z_(MAX_PATH) _CHAR* _strServiceName, _Out_writes_opt_z_(MAX_PATH) _CHAR* _strBinaryPathName = nullptr);
_Success_(return!=0) uint32_t GetServicePathName(_Out_writes_opt_z_(MAX_PATH) _CHAR_SUB* _strServiceName, _Out_writes_opt_z_(MAX_PATH) _CHAR_SUB* _strBinaryPathName = nullptr);

}

namespace CGServerAdmin
{

	CCGBuffer GetMessage_SendConnectiveInfo();
	CCGBuffer GetMessage_SendBinderInfo();
	CCGBuffer GetMessage_SendEventInfo();
	CCGBuffer GetMessage_SendPoolInfo();

	CCGBuffer GetMessage_UpdateTrafficStatus();
	CCGBuffer GetMessage_UpdateConnectiveStatus();
	CCGBuffer GetMessage_UpdateBinderStatus();
	CCGBuffer GetMessage_UpdateEventStatus();
	CCGBuffer GetMessage_UpdatePoolStatus();

}

