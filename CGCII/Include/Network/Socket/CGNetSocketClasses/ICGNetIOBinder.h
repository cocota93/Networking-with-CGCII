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
// CGNet::IO::IBindable
//
// 1. IBindable은~
//    Bind를 위한 Bind Interface를 가진 Interface Class임.
//
// 2. 주요사용처.
//    1) UDP Socket을 위한 Binder이다.
//    2) 만약 UDP Socket을 특정한 주소와 Port에 Bind해야 한다면 이 Binder 클래스를
//       상속받아 Bind()함수를 사용하여 특정 주소와 포트에 Bind할 수 있다.
//    3) Binder가 된다면 내부적으로 Binder Manager에 등록된다. 또 CloseSocket()
//       되면 Binder Manager에서 등록해제된다.
//    4) 등록된 Binder들은 싱글턴인 CGNet::IO::Binder::Manager 객체를 통해 정보를
//       얻을 수 있다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IBinder : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				CGNet::IO::ISocket,						// (I) Socket Handle
	virtual public				ICGMessageable,							// (I) Messageable
	virtual	public				ICGNameable								// (I) Nameable
{
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) 추가 Bind함수
			bool				Bind(_In_opt_ const SOCKADDR_CGNETWORK* _pSocketAddr);
			bool				Bind(_In_ u_short p_dwPort = 0);


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	// 1) Bind함수
	virtual	bool				RequestBind(_In_ const SOCKADDR_CGNETWORK& _rSocketAddr) PURE;

public:
	// 2) Reset할때 호출하는 함수.(기본은 빈것...)
	virtual	void				ResetBinder() PURE;

protected:
			void				RegisterBinder();
			void				UnregisterBinder();
};



}
}