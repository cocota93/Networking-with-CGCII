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

namespace CGServerGroup
{

//-----------------------------------------------------------------------------
/**

 @class		CArray
 @brief		�迭������ ����� �����ϴ� �׷� Ŭ������ �ڸ��� �ڵ� �������ش�.
 @todo		
 @ref		CGServerGroup::CArraySeat, CGServerGroup::CArraySeatSender, CGServerGroup::CArraySeatDispatchable
 @details	\n
 �迭������ ������� �����ϴ� �׷� Ŭ�����̴�.
 ���� �׷��� �ִ� �ο��� �������־�� �Ѵ�.(���� ���������� ������ �⺻���� 256�� �ȴ�.)
 ����� ������ �ϰ� �Ǹ� �¼���ȣ�� �ڵ����� �����Ǿ� ����ȴ�.
 �� �������� ��� �� �¼� ��ȣ�� ��ȯ�ȴ�.

 ���� �ο��� �ִ�ġ�� ������ �ִ� ä�ù��̳� N:N�� ���� ���� ������ ���� ���ȴ�.
       
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
	//! @brief �ش� _iSeat�� ����� �����Ų��. @param _iSeat �¼� ��ȣ @return ������ '��� ��ü'
			CGPTR<TMEMBER>		LeaveMemberBySeat(int _iSeat);
	//! @brief ��� '��� ��ü'�� �����Ų��.
			void				LeaveAllMember();

	//! @brief '��� ��ü'�� ������ ��´�. @return ��� ��ü ����
			int					GetMemberCount() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _GetMemberCount();}}
	//! @brief ���� �ִ� '��� ��ü'�� ������ ��´�. @return ���� ��� ��ü ����
			int					GetMemberRoomCount() const				{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _GetMemberRoomCount();}}
	//! @brief �ִ� '��� ��ü'�� ������ ��´�. @return �ִ� ��� ��ü ����
			int					GetMaxMemberCount() const				{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _GetMaxMemberCount();}}
	//! @brief �ִ� '��� ��ü'�� �����Ѵ�. @param _MaxCount ������ '�ִ� ��� ��ü ����'
			void				SetMaxMemberCount(int _MaxCount);
			
	//! @brief ��� ��ü�� �� á������ Ȯ���Ѵ�. @return true ��á��. false ������ �ʾҴ�.
			bool				IsMemberFull() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _IsMemberFull();}}
	//! @brief ��� ��ü�� �ϳ��� ������ Ȯ���Ѵ�. @return true ������ ����ִ�. false ������� �ʴ�.
			bool				IsMemberEmpty() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _IsMemberEmpty();}}
	//! @brief ��� ��ü�� �� ������ �ִ°��� Ȯ���Ѵ�. @return true �ִ� �ο���ŭ ��á��. false �� ������ �ִ�.
			bool				IsMemberRoom() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return _IsMemberRoom();}}
	//! @brief ��� ��ü�� �ϳ��� �ִ°��� Ȯ���Ѵ�. @return true ������� �ʴ�. false ������ ��� �ִ�.
			bool				IsMemberExist() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return !_IsMemberExist();}}

	//! @brief ��� ��ü�� ��´�. @param _iSeat '��� �ø���' @return '��� ��ü'
			CGPTR<TMEMBER>		GetMember(int _iSeat);
	//! @brief ��� ��ü�� �ϳ��� �ִ°��� Ȯ���Ѵ�. @param _pMember '��� ��ü' @return _pMember�� ��� ������
			TMEMBER_DATA&		GetMemberData(const TMEMBER* _pMember);
	//! @brief ��� �ø����� ��´�. @param _pMember '��� ��ü' @return _pMember�� ��� �ø���
			int					GetMemberSerial(const TMEMBER* _pMember) const	{ return ((TMEMBER_SET*)_pMember->GetMemberSet())->GetMemberSerial();}

	//! @brief ���忡 ���� �Ǵ�.
			void				LockEnter()								{	ICGReferenceable::AddRef(); m_csEnter.lock();}
	//! @brief ���忡 ����Ѵ�.
			void				UnlockEnter()							{	m_csEnter.unlock(); ICGReferenceable::Release();}
	//! @brief ���� ���� ��´�.
			LOCKABLE<>&			GetEnterLock()							{	return m_csEnter;}

	//! @brief ������ �ݺ��� ó�� ����� ��´�. @return 'ó�� ���'
			ITERATOR			begin()									{ return m_containerMember.begin();}
	//! @brief ������ �ݺ��� ó�� ����� ��´�. @return 'ó�� ���'
			CONST_ITERATOR		begin() const							{ return m_containerMember.begin();}
	//! @brief ������ �ݺ��� �� ����� ��´�. @return 'ó�� ��'
			ITERATOR			end()									{ return m_containerMember.end();}
	//! @brief ������ �ݺ��� �� ����� ��´�. @return 'ó�� ��'
			CONST_ITERATOR		end() const								{ return m_containerMember.end();}

	//! @brief Ư�� ����� ã�´�. @param _fCondition ã�� ���� �Լ� @return ã�� ��� ������
	virtual	CGPTR<_TMEMBERBASE>	FindMember(const std::function<bool (_TMEMBERBASE*)>& _fCondition) override;
	//! @brief ��� ����� Ư�� �Լ��� �����Ѵ�. @param _fExecute �����ϴ� �Լ� @return true ���� @return false ����
	virtual	bool				ForEachMember(const std::function<bool (_TMEMBERBASE*)>& _fExecute) override;


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief ������ ������� �� ȣ��Ǵ� �Լ�
	virtual	void				OnEnableEnter()							{}
	//! @brief ������ �������� �� ȣ��Ǵ� �Լ�
	virtual	void				OnDisableEnter()						{}

	//! @brief ���ο� ����� �����ϱ� ���� ȣ��Ǵ� �Լ� @param _pMember ������ '��� ��ü' @param _Msg ����� ������ �޽��� @return eOBJECT_RESULT::SUCCESS ���� ���� @return !eOBJECT_RESULT::SUCCESS ���� ����
	virtual	eOBJECT_RESULT		OnMemberEntering(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/){ return eOBJECT_RESULT::SUCCESS;}
	//! @brief ���ο� ����� ����� �� ȣ��Ǵ� �Լ� @param _pMember ������ '��� ��ü' @param _Msg ����� ������ �޽���
	virtual	void				OnMemberEntered(TMEMBER* /*_pMember*/, CGMSG& /*_Msg*/) {}

	//! @brief ����� ����Ǳ� ������ ȣ��Ǵ� �Լ� @param _pMember ������ '��� ��ü' @return ������ ��
	virtual	uintptr_t			OnMemberLeaving(TMEMBER* /*_pMember*/)	{ return 0;}
	//! @brief ����� ����� �� ȣ��Ǵ� �Լ� @param _pMember ������ '��� ��ü' @param _Result OnMemberLeaving()�� ���� �Լ�
	virtual	void				OnMemberLeaved(TMEMBER* /*_pMember*/, _In_ uintptr_t /*_Result*/)	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	//! @brief ���� ���� ���θ� �����ϴ� ������ �����Ѵ�. @param _pEnable ���� ���� ���� @return true ���� @return false ����
	virtual	bool				ProcessEnableEnter(bool _bEnable) override;

	//! @brief '��� ��ü'�� �����Ų��. @param _pMember ������ '��� ��ü' @param _Msg ������ �� ������ �޽��� @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
	virtual	eOBJECT_RESULT		ProcessEnterMember(TMEMBERBASE* _pMember, CGMSG& _Msg) override;

	//! @brief �׷쿡�� ����� �����ϴ� ó���� �����Ѵ�. @param _pMember ������ '��� ��ü'
	virtual	void				ProcessLeaveMember(TMEMBERBASE* _pMember) override;

private:
	// 1) Attach & Detach
			void				_AttachMember(TMEMBER* _pMember);
			void				_DetachMember(TMEMBERBASE* _pMember);

	// 2) ���� �پ� �ִ� Peer�� ��/�ִ� Peer�� ���� �����ϱ� �Լ�.
			int					_GetMemberCount() const					{	return static_cast<int>(m_countMember);}
			int					_GetMemberRoomCount() const				{	return m_countMaxMember-m_countMember;}
			int					_GetMaxMemberCount() const				{	return m_countMaxMember;}
			
	// 3) Peer�� ���¸� ��� �Լ�.(��á�°�?, ������ ����°�?, �ڸ��� ���Ҵ°�?)
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

	// 6) Member�� Enter�� ���� Lock
			bool				m_bEnableEnter;
			LOCKABLE<>			m_csEnter;

	// 7) 
			TCONTAINER			m_containerMember;
			int					m_countMember;
			int					m_countMaxMember;
};


}

#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupArraySeat.inl"
