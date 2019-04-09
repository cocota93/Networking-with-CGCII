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
// CGNet::CAcceptor<TSOCKET>
//
// 1. CGNet::CAcceptor<T>��~
//    1) �⺻������ CGNet::IO::Acceptor::NTCP�̴� ������ ���⿡ ProcessAllocConnectable()
//       �Լ��� �������� Template class�̴�.
//
//    2) Accept�� ����� Socket�� Class�� Template ���ڷ� ������ �ָ� �� Socket
//       ���� Accept�� �����Ѵ�.
//
//    3) �� Class�� ���� �� �� TSOCKET�� Acceptor�� �����Ͽ� ����Ϸ��� Socket�� 
//       ���� ������ Acceptor�� ������ �ϰ� �Ǹ� T�� ������ Socket�� �����Ͽ� 
//       Accept�� �ɾ Acceptor�� �����Ѵ�.
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
// 3. ���ǻ���
//    1) TSOCKET Class�� �ݵ�� CGNet::IO::IConnectable�� ��ӹ��� class�������� 
//       �Ѵ�.
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

