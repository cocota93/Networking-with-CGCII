//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                         Socket template Classes                           *
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

namespace CGServerObservers
{

//-----------------------------------------------------------------------------
/**

 @class		CList
 @brief		
 @todo		
 @ref		
 @details	\n
 List형 Observer Class 객체
 Group과 다른 점은 독점적이지 않다는 것이다.
 여러개의 Observer에도 붙어서 동작할 수 있다.

*///-----------------------------------------------------------------------------
template <class _TOBSERVER>
class CListSender :
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				CGServerObservers::CList<_TOBSERVER>,	// (I) CGServerObservers::CList
	virtual public				CGNet::IO::ISender						// (I) Sender Base
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CGServerObservers::CList<_TOBSERVER>					BASEOBSERVER;
	typedef	_TOBSERVER												TOBSERVER;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CListSender()												{}
	virtual	~CListSender()												{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief 전체 멤버에게 메모리 버퍼의 내용을 전송한다. @param _Buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer);
	//! @brief 특정 멤버를 제외한 전체 멤버에게 메모리 버퍼의 전송한다. @param _pExcept 제외할 멤버 @param _Buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
			bool				SendExcept(_In_ TOBSERVER* _pExcept, _In_ const CCGBuffer& _Buffer);
	//! @brief 조건을 만족한 멤버에게만 메모리 버퍼의 전송한다. @param _Buffer 전송할 메모리 버퍼 @param _fPred 조건 함수 @return true 성공 @return false 실패
			bool				SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TOBSERVER*)>& _fPred);
};

template <class _TOBSERVER>
bool CListSender<_TOBSERVER>::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf가 nullptr이 아닌가?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len이 0이 아닌가?
	ERROR_RETURN_IF(_Buffer.len==0, false, )
	
	// 1) 모두에게 전송한다.
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		for(auto& iter: BASEOBSERVER::m_containerObserver)
		{
			iter->Send(_Buffer);
		}
	}

	// Return) 성공...
	return	true;
}

template <class _TOBSERVER>
bool CListSender<_TOBSERVER>::SendExcept(_In_ TOBSERVER* _pExcept, _In_ const CCGBuffer& _Buffer)
{
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		auto	iter	 = BASEOBSERVER::m_containerObserver.begin();
		auto	iterEnd	 = BASEOBSERVER::m_containerObserver.end();

		for(; iter!=iterEnd; ++iter)
		{
			// Check) _pExcept일 경우 다음...
			if(*iter==_pExcept)
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

template <class _TOBSERVER>
bool CListSender<_TOBSERVER>::SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TOBSERVER*)>& _fPred)
{
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		for(auto& iter: BASEOBSERVER::m_containerObserver)
		{
			// Check) _fPred가 false면 전송하지 않는다.
			CONTINUE_IF(_fPred(iter)==false);

			// - 전송한다.
			iter->Send(_Buffer);
		}
	}

	// Return) 성공...
	return	true;
}


}