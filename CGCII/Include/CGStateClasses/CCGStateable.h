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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGFSM::CManager
//
// 1. CGFSM::CManager��?
//     �� Member�� Array���·� �����ϴ� Group System�̴�.
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
	// 1) State�� �����ϴ� �Լ�.
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
		// Check) ���� State�� �׳� false�� �����Ѵ�.
		RETURN_IF(_pStateNew==m_pstateCurrent, false);

		// 1) ���� State�� Leave�Ѵ�.
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

		// 2) State ����
		m_pstateCurrent	 = _pStateNew;

		// Check) ���ο� State�� nullptr�̸� �׳� ������.
		RETURN_IF(_pStateNew==nullptr, false);

		// 3) ���� ������ State�� ProcessStateEnterȣ��
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
