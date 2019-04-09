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
//-----------------------------------------------------------------------------
/*!
* @class NDatagram
*
* @ingroup CGNet::IO::Receivable
*
* @brief Datagram(UDP)�� ������ ������ ó���ϴ� Ŭ����
*
*   UDP�� Receive ó���� ������ Ŭ�����̴�. 
*   UDP�� Receive�� ������ ������� �ʰ� �ϳ��� Socket�� ���� ���� Peer�κ��� 
*   ������ �ޱ� ������ �ִ��� ������ �ٽ� Receive�� ���� �� �ֵ��� ����Ǿ�����
*   ���ÿ� ���� ���� Receive�� ��û�� ���´�.
*   ������ I/O ��ġ�� API Ȥ�� ó�� ����� ���� �޶����� �ִ�.
*
*   Receive�� �ްԵ� Buffer�� ũ�⸦ �����ϰ� ������ �־���Ѵ�.
*   ���� Receive�� Buffer���� �� ū Packet�� ���޵Ǿ� �� ��� Lost�Ǳ� �����̴�.
*   Receive�� ������ ũ�⸦ ������ ��� �ݵ�� Bind�ϱ� ���� ���־�� �Ѵ�.
*   SetReceiveBufferSize()�Լ��� ����Ͽ� Receive�� ������ ũ�⸦ ������ �� �ִ�.
*   (Default�� SIZE_OF_RECEIVE_BUFFER)
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
	virtual public				CGNet::IO::Statistics::NSocket			// (@) ���
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
	// 1) Receive�� �������� �� ȣ��Ǵ� �Լ�.
	virtual	void				OnReceive(_In_ const CGD::buffer& /*_rWSABuffer*/, _In_ size_t /*_Transferred*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/) {}

	// 2) �������� �� ȣ��Ǵ� Hook�Լ�.
	virtual void				OnFailReceive(_In_ int /*p_ErrorCode*/, _In_ const CGD::buffer& /*_rWSABuffer*/, _In_opt_ const SOCKADDR_CGNETWORK* /*_pSockAddr*/) {}

	// 3) Overlapped�� �ɾ� ���� ReceiveReceive�� 0���� �Ǿ��� �� ȣ��Ǵ� �Լ�.
	virtual	void				OnReceiveExhausted() {}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) ProcessCompleteReceive()�� ������. 
	virtual	void				ProcessCompleteReceive(_In_ uintptr_t _Return, _In_ size_t _Transfered, _In_ CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr);

	// 2) Reset�Ҷ� ȣ���ϴ� �Լ�.(Ư���� ������ ���� �����Ƿ� �����.)
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