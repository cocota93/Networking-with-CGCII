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

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::CList(int _nMaxMember):
	m_bEnableEnter(false)
{
	// 1) �ִ� Member�� ���� �����Ѵ�.
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
		// 1) �ִ� Member���� �����Ѵ�.
		m_countMaxMember	 = _MaxCount;
	
		// 2) Reserve�Ѵ�.(Reserver�Լ��� ���� ��쿡��...)
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
	// Return) ���� Member Data�� ��� Return�Ѵ�.		
	return ((TMEMBER_SET*)_pMember->GetMemberSet())->m_MemberData;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<_TMEMBERBASE> CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::FindMember(const std::function<bool (_TMEMBERBASE*)>& _fCondition)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		for(auto& iter:m_containerMember)
		{
			// 1) Execute�Լ��� �����Ѵ�.
			bool	result	 = _fCondition(*iter);

			// Check) 
			RETURN_IF(result==true, *iter);
		}
	}

	// Return) ã�� ���ߴ�..
	return	CGPTR<TMEMBER>();
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ForEachMember(const std::function<bool (_TMEMBERBASE*)>& _fExecute)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		for(auto& iter:m_containerMember)
		{
			// 1) Execute�Լ��� �����Ѵ�.
			bool	result	 = _fExecute(iter.GetMember());

			// Check) 
			RETURN_IF(result==false, false);
		}
	}

	// Return) ����...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_AttachMemberToListHead(TMEMBER* _pMember)
{
	// 1) Attach�� �Ѵ�.
	push_front(TMEMBER_SET(this));

	// 2) ���� �о�´�.
	TMEMBER_SET&	rSeat	 = m_containerMember.back();

	// 3) Detach�� ���� ������ ���´�.
	rSeat.SetMember(_pMember);
	rSeat.iter	 = m_containerMember.begin();

	// 4) Seat Info�� Push�ϳ�.
	_pMember->SetMemberSet(&rSeat);

	// 5) Object�� ����!
	ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_AttachMemberToListTail(TMEMBER* _pMember)
{
#if defined(_MSC_VER)
	__if_exists(TCONTAINER::attach)
#endif
	{
		// 1) Attach�� �Ѵ�.
		m_containerMember.push_back(TMEMBER_SET(this));

		// 2) ���� �о�´�.
		TMEMBER_SET&	rSeat	 = m_containerMember.back();

		// 3) ���� �����Ѵ�.
		rSeat.SetMember(_pMember);
		rSeat.iter	 = --m_containerMember.end();

		// 4) Seat Info�� Push�ϳ�.
		_pMember->SetMemberSet(&rSeat);
	}

	// 5) Object�� ����!
	ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_DetachMember(TMEMBERBASE* _pMember)
{
#if defined(_MSC_VER)
	__if_exists(TCONTAINER::detach)
#endif
	{
		// 1) pMemberData�� ����.
		TMEMBER_SET*	pMemberSet	 = (TMEMBER_SET*)_pMember->GetMemberSet();

		// 2) Object�� ������.
		m_containerMember.erase(pMemberSet->iter);

		// 3) Seat Info�� Pop�Ѵ�.
		_pMember->ResetMemberSet();
	}

	// 4) ObejctGroup�� nullptr�� �����Ѵ�.
	ICGServerGroup<TMEMBERBASE>::ResetMemberGroup(_pMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnableEnter(bool _bEnable)
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

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
eOBJECT_RESULT CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg)
{
	// Check) _pMember�� nullptr�ΰ�?
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) �̹� Member�ΰ�?
		RETURN_IF(_pMember->IsMemberOf(this) == true, eOBJECT_RESULT::ALEADY_EXIST);

		// Check) Enter������ �����ΰ�?
		RETURN_IF(m_bEnableEnter==false, eOBJECT_RESULT::FAIL_DISABLED);

		// Check) �� á�°�?
		RETURN_IF(IsMemberFull(), eOBJECT_RESULT::MEMBER_FULL);

		// 1) OnMemberEntering()�Լ��� ȣ���Ѵ�.
		auto	eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult);
		
		// 2) ���� Group���� ������.
		_pMember->LeaveGroup();

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// 3) Attach�Ѵ�.
			_AttachMember(_pMember);

			// 4) OnMemberEntered()�Լ��� ȣ���Ѵ�. 
			try
			{
				_ProcessMemberEntered(_pMember, _Msg);
			}
			// Exception) Rollback�Ѵ�.
			catch(const std::exception& e)
			{
				// Trace)
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Complete[OnMemberEntered] ") _CGFUNCTION);

				// - OnException�� ȣ���Ѵ�.
				auto	bExecuted = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - Member�� ������.
				_DetachMember(_pMember);

				// Check) CGException::ExecuteExceptionHandler�Լ����� ó���� ������ �����Ǿ��ٸ� reraise���� �ʴ´�.
				RETURN_IF(bExecuted, eOBJECT_RESULT::EXCEPTION);

				// Reraise) 
				throw;
			}
		}
	}
	
	// Return) �����̴�!!!
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
	// Check) _pMember�� nullptr�̾�� �ȉ´�.
	CGASSERT(_pMember!=nullptr, );

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) _pMember�� Group�� �Ȱ��� ������?
			ERROR_RETURN_IF(_pMember->IsMemberOf(this) == false, , CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGServerGroup: Not member of Group[%s] ") _CGFUNCTION, GET_NAME(this)));

			// 1) ProcessMemberLeaving()�Լ��� ȣ���Ѵ�.
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

			// 2) Detach�Ѵ�.
			_DetachMember(_pMember);
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
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering�Լ��� ȣ���Ѵ�.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t CList<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving�Լ��� ȣ���Ѵ�.
	return	OnMemberLeaving(_pMember);
}


}