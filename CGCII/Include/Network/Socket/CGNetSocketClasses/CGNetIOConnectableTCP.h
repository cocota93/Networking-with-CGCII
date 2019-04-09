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
// CGNet::IO::Connectable::NTCP
//
// 1. CGNet::IO::Connectable::NTCP이란!
//    1) TCP용 IConnectable을 정의한 클래스이다.
//    2) TCP로 접속을 시도하여 접속처리가 완료되었을 때(성공했을때나 실패했을 때나)
//       이 클래스가 이후 처리과정을 정의하게 된다.
//    3) 이 클래스는 Overlapped I/O를 사용한 Receive를 처리하도록 정의되었으므로
//       접속 후 Receive()를 걸도록 작성되었다.
//    4) 접속이 성공할 경우 OnConnect()함수를 호출하고 실패했을 경우 OnFailConnect()를
//       호출한다.
//    5) 접속이 종료되었을 때 OnDisconnect()함수를 호출하도록 정의되어 있다.
//    6) 접속을 종료를 요구할 때 Disconnect()함수를 호출하면 되며 이는 Graceful
//       Close를 수행하게 된다.
//       주의) 만약 Abortive Close를 사용하고자 한다면 ISocket의 CloseSocket()함수를
//             사용하도록 한다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connectable
{

class NTCP :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IConnectable,				//     Connectable
	virtual protected			CGNet::IO::IReceivable					// (I) Receivable
{
// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
// - 사용자가 이 Socket을 사용자가 조작하기 위한 함수.
public:
	// 1) Disconnect.(Graceful)
	virtual	bool				Disconnect();


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
// - 이 함수들을 재정의 함으로써 프로그래밍을 한다.
// - 어떠한 작업이 수행되었을 때 불려지는 함수이다.
protected:
	// 1) 일반적인 On함수.
	virtual void				OnConnect(CGNet::IO::IConnective* /*_pConnective*/){}
	virtual void				OnDisconnect(uint32_t /*_Reason*/)		{}

	// 2) 실패했을 때 On함수.
	virtual void				OnFailConnect(CGNet::IO::IConnective* /*_pConnective*/, uint32_t /*_Reason*/)		{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Complete Process관련.
	virtual bool				ProcessCompleteConnect(_In_opt_ CGNet::IO::IConnective* _pConnective, _In_ uintptr_t _Return) override;// 1) 접속되었을 때의 처리 절차를 정의하는 함수.
	virtual bool				ProcessCompleteDisconnect() override;// 2) 종료되었을 때의 처리 절차를 정의하는 함수.

	virtual void				ProcessOnConnect(CGNet::IO::IConnective* _pConnective)	{	OnConnect(_pConnective);}
	virtual	void				ProcessOnDisconnect(uint32_t _Resson)	{	OnDisconnect(_Resson);}
	virtual	void				ProcessOnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t _Resson)	{	OnFailConnect(_pConnective, _Resson);}

	// 2) Reset할때 호출하는 함수.
	virtual	void				ResetConnectable() override;
			void				ProcessDisconnect();

			class	CCGExecutableDisconnect;
			friend	class CCGExecutableDisconnect;

			CGPTR<ICGExecutable> AllocExecutableDisconnect(_In_ CGNet::IO::Connectable::NTCP* _pConnectable);
};


}
}
}