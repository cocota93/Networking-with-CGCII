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
// CGNet::IO::Connective::Connector(연결 중계기)
//
// 1. CGNet::IO::Connective::Connector은~
//    1) Connectable의 대량 연결을 처리해 시켜주는 것이다.
//    2) 대표적인 것으로 TCP의 Acceptor와 Connetor가 있다.
//
// 2. 가상 함수.
//    1) ProcessConnect()
//       - 접속처리 과정을 정의하는 함수.
//
//    2) ProcessDisconnect()
//       - 접속해제 과정을 정의하는 함수.
//
// 3. 주의점!!!
//	  1) Connector를 소멸하기 전에 반드시 Stop함수를 호출하여 Stop된 상태에서
//	     종료해야 한다!!! 그렇지 않으면 메모리 Leak이 발생할 수 있다.
//		  이를 위해 이 클래스와 ConnectableManager를 동시에 상속받은 클래스에 
//		 소멸자에 Stop()함수를 넣어 주는 것을 강력 권장한다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connective
{
namespace Connector
{

class NTCP :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::Connective::IConnector,
	public						CGNameable::NString,
	public						NCGObjectState,
	public						NCGStartable,
	public						NCGInitializable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NTCP(_In_opt_z_ const _CHAR* _strName = nullptr, _In_ int _nMaxAllocate = INT_MAX);
			NTCP(_In_opt_z_ const _CHAR_SUB* _strName, _In_ int _nMaxAllocate = INT_MAX);
	virtual ~NTCP();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Socket Status
	virtual	bool				Enable();
	virtual	bool				Disable();

	// 2) Status
	virtual	bool				IsEnable() const override				{ return m_bEnable!=0;}
			bool				IsDisable() const 						{ return m_bEnable==0;}
			int					GetAllocatedCount() const				{ return m_nSocketAllocated;}
			int					GetMaxAllocate() const					{ return m_nMaxAllocate;}
			void				SetMaxAllocate(_In_ int p_iMaxAllocate)	{ m_nMaxAllocate = p_iMaxAllocate; }

	// 3) RequestConnect
	virtual	CGPTR<IConnectable>	AllocConnectable(ADDRESS_FAMILY _AddressFamily=AF_INET);

	// 4) Executor
			void				SetExecutor(CGExecutor::CCompletionPort* p_pExecutor)	{	m_pExecutor=p_pExecutor;}
			CGPTR<CGExecutor::CCompletionPort>	GetExecutor() const		{	return m_pExecutor;}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	// 1) On Functions
	virtual	void				OnRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* /*_paddrPeer*/, _In_ CGNet::IO::IConnectable* /*_pConnectable*/){}
	virtual	void				OnConnect(_In_ CGNet::IO::IConnectable* /*_pConnectable*/)	{}
	virtual	void				OnDisconnect(_In_ CGNet::IO::IConnectable* /*_pConnectable*/, uint32_t /*_Reason*/)	{}
	virtual	void				OnFailConnect(_In_ CGNet::IO::IConnectable* /*_pConnectable*/, uint32_t /*_Reason*/)	{}

	// 2) ProcessAllocConnectable(반드시 재정의해야 한다.)
	virtual	CGPTR<IConnectable>	ProcessAllocConnectable() PURE;
	

// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Start/Stop
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;
	virtual void				_ProcessStopping() override;
	virtual void				_ProcessStop() override;

	//! @brief 자식 노드의 파괴 처리가 진행된 후 처리할 내용을 정의하는 함수 @param _MSg 초기활 할 때 전달된 메시지
	virtual void				_ProcessDestroy();

	// 2) Connect/Disconnect Process 
	virtual	void				ProcessConnectiveConnect(_In_ CGNet::IO::IConnectable* _pConnectable, _In_ uintptr_t _Return) override;
	virtual	void				ProcessConnectiveDisconnect(_In_ CGNet::IO::IConnectable* _pConnectable) override;

	// 3) Connecting Process
	virtual	CGPTR<IConnectable>	ProcessRequestConnect(_In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;
	virtual	bool				ProcessConnecting(_In_ IConnectable* _pConnectable, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) override;

	// 4) Member Variable
			ATOMIC<int>			m_bEnable;
			ATOMIC<int>			m_nSocketAllocated;
			int					m_nMaxAllocate;

	// 5) Executor
			CGPTR<CGExecutor::CCompletionPort>	m_pExecutor;
};


}
}
}
}