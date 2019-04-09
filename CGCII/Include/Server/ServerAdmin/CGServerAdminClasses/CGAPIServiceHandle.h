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

class CServiceHandle :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CServiceHandle();
	virtual ~CServiceHandle();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Open / Close
							void	OpenSCManager(_In_ uint32_t _DesiredAccess=SC_MANAGER_ALL_ACCESS);
							void	OpenSCManager(_In_opt_z_ const _CHAR* _lpMachineName, _In_opt_z_ const _CHAR* _lpDatabaseName = nullptr, _In_ uint32_t _DesiredAccess = SC_MANAGER_ALL_ACCESS);
							void	OpenSCManager(_In_opt_z_ const _CHAR_SUB* _lpMachineName, _In_opt_z_ const _CHAR_SUB* _lpDatabaseName = nullptr, _In_ uint32_t _DesiredAccess = SC_MANAGER_ALL_ACCESS);
							void	Open(_In_ SC_HANDLE _hSCManager, _In_z_ const _CHAR* _lpServiceName, _In_ uint32_t _DesiredAccess = SERVICE_ALL_ACCESS);
							void	Open(_In_ SC_HANDLE _hSCManager, _In_z_ const _CHAR_SUB* _lpServiceName, _In_ uint32_t _DesiredAccess = SERVICE_ALL_ACCESS);

							void	Create(
										_In_ SC_HANDLE				_hSCManager,
										_In_z_ const _CHAR*			_lpServiceName,
										_In_opt_z_ const _CHAR*		_lpDisplayName,
										_In_ uint32_t				_DesiredAccess,
										_In_ uint32_t				_ServiceType,
										_In_ uint32_t				_StartType,
										_In_ uint32_t				_ErrorControl,
										_In_opt_z_ const _CHAR*		_lpBinaryPathName,
										_In_opt_z_ const _CHAR*		_lpLoadOrderGroup	= nullptr,
										_Out_opt_ uint32_t*			_lpdwTagId			= nullptr,
										_In_opt_z_ const _CHAR*		_lpDependencies		= nullptr,
										_In_opt_z_ const _CHAR*		_lpServiceStartName	= nullptr,
										_In_opt_z_ const _CHAR*		_lpPassword			= nullptr);

							void	Create(
										_In_ SC_HANDLE				_hSCManager,
										_In_z_ const _CHAR_SUB*		_lpServiceName,
										_In_opt_z_ const _CHAR_SUB*	_lpDisplayName,
										_In_ uint32_t				_DesiredAccess,
										_In_ uint32_t				_ServiceType,
										_In_ uint32_t				_StartType,
										_In_ uint32_t				_ErrorControl,
										_In_opt_z_ const _CHAR_SUB*	_lpBinaryPathName,
										_In_opt_z_ const _CHAR_SUB*	_lpLoadOrderGroup	= nullptr,
										_Out_opt_ uint32_t*			_lpdwTagId			= nullptr,
										_In_opt_z_ const _CHAR_SUB*	_lpDependencies		= nullptr,
										_In_opt_z_ const _CHAR_SUB*	_lpServiceStartName	= nullptr,
										_In_opt_z_ const _CHAR_SUB*	_lpPassword			= nullptr);

	_Success_(return!=false) bool	Delete();
	_Success_(return!=false) bool	Close();

	// 2) Service Configure
	_Success_(return!=false) bool	SetConfig(_In_ uint32_t _dwInfoLevel, _In_opt_ void* _lpInfo);

	_Success_(return!=false) bool	SetDescription(_In_z_ const _CHAR* _strServiceDescription);
	_Success_(return!=false) bool	SetDescription(_In_z_ const _CHAR_SUB* _strServiceDescription);

	// 3) Service Control
	_Success_(return!=false) bool	Start(_In_ uint32_t _dwNumServiceArgs=0, _In_reads_opt_(_dwNumServiceArgs) const _CHAR** _lpServiceArgVectors=nullptr);
	_Success_(return!=false) bool	Start(_In_ uint32_t _dwNumServiceArgs=0, _In_reads_opt_(_dwNumServiceArgs) const _CHAR_SUB** _lpServiceArgVectors=nullptr);
	_Success_(return!=false) bool	Control(_In_ uint32_t _dwControl, _Out_ LPSERVICE_STATUS _lpServiceStatus);
	_Success_(return!=false) bool	Stop();
	_Success_(return!=false) bool	Pause();
	_Success_(return!=false) bool	Continue();
	_Success_(return!=false) bool	GetStatus(_Out_ LPSERVICE_STATUS _lpServiceStatus);
	_Success_(return!=0) uint32_t	GetStatus();
	_Success_(return!=false) bool	QueryStatus(_Out_ LPSERVICE_STATUS _lpServiceStatus);

	// 4) Status
							bool	IsReady() const	{	return	m_hService!=NULL;}

	// 5) Operator
			operator SC_HANDLE()	{	return m_hService;}
			

// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			SC_HANDLE			m_hService;
};


}