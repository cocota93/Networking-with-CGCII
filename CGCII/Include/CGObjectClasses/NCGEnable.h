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
/**

@class		NCGEnable
@brief		가능/불가능 속성을 가진 인터페이스 클래스
@todo		
@ref		ICGReferenceable
@details	\n

*/
//-----------------------------------------------------------------------------
class NCGEnable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGEnable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NCGEnable(bool _bState=false) : m_bState(_bState)			{}
	virtual	~NCGEnable()	{}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	void				OnEanble(bool _bState)					{}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
protected:
	//! @brief 가능/불가능 상태의 설정 처리를 정의한다. @param _bState 설정할 State @return 이전 설정 상태
	virtual	bool				ProcessSetEnable(bool _bState)	{	auto bOld=m_bState.exchange(_bState); if(bOld!=_bState) OnEanble(_bState); return bOld;}

	//! @brief 현재의 가능/불가능 상태의 설정을 정의한다. @return 현재의 가능/불가능 설정상태
	virtual	bool				ProcessGetEnable()				{	return m_bState.load();}

private:
			ATOMIC<bool>		m_bState;
};
