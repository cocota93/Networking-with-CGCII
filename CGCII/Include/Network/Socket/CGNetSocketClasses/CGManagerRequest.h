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
// CManagerRegister
//
// 1. CManagerRegister��!
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
		// Declare) RequestID�� ��´�.
		uint32_t	dwRequestID	 = (m_dwRequestID!=0) ? m_dwRequestID++ : (++m_dwRequestID)++;

		// 1) Insert�Ѵ�.
		auto	result	 = m_mapRequest.insert(std::make_pair(dwRequestID, _pRequest));

		// Check) �������� ���ߴٸ� Exception�� ������.
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
		// 1) Account ID�� �ش��ϴ� Request������ ��´�.
		auto	iterFind	 = m_mapRequest.find(_idTransaction);

		// Check) ã�� ���ߴٸ� ������.
		RETURN_IF(iterFind==m_mapRequest.end(), CGPTR<TREQUEST>());

		// 2) ã�� Request�� SocketUser�� ������ ���´�.
		pRequest	 = iterFind->second;

		// 3) �����.
		m_mapRequest.erase(iterFind);
	}

	// Return) 
	return	pRequest;
}

template <class TREQUEST>
void CManagerRegister<TREQUEST>::UnregisterRequestAll()
{
	// 1) ��� �����Ѵ�.
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
		// 1) ���� Reserve�Ѵ�.
		vectorRequest.reserve(m_mapRequest.size());

		// 2) �����Ѵ�.
		for(auto& iter:m_mapRequest)
		{
			vectorRequest.push_back(iter.second);
		}

		// 3) ��� �����Ѵ�.
		m_mapRequest.clear();
	}

	// 4) ��ο��� ���� �޽����� �����Ѵ�.
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