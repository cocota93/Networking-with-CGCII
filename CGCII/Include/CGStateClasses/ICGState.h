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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGFSM::IState
//
// 1. CGFSM::IState¶õ!
//    1) 
//    2) 
//
//-----------------------------------------------------------------------------
template <class _TSTATE_ID=_STRING>
class ICGState :
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (I) Reference Counter.
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE_ID			TSTATE_ID;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGState()													{}
			ICGState(_In_ const TSTATE_ID& _idState) : m_idState(_idState)	{}
	virtual	~ICGState()													{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) State ID
			const TSTATE_ID&	GetStateID() const						{	return m_idState;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	virtual	void				ProcessStateEnter()						{}
	virtual	void				ProcessStateLeave()						{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			bool	operator!=(const ICGState<TSTATE_ID>& rhs) const	{ return m_idState!=rhs.m_idState;}
			bool	operator==(const ICGState<TSTATE_ID>& rhs) const	{ return m_idState==rhs.m_idState;}
			bool	operator< (const ICGState<TSTATE_ID>& rhs) const	{ return m_idState< rhs.m_idState;}
			bool	operator<=(const ICGState<TSTATE_ID>& rhs) const	{ return m_idState<=rhs.m_idState;}
			bool	operator> (const ICGState<TSTATE_ID>& rhs) const	{ return m_idState> rhs.m_idState;}
			bool	operator>=(const ICGState<TSTATE_ID>& rhs) const	{ return m_idState>=rhs.m_idState;}
private:
	// 1) State ID
			TSTATE_ID			m_idState;
};
