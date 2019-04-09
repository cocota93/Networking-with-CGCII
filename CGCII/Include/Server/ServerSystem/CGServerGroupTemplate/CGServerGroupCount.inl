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

namespace CGServerGroup
{

template <class _TMEMBER, class _TMEMBERBASE>
CCount<_TMEMBER, _TMEMBERBASE>::CCount(int _nMaxMember) : 
	m_countMember(0),
	m_bEnableEnter(false)
{
	// 1) �ִ� Member�� ���� �����Ѵ�.
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

		// 1) ���� ����
		m_bEnableEnter	 = _bEnable;

		// 2) OnOpen�� ȣ���Ѵ�.
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
	// Check) _pMember�� nullptr�ΰ�?
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);
	
	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) �̹� Member�ΰ�?
		RETURN_IF(_pMember->IsMemberOf(this) == true, eOBJECT_RESULT::ALEADY_EXIST);

		// Check) Enter�� ������ �����ΰ�?
		RETURN_IF(m_bEnableEnter==false, eOBJECT_RESULT::FAIL_DISABLED);

		// Check) �� �� �ִ°�?
		RETURN_IF(IsMemberFull(), eOBJECT_RESULT::MEMBER_FULL);

		// 1) OnMemberEntering()�Լ��� ȣ���Ѵ�.
		auto	eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) ���� ���ǿ� ���� �ʴ´�!
		ERROR_RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult, );

		// 2) Add Reference�Ѵ�.
		_pMember->AddRef();

		// 3) ���� Group���� ������.
		_pMember->LeaveGroup();

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// 4) Member Count�� �ϳ� ���δ�.
			++m_countMember;

			// 5) _pMember�� Group�� ������.
			ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);

			// 6) _ProcessMemberEntered()�Լ��� ȣ���Ѵ�.
			try
			{
				_ProcessMemberEntered(_pMember, _Msg);
			}
			// Exception) Rollback
			catch(const std::exception& e)
			{
				// Log)
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Complete[OnMemberEntered] ") _CGFUNCTION);

				// - OnException�� ȣ���Ѵ�.
				auto	bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - ���ڸ� ���δ�.
				--m_countMember;

				// - ObejctGroup�� nullptr�� �����Ѵ�.
				ResetMemberGroup(_pMember);

				// - Member�� Release�Ѵ�.
				_pMember->Release();

				// Check) CGException::ExecuteExceptionHandler���� ó���� ���̸� reraise���� �ʴ´�.
				RETURN_IF(bExecuted, eOBJECT_RESULT::EXCEPTION);

				// Reraise) 
				throw;
			}
		}
	}

	// Result) ��·�� Success!!!
	return	eOBJECT_RESULT::SUCCESS;
}

template <class _TMEMBER, class _TMEMBERBASE>
void CCount<_TMEMBER, _TMEMBERBASE>::ProcessLeaveMember(TMEMBERBASE* _pMember)
{
	// Check) _pMember�� nullptr�ΰ�?
	CGASSERT(_pMember != nullptr,)

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) _pMember�� �� Group�� Member�ΰ�?
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

				// - OnException�� ȣ���Ѵ�.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 2) _pMember�� Group�� Reset
			ResetMemberGroup(_pMember);

			// 3) Member Count���� ����.
			--m_countMember;
		}
		
		// 4) OnMemberLeaved()�Լ��� ȣ���Ѵ�.
		try
		{
			OnMemberLeaved(_pMember, dwResult);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			// Log) 
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

			// - OnException�� ȣ���Ѵ�.
			CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
		}
	}

	// 5) Release�Ѵ�.(Release�� �ݵ�� Critical Section �ۿ��� �Ѵ�.)
	_pMember->Release();
}

template <class _TMEMBER, class _TMEMBERBASE>
void CCount<_TMEMBER, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering�Լ��� ȣ���Ѵ�.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBERBASE>
uintptr_t CCount<_TMEMBER, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving�Լ��� ȣ���Ѵ�.
	return	OnMemberLeaving(_pMember);
}


}