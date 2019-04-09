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
CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::CArray(int _nMaxMember) :
	m_countMember(0),
	m_bEnableEnter(false)
{
	// 1) MaxCount를 설정한다.
	SetMaxMemberCount(_nMaxMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::~CArray()
{
	LeaveAllMember();
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SetMaxMemberCount(int _MaxCount)
{
	// 1) 최대 Member수를 설정한다.
	m_countMaxMember=_MaxCount; 
	
	// 2) 새로 할당한다.
	m_containerMember.assign(_MaxCount, TMEMBER_SET(this));

	// 3) Member Seat번호는 GMD에 미리 써놓는다.
	for(int i=0; i<_MaxCount; ++i)
	{
		m_containerMember.at(i).SetMemberSerial(i);
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<_TMEMBERBASE> CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::FindMember(const std::function<bool (_TMEMBERBASE*)>& _fCondition)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int		iCount	 = GetMemberCount();

		for(auto iter=m_containerMember.begin(); iCount>0; ++iter)
		{
			// Check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Execute함수를 실행한다.
			bool	result	 = _fCondition(*iter);

			// Check) 
			RETURN_IF(result==true, *iter);

			--iCount;
		}
	}

	// Return) 찾지 못했다..
	return	CGPTR<_TMEMBERBASE>();
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ForEachMember(const std::function<bool (_TMEMBERBASE*)>& _fExecute)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int		iCount	 = GetMemberCount();

		for(auto iter=m_containerMember.begin(); iCount>0; ++iter)
		{
			// Check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Execute함수를 실행한다.
			bool	result	 = _fExecute(*iter);

			// Check) 
			RETURN_IF(result==false, false);

			--iCount;
		}
	}

	// Return) 성공...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
typename CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER_DATA& CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::GetMemberData(const TMEMBER* _pMember)
{
	// Return) 현재 Member Data를 즉시 Return한다.		
	return ((TMEMBER_SET*)_pMember->GetMemberSet())->m_MemberData;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
eOBJECT_RESULT CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnterMember(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/)
{
	throw	CGException::CThrow_AccessDenied();
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnableEnter(bool _bEnable)
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
CGPTR<typename CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SetMember(TMEMBER* _pMember, int _iSeat, CGMSG& _Msg)
{
	// Declare) 
	CGPTR<TMEMBER>	pObjectOld;

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) 이미 현 Group의 멤버이면서 Seat까지 같은가?
		ERROR_RETURN_IF(_pMember->IsMemberOf(this) == true && (GetMemberSerial(_pMember) == _iSeat), CGPTR<TMEMBER>(), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGServerGroup: It's same seat position ") _CGFUNCTION));

		// Check) Enter가능한 상태인가?
		RETURN_IF(m_bEnableEnter==false, CGPTR<TMEMBER>());

		// Check) 방이 꽉 찼는가?
		RETURN_IF(IsMemberFull(), CGPTR<TMEMBER>());

		// Declare) 
		eOBJECT_RESULT	eResult;

		// 1) OnMemberEntering()함수를 호출한다.
		eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) 입장 조건에 맞지 않는다!
		RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, CGPTR<TMEMBER>());

		// 2) 현재 Seat에 붙어 있는 Object를 떼낸다.
		pObjectOld	 = LeaveMemberBySeat(_iSeat);

		// 3) 부모 Group에서 떼낸다.(이거 잘못하면 Dead Lock이 걸릴 수 있으므로 주의해야 함.)
		if(_pMember != nullptr)
		{
			_pMember->LeaveGroup();
		}

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// 4) 값을 읽어온다.
			TMEMBER_SET&	rSeat	 = m_containerMember.at(_iSeat);

			// 5) Node에 _pMember을 설정한다.
			rSeat	 = _pMember;		// 

			// Check) _pMember가 nullptr이면 if안에 내용은 실행하지 않는다.
			RETURN_IF(_pMember == nullptr, pObjectOld)

			// 6) 숫자를 하나 늘린다.
			++m_countMember;

			// 7) Seat Info를 Push한다..
			_pMember->SetMemberSet(&rSeat);

			// 8) _pMember의 Group을 설정함.
			ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);
			
			// 9) ProcessMemberEntered를 호출한다.
			try
			{
				_ProcessMemberEntered(_pMember, _Msg);
			}
			// Exception) Rollback한다.
			catch(const std::exception& e)
			{
				// Trace)
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Complete[OnMemberEntered] ") _CGFUNCTION);

				// Declare) 
				bool	bExecuted;

				// - OnException을 호출한다.
				bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - Node를 Reset한다.
				rSeat.ResetMember();

				// - 숫자를 줄인다.
				--m_countMember;

				// - Seat Info를 Pop한다.
				_pMember->ResetMemberSet();

				// - ObejctGroup를 nullptr로 설정한다.
				ResetMemberGroup(_pMember);

				// Check) 
				RETURN_IF(bExecuted, CGPTR<TMEMBER>());

				// Reraise) 
				throw;
			}
		}
	}

	// Result) 어쨌든 Success!!!
	return	pObjectOld;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::LeaveAllMember()
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int	i=0; 

		for(auto iter=m_containerMember.begin(); i<GetMemberCount();)
		{
			// Check) nullptr이면 다음...
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Member를 Leave한다.
			(*(iter++))->LeaveGroup();

			// 2) 증가...
			++i;
		}
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessLeaveMember(TMEMBERBASE* _pMember)
{
	// Check) _pMember이 nullptr인가?
	CGASSERT(_pMember != nullptr,)

	//1) Leave한다.
	CGPTR<TMEMBER>	pObject	 = LeaveMemberBySeat(GetMemberSerial(_pMember));

	// Check) pObject와 _pMember는 반드시 같아야 한다.
	CGASSERT_ERROR(pObject==_pMember);
}


template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<typename CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::LeaveMemberBySeat(int _iSeat)
{
	// Check) _iSeat의 범위가 제대로 되었는가?
	ERROR_RETURN_IF(_iSeat<0 || _iSeat >= GetMaxMemberCount(), CGPTR<TMEMBER>(), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGServerGroup: Seat Number(%d) is out of range ") _CGFUNCTION, _iSeat));
	
	// Declare) 
	CGPTR<TMEMBER>	pMember;

	// 1) _iSeat위치의 pMember를 먼저 얻어온다.
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		pMember	 = m_containerMember.at(_iSeat).GetMember();
	}

	// Check) 
	RETURN_IF(pMember.empty(), CGPTR<TMEMBER>());

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) pMember는 반드시 _iSeat의 값과 동일해야 한다.
			RETURN_IF(pMember!= m_containerMember.at(_iSeat).GetMember(), CGPTR<TMEMBER>());
			
			// 2) OnMemberLeaving()함수를 호출한다.
			try
			{
				dwResult	 = _ProcessMemberLeaving(pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// - Log
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

				// - OnException을 호출한다.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 3) Seat값을 얻어온다.
			TMEMBER_SET&	rSeat	 = m_containerMember.at(_iSeat);

			// 4) Seat의 Node를 nullptr을 한다.
			rSeat.ResetMember();

			// 5) Seat Info를 Pop한다.
			pMember->ResetMemberSet();

			// 6) pMember의 Group을 해제함.
			ResetMemberGroup(pMember);

			// 7) Socket 숫자를 하나 줄인다.
			--m_countMember;
		}
		
		// 8) OnMemberLeaved()함수를 호출한다.
		try
		{
			OnMemberLeaved(pMember, dwResult);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			// - Log
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

			// - OnException을 호출한다.
			CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
		}
	}

	// Result) Success!!!
	return	pMember;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<typename CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::GetMember(int _iSeat)
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
void CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering함수를 호출한다.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving함수를 호출한다.
	return	OnMemberLeaving(_pMember);
}


}