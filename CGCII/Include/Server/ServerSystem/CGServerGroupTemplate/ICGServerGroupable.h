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

 @class		CArray
 @brief		�׷��� ����� �Ǳ� ���� �������̽� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE, class _TGROUPBASE=ICGServerGroup<_TMEMBERBASE>>
class ICGServerGroupable : virtual public ICGReferenceable
{
// ****************************************************************************
// Declare) Member�� Type
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
	//! @brief ���� �׷��� ��´�. @return ���� �׷�
			CGPTR<TGROUPBASE>	GetGroup() const						{	return m_pGroup;}
	//! @brief Ư�� �׷��� ����ΰ��� Ȯ���Ѵ�. @param _pGroup �׷� @return true �׷��� ����̴�. @return false �׷��� ����� �ƴϴ�.
			bool				IsMemberOf(const ICGServerGroup<_TMEMBERBASE>* _pGroup) const{	return m_pGroup==_pGroup;}

	//! @brief ���� �׷쿡�� ���´�.
			void				LeaveGroup();

	//! @brief ��� �����͸� ��´�. @return �׷��� ��� ������
			TMEMBER_SET*		GetMemberSet() const					{	return m_pGroupMemberSet;}
	//! @brief ��� �����͸� nullptr�� �����Ѵ�. 
			void				ResetMemberSet()						{	m_pGroupMemberSet=nullptr;}
	//! @brief ��� �����͸� �����Ѵ�. @param _pGMD ����� '��� ������'
			void				SetMemberSet(TMEMBER_SET* p_pGMD)		{	m_pGroupMemberSet=p_pGMD;}
	//! @brief ��� �ø����� ��´�. @return ��� �ø���
			int					GetMemberSerial() const					{	RETURN_IF(m_pGroupMemberSet==nullptr, -1); return m_pGroupMemberSet->GetMemberSerial();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Group(Memberable�� �����ִ� Group�̴�. Group�� �������� ������ nullptr�� �ȴ�.)
			CGPTR<TGROUPBASE>	m_pGroup;
			LOCKABLE<>			m_csGroup;

	// 2) Group Member Data(Group�� ���ӵ� Data)
			TMEMBER_SET*		m_pGroupMemberSet;

	// 3) �پ� �ִ� Group�� ��� �����ϴ� �Լ�.
	//    - SetGroup()�� ResetGroup()�� �ǵ��� Group�ۿ����� ������� �ʴ� ���� �ٶ����ϴ�.
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

		// Check) �ƿ� Group�� ���� ���� ������ �׳� ������.
		RETURN_IF(rGroup.empty(),);

		// 1) �ϴ� Group���� Leave�� ���� �Ѵ�.
		TGROUPBASE::RequestLeaveMember(rGroup.get(), (TMEMBERBASE*)this);
	}
}
