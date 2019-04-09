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

 @class		CArray
 @brief		그룹의 멤버가 되기 위한 인터페이스 클래스이다.
 @todo		
 @ref		
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE, class _TGROUPBASE=ICGServerGroup<_TMEMBERBASE>>
class ICGServerGroupable : virtual public ICGReferenceable
{
// ****************************************************************************
// Declare) Member의 Type
// ----------------------------------------------------------------------------
public:
	typedef	_TMEMBERBASE		TMEMBERBASE;
	typedef	_TGROUPBASE			TGROUPBASE;
	typedef CGServerGroup::MEMBER_SET<_TMEMBERBASE>	TMEMBER_SET;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGServerGroupable() : m_pGroupMemberSet(nullptr)			{}
	virtual	~ICGServerGroupable()										{	CGASSERT_ERROR(m_pGroup.empty()); CGASSERT_ERROR(m_pGroupMemberSet==nullptr);}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief 현재 그룹을 얻는다. @return 현재 그룹
			CGPTR<TGROUPBASE>	GetGroup() const						{	return m_pGroup;}
	//! @brief 특정 그룹의 멤버인가를 확인한다. @param _pGroup 그룹 @return true 그룹의 멤버이다. @return false 그룹의 멤버가 아니다.
			bool				IsMemberOf(const ICGServerGroup<_TMEMBERBASE>* _pGroup) const{	return m_pGroup==_pGroup;}

	//! @brief 현재 그룹에서 나온다.
			void				LeaveGroup();

	//! @brief 멤버 데이터를 얻는다. @return 그룹의 멤버 데이터
			TMEMBER_SET*		GetMemberSet() const					{	return m_pGroupMemberSet;}
	//! @brief 멤버 데이터를 nullptr로 리셋한다. 
			void				ResetMemberSet()						{	m_pGroupMemberSet=nullptr;}
	//! @brief 멤버 데이터를 설정한다. @param _pGMD 등록할 '멤버 데이터'
			void				SetMemberSet(TMEMBER_SET* p_pGMD)		{	m_pGroupMemberSet=p_pGMD;}
	//! @brief 멤버 시리얼을 얻는다. @return 멤버 시리얼
			int					GetMemberSerial() const					{	RETURN_IF(m_pGroupMemberSet==nullptr, -1); return m_pGroupMemberSet->GetMemberSerial();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Group(Memberable가 속해있는 Group이다. Group에 속해있지 않으면 nullptr이 된다.)
			CGPTR<TGROUPBASE>	m_pGroup;
			LOCKABLE<>			m_csGroup;

	// 2) Group Member Data(Group에 종속된 Data)
			TMEMBER_SET*		m_pGroupMemberSet;

	// 3) 붙어 있는 Group을 얻고 설정하는 함수.
	//    - SetGroup()과 ResetGroup()은 되도록 Group밖에서는 사용하지 않는 것이 바람직하다.
			template <class TSETGROUP>
			void				_SetGroup(TSETGROUP* _pGroup)			{	m_pGroup=_pGroup;}
			void				_ResetGroup()							{	m_pGroup.reset();}

	// Friend)
	friend	ICGServerGroup<TMEMBERBASE>;
};

template <class _TMEMBERBASE, class _TGROUPBASE>
void ICGServerGroupable<_TMEMBERBASE, _TGROUPBASE>::LeaveGroup()
{
	LOCK(m_csGroup)
	{
		// Declare) 
		CGPTR<TGROUPBASE>	rGroup(m_pGroup);

		// Check) 아에 Group에 속해 있지 않으면 그냥 끝낸다.
		RETURN_IF(rGroup.empty(),);

		// 1) 일단 Group에서 Leave를 먼저 한다.
		TGROUPBASE::RequestLeaveMember(rGroup.get(), (TMEMBERBASE*)this);
	}
}
