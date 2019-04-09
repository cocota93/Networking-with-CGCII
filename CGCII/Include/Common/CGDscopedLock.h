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
// CGD::lock_guard
// 
// 1. CGD::lock_guard란..
//    1) Critical section 객체를 Set하게 되면 자동으로 EnterCriticalsection을
//       수행한다.
//    2) 객체가 파괴되면 자동으로 LeaveCriticalsection을 수행한다.
//    3) 파괴되기 이전에 Release()를 수행하게 되면 객체를 해제하면서 Leave-
//       Criticalsection을 수행한다.
//    4) 단 객체를 생성할 때 반드시 Critical section 객체를 설정해야 합니다.
//       (중간에 객체를 설정해 놓을 수 없습니다.)
//     
//
//-----------------------------------------------------------------------------
namespace CGD
{


class lock_guard
{
// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			lock_guard(const CGD::lockable* cs) : m_pcsLock(&cs->m_lock){	CHECK_VALID(); CGD::lockable::lock(m_pcsLock);}
			lock_guard(const CGD::lockable& cs) : m_pcsLock(&cs.m_lock)	{	CHECK_VALID(); CGD::lockable::lock(m_pcsLock);}
			~lock_guard()												{	release();}

			
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			void				release()								{	if(m_pcsLock==nullptr) return; CGD::lockable::unlock(m_pcsLock); m_pcsLock=nullptr;}

								operator bool() const					{	return !CHECK_VALID();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			CGD::lockable::TLOCK*	m_pcsLock;

	// Check) 
			bool				CHECK_VALID() const
			{
				// Check) m_pcsLock이 nullptr이면 안된다.
				CGASSERT_ERROR(m_pcsLock!=nullptr);

				return	m_pcsLock!=nullptr;
			}
};

}


// ----------------------------------------------------------------------------
// 1) Critical Section Lock
//    - 이것은 지정된 Block을 이용해서 지정된 영역을 벗어날 경우 자동으로
//      CriticalSection을 벗어나게 하게 하기 위한 것이다.
// 
// ----------------------------------------------------------------------------
#define	LOCK_BEGIN(cs)				{	CGD::lock_guard	_UNIQUE_TEMPORARY_NAME(_tempCSLock)(cs);
#define	LOCK_BEGIN_NAMED(cs, name)	{	CGD::lock_guard	name(cs);
#define	LOCK_LEAVE(name)			name.release();
#define	LOCK_END					}
#define	LOCK(cs)					if(CGD::lock_guard _UNIQUE_TEMPORARY_NAME(_tempCSLock)=cs) throw std::exception(); else
#define	LOCK_NAMED(cs, name)		if(CGD::lock_guard name=cs) throw std::exception(); else
#define	SYNCHRONIZED(cs)			LOCK(cs)