//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                      Network Socket Template Classes                      *
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
// CGNet::Socket::CTCPServer
//
// 1. CGNet::Socket::CTCPServer��!
//    1) �⺻�����δ� CGNet::Socket::CTCP�� CTCPQueue�� �����ϴ�. �׷��� ���⿡ 
//       ���� �ð��� �ۼ����� ���� ��� �ڵ����� ������ ��������� ������ ������ 
//       Add-On�� �߰��� ���̴�.
//    2) �⺻������ �̷� ���´� Server���� ���� ���ȴٰ� �� �� �ִ�.
//
//       @ ���� �̷��� ���ǵ� ���� �ܿ� �پ��� ���¸� ���� �����Ͽ� ��밡���ϴ�.
//         �� Template�� ���� ����ϱ� ������ �̸� ����� ���� �Ϳ� �Ұ��ϴ�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class TCLASS, class THEAD=CGNet::IO::Packetable::PRIMITIVE<uint32_t>>
class CTCPServer :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::Socket::CTCPDispatchable<TCLASS, THEAD>,// (@) TCP Socket
	public						CGNet::IO::AddOn::NSocketSustain		// (@) Socket Sustainer
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCPServer()												{}
	virtual	~CTCPServer()												{}
};


}
}