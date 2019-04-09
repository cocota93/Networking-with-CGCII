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
 @ref		
 @details	\n
 ��� ��ü�� ���� ������ ���� �ʰ� ���� ��� ���� ī�����ϴ� �׷��̴�.
 �ִ� ������� �����ϰų� �����̳� ���� �� ó���ؾ��� ����� ������ �� �ִ�.
 �Ϲ������� ����� ������ ���������� ó���ϰų� ��������� �ʿ���� ���� ī�����ϸ� �Ǵ� ���� ���� ���ȴ�.
       
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
	//! @brief '��� ��ü'�� ������ ��´�. @return ��� ��ü ����
			int					GetMemberCount() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember;}}
	//! @brief ���� �ִ� '��� ��ü'�� ������ ��´�. @return ���� ��� ��ü ����
			int					GetMemberRoomCount() const				{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMaxMember-m_countMember;}}
	//! @brief �ִ� '��� ��ü'�� ������ ��´�. @return �ִ� ��� ��ü ����
			int					GetMaxMemberCount() const				{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMaxMember;}}
	//! @brief �ִ� '��� ��ü'�� �����Ѵ�. @param _MaxCount ������ '�ִ� ��� ��ü ����'
			void				SetMaxMemberCount(int _MaxCount)		{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { m_countMaxMember=_MaxCount;}}

	//! @brief ��� ��ü�� �� á������ Ȯ���Ѵ�. @return true ��á��. false ������ �ʾҴ�.
			bool				IsMemberFull() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember>=m_countMaxMember;}}
	//! @brief ��� ��ü�� �ϳ��� ������ Ȯ���Ѵ�. @return true ������ ����ִ�. false ������� �ʴ�.
			bool				IsMemberEmpty() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember==0;}}
	//! @brief ��� ��ü�� �� ������ �ִ°��� Ȯ���Ѵ�. @return true �ִ� �ο���ŭ ��á��. false �� ������ �ִ�.
			bool				IsMemberRoom() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember<m_countMaxMember;}}
	//! @brief ��� ��ü�� �ϳ��� �ִ°��� Ȯ���Ѵ�. @return true ������� �ʴ�. false ������ ��� �ִ�.
			bool				IsMemberExist() const					{ LOCK(ICGServerGroup<TMEMBERBASE>::m_csGroup) { return m_countMember!=0;}}

	//! @brief ���忡 ���� �Ǵ�.
			void				LockEnter()								{ ICGReferenceable::AddRef(); m_csEnter.lock();}
	//! @brief ���忡 ����Ѵ�.
			void				UnlockEnter()							{	m_csEnter.unlock(); ICGReferenceable::Release();}
	//! @brief ���� ���� ��´�.
			LOCKABLE<>&			GetEnterLock()							{	return m_csEnter;}


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
	// 1) ���� �پ� �ִ� Peer�� ��/�ִ� Peer�� ���� �����ϱ� �Լ�.
			int					_GetMemberCount() const					{	return static_cast<int>(m_countMember);}
			int					_GetMemberRoomCount() const				{	return m_countMaxMember-m_countMember;}
			int					_GetMaxMemberCount() const				{	return m_countMaxMember;}
			
	// 2) Peer�� ���¸� ��� �Լ�.(��á�°�?, ������ ����°�?, �ڸ��� ���Ҵ°�?)
			bool				_IsMemberFull() const					{	return m_countMember>=m_countMaxMember;}
			bool				_IsMemberEmpty() const					{	return m_countMember==0;}
			bool				_IsMemberRoom() const					{	return m_countMember<m_countMaxMember;}
			bool				_IsMemberExist() const					{	return m_countMember!=0;}

	// 3) Process Entered/Leaving
	virtual	void				_ProcessMemberEntered(TMEMBER* _pMember, CGMSG& _Msg);
	virtual	uintptr_t			_ProcessMemberLeaving(TMEMBER* _pMember);

private:
	// 4) Member�� Enter�� ���� Lock
			bool				m_bEnableEnter;
			LOCKABLE<>			m_csEnter;

	// 5) Member ����.
			int					m_countMember;
			int					m_countMaxMember;
};


}

#include "Server/ServerSystem/CGServerGroupTemplate/CGServerGroupCount.inl"
