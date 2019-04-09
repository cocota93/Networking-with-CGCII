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
CGNet::CConnector<TSOCKET, TCONNECTABLEMANAGER>::CConnector(_In_opt_z_ const char* _strName, _In_ int _nMaxAllocate)
	: CGNet::IO::Connective::Connector::NTCP(_strName, _nMaxAllocate)
	, TCONNECTABLEMANAGER()	
{
	// 1) Name�� ���� ��� Connector�� Name�� �����Ѵ�.
	if(_strName==nullptr)
	{
		// Declare) 
		char	temp[MAX_NAME_LENGTH];

		// - �⺻ Acceptor�� Name�� �����Ѵ�.
		sprintf_s(temp, MAX_NAME_LENGTH, "connector Base<%hs>", typeid(TSOCKET).name());

		// - �⺻ �̸��� �����Ѵ�.
		SetName(temp);
	}
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGNet::CConnector<TSOCKET, TCONNECTABLEMANAGER>::CConnector(_In_opt_z_ const wchar_t* _strName, _In_ int _nMaxAllocate)
	: CGNet::IO::Connective::Connector::NTCP(_strName, _nMaxAllocate)
	, TCONNECTABLEMANAGER()	
{
	// 1) Name�� ���� ��� Connector�� Name�� �����Ѵ�.
	if(_strName==nullptr)
	{
		// Declare) 
		wchar_t	temp[MAX_NAME_LENGTH];

		// - �⺻ Acceptor�� Name�� �����Ѵ�.
		swprintf_s(temp, MAX_NAME_LENGTH, L"connector Base<%hs>", typeid(TSOCKET).name());

		// - �⺻ �̸��� �����Ѵ�.
		SetName(temp);
	}
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGNet::CConnector<TSOCKET, TCONNECTABLEMANAGER>::~CConnector()
{
	// 1) Connector Connective�� �Ҹ��ϱ������� �ݵ�� Stop�Ѵ�. �ݵ��!!!!
	Stop();
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGPTR<CGNet::IO::IConnectable> CGNet::CConnector<TSOCKET, TCONNECTABLEMANAGER>::ProcessAllocConnectable()
{
	// Return) Socket�� �ϴ� �Ҵ��Ͽ� ��ȯ�Ѵ�.
	return NEW<TSOCKET>();
}
