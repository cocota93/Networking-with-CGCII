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
// CGNet::IO::IConnectable
//
// 1. CGNet::IO::IConnectable은~
//    1) 접속이 필요한 Socket에 필요한 Connectable이다.
//    2) 일반적으로 TCP socket이나 Reliable UDP에 사용된다.
//    3) TCP Socket의 경우 Server측이나 Client측이나 모두 접속이 필요하므로 
//       TCP Socket은 모두 ICGConnectable을 상속받은 것이다.
//    4) 접속 후 처리 과정을 작성하는 클래스로 아래와 같은 주요 함수가 있다.
//
//       - bool ProcessCompleteConnect(_In_opt_ CGNet::IO::IConnective* _pConnective, _In_ uintptr_t _Return);
//         접속 완료 후 처리과정을 정의하는 함수이다.
//
//       - bool ProcessCompleteDisconnect();
//         접속 종료 후 접속 종료처리과정을 정의하는 함수이다.
//
//       - bool Disconnect();
//         접속 종료 요구의 처리를 정의하는 함수이다.
//
//    5) ICGConnectable은 접속이 성립되거나 혹은 접속 처리가 실패한 후 처리 과정을
//       정의하는 클래스이다. 
//       접속을 요구하는 클래스는 IConnector와 Connective::IAcceptor를 사용해야
//       한다.
// 
// 
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IConnectable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				CGNet::IO::ISocket,						// (I) 핵심 요소인 Socket
	virtual public				IAddress,								// (@) Address
	virtual public				CGNet::IO::Statistics::NSocket			// (@) 통계
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			IConnectable() : m_pConnective(nullptr)						{}
	virtual	~IConnectable()												{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Disconnect를 수행할 때 부르는 함수이다.(Graceful)
	virtual	bool				Disconnect() PURE;

	// 2) Reset할때 호출하는 함수.(기본은 빈것...)
	virtual	void				ResetConnectable() PURE;


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
public:
	virtual	bool				ProcessCompleteConnect(_In_opt_ CGNet::IO::IConnective* _pConnective, _In_ uintptr_t _Return) PURE;
	virtual	bool				ProcessCompleteDisconnect() PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	// 1) Connective
			IConnective*		m_pConnective;
			flexible<16>		m_flexible;
			circular_list<CGNet::IO::IConnectable*>::iterator	m_iterConnectable;
};


}
}