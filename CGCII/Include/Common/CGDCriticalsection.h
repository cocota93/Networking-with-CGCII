//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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
// CGD::lockable
//
// 1. lockable은~
//    
//    1) 
//    2) 
//
//-----------------------------------------------------------------------------
namespace CGD
{

//-----------------------------------------------------------------------------
/**

 @class		lockable
 @brief		크리티컬 섹션 클래스
 @todo		
 @ref		
 @details	\n
 가벼운 동기화 객체인 크리티컬 섹션 혹은 std:recursive_mutex를 포장한 클래스이다.

*///-----------------------------------------------------------------------------
class lockable
{
// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:
#if defined(_MSC_VER) && defined(_USE_NATIVE_LOCK)
// Use Windows native lock
	typedef	CRITICAL_SECTION	TLOCK;
	#define						_INIT(cs)								bool bResult = InitializeCriticalSectionAndSpinCount(&cs, 4000) != FALSE; ERROR_THROW_IF(bResult == false, std::bad_alloc(), );
	#define						_DESTORY(cs)							RETURN_IF(m_lock.LockCount == 0, ); DeleteCriticalSection(&cs);
	#define						_LOCK_P(pcs)							EnterCriticalSection(pcs);
	#define						_LOCK(cs)								_LOCK_P(&cs);
	#define						_TRY_LOCK_P(pcs)						return TryEnterCriticalSection(pcs) != 0;
	#define						_TRY_LOCK(cs)							_TRY_LOCK_P(&cs);
	#define						_UNLOCK_P(pcs)							LeaveCriticalSection(pcs);
	#define						_UNLOCK(cs)								_UNLOCK_P(&cs);

#elif defined(_USE_NATIVE_LOCK)
// Use LINUX native lock
	typedef	pthread_mutex_t		TLOCK;
	#define						_INIT(cs)								cs = PTHREAD_RECURSIVE_MUTEX_INITIALIZER; return true;
	#define						_DESTORY(cs)
	#define						_LOCK_P(pcs)							pthread_mutex_lock(cs);
	#define						_LOCK(cs)								_LOCK_P(&cs);
	#define						_TRY_LOCK_P(pcs)						return pthread_mutex_trylock(pcs) == 0;
	#define						_TRY_LOCK(cs)							_TRY_LOCK_P(&cs);
	#define						_UNLOCK_P(pcs)							pthread_mutex_unlock(pcs);
	#define						_UNLOCK(cs)								_UNLOCK_P(&cs);

#else
// Use C++ Standard lock
	typedef	std::recursive_mutex TLOCK;
	#define						_INIT(cs)
	#define						_DESTORY(cs)
	#define						_LOCK_P(pcs)							pcs->lock();
	#define						_LOCK(cs)								cs.lock();
	#define						_TRY_LOCK_P(pcs)						return pcs->try_lock();
	#define						_TRY_LOCK(cs)							return cs.try_lock();
	#define						_UNLOCK_P(pcs)							pcs->unlock();
	#define						_UNLOCK(cs)								cs.unlock();
#endif


// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			lockable()													{ _INIT(m_lock) }
			~lockable()													{ _DESTORY(m_lock) }


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief 블락킹 락을 한다. @param _pExecutable 등록할 '실행 객체' @return true 성공 @return false 실패 (이미 등록된 객체일 경우 발생한다.)
			void				lock() const							{ _LOCK(m_lock) }
	static	void				lock(TLOCK* _lock)						{ _LOCK_P(_lock) }
	//! @brief 논블락킹 락을 시도한다. @return true 락에 성공 @return false 락에 실패 @details  락을 시도 후 락 걸기에 성공하면 락을 걸고 true를 리턴하며 실패하면 바로 false를 리턴한다.
			bool				try_lock() const						{ _TRY_LOCK(m_lock) }
	static	bool				try_lock(TLOCK* _lock)					{ _TRY_LOCK_P(_lock) }
	//! @brief 락을 푼다.
			void				unlock() const							{ _UNLOCK(m_lock) }
	static	void				unlock(TLOCK* _lock)					{ _UNLOCK_P(_lock) }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			lockable&			operator=(lockable&& ) _DELETE;
			void				operator=(lockable& ) _DELETE

public:
	// 1) Critical Section
	mutable TLOCK				m_lock;

	// Undef)
	#undef						_INIT
	#undef						_DESTORY
	#undef						_LOCK_P
	#undef						_LOCK
	#undef						_TRY_LOCK_P
	#undef						_TRY_LOCK
	#undef						_UNLOCK_P
	#undef						_UNLOCK
};


}


//-----------------------------------------------------------------------------
/**

 @class		LOCKABLE
 @brief		범위 락 클래스
 @todo		
 @ref		
 @details	\n
 가벼운 동기화 객체인 크리티컬 섹션 혹은 std:recursive_mutex를 포장한 클래스이다.

*///-----------------------------------------------------------------------------
template <class TOBJECT=void>
class LOCKABLE : public TOBJECT, public CGD::lockable
{
public:
#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
	template<class... TARGS>
	LOCKABLE(TARGS&&... _Arguments) : TOBJECT(_Arguments...) {}
#elif _MSC_VER>=_MSC_VER_2010
	LOCKABLE() {}

	template <typename TA>
	LOCKABLE(TA a) : TOBJECT(a) {}

	template <typename TA, typename TB>
	LOCKABLE(TA a, TB b) : TOBJECT(a, b) {}

	template <typename TA, typename TB, typename TC>
	LOCKABLE(TA a, TB b, TC c) : TOBJECT(a, b, c) {}

	template <typename TA, typename TB, typename TC, typename TD>
	LOCKABLE(TA a, TB b, TC c, TD d) : TOBJECT(a, b, c, d) {}

	template <typename TA, typename TB, typename TC, typename TD, typename TE>
	LOCKABLE(TA a, TB b, TC c, TD d, TE e) : TOBJECT(a, b, c, d, e) {}
#else
	#error	"CGCommon: Unsupported compiler"
#endif
public:
	template <class TDATA>
			TOBJECT&			operator=( const TDATA& _rData )		{	*(TOBJECT*)this=_rData; return *this;}
};

template<>
class LOCKABLE<void> : public CGD::lockable
{
};
