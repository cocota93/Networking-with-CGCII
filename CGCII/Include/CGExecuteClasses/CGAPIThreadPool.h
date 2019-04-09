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

//-----------------------------------------------------------------------------
/**

 @class		CThreadPool
 @brief		쓰레드풀 클래스이다.
 @todo		
 @ref		
 @details	\n
 단지 하나의 함수를 여러 Thread로 수행하도록 하는 class이다.
 Thread에서 실행해야 되는 내용은 ThreadRun()함수를 재정의함으로써 설정
 한다.
 CreateThread를 통해 생성된 Thread는 ThreadRon()함수를 호출한다.
 CreateThread함수가 호출되면 OnThreadStart()함수가 호출되고 종료될때
 OnThreadTerminate()함수가 호출된다.
 IOCP를 사용한 Network I/O가 이것으로 제작되었다.

*///-----------------------------------------------------------------------------
class CThreadPool : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CThreadPool();
	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
	//! @brief 생성과 동시에 쓰레드풀을 시작한다. @param _Function 실행할 함수 @param _Arguments 실행시 전달될 인자들
			template<class TFN, class... TARGS>
			CThreadPool(typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, TFN>::type&& _Function, TARGS&&... _Arguments) : m_countThreadExist(0) { Begin(std::forward<TFN>(_Function), std::forward<TARGS>(_Arguments)...);}
	//! @brief 생성과 동시에 쓰레드풀을 시작한다. @param _iCount 생성할 쓰레드 수 @param _Function 실행할 함수 @param _Arguments 실행시 전달될 인자들
			template<class TFN, class... TARGS>
			CThreadPool(int _iCount, TFN&& _Function, TARGS&&... _Arguments) : m_countThreadExist(0) { Begin(_iCount, std::forward<TFN>(_Function), std::forward<TARGS>(_Arguments)...); }

	#elif _MSC_VER>=_MSC_VER_2010
	//! @brief 생성과 동시에 쓰레드풀을 시작한다. @param _Function 실행할 함수 @param _Arguments 실행시 전달될 인자들
			template<class TFN>
			CThreadPool(TFN&& _Function)								{	Begin(std::forward<TFN>(_Function));}
			template<class TFN, class TPARAM1>
			CThreadPool(typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, TFN>::type&& _Function, TPARAM1&& p1)					{	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1));}
			template<class TFN, class TPARAM1, class TPARAM2>
			CThreadPool(typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, TFN>::type&& _Function, TPARAM1&& p1, TPARAM2&& p2)	{	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));}
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			CThreadPool(typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, TFN>::type&& _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM2&& p3){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));}

	//! @brief 생성과 동시에 쓰레드풀을 시작한다. @param _iCount 생성할 쓰레드 수 @param _Function 실행할 함수 @param _Arguments 실행시 전달될 인자들
			template<class TFN>
			CThreadPool(int _iCount, TFN&& _Function)					{	Begin(_iCount, std::forward<TFN>(_Function));}
			template<class TFN, class TPARAM1>
			CThreadPool(int _iCount, TFN&& _Function, TPARAM1&& p1)		{	Begin(_iCount, std::forward<TFN>(_Function), std::forward<TPARAM1>(p1));}
			template<class TFN, class TPARAM1, class TPARAM2>
			CThreadPool(int _iCount, TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2){	Begin(_iCount, std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));}
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			CThreadPool(int _iCount, TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3){	Begin(std::forward<TFN>(_Function), _Function, std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));}
	#else
		#error	"CGExecute: Unsupported compiler"
	#endif
	virtual	~CThreadPool();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Threa의 시작/중지관련
	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
	//! @brief 쓰레드를 시작한다. @param _pFunction 실행할 함수 @param _Arguments 실행시 전달될 인자
			template<class TFN, class... TARGS>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN&& _Function, TARGS&&... _Arguments);
	//! @brief 쓰레드를 시작한다. @param _iCount 생성할 쓰레드 수 @param _Function 실행할 함수 @param _Arguments 실행시 전달될 인자
			template<class TFN, class... TARGS>
			void				Begin(int _iCount, TFN&& _Function, TARGS&&... _Arguments);
	#elif _MSC_VER>=_MSC_VER_2010
	//! @brief 쓰레드를 시작한다. @param _pFunction 실행할 함수
			template<class TFN>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN _Function);
			template<class TFN, class TPARAM1>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN _Function, TPARAM1&& p1);
			template<class TFN, class TPARAM1, class TPARAM2>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2);
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3);
			
	//! @brief 쓰레드를 시작한다. @param _iCount 생성할 쓰레드 수 @param _Function 실행할 함수
			template<class TFN>
			void				Begin(int _iCount, TFN&& _Function)	{ for(int i=0; i<_iCount; ++i){	Begin(std::forward<TFN>(_Function));}}
			template<class TFN, class TPARAM1>
			void				Begin(int _iCount, TFN&& _Function, TPARAM1&& p1) {	for(int i=0; i<_iCount; ++i){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1));}}
			template<class TFN, class TPARAM1, class TPARAM2>
			void				Begin(int _iCount, TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2){ for(int i=0; i<_iCount; ++i){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));}}
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			void				Begin(int _iCount, TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3){	for(int i=0; i<_iCount; ++i){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));}}
	#else
		#error	"CGExecute: Unsupported compiler"
	#endif
	//! @brief 모든 쓰레드를 모두 강제종료한다.
			void				TerminateAll();

	// 2) Thread 상태
	//! @brief 쓰레드의 갯수를 얻는다. @return 쓰레드 갯수
			int					GetExistThreadCount() const				{	return m_countThreadExist;}
	//! @brief 쓰레드의 갯수가 0개인가? @return true 0개다. false 0개가 아니다.
			bool				empty() const							{	return GetExistThreadCount()==0;}
	//! @brief 쓰레드의 갯수가 0개가 아닌가? @return true 0개가 아니다. false 0개다.
			bool				exist() const							{	return GetExistThreadCount()!=0;}
			
	// Definitions)
	typedef	vector<CGPTR<CThread>>::iterator		ITERATOR;
	typedef	vector<CGPTR<CThread>>::const_iterator	CONST_ITERATOR;

	// 3) Iterator
	//! @brief 락 객체를 얻는다.
								operator lockable&()					{	return m_vectorThread;}
	//! @brief 정방향 반복자 처음 쓰레드를 얻는다. @return '처음 반복자'
			ITERATOR			begin()									{	return m_vectorThread.begin();}
	//! @brief 정방향 반복자 처음 쓰레드를 얻는다. @return '처음 반복자'
			CONST_ITERATOR		begin() const							{	return m_vectorThread.begin();}
	//! @brief 정방향 반복자 끝 쓰레드를 얻는다. @return '끝 반복자'
			ITERATOR			end()									{	return m_vectorThread.end();}
	//! @brief 정방향 반복자 끝 쓰레드를 얻는다. @return '끝 쓰레드 반복자'
			CONST_ITERATOR		end() const								{	return m_vectorThread.end();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	//! @brief 쓰레드 함수
	template <class TTYPE>
	static	void				fnProcessThreadPool(CGAPI::CThreadPool* _pPool, CGAPI::CThread* _pThread, TTYPE* _pFunctor);

	//! @brief 쓰레드 시작 시 처리를 정의한 함수
			void				ProcessBeginThreadObject(CThread* _pThread);
	//! @brief 쓰레드 종료 시 처리를 정의한 함수
			void				ProcessEndThreadObject(CThread* _pThread);
private:
			LOCKABLE<vector<CGPTR<CThread>>>	m_vectorThread;
			ATOMIC<int>			m_countThreadExist;
};


