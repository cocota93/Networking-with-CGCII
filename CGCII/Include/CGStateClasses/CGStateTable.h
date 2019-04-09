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
// CGState::CManager
//
// 1. CGState::CManager��?
//    ��ϵ� State�� ���̸� 
// 
// 2. ����
//    ũ�� State�� � State���� � Event������ � State�� �����ϴ°��� ������
//    ��� �ִ� Transition Table�� �����Ǿ� �ִ�.
// 
//
//-----------------------------------------------------------------------------
namespace CGStateTable
{

template <class _TSTATE>
class CSimple : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGStateTable<_TSTATE>					//     Group Base
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE				TSTATE;
	typedef	typename ICGStateTable<TSTATE>::TSTATE_ID	TSTATE_ID;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CSimple()	{}
	virtual	~CSimple()	{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) State�� �����ϴ� �Լ�.
	virtual	bool				RegisterState(_In_ TSTATE* p_pState, bool p_bIsInitial=false);
	virtual	CGPTR<TSTATE>		UnregisterState(_In_ const TSTATE_ID& p_rStateID);
	virtual	CGPTR<TSTATE>		FindState(_In_ const TSTATE_ID& p_rStateID);
	virtual	CGPTR<TSTATE>		GetInitialState();

			void				SetInitialStateID(_In_ const TSTATE_ID& p_rStateID);
			const TSTATE_ID&	GetInitialStateID() const				{	LOCK(m_mapTable) return m_idInitialState; }


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Current State
			LOCKABLE<std::map<TSTATE_ID, CGPTR<TSTATE>>>	m_mapTable;
			TSTATE_ID			m_idInitialState;
};

template <class _TSTATE>
bool CSimple<_TSTATE>::RegisterState(_In_ TSTATE* p_pState, bool p_bIsInitial)
{
	// Check) 
	CGASSERT_ERROR(p_pState!=nullptr);

	// Check) 
	RETURN_IF(p_pState==nullptr, false);
	

	LOCK(m_mapTable)
	{
		// 1) State ID����´�.
		const TSTATE_ID& ridState	 = p_pState->GetStateID();

		// 2) ���� Key�� �ִ��� ã�´�.
		auto	iterFind	 = m_mapTable.find(ridState);

		// Check) �̹� �����ϸ� Exception�� ������. �������� ����!
		ERROR_THROW_IF(iterFind!=m_mapTable.end(), CGException::CThrow_InvalidArgument(), );

		// 3) Initial�� ������ true�� Initial State�� �����Ѵ�.
		if(p_bIsInitial==true)
		{
			SetInitialStateID(ridState);
		}

		// 3) �߰��Ѵ�.
		m_mapTable.insert(std::make_pair(ridState, p_pState));
	}

	// Return) 
	return	true;
}

template <class _TSTATE>
CGPTR<typename CSimple<_TSTATE>::TSTATE> CSimple<_TSTATE>::UnregisterState(_In_ const TSTATE_ID& p_rStateID)
{
	LOCK(m_mapTable)
	{
		// 1) ���� Key�� �ִ��� ã�´�.
		auto	iterFind	 = m_mapTable.find(p_rStateID);

		// Check) �̹� �����ϸ� Exception�� ������. �������� ����!
		RETURN_IF(iterFind==m_mapTable.end(), CGPTR<TSTATE>());

		// Declare)
		CGPTR<TSTATE>	pSource	 = iterFind->second;

		// 2) �����Ѵ�.
		m_mapTable.erase(iterFind);

		// Return) 
		return	pSource;
	}
}

template <class _TSTATE>
CGPTR<typename CSimple<_TSTATE>::TSTATE> CSimple<_TSTATE>::FindState(_In_ const TSTATE_ID& p_rStateID)
{
	LOCK(m_mapTable)
	{
		// 1) ã��
		auto	iterFind	 = m_mapTable.find(p_rStateID);

		// Check) ã�� �������� nullptr�� �ǵ�����.
		RETURN_IF(iterFind==m_mapTable.end(), CGPTR<TSTATE>());

		// Return) ã�� State �ǵ����ֱ�.
		return	iterFind->second;
	}
}

template <class _TSTATE>
CGPTR<typename CSimple<_TSTATE>::TSTATE> CSimple<_TSTATE>::GetInitialState()
{
	return	FindState(m_idInitialState);
}

template <class _TSTATE>
void CSimple<_TSTATE>::SetInitialStateID(_In_ const TSTATE_ID& p_rStateID)
{
	LOCK(m_mapTable)
	{
		m_idInitialState	 = p_rStateID;
	}
}


}