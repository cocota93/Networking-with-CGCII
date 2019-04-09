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
		// 1) �ִ� Member���� �����Ѵ�.
		m_countMaxMember = _MaxCount;

		// 2) ���� �Ҵ��Ѵ�.
		m_containerMember.assign(_MaxCount, TMEMBER_SET(this));

		// 3) Member Seat��ȣ�� GMD�� �̸� ����´�.
		for (int i = 0; i < _MaxCount; ++i)
		{
			m_containerMember.at(i).SetMemberSerial(i);
		}
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
typename CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER_DATA& CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::GetMemberData(const TMEMBER* _pMember)
{
	// Return) ���� Member Data�� ��� Return�Ѵ�.		
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
			// Check) Member�� ��� ������ �Ѿ��.
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Execute�Լ��� �����Ѵ�.
			bool	result	 = _fCondition(iter->GetMember());

			// Check) 
			RETURN_IF(result==true, *iter);

			--iCount;
		}
	}

	// Return) ����...
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
			// Check) Member�� ��� ������ �Ѿ��.
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Execute�Լ��� �����Ѵ�.
			bool	result	 = _fExecute(iter->GetMember());

			// Check) 
			RETURN_IF(result==false, false);

			--iCount;
		}
	}

	// Return) ����...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_AttachMember(TMEMBER* _pMember)
{
	// Declare) 
	int	iSeat;

	// 1) ���ڸ� �ϳ� �ø���.(�̰� ���� ���� �Ѵ�.)
	++m_countMember;

	// 2) Seat�� ��´�.
	iSeat	 = m_seat.alloc_seat();

	// Check) Seat�� -1�̸� Seat�� ���� ���� ���� ���̹Ƿ� �׳� �ǵ�����.
	CGASSERT_ERROR(iSeat>=0);

	// 3) ���� �о�´�.
	TMEMBER_SET&	rSeat	 = m_containerMember.at(iSeat);

	// 4) Seat�� Node�� nullptr�� �Ѵ�.
	rSeat.SetMember(_pMember);

	// 6) Seat Info�� Push�Ѵ�.
	_pMember->SetMemberSet(&rSeat);

	// 7) _pMember�� Group�� ������.(�̰��� ���� �������� �Ѵ�.)
	ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_DetachMember(TMEMBERBASE* _pMember)
{
	// 1) Seat Serial�� ��� ������ ���´�.
	int	iSeat		 = GetMemberSerial(_pMember);

	// 2) ���� �о�´�.
	TMEMBER_SET&	rSeat	 = m_containerMember.at(iSeat);

	// Check) _pMember�� Seat�� �ִ� Object�� ���� ���̾�� �Ѵ�.
	CGASSERT_ERROR(rSeat==_pMember);

	// 3) Seat Info�� Pop�Ѵ�.
	_pMember->ResetMemberSet();

	// 4) _pMember�� Group�� ������.(�̰� ���� ���� �Ѵ�.)
	ICGServerGroup<_TMEMBERBASE>::ResetMemberGroup(_pMember);

	// 5) Seat�� Node�� nullptr�� �Ѵ�.
	rSeat.ResetMember();

	// 6) Seat��ȣ�� �����ش�.
	m_seat.free_seat(iSeat);

	// 7) Socket ���ڸ� �ϳ� ���δ�.(�̰� ���� �������� �Ѵ�.)
	--m_countMember;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
bool CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnableEnter(bool _bEnable)
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
eOBJECT_RESULT CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg)
{
	// Check) _pMember�� nullptr�ΰ�?
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) _pMember�� �̹� Member�ΰ�?
		RETURN_IF(_pMember->IsMemberOf(this) == true, eOBJECT_RESULT::ALEADY_EXIST);

		// Check) _Enter�� �� �ִ� �����ΰ�?
		RETURN_IF(m_bEnableEnter==false, eOBJECT_RESULT::FAIL_DISABLED);

		// Check) �̹� �� á�°�?
		RETURN_IF(IsMemberFull(), eOBJECT_RESULT::MEMBER_FULL);

		// 1) OnMemberEntering�Լ��� ȣ���Ѵ�.
		auto	eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) ���� ���ǿ� ���� �ʴ´�!
		ERROR_RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult, );

		// 2) ���� Group���� ������.
		_pMember->LeaveGroup();

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup);
		{
			// 3) Attach�Ѵ�.
			_AttachMember(_pMember);

			// 4) ProcessMemberEntered�Լ��� ȣ���Ѵ�.
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
				auto	bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - ���ڸ� ���δ�.
				--m_countMember;

				// - Seat Info�� Pop�Ѵ�.
				_DetachMember(_pMember);

				// - ExecuteExceptionHandler���� ó���Ǿ����� Reraise��Ű�� �ʴ´�.
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
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::LeaveAllMember()
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		int	i=GetMemberCount(); 

		for(auto iter=m_containerMember.begin(); i>0;)
		{
			// Check) nullptr�̸� ����...
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Member�� Leave�Ѵ�.
			(*(iter++))->LeaveGroup();

			// 2) ����...
			--i;
		}
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessLeaveMember(TMEMBERBASE* _pMember)
{
	// Check) _pMember�� nullptr�ΰ�?
	CGASSERT(_pMember!=nullptr, );

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) _pMember�� �� Group�� Member�ΰ�?
			ERROR_RETURN_IF(_pMember->IsMemberOf(this) == false, , );

			// 1) ProcessMemberLeaving()�Լ��� ȣ���Ѵ�.
			try
			{
				dwResult	 = _ProcessMemberLeaving(_pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// Log) 
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

				// - OnException�� ȣ���Ѵ�.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 2) Detach�Ѵ�.
			_DetachMember(_pMember);
		}

		// 3) OnMemberLeaved �Լ��� ȣ���Ѵ�.
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
}


template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<typename CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::LeaveMemberBySeat(int _iSeat)
{
	// Check) _iSeat�� ������ ����� �Ǿ��°�?
	ERROR_RETURN_IF(_iSeat<0 || _iSeat >= GetMaxMemberCount(), , );

	// Declare) 
	CGPTR<TMEMBER>	pMember;

	// 1) _iSeat �ڸ��� Member�� ���� ��´�.
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		pMember	 = m_containerMember.at(_iSeat).GetMember();
	}

	// Check) pMember�� empty�� �׳� ������.
	RETURN_IF(pMember.empty(), CGPTR<TMEMBER>());

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(pMember))
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;
	
		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// Check) 
			RETURN_IF(pMember!= m_containerMember.at(_iSeat).GetMember(), CGPTR<TMEMBER>());

			// 1) OnMemberLeaving()�Լ��� ȣ���Ѵ�.
			try
			{
				dwResult	 = OnMemberLeaving(pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// Log) 
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr ) CGServerGroup : Occure exception in 'OnMeberLeaving' function on Group ") _CGFUNCTION);

				// - OnException�� ȣ���Ѵ�.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 2) pMember�� ������.
			_DetachMember(pMember);

			// 3) Member Count�� �ϳ� ���δ�.
			--m_countMember;
		}

		// 4) OnMemberLeaved()�Լ��� ȣ���Ѵ�.
		try
		{
			OnMemberLeaved(pMember, dwResult);
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

	// Return)
	return	pMember;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<typename CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::GetMember(int _iSeat)
{
	LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
	{
		// Check) ���࿡ _iSeat�� 0���� �۰ų� Size()���� ũ�� �׳� nullptr�� Return�Ѵ�.
		RETURN_IF(_iSeat<0 || _iSeat>=static_cast<int>(m_containerMember.size()), CGPTR<TMEMBER>());

		// Return) pMember�� Return�Ѵ�.
		return m_containerMember.at(_iSeat).GetMember();
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering�Լ��� ȣ���Ѵ�.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t CArraySeat<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving�Լ��� ȣ���Ѵ�.
	return	OnMemberLeaving(_pMember);
}


}