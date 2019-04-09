//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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

 @class		NCGObjectState
 @brief		ICGObjectState를 구현한 클래스
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class NCGObjectState : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGObjectState
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NCGObjectState() : m_stateObject(eOBJECT_STATE::NONE)			{}
			NCGObjectState(_In_ eOBJECT_STATE _State) : m_stateObject(_State) {}
	virtual	~NCGObjectState()												{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief 현재 객체 상태를 얻는다. @return true 현재 객체 상태
	virtual	eOBJECT_STATE		GetObjectState() const override				{	return m_stateObject;}
	//! @brief 현재 객체 상태를 설정한다. @param _State 설정하고자 하는 '객체 상태' @return 이전의 '객체 상태'
	virtual	eOBJECT_STATE		SetObjectState(_In_ eOBJECT_STATE _State) NOEXCEPT  override  	{	eOBJECT_STATE statusPre=m_stateObject.exchange(_State); if(statusPre!=_State) ProcessStateChanged(_State); return statusPre;}
	//! @brief 현재 상태가 _StateCompare일 경우 _State로 변경한다. @param _StateCompare 비교할 객체 상태 @ param _State 변경할 객체 상태 @return true 변경 성공 @return false 변경 실패
	virtual	bool				SetObjectStateIf(_In_ eOBJECT_STATE _StateCompare, _In_ eOBJECT_STATE _State) NOEXCEPT override	{	bool bChanged=m_stateObject.compare_exchange_weak(_StateCompare, _State); if(bChanged) ProcessStateChanged(_State); return bChanged;}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	//! @brief 상태가 변경되었을 때 호출된다. @param _State 변경된 상태
	virtual	void				ProcessStateChanged(_In_ eOBJECT_STATE /*_State*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			ATOMIC<eOBJECT_STATE>	m_stateObject;
};
