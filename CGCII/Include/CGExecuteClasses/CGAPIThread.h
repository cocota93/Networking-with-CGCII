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
namespace CGAPI
{

template<class _Rep, class _Period>
inline void Sleep(const std::chrono::duration<_Rep, _Period>& _tick)	{	std::this_thread::sleep_for(_tick);}
inline void Sleep(uint64_t _tick)										{	::Sleep(static_cast<uint32_t>(_tick));}
inline void Sleep(uint32_t _tick)										{	::Sleep(_tick);}

//-----------------------------------------------------------------------------
/**

 @class		CThread
 @brief		Thread API�Լ����� Wrapping�� Class�̴�.
 @todo		
 @ref
 @details	\n

*///-----------------------------------------------------------------------------
class CThread : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNameable::NString,
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CThread()													{}
	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
	//! @brief ������ ���ÿ� �����带 �����Ѵ�. @param _Function ������ �Լ� @param _Arguments ����� ���޵� ���ڵ�
			template<class TFN, class... TARGS>
			CThread(TFN&& _Function, TARGS&&... _Arguments) : CGNameable::NString() { Begin(_Function, _Arguments...); }
	#elif _MSC_VER>=_MSC_VER_2010
	//! @brief ������ ���ÿ� �����带 �����Ѵ�. @param _Function ������ �Լ�
			template<class TFN>
			CThread(TFN&& _Function)									{	Begin(std::forward<TFN>(_Function));}
			template<class TFN, class TPARAM1>
			CThread(TFN&& _Function, TPARAM1&& p1)						{	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1));}
			template<class TFN, class TPARAM1, class TPARAM2>
			CThread(TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2)		{	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));}
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			CThread(TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));}
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3, class TPARAM4>
			CThread(TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3, TPARAM4&& p4){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3), std::forward<TPARAM4>(p4));}
	#else
		#error	"CGExecute: Unsupported compiler"
	#endif
	virtual	~CThread();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
	//! @brief �����带 �����Ѵ�. @param _pFunction ������ �Լ� @param _Arguments ����� ���޵� ����
			template<class TFN, class... TARGS>
			void				Begin(TFN&& _Function, TARGS&&... _Arguments);
	#elif _MSC_VER>=_MSC_VER_2010
	//! @brief �����带 �����Ѵ�. @param _pFunction ������ �Լ�
			template<class TFN>
			void				Begin(TFN _pFunction);
			template<class TFN, class TPARAM1>
			void				Begin(TFN _Function, TPARAM1&& p1);
			template<class TFN, class TPARAM1, class TPARAM2>
			void				Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2);
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			void				Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3);
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3, class TPARAM4>
			void				Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3, TPARAM4&& p4);
	#else
		#error	"CGExecute: Unsupported compiler"
	#endif

	//! @brief ��� �����尡 ���� ������ ��ٸ���.
			bool				Wait();
	//! @brief �������� ������ �ߴܽ�Ų��. @return true ���� @return false ����
			bool				Terminate(_In_ uint32_t _ExitCode=-1, _In_ TICK::duration _tickWait=TICK::seconds(60));
	//! @brief �������� ������ ��� �ߴ��Ѵ�. @return ������ �ڵ�
			uint32_t			Suspend();
	//! @brief ��� �ߴ� �ߴ� �����带 �ٽ� �����Ѵ�. @return ������ �ڵ�
			uint32_t			Resume();
	//!	@brief ������ ���ܸ� �߻���Ų��. @return true ���� @return false ����
			bool				RaiseException();

	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2012
	//! @brief ������ �ڵ��� ��´�. @return ������ ID
			THREAD_ID			GetThreadHandle() const					{	return m_thread.native_handle();}
	#else
	//! @brief ������ �ڵ��� ��´�. @return ������ ID
			THREAD_ID			GetThreadHandle() const					{	return m_thread;}
	#endif
	//! @brief �ּ� ����� �ð��� ��´�. @return ���� ����� �ð�
			TICK::time_point	GetLastExecute() const					{	return m_statisticsThread.tickLastExecute;}
	//! @brief ��� ������ ��´�. @return ��� ����
			const THREAD_STATISTICS&	GetThreadStatistics() const		{	return m_statisticsThread;}
	//! @brief ������ ����� �ð����� ���� �ð��� �������� Ȯ���Ѵ�. @param _tickDifferTime �Ѱ� �ð�  @return true ������. @return false ������ �ʾҴ�.
			bool				IsTimeout(_In_ TICK::duration _tickDifferTime) const;
	//! @brief ����ð��� ������ ����� �ð��� ���� ���� �ð��̻� �Ǵ��� Ȯ���Ѵ�. @param _tickDifferTime �Ѱ� �ð� @param _tickNow ���� �ð�  @return true ������. @return false ������ �ʾҴ�.
			bool				IsTimeout(_In_ TICK::duration _tickDifferTime, _In_ TICK::time_point _tickNow) const;

	//! @brief �������] ������ ��ü�� �ʱ�ȭ�� �Ѵ�.
			void				Reset();

	//! @brief �������] ������ ���� Ƚ��
			void				Statistics_ExecutingBegin();
	//! @brief �������] ������ ���� Ƚ��
			void				Statistics_ExecutingEnd();
	//! @brief �������] ������ ����
			void				Statistics_Error();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	//! @brief ������ �Լ�
	template <class TTYPE>
	static	void				fnProcessThread(CGAPI::CThread* _pThread, TTYPE* _Functor);

	//! @brief ������ ��ü�� ����Ѵ�.
			void				RegisterThread();
	//! @brief ������ ��ü�� ��� �����Ѵ�.
			void				UnregisterThread();
	//! @brief ������ ���� �� ó���� ������ �Լ�
			void				ProcessBeginThread();
	//! @brief ������ ���� �� ó���� ������ �Լ�
			void				ProcessEndThread();
			
