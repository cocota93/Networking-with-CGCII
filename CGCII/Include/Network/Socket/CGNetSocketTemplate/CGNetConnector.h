//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                      Network Socket Template Classes                      *
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
// CGNet::CConnector<TSOCKET>
//
// 1. CGNet::CConnector<T>��~
//    1) �⺻������ CGNet::IO::CGNetConnector::NTCP�̴� ������ ���⿡ ProcessAllocConnectable()
//       �Լ��� �������� Template class�̴�.
//
//    2) �� Class�� ���� �� �� TSOCKET�� Connector�� �����Ͽ� ����� Socket�� 
//       typename�� ���� ������ Connect�� ȣ���ϸ� ��ü������ Socket�� ������ ��
//       ������ Socket�� ���ϴ� IP Address�� ���ӽ����ش�.
//
//    3) Connector���� ������ Socket�� ��ü������ �����ȴ�. ���� �ʿ��� ���
//       ConnectableManager�� �����Ǵ� Socket�� ��� �ü��� �ִ�.
//
//
// 2. �����ǿ� Hook�Լ���.
//
//		// 1) CGNet::IO::Socket::CTCP
//		virtual	void	OnConnect(CGNet::IO::IConnectable* _pConnectable);
//		virtual	void	OnFailConnect(CGNet::IO::IConnectable* _pConnectable, uint32_t _Reason);
//		virtual	void	OnDisconnect(CGNet::IO::IConnectable* _pConnectable, uint32_t _Reason);
//
//
// 3. ���ǻ���
//    1) TSOCKET Class�� �ݵ�� CGNet::IO::IConnectable�� ��ӹ��� class�������� 
//       �Ѵ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{

template <class TSOCKET, class TCONNECTABLEMANAGER=CGNet::IO::ConnectableManager::CList<TSOCKET> >
class CConnector : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						TCONNECTABLEMANAGER,					// (@) ConnectableManager
	public						CGNet::IO::Connective::Connector::NTCP	// (@) Connector TCP.
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CConnector(_In_opt_z_ const char* _strName = nullptr, _In_ int _nMaxAllocate = INT_MAX);
			CConnector(_In_opt_z_ const wchar_t* _strName, _In_ int _nMaxAllocate = INT_MAX);
	virtual	~CConnector();


// ****************************************************************************
// Implementations) 
// ----------------------------------------------------------------------------
protected:
	// Process Functions)
	virtual	CGPTR<CGNet::IO::IConnectable>	ProcessAllocConnectable() override;
};


}

#include "Network/Socket/CGNetSocketTemplate/CGNetConnector.inl"
