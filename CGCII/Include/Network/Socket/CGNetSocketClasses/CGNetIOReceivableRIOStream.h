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
* @class NStreamRIO
*
* @ingroup CGNet::IO::Receivable
*
* @brief Registered I/O로 구현된 Receive Receiveable 클래스
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Receivable
{

class NStreamRIO :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Socket
	virtual public				CGNet::IO::IReceivable,					//     Receivable
	virtual protected			CGNet::IO::IConnectable,				// (I) Connectable
	virtual protected			CGNet::IO::IPacketable,					// (I) Packetable
	protected					ICGExecutable							// [E] Execute Executable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NStreamRIO();
			~NStreamRIO()												{}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) 일반적인 On함수.
	virtual	void				OnReceive(_In_ const CGD::buffer& /*_rWSABuffer*/, _In_ size_t /*_Transferred*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Buffers
			CCGBuffer			m_bufferReceived;	// 처리되지 않은 데이터 버퍼
			CGD::buffer			m_bufferReceiving;	// Receive를 걸어 놓은 버퍼

	// 2) RIO Buffers
			RIO_BUF				m_bufferRIOReceiving;

	// 3) RIO Request/Completion Queue
			RIO_RQ				m_queueRequest;
			RIO_CQ				m_queueCompletion;
protected:
	// 4) Reset할때 호출하는 함수.
	virtual	void				ResetReceivable() override;

	// 5) Prepare Receive
	virtual	bool				PrepareReceive() override;

			void				InitRIO();

private:
	// 5) Completion 되었을 때 수행되는 함수.
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


}
}
}