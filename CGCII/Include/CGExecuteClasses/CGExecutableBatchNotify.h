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

namespace CGExecutable
{

//-----------------------------------------------------------------------------
/**

 @class		CBatchNotify
 @brief		여러 개의 Executable 객체를 실행하기 위한 클래스로 완료 시 특정 메시지를 전달해 준다.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TMESSAGE>
class CBatchNotify :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NBatch
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CBatchNotify()												{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_NOTIFY);}
	virtual ~CBatchNotify()												{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief '완료 후 전송할 메시지'와 '완료 후 수신할 객체'를 설정한다. @param _Msg '완료 후 송신할 메시지' @param _pTarget '완료 후 메시지를 수신할 객체'
			void				SetMessage(_In_ const TMESSAGE& _Msg, _In_ ICGMessageable* _pTarget) {	SetMessage(_Msg); SetTarget(_pTarget);}
	//! @brief '완료 후 전송할 메시지'를 설정한다. @param _Msg 완료 후 송신할 메시지
			void				SetMessage(_In_ const TMESSAGE& _Msg) {	m_Message=_Msg;}
	//! @brief 설정된 '완료 후 전송할 메시지'를 얻는다. @return 설정된 '완료 후 전송할 메시지'
			const TMESSAGE&		GetMessage() const						{	return m_Message;}
	//! @brief '완료 후 메시지를 수신할 객체'를 설정한다. @param _pTarget '완료 후 메시지를 수신할 객체'
			void				SetTarget(_In_ ICGMessageable* _pTarget){	m_pTarget=_pTarget;}
	//! @brief 설정된 '완료 후 메시지를 수신할 객체'를 얻는다. @return '완료 후 메시지를 수신할 객체'
			CGPTR<ICGMessageable> GetTarget() const						{	return m_pTarget;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessCompleteExecution
	virtual	void				ProcessCompleteExecution() override		{	m_pTarget->RequestProcessMessage(m_Message);}

	// 2) Message
			CGPTR<ICGMessageable> m_pTarget;
			TMESSAGE			m_Message;
};


}
