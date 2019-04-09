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
// CManagerRegister
//
// 1. CManagerRegister란!
//    1) 
//    2) 
//
//-----------------------------------------------------------------------------
template <class TREQUEST>
class CManagerRegister : virtual public ICGReferenceable
{
public:
			CManagerRegister() : m_dwRequestID(1)	{}
	virtual	~CManagerRegister()						{}

public:
	// 1) Request/Unrequester
			uint32_t			RegisterRequest(_In_ TREQUEST* _pRequest);
			CGPTR<TREQUEST>		UnregisterRequest(_In_ uint32_t _idTransaction);
			void				UnregisterRequestAll();
			void				UnregisterRequestAll(_In_ const std::function<void (TREQUEST* _pRequest)>& _Function);

	// 2) Request Count
			int					GetRequestCount() const;

public:
			LOCKABLE<std::map<uint32_t, CGPTR<TREQUEST>>>	m_mapRequest;
			uint32_t			m_dwRequestID;
};

template <class TREQUEST>
uint32_t CManagerRegister<TREQUEST>::RegisterRequest(_In_ TREQUEST* _pRequest)
{
	LOCK(m_mapRequest)
	{
		// Declare) RequestID을 얻는다.
		uint32_t	dwRequestID	 = (m_dwRequestID!=0) ? m_dwRequestID++ : (++m_dwRequestID)++;

		// 1) Insert한다.
		auto	result	 = m_mapRequest.insert(std::make_pair(dwRequestID, _pRequest));

		// Check) 삽입하지 못했다면 Exception을 던진다.
		THROW_IF(result.second==false, CGException::CThrow_DomainError(_CGTEXT("Fail to insert ") _CGFUNCTION));

		// Return) 
		return	dwRequestID;
	}
}

template <class TREQUEST>
CGPTR<TREQUEST> CManagerRegister<TREQUEST>::UnregisterRequest(_In_ uint32_t _idTransaction)
{
	// Check)
	RETURN_IF(_idTransaction==0, CGPTR<TREQUEST>());

	// Declare) 
	CGPTR<TREQUEST>	pRequest;

	LOCK(m_mapRequest)
	{
		// 1) Account ID에 해당하는 Request정보를 얻는다.
		auto	iterFind	 = m_mapRequest.find(_idTransaction);

		// Check) 찾지 못했다면 끝낸다.
		RETURN_IF(iterFind==m_mapRequest.end(), CGPTR<TREQUEST>());

		// 2) 찾은 Request의 SocketUser를 저장해 놓는다.
		pRequest	 = iterFind->second;

		// 3) 지운다.
		m_mapRequest.erase(iterFind);
	}

	// Return) 
	return	pRequest;
}

template <class TREQUEST>
void CManagerRegister<TREQUEST>::UnregisterRequestAll()
{
	// 1) 모두 제거한다.
	LOCK(m_mapRequest)
	{
		m_mapRequest.clear();
	}
}

template <class TREQUEST>
void CManagerRegister<TREQUEST>::UnregisterRequestAll(_In_ const std::function<void (TREQUEST* _pRequest)>& _Function)
{
	// Declare) 
	vector<CGPTR<TREQUEST>>	vectorRequest;

	LOCK(m_mapRequest)
	{
		// 1) 먼저 Reserve한다.
		vectorRequest.reserve(m_mapRequest.size());

		// 2) 복사한다.
		for(auto& iter:m_mapRequest)
		{
			vectorRequest.push_back(iter.second);
		}

		// 3) 모두 제거한다.
		m_mapRequest.clear();
	}

	// 4) 모두에게 실패 메시지를 전송한다.
	if(_Function!=nullptr)
	{
		std::for_each(vectorRequest.begin(), vectorRequest.end(), _Function);
	}
}

template <class TREQUEST>
int CManagerRegister<TREQUEST>::GetRequestCount() const
{
	LOCK(m_mapRequest)
	{
		return	static_cast<int>(m_mapRequest.size());
	}
}