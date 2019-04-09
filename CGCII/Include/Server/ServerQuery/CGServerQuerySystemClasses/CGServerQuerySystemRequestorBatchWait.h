//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                             Server DB Classes                             *
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
// CGServerQuery::DB::CRequestorBatchWait
//
// 1. CGServerQuery::DB::CRequestorConcurrentWait란!
//    1) CGServerQuery::DB::CRequestorConcurrent를 상속받아 완료시 호출되는 ProcessCompleteQuery()
//       함수만 재정의한 클래스이다.
//    2) Query를 수행후 WaitCompleteQuery()함수를 호출하면 완료될 때까지 이 함수가
//       블록킹된다. 따라서 모든 Query가 완료될 때까지 기다린 후 처리를 진행해야 
//       된다면 이 객체를 사용한다.
//
//
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DBSystem
{
namespace RequestorBatch
{

class CWait : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						NRequestorBatch
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CWait()				{	m_hComplete	 = CreateEvent(nullptr, FALSE, FALSE, nullptr);};
	virtual ~CWait()			{	CloseHandle(m_hComplete);}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) 모든 Query가 완료되기를 기대리는 함수.
			bool				WaitCompleteQuery(TICK::duration _Millisecond= TICK::milliseconds(INFINITE));


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Executor
			HANDLE				m_hComplete;

	// 2) ProcessCompleteQuery
	virtual	void				ProcessCompleteQuery()					{	SetEvent(m_hComplete);}
};

inline bool CGServerQuery::DBSystem::RequestorBatch::CWait::WaitCompleteQuery(TICK::duration _Millisecond)
{
	// Declare) 
	DWORD	dwResult;

	// 1) Wait한다.
	dwResult	 = WaitForSingleObject(m_hComplete, (uint32_t)TICK::DURATION_CAST<TICK::milliseconds>(_Millisecond).count());

	// Check) 
	RETURN_IF(dwResult!=WAIT_OBJECT_0, false);

	// Return) 
	return	true;
}


}
}
}