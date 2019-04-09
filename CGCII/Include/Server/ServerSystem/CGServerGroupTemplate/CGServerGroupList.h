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

 @class		CList
 @brief		링크드-리스트형으로 멤버를 관리하는 그룹 클래스이다.
 @todo		
 @ref		
 @details	\n
 링크드-리스트형으로 멤버를 관리하는 그룹이다.
 따라서 멤버수의 제한이 거의 없는 편이다.
 다만 배열형과 다르게 Index로 해당 멤버를 얻어올 수가 없다.

 일반적으로 사용자 수의 제한이 없고 임의접근이 필요 없는 곳에 많이 사용된다.
 대표적으로 각종 게임이나 채팅시스템의 대기실 같은 것이 이에 해당한다.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA=int, class _TMEMBERBASE=_TMEMBER>
class CList : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGServerGroup<_TMEMBERBASE>,
	virtual public				ICGServerMemberContainerable<_TMEMBERBASE>
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TMEMBER													TMEMBER;
	typedef	_TMEMBERBASE												TMEMBERBASE;
	typedef	_TMEMBER_DATA												TMEMBER_DATA;
	typedef	MEMBER_SET_LIST<TMEMBER, TMEMBER_DATA>						TMEMBER_SET;
	typedef	circular_list<TMEMBER_SET>									TCONTAINER;
	typedef	typename TCONTAINER::iterator								ITERATOR;
	typedef	typename TCONTAINER::const_iterator							CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CList(int _nMaxMember=INT_MAX);
	virtual	~CList();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief 모든 '멤버 객체'를 퇴장시킨다.
			void				LeaveAllMember();

	//! @brief '멤버 객체'의 갯수를 얻는다. @return 멤버 객체 갯수
			int					GetMemberCount() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _GetMemberCount();}}
	//! @brief 남아 있는 '멤버 객체'의 갯수를 얻는다. @return 남은 멤버 객체 갯수
			int					GetMemberRoomCount() const				{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _GetMemberRoomCount();}}
	//! @brief 최대 '멤버 객체'의 갯수를 얻는다. @return 최대 멤버 객체 갯수
			int					GetMaxMemberCount() const				{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _GetMaxMemberCount();}}
	//! @brief 최대 '멤버 객체'의 설정한다. @param _MaxCount 설정할 '최대 멤버 객체 갯수'
			void				SetMaxMemberCount(int _MaxCount);
			
	//! @brief 멤버 객체가 꽉 찼는지를 확인한다. @return true 꽉찼다. false 꽉차지 않았다.
			bool				IsMemberFull() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _IsMemberFull();}}
	//! @brief 멤버 객체가 하나도 없는지 확인한다. @return true 완전히 비어있다. false 비어있지 않다.
			bool				IsMemberEmpty() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _IsMemberEmpty();}}
	//! @brief 멤버 객체가 들어갈 여유가 있는가를 확인한다. @return true 최대 인원만큼 꽉찼다. false 들어갈 여유가 있다.
			bool				IsMemberRoom() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _IsMemberRoom();}}
	//! @brief 멤버 객체가 하나라도 있는가를 확인한다. @return true 비어있지 않다. false 완전히 비어 있다.
			bool				IsMemberExist() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return !_IsMemberExist();}}

	//! @brief 멤버 객체가 하나라도 있는가를 확인한다. @param _pMember '멤버 객체' @return _pMember의 멤버 데이터
			TMEMBER_DATA&		GetMemberData(const TMEMBER* _pMember);
	//! @brief 멤버 시리얼을 얻는다. @param _pMember '멤버 객체' @return _pMember의 멤버 시리얼
			int					GetMemberSerial(const TMEMBER* _pMember) const { return ((TMEMBER_SET*)_pMember->GetMemberSet())->GetMemberSerial();}
	//! @brief 멤버 시리얼을 설정한다. @param _pMember '멤버 객체' @param _iSeat '멤버 시리얼'
			void				SetMemberSerial(TMEMBER* _pMember, int _iSeat) const{ ((TMEMBER_SET*)_pMember->GetMemberSet())->SetMemberSerial(_iSeat);}
	//! @brief 멤버 시리얼을 리셋한다. @param _pMember '멤버 객체'
			void				ResetMemberSerial(TMEMBER* _pMember) const { ((TMEMBER_SET*)_pMember->GetMemberSet())->ResetMemberSerial();}

	//! @brief 입장에 락을 건다.
			void				LockEnter()								{ ICGReferenceable::AddRef(); m_csEnter.lock();}
	//! @brief 입장에 언락한다.
			void				UnlockEnter()							{	m_csEnter.unlock(); ICGReferenceable::Release();}
	//! @brief 입장 락을 얻는다.
			LOCKABLE<>&			GetEnterLock()							{	return m_csEnter;}

	//! @brief 정방향 반복자 처음 멤버를 얻는다. @return '처음 멤버'
			ITERATOR			begin()									{ return m_containerMember.begin();}
	//! @brief 정방향 반복자 처음 멤버를 얻는다. @return '처음 멤버'
			CONST_ITERATOR		begin() const							{ return m_containerMember.begin();}
	//! @brief 정방향 반복자 끝 멤버를 얻는다. @return '처음 끝'
			ITERATOR			end()									{ return m_containerMember.end();}
	//! @brief 정방향 반복자 끝 멤버를 얻는다. @return '처음 끝'
			CONST_ITERATOR		end() const								{ return m_containerMember.end();}

	//! @brief 특정 멤버를 찾는다. @param _fCondition 찾는 조건 함수 @return 찾은 멤버 데이터
	virtual	CGPTR<_TMEMBERBASE>	FindMember(const std::function<bool (_TMEMBERBASE*)>& _fCondition) override;
	//! @brief 모든 멤버에 특정 함수를 실행한다. @param _fExecute 실행하는 함수 @return true 성공 @return false 실패
	virtual	bool				ForEachMember(const std::function<bool (_TMEMBERBASE*)>& _fExecute) override;


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

	//! @brief 그룹에서 멤버가 입장하는 처리를 정의한다. @param _pMember 입장할 '멤버 객체'
	virtual eOBJECT_RESULT		ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) override;

	//! @brief 그룹에서 멤버가 퇴장하는 처리를 정의한다. @param _pMember 퇴장할 '멤버 객체'
	virtual	void				ProcessLeaveMember(TMEMBERBASE* _pMember) override;

