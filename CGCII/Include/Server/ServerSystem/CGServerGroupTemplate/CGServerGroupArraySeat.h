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
 @ref		CGServerGroup::CArraySeat, CGServerGroup::CArraySeatSender, CGServerGroup::CArraySeatDispatchable
 @details	\n
 배열형으로 멤버들을 관리하는 그룹 클래스이다.
 따라서 그룹의 최대 인원을 설정해주어야 한다.(만약 설정해주지 않으면 기본값이 256이 된다.)
 멤버가 입장을 하게 되면 좌석번호가 자동으로 배정되어 입장된다.
 또 빠져나갈 경우 그 좌석 번호는 반환된다.

 입장 인원의 최대치가 정해져 있는 채팅방이나 N:N의 게임 방의 구현에 많이 사용된다.
       
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA=int, class _TMEMBERBASE= _TMEMBER>
class CArraySeat : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGServerGroup<_TMEMBERBASE>,			//     Group Base
	virtual public				ICGServerMemberContainerable<_TMEMBERBASE>
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TMEMBER													TMEMBER;
	typedef	_TMEMBERBASE												TMEMBERBASE;
	typedef	_TMEMBER_DATA												TMEMBER_DATA;
	typedef	MEMBER_SET_ARRAY<TMEMBER, TMEMBER_DATA>						TMEMBER_SET;
	typedef	vector<TMEMBER_SET>											TCONTAINER;
	typedef typename TCONTAINER::iterator								ITERATOR;
	typedef typename TCONTAINER::const_iterator							CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor).
// ----------------------------------------------------------------------------
public:
			CArraySeat(int _nMaxMember=256);
	virtual	~CArraySeat();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief 해당 _iSeat의 멤버를 퇴장시킨다. @param _iSeat 좌석 번호 @return 퇴장한 '멤버 객체'
			CGPTR<TMEMBER>		LeaveMemberBySeat(int _iSeat);
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

	//! @brief 멤버 객체를 얻는다. @param _iSeat '멤버 시리얼' @return '멤버 객체'
			CGPTR<TMEMBER>		GetMember(int _iSeat);
	//! @brief 멤버 객체가 하나라도 있는가를 확인한다. @param _pMember '멤버 객체' @return _pMember의 멤버 데이터
			TMEMBER_DATA&		GetMemberData(const TMEMBER* _pMember);
	//! @brief 멤버 시리얼을 얻는다. @param _pMember '멤버 객체' @return _pMember의 멤버 시리얼
			int					GetMemberSerial(const TMEMBER* _pMember) const	{ return ((TMEMBER_SET*)_pMember->GetMemberSet())->GetMemberSerial();}

	//! @brief 입장에 락을 건다.
			void				LockEnter()								{	ICGReferenceable::AddRef(); m_csEnter.lock();}
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

	//! @brief '멤버 객체'를 입장시킨다. @param _pMember 입장할 '멤버 객체' @param _Msg 입장할 때 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
	virtual	eOBJECT_RESULT		ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) override;

	//! @brief 그룹에서 멤버가 퇴장하는 처리를 정의한다. @param _pMember 퇴장할 '멤버 객체'
	virtual	void				ProcessLeaveMember(TMEMBERBASE* _pMember) override;

private:
	// 1) Attach & Detach
			void				_AttachMember(TMEMBER* _pMember);
			void				_DetachMember(TMEMBERBASE* _pMember);

	// 2) 현재 붙어 있는 Peer의 수/최대 Peer수 얻기와 설정하기 함수.
			int					_GetMemberCount() const					{	return static_cast<int>(m_countMember);}
			int					_GetMemberRoomCount() const				{	return m_countMaxMember-m_countMember;}
			int					_GetMaxMemberCount() const				{	return m_countMaxMember;}
			
	// 3) Peer의 상태를 얻는 함수.(꽉찼는가?, 완전히 비었는가?, 자리가 남았는가?)
			bool				_IsMemberFull() const					{	return m_countMember>=m_countMaxMember;}
			bool				_IsMemberEmpty() const					{	return m_countMember==0;}
			bool				_IsMemberRoom() const					{	return m_countMember<m_countMaxMember;}
			bool				_IsMemberExist() const					{	return m_countMember!=0;}

	// 4) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);

private:
	// 5) Member Variable
			seat				m_seat;

	// 6) Member의 Enter에 대한 Lock
			bool				m_bEnableEnter;
			LOCKABLE<>			m_csEnter;

	// 7) 
			TCONTAINER			m_containerMember;
			int					m_countMember;
			int					m_countMaxMember;
};


}

#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArraySeat.inl"
