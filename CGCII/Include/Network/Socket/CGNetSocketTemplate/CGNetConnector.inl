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
template <class TSOCKET, class TCONNECTABLEMANAGER>
CGNet::CConnector<TSOCKET, TCONNECTABLEMANAGER>::CConnector(_In_opt_z_ const char* _strName, _In_ int _nMaxAllocate)
	: CGNet::IO::Connective::Connector::NTCP(_strName, _nMaxAllocate)
	, TCONNECTABLEMANAGER()	
{
	// 1) Name이 없을 경우 Connector의 Name을 설정한다.
	if(_strName==nullptr)
	{
		// Declare) 
		char	temp[MAX_NAME_LENGTH];

		// - 기본 Acceptor의 Name을 설정한다.
		sprintf_s(temp, MAX_NAME_LENGTH, "connector Base<%hs>", typeid(TSOCKET).name());

		// - 기본 이름을 설정한다.
		SetName(temp);
	}
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGNet::CConnector<TSOCKET, TCONNECTABLEMANAGER>::CConnector(_In_opt_z_ const wchar_t* _strName, _In_ int _nMaxAllocate)
	: CGNet::IO::Connective::Connector::NTCP(_strName, _nMaxAllocate)
	, TCONNECTABLEMANAGER()	
{
	// 1) Name이 없을 경우 Connector의 Name을 설정한다.
	if(_strName==nullptr)
	{
		// Declare) 
		wchar_t	temp[MAX_NAME_LENGTH];

		// - 기본 Acceptor의 Name을 설정한다.
		swprintf_s(temp, MAX_NAME_LENGTH, L"connector Base<%hs>", typeid(TSOCKET).name());

		// - 기본 이름을 설정한다.
		SetName(temp);
	}
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGNet::CConnector<TSOCKET, TCONNECTABLEMANAGER>::~CConnector()
{
	// 1) Connector Connective를 소멸하기전에는 반드시 Stop한다. 반드시!!!!
	Stop();
}

template <class TSOCKET, class TCONNECTABLEMANAGER>
CGPTR<CGNet::IO::IConnectable> CGNet::CConnector<TSOCKET, TCONNECTABLEMANAGER>::ProcessAllocConnectable()
{
	// Return) Socket을 일단 할당하여 반환한다.
	return NEW<TSOCKET>();
}
