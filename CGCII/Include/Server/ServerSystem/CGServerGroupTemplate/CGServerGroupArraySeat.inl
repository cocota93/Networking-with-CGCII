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
CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::CArraySeat(int _nMaxMember) :
	m_seat(_nMaxMember),
	m_bEnableEnter(false),
	m_countMember(0)
{
	SetMaxMemberCount(_nMaxMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::~CArraySeat()
{
	LeaveAllMember();
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SetMaxMemberCount(int _MaxCount)
{
	LOCK(m_csGroup)
	{
		// 1) 최대 Member수를 설정한다.
		m_countMaxMember = _MaxCount;

		// 2) 새로 할당한다.
		m_containerMember.assign(_MaxCount, TMEMBER_SET(this));

		// 3) Member Seat번호는 GMD에 미리 써놓는다.
		for (int i = 0; i < _MaxCount; ++i)
		{
			m_containerMember.at(i).SetMemberSerial(i);
		}
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
typename CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER_DATA& CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::GetMemberData(const TMEMBER* _pMember)
{
	// Return) 현재 Member Data를 즉시 Return한다.		
	return ((TMEMBER_SET*)_pMember->GetMemberSet())->m_MemberData;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<_TMEMBERBASE> CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::FindMember(const std::function<bool (_TMEMBERBASE*)>& _fCondition)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int		iCount	 = GetMemberCount();

		for(auto iter=m_containerMember.begin(); iCount>0; ++iter)
		{
			// Check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Execute함수를 실행한다.
			bool	result	 = _fCondition(iter->GetMember());

			// Check) 
			RETURN_IF(result==true, *iter);

			--iCount;
		}
	}

	// Return) 성공...
	return	CGPTR<_TMEMBERBASE>();
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ForEachMember(const std::function<bool (_TMEMBERBASE*)>& _fExecute)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int		iCount	 = GetMemberCount();

		for(auto iter=m_containerMember.begin(); iCount>0; ++iter)
		{
			// Check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Execute함수를 실행한다.
			bool	result	 = _fExecute(iter->GetMember());

			// Check) 
			RETURN_IF(result==false, false);

			--iCount;
		}
	}

	// Return) 성공...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_AttachMember(TMEMBER* _pMember)
{
	// Declare) 
	int	iSeat;

	// 1) 숫자를 하나 늘린다.(이걸 제일 먼저 한다.)
	++m_countMember;

	// 2) Seat를 얻는다.
	iSeat	 = m_seat.alloc_seat();

	// Check) Seat가 -1이면 Seat가 남아 있지 않은 것이므로 그냥 되돌린다.
	CGASSERT_ERROR(iSeat>=0);

	// 3) 값을 읽어온다.
	TMEMBER_SET&	rSeat	 = m_containerMember.at(iSeat);

	// 4) Seat의 Node를 nullptr을 한다.
	rSeat.SetMember(_pMember);

	// 6) Seat Info를 Push한다.
	_pMember->SetMemberSet(&rSeat);

	// 7) _pMember의 Group을 설정함.(이것을 제일 마지막에 한다.)
	ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_DetachMember(TMEMBERBASE* _pMember)
{
	// 1) Seat Serial을 잠시 저장해 놓는다.
	int	iSeat		 = GetMemberSerial(_pMember);

	// 2) 값을 읽어온다.
	TMEMBER_SET&	rSeat	 = m_containerMember.at(iSeat);

	// Check) _pMember와 Seat에 있는 Object가 같은 것이어야 한다.
	CGASSERT_ERROR(rSeat==_pMember);

	// 3) Seat Info를 Pop한다.
	_pMember->ResetMemberSet();

	// 4) _pMember의 Group을 해제함.(이걸 제일 먼저 한다.)
	ICGServerGroup<_TMEMBERBASE>::ResetMemberGroup(_pMember);

	// 5) Seat의 Node를 nullptr을 한다.
	rSeat.ResetMember();

	// 6) Seat번호를 돌려준다.
	m_seat.free_seat(iSeat);

	// 7) Socket 숫자를 하나 줄인다.(이걸 제일 마지막에 한다.)
	--m_countMember;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnableEnter(bool _bEnable)
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
eOBJECT_RESULT CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg)
{
	// Check) _pMember가 nullptr인가?
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) _pMember가 이미 Member인가?
		RETURN_IF(_pMember->IsMemberOf(this) == true, eOBJECT_RESULT::ALEADY_EXIST);

		// Check) _Enter할 수 있는 상태인가?
		RETURN_IF(m_bEnableEnter==false, eOBJECT_RESULT::FAIL_DISABLED);

		// Check) 이미 꽉 찼는가?
		RETURN_IF(IsMemberFull(), eOBJECT_RESULT::MEMBER_FULL);

		// 1) OnMemberEntering함수를 호출한다.
		auto	eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) 입장 조건에 맞지 않는다!
		ERROR_RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult, );

		// 2) 이전 Group에서 떼낸다.
		_pMember->LeaveGroup();

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup);
		{
			// 3) Attach한다.
			_AttachMember(_pMember);

			// 4) ProcessMemberEntered함수를 호출한다.
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
				auto	bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - 숫자를 줄인다.
				--m_countMember;

				// - Seat Info를 Pop한다.
				_DetachMember(_pMember);

				// - ExecuteExceptionHandler에서 처리되었으면 Reraise시키지 않는다.
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
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::LeaveAllMember()
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int	i=GetMemberCount(); 

		for(auto iter=m_containerMember.begin(); i>0;)
		{
			// Check) nullptr이면 다음...
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Member를 Leave한다.
			(*(iter++))->LeaveGroup();

			// 2) 증가...
			--i;
		}
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessLeaveMember(TMEMBERBASE* _pMember)
{
	// Check) _pMember가 nullptr인가?
	CGASSERT(_pMember!=nullptr, );

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) _pMember가 이 Group에 Member인가?
			ERROR_RETURN_IF(_pMember->IsMemberOf(this) == false, , );

			// 1) ProcessMemberLeaving()함수를 호출한다.
			try
			{
				dwResult	 = _ProcessMemberLeaving(_pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// Log) 
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

				// - OnException을 호출한다.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 2) Detach한다.
			_DetachMember(_pMember);
		}

		// 3) OnMemberLeaved 함수를 호출한다.
		try
		{
			OnMemberLeaved(_pMember, dwResult);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			// Log) 
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

			// - OnException을 호출한다.
			CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
		}
	}
}


template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<typename CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::LeaveMemberBySeat(int _iSeat)
{
	// Check) _iSeat의 범위가 제대로 되었는가?
	ERROR_RETURN_IF(_iSeat<0 || _iSeat >= GetMaxMemberCount(), , );

	// Declare) 
	CGPTR<TMEMBER>	pMember;

	// 1) _iSeat 자리의 Member를 먼저 얻는다.
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		pMember	 = m_containerMember.at(_iSeat).GetMember();
	}

	// Check) pMember가 empty면 그냥 끝낸다.
	RETURN_IF(pMember.empty(), CGPTR<TMEMBER>());

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;
	
		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) 
			RETURN_IF(pMember!= m_containerMember.at(_iSeat).GetMember(), CGPTR<TMEMBER>());

			// 1) OnMemberLeaving()함수를 호출한다.
			try
			{
				dwResult	 = OnMemberLeaving(pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// Log) 
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaving' function on Group ") _CGFUNCTION);

				// - OnException을 호출한다.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 2) pMember를 떼낸다.
			_DetachMember(pMember);

			// 3) Member Count를 하나 줄인다.
			--m_countMember;
		}

		// 4) OnMemberLeaved()함수를 호출한다.
		try
		{
			OnMemberLeaved(pMember, dwResult);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			// Log)
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

			// - OnException을 호출한다.
			CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
		}
	}

	// Return)
	return	pMember;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<typename CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::GetMember(int _iSeat)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		// Check) 만약에 _iSeat가 0보다 작거나 Size()보다 크면 그냥 nullptr을 Return한다.
		RETURN_IF(_iSeat<0 || _iSeat>=static_cast<int>(m_containerMember.size()), CGPTR<TMEMBER>());

		// Return) pMember를 Return한다.
		return m_containerMember.at(_iSeat).GetMember();
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering함수를 호출한다.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving함수를 호출한다.
	return	OnMemberLeaving(_pMember);
}


}