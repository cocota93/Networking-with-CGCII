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
// CGNet::IO::Socket::NTCP
//
// 1. CGNet::IO::Socket::NTCP�� Ư¡!
//    1) TCP������ ���۵� Socket Class�̴�.
//    2) Socket�� �����ϰ� �Ҹ��ϴ� ����� ������ �ִ�.
//    3) Socket�� Send Buffer�� Receive Buffer�� ���Ϻ��� ������ �� ������
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
//    4) �Ϲ������� ������ Send�� Receive ���۸� ũ�� �ϸ� Traffic�� ���� ����
//       �� �� ���� ������ �������ش�. ������ �׸�ŭ �뷮�� ���� �����ϹǷ� 
//       ������ �����ؾ� �Ѵ�.
//        
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Socket
{

class NTCP :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NBase									// (@) Socket Base
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NTCP(uint32_t _Flag=WSA_FLAG_OVERLAPPED);
			~NTCP();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) UDP �⺻ Send/Receive Buffer�� �����Ѵ�.
	static	void				SetDefaultSendBufferSize(_In_ size_t _iSize){	m_iDefaultSendBufferSize=_iSize;}
	static	size_t				GetDefaultSendBufferSize()					{	return m_iDefaultSendBufferSize;}

	static	void				SetMaxSendBufferSize(_In_ size_t _iSize)	{	m_iMaxSendBufferSize=_iSize;}
	static	size_t				GetMaxSendBufferSize()						{	return m_iMaxSendBufferSize;}

	static	void				SetDefaultReceiveBufferSize(_In_ size_t _iSize){	m_bytesDefaultReceiveBufferSize=_iSize;}
	static	size_t				GetDefaultReceiveBufferSize()				{	return m_bytesDefaultReceiveBufferSize;}

	static	void				SetMaxReceiveBufferSize(_In_ size_t _iSize)	{	m_bytesMaxReceiveBufferSize=_iSize;}
	static	size_t				GetMaxReceiveBufferSize()					{	return m_bytesMaxReceiveBufferSize;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			uint32_t			m_Flag;

protected:
	// 1) Socket�� Reset�ϰų� CloseSocket�Ҷ��� ������ ������ �Լ�.
	//    (�ʿ��� ��� �������Ҽ� �ִ�.)
	virtual	void				ProcessCreateSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) override;
	virtual	bool				ProcessCloseSocket(uint32_t _dwReason=SOCKET_REASON_NONE) override;

	// 3) TCP Socket�� �� �⺻ ����Ǵ� Default Send/Receive Buffer ũ��
	static	size_t				m_iDefaultSendBufferSize;
	static	size_t				m_iMaxSendBufferSize;

	static	size_t				m_bytesDefaultReceiveBufferSize;
	static	size_t				m_bytesMaxReceiveBufferSize;

};


}
}
}