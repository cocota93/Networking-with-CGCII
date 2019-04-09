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

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		ICGServerGroup
 @brief		그룹의 기반 인터페이스 클래스이다.
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
// Declare) Member의 Type
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
	//! @brief '멤버 객체'를 입장시킨다. @param _pMember 입장할 '멤버 객체' @param _Msg 입장할 때 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
			eOBJECT_RESULT		EnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) { return ProcessEnterMember(_pMember, _Msg); }
	//! @brief '멤버 객체'를 입장시킨다. 전달되는 _Msg 파라메터는 기본 CGMSG()객체를 임시로 생성해 전달한다. @param _pMember 입장할 '멤버 객체' @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
			eOBJECT_RESULT		EnterMember(TMEMBERBASE* _pMember)			{ CGMSG msg; return ProcessEnterMember(_pMember, msg); }

	//! @brief 그룹에서 '멤버 객체'를 퇴장시킨다. @param _pMember 퇴장할 '멤버 객체' @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
			eOBJECT_RESULT		LeaveMember(TMEMBERBASE* _pMember);

	//! @brief 부모 그룹을 얻는다. @return '부모 그룹' 포인터
			CGPTR<TGROUP>		GetParentGroup() const					{	LOCK(m_csGroup) { return m_pgroupParent;}}
	//! @brief 부모 그룹을 설정한다. @param _pgroupParent 설정할 '부모 그룹 객체'
			void				SetParentGroup(TGROUP* _pgroupParent)	{	LOCK(m_csGroup) { m_pgroupParent=_pgroupParent;}}

	//! @brief 그룹에 락을 건다.
			void				LockGroup()								{	AddRef(); m_csGroup.lock();}
	//! @brief 그룹을 언락한다.
			void				UnlockGroup()							{	m_csGroup.unlock(); Release();}
	//! @brief 그룹의 락을 얻는다.
			LOCKABLE<>&			GetGroupLock()							{	return m_csGroup;}

	//! @brief 입장을 허용한다. @param _pEnable 허용/불허 @return true 성공 @return false 실패
			bool				EnableEnter(bool _bEnable=true)			{	return ProcessEnableEnter(_bEnable);}
	//! @brief 입장을 불허한다. @return true 성공 @return false 실패
			bool				DisableEnter()							{	return ProcessEnableEnter(false);}

	//! @brief 락객체를 얻는다.
								operator LOCKABLE<>&()					{	return m_csGroup;}	// 연산자 overlading(LOCKU용)


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief 입장 가능 여부를 설정하는 과정을 정의한다. @param _pEnable 입장 가능 여부 @return true 성공 @return false 실패
	virtual	bool				ProcessEnableEnter(bool _bEnable) PURE;

	//! @brief 그룹에서 멤버가 입장 처리를 정의한다. @param _Msg 입장할 때 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
	virtual	eOBJECT_RESULT		ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) PURE;

	//! @brief 그룹에서 멤버가 퇴장 처리를 정의한다. @param _pMember 퇴장할 '멤버 객체'
	virtual	void				ProcessLeaveMember(TMEMBERBASE* _pMember) PURE;

protected:
			LOCKABLE<>			m_csGroup;
			CGPTR<TGROUP>		m_pgroupParent;
 
protected:
	// Access 권한 때문에 쓰여지는 함수들이다.
	template <class TGROUP>
	static	void				SetMemberGroupAs(TGROUP* _pGroup, TMEMBERBASE* _pMember)	{	_pMember->_SetGroup(_pGroup);}
	static	void				ResetMemberGroup(TMEMBERBASE* _pMember)		{	_pMember->_ResetGroup();}
	static	LOCKABLE<>&			GetMemberGroupLock(TMEMBERBASE* _pMember)	{	return _pMember->m_csGroup;}

public:
	//! @brief 정적함수) _Group에서 _pMember가 퇴장하기를 요청한다. @param _pGroup 그룹 객체 @param _pMember 멤버 그룹
	static	void				RequestLeaveMember(TGROUP* _pGroup, TMEMBERBASE* _pMember);
};

template <class _TMEMBERBASE>
eOBJECT_RESULT ICGServerGroup<_TMEMBERBASE>::LeaveMember(TMEMBERBASE* _pMember)
{
	// Check)
	RETURN_IF(_pMember==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);

	LOCK(_pMember->m_csGroup)
	{
		// Check) 아에 Group에 속해 있지 않으면 그냥 끝낸다.
		RETURN_IF(_pMember->GetGroup() != this, eOBJECT_RESULT::INVALID_ARGUMENT);

		// 1) 일단 Group에서 Leave를 먼저 한다.
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
