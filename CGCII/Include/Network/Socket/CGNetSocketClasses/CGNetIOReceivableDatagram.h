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
/*!
* @class NDatagram
*
* @ingroup CGNet::IO::Receivable
*
* @brief Datagram(UDP)의 저수준 수신을 처리하는 클래스
*
*   UDP용 Receive 처리를 정의한 클래스이다. 
*   UDP용 Receive는 순서를 고려하지 않고 하나의 Socket이 여러 개의 Peer로부터 
*   전송을 받기 때문에 최대한 빠르게 다시 Receive를 받을 수 있도록 설계되었으며
*   동시에 여러 개의 Receive를 요청해 놓는다.
*   저수준 I/O 장치나 API 혹은 처리 방법에 따라 달라질수 있다.
*
*   Receive를 받게될 Buffer의 크기를 적절하게 설정해 주어야한다.
*   만약 Receive한 Buffer보다 더 큰 Packet이 전달되어 올 경우 Lost되기 때문이다.
*   Receive할 버퍼의 크기를 설정할 경우 반드시 Bind하기 전에 해주어야 한다.
*   SetReceiveBufferSize()함수를 사용하여 Receive할 버퍼의 크기를 설정할 수 있다.
*   (Default는 SIZE_OF_RECEIVE_BUFFER)
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Receivable
{

class NDatagram : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Socket
	virtual	public				CGNet::IO::IReceivable,					//     Receivable
	virtual protected			CGNet::IO::IPacketable,					// (I) Packetable
	virtual public				CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NDatagram();
			~NDatagram()												{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			size_t				GetMessageSize() const					{	return m_iReceiveBufferSize;}
			void				SetPacketSize(_In_ size_t p_dwReceiveBufferSize);

			size_t				GetPrepareReceiveCount() const			{	return m_iPrepareReceiveCount;}
			void				SetPrepareReceiveCount(_In_ size_t p_dwCount);

	virtual	void				SuspendReceive();
	virtual	void				ResumeReceive();


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) Receive에 성공했을 때 호출되는 함수.
	virtual	void				OnReceive(_In_ const CGD::buffer& /*_rWSABuffer*/, _In_ size_t /*_Transferred*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/) {}

	// 2) 실패했을 때 호출되는 Hook함수.
	virtual void				OnFailReceive(_In_ int /*p_ErrorCode*/, _In_ const CGD::buffer& /*_rWSABuffer*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/) {}

	// 3) Overlapped로 걸어 놓은 ReceiveReceive가 0개가 되었을 때 호출되는 함수.
	virtual	void				OnReceiveExhausted() {}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) ProcessCompleteReceive()의 재정의. 
	virtual	void				ProcessCompleteReceive(_In_ uintptr_t _Return, _In_ size_t _Transfered, _In_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr);

	// 2) Reset할때 호출하는 함수.(특별히 수행할 것이 없으므로 빈것임.)
	virtual	void				ResetReceivable() override				{}
	 
	// 3) Prepare Receive
	virtual	bool				PrepareReceive() override;

			class				CExecutableReceive;

private:
			size_t				m_iReceiveBufferSize;
			size_t				m_iPrepareReceiveCount;
};


}
}
}