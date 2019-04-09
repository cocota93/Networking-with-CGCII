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
// CGNet::IO::Binder::NUDP
//
// 1. Binder은~
//    1) Socket의 bind() 기능이 있는 클래스로 기본적으로 UDP의 Bind를 위한 것이다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Binder
{

class NUDP : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Socket
	virtual public				CGNet::IO::IBinder,						//     Binder
	virtual protected			CGNet::IO::IReceivable,					// (I) Receivable
	public						CGNameable::NString,					// (@) Nameable String
	virtual public				CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	virtual	bool				RequestBind(_In_ const SOCKADDR_CGNETWORK& _pSocketAddr) override;
	virtual	void				ResetBinder() override					{}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	void				OnBind()								{}
};


}
}
}