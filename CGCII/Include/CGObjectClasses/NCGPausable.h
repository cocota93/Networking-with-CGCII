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

 @class		NCGPausable
 @brief		ICGPausable을 구현한 클래스
 @todo		
 @ref		
 @details	\n

 */
//-----------------------------------------------------------------------------
class NCGPausable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGPausable,
	virtual	public				ICGObjectState
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 정지한다. @return true 성공 @return false 실패
	virtual	bool				Pause() override;
	//! @brief 재개한다. @return true 성공 @return false 실패
	virtual	bool				Continue() override;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 잠시 중단되기 전 호출된다.(OnContinue()함수와 짝함수다.)
	virtual	void				OnPausing()							{}
	//! @brief 잠시 중단될 때 호출된다.(OnContinuing()함수와 짝함수다.)
	virtual	void				OnPause()							{}

	//! @brief 다시 시작 되기 전호출된다.(OnDestroying()함수와 짝함수다.)
	virtual	void				OnContinuing()						{}
	//! @brief 다시시작할 때 호출된다.(OnPausing()함수와 짝함수다.)
	virtual	void				OnContinue()						{}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
public:
	//! @brief 잠시 중지할 때 처리해야할 내용을 정의한다. @param _Msg 전달할 인자
	virtual	void				ProcessPause();
	//! @brief 중지를 해제할 때 처리해야할 내용을 정의한다.
	virtual	void				ProcessContinue();
};
