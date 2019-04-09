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

 @class		NCGStartable
 @brief		ICGStartable을 구현한 클래스
 @todo		
 @ref		
 @details	\n

 */
//-----------------------------------------------------------------------------
class NCGStartable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGStartable,
	virtual	public				ICGObjectState
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 전달 인자 없이 시작한다. @return true 성공 @return false 실패
			bool				Start() { CGMSG_CONTEXT tempMSG; return Start(tempMSG); }
	//! @brief 시작한다. @param _pMSG 시작시 전달할 인자 @return true 성공 @return false 실패
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override;
	//! @brief 중지한다. @return true 성공 @return false 실패
	virtual	bool				Stop() override;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 초기화되기 전 호출된다.(OnDestroy()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStarting(CGMSG_CONTEXT& /*_Msg*/)	{}
	//! @brief 초기화될 때 호출된다.(OnDestroying()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStart(CGMSG_CONTEXT& /*_Msg*/)	{}

	//! @brief 파괴되기 전 호출된다.(OnInitialize()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStopping()						{}
	//! @brief 파괴될 때 호출된다.(OnInitializing()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStop()							{}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	//! @brief 시작시 처리해야할 내용을 정의한다. @param _Msg 시작시 전달할 인자
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg);
	//! @brief 중지시 처리해야할 내용을 정의한다.
	virtual	void				ProcessStop();

	//! @brief 자식 노드의 시작 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg){ OnStarting(_Msg); }
	//! @brief 자식 노드의 시작 처리가 진행된 후 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessStart(CGMSG_CONTEXT& _Msg)	{ OnStart(_Msg); }
	//! @brief 자식 노드의 종료 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessStopping()					{ try{OnStopping();}catch(...){}}
	//! @brief 자식 노드의 종료 처리가 진행된 후 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessStop()						{ try{OnStop();}catch(...){} }
};