private:
			LOCKABLE<CGPTR<CGAPI::ManagerThread>> m_pManager;
	friend	CGAPI::ManagerThread;

	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2012
	mutable std ::thread		m_thread;
	#else
	mutable HANDLE				m_thread;
	#endif
			THREAD_STATISTICS	m_statisticsThread;
};

CGPTR<CGAPI::CThread>	GetCurrentThread();


template <class TTYPE>
void CGAPI::CThread::fnProcessThread(CGAPI::CThread* _pThread, TTYPE* _Functor)
{
	// 1) Hold
	CGPTR<CGAPI::CThread>	pThread = _pThread;

	// 2) Functor ȣ���� ����ó��
	pThread->ProcessBeginThread();

	// 3) Functor�� ȣ���Ѵ�.
	try
	{
		(*_Functor)();
	}
	catch (...)
	{
	}

	// 4) Functor�� �����.
	delete _Functor;

	// 5) Functor ȣ���� ����ó��
	pThread->ProcessEndThread();

	// 6) Reference Count ����.
	pThread->Release();
}

#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
template<class TFN, class... TARGS>
void CGAPI::CThread::Begin(TFN&& _Function, TARGS&&... _Arguments)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...))	TFUNCTOR;

	// 1) Thread���� ������ Functor ����~
	TFUNCTOR*	pfunctor = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...);

	// 2) Reference Count ����.
	AddRef();

	try
	{
		// 3) Thread�� �����ؼ� �����Ѵ�.
		m_thread = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);
	}
	catch(...)
	{
		// - Release
		NO_EXCEPTION_BEGIN
		{
			Release();
		}
		NO_EXCEPTION_END

		// - delete
		NO_EXCEPTION_BEGIN
		{
			delete	pfunctor;
		}
		NO_EXCEPTION_END

		// Reraise)
		throw;
	}

	// 4) Thread ID�� Reset�Ѵ�.
	m_statisticsThread.idThread = m_thread.native_handle();
}

