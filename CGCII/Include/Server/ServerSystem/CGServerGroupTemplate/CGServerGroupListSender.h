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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CListSender
 @brief		링크드-리스트형 멤버 관리에 전체 전송 기능을 추가한 클래스이다.
 @todo		
 @ref		CGServerGroup::CList
 @details	\n
 링크드-리스트형 멤버 관리에 전체전송 기능을 추가한 클래스이다
 Send()함수로 그룹에 전송하게 되면 멤버 전체에게 전송한다.
       
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
	//! @brief 전체 멤버에게 메모리 버퍼의 내용을 전송한다. @param _Buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;
	//! @brief 특정 멤버를 제외한 전체 멤버에게 메모리 버퍼의 전송한다. @param _pExcept 제외할 멤버 @param _Buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
			bool				SendExcept(_In_ TMEMBER* _pExcept, _In_ const CCGBuffer& _Buffer);
	//! @brief 조건을 만족한 멤버에게만 메모리 버퍼의 전송한다. @param _Buffer 전송할 메모리 버퍼 @param _fPred 조건 함수 @return true 성공 @return false 실패
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
	// Check) _Buffer->buf가 nullptr이 아닌가?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len이 0이 아닌가?
	ERROR_RETURN_IF(_Buffer.len==0, false, )
	
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		// - 모든 Member에게 전송한다.
		for(auto& iter: BASEGROUP::m_containerMember)
		{
			iter->Send(_Buffer);
		}
	}

	// Return) 성공...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CListSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SendExcept(_In_ TMEMBER* _pExcept, _In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf가 nullptr이 아닌가?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len이 0이 아닌가?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		auto	iter	 = BASEGROUP::m_containerMember.begin();
		auto	iterEnd	 = BASEGROUP::m_containerMember.end();

		for(; iter!=iterEnd; ++iter)
		{
			// Check) _pExcept일 경우 다음...
			if((*iter).GetMember()==_pExcept)
			{
				++iter;
				break;
			}

			// - 전송한다.
			(*iter)->Send(_Buffer);
		}

		for(; iter!=iterEnd; ++iter)
		{
			// - 전송한다.
			(*iter)->Send(_Buffer);
		}
	}

	// Return) 성공...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CListSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TMEMBER*)>& _fPred)
{
	// Check) _Buffer->buf가 nullptr이 아닌가?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len이 0이 아닌가?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		for(auto& iter: BASEGROUP::m_containerMember)
		{
			// Check) _fPred가 false면 전송하지 않는다.
			CONTINUE_IF(_fPred(iter->GetMember())==false);

			// - 전송한다.
			iter->Send(_Buffer);
		}
	}

	// Return)
	return	true;
}


}