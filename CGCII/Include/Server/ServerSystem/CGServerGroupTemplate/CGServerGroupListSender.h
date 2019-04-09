//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Group Template Classes                           *
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

namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CListSender
 @brief		��ũ��-����Ʈ�� ��� ������ ��ü ���� ����� �߰��� Ŭ�����̴�.
 @todo		
 @ref		CGServerGroup::CList
 @details	\n
 ��ũ��-����Ʈ�� ��� ������ ��ü���� ����� �߰��� Ŭ�����̴�
 Send()�Լ��� �׷쿡 �����ϰ� �Ǹ� ��� ��ü���� �����Ѵ�.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA=int, class _TMEMBERBASE=_TMEMBER>
class CListSender : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>,// (@) Group List
	virtual public				CGNet::IO::ISender						//     Sender
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>			BASEGROUP;
	typedef	_TMEMBER												TMEMBER;
	typedef	_TMEMBERBASE											TMEMBERBASE;
	typedef	_TMEMBER_DATA											TMEMBER_DATA;
	typedef typename BASEGROUP::ITERATOR							ITERATOR;
	typedef typename BASEGROUP::CONST_ITERATOR						CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CListSender(int _nMaxMember=INT_MAX);
	virtual	~CListSender()												{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief ��ü ������� �޸� ������ ������ �����Ѵ�. @param _Buffer ������ �޸� ���� @return true ���� @return false ����
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;
	//! @brief Ư�� ����� ������ ��ü ������� �޸� ������ �����Ѵ�. @param _pExcept ������ ��� @param _Buffer ������ �޸� ���� @return true ���� @return false ����
			bool				SendExcept(_In_ TMEMBER* _pExcept, _In_ const CCGBuffer& _Buffer);
	//! @brief ������ ������ ������Ը� �޸� ������ �����Ѵ�. @param _Buffer ������ �޸� ���� @param _fPred ���� �Լ� @return true ���� @return false ����
			bool				SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TMEMBER*)>& _fPred);
};

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CListSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::CListSender(int _nMaxMember) :
	CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>(_nMaxMember)
{
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CListSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf�� nullptr�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len�� 0�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.len==0, false, )
	
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		// - ��� Member���� �����Ѵ�.
		for(auto& iter: BASEGROUP::m_containerMember)
		{
			iter->Send(_Buffer);
		}
	}

	// Return) ����...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CListSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SendExcept(_In_ TMEMBER* _pExcept, _In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf�� nullptr�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len�� 0�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		auto	iter	 = BASEGROUP::m_containerMember.begin();
		auto	iterEnd	 = BASEGROUP::m_containerMember.end();

		for(; iter!=iterEnd; ++iter)
		{
			// Check) _pExcept�� ��� ����...
			if((*iter).GetMember()==_pExcept)
			{
				++iter;
				break;
			}

			// - �����Ѵ�.
			(*iter)->Send(_Buffer);
		}

		for(; iter!=iterEnd; ++iter)
		{
			// - �����Ѵ�.
			(*iter)->Send(_Buffer);
		}
	}

	// Return) ����...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CListSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TMEMBER*)>& _fPred)
{
	// Check) _Buffer->buf�� nullptr�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len�� 0�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		for(auto& iter: BASEGROUP::m_containerMember)
		{
			// Check) _fPred�� false�� �������� �ʴ´�.
			CONTINUE_IF(_fPred(iter->GetMember())==false);

			// - �����Ѵ�.
			iter->Send(_Buffer);
		}
	}

	// Return)
	return	true;
}


}