#elif _MSC_VER>=_MSC_VER_2010
template<class TFN>
void CGAPI::CThread::Begin(TFN _Function)
{
	// Declare) 
	typedef	decltype(std::bind(_Function))	TFUNCTOR;

	// 1) Functor ����
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function));

	// 2) Reference Count ����.
	AddRef();

	try
	{
		// 3) thread ��ü ������ ���� ��ȯ
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 3) Thread ID�� Reset�Ѵ�.
		m_statisticsThread.idThread = m_thread.native_handle();
	}
	catch(...)
	{
		// - Release
		NO_EXCEPTION_BEGIN
		{
			Release();
		}
		NO_EXCEPTION_END

		// - functor �����
		NO_EXCEPTION_BEGIN
		{
			delete	pfunctor;
		}
		NO_EXCEPTION_END

		// Reraise)
		throw;
	}
}

template<class TFN, class TPARAM1>
void CGAPI::CThread::Begin(TFN _Function, TPARAM1&& p1)
{
	// Declare) 
	typedef	decltype(std::bind(_Function, p1))	TFUNCTOR;

	// 1) Functor �����
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function, p1));

	// 2) Reference Count ����.
	AddRef();

	try
	{
		// 3) thread ��ü ������ ���� ��ȯ
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 4) Thread ID�� Reset�Ѵ�.
		m_statisticsThread.idThread = m_thread.native_handle();
	}
	catch(...)
	{
		// - Release
		NO_EXCEPTION_BEGIN
		{
			Release();
		}
		NO_EXCEPTION_END

		// - functor �����
		NO_EXCEPTION_BEGIN
		{
			delete	pfunctor;
		}
		NO_EXCEPTION_END

		// Reraise)
		throw;
	}
}

template<class TFN, class TPARAM1, class TPARAM2>
void CGAPI::CThread::Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2)
{
	// Declare) 
	typedef	decltype(std::bind(_Function, p1, p2))	TFUNCTOR;

	// 1) Functor �����
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function, p1, p2));

	// 2) Reference Count ����.
	AddRef();

	try
	{
		// 2) thread ��ü ������ ���� ��ȯ
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 3) Thread ID�� Reset�Ѵ�.
		m_statisticsThread.idThread = m_thread.native_handle();
	}
	catch(...)
	{
		// - Release
		NO_EXCEPTION_BEGIN
		{
			Release();
		}
		NO_EXCEPTION_END

		// - functor �����
		NO_EXCEPTION_BEGIN
		{
			delete	pfunctor;
		}
		NO_EXCEPTION_END

		// Reraise)
		throw;
	}
}

template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
void CGAPI::CThread::Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3)
{
	// Declare) 
	typedef	decltype(std::bind(_Function, p1, p2, p3))	TFUNCTOR;

	// 1) Functor �����
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function, p1, p2, p3));

	// 2) Reference Count ����.
	AddRef();

	try
	{
		// 2) thread ��ü ������ ���� ��ȯ
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 3) Thread ID�� Reset�Ѵ�.
		m_statisticsThread.idThread = m_thread.native_handle();
	}
	catch(...)
	{
		// - Release
		NO_EXCEPTION_BEGIN
		{
			Release();
		}
		NO_EXCEPTION_END

		// - functor �����
		NO_EXCEPTION_BEGIN
		{
			delete	pfunctor;
		}
		NO_EXCEPTION_END

		// Reraise)
		throw;
	}
}

template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3, class TPARAM4>
void CGAPI::CThread::Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3, TPARAM4&& p4)
{
	// Declare) 
	typedef	decltype(std::bind(_Function, p1, p2, p3, p4))	TFUNCTOR;

	// 1) Functor �����
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function, p1, p2, p3, p4));

	// 2) Reference Count ����.
	AddRef();

	try
	{
		// 2) thread ��ü ������ ���� ��ȯ
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 3) Thread ID�� Reset�Ѵ�.
		m_statisticsThread.idThread = m_thread.native_handle();
	}
	catch(...)
	{
		// - Release
		NO_EXCEPTION_BEGIN
		{
			Release();
		}
		NO_EXCEPTION_END

		// - functor �����
		NO_EXCEPTION_BEGIN
		{
			delete	pfunctor;
		}
		NO_EXCEPTION_END

		// Reraise)
		throw;
	}
}

#else
	#error	"CGExecute: Unsupported compiler"
#endif


}
