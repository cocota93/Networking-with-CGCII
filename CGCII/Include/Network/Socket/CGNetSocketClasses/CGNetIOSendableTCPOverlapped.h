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
// CGNet::IO::Sendable::NTCPOverlapped
//
// 1. CGNet::IO::Sendable::NTCPOverlapped란!
//    1) TCP용 Send로 한번의 Send를 한번의 Overlapped I/O로 걸어서 수행하는 
//       Sendable이다.
//    2) 한번의 Send에 한번의 Overlapped I/O를 쓰기 때문에 구조가 간단하여 Send
//       빈도가 낮은 Socket에서는 좋은 성능을 낸다.
//    3) 하지만 Send의 빈도가 높은 Socket에서는 많은 I/O가 오히려 성능이 떨어질
//       수 있으므로 빈도가 높은 Send를 수행하는 Socket에서는 이 Sendable대신
//       Send Gathering을 수행하는 TCPGathering을 사용하도록 권한다.
//    4) 대부분의 Server Socket이나 Client Socket의 경우 이 간단한 Sendable로
//       충분하다.
//
// 2. CGNet::IO::Sendable::CTCP의 핵심! Function의 기능 설명
//    1) ProcessSend()		CCGBuffer를 전송한다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sendable
{

class NTCPOverlapped :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISendable,					//     Sendable
	virtual protected			CGNet::IO::IConnectable					// (I) Sendable
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