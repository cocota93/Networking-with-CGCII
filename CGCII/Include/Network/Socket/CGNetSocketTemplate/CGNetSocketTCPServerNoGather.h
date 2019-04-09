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
// CGNet::Socket::CTCPServerNoGather
//
// 1. CGNet::Socket::CTCPServerNoGather��!
//    1) �⺻�����δ� CGNet::Socket::CTCPServer�� �����ϳ� Socket�� Sender�κи�
//       No Gather ������ ����� ���̴�.
//    2) ������ ���� ���� Socket�� ��� No Gather������ �� �뷮�� ó�� ���� �鿡��
//       ȿ�����̴�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace Socket
{

template <class THEAD=CGNet::IO::Packetable::PRIMITIVE<uint32_t>>
class CTCPServerNoGather :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNet::Socket::CTCPNoGather<THEAD>,		// (@) TCP Socket
	public						CGNet::IO::AddOn::NSocketSustain		// (@) Socket Sustainer
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTCPServerNoGather()										{}
	virtual	~CTCPServerNoGather()										{}
};


}
}