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
// CGNet::IO::Sender::NContainer
//
// 1. CGNet::IO::Sender::CContainer��~
//     ���� ���� SenderStream�� �����͸� ������ �ִٰ� Send�� ��� Peer�� 
//    ��� �����ϴ� �Լ��̴�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sender
{

template <class TCONTAINER>
class NContainer : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISender,						//     Sender
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) ���
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NContainer(_In_ TCONTAINER& p_rContainer) : m_rContainer(p_rContainer)	{}
			~NContainer()												{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send�� �� �θ��� �Լ�.
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			TCONTAINER&			m_rContainer;
};


template <class TCONTAINER>
bool NContainer<TCONTAINER>::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf�� nullptr�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len�� 0�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	// 1) ���鼭 ����~
	for(auto& iter: m_rContainer)
	{	
		// Check) ���࿡ nullptr�̸� ����...
		CONTINUE_IF(iter==nullptr);

		// 1) Node�� �� �����Ѵ�.
		iter->Send(_pBuffer, _pSockAddress);
	}
	//-----------------------------------------------------------------
	// ����) Sender�� �⺻������ AddReference�� Release�� �������� �ʴ´�.
	//       ���� ���⼭ Release�� �ϸ� �ȵȴ�.
	//       ���� �ʿ��� ��� Send�κа� ProcessCompleteSend�κ��� AddReference
	//       �� Release�� ¦�� ��Ȯ�� ���ߵ��� �ؾ��Ѵ�.
	//-----------------------------------------------------------------

	// ���) Sended Packet�� ����Ѵ�.
	Statistics_OnSendMessage();

	// Return) ����!!!
	return	true;
}


}
}
}