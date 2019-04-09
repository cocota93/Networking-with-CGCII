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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::CConnector<TSOCKET>
//
// 1. CGNet::CConnector<T>은~
//    1) 기본적으로 CGNet::IO::CGNetConnector::NTCP이다 하지만 여기에 ProcessAllocConnectable()
//       함수를 재정의한 Template class이다.
//
//    2) 이 Class를 선언 할 때 TSOCKET에 Connector가 생성하여 사용할 Socket의 
//       typename만 집어 넣으면 Connect를 호출하면 자체적으로 Socket을 생성한 후
//       생성한 Socket을 원하는 IP Address에 접속시켜준다.
//
//    3) Connector에서 생성된 Socket은 자체적으로 관리된다. 따라서 필요할 경우
//       ConnectableManager에 관리되는 Socket을 얻어 올수도 있다.
//
//
// 2. 재정의용 Hook함수들.
//
//		// 1) CGNet::IO::Socket::CTCP
//		virtual	void	OnConnect(CGNet::IO::IConnectable* _pConnectable);
//		virtual	void	OnFailConnect(CGNet::IO::IConnectable* _pConnectable, uint32_t _Reason);
//		virtual	void	OnDisconnect(CGNet::IO::IConnectable* _pConnectable, uint32_t _Reason);
//
//
// 3. 주의사항
//    1) TSOCKET Class는 반드시 CGNet::IO::IConnectable을 상속받은 class여야지만 
//       한다.
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
