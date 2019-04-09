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
// CGNet::IO::CRemoteMessage
//
// 1. CGNet::IO::CRemoteMessage��!
//    1) �������� ���ӵǾ� �ִ�(�Ϲ������� TCP) ��뿡�� ���� �޽����� ���� ȸ�� 
//       �޽����� ���� �� �ֵ��� �ϴ� �ý����̴�.
//    2) ������ �� ������ Lambda�Լ��� ������ �ָ� �ش� �޽����� ���� �亯 �޽�����
//       �����Ͽ��� �� �� Lambda �Լ��� ȣ���� �ش�.
//
//-----------------------------------------------------------------------------
template <class TSOURCE=ICGMessageable>
class CMessageRemoteRequest : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGMessageable							//     Messageable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
			typedef	std::function<bool (TSOURCE* p_pSource, CGMSG& _Msg)>	TRESPONSE_FUNCTION;


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			CMessageRemoteRequest() : m_iRequestID(0), m_dwRequestSerial(0)	{}
	virtual ~CMessageRemoteRequest()									{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual	CCGBuffer			RequestMessage(_In_ const CCGBuffer& _Buffer, _In_ const TRESPONSE_FUNCTION& p_fResponse, _In_ TSOURCE* p_pSource);


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) Process Message
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	// Definitions)
	class CRequest : public NCGPoolable<CRequest>
	{
	public:
		TRESPONSE_FUNCTION		m_fResponse;
		CGPTR<TSOURCE>			m_pSource;
	};

	// 2) Request ID
			int					m_iRequestID;
			uint32_t			m_dwRequestSerial;

	// 3) Request map
			LOCKABLE<std::map<uint32_t, CGPTR<CRequest>>>	m_mapRequest;
};

template <class TSOURCE>
inline CCGBuffer CMessageRemoteRequest<TSOURCE>::RequestMessage(_In_ const CCGBuffer& _Buffer, _In_ const TRESPONSE_FUNCTION& p_fResponse, _In_ TSOURCE* p_pSource)
{
	// 1) Request Object�� ��´�.
	CGPTR<CRequest>	pRequest	 = NEW<CRequest>();

	// 2) Response Function�� ������ ���´�.
	pRequest->m_fResponse	 = p_fResponse;
	pRequest->m_pSource		 = p_pSource;

	// 3) Message�� �����.
	CCGBuffer	tempBuffer	 = MEM_POOL_ALLOC(16+_Buffer.len);

	tempBuffer.append<uint32_t>();
	tempBuffer.append<uint32_t>(CGMESSAGE::NETWORK::SOCKET::REMOTE_REQUEST);
	tempBuffer.append<int>(m_iRequestID);
	tempBuffer.append<uint32_t>();
	tempBuffer.append(_Buffer);
	tempBuffer.front<uint32_t>()	 = tempBuffer.len;

	// 4) �߰��Ѵ�.
	LOCK(m_mapRequest)
	{
		// -Request Serial�� ��´�.
		uint32_t	dwRequestSerial		 = m_dwRequestSerial++;

		// - Request Serial�� ���� �ִ´�.
		tempBuffer.front<uint32_t>(8)	 = dwRequestSerial;

		// - �߰��Ѵ�.
		m_mapRequest.insert(std::make_pair<uint32_t, CGPTR<CRequest>>(dwRequestSerial, pRequest));
	}

	// Return) 
	return	tempBuffer;
}

template <class TSOURCE>
int CMessageRemoteRequest<TSOURCE>::ProcessMessage(CGMSG& _Msg)
{
	// Check) 
	RETURN_IF((_Msg.message & CGMESSAGE::SYSTEM::BUFFER)!=CGMESSAGE_BUFFER, false);

	// 1) Message�� Casting�Ѵ�.
	CGNETMSG&	rMSG	 = (CGNETMSG&)_Msg;

	// Check) Response�� ���� Message�� ó���Ѵ�.
	if(rMSG.Buffer.front<uint32_t>(4)==CGMESSAGE::NETWORK::SOCKET::REMOTE_RESPONSE)
	{
		// 2) Resquestor�� ID�� Ȯ���Ѵ�.
		int		iRequestID	 = rMSG.Buffer.front<int>(8);

		// Check) Request ID�� �ٸ��� ������.
		RETURN_IF(iRequestID!=m_iRequestID, false);

		// 3) Request ID�� ��´�.
		uint32_t	dwRequestSerial		 = rMSG.Buffer.front<uint32_t>(12);

		// Declare) 
		CGPTR<CRequest>	pRequest;

		LOCK(m_mapRequest)
		{
			// - Request�� ã�´�.
			auto	iter	 = m_mapRequest.find(dwRequestSerial);

			// Check) �ش� Request ��ü�� ã�� �������� ������.
			RETURN_IF(iter==m_mapRequest.end(), false);

			// Check) Request�� ã�� �������� ������.
			RETURN_IF(iter->second.empty(), false);

			// - ���� �����Ѵ�.
			pRequest	 = iter->second;
		}

		// 4) ������ ���� Message head �κ��� 12Byte�� Extract�Ѵ�.
		rMSG.Buffer.extract<16>();

		// 5) �����Ѵ�.
		pRequest->m_fResponse(pRequest->m_pSource, _Msg);

		// Return) 
		return	1;
	}

	// Return) 
	return	0;
}

#define	NOTIFY_MESSAGE_REQUEST(request, msg)		\
{													\
	uint32_t dwResult=request->DispatchMessage(msg);\
													\
	if(dwResult!=0)									\
		return dwResult;							\
}

#define	NOTIFY_MESSAGE_REQUEST_SOURCE(request, msg, source)	\
{													\
	msg.pSource	 = source;							\
	uint32_t dwResult=request->DispatchMessage(msg);\
													\
	if(dwResult!=0)									\
		return dwResult;							\
}
