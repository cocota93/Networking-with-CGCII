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
// CGNet::IO::Sendable::NProxy
//
// 1. CGNet::IO::CSendable::NProxy은~
//     Sendable을 포인터로 가지고 있으며 ProcessReqestSend()함수를 호출하게 되면
//    포인터로 지적된 함수의 ProcessSend()함수를 호출한다.
//
//    1) 이 Sendalble이 직접 전송능력은 없다.
//    2) 그 대신 다른 Sendable을 포인팅해 있다가 ProcessSend()로 전송을 요구하면
//       포인팅한 Sendable의 ProcessSend()를 호출해 준다.
//    3) 즉 기생적인 성격의 Sendable이다.
//    4) 주로 Peer 제작에 많이 사용된다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sendable
{

class NProxy : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISendable					//     Sendable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NProxy(_In_ ISendable* _pSendable = nullptr) : m_pSendable(_pSendable)	{}
			~NProxy()													{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief '전달할 ISendable 객체'를 설정한다. @param _pSendable ISendable 객체 @return true 성공  @return false 실패
			void				SetSendable(_In_ ISendable* _pSendable){ m_pSendable = _pSendable; }
	//! @brief 설정된 '전달할 ISendable 객체'를 얻는다. @return 설정된 '전달할 ISendable 객체'
			ISendable*			GetSendable() const						{	 return m_pSendable;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief 전송 처리 과정을 정의하는 함수. @param _pSendCompletor 완료후 호출된 함수 객체 @param _arrayBuffer 전송할 버퍼 배열 @param _countBuffer 버퍼의 개수 @param _pOriginal 전송중 참조계수를 유지할 객체 전송중일 때에는 참조계수가 1 증가하며 전송이 완료되면 1 감소시킨다. @param _pSockAddress 전송할 주소(UDP전용)  @return true 성공  @return false 실패
	virtual	bool				ProcessSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override;

	//! @brief 전송이 완료되었을 때 처리를 정의하는 함수. @param _pSendCompletor 완료후 호출된 함수 객체 @param _Return 전송 결과 @param _Transfered 전송된 바이트 수
	virtual	void				ProcessCompleteSendable(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_ uintptr_t _Return, _In_ size_t _Transfered) override;

	//! @brief 초기화 될 때 호출되는 함수.
	virtual	void				ResetSendable() override;

protected:
			ISendable*			m_pSendable;
};


}
}
}