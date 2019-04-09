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
// CGNet::IO::Acceptor::NTCP
//
// 1. CGNet::IO::Acceptor::CTCP는~
//     IAcceptor를 상속받아 TCP의 Acceptor로 동작하도록 만든 Class임.
//
// 2. 사용 함수들.
//    1) Start()
//       - Bind와 Listen을 수행하는 함수.
//       - 이 함수를 수행하는 것만으로 내부적으로 자동으로 StartAccept()를 호출
//         한다. 만약에 Listen과 동시에 StartAccept()를 원하지 않는다면 옵션으로
//         조정이 가능하다.
//    2) Stop()
//       - 완전히 Socket을 닫고 Bind를 풀어벌이는 함수이다.
//       - 이함수를 호출하면 OnStop()함수가 호출되며 걸어 놓은 모든 Accept는
//         Completion되어 종료되게 되며 더이상 Accept를 걸지 않는다.
// 
//    3) IsEnable() / IsDisable()
//       - 현재 Accept를 처리하고 있는상태인지 아닌지를 판별하는 함수이다.
//       - StartAccept()가 수행된 상태라면 Enable상태가 되고 StopAccept()를
//         수행하면 Disable상태가 된다.
//
//    4) IsBinded() / IsUnbinded()
//       - 일반 Socket으로 말하자면 Connect상태인지 아닌지를 알아보는 함수이다.
//       - Bind된 상태라면 Listen상태임을 의미한다. 
//
//    5) GetSocketCountPreparedToAccept()
//       - Overlapped로 Accept가 몇개를 걸려있는지를 얻는 함수.
//
//    6) GetSocketCountMustPrepareToAccept()/ SetSocketCountMustPrepareToAccept()
//       - 무슨 일이 있더라도 Prepare To Accept 숫자이하로 Accept수를 줄이지 않는 마지노 선이다.
//       - 물론 Service를 중지하면 의미없는 값이다.
//
//    7) GetSocketCountMustPrepareToAccept() / SetSocketCountMustPrepareToAccept()
//       - 미리 걸어 놓을 Accept의 수를 설정하는 함수.
//
//    8) GetSocketCountConnected()
//       - 이 Acceptor를 통해 접속받은 Socket중 현재 접속중인 Socket의 수를 얻는다.
//
//
// 3. 재정의용 On함수들.
//    1) OnAccept()
//       - Accept에 성공했을 경우 호출되는 함수이다. 그러나 일반적으로
//         Accept가 되었을 때 하는 처리는 Socket당 처리가 많으면 따라서 Socket
//         의 OnConnect()의 재정의를 많이 사용해서 OnAccept는 거의 사용되지 
//         않는다.
//
//    2) OnFailAccept()		Socket을 Reset할때 불려지는 함수.
//       - Overlapped로 걸어놓은 Accept가 실패했을 경우 호출되는 함수이다.
//
//    3) ProcessAllocConnectable() 함수.
//       - Acceptor가 제대로 동작하려면 반드시 ProcessAllocConnectable()함수를 재정의
//         해주어야 한다. 
//       - 이 함수에서 Socket을 생성하여 돌려주도록 프로그램해주면 된다.
//         일반적으로 Socket은 Pool을 사용하여 할당하여 돌려주도록 많이 설정된다.
//         또 이 함수를 Template로 재정의 해놓은 것으로 CGNetAcceptor::CPool<T>와 
//         CGNetAcceptor::CFactory<T>가 있어서 이것을 사용하면 보다 쉽게 사용이
//         가능하다.
//
//    4) OnStart()	Start될 때 호출되는 함수.
//
//    5) OnStop()	Stop될 때 호출되는 함수.
//
// 3. Initialize/Start String
//
//	  [Name]["AddressFormat]			Address Format ("IPv4", "IPv6", "IPv6Only") (Optional:Default="IPv6")
//    [Name]["Address"]					Acceptor할 주소 (Optional:Default=BIND_ANY)
//	  [Name]["Port"]					Acceptor할 포트
//	  [Name]["AcceptPrepareOnStart"]	최초 시작할 때 준비할 소켓수 (Optional:Default=0)
//	  [Name]["AcceptMustPrepare"]		준비할 최소 소켓 수 (Optional:Default=0)
//
//    예)  객체명이 "NAME"이라고 한다면....
//
//		   CGMSG msgContext;
//         msgContext.Setting["NAME"]["AddressFormat"]			 = "IPv6";	// "IPv4", "IPv6", "IPv6Only"
//         msgContext.Setting["NAME"]["Port"]					 = 20000;
//         msgContext.Setting["NAME"]["AcceptPrepareOnStart"]	 = 64";
//         msgContext.Setting["NAME"]["AcceptMustPrepare"]		 = 32;
//
// 4. Message Notify
//    1) Enable/Disable
//
//
//    2) Enable/Disable
//       - CGMESSAGE::NETWORK::SOCKET::CONNECTIVE_ENABLE
//		 - CGMESSAGE::NETWORK::SOCKET::CONNECTIVE_DISABLE
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connective
{
namespace Acceptor
{

class NTCP :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::Connective::IAcceptor,
	public						CGNameable::NString,
	public						NCGObjectState,
	public						NCGStartable,
	public						NCGInitializable,
	virtual protected			CGNet::IO::ISocket,
	virtual public				ICGDispatchable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NTCP(_In_opt_z_ const char* _strName=nullptr, _In_ int _nMax=INT_MAX);
			NTCP(_In_opt_z_ const wchar_t* _strName, _In_ int _nMax=INT_MAX);
			~NTCP();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Service의 시작과 중지
			bool				Start()									{ CGMSG_CONTEXT tempMSG; return Start(tempMSG);}
			bool				Start(_In_ uint16_t _Port, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);
			bool				Start(_In_ SOCKADDR_CGNETWORK& _rSockAddr, _In_ int _AcceptPrepareOnStart=0, _In_ int _AcceptMustPrepare=0);
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) override		{ return NCGStartable::Start(_Msg);}

	// 2) Accept Enable/Disable
	virtual	bool				Enable() override;
	virtual	bool				Disable() override;

	// 3) Socket Status
	virtual	bool				IsEnable() const 						{ return m_bEnable!=0;}
			bool				IsDisable() const 						{ return m_bEnable==0;}
			int					GetAllocatedCount() const				{ return m_nSocketAllocated;}
			void				SetMaxAllocate(int _nMaxAllocate)		{ m_nMaxAllocate= _nMaxAllocate; }
			int					GetMaxAllocate() const					{ return m_nMaxAllocate; }
			int					GetSocketPreparedToAccept() const		{ return m_nSocketPreparedToAccept;}
			int					GetSocketMustPrepare() const			{ return m_nAcceptMustPrepare;}

	// 4) Others
			SOCKADDR_CGNETWORK	GetAcceptAddress() const;


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	//! @brief 초기화되기 전 호출된다.(OnDestroy()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnInitializing(CGMSG_CONTEXT& /*_Msg*/) override {}
	//! @brief 초기화될 때 호출된다.(OnDestroying()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnInitialize(CGMSG_CONTEXT& /*_Msg*/) override {}

	//! @brief 파괴되기 전 호출된다.(OnInitialize()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnDestroying() override					{}
	//! @brief 파괴될 때 호출된다.(OnInitializing()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnDestroy() override					{}

	//! @brief 초기화되기 전 호출된다.(OnDestroy()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStarting(CGMSG_CONTEXT& /*_Msg*/) override {}
	//! @brief 초기화될 때 호출된다.(OnDestroying()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStart(CGMSG_CONTEXT& /*_Msg*/) override {}

	//! @brief 파괴되기 전 호출된다.(OnInitialize()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStopping() override					{}
	//! @brief 파괴될 때 호출된다.(OnInitializing()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStop() override						{}

	//! @brief Accept를 요청했을 때 호출된다. @param _pConnectable Aceept를 받을 객체
	virtual	void				OnRequestAccept(_In_ CGNet::IO::IConnectable* /*_pConnectable*/){}
	//! @brief Accept가 되었을 때 호출된다. @param _pConnectable Aceept된 객체
	virtual	void				OnAccept(_In_ CGNet::IO::IConnectable* /*_pConnectable*/)		{}
	//! @brief 요청한 Accept가 실패했을 때 호출된다. @param _pConnectable 요청 실패할 Aceept 객체
	virtual	void				OnFailAccept(_In_ CGNet::IO::IConnectable* /*_pConnectable*/)	{}

	//! @brief Accept가 Abort되어 회복할 수 없게 되었을 대 호출된다.
	virtual	void				OnAcceptAborted()						{}
	//! @brief Abort된 후 다시 회복되었을 때 호출된다.
	virtual	void				OnAcceptRecovered()						{}

	//! @brief Listen용 소켓이 준비되었을 때 호출된다.
	virtual	void				OnPrepareSocket()						{}
	//! @brief Listen용 소켓이 닫혔을 때 호출된다.
	virtual	void				OnCloseSocket()							{}

	//! @brief Accept 받기 위해 필요한 IConnectable 객체를 할당 받는 공장 메써드(Factory Method) @ return 할당된 IConnectable 객체
	virtual	CGPTR<IConnectable>	ProcessAllocConnectable() PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Start/Stop Process
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;
	virtual void				_ProcessStart(CGMSG_CONTEXT& _Msg) override;
	virtual void				_ProcessStopping() override;
	virtual void				_ProcessStop() override;

	//! @brief 자식 노드의 파괴 처리가 진행된 후 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessDestroy();


	// 2) Connect/Disconnect Process
	virtual	void				ProcessConnectiveConnect(_In_ IConnectable* _pConnectable, _In_ uintptr_t _Return) override;
	virtual	void				ProcessConnectiveDisconnect(_In_ IConnectable* _pConnectable) override;

	// 3) Socket Process
	virtual	void				ProcessPrepareSocket(ADDRESS_FAMILY _AddressFamily=AF_INET) override;
	virtual	bool				ProcessCloseSocket(uint32_t _dwReason=SOCKET_REASON_NONE) override;

	// 4) Acceptor Regeneration 
			bool				ProcessRegenAcceptor();
	
	// 5) Accept
	virtual	bool				RequestAccept() override;

	// 6) Reset
	virtual	void				ResetAcceptor() override				{}

	// 7) Member Variable
			ATOMIC<int>			m_bEnable;
			int					m_nAcceptMustPrepare;
			ATOMIC<int>			m_nSocketPreparedToAccept;
			ATOMIC<int>			m_nSocketAllocated;
			int					m_nMaxAllocate;

	// 8) Error Tolerance
			LOCKABLE<>			m_csErrorTolerance;
			int					m_countErrorTolerance;

	// 9) IP6 Option
			int					m_isIP6Only	;
};


}
}
}
}