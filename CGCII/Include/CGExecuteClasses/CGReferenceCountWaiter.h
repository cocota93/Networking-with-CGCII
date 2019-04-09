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
//-----------------------------------------------------------------------------
/**

 @class		CCGReferenceCountWaiter
 @brief		참조계수가 0이 될때까지 블록킹 기능이 있는 ICGReferenceable클래스이다.
 @todo		
 @ref		
 @details	\n
 여러 작업을 동시해 수행해서 모든 작업의 완료를 기다리는 클래스이다.
 하나의 작업이 수행될 때 ReadyToWait()함수를 호출한다.
 작업의 완료를 기다리는 쪽에서는 WaitForCompletion()함수를 호출한다.
 이 함수를 호출하면 모든 작업이 완료될 때까지 기다린다.
 작업이 완료되면 Release()함수를 호출한다.
 Relese의 결과 Reference Count가 0이 되면 OnFinalRelease/ProcessDispose함수가
 호출되며 Event가 Signal되며 WaitForCompletion함수를 완료시킨다.

*///-----------------------------------------------------------------------------
class CCGReferenceCountWaiter :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CCGReferenceCountWaiter();
	virtual ~CCGReferenceCountWaiter();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			void				ReadyToWait();
			bool				WaitForComplete(_In_ TICK::duration _tickdiff=TICK::milliseconds(INFINITE));


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	// 1) Rendering을 완전히 완료시...
	virtual	void				OnFinalRelease() override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			HANDLE				m_hEvent;
};


inline CCGReferenceCountWaiter::CCGReferenceCountWaiter()
{
	// 1) Event를 생성한다.
	m_hEvent	 = CreateEvent(NULL, FALSE, FALSE, NULL);
}

inline CCGReferenceCountWaiter::~CCGReferenceCountWaiter()
{
	// 1) Event Handle을 닫는다.
	CloseHandle(m_hEvent);
}


inline void CCGReferenceCountWaiter::ReadyToWait()
{
	// Check) 
	CGASSERT_TRACE(GetReferenceCount()==0,, CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGExecutor: Reference Count must be Zero ") _CGFUNCTION));

	// 1) Reference Count를 일단 증가시킨다.
	AddRef();
}

inline bool CCGReferenceCountWaiter::WaitForComplete(_In_ TICK::duration _tickdiff)
{
	// 1) 일단 Release한번한다. (ReadyToWait할때 AddReference했던 것...)
	Release();

	// Declare)
	uint32_t	result;

	// 2) 기다린다.
	result	 = WaitForSingleObject(m_hEvent, static_cast<uint32_t>(TICK::DURATION_CAST<TICK::milliseconds>(_tickdiff).count()));

	// Check) WAIT_OBJECT_0가 아니라면 정상적인 종료가 아니다.
	RETURN_IF(result != WAIT_OBJECT_0, FALSE);

	// Check) 여기서는 무조건 Reference Count가 0이여야지만 된다.
	CGASSERT_ERROR(GetReferenceCount()==0);


	// Return) 성공!!
	return	TRUE;
}

inline void CCGReferenceCountWaiter::OnFinalRelease()
{
	//----------------------------------------------------------------
	// Release()를 수행하여 Reference Count가 0이 되면 이 함수가 호출
	// 되고 이때 Event를 Signal시키게 된다.
	// 그러면 WaitForComplete함수가 완료가 되어 Return하게 된다.
	//----------------------------------------------------------------
	SetEvent(m_hEvent);
}
