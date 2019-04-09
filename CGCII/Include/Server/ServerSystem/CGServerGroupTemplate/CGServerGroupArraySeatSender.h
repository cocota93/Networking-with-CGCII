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

 @class		CArraySeatSender
 @brief		배열형으로 멤버를 관리하는 그룹 클래스로 자리를 자동 결정해준다.
 @todo		
 @ref		CGServerGroup::CArraySeat, CGServerGroup::CArrayDispatchable
 @details	\n
 좌석 배열형 멤버 관리 그룹에 전체 전송 기능을 추가한 클래스이다.
 그룹에 Send()함수를 사용해 전송하면 그룹 전체 멤버에게 전송된다.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA=int, class _TMEMBERBASE= _TMEMBER>
class CArraySeatSender : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>,// (@) Group
	virtual public				CGNet::IO::ISender,						//     Sender Base
	virtual public				CGNet::IO::ISenderPeer					//     Sender Peer
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>		BASEGROUP;
	typedef	_TMEMBER												TMEMBER;
	typedef	_TMEMBERBASE											TMEMBERBASE;
	typedef	_TMEMBER_DATA											TMEMBER_DATA;
	typedef	typename BASEGROUP::TCONTAINER							TCONTAINER;
	typedef typename BASEGROUP::ITERATOR							ITERATOR;
	typedef typename BASEGROUP::CONST_ITERATOR						CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CArraySeatSender(int _nMaxMember = 256);
	virtual	~CArraySeatSender();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief 전체 멤버에게 메모리 버퍼의 내용을 전송한다. @param _Buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer) override;
	//! @brief 특정 멤버에게 메모리 버퍼를 전송한다. @param _iMember 전송할 멤버 인덱스 @param _Buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
	virtual	bool				SendTo(_In_ int _iMember, _In_ const CCGBuffer& _Buffer) override;
	//! @brief 특정 멤버를 제외한 전체 멤버에게 메모리 버퍼의 전송한다. @param _pExcept 제외할 멤버 @param _Buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
			bool				SendExcept(_In_ TMEMBER* _pExcept, _In_ const CCGBuffer& _Buffer);
	//! @brief 조건을 만족한 멤버에게만 메모리 버퍼의 전송한다. @param _Buffer 전송할 메모리 버퍼 @param _fPred 조건 함수 @return true 성공 @return false 실패
			bool				SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TMEMBER*)>& _fPred);
};




template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CArraySeatSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::CArraySeatSender(int _nMaxMember) :
	CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>(_nMaxMember)
{
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CArraySeatSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::~CArraySeatSender()
{
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArraySeatSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::Send(const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf가 nullptr이 아닌가?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len이 0이 아닌가?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int		iCount	 = BASEGROUP::GetMemberCount();

		for(auto iter= BASEGROUP::begin();iCount>0; ++iter)
		{
			CONTINUE_IF((*iter).IsEmpty());

			(*iter)->Send(_Buffer);

			--iCount;
		}
	}

	// Return) 성공...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArraySeatSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SendTo(_In_ int _iIndex, _In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf가 nullptr이 아닌가?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len이 0이 아닌가?
	ERROR_RETURN_IF(_Buffer.len==0, false, )

	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		// Check) _Index가 정당한 범위 내에 있는가?
		ERROR_RETURN_IF(_iIndex<0 || _iIndex>= BASEGROUP::GetMaxMemberCount(), false, )

		// 1) 해당 Member를 얻는다.
		CGPTR<TMEMBER>	pMember	 = BASEGROUP::GetMember(_iIndex);

		// Check)
		RETURN_IF(pMember.empty(), false);

		// 2) 해당 Member에게 전송한다.
		pMember->Send(_Buffer);
	}

	// Return)
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArraySeatSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SendExcept(_In_ TMEMBER* _pExcept, _In_ const CCGBuffer& _Buffer)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		// Declare) 
		int		iCount	 = BASEGROUP::GetMemberCount();

		auto iter		 = BASEGROUP::m_containerMember.begin();
		auto iterEnd	 = BASEGROUP::m_containerMember.end();

		// 1) 제외시킬 객체를 찾기전...(객체를 비교함.)
		for(; iCount>0; ++iter)
		{
			// Check)
			CGASSERT_ERROR(iter!=iterEnd);

			// Check) 
			RETURN_IF(iter==iterEnd, false);

			// Check) nullptr이면 다음...
			CONTINUE_IF((*iter).IsEmpty());

			// - 갯수를 줄인다.
			--iCount;

			// Check) _pExcept일 경우 다음...
			if((*iter).GetMember()==_pExcept)
			{
				++iter;
				break;
			}

			// - Send한다.
			(*iter)->Send(_Buffer);
		}

		// 2) 제외시킬 객체를 찾은 후...(객체 비교없이 바로 전송)
		for(; iCount>0; ++iter)
		{
			// Check)
			CGASSERT_ERROR(iter!=iterEnd);

			// Check) 
			RETURN_IF(iter==iterEnd, false);

			// Check) nullptr이면 다음...
			CONTINUE_IF((*iter).IsEmpty());

			// - 갯수를 줄인다.
			--iCount;

			// - Send한다.
			(*iter)->Send(_Buffer);
		}
	}

	// Return) 성공...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArraySeatSender<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TMEMBER*)>& _fPred)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int		iCount	 = BASEGROUP::GetMemberCount();

		for(auto iter= BASEGROUP::m_containerMember.begin(); iCount>0; ++iter)
		{
			// Check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).IsEmpty());

			// Check) 조건에 맞지 않으면 즉! fPred함수의 결과가 false이면 그냥 넘어간다.
			CONTINUE_IF(_fPred((*iter).GetMember())==false);

			(*iter)->Send(_Buffer);

			--iCount;
		}
	}

	// Return) 성공...
	return	true;
}


}