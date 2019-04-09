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

namespace CGNet
{
namespace IO
{
namespace Receivable
{
//-----------------------------------------------------------------------------
/**

@class		NStream
@brief 스트림(TCP)용 저수준 I/O Receive 처리 클래스

TCP와 같이 Stream으로 전달되어 오는 데이터의 Receive를 처리하는 class이다.
구현은 Pro-Actor패턴인 IOCP로 구현되어 있기 때문에 접속과 동시에 PrepareReceive()함수를 호출하여
Receive을 걸어놓는다.
Stream처리이기 때문에 동시에 한번의 Receive I/O만 걸어놓는다.
Receive 완료된 후 받은 Message를 완전히 다 처리한 후 다시 Receive를 걸도록 설계되었다.
이로 인해 대량의 데이터를 Receive할 경우 처리가 지연될 수 있다.
Receive의 완료가 0Byte 혹은 Error로 되면 접속 종료처리를 한다.

@todo
@ref		CGNet::IO::Receiveable::NStreamQueue, CGNet::IO::Receiveable::NStreamRIO 
@details	\n

*/
//-----------------------------------------------------------------------------
class NStream :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Socket
	virtual public				CGNet::IO::IReceivable,					//     Receivable
	virtual protected			CGNet::IO::IConnectable,				// (I) Connectable
	virtual protected			CGNet::IO::IPacketable					// (I) Packetable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NStream();
			~NStream()													{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief '수신 지연' 기능 사용 여부를 설정한다.
			void				EnableReceivePending(bool _bEnable=true){ m_bEnableReceivePending = _bEnable;}
	//! @brief '수신 지연' 기능 사용 여부를 끈다.
			void				DisableReceivePending()					{ EnableReceivePending(false); }
	//! @brief '수신 지연' 기능 상태를 얻는다. @return true '수신 지연 상태'
			bool				GetReceivePending() const				{ return m_bEnableReceivePending;}

	//! @brief '소켓별 최소 수신 버퍼'를 설정한다.
			size_t				SetMinMessageBufferSize(size_t _Size) noexcept;
			size_t				GetMinMessageBufferSize() noexcept;

			size_t				SetMaxMessageBufferSize(size_t _Size) noexcept;
			size_t				GetMaxMessageBufferSize() noexcept;


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	//! @brief 데이터를 수신 했을 때 호출되는 함수.
	virtual	void				OnReceive(_In_ const CGD::buffer& /*_rWSABuffer*/, _In_ size_t /*_Transferred*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief Receive를 거는 함수. @return true true 성공 @return true false 실패
			bool				Receive(_In_ CGD::buffer* _arrayBuffer);

	//! @brief Receivable을 초기화한다.
	virtual	void				ResetReceivable() override;
	//! @brief 최초 접속 시 Receive를 준비한다.
	virtual	bool				PrepareReceive() override;

	//! @brief Receive를 받았을 때 호출된다. @return 0 성공 @return !0 실패
	virtual	intptr_t			ProcessCompleteReceivable(_In_ intptr_t _Return, _In_ size_t _Param);

protected:
			size_t				m_sizeMinMessageBuffer;
			size_t				m_sizeMaxMessageBuffer;

			CCGBuffer			m_bufferReceived;		// 현재 Packet을 처리하기 위해 남은 잔량 Buffer...
			CGD::buffer			m_bufferReceiving;		// Receive를 걸어 놓은 Buffer...

			size_t				m_sizeBufferReceive;	// 수신 버퍼 크기
			bool				m_bEnableReceivePending;// 수신 지연 사용 여부

	// Declare) 
			class CGExecutableReceive : virtual public ICGExecutable
			{
			public:
				NStream*		m_pReceivable;
				virtual	intptr_t ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param);
			};

	//! @brief Receive를 처리할 ICGExecutable 객체
			CGPTR<CGExecutableReceive>	m_pexecutableReceive;
};

//! @brief '기본 수신 지연'를 설정한다. @param _bEnable 설정할 '기본 수신 지연' 상태
void	SetDefaultReceivePending(bool _bEnable);
//! @brief '기본 수신 지연'를 얻는다. @return '기본 수신 지연' 상태
bool	GetDefaultReceivePending();
//! @brief '기본 최소 메시지 버퍼 크기'를 설정한다. @param _bytesSize 설정할 '기본 최소 메시지 버퍼 크기'
void	SetDefaultMessageBufferMinSize(_In_ size_t _bytesSize);
//! @brief '기본 최대 메시지 버퍼 크기'를 설정한다. @param _bytesSize 설정할 '기본 최대 메시지 버퍼 크기'
void	SetDefaultMessageBufferMaxSize(_In_ size_t _bytesSize);
//! @brief '기본 메시지 버퍼 크기'를 설정한다. @param _bytesSizeMin 설정할 '기본 최소 메시지 버퍼 크기' @param _bytesSizeMax 설정할 '기본 최대 메시지 버퍼 크기'
void	SetDefaultMessageBufferSize(_In_ size_t _bytesSizeMin, _In_ size_t _bytesSizeMax);
//! @brief '기본 최소 메시지 버퍼 크기'를 얻는다. @return 설정된 '기본 최소 메시지 버퍼 크기'
size_t	GetDefaultMessageBufferMinSize();
//! @brief '기본 최대 메시지 버퍼 크기'를 얻는다. @return 설정된 '기본 최대 메시지 버퍼 크기'
size_t	GetDefaultMessageBufferMaxSize();

}
}
}