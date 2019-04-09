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
// CGD::slimlock
//
// 1. slimlock��~
//    
//    1) Windows�� SRW(Slip Read/Write) Lock �ѹ� ������ class�̴�.
//    2) Slip�� ���� ���� ���� Shared Lock�� ����ϰ� ������ Exclusive Lock��
//       �ٿ��Ͽ� ���� Read�� ���� ���������� ���� ���� �� �ִ�.
//    3) Slip Lock�� Critical section���� �ξ� ������ ���� �뷮�� �����Ѵ�.
//       (���� Pointer ���� �ϳ���ŭ�� �뷮���� �����Ѵ�.)
//    4) ������ �� ������ Critical Section�� ���ó���� ���� ���� ���� �� ����
//       ���Ǹ� ��￩�� �Ѵ�.
//
// 2. ���
//    1) ���� �� ���� execlusive lock�� ����Ѵ�.
//    2) ���� ���� ���� shared lock�� ����Ѵ�.
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