template <class TTYPE>
void CGAPI::CThreadPool::fnProcessThreadPool(CGAPI::CThreadPool* _pPool, CGAPI::CThread* _pThread, TTYPE* _pFunctor)
{
	// 1) Hold
	CGPTR<CGAPI::CThread>		pThread	 = _pThread;
	CGPTR<CGAPI::CThreadPool>	pPool	 = _pPool;

	// 2) Functor 호출전 사전처리
	pPool->ProcessBeginThreadObject(pThread);

	// 3) Functor를 호출한다.
	try
	{
		(*_pFunctor)();
	}
	catch (...)
	{
	}

	// 5) Functor를 지운다.
	delete _pFunctor;

	// 4) Functor 호출후 사전처리
	pPool->ProcessEndThreadObject(pThread);
}

#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
template<class TFN, class... TARGS>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN&& _Function, TARGS&&... _Arguments)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024] = { 0 };

	// 1) Nameable을 얻는다.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) 이름을 작성~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread 시작
	LOCK(m_vectorThread)
	{
		// - Thread에서 실행할 Functor 생성~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...);

		// - Thread를 생성한다.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - 이름을 설정한다.
		pThread->SetName(tempString);

		// - Thread List에 추가한다.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread를 시작한다.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Thread List에서 제거한다.
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise)
			throw;
		}

	}
}

