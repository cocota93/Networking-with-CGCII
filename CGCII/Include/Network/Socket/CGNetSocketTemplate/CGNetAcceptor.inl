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
template <class TSOCKET, class TCONNECTABLEMANAGER>
CGNet::CAcceptor<TSOCKET, TCONNECTABLEMANAGER>::CAcceptor(_In_opt_z_ const char* _strName, _In_ int _nMaxAllocate)
	: CGNet::IO::Connective::Acceptor::NTCP(_strName, _nMaxAllocate)
	, NCGDispatchable()
	, TCONNECTABLEMANAGER()	
{
	// 1) Name�� ���� ��� Acceptor�� Name�� �����Ѵ�.
	if(_strName==nullptr)
	{
		// Declare) 
		char	temp[MAX_NAME_LENGTH];

		// - �⺻ Acceptor�� Name�� �����Ѵ�.
		sprintf_s(temp, MAX_NAME_LENGTH, "acceptor Base<%s>", typeid(TSOCKET).name());

		// - �⺻ �̸��� �����Ѵ�.
		SetName(temp);
	}
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGNet::CAcceptor<TSOCKET, TCONNECTABLEMANAGER>::CAcceptor(_In_opt_z_ const wchar_t* _strName, _In_ int _nMaxAllocate)
	: CGNet::IO::Connective::Acceptor::NTCP(_strName, _nMaxAllocate)
	, NCGDispatchable()
	, TCONNECTABLEMANAGER()
{
	// 1) Name�� ���� ��� Acceptor�� Name�� �����Ѵ�.
	if(_strName==nullptr)
	{
		// Declare) 
		wchar_t	temp[MAX_NAME_LENGTH];

		// - �⺻ Acceptor�� Name�� �����Ѵ�.
		swprintf_s(temp, MAX_NAME_LENGTH, L"acceptor Base<%hs>", typeid(TSOCKET).name());

		// - �⺻ �̸��� �����Ѵ�.
		SetName(temp);
	}
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGNet::CAcceptor<TSOCKET, TCONNECTABLEMANAGER>::~CAcceptor()
{
	// 1) Acceptor�� �Ҹ��ϱ� �� �ݵ�� CloseSocket()�� ���־�� �Ѵ�!!! (�ݵ��...)
	Stop();
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGPTR<CGNet::IO::IConnectable> CGNet::CAcceptor<TSOCKET, TCONNECTABLEMANAGER>::ProcessAllocConnectable()
{
	// Return) Socket�� �ϴ� �Ҵ��Ͽ� ��ȯ�Ѵ�.
	return NEW<TSOCKET>();
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
void CGNet::CAcceptor<TSOCKET, TCONNECTABLEMANAGER>::_ProcessDestroy()
{
	// 1) Call Parent's _ProcessDestroy function
	CGNet::IO::Connective::Acceptor::NTCP::_ProcessDestroy();

	// 2) Unregister all messageable objects
	ResetDispatchable();
}