private:
	// 1) Attach/Detach관련 함수.
			void				_AttachMember(TMEMBER* _pMember)		{ _AttachMemberToListTail(_pMember);}
			void				_AttachMemberToListHead(TMEMBER* _pMember);
			void				_AttachMemberToListTail(TMEMBER* _pMember);
			void				_DetachMember(TMEMBERBASE* _pMember);

	// 2) 현재 붙어 있는 Peer의 수/최대 Peer수 얻기와 설정하기 함수.
			int					_GetMemberCount() const					{ return static_cast<int>(m_containerMember.size());}
			int					_GetMemberRoomCount() const				{ return m_countMaxMember-static_cast<int>(m_containerMember.size());}
			int					_GetMaxMemberCount() const				{ return m_countMaxMember;}
			
	// 3) Peer의 상태를 얻는 함수.(꽉찼는가?, 완전히 비었는가?, 자리가 남았는가?)
			bool				_IsMemberFull() const					{ return static_cast<int>(m_containerMember.size())>=m_countMaxMember;}
			bool				_IsMemberEmpty() const					{ return m_containerMember.empty();}
			bool				_IsMemberRoom() const					{ return static_cast<int>(m_containerMember.size())<m_countMaxMember;}
			bool				_IsMemberExist() const					{ return !m_containerMember.empty();}

	// 4) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);

protected:
	// 5) Member의 Enter에 대한 Lock
			bool				m_bEnableEnter;
			LOCKABLE<>			m_csEnter;

	// 6) Member Variable
			TCONTAINER			m_containerMember;
			int					m_countMaxMember;
};


}


#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupList.inl"
