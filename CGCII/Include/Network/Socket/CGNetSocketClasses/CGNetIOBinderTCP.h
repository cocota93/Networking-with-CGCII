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
// CGNet::IO::Binder::NTCP
// 
// 1. Binder은~
//    1) TCP를 위한 Bind() 기능이 있는 함수로 TCP를 위해 제작된 클래스이다.
//    2) TCP의 경우 Accept를 위해 Bind를 수행하는데 이를 위한 클래스이다.
//    3) Accept를 하지 않더라도 클라이언트 TCP 소켓의 경우 BInd를 하고자 할 때가
//       있다 이때 사용할 수 있다.
//    4) TCP용 Connector 객체는 기본적으로 BInder를 상속받아 제작된다.
//    5) Bind시 주소에 0으로  설정하면 하드웨어의 모든 주소에 Bind되며 포트를 0으로
//       하면 임의의 빈 포트를 자동적으로 선택하여 Bind된다.
//    6) 특정한 주소와 포트에 바인드를 할 때는 되도록 1000이상의 포트를 사용하는
//       것이 좋다. 왜냐하면 그 이하의 포트는 예약된 포트가 많기 때문이다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Binder
{

class NTCP : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual protected			CGNet::IO::ISocket,						// (I) Socket
	virtual public				CGNet::IO::IBinder,						//     Binder
	virtual public				CGNet::IO::Statistics::NSocket			//     Socket Stistics
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	virtual	bool				RequestBind(_In_ const SOCKADDR_CGNETWORK& _pSocketAddr) override;
	virtual	void				ResetBinder() override					{}
};


}
}
}