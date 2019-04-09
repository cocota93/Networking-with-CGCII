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

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		ICGServerGroup
 @brief		�׷��� ��� �������̽� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE>
class ICGServerGroup :
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable							// (I) Reference Count
{
// ****************************************************************************
// Declare) Member�� Type
// ----------------------------------------------------------------------------
public:
	typedef	_TMEMBERBASE		TMEMBERBASE;
	typedef	typename _TMEMBERBASE::TGROUPBASE	TGROUP;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGServerGroup()											{}
	virtual	~ICGServerGroup()											{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief '��� ��ü'�� �����Ų��. @param _pMember ������ '��� ��ü' @param _Msg ������ �� ������ �޽��� @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
			eOBJECT_RESULT		EnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) { return ProcessEnterMember(_pMember, _Msg); }
	//! @brief '��� ��ü'�� �����Ų��. ���޵Ǵ� _Msg �Ķ���ʹ� �⺻ CGMSG()��ü�� �ӽ÷� ������ �����Ѵ�. @param _pMember ������ '��� ��ü' @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
			eOBJECT_RESULT		EnterMember(TMEMBERBASE* _pMember)			{ CGMSG msg; return ProcessEnterMember(_pMember, msg); }

	//! @brief �׷쿡�� '��� ��ü'�� �����Ų��. @param _pMember ������ '��� ��ü' @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
			eOBJECT_RESULT		LeaveMember(TMEMBERBASE* _pMember);

	//! @brief �θ� �׷��� ��´�. @return '�θ� �׷�' ������
			CGPTR<TGROUP>		GetParentGroup() const					{	LOCK(m_csGroup) { return m_pgroupParent;}}
	//! @brief �θ� �׷��� �����Ѵ�. @param _pgroupParent ������ '�θ� �׷� ��ü'
			void				SetParentGroup(TGROUP* _pgroupParent)	{	LOCK(m_csGroup) { m_pgroupParent=_pgroupParent;}}

	//! @brief �׷쿡 ���� �Ǵ�.
			void				LockGroup()								{	AddRef(); m_csGroup.lock();}
	//! @brief �׷��� ����Ѵ�.
			void				UnlockGroup()							{	m_csGroup.unlock(); Release();}
	//! @brief �׷��� ���� ��´�.
			LOCKABLE<>&			GetGroupLock()							{	return m_csGroup;}

	//! @brief ������ ����Ѵ�. @param _pEnable ���/���� @return true ���� @return false ����
			bool				EnableEnter(bool _bEnable=true)			{	return ProcessEnableEnter(_bEnable);}
	//! @brief ������ �����Ѵ�. @return true ���� @return false ����
			bool				DisableEnter()							{	return ProcessEnableEnter(false);}

	//! @brief ����ü�� ��´�.
								operator LOCKABLE<>&()					{	return m_csGroup;}	// ������ overlading(LOCKU��)


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief ���� ���� ���θ� �����ϴ� ������ �����Ѵ�. @param _pEnable ���� ���� ���� @return true ���� @return false ����
	virtual	bool				ProcessEnableEnter(bool _bEnable) PURE;

	//! @brief �׷쿡�� ����� ���� ó���� �����Ѵ�. @param _Msg ������ �� ������ �޽��� @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
	virtual	eOBJECT_RESULT		ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) PURE;

	//! @brief �׷쿡�� ����� ���� ó���� �����Ѵ�. @param _pMember ������ '��� ��ü'
	virtual	void				ProcessLeaveMember(TMEMBERBASE* _pMember) PURE;

protected:
			LOCKABLE<>			m_csGroup;
			CGPTR<TGROUP>		m_pgroupParent;
 
protected:
	// Access ���� ������ �������� �Լ����̴�.
	template <class TGROUP>
	static	void				SetMemberGroupAs(TGROUP* _pGroup, TMEMBERBASE* _pMember)	{	_pMember->_SetGroup(_pGroup);}
	static	void				ResetMemberGroup(TMEMBERBASE* _pMember)		{	_pMember->_ResetGroup();}
	static	LOCKABLE<>&			GetMemberGroupLock(TMEMBERBASE* _pMember)	{	return _pMember->m_csGroup;}

public:
	//! @brief �����Լ�) _Group���� _pMember�� �����ϱ⸦ ��û�Ѵ�. @param _pGroup �׷� ��ü @param _pMember ��� �׷�
	static	void				RequestLeaveMember(TGROUP* _pGroup, TMEMBERBASE* _pMember);
};

template <class _TMEMBERBASE>
eOBJECT_RESULT ICGServerGroup<_TMEMBERBASE>::LeaveMember(TMEMBERBASE* _pMember)
{
	// Check)
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);

	LOCK(_pMember->m_csGroup)
	{
		// Check) �ƿ� Group�� ���� ���� ������ �׳� ������.
		RETURN_IF(_pMember->GetGroup() != this, eOBJECT_RESULT::INVALID_ARGUMENT);

		// 1) �ϴ� Group���� Leave�� ���� �Ѵ�.
		ProcessLeaveMember(_pMember);
	}

	// Return) 
	return	eOBJECT_RESULT::SUCCESS;
}

template <class _TMEMBERBASE>
void ICGServerGroup<_TMEMBERBASE>::RequestLeaveMember(TGROUP* _pGroup, TMEMBERBASE* _pMember)
{
	// Check)
	CGASSERT_ERROR(_pGroup!=nullptr); 

	// Check)
	ERROR_RETURN_IF(_pGroup==nullptr, , );

	// 1) Process...
	((ICGServerGroup<_TMEMBERBASE>*)_pGroup)->ProcessLeaveMember(_pMember);
}
