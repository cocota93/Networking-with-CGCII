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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// 
// CGD::lock_guard
// 
// 1. CGD::lock_guard��..
//    1) Critical section ��ü�� Set�ϰ� �Ǹ� �ڵ����� EnterCriticalsection��
//       �����Ѵ�.
//    2) ��ü�� �ı��Ǹ� �ڵ����� LeaveCriticalsection�� �����Ѵ�.
//    3) �ı��Ǳ� ������ Release()�� �����ϰ� �Ǹ� ��ü�� �����ϸ鼭 Leave-
//       Criticalsection�� �����Ѵ�.
//    4) �� ��ü�� ������ �� �ݵ�� Critical section ��ü�� �����ؾ� �մϴ�.
//       (�߰��� ��ü�� ������ ���� �� �����ϴ�.)
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
				// Check) m_pcsLock�� nullptr�̸� �ȵȴ�.
				CGASSERT_ERROR(m_pcsLock!=nullptr);

				return	m_pcsLock!=nullptr;
			}
};

}


// ----------------------------------------------------------------------------
// 1) Critical Section Lock
//    - �̰��� ������ Block�� �̿��ؼ� ������ ������ ��� ��� �ڵ�����
//      CriticalSection�� ����� �ϰ� �ϱ� ���� ���̴�.
// 
// ----------------------------------------------------------------------------
#define	LOCK_BEGIN(cs)				{	CGD::lock_guard	_UNIQUE_TEMPORARY_NAME(_tempCSLock)(cs);
#define	LOCK_BEGIN_NAMED(cs, name)	{	CGD::lock_guard	name(cs);
#define	LOCK_LEAVE(name)			name.release();
#define	LOCK_END					}
#define	LOCK(cs)					if(CGD::lock_guard _UNIQUE_TEMPORARY_NAME(_tempCSLock)=cs) throw std::exception(); else
#define	LOCK_NAMED(cs, name)		if(CGD::lock_guard name=cs) throw std::exception(); else
#define	SYNCHRONIZED(cs)			LOCK(cs)