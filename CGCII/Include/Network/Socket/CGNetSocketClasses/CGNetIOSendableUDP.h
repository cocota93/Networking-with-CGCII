//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Network Socket Classes                           *
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
//
// CGNet::IO::Sender::NUDP
//
// 1. CGNet::IO::Sendable::CUDP란!
//    1) 가장 일반적인 UDP용 Sendable이다.
//    2) 가장 기본적인 SendTo()함수만 수행한다.
//    3) Send가 완료되면 ProcessCompleteSendable()함수가 호출된다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sendable
{

//-----------------------------------------------------------------------------
/**

 @class		NUDP
 @brief		비동기 전송을 하는 UDP Sendable 클래스
 @todo		
 @ref		
 @details	\n

 비동기 전송을 수행하는 UDP Sendable 클래스이다.
 Overlapped를 사용해 전송을 수행한다.
*/
//-----------------------------------------------------------------------------
class NUDP : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Socket.
	virtual public				CGNet::IO::ISendable,					//     Sendable.
	virtual public				CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
protected:
	//! @brief 전송 처리 과정을 정의하는 함수. @param _pSendCompletor 완료후 호출된 함수 객체 @param _arrayBuffer 전송할 버퍼 배열 @param _countBuffer 버퍼의 개수 @param _pOriginal 전송중 참조계수를 유지할 객체 전송중일 때에는 참조계수가 1 증가하며 전송이 완료되면 1 감소시킨다. @param _pSockAddress 전송할 주소(UDP전용)  @return true 성공  @return false 실패
	virtual	bool				ProcessSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override;

	//! @brief 전송이 완료되었을 때 처리를 정의하는 함수. @param _pSendCompletor 완료후 호출된 함수 객체 @param _Return 전송 결과 @param _Transfered 전송된 바이트 수
	virtual	void				ProcessCompleteSendable(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_ uintptr_t _Return, _In_ size_t _Transfered) override;

	//! @brief 초기화 될 때 호출되는 함수.
	virtual	void				ResetSendable() override;
};


}
}
}