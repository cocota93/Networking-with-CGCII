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
// CGNet::IO::Connective::Connector(���� �߰��)
//
// 1. CGNet::IO::Connective::Connector��~
//    1) Connectable�� �뷮 ������ ó���� �����ִ� ���̴�.
//    2) ��ǥ���� ������ TCP�� Acceptor�� Connetor�� �ִ�.
//
// 2. ���� �Լ�.
//    1) ProcessConnect()
//       - ����ó�� ������ �����ϴ� �Լ�.
//
//    2) ProcessDisconnect()
//       - �������� ������ �����ϴ� �Լ�.
//
// 3. ������!!!
//	  1) Connector�� �Ҹ��ϱ� ���� �ݵ�� Stop�Լ��� ȣ���Ͽ� Stop�� ���¿���
//	     �����ؾ� �Ѵ�!!! �׷��� ������ �޸� Leak�� �߻��� �� �ִ�.
//		  �̸� ���� �� Ŭ������ ConnectableManager�� ���ÿ� ��ӹ��� Ŭ������ 
//		 �Ҹ��ڿ� Stop()�Լ��� �־� �ִ� ���� ���� �����Ѵ�.
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

	// 2) ProcessAllocConnectable(�ݵ�� �������ؾ� �Ѵ�.)
	virtual	CGPTR<IConnectable>	ProcessAllocConnectable() PURE;
	

// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Start/Stop
	virtual void				_ProcessStarting(CGMSG_CONTEXT& _Msg) override;
	virtual void				_ProcessStopping() override;
	virtual void				_ProcessStop() override;

	//! @brief �ڽ� ����� �ı� ó���� ����� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
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