template<class TFN, class... TARGS>
void CGAPI::CThreadPool::Begin(int _iCount, TFN&& _Function, TARGS&&... _Arguments)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...))	TFUNCTOR;

	// 1) Nameable을 얻는다.
	ICGNameable*	pNameable	 = dynamic_cast<ICGNameable*>(this);

	// 2) iCount수만큼 Thread 시작
	LOCK(m_vectorThread)
	{
		for (int i=0; i<_iCount; ++i)
		{
			// - Thread에서 실행할 Functor 생성~
			TFUNCTOR*	pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...);

			// - Thread를 생성한다.
			CGPTR<CThread>	pThread = NEW<CThread>();

			// Declare)
			_CHAR	tempString[1024] = { 0 };

			// - 이름을 작성~
			CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable!=nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

			// - 이름을 설정한다.
			pThread->SetName(tempString);

			// - thread를 넣는다.
			m_vectorThread.push_back(pThread);

			// - AddRef
			AddRef();

			try
			{
				// - Thread를 시작한다.
				pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
			}
			catch(...)
			{
				// - Release
				NO_EXCEPTION_BEGIN
				{
					Release();
				}
				NO_EXCEPTION_END

				// - Thread List에서 제거한다.
				NO_EXCEPTION_BEGIN
				{
					m_vectorThread.pop_back();
				}
				NO_EXCEPTION_END

				// Reraise)
				throw;
			}
		}
	}
}
#elif _MSC_VER>=_MSC_VER_2010
template<class TFN>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN _Function)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function))))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024]{};
	
	// 1) Nameable을 얻는다.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) 이름을 작성~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread 시작
	LOCK(m_vectorThread)
	{
		// - Thread에서 실행할 Functor 생성~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)));

		// - Thread를 생성한다.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - 이름을 설정한다.
		pThread->SetName(tempString);

		// - thread를 넣는다.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread를 시작한다.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Popback
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
}

template<class TFN, class TPARAM1>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN _Function, TPARAM1&& p1)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1)))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024] = { 0 };

	// 1) Nameable을 얻는다.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) 이름을 작성~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread 시작
	LOCK(m_vectorThread)
	{
		// - Thread에서 실행할 Functor 생성~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1));

		// - Thread를 생성한다.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - 이름을 설정한다.
		pThread->SetName(tempString);

		// - thread를 넣는다.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread를 시작한다.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Popback
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
}

template<class TFN, class TPARAM1, class TPARAM2>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2)))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024] = { 0 };

	// 1) Nameable을 얻는다.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) 이름을 작성~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread 시작
	LOCK(m_vectorThread)
	{
		// - Thread에서 실행할 Functor 생성~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));

		// - Thread를 생성한다.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - 이름을 설정한다.
		pThread->SetName(tempString);

		// - thread를 넣는다.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread를 시작한다.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Popback
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
}

template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2)))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024] = { 0 };

	// 1) Nameable을 얻는다.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) 이름을 작성~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread 시작
	LOCK(m_vectorThread)
	{
		// - Thread에서 실행할 Functor 생성~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));

		// - Thread를 생성한다.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - 이름을 설정한다.
		pThread->SetName(tempString);

		// - thread를 넣는다.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread를 시작한다.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Popback
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
}
#else
		#error	"CGExecute: Unsupported compiler"
#endif


}
