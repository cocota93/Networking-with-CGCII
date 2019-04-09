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
// CGNet::IO::Acceptor::NTCP
//
// 1. CGNet::IO::Acceptor::CTCP��~
//     IAcceptor�� ��ӹ޾� TCP�� Acceptor�� �����ϵ��� ���� Class��.
//
// 2. ��� �Լ���.
//    1) Start()
//       - Bind�� Listen�� �����ϴ� �Լ�.
//       - �� �Լ��� �����ϴ� �͸����� ���������� �ڵ����� StartAccept()�� ȣ��
//         �Ѵ�. ���࿡ Listen�� ���ÿ� StartAccept()�� ������ �ʴ´ٸ� �ɼ�����
//         ������ �����ϴ�.
//    2) Stop()
//       - ������ Socket�� �ݰ� Bind�� Ǯ����̴� �Լ��̴�.
//       - ���Լ��� ȣ���ϸ� OnStop()�Լ��� ȣ��Ǹ� �ɾ� ���� ��� Accept��
//         Completion�Ǿ� ����ǰ� �Ǹ� ���̻� Accept�� ���� �ʴ´�.
// 
//    3) IsEnable() / IsDisable()
//       - ���� Accept�� ó���ϰ� �ִ»������� �ƴ����� �Ǻ��ϴ� �Լ��̴�.
//       - StartAccept()�� ����� ���¶�� Enable���°� �ǰ� StopAccept()��
//         �����ϸ� Disable���°� �ȴ�.
//
//    4) IsBinded() / IsUnbinded()
//       - �Ϲ� Socket���� �����ڸ� Connect�������� �ƴ����� �˾ƺ��� �Լ��̴�.
//       - Bind�� ���¶�� Listen�������� �ǹ��Ѵ�. 
//
//    5) GetSocketCountPreparedToAccept()
//       - Overlapped�� Accept�� ��� �ɷ��ִ����� ��� �Լ�.
//
//    6) GetSocketCountMustPrepareToAccept()/ SetSocketCountMustPrepareToAccept()
//       - ���� ���� �ִ��� Prepare To Accept �������Ϸ� Accept���� ������ �ʴ� ������ ���̴�.
//       - ���� Service�� �����ϸ� �ǹ̾��� ���̴�.
//
//    7) GetSocketCountMustPrepareToAccept() / SetSocketCountMustPrepareToAccept()
//       - �̸� �ɾ� ���� Accept�� ���� �����ϴ� �Լ�.
//
//    8) GetSocketCountConnected()
//       - �� Acceptor�� ���� ���ӹ��� Socket�� ���� �������� Socket�� ���� ��´�.
//
//
// 3. �����ǿ� On�Լ���.
//    1) OnAccept()
//       - Accept�� �������� ��� ȣ��Ǵ� �Լ��̴�. �׷��� �Ϲ�������
//         Accept�� �Ǿ��� �� �ϴ� ó���� Socket�� ó���� ������ ���� Socket
//         �� OnConnect()�� �����Ǹ� ���� ����ؼ� OnAccept�� ���� ������ 
//         �ʴ´�.
//
//    2) OnFailAccept()		Socket�� Reset�Ҷ� �ҷ����� �Լ�.
//       - Overlapped�� �ɾ���� Accept�� �������� ��� ȣ��Ǵ� �Լ��̴�.
//
//    3) ProcessAllocConnectable() �Լ�.
//       - Acceptor�� ����� �����Ϸ��� �ݵ�� ProcessAllocConnectable()�Լ��� ������
//         ���־�� �Ѵ�. 
//       - �� �Լ����� Socket�� �����Ͽ� �����ֵ��� ���α׷����ָ� �ȴ�.
//         �Ϲ������� Socket�� Pool�� ����Ͽ� �Ҵ��Ͽ� �����ֵ��� ���� �����ȴ�.
//         �� �� �Լ��� Template�� ������ �س��� ������ CGNetAcceptor::CPool<T>�� 
//         CGNetAcceptor::CFactory<T>�� �־ �̰��� ����ϸ� ���� ���� �����
//         �����ϴ�.
//
//    4) OnStart()	Start�� �� ȣ��Ǵ� �Լ�.
//
//    5) OnStop()	Stop�� �� ȣ��Ǵ� �Լ�.
//
// 3. Initialize/Start String
//
//	  [Name]["AddressFormat]			Address Format ("IPv4", "IPv6", "IPv6Only") (Optional:Default="IPv6")
//    [Name]["Address"]					Acceptor�� �ּ� (Optional:Default=BIND_ANY)
//	  [Name]["Port"]					Acceptor�� ��Ʈ
//	  [Name]["AcceptPrepareOnStart"]	���� ������ �� �غ��� ���ϼ� (Optional:Default=0)
//	  [Name]["AcceptMustPrepare"]		�غ��� �ּ� ���� �� (Optional:Default=0)
//
//    ��)  ��ü���� "NAME"�̶�� �Ѵٸ�....
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
	// 1) Service�� ���۰� ����
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
	//! @brief �ʱ�ȭ�Ǳ� �� ȣ��ȴ�.(OnDestroy()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnInitializing(CGMSG_CONTEXT& /*_Msg*/) override {}
	//! @brief �ʱ�ȭ�� �� ȣ��ȴ�.(OnDestroying()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnInitialize(CGMSG_CONTEXT& /*_Msg*/) override {}

	//! @brief �ı��Ǳ� �� ȣ��ȴ�.(OnInitialize()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnDestroying() override					{}
	//! @brief �ı��� �� ȣ��ȴ�.(OnInitializing()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnDestroy() override					{}

	//! @brief �ʱ�ȭ�Ǳ� �� ȣ��ȴ�.(OnDestroy()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStarting(CGMSG_CONTEXT& /*_Msg*/) override {}
	//! @brief �ʱ�ȭ�� �� ȣ��ȴ�.(OnDestroying()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStart(CGMSG_CONTEXT& /*_Msg*/) override {}

	//! @brief �ı��Ǳ� �� ȣ��ȴ�.(OnInitialize()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStopping() override					{}
	//! @brief �ı��� �� ȣ��ȴ�.(OnInitializing()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStop() override						{}

	//! @brief Accept�� ��û���� �� ȣ��ȴ�. @param _pConnectable Aceept�� ���� ��ü
	virtual	void				OnRequestAccept(_In_ CGNet::IO::IConnectable* /*_pConnectable*/){}
	//! @brief Accept�� �Ǿ��� �� ȣ��ȴ�. @param _pConnectable Aceept�� ��ü
	virtual	void				OnAccept(_In_ CGNet::IO::IConnectable* /*_pConnectable*/)		{}
	//! @brief ��û�� Accept�� �������� �� ȣ��ȴ�. @param _pConnectable ��û ������ Aceept ��ü
	virtual	void				OnFailAccept(_In_ CGNet::IO::IConnectable* /*_pConnectable*/)	{}

	//! @brief Accept�� Abort�Ǿ� ȸ���� �� ���� �Ǿ��� �� ȣ��ȴ�.
	virtual	void				OnAcceptAborted()						{}
	//! @brief Abort�� �� �ٽ� ȸ���Ǿ��� �� ȣ��ȴ�.
	virtual	void				OnAcceptRecovered()						{}

	//! @brief Listen�� ������ �غ�Ǿ��� �� ȣ��ȴ�.
	virtual	void				OnPrepareSocket()						{}
	//! @brief Listen�� ������ ������ �� ȣ��ȴ�.
	virtual	void				OnCloseSocket()							{}

	//! @brief Accept �ޱ� ���� �ʿ��� IConnectable ��ü�� �Ҵ� �޴� ���� �޽��(Factory Method) @ return �Ҵ�� IConnectable ��ü
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

	//! @brief �ڽ� ����� �ı� ó���� ����� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
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