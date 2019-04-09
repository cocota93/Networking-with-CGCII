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
//-----------------------------------------------------------------------------
//
// CGNet::IO::Sender::NContainer
//
// 1. CGNet::IO::Sender::CContainer은~
//     여러 개의 SenderStream의 포인터를 가지고 있다가 Send시 모든 Peer에 
//    모두 전송하는 함수이다.
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
	virtual protected			CGNet::IO::Statistics::NSocket			// (@) 통계
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
	// 1) Send할 때 부르는 함수.
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
	// Check) _Buffer->buf가 nullptr이 아닌가?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len이 0이 아닌가?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	// 1) 돌면서 전송~
	for(auto& iter: m_rContainer)
	{	
		// Check) 만약에 nullptr이면 다음...
		CONTINUE_IF(iter==nullptr);

		// 1) Node에 다 전송한다.
		iter->Send(_pBuffer, _pSockAddress);
	}
	//-----------------------------------------------------------------
	// 주의) Sender는 기본적으로 AddReference와 Release를 수행하지 않는다.
	//       따라서 여기서 Release를 하면 안된다.
	//       만약 필요할 경우 Send부분과 ProcessCompleteSend부분의 AddReference
	//       와 Release의 짝을 정확히 맞추도록 해야한다.
	//-----------------------------------------------------------------

	// 통계) Sended Packet을 계산한다.
	Statistics_OnSendMessage();

	// Return) 성공!!!
	return	true;
}


}
}
}