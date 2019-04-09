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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		CCGReferenceCountWaiter
 @brief		��������� 0�� �ɶ����� ���ŷ ����� �ִ� ICGReferenceableŬ�����̴�.
 @todo		
 @ref		
 @details	\n
 ���� �۾��� ������ �����ؼ� ��� �۾��� �ϷḦ ��ٸ��� Ŭ�����̴�.
 �ϳ��� �۾��� ����� �� ReadyToWait()�Լ��� ȣ���Ѵ�.
 �۾��� �ϷḦ ��ٸ��� �ʿ����� WaitForCompletion()�Լ��� ȣ���Ѵ�.
 �� �Լ��� ȣ���ϸ� ��� �۾��� �Ϸ�� ������ ��ٸ���.
 �۾��� �Ϸ�Ǹ� Release()�Լ��� ȣ���Ѵ�.
 Relese�� ��� Reference Count�� 0�� �Ǹ� OnFinalRelease/ProcessDispose�Լ���
 ȣ��Ǹ� Event�� Signal�Ǹ� WaitForCompletion�Լ��� �Ϸ��Ų��.

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
	// 1) Rendering�� ������ �Ϸ��...
	virtual	void				OnFinalRelease() override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			HANDLE				m_hEvent;
};


inline CCGReferenceCountWaiter::CCGReferenceCountWaiter()
{
	// 1) Event�� �����Ѵ�.
	m_hEvent	 = CreateEvent(NULL, FALSE, FALSE, NULL);
}

inline CCGReferenceCountWaiter::~CCGReferenceCountWaiter()
{
	// 1) Event Handle�� �ݴ´�.
	CloseHandle(m_hEvent);
}


inline void CCGReferenceCountWaiter::ReadyToWait()
{
	// Check) 
	CGASSERT_TRACE(GetReferenceCount()==0,, CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGExecutor: Reference Count must be Zero ") _CGFUNCTION));

	// 1) Reference Count�� �ϴ� ������Ų��.
	AddRef();
}

inline bool CCGReferenceCountWaiter::WaitForComplete(_In_ TICK::duration _tickdiff)
{
	// 1) �ϴ� Release�ѹ��Ѵ�. (ReadyToWait�Ҷ� AddReference�ߴ� ��...)
	Release();

	// Declare)
	uint32_t	result;

	// 2) ��ٸ���.
	result	 = WaitForSingleObject(m_hEvent, static_cast<uint32_t>(TICK::DURATION_CAST<TICK::milliseconds>(_tickdiff).count()));

	// Check) WAIT_OBJECT_0�� �ƴ϶�� �������� ���ᰡ �ƴϴ�.
	RETURN_IF(result != WAIT_OBJECT_0, FALSE);

	// Check) ���⼭�� ������ Reference Count�� 0�̿������� �ȴ�.
	CGASSERT_ERROR(GetReferenceCount()==0);


	// Return) ����!!
	return	TRUE;
}

inline void CCGReferenceCountWaiter::OnFinalRelease()
{
	//----------------------------------------------------------------
	// Release()�� �����Ͽ� Reference Count�� 0�� �Ǹ� �� �Լ��� ȣ��
	// �ǰ� �̶� Event�� Signal��Ű�� �ȴ�.
	// �׷��� WaitForComplete�Լ��� �Ϸᰡ �Ǿ� Return�ϰ� �ȴ�.
	//----------------------------------------------------------------
	SetEvent(m_hEvent);
}
