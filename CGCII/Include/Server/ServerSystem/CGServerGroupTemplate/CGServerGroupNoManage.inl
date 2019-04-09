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
CNoManage<_TMEMBER, _TMEMBERBASE>::CNoManage():
	m_bEnableEnter(false)
{
}

template <class _TMEMBER, class _TMEMBERBASE>
CNoManage<_TMEMBER, _TMEMBERBASE>::~CNoManage()
{
}

template <class _TMEMBER, class _TMEMBERBASE>
bool CNoManage<_TMEMBER, _TMEMBERBASE>::ProcessEnableEnter(bool _bEnable)
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
eOBJECT_RESULT CNoManage<_TMEMBER, _TMEMBERBASE>::ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg)
{
	// Check) _pMember�� nullptr�̸� �ȉ´�.
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) �̹� Member�ΰ�?
		RETURN_IF(_pMember->IsMemberOf(this) == true, eOBJECT_RESULT::ALEADY_EXIST);

		// Check) ���� ������ �����ΰ�?
		RETURN_IF(m_bEnableEnter==false, eOBJECT_RESULT::FAIL_DISABLED);

		// 1) OnMemberEntering() �Լ��� ȣ���Ѵ�.
		auto	eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult);

		// 2) Add Reference�Ѵ�.
		_pMember->AddRef();

		// 3) ���� Group���� ������.
		_pMember->LeaveGroup();

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// 4) _pMember�� Group�� ������.
			ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);

			// 5) ProcessMemberEntered()�Լ��� ȣ���Ѵ�.
			try
			{
				_ProcessMemberEntered(_pMember, _Msg);
			}
			// Exception) Rollback�Ѵ�.
			catch(const std::exception& e)
			{
				// Log)
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Complete[OnMemberEntered] ") _CGFUNCTION);

				// - OnException�� ȣ���Ѵ�.
				auto bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - ObejctGroup�� nullptr�� �����Ѵ�.
				ResetMemberGroup(_pMember);

				// - Member�� Release�Ѵ�.
				_pMember->Release();

				// Check) CGException::ExecuteExceptionHandler���� ó���Ǿ��ٸ� Reraise�� ȣ������ �ʴ´�. 
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
void CNoManage<_TMEMBER, _TMEMBERBASE>::ProcessLeaveMember(TMEMBERBASE* _pMember)
{
	// Check) _pMember�� nullptr�̾�� �ȉ´�.
	CGASSERT(_pMember!=nullptr, )
	
	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = eOBJECT_RESULT::EXCEPTION;

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) _pMember�� Member�ΰ�?
			ERROR_RETURN_IF(_pMember->IsMemberOf(this) == false, , CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) Not member of Group[%s] ") _CGFUNCTION, GET_NAME(this)));

			// 1) ProcessMemberLeaving�Լ��� ȣ���Ѵ�.
			try
			{
				dwResult	 = _ProcessMemberLeaving(_pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// Log) 
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaving' function on Group ") _CGFUNCTION);

				// - OnException�� ȣ���Ѵ�.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 2) _pMember�� Group�� ������.
			ResetMemberGroup(_pMember);
		}

		// 3) OnMemberLeaved()�Լ��� ȣ���Ѵ�.
		try
		{
			OnMemberLeaved(_pMember, dwResult);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			// Log) 
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

			// - OnException�� ȣ���Ѵ�.
			CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
		}
	}

	// 4) Release�Ѵ�.(Release�� �ݵ�� Critical Section �ۿ��� �Ѵ�.)
	_pMember->Release();
}

template <class _TMEMBER, class _TMEMBERBASE>
void CNoManage<_TMEMBER, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering�Լ��� ȣ���Ѵ�.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBERBASE>
uintptr_t CNoManage<_TMEMBER, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving�Լ��� ȣ���Ѵ�.
	return	OnMemberLeaving(_pMember);
}


}