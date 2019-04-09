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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::IO::CRemoteMessage
//
// 1. CGNet::IO::CRemoteMessage란!
//    1) 원격으로 접속되어 있는(일반적으로 TCP) 상대에게 보낸 메시지에 대한 회신 
//       메시지를 받을 수 있도록 하는 시스템이다.
//    2) 전송할 때 실행할 Lambda함수를 정의해 주면 해당 메시지에 대한 답변 메시지가
//       도착하였을 때 그 Lambda 함수를 호출해 준다.
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
	// 1) Request Object를 얻는다.
	CGPTR<CRequest>	pRequest	 = NEW<CRequest>();

	// 2) Response Function을 저장해 놓는다.
	pRequest->m_fResponse	 = p_fResponse;
	pRequest->m_pSource		 = p_pSource;

	// 3) Message를 만든다.
	CCGBuffer	tempBuffer	 = MEM_POOL_ALLOC(16+_Buffer.len);

	tempBuffer.append<uint32_t>();
	tempBuffer.append<uint32_t>(CGMESSAGE::NETWORK::SOCKET::REMOTE_REQUEST);
	tempBuffer.append<int>(m_iRequestID);
	tempBuffer.append<uint32_t>();
	tempBuffer.append(_Buffer);
	tempBuffer.front<uint32_t>()	 = tempBuffer.len;

	// 4) 추가한다.
	LOCK(m_mapRequest)
	{
		// -Request Serial을 얻는다.
		uint32_t	dwRequestSerial		 = m_dwRequestSerial++;

		// - Request Serial을 적어 넣는다.
		tempBuffer.front<uint32_t>(8)	 = dwRequestSerial;

		// - 추가한다.
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

	// 1) Message를 Casting한다.
	CGNETMSG&	rMSG	 = (CGNETMSG&)_Msg;

	// Check) Response일 때만 Message를 처리한다.
	if(rMSG.Buffer.front<uint32_t>(4)==CGMESSAGE::NETWORK::SOCKET::REMOTE_RESPONSE)
	{
		// 2) Resquestor의 ID를 확인한다.
		int		iRequestID	 = rMSG.Buffer.front<int>(8);

		// Check) Request ID가 다르면 끝낸다.
		RETURN_IF(iRequestID!=m_iRequestID, false);

		// 3) Request ID를 얻는다.
		uint32_t	dwRequestSerial		 = rMSG.Buffer.front<uint32_t>(12);

		// Declare) 
		CGPTR<CRequest>	pRequest;

		LOCK(m_mapRequest)
		{
			// - Request를 찾는다.
			auto	iter	 = m_mapRequest.find(dwRequestSerial);

			// Check) 해당 Request 객체를 찾지 못했으면 끝낸다.
			RETURN_IF(iter==m_mapRequest.end(), false);

			// Check) Request를 찾지 못했으면 끝낸다.
			RETURN_IF(iter->second.empty(), false);

			// - 값을 복사한다.
			pRequest	 = iter->second;
		}

		// 4) 전달을 위한 Message head 부분의 12Byte를 Extract한다.
		rMSG.Buffer.extract<16>();

		// 5) 실행한다.
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
