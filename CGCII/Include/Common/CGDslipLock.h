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
// CGD::slimlock
//
// 1. slimlock은~
//    
//    1) Windows의 SRW(Slip Read/Write) Lock 한번 포장한 class이다.
//    2) Slip은 값을 읽을 때는 Shared Lock을 사용하고 쓸때는 Exclusive Lock을
//       다용하여 다중 Read로 인한 병목현상을 대폭 줄일 수 있다.
//    3) Slip Lock은 Critical section보다 훨씬 가볍고 적은 용량을 차지한다.
//       (단지 Pointer 변수 하나만큼의 용량만을 차지한다.)
//    4) 하지만 이 때문에 Critical Section의 재귀처리는 하지 못해 사용상 더 많은
//       주의를 기울여야 한다.
//
// 2. 사용
//    1) 값을 쓸 때는 execlusive lock을 사용한다.
//    2) 값을 읽을 때는 shared lock을 사용한다.
//
//
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
namespace CGD
{

class slimlock
{
// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			slimlock()													{	InitializeSRWLock(&m_sliplock);}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			void				acquire_execlusive()					{	AcquireSRWLockExclusive(&m_sliplock);}
			void				release_execlusive()					{	ReleaseSRWLockExclusive(&m_sliplock);}
			bool				try_execlusive()						{	return TryAcquireSRWLockExclusive(&m_sliplock)!=0;}

			void				acquire_shared()						{	AcquireSRWLockShared(&m_sliplock);}
			void				release_shared()						{	ReleaseSRWLockShared(&m_sliplock);}
			bool				try_shared()							{	return TryAcquireSRWLockShared(&m_sliplock)!=0;}

			PSRWLOCK			get_slimlock()							{	return &m_sliplock;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			SRWLOCK				m_sliplock;
};


}
#endif
