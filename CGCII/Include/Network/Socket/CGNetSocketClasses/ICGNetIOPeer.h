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
// CGNet::IO::IPeer
//
// 1. CGNet::IO::IPeer��~
//     Peer�� Interface class�̴�. 
//     Peer Index�� Peer�� ��ȣ�� �ǹ��ϸ� GroupPeer�� ���� �� �־�����.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IPeer : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (I) Reference Counter.
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			int					GetPeerIndex() const						{	return m_iPeerIndex;}
			void				SetPeerIndex(_In_ int _iPeerIndex)			{ m_iPeerIndex = _iPeerIndex; }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			int					m_iPeerIndex;
};


}
}