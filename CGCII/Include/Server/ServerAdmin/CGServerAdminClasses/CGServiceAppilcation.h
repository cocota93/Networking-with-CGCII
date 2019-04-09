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
// CGServerService::CApplication
//
// 1. CGServerService::CApplication란!
//    1) CGServerService::NApplication을 상속하여 Windows Service용으로 제작한 것
//       
//
//
//-----------------------------------------------------------------------------
namespace CGServerService
{

template<typename TCLASS>
class CApplication :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NApplication
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			CApplication()		{}
	virtual	~CApplication()		{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Start/Stop/Pause/Continue
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override;
	virtual	bool				Stop() override;
	virtual	bool				Pause() override;
	virtual	bool				Continue() override;

	// 2) Init Instance/RunExecutor
	static	CGPTR<TCLASS>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	static	void				InitInstance();
	static	void				SetInstance(TCLASS* _pInstance);
	static	void				ResetInstance();

	static	uintptr_t			Run(int _argc=0, _CHAR** _pargv=nullptr);


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Static Function
	static	DWORD WINAPI		fServiceMain(int _argc, _CHAR** _pargv);
	static	DWORD WINAPI		fServiceHandler(DWORD p_dwControl, DWORD _dwEventType, void* _lpEventData, void* _lpContext);

	// 2) Instance
	static	CGOWN<TCLASS>		m_pInstance;
	static	LOCKABLE<>			m_csCreate;
};

template<typename TCLASS>
LOCKABLE<> CApplication<TCLASS>::m_csCreate;
template<typename TCLASS>
CGOWN<TCLASS> CApplication<TCLASS>::m_pInstance;

template<typename TCLASS>
void CApplication<TCLASS>::SetInstance(TCLASS* _pInstance)
{
	m_pInstance	 = _pInstance;
}

template<typename TCLASS>
void CApplication<TCLASS>::ResetInstance()
{
	m_pInstance.reset();
}

template<typename TCLASS>
void CApplication<TCLASS>::InitInstance()
{
	LOCK(m_csCreate)
	{ 
		// Check) 기존에 Instance가 있는지 확인한다.
		RETURN_IF(m_pInstance.exist(),)

		// 1)새로운 Instance를 생성한다.
		SetInstance(NEW<TCLASS>());
	}
}

template<typename TCLASS>
DWORD WINAPI CApplication<TCLASS>::fServiceMain(int _argc, _CHAR** _pargv)
{
	return	GetInstance()->ProcessService_Main(_argc, _pargv, fServiceHandler);
}

template<typename TCLASS>
DWORD WINAPI CApplication<TCLASS>::fServiceHandler(DWORD _Control, DWORD _EventType, void* _lpEventData, void* _lpContext)
{
	return	(DWORD)GetInstance()->ProcessService_Handler(_Control, _EventType, _lpEventData, _lpContext);
}

template<typename TCLASS>
bool CApplication<TCLASS>::Start(CGMSG_CONTEXT& _Msg)
{
	if(_Msg.message==CGMESSAGE::ADMIN::TEST)
	{
		// - Test일 경우...
		POST_EXECUTE([=](){ ProcessService_Main(0, nullptr, nullptr);});

		// Return) 
		return	true;
	}

	return	NApplication::Start(_Msg);
}

template<typename TCLASS>
bool CApplication<TCLASS>::Stop()
{
	return	NApplication::Stop();
}

template<typename TCLASS>
bool CApplication<TCLASS>::Pause()
{
	return	NApplication::Pause();
}

template<typename TCLASS>
bool CApplication<TCLASS>::Continue()
{
	return	NApplication::Continue();
}

template<typename TCLASS>
uintptr_t CApplication<TCLASS>::Run(int _argc, _CHAR** _pargv)
{
	// 1) Instance를 얻는다. 
	CGPTR<TCLASS>	pInstance	 = GetInstance();

	// Check) 
	ERROR_THROW_IF(pInstance.empty(), CGException::CThrow_BadAlloc(), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CApplication<TCLASS>: Fail to GetInstance() ") _CGFUNCTION));

	// Check) 
	ERROR_RETURN_IF(pInstance->GetName()[0]==NULL, (uint32_t)-1, );

	// 2) Service Mode인가를 확인한다.
	bool	bServiceMode	 = GetConsoleWindow() ? false : true;

	// 2-A) 콘솔모드면 그냥 함수 실행
	if(bServiceMode==false)
	{
		pInstance->ProcessService_Main(_argc, _pargv, nullptr);
	}
	// 2-B) 아니면 서비스 모드로 동작
	else
	{
		// Declare) 
		BOOL	bResult;

	#if defined(_USE_CHAR_STRING)
		// Declare) 
		SERVICE_TABLE_ENTRYA	sSTE[]	 = 
		{
			{ (char*)pInstance->GetName(), (LPSERVICE_MAIN_FUNCTION)fServiceMain },
			{ NULL, NULL}
		};

		// 1) 등록
		bResult	 = StartServiceCtrlDispatcherA(sSTE);
	#elif defined(_USE_WCHAR_STRING)
		// Declare) 
		SERVICE_TABLE_ENTRYW	sSTE[]	 = 
		{
			{ (wchar_t*)pInstance->GetName(), (LPSERVICE_MAIN_FUNCTION)fServiceMain },
			{ NULL, NULL}
		};

		// 1) 등록
		bResult	 = StartServiceCtrlDispatcherW(sSTE);
	#else
		CGASSERT_ERRPR(false);
	#endif

		// Check) 
		ERROR_RETURN_IF(bResult==FALSE, (uint32_t)-1, );
	}

	// Return) 
	return	0;
}


}