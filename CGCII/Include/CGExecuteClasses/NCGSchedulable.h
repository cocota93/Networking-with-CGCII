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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
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
	//! @brief '실행 간격'을 얻는다. @return 설정된 '실행 간격'
			TICK::duration		GetExecuteInterval() const				{ return m_tickdiffExecute; }
	//! @brief '실행 간격'을 설정한다. @param _tickInterval '실행 간격'
			void				SetExecuteInterval(_In_ TICK::duration _tickInterval)	{ m_tickdiffExecute=_tickInterval; m_tickNext=TICK::now()+m_tickdiffExecute;}
	//! @brief '다음 실행 시간'을 얻는다. @return 다음 실행 시간
			TICK::time_point	GetNextTick() const						{ return m_tickNext; }


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 3) Interval과 Next
			TICK::time_point	m_tickNext;
			TICK::duration		m_tickdiffExecute;							// Update를 진행하는 Gap
};
