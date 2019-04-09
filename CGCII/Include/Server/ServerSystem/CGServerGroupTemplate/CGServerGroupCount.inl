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

template <class _TMEMBER, class _TMEMBERBASE>
CCount<_TMEMBER, _TMEMBERBASE>::CCount(int _nMaxMember) : 
	m_countMember(0),
	m_bEnableEnter(false)
{
	// 1) 최대 Member의 수를 설정한다.
	SetMaxMemberCount(_nMaxMember);
}

template <class _TMEMBER, class _TMEMBERBASE>
CCount<_TMEMBER, _TMEMBERBASE>::~CCount()
{
}

template <class _TMEMBER, class _TMEMBERBASE>
bool CCount<_TMEMBER, _TMEMBERBASE>::ProcessEnableEnter(bool _bEnable)
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

template <class _TMEMBER, class _TMEMBERBASE>
eOBJECT_RESULT CCount<_TMEMBER, _TMEMBERBASE>::ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg)
{
	// Check) _pMember가 nullptr인가?
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);
	
	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) 이미 Member인가?
		RETURN_IF(_pMember->IsMemberOf(this) == true, eOBJECT_RESULT::ALEADY_EXIST);

		// Check) Enter가 가능한 상태인가?
		RETURN_IF(m_bEnableEnter==false, eOBJECT_RESULT::FAIL_DISABLED);

		// Check) 꽉 차 있는가?
		RETURN_IF(IsMemberFull(), eOBJECT_RESULT::MEMBER_FULL);

		// 1) OnMemberEntering()함수를 호출한다.
		auto	eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) 입장 조건에 맞지 않는다!
		ERROR_RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult, );

		// 2) Add Reference한다.
		_pMember->AddRef();

		// 3) 이전 Group에서 떼낸다.
		_pMember->LeaveGroup();

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// 4) Member Count를 하나 줄인다.
			++m_countMember;

			// 5) _pMember의 Group을 설정함.
			ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);

			// 6) _ProcessMemberEntered()함수를 호출한다.
			try
			{
				_ProcessMemberEntered(_pMember, _Msg);
			}
			// Exception) Rollback
			catch(const std::exception& e)
			{
				// Log)
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Complete[OnMemberEntered] ") _CGFUNCTION);

				// - OnException을 호출한다.
				auto	bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - 숫자를 줄인다.
				--m_countMember;

				// - ObejctGroup를 nullptr로 설정한다.
				ResetMemberGroup(_pMember);

				// - Member를 Release한다.
				_pMember->Release();

				// Check) CGException::ExecuteExceptionHandler에서 처리된 것이면 reraise하지 않는다.
				RETURN_IF(bExecuted, eOBJECT_RESULT::EXCEPTION);

				// Reraise) 
				throw;
			}
		}
	}

	// Result) 어쨌든 Success!!!
	return	eOBJECT_RESULT::SUCCESS;
}

template <class _TMEMBER, class _TMEMBERBASE>
void CCount<_TMEMBER, _TMEMBERBASE>::ProcessLeaveMember(TMEMBERBASE* _pMember)
{
	// Check) _pMember가 nullptr인가?
	CGASSERT(_pMember != nullptr,)

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) _pMember가 현 Group의 Member인가?
			ERROR_RETURN_IF(_pMember->IsMemberOf(this)==false, , CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) Not member of Group ") _CGFUNCTION, GET_NAME(this)));

			// 1) Call OnMemberLeaving
			try
			{
				dwResult	 = _ProcessMemberLeaving(_pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// - Log
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaving' function on Group ") _CGFUNCTION);

				// - OnException을 호출한다.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 2) _pMember의 Group을 Reset
			ResetMemberGroup(_pMember);

			// 3) Member Count수를 줄임.
			--m_countMember;
		}
		
		// 4) OnMemberLeaved()함수를 호출한다.
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

	// 5) Release한다.(Release는 반드시 Critical Section 밖에서 한다.)
	_pMember->Release();
}

template <class _TMEMBER, class _TMEMBERBASE>
void CCount<_TMEMBER, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering함수를 호출한다.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBERBASE>
uintptr_t CCount<_TMEMBER, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving함수를 호출한다.
	return	OnMemberLeaving(_pMember);
}


}