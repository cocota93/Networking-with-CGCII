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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
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
@brief ��Ʈ��(TCP)�� ������ I/O Receive ó�� Ŭ����

TCP�� ���� Stream���� ���޵Ǿ� ���� �������� Receive�� ó���ϴ� class�̴�.
������ Pro-Actor������ IOCP�� �����Ǿ� �ֱ� ������ ���Ӱ� ���ÿ� PrepareReceive()�Լ��� ȣ���Ͽ�
Receive�� �ɾ���´�.
Streamó���̱� ������ ���ÿ� �ѹ��� Receive I/O�� �ɾ���´�.
Receive �Ϸ�� �� ���� Message�� ������ �� ó���� �� �ٽ� Receive�� �ɵ��� ����Ǿ���.
�̷� ���� �뷮�� �����͸� Receive�� ��� ó���� ������ �� �ִ�.
Receive�� �Ϸᰡ 0Byte Ȥ�� Error�� �Ǹ� ���� ����ó���� �Ѵ�.

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
	//! @brief '���� ����' ��� ��� ���θ� �����Ѵ�.
			void				EnableReceivePending(bool _bEnable=true){ m_bEnableReceivePending = _bEnable;}
	//! @brief '���� ����' ��� ��� ���θ� ����.
			void				DisableReceivePending()					{ EnableReceivePending(false); }
	//! @brief '���� ����' ��� ���¸� ��´�. @return true '���� ���� ����'
			bool				GetReceivePending() const				{ return m_bEnableReceivePending;}

	//! @brief '���Ϻ� �ּ� ���� ����'�� �����Ѵ�.
			size_t				SetMinMessageBufferSize(size_t _Size) noexcept;
			size_t				GetMinMessageBufferSize() noexcept;

			size_t				SetMaxMessageBufferSize(size_t _Size) noexcept;
			size_t				GetMaxMessageBufferSize() noexcept;


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	//! @brief �����͸� ���� ���� �� ȣ��Ǵ� �Լ�.
	virtual	void				OnReceive(_In_ const CGD::buffer& /*_rWSABuffer*/, _In_ size_t /*_Transferred*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief Receive�� �Ŵ� �Լ�. @return true true ���� @return true false ����
			bool				Receive(_In_ CGD::buffer* _arrayBuffer);

	//! @brief Receivable�� �ʱ�ȭ�Ѵ�.
	virtual	void				ResetReceivable() override;
	//! @brief ���� ���� �� Receive�� �غ��Ѵ�.
	virtual	bool				PrepareReceive() override;

	//! @brief Receive�� �޾��� �� ȣ��ȴ�. @return 0 ���� @return !0 ����
	virtual	intptr_t			ProcessCompleteReceivable(_In_ intptr_t _Return, _In_ size_t _Param);

protected:
			size_t				m_sizeMinMessageBuffer;
			size_t				m_sizeMaxMessageBuffer;

			CCGBuffer			m_bufferReceived;		// ���� Packet�� ó���ϱ� ���� ���� �ܷ� Buffer...
			CGD::buffer			m_bufferReceiving;		// Receive�� �ɾ� ���� Buffer...

			size_t				m_sizeBufferReceive;	// ���� ���� ũ��
			bool				m_bEnableReceivePending;// ���� ���� ��� ����

	// Declare) 
			class CGExecutableReceive : virtual public ICGExecutable
			{
			public:
				NStream*		m_pReceivable;
				virtual	intptr_t ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param);
			};

	//! @brief Receive�� ó���� ICGExecutable ��ü
			CGPTR<CGExecutableReceive>	m_pexecutableReceive;
};

//! @brief '�⺻ ���� ����'�� �����Ѵ�. @param _bEnable ������ '�⺻ ���� ����' ����
void	SetDefaultReceivePending(bool _bEnable);
//! @brief '�⺻ ���� ����'�� ��´�. @return '�⺻ ���� ����' ����
bool	GetDefaultReceivePending();
//! @brief '�⺻ �ּ� �޽��� ���� ũ��'�� �����Ѵ�. @param _bytesSize ������ '�⺻ �ּ� �޽��� ���� ũ��'
void	SetDefaultMessageBufferMinSize(_In_ size_t _bytesSize);
//! @brief '�⺻ �ִ� �޽��� ���� ũ��'�� �����Ѵ�. @param _bytesSize ������ '�⺻ �ִ� �޽��� ���� ũ��'
void	SetDefaultMessageBufferMaxSize(_In_ size_t _bytesSize);
//! @brief '�⺻ �޽��� ���� ũ��'�� �����Ѵ�. @param _bytesSizeMin ������ '�⺻ �ּ� �޽��� ���� ũ��' @param _bytesSizeMax ������ '�⺻ �ִ� �޽��� ���� ũ��'
void	SetDefaultMessageBufferSize(_In_ size_t _bytesSizeMin, _In_ size_t _bytesSizeMax);
//! @brief '�⺻ �ּ� �޽��� ���� ũ��'�� ��´�. @return ������ '�⺻ �ּ� �޽��� ���� ũ��'
size_t	GetDefaultMessageBufferMinSize();
//! @brief '�⺻ �ִ� �޽��� ���� ũ��'�� ��´�. @return ������ '�⺻ �ִ� �޽��� ���� ũ��'
size_t	GetDefaultMessageBufferMaxSize();

}
}
}