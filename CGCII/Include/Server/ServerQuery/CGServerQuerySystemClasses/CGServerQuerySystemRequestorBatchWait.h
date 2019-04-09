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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGServerQuery::DB::CRequestorBatchWait
//
// 1. CGServerQuery::DB::CRequestorConcurrentWait��!
//    1) CGServerQuery::DB::CRequestorConcurrent�� ��ӹ޾� �Ϸ�� ȣ��Ǵ� ProcessCompleteQuery()
//       �Լ��� �������� Ŭ�����̴�.
//    2) Query�� ������ WaitCompleteQuery()�Լ��� ȣ���ϸ� �Ϸ�� ������ �� �Լ���
//       ���ŷ�ȴ�. ���� ��� Query�� �Ϸ�� ������ ��ٸ� �� ó���� �����ؾ� 
//       �ȴٸ� �� ��ü�� ����Ѵ�.
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
	// 1) ��� Query�� �Ϸ�Ǳ⸦ ��븮�� �Լ�.
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

	// 1) Wait�Ѵ�.
	dwResult	 = WaitForSingleObject(m_hComplete, (uint32_t)TICK::DURATION_CAST<TICK::milliseconds>(_Millisecond).count());

	// Check) 
	RETURN_IF(dwResult!=WAIT_OBJECT_0, false);

	// Return) 
	return	true;
}


}
}
}