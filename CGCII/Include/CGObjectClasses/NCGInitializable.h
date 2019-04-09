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

 @class		NCGInitializable
 @brief		ICGInitializable을 구현한 클래스
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class NCGInitializable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				ICGObjectState,
	virtual public				ICGInitializable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual ~NCGInitializable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 전달 인자 없이 초기화를 실행한다. @return true 성공 @return false 실패
			bool				Initialize() { CGMSG_CONTEXT tempMSG; return Initialize(tempMSG); }
	//! @brief 초기화한다. @param _Msg 초기화 할때 전달될 메시지@return true 성공 @return false 실패
	virtual	bool				Initialize(CGMSG_CONTEXT& _Msg) override;
	//! @brief 파괴한다. @return true 성공 @return false 실패
	virtual	bool				Destroy() override;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief 초기화되기 전 호출된다.(OnDestroy()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnInitializing(CGMSG_CONTEXT& /*_Msg*/)			{}
	//! @brief 초기화될 때 호출된다.(OnDestroying()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnInitialize(CGMSG_CONTEXT& /*_Msg*/)			{}

	//! @brief 파괴되기 전 호출된다.(OnInitialize()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnDestroying()							{}
	//! @brief 파괴될 때 호출된다.(OnInitializing()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnDestroy()								{}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	//! @brief 초기화 절차를 정의한다. @param _MSg 초기활 할 때 전달된 메시지
	virtual	void				ProcessInitialize(CGMSG_CONTEXT& _Msg);
	//! @brief 파괴 절차를 정의한다.
	virtual	void				ProcessDestroy();

	//! @brief 자식 노드의 초기화 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessInitializing(CGMSG_CONTEXT& _Msg){ OnInitializing(_Msg);}
	//! @brief 자식 노드의 초기화 처리가 진행된 후 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessInitialize(CGMSG_CONTEXT& _Msg)	{ OnInitialize(_Msg);}
	//! @brief 자식 노드의 파괴 처리가 진행되기 전 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessDestroying()					{ OnDestroying();}
	//! @brief 자식 노드의 파괴 처리가 진행된 후 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessDestroy()						{ OnDestroy();}
};
