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

class NTCPRIO :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NTCP
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NTCPRIO() : NTCP(WSA_FLAG_REGISTERED_IO)					{}
			~NTCPRIO()													{}
};


}
}
}