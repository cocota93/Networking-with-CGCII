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
// CGNet::IO::ISender
//
// 1. ISender Interface들은~
//     다양한 Send의 형태를 정의한 Interface들이다.
//    전송은 ISendRequest에 정의된 RequestSend에 의해서 수행되지만 이 함수를
//    사용상의 편리를 위한 다양한 형태의 Interface로 정의한 것이다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class ISender : virtual public ICGReferenceable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) PURE;

	// 2) Send할 때 부르는 함수.
	template <class TDATA>
			bool				Send(_In_ const TDATA& p_rData)			{	return Send(CCGBuffer(sizeof(TDATA))<<p_rData);}

	// 3) Operator Overriding
			ISender&			operator<<(const CCGBuffer& p_RHS){	Send(p_RHS); return *this;}
};

class ISenderMass : virtual public ICGReferenceable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				SendMass(_In_ const CGD::buffer* _pBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal) PURE;
};

class ISenderDatagram : virtual public ICGReferenceable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				SendTo(_In_ const CCGBuffer& _Buffer, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) PURE;
};

class ISenderPeer : virtual public ICGReferenceable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	bool				SendTo(_In_ int p_iPeer, _In_ const CCGBuffer& _Buffer) PURE;
};

class ISenderClosser : virtual public ICGReferenceable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Send할 때 부르는 함수.
	virtual	void				ProcessCloseSender() PURE;
};


}
}