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
namespace CGExecutor
{

//-----------------------------------------------------------------------------
/**

 @class		CCompletionPort
 @brief		IOCP를 사용한 쓰레드풀을 구성한 Executor이다.
 @todo		
 @ref		
 @details	\n
 @remark	\n
 IOCP에 Socket을 붙이거나 IO를 Post하는 용도로 주로 사용된다.
 이 IOCP Completion Port는 상속을 하여 Thread용으로 사용되기도 하지만 주로 .
 Client IOCP에 많이 사용된다. MainLoop와 동일한 Thread에서 사용하기 위해
 Execut()함수를 TimeOut을 0으로 절어줘서 사용한다.

*///-----------------------------------------------------------------------------
class CCompletionPort :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor,							//     Executor Interface
	public						CGNameable::NString,					// (@) Nameable
	public						CGAPI::CIOCompletionPort				// (@) CompletionPort
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCompletionPort();
	//! @brief 생성자 (이름을 설정한다.) @param _strName '객체 이름'
			CCompletionPort(_In_ const _CHAR* _strName);
	//! @brief 생성자 (이름을 설정한다.) @param _strName '객체 이름'
			CCompletionPort(_In_ const _CHAR_SUB* _strName);
	virtual	~CCompletionPort();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Start/Stop function
	//! @brief 전달 인자 없이 시작한다. @return true 성공 @return false 실패
			bool				Start() { CGMSG_CONTEXT msg; return Start(msg);}
	//! @brief '실행자'를 연다. @param _Msg 값을 전달할 메시지 @return true 성공 @return false 실패
	virtual bool				Start(CGMSG_CONTEXT& _Msg) override;
	//!	@brief '실행자'를 닫는다. @return true 성공 @return false 실패
	virtual	bool				Stop() override;

	// 2) Post함수임.
	//! @brief '실행 객체'의 실행을 요청한다. @param _pExecutable 실행할 '실행 객체' @param _Para 실행시 넘길 인자 @return true 성공 @return false 실패
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0) override;

	// 3) Execute함수임...
	//! @brief 실행을 처리하는 함수 @param _tickdiff 최대 실행 대기 시간(이 시간 내에 처리가 되지 않으면 TIME_OUT으로 리턴한다.) @return	true 성공 @return false 실패
	virtual	bool				Execute(_In_ TICK::duration _tickMilliseconds=TICK::milliseconds(INFINITE)) override;

	//! @brief 큐잉된 '실행 객체'를 모두 실행한다.
			void				ExecuteAllQueued();
};

}