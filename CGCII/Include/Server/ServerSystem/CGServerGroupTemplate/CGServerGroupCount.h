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

namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CArray
 @brief		배열형으로 멤버를 관리하는 그룹 클래스로 자리를 자동 결정해준다.
 @todo		
 @ref		
 @details	\n
 멤버 객체에 대한 관리를 하지 않고 단지 멤버 수만 카운팅하는 그룹이다.
 최대 멤버수를 제한하거나 입장이나 퇴장 때 처리해야할 기능을 정의할 수 있다.
 일반적으로 멤버의 관리는 내부적으로 처리하거나 멤버관리가 필요없이 수만 카운팅하면 되는 곳에 많이 사용된다.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBERBASE=_TMEMBER>
class CCount : 
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
		virtual public			ICGServerGroup<_TMEMBERBASE>			//     Group Base
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TMEMBER			TMEMBER;
	typedef	_TMEMBERBASE		TMEMBERBASE;


// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			CCount(int _nMaxMember=INT_MAX);
	virtual	~CCount();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief '멤버 객체'의 갯수를 얻는다. @return 멤버 객체 갯수
			int					GetMemberCount() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember;}}
	//! @brief 남아 있는 '멤버 객체'의 갯수를 얻는다. @return 남은 멤버 객체 갯수
			int					GetMemberRoomCount() const				{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMaxMember-m_countMember;}}
	//! @brief 최대 '멤버 객체'의 갯수를 얻는다. @return 최대 멤버 객체 갯수
			int					GetMaxMemberCount() const				{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMaxMember;}}
	//! @brief 최대 '멤버 객체'의 설정한다. @param _MaxCount 설정할 '최대 멤버 객체 갯수'
			void				SetMaxMemberCount(int _MaxCount)		{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { m_countMaxMember=_MaxCount;}}

	//! @brief 멤버 객체가 꽉 찼는지를 확인한다. @return true 꽉찼다. false 꽉차지 않았다.
			bool				IsMemberFull() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember>=m_countMaxMember;}}
	//! @brief 멤버 객체가 하나도 없는지 확인한다. @return true 완전히 비어있다. false 비어있지 않다.
			bool				IsMemberEmpty() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember==0;}}
	//! @brief 멤버 객체가 들어갈 여유가 있는가를 확인한다. @return true 최대 인원만큼 꽉찼다. false 들어갈 여유가 있다.
			bool				IsMemberRoom() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember<m_countMaxMember;}}
	//! @brief 멤버 객체가 하나라도 있는가를 확인한다. @return true 비어있지 않다. false 완전히 비어 있다.
			bool				IsMemberExist() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember!=0;}}

	//! @brief 입장에 락을 건다.
			void				LockEnter()								{ ICGReferenceable::AddRef(); m_csEnter.lock();}
	//! @brief 입장에 언락한다.
			void				UnlockEnter()							{	m_csEnter.unlock(); ICGReferenceable::Release();}
	//! @brief 입장 락을 얻는다.
			LOCKABLE<>&			GetEnterLock()							{	return m_csEnter;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief 입장을 허용했을 때 호출되는 함수
	virtual	void				OnEnableEnter()							{}
	//! @brief 입장이 금지했을 때 호출되는 함수
	virtual	void				OnDisableEnter()						{}

	//! @brief 새로운 멤버가 입장하기 직전 호출되는 함수 @param _pMember 입장할 '멤버 객체' @param _Msg 입장시 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 입장 성공 @return !eOBJECT_RESULT::SUCCESS 입장 실패
	virtual	eOBJECT_RESULT		OnMemberEntering(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/){ return eOBJECT_RESULT::SUCCESS;}
	//! @brief 새로운 멤버가 입장된 후 호출되는 함수 @param _pMember 입장한 '멤버 객체' @param _Msg 입장시 전달할 메시지
	virtual	void				OnMemberEntered(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/) {}

	//! @brief 멤버가 퇴장되기 직전에 호출되는 함수 @param _pMember 퇴장할 '멤버 객체' @return 전달할 값
	virtual	uintptr_t			OnMemberLeaving(TMEMBER* /*_pMember*/)	{ return 0;}
	//! @brief 멤버가 퇴장된 후 호출되는 함수 @param _pMember 퇴장한 '멤버 객체' @param _Result OnMemberLeaving()의 리턴 함수
	virtual	void				OnMemberLeaved(TMEMBER* /*_pMember*/, _In_ uintptr_t /*_Result*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief 입장 가능 여부를 설정하는 과정을 정의한다. @param _pEnable 입장 가능 여부 @return true 성공 @return false 실패
	virtual	bool				ProcessEnableEnter(bool _bEnable) override;

	//! @brief '멤버 객체'를 입장시킨다. @param _pMember 입장할 '멤버 객체' @param _Msg 입장할 때 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
	virtual	eOBJECT_RESULT		ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) override;

	//! @brief 그룹에서 멤버가 퇴장하는 처리를 정의한다. @param _pMember 퇴장할 '멤버 객체'
	virtual	void				ProcessLeaveMember(TMEMBERBASE* _pMember) override;

private:
	// 1) 현재 붙어 있는 Peer의 수/최대 Peer수 얻기와 설정하기 함수.
			int					_GetMemberCount() const					{	return static_cast<int>(m_countMember);}
			int					_GetMemberRoomCount() const				{	return m_countMaxMember-m_countMember;}
			int					_GetMaxMemberCount() const				{	return m_countMaxMember;}
			
	// 2) Peer의 상태를 얻는 함수.(꽉찼는가?, 완전히 비었는가?, 자리가 남았는가?)
			bool				_IsMemberFull() const					{	return m_countMember>=m_countMaxMember;}
			bool				_IsMemberEmpty() const					{	return m_countMember==0;}
			bool				_IsMemberRoom() const					{	return m_countMember<m_countMaxMember;}
			bool				_IsMemberExist() const					{	return m_countMember!=0;}

	// 3) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);

private:
	// 4) Member의 Enter에 대한 Lock
			bool				m_bEnableEnter;
			LOCKABLE<>			m_csEnter;

	// 5) Member 변수.
			int					m_countMember;
			int					m_countMaxMember;
};


}

#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupCount.inl"
