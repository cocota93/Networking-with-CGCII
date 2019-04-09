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
// CGStateable::CControl<TSTATE>
//
// 1. CGStateable::CControl<TSTATE>��?
//     �� Member�� Array���·� �����ϴ� Group System�̴�.
// 
//
//-----------------------------------------------------------------------------
namespace CGStateable
{

template <class _TSTATE>
class CControl : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						NControl<_TSTATE>,					// 
	public						CCGStateable<_TSTATE>				// 
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE				TSTATE;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CControl()			{}
			CControl(ICGStateTable<TSTATE>* p_pStateTable) : NControl<TSTATE>(p_pStateTable)	{}
	virtual	~CControl()			{}
};


}