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
//
// CGServerGroup::MEMBER_SET
//
//-----------------------------------------------------------------------------
namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CArray
 @brief		멤버별 데이터를 저장할 데이터
 @todo		
 @ref		
 @details	\n
 멤버별 데이터를 임시 저장하는 용도로 사용되는 것이다.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER>
struct MEMBER_SET
{
public:
	typedef	_TMEMBER			TMEMBER;

public:
			MEMBER_SET()												{}
			MEMBER_SET(ICGServerGroup<TMEMBER>* _pGroup) : m_pGroup(_pGroup){}

public:
			CGPTR<ICGServerGroup<TMEMBER>> GetGroup() const				{	return m_pGroup;}
			void				SetGroup(ICGServerGroup<TMEMBER>* _pGroup){	m_pGroup=_pGroup;}

			void				SetMember(TMEMBER* _pMember)			{	m_pMember=_pMember;}
			void				ResetMember()							{	m_pMember.reset();}
			CGPTR<TMEMBER>		GetMember() const						{	return m_pMember;}

			void				SetMemberSerial(int p_iMemberSerial)	{	m_iMemberSerial=p_iMemberSerial;}
			void				ResetMemberSerial()						{	m_iMemberSerial=-1;}
			int					GetMemberSerial() const					{	return m_iMemberSerial;}

			bool				IsExist() const							{	return m_pMember.exist();}
			bool				IsEmpty() const							{	return m_pMember.empty();}

			bool				IsMemberOf(const ICGServerGroup<TMEMBER>* _pGroup) const{	return m_pMember->IsMemberOf(_pGroup);}

public:
								operator const CGPTR<TMEMBER>&() const	{	return m_pMember;}

			CGPTR<TMEMBER>&			operator->()						{	return m_pMember;}
			const CGPTR<TMEMBER>&	operator->() const					{	return m_pMember;}
			CGPTR<TMEMBER>&			operator*()							{ return m_pMember; }
			const CGPTR<TMEMBER>&	operator*() const					{	return m_pMember;}

			MEMBER_SET&			operator=(TMEMBER* rhs)					{	m_pMember=rhs; return *this;}
			MEMBER_SET&			operator=(const CGPTR<TMEMBER>& rhs)	{	m_pMember=rhs; return *this;}

			bool				operator==(const TMEMBER* rhs) const	{	return m_pMember==rhs;}
			bool				operator!=(const TMEMBER* rhs) const	{	return m_pMember!=rhs;}
			bool				operator==(const ICGServerGroup<TMEMBER>* rhs) const	{	return m_pGroup==rhs;}
			bool				operator!=(const ICGServerGroup<TMEMBER>* rhs) const	{	return m_pGroup!=rhs;}

private:
			CGPTR<TMEMBER>		m_pMember;
			ICGServerGroup<TMEMBER>* m_pGroup;
			int					m_iMemberSerial;
};


//-----------------------------------------------------------------------------
//
// CGServerGroup::MEMBER_SET_ARRAY
//
// Array형 Group의 MemberData
//
//-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA>
struct MEMBER_SET_ARRAY : public MEMBER_SET<_TMEMBER>
{
public:
	typedef	_TMEMBER_DATA		TMEMBER_DATA;

public:
			MEMBER_SET_ARRAY()											{}
			MEMBER_SET_ARRAY(ICGServerGroup<_TMEMBER>* _pGroup) : MEMBER_SET<_TMEMBER>(_pGroup)	{}
public:
			TMEMBER_DATA		m_MemberData;

public:
			MEMBER_SET_ARRAY&		operator=(_TMEMBER* rhs)			{	SetMember(rhs); return *this;}
};


//-----------------------------------------------------------------------------
//
// CGServerGroup::MEMBER_SET_LIST
//
// List형 Group의 MemberData
//
//-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA>
struct MEMBER_SET_LIST : public MEMBER_SET<_TMEMBER>
{
public:
	typedef	_TMEMBER_DATA		TMEMBER_DATA;

public:
			MEMBER_SET_LIST()											{}
			MEMBER_SET_LIST(ICGServerGroup<_TMEMBER>* _pGroup) : MEMBER_SET<_TMEMBER>(_pGroup){}
public:
			TMEMBER_DATA		m_MemberData;
public:
	typename circular_list<MEMBER_SET_LIST<_TMEMBER, TMEMBER_DATA> >::const_iterator	iter;

			MEMBER_SET_LIST&		operator=(_TMEMBER* rhs)			{ MEMBER_SET<_TMEMBER>::m_pMember=rhs; return *this;}
};


}