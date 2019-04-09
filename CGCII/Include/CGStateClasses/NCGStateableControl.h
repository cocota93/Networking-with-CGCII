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
// CGStateable::NControl<_TSTATE>
//
// 1. CGStateable::NControl<_TSTATE>란?
//     각 Member를 Array형태로 관리하는 Group System이다.
// 
//
//-----------------------------------------------------------------------------
namespace CGStateable
{

template <class _TSTATE>
class NControl : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGStateableControl<_TSTATE>					// 
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE				TSTATE;
	typedef	typename ICGStateableControl<TSTATE>::TSTATE_ID	TSTATE_ID;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NControl()			{}
			NControl(ICGStateTable<TSTATE>* p_pStateTable)			{	SetStateTable(p_pStateTable);}
	virtual	~NControl()			{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) State를 조작하는 함수.
	virtual	bool				ChangeState(_In_ const TSTATE_ID& p_ridState);
	virtual	bool				ResetState();

	// 2) State Manager
			void				SetStateTable(ICGStateTable<TSTATE>* p_pTable);
			CGPTR<ICGStateTable<TSTATE>> GetStateTable() const			{	LOCK(ICGStateable<TSTATE>::m_csState) return m_pStateTable; }

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) State Table
			CGPTR<ICGStateTable<TSTATE>>	m_pStateTable;
};

template <class _TSTATE>
bool NControl<_TSTATE>::ChangeState(_In_ const TSTATE_ID& p_ridState)
{
	LOCK(ICGStateable<TSTATE>::m_csState)
	{
		// Check) 
		CGASSERT_ERROR(m_pStateTable.exist());

		// Check) State Table이 없으면 Exception을 던진다.
		ERROR_THROW_IF(m_pStateTable.empty(), CGException::CThrow_NoInitialized(), );

		// 1) 새로운 State를 먼저 찾는다.
		CGPTR<TSTATE>	pstateNew	 = m_pStateTable->FindState(p_ridState);

		// 2) State를 설정한다.
		return	this->SetState(pstateNew);
	}
}

template <class _TSTATE>
bool NControl<_TSTATE>::ResetState()
{
	LOCK(ICGStateable<TSTATE>::m_csState)
	{
		// Check) 
		CGASSERT_ERROR(m_pStateTable.exist());

		// Check) State Table이 없으면 Exception을 던진다.
		ERROR_THROW_IF(m_pStateTable.empty(), CGException::CThrow_NoInitialized(), );

		// 1) Initial State로 설정한다.
		return	this->SetState(m_pStateTable->GetInitialState());
	}
}

template <class _TSTATE>
void NControl<_TSTATE>::SetStateTable(ICGStateTable<TSTATE>* p_pTable)
{
	LOCK(ICGStateable<TSTATE>::m_csState)
	{
		m_pStateTable	 = p_pTable;
	}
}


}