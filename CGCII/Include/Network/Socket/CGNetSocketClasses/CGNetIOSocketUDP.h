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
//
// CGNet::IO::Socket::NUDP
//
// 1. CGNet::IO::Socket::NUDP�� Ư¡!
//    1) UDP������ ���۵� Socket�̴�.
//    2) UDP������ ���� �����̳� �ɼ��� �⺻������ ����ȴ�.
//    3) UDP�� Send/Receive ���� ũ�⸦ �Ʒ��� ���� �����ϰ� ���� �� �ִ�.
//
//    4) Socket�� Send Buffer�� Receive Buffer�� ���Ϻ��� ������ �� ������
//       Ư���� �������� ������ �⺻���� ������ ���� �Ʒ��� �����Լ��� ������
//       ���� �ִ�.
//       
//       static void	SetDefaultSendBufferSize(int _iSize);
//       static int		GetDefaultSendBufferSize() const;
//
//       static void	SetDefaultReceiveBufferSize(int _iSize);
//       static int		GetDefaultReceiveBufferSize() const;
//
//       ������ �����Ǹ� �ϴ� Default������ �����Ǹ� ���Ϻ��� ������ �� ���
//       ���� ���� ������ �־�� �Ѵ�.
//
//    5) �Ϲ������� ������ Send�� Receive ���۸� ũ�� �ϸ� Traffic�� ���� ����
//       �� �� ���� ������ �������ش�. ������ �׸�ŭ �뷮�� ���� �����ϹǷ� 
//       ������ �����ؾ� �Ѵ�.
//       
//    6) ConnectReset�� �뺸 ���� ����.
//       - UDP�� ��� ConnectReset�� �߿��ϴ�. SendTo�� �������� �� Ư�� 
//         Address�� �����Ҽ� ���� ��Ȳ�� �� SendTo�� ����� �뺸���ִ� ���� 
//         �ƴ϶� Receive���� CONNECT_RESET Error�� �߻���Ų��. 
//       - �� CONNECT_RESET�� ��� UDP������ ���������� Error�� �ƴ�����
//         �߿��� ������ �ɼ� �ִ�.
//         ���� �� CONNECT_RESET ��ȣ�� ���� ������ ���� ���� ��������
//         �����Ҽ� �ִ�.
//       - �Ϲ������� ���� Server�� Client�� ���۽�ų�� �� Option�� 
//         ���ְ� ������ Reliable�� ���۽�Ű�� UDP Socket�� ���� ��� �� 
//         �ɼ��� ���ش�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Socket
{

class NUDP :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NBase									// (@) IOCP Socket
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NUDP(_In_ bool p_bReportConnectReset=false);
			~NUDP();

// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) UDP �⺻ Send/Receive Buffer�� �����Ѵ�.
	static	void				SetDefaultSendBufferSize(_In_ size_t _iSize) NOEXCEPT{	m_iDefaultSendBufferSize=_iSize;}
	static	size_t				GetDefaultSendBufferSize() NOEXCEPT			{	return m_iDefaultSendBufferSize;}

	static	void				SetDefaultReceiveBufferSize(_In_ size_t _iSize) NOEXCEPT{	m_bytesDefaultReceiveBufferSize=_iSize;}
	static	size_t				GetDefaultReceiveBufferSize() NOEXCEPT		{	return m_bytesDefaultReceiveBufferSize;}

	// 2) Address
	virtual	SOCKADDR_CGNETWORK	GetPeerAddress() const NOEXCEPT				{	return m_addrPeer;}
	virtual	bool				SetPeerAddress(const SOCKADDR_CGNETWORK& _addrSocket) NOEXCEPT { m_addrPeer = _addrSocket; return true; }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Socket�� Reset�ϰų� CloseSocket�� ���� ������ ������ �Լ�.
	//    (�ʿ��� ��� �������Ҽ� �ִ�.)
	virtual	void				ProcessCreateSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) override;
	virtual	bool				ProcessCloseSocket(uint32_t _Reason=SOCKET_REASON_NONE) override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Connect Reset�� �� ���ΰ� �ƴѰ��� �����ϴ� ������.
			bool				m_bReportConnectReset;	// UDP ConnectReset Report����

	// 2) UDP Socket�� �� �⺻ ����Ǵ� Default Send/Receive Buffer ũ��
	static	size_t				m_iDefaultSendBufferSize;
	static	size_t				m_bytesDefaultReceiveBufferSize;

	// 3) 
			SOCKADDR_CGNETWORK	m_addrPeer;
};


}
}
}