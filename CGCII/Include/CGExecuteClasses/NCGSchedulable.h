//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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
/**

 @class		NCGSchedulable
 @brief		
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
class NCGSchedulable :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
		virtual public			ICGSchedulable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NCGSchedulable(_In_ TICK::duration _tickdifferExecute=TICK::seconds(1))		{ SetExecuteInterval(_tickdifferExecute);}
	virtual	~NCGSchedulable()											{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief '���� ����'�� ��´�. @return ������ '���� ����'
			TICK::duration		GetExecuteInterval() const				{ return m_tickdiffExecute; }
	//! @brief '���� ����'�� �����Ѵ�. @param _tickInterval '���� ����'
			void				SetExecuteInterval(_In_ TICK::duration _tickInterval)	{ m_tickdiffExecute=_tickInterval; m_tickNext=TICK::now()+m_tickdiffExecute;}
	//! @brief '���� ���� �ð�'�� ��´�. @return ���� ���� �ð�
			TICK::time_point	GetNextTick() const						{ return m_tickNext; }


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 3) Interval�� Next
			TICK::time_point	m_tickNext;
			TICK::duration		m_tickdiffExecute;							// Update�� �����ϴ� Gap
};
