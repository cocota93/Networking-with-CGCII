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
namespace CGServerGroup
{

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::CList(int _nMaxMember):
	m_bEnableEnter(false)
{
	// 1) 최대 Member의 수를 설정한다.
	SetMaxMemberCount(_nMaxMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::~CList()
{
	LeaveAllMember();
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SetMaxMemberCount(int _MaxCount)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		// 1) 최대 Member수를 설정한다.
		m_countMaxMember	 = _MaxCount;
	
		// 2) Reserve한다.(Reserver함수가 있을 경우에만...)
	#if defined(_MSC_VER)
		__if_exists(TCONTAINER::reserve)
		{
			m_containerMember.reserve((_MaxCount>256) ? 256:_MaxCount);
		}
	#endif
	}
}


template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
typename CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER_DATA& CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::GetMemberData(const TMEMBER* _pMember)
{
	// Return) 현재 Member Data를 즉시 Return한다.		
	return ((TMEMBER_SET*)_pMember->GetMemberSet())->m_MemberData;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<_TMEMBERBASE> CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::FindMember(const std::function<bool (_TMEMBERBASE*)>& _fCondition)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		for(auto& iter:m_containerMember)
		{
			// 1) Execute함수를 실행한다.
			bool	result	 = _fCondition(*iter);

			// Check) 
			RETURN_IF(result==true, *iter);
		}
	}

	// Return) 찾지 못했다..
	return	CGPTR<TMEMBER>();
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ForEachMember(const std::function<bool (_TMEMBERBASE*)>& _fExecute)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		for(auto& iter:m_containerMember)
		{
			// 1) Execute함수를 실행한다.
			bool	result	 = _fExecute(iter.GetMember());

			// Check) 
			RETURN_IF(result==false, false);
		}
	}

	// Return) 성공...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_AttachMemberToListHead(TMEMBER* _pMember)
{
	// 1) Attach를 한다.
	push_front(TMEMBER_SET(this));

	// 2) 값을 읽어온다.
	TMEMBER_SET&	rSeat	 = m_containerMember.back();

	// 3) Detach를 위해 저장해 놓는다.
	rSeat.SetMember(_pMember);
	rSeat.iter	 = m_containerMember.begin();

	// 4) Seat Info를 Push하낟.
	_pMember->SetMemberSet(&rSeat);

	// 5) Object을 설정!
	ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_AttachMemberToListTail(TMEMBER* _pMember)
{
#if defined(_MSC_VER)
	__if_exists(TCONTAINER::attach)
#endif
	{
		// 1) Attach를 한다.
		m_containerMember.push_back(TMEMBER_SET(this));

		// 2) 값을 읽어온다.
		TMEMBER_SET&	rSeat	 = m_containerMember.back();

		// 3) 값을 설정한다.
		rSeat.SetMember(_pMember);
		rSeat.iter	 = --m_containerMember.end();

		// 4) Seat Info를 Push하낟.
		_pMember->SetMemberSet(&rSeat);
	}

	// 5) Object을 설정!
	ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_DetachMember(TMEMBERBASE* _pMember)
{
#if defined(_MSC_VER)
	__if_exists(TCONTAINER::detach)
#endif
	{
		// 1) pMemberData를 얻어낸다.
		TMEMBER_SET*	pMemberSet	 = (TMEMBER_SET*)_pMember->GetMemberSet();

		// 2) Object을 때낸다.
		m_containerMember.erase(pMemberSet->iter);

		// 3) Seat Info를 Pop한다.
		_pMember->ResetMemberSet();
	}

	// 4) ObejctGroup를 nullptr로 설정한다.
	ICGServerGroup<TMEMBERBASE>::ResetMemberGroup(_pMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnableEnter(bool _bEnable)
{
	LOCK(m_csEnter)
	{
		// Check) 
		RETURN_IF(m_bEnableEnter==_bEnable, false);

		// 1) 값을 설정
		m_bEnableEnter	 = _bEnable;

		// 2) OnOpen을 호출한다.
		if(_bEnable)
		{
			OnEnableEnter();
		}
		else
		{
			OnDisableEnter();
		}
	}

	// Return) 
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
eOBJECT_RESULT CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg)
{
	// Check) _pMember가 nullptr인가?
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) 이미 Member인가?
		RETURN_IF(_pMember->IsMemberOf(this) == true, eOBJECT_RESULT::ALEADY_EXIST);

		// Check) Enter가능한 상태인가?
		RETURN_IF(m_bEnableEnter==false, eOBJECT_RESULT::FAIL_DISABLED);

		// Check) 꽉 찼는가?
		RETURN_IF(IsMemberFull(), eOBJECT_RESULT::MEMBER_FULL);

		// 1) OnMemberEntering()함수를 호출한다.
		auto	eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) 입장 조건에 맞지 않는다!
		RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult);
		
		// 2) 이전 Group에서 떼낸다.
		_pMember->LeaveGroup();

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// 3) Attach한다.
			_AttachMember(_pMember);

			// 4) OnMemberEntered()함수를 호출한다. 
			try
			{
				_ProcessMemberEntered(_pMember, _Msg);
			}
			// Exception) Rollback한다.
			catch(const std::exception& e)
			{
				// Trace)
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Complete[OnMemberEntered] ") _CGFUNCTION);

				// - OnException을 호출한다.
				auto	bExecuted = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - Member를 떼낸다.
				_DetachMember(_pMember);

				// Check) CGException::ExecuteExceptionHandler함수에서 처리된 것으로 설정되었다면 reraise하지 않는다.
				RETURN_IF(bExecuted, eOBJECT_RESULT::EXCEPTION);

				// Reraise) 
				throw;
			}
		}
	}
	
	// Return) 성공이닷!!!
	return	eOBJECT_RESULT::SUCCESS;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::LeaveAllMember()
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		for(auto& iter:m_containerMember)
		{
			iter->LeaveGroup();
		}
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessLeaveMember(TMEMBERBASE* _pMember)
{
	// Check) _pMember가 nullptr이어서는 안됀다.
	CGASSERT(_pMember!=nullptr, );

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) _pMember의 Group이 똑같지 않은가?
			ERROR_RETURN_IF(_pMember->IsMemberOf(this) == false, , CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGServerGroup: Not member of Group[%s] ") _CGFUNCTION, GET_NAME(this)));

			// 1) ProcessMemberLeaving()함수를 호출한다.
			try
			{
				dwResult	 = _ProcessMemberLeaving(_pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// Log)
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaving' function on Group ") _CGFUNCTION);

				// - OnException을 호출한다.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 2) Detach한다.
			_DetachMember(_pMember);
		}

		// 3) OnMemberLeaved()함수를 호출한다.
		try
		{
			OnMemberLeaved(_pMember, dwResult);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			// Log) 
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

			// - OnException을 호출한다.
			CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
		}
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering함수를 호출한다.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving함수를 호출한다.
	return	OnMemberLeaving(_pMember);
}


}