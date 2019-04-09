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
// CGNet::IO::Binder::NUDP
//
// 1. Binder��~
//    1) Socket�� bind() ����� �ִ� Ŭ������ �⺻������ UDP�� Bind�� ���� ���̴�.
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
	virtual public				CGNet::IO::Statistics::NSocket			// (@) ���
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