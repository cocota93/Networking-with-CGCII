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
namespace CGAPI
{

template<class _Rep, class _Period>
inline void Sleep(const std::chrono::duration<_Rep, _Period>& _tick)	{	std::this_thread::sleep_for(_tick);}
inline void Sleep(uint64_t _tick)										{	::Sleep(static_cast<uint32_t>(_tick));}
inline void Sleep(uint32_t _tick)										{	::Sleep(_tick);}

//-----------------------------------------------------------------------------
/**

 @class		CThread
 @brief		Thread API함수들을 Wrapping한 Class이다.
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
	//! @brief 생성과 동시에 쓰레드를 시작한다. @param _Function 실행할 함수 @param _Arguments 실행시 전달될 인자들
			template<class TFN, class... TARGS>
			CThread(TFN&& _Function, TARGS&&... _Arguments) : CGNameable::NString() { Begin(_Function, _Arguments...); }
	#elif _MSC_VER>=_MSC_VER_2010
	//! @brief 생성과 동시에 쓰레드를 시작한다. @param _Function 실행할 함수
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
	//! @brief 쓰레드를 시작한다. @param _pFunction 실행할 함수 @param _Arguments 실행시 전달될 인자
			template<class TFN, class... TARGS>
			void				Begin(TFN&& _Function, TARGS&&... _Arguments);
	#elif _MSC_VER>=_MSC_VER_2010
	//! @brief 쓰레드를 시작한다. @param _pFunction 실행할 함수
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

	//! @brief 모든 쓰레드가 끝날 때까지 기다린다.
			bool				Wait();
	//! @brief 쓰레드의 강제로 중단시킨다. @return true 성공 @return false 실패
			bool				Terminate(_In_ uint32_t _ExitCode=-1, _In_ TICK::duration _tickWait=TICK::seconds(60));
	//! @brief 쓰레드의 실행을 잠시 중단한다. @return 쓰레드 핸들
			uint32_t			Suspend();
	//! @brief 잠시 중단 했던 쓰레드를 다시 시작한다. @return 쓰레드 핸들
			uint32_t			Resume();
	//!	@brief 강제로 예외를 발생시킨다. @return true 성공 @return false 실패
			bool				RaiseException();

	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2012
	//! @brief 쓰레드 핸들을 얻는다. @return 쓰레드 ID
			THREAD_ID			GetThreadHandle() const					{	return m_thread.native_handle();}
	#else
	//! @brief 쓰레드 핸들을 얻는다. @return 쓰레드 ID
			THREAD_ID			GetThreadHandle() const					{	return m_thread;}
	#endif
	//! @brief 최수 실행된 시간을 얻는다. @return 최후 실행된 시간
			TICK::time_point	GetLastExecute() const					{	return m_statisticsThread.tickLastExecute;}
	//! @brief 통계 정보를 얻는다. @return 통계 정보
			const THREAD_STATISTICS&	GetThreadStatistics() const		{	return m_statisticsThread;}
	//! @brief 마지막 실행된 시간에서 일정 시간이 지났는지 확인한다. @param _tickDifferTime 한계 시간  @return true 지났다. @return false 지나지 않았다.
			bool				IsTimeout(_In_ TICK::duration _tickDifferTime) const;
	//! @brief 현재시간과 마지막 실행된 시간의 차가 일정 시간이상 되는지 확인한다. @param _tickDifferTime 한계 시간 @param _tickNow 현재 시간  @return true 지났다. @return false 지나지 않았다.
			bool				IsTimeout(_In_ TICK::duration _tickDifferTime, _In_ TICK::time_point _tickNow) const;

	//! @brief 통계정보] 쓰레드 객체를 초기화를 한다.
			void				Reset();

	//! @brief 통계정보] 쓰레드 시작 횟수
			void				Statistics_ExecutingBegin();
	//! @brief 통계정보] 쓰레드 종료 횟수
			void				Statistics_ExecutingEnd();
	//! @brief 통계정보] 쓰레드 에러
			void				Statistics_Error();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	//! @brief 쓰레드 함수
	template <class TTYPE>
	static	void				fnProcessThread(CGAPI::CThread* _pThread, TTYPE* _Functor);

	//! @brief 쓰레드 객체를 등록한다.
			void				RegisterThread();
	//! @brief 쓰레드 객체를 등록 해제한다.
			void				UnregisterThread();
	//! @brief 쓰레드 시작 시 처리를 정의한 함수
			void				ProcessBeginThread();
	//! @brief 쓰레드 종료 시 처리를 정의한 함수
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

	// 2) Functor 호출전 사전처리
	pThread->ProcessBeginThread();

	// 3) Functor를 호출한다.
	try
	{
		(*_Functor)();
	}
	catch (...)
	{
	}

	// 4) Functor를 지운다.
	delete _Functor;

	// 5) Functor 호출후 사전처리
	pThread->ProcessEndThread();

	// 6) Reference Count 증가.
	pThread->Release();
}

#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
template<class TFN, class... TARGS>
void CGAPI::CThread::Begin(TFN&& _Function, TARGS&&... _Arguments)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...))	TFUNCTOR;

	// 1) Thread에서 실행할 Functor 생성~
	TFUNCTOR*	pfunctor = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...);

	// 2) Reference Count 증가.
	AddRef();

	try
	{
		// 3) Thread를 생성해서 대입한다.
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

	// 4) Thread ID를 Reset한다.
	m_statisticsThread.idThread = m_thread.native_handle();
}

#elif _MSC_VER>=_MSC_VER_2010
template<class TFN>
void CGAPI::CThread::Begin(TFN _Function)
{
	// Declare) 
	typedef	decltype(std::bind(_Function))	TFUNCTOR;

	// 1) Functor 생성
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function));

	// 2) Reference Count 증가.
	AddRef();

	try
	{
		// 3) thread 객체 저장을 위해 교환
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 3) Thread ID를 Reset한다.
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

		// - functor 지우기
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

	// 1) Functor 만들기
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function, p1));

	// 2) Reference Count 증가.
	AddRef();

	try
	{
		// 3) thread 객체 저장을 위해 교환
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 4) Thread ID를 Reset한다.
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

		// - functor 지우기
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

	// 1) Functor 만들기
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function, p1, p2));

	// 2) Reference Count 증가.
	AddRef();

	try
	{
		// 2) thread 객체 저장을 위해 교환
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 3) Thread ID를 Reset한다.
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

		// - functor 지우기
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

	// 1) Functor 만들기
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function, p1, p2, p3));

	// 2) Reference Count 증가.
	AddRef();

	try
	{
		// 2) thread 객체 저장을 위해 교환
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 3) Thread ID를 Reset한다.
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

		// - functor 지우기
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

	// 1) Functor 만들기
	TFUNCTOR*	pfunctor	 = new TFUNCTOR(std::bind(_Function, p1, p2, p3, p4));

	// 2) Reference Count 증가.
	AddRef();

	try
	{
		// 2) thread 객체 저장을 위해 교환
		m_thread	 = std::thread(fnProcessThread<TFUNCTOR>, this, pfunctor);

		// 3) Thread ID를 Reset한다.
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

		// - functor 지우기
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
