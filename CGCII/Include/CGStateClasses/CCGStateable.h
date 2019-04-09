//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               State Classes                               *
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
// CGFSM::CManager
//
// 1. CGFSM::CManager란?
//     각 Member를 Array형태로 관리하는 Group System이다.
// 
//
//-----------------------------------------------------------------------------
template <class _TSTATE>
class CCGStateable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGStateable<_TSTATE>
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	typename ICGStateable<_TSTATE>::TSTATE		TSTATE;


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) State를 조작하는 함수.
	virtual	CGPTR<TSTATE>		GetState()								{ LOCK(ICGStateable<_TSTATE>::m_csState) return m_pstateCurrent; }
	virtual	bool				SetState(_In_ TSTATE* _pStateNew=nullptr);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Current State
			CGPTR<TSTATE>		 m_pstateCurrent;
};

template <class _TSTATE>
inline bool CCGStateable<_TSTATE>::SetState(_In_ TSTATE* _pStateNew)
{
	LOCK(ICGStateable<_TSTATE>::m_csState)
	{
		// Check) 같은 State면 그냥 false를 리턴한다.
		RETURN_IF(_pStateNew==m_pstateCurrent, false);

		// 1) 기존 State를 Leave한다.
#if defined(_MSC_VER)
		__if_exists(TSTATE::ProcessStateLeave)
		{
#endif
			if(m_pstateCurrent.exist())
			{
				m_pstateCurrent->ProcessStateLeave();
			}
#if defined(_MSC_VER)
		}
#endif

		// 2) State 설정
		m_pstateCurrent	 = _pStateNew;

		// Check) 새로운 State가 nullptr이면 그냥 끝낸다.
		RETURN_IF(_pStateNew==nullptr, false);

		// 3) 새로 설정된 State의 ProcessStateEnter호출
#if defined(_MSC_VER)
		__if_exists(TSTATE::ProcessStateEnter)
		{
#endif
			_pStateNew->ProcessStateEnter();
#if defined(_MSC_VER)
		}
#endif
	}

	// Return) 
	return	true;
}
