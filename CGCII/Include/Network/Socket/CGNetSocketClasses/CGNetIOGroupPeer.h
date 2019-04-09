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
// CGNet::IO::GroupPeer::NArray<T>
//
// 1. CGNet::IO::GroupPeer::CArray��~
//    ���� Peer�� Array���·� �����ϴ� Class�̴�.
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
	// Check) iPeer�� Min�� Max ���̰� �ƴϸ� �ȉ´�!
	CGASSERT_ERROR(_iPeerIndex>=0 && _iPeerIndex<static_cast<int>(m_vectorPeer.size()));

	//  1) Peer ��� Return�ϱ�.
	return		m_vectorPeer.at(_iPeerIndex);
}


template <class TPEER>
CGPTR<TPEER> NArray<TPEER>::GetPeer(_In_ int _iPeerIndex) const
{
	// Check) iPeer�� Min�� Max ���̰� �ƴ� ���� nullptr�� �����Ѵ�.
	RETURN_IF(_iPeerIndex<0 || _iPeerIndex>=static_cast<int>(m_vectorPeer.size()), CGPTR<TPEER>());

	//  1) Peer ��� Return�ϱ�.
	return		m_vectorPeer.at(_iPeerIndex);
}



template <class TPEER>
bool NArray<TPEER>::AttachPeer(_In_ int _iPeerIndex, _In_ TPEER* _pPeer)
{
	// Check) _pPeer�� nullptr�̸� �ȵȴ�.
	CGASSERT(_pPeer != nullptr, false);

	LOCK(m_csvectorPeer)
	{
		// Check) iPeer�� Min�� Max ���̰� �ƴ� ���� false�� �����Ѵ�.
		RETURN_IF(_iPeerIndex<0 || _iPeerIndex>=static_cast<int>(m_vectorPeer.size()), false);

		// Check) 
		RETURN_IF(m_vectorPeer.at(_iPeerIndex)!=nullptr, false);

		// 1) Peer�� list�� �߰��Ѵ�.
		m_vectorPeer.at(_iPeerIndex)	 = _pPeer;

		// 2) Peer�� ��ȣ�� �����.
		_pPeer->SetPeerIndex(_iPeerIndex);

		// 3) OnPeerAttach�Լ��� ȣ���Ѵ�.
		OnPeerAttach(_iPeerIndex, _pPeer);
	}


	// Return) ����!!!
	return	true;
}

template <class TPEER>
CGPTR<TPEER> NArray<TPEER>::DetachPeer(_In_ int _iPeerIndex)
{
	// Declare)
	CGPTR<TPEER>	pPeer;

	LOCK(m_csvectorPeer)
	{
		// Check) iPeer�� Min�� Max ���̿������� �Ѵ�.
		RETURN_IF(_iPeerIndex<0 && _iPeerIndex>=static_cast<int>(m_vectorPeer.size()), CGPTR<TPEER>());

		// 1) Peer�� ��´�.
		pPeer	 = m_vectorPeer.at(_iPeerIndex);

		// Check) 
		RETURN_IF(pPeer.exist(), pPeer);

		// 2) OnPeerDetach�Լ��� ȣ���Ѵ�.
		OnPeerDetach(_iPeerIndex, pPeer);

		// 1) Peer�� list�� �߰��Ѵ�.
		m_vectorPeer.at(_iPeerIndex).reset();

		// 2) Peer�� ��ȣ�� �����.
		pPeer->SetPeerIndex(-1);
	}


	// Return) ����!!!
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
		// 1) vector�� Size�� �����Ѵ�.
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