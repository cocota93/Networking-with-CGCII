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
// CGNet::IO::GroupPeer::NArray<T>
//
// 1. CGNet::IO::GroupPeer::CArray은~
//    여러 Peer를 Array형태로 관리하는 Class이다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace GroupPeer
{

template <class TPEER>
class NArray :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual	public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NArray(int p_nMax=16)										{	SetMaxPeer(p_nMax);}
			~NArray()													{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			CGPTR<TPEER>		GetPeer(_In_ int _iPeerIndex) const;
			CGPTR<TPEER>&		Peer(_In_ int _iPeerIndex);

	virtual	bool				AttachPeer(_In_ int	_iPeerIndex, TPEER* _pPeer);
	virtual	CGPTR<TPEER>		DetachPeer(_In_ int	_iPeerIndex);
			bool				DetachPeer(_In_ TPEER* _pPeer);

			bool				SetMaxPeer(_In_ int p_nMaxPeer);
			int					GetMaxPeer() const						{	return static_cast<int>(m_vectorPeer.size());}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	void				OnPeerAttach(_In_ int _iPeerIndex, _In_ TPEER* _pPeer);
	virtual	void				OnPeerDetach(_In_ int _iPeerIndex, _In_ TPEER* _pPeer);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			vector<CGPTR<TPEER>> m_vectorPeer;
			LOCKABLE<>			m_csvectorPeer;
};


template <class TPEER>
CGPTR<TPEER>& NArray<TPEER>::Peer(_In_ int _iPeerIndex)
{
	// Check) iPeer가 Min과 Max 사이가 아니면 안됀다!
	CGASSERT_ERROR(_iPeerIndex>=0 && _iPeerIndex<static_cast<int>(m_vectorPeer.size()));

	//  1) Peer 얻어 Return하기.
	return		m_vectorPeer.at(_iPeerIndex);
}


template <class TPEER>
CGPTR<TPEER> NArray<TPEER>::GetPeer(_In_ int _iPeerIndex) const
{
	// Check) iPeer가 Min과 Max 사이가 아닐 때는 nullptr을 리턴한다.
	RETURN_IF(_iPeerIndex<0 || _iPeerIndex>=static_cast<int>(m_vectorPeer.size()), CGPTR<TPEER>());

	//  1) Peer 얻어 Return하기.
	return		m_vectorPeer.at(_iPeerIndex);
}



template <class TPEER>
bool NArray<TPEER>::AttachPeer(_In_ int _iPeerIndex, _In_ TPEER* _pPeer)
{
	// Check) _pPeer가 nullptr이면 안된다.
	CGASSERT(_pPeer != nullptr, false);

	LOCK(m_csvectorPeer)
	{
		// Check) iPeer가 Min과 Max 사이가 아닐 때는 false을 리턴한다.
		RETURN_IF(_iPeerIndex<0 || _iPeerIndex>=static_cast<int>(m_vectorPeer.size()), false);

		// Check) 
		RETURN_IF(m_vectorPeer.at(_iPeerIndex)!=nullptr, false);

		// 1) Peer를 list에 추가한다.
		m_vectorPeer.at(_iPeerIndex)	 = _pPeer;

		// 2) Peer의 번호를 맞춘다.
		_pPeer->SetPeerIndex(_iPeerIndex);

		// 3) OnPeerAttach함수를 호출한다.
		OnPeerAttach(_iPeerIndex, _pPeer);
	}


	// Return) 성공!!!
	return	true;
}

template <class TPEER>
CGPTR<TPEER> NArray<TPEER>::DetachPeer(_In_ int _iPeerIndex)
{
	// Declare)
	CGPTR<TPEER>	pPeer;

	LOCK(m_csvectorPeer)
	{
		// Check) iPeer가 Min과 Max 사이여야지만 한다.
		RETURN_IF(_iPeerIndex<0 && _iPeerIndex>=static_cast<int>(m_vectorPeer.size()), CGPTR<TPEER>());

		// 1) Peer를 얻는다.
		pPeer	 = m_vectorPeer.at(_iPeerIndex);

		// Check) 
		RETURN_IF(pPeer.exist(), pPeer);

		// 2) OnPeerDetach함수를 호출한다.
		OnPeerDetach(_iPeerIndex, pPeer);

		// 1) Peer를 list에 추가한다.
		m_vectorPeer.at(_iPeerIndex).reset();

		// 2) Peer의 번호를 맞춘다.
		pPeer->SetPeerIndex(-1);
	}


	// Return) 성공!!!
	return	pPeer;
}

template <class TPEER>
bool NArray<TPEER>::DetachPeer(_In_ TPEER* _pPeer)
{
	DetachPeer(_pPeer->GetPeerIndex());

	// Return)
	return	true;
}


template <class TPEER>
bool NArray<TPEER>::SetMaxPeer(_In_ int p_nMaxPeer)
{
	LOCK(m_csvectorPeer)
	{
		// 1) vector의 Size를 설정한다.
		m_vectorPeer.resize(p_nMaxPeer);
	}

	return	true;
}

template <class TPEER>
void NArray<TPEER>::OnPeerAttach(_In_ int /*_iPeerIndex*/, _In_ TPEER* /*_pPeer*/)
{
}

template <class TPEER>
void NArray<TPEER>::OnPeerDetach(_In_ int /*_iPeerIndex*/, _In_ TPEER* /*_pPeer*/)
{
}


}
}
}