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
CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::CArray(int _nMaxMember) :
	m_countMember(0),
	m_bEnableEnter(false)
{
	// 1) MaxCount�� �����Ѵ�.
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
	// 1) �ִ� Member���� �����Ѵ�.
	m_countMaxMember=_MaxCount; 
	
	// 2) ���� �Ҵ��Ѵ�.
	m_containerMember.assign(_MaxCount, TMEMBER_SET(this));

	// 3) Member Seat��ȣ�� GMD�� �̸� ����´�.
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
			// Check) Member�� ��� ������ �Ѿ��.
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Execute�Լ��� �����Ѵ�.
			bool	result	 = _fCondition(*iter);

			// Check) 
			RETURN_IF(result==true, *iter);

			--iCount;
		}
	}

	// Return) ã�� ���ߴ�..
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
			// Check) Member�� ��� ������ �Ѿ��.
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Execute�Լ��� �����Ѵ�.
			bool	result	 = _fExecute(*iter);

			// Check) 
			RETURN_IF(result==false, false);

			--iCount;
		}
	}

	// Return) ����...
	return	true;
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
typename CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER_DATA& CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::GetMemberData(const TMEMBER* _pMember)
{
	// Return) ���� Member Data�� ��� Return�Ѵ�.		
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
CGPTR<typename CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::SetMember(TMEMBER* _pMember, int _iSeat, CGMSG& _Msg)
{
	// Declare) 
	CGPTR<TMEMBER>	pObjectOld;

	LOCK(ICGServerGroup<TMEMBERBASE>::GetMemberGroupLock(_pMember))
	LOCK(m_csEnter)
	{
		// Check) �̹� �� Group�� ����̸鼭 Seat���� ������?
		ERROR_RETURN_IF(_pMember->IsMemberOf(this) == true && (GetMemberSerial(_pMember) == _iSeat), CGPTR<TMEMBER>(), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGServerGroup: It's same seat position ") _CGFUNCTION));

		// Check) Enter������ �����ΰ�?
		RETURN_IF(m_bEnableEnter==false, CGPTR<TMEMBER>());

		// Check) ���� �� á�°�?
		RETURN_IF(IsMemberFull(), CGPTR<TMEMBER>());

		// Declare) 
		eOBJECT_RESULT	eResult;

		// 1) OnMemberEntering()�Լ��� ȣ���Ѵ�.
		eResult	 = OnMemberEntering(_pMember, _Msg);

		// Check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, CGPTR<TMEMBER>());

		// 2) ���� Seat�� �پ� �ִ� Object�� ������.
		pObjectOld	 = LeaveMemberBySeat(_iSeat);

		// 3) �θ� Group���� ������.(�̰� �߸��ϸ� Dead Lock�� �ɸ� �� �����Ƿ� �����ؾ� ��.)
		if(_pMember != nullptr)
		{
			_pMember->LeaveGroup();
		}

		LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup)
		{
			// 4) ���� �о�´�.
			TMEMBER_SET&	rSeat	 = m_containerMember.at(_iSeat);

			// 5) Node�� _pMember�� �����Ѵ�.
			rSeat	 = _pMember;		// 

			// Check) _pMember�� nullptr�̸� if�ȿ� ������ �������� �ʴ´�.
			RETURN_IF(_pMember == nullptr, pObjectOld)

			// 6) ���ڸ� �ϳ� �ø���.
			++m_countMember;

			// 7) Seat Info�� Push�Ѵ�..
			_pMember->SetMemberSet(&rSeat);

			// 8) _pMember�� Group�� ������.
			ICGServerGroup<TMEMBERBASE>::SetMemberGroupAs((typename _TMEMBER::TGROUPBASE*)this, _pMember);
			
			// 9) ProcessMemberEntered�� ȣ���Ѵ�.
			try
			{
				_ProcessMemberEntered(_pMember, _Msg);
			}
			// Exception) Rollback�Ѵ�.
			catch(const std::exception& e)
			{
				// Trace)
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Complete[OnMemberEntered] ") _CGFUNCTION);

				// Declare) 
				bool	bExecuted;

				// - OnException�� ȣ���Ѵ�.
				bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

				// - Node�� Reset�Ѵ�.
				rSeat.ResetMember();

				// - ���ڸ� ���δ�.
				--m_countMember;

				// - Seat Info�� Pop�Ѵ�.
				_pMember->ResetMemberSet();

				// - ObejctGroup�� nullptr�� �����Ѵ�.
				ResetMemberGroup(_pMember);

				// Check) 
				RETURN_IF(bExecuted, CGPTR<TMEMBER>());

				// Reraise) 
				throw;
			}
		}
	}

	// Result) ��·�� Success!!!
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
			// Check) nullptr�̸� ����...
			CONTINUE_IF((*iter).IsEmpty());

			// 1) Member�� Leave�Ѵ�.
			(*(iter++))->LeaveGroup();

			// 2) ����...
			++i;
		}
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::ProcessLeaveMember(TMEMBERBASE* _pMember)
{
	// Check) _pMember�� nullptr�ΰ�?
	CGASSERT(_pMember != nullptr,)

	//1) Leave�Ѵ�.
	CGPTR<TMEMBER>	pObject	 = LeaveMemberBySeat(GetMemberSerial(_pMember));

	// Check) pObject�� _pMember�� �ݵ�� ���ƾ� �Ѵ�.
	CGASSERT_ERROR(pObject==_pMember);
}


template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
CGPTR<typename CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::TMEMBER> CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::LeaveMemberBySeat(int _iSeat)
{
	// Check) _iSeat�� ������ ����� �Ǿ��°�?
	ERROR_RETURN_IF(_iSeat<0 || _iSeat >= GetMaxMemberCount(), CGPTR<TMEMBER>(), CGLOG_ERROR(DEFAULT_LOGGER, _CGTEXT("(Err ) CGServerGroup: Seat Number(%d) is out of range ") _CGFUNCTION, _iSeat));
	
	// Declare) 
	CGPTR<TMEMBER>	pMember;

	// 1) _iSeat��ġ�� pMember�� ���� ���´�.
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
			// Check) pMember�� �ݵ�� _iSeat�� ���� �����ؾ� �Ѵ�.
			RETURN_IF(pMember!= m_containerMember.at(_iSeat).GetMember(), CGPTR<TMEMBER>());
			
			// 2) OnMemberLeaving()�Լ��� ȣ���Ѵ�.
			try
			{
				dwResult	 = _ProcessMemberLeaving(pMember);
			}
			// Exception) 
			catch(const std::exception& e)
			{
				// - Log
				CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

				// - OnException�� ȣ���Ѵ�.
				CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));
			}

			// 3) Seat���� ���´�.
			TMEMBER_SET&	rSeat	 = m_containerMember.at(_iSeat);

			// 4) Seat�� Node�� nullptr�� �Ѵ�.
			rSeat.ResetMember();

			// 5) Seat Info�� Pop�Ѵ�.
			pMember->ResetMemberSet();

			// 6) pMember�� Group�� ������.
			ResetMemberGroup(pMember);

			// 7) Socket ���ڸ� �ϳ� ���δ�.
			--m_countMember;
		}
		
		// 8) OnMemberLeaved()�Լ��� ȣ���Ѵ�.
		try
		{
			OnMemberLeaved(pMember, dwResult);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			// - Log
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGServerGroup : Occure exception in 'OnMeberLeaved' function on Group ") _CGFUNCTION);

			// - OnException�� ȣ���Ѵ�.
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
		// Check) ���࿡ _iSeat�� 0���� �۰ų� Size()���� ũ�� �׳� nullptr�� Return�Ѵ�.
		RETURN_IF(_iSeat<0 || _iSeat>=static_cast<int>(m_containerMember.size()), CGPTR<TMEMBER>());

		// Return) pMember�� Return�Ѵ�.
		return m_containerMember.at(_iSeat).GetMember();
	}
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
void CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg)
{
	// 1) OnMemberEntering�Լ��� ȣ���Ѵ�.
	OnMemberEntered(_pMember, _Msg);
}

template <class _TMEMBER, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t CArray<_TMEMBER, _TMEMBER_DATA, _TMEMBERBASE>::_ProcessMemberLeaving(TMEMBER* _pMember)
{
	// 1) OnMemberLeaving�Լ��� ȣ���Ѵ�.
	return	OnMemberLeaving(_pMember);
}


}