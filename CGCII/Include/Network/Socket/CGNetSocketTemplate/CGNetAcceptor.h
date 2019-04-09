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
// CGNet::CAcceptor<TSOCKET>
//
// 1. CGNet::CAcceptor<T>은~
//    1) 기본적으로 CGNet::IO::Acceptor::NTCP이다 하지만 여기에 ProcessAllocConnectable()
//       함수를 재정의한 Template class이다.
//
//    2) Accept때 사용할 Socket의 Class만 Template 인자로 설정해 주면 그 Socket
//       으로 Accept를 수행한다.
//
//    3) 이 Class를 선언 할 때 TSOCKET에 Acceptor가 생성하여 사용하려는 Socket만 
//       집어 넣으면 Acceptor를 접속을 하게 되면 T로 설정한 Socket을 생성하여 
//       Accept를 걸어서 Acceptor로 동작한다.
//
//
// 2. Initialize/Start String
//
//    "[Name]/Address"
//	  "[Name]/Port"
//	  "[Name]/AcceptPrepareOnStart"
//	  "[Name]/AcceptMustPrepare"
//
//
// 3. 주의사항
//    1) TSOCKET Class는 반드시 CGNet::IO::IConnectable을 상속받은 class여야지만 
//       한다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{

template <class TSOCKET, class TCONNECTABLEMANAGER=CGNet::IO::ConnectableManager::CList<TSOCKET>>
class CAcceptor : 
// ****************************************************************************
// Inherited Classes) NTCP
// ----------------------------------------------------------------------------
	public						CGNet::IO::Connective::Acceptor::NTCP,	// (@) Acceptor TCP.
	public						NCGDispatchable,						// (@) Dispatchable List
	public						TCONNECTABLEMANAGER						// (@) ConnectableManager
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CAcceptor(_In_opt_z_ const char* _strName = nullptr, _In_ int _nMaxAllocate = INT_MAX);
			CAcceptor(_In_opt_z_ const wchar_t* _strName, _In_ int _nMaxAllocate = INT_MAX);
	virtual	~CAcceptor();


// ****************************************************************************
// Implementations) 
// ----------------------------------------------------------------------------
protected:
	virtual	CGPTR<CGNet::IO::IConnectable>	ProcessAllocConnectable() override;
	virtual void				_ProcessDestroy() override;
};


}

#include "Network/Socket/CGNetSocketTemplate/CGNetAcceptor.inl"

