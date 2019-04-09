//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                         Socket template Classes                           *
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

namespace CGServerObservers
{

//-----------------------------------------------------------------------------
/**

 @class		CList
 @brief		
 @todo		
 @ref		
 @details	\n
 일반적인 선형 Container를 가진 Observer 관리자.
 Array/Linked-List Container로 Observer를 관리한다.

*///-----------------------------------------------------------------------------
template <class TOBSERVER>
class CList :
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				ICGServerObservers<TOBSERVER>		// (I) Reference Counter.
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	circular_list<CGPTR<TOBSERVER>>			TCONTAINER;
	typedef	typename TCONTAINER::iterator			ITERATOR;
	typedef	typename TCONTAINER::const_iterator		CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CList()														{}
	virtual	~CList()													{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief '옵저버 객체'를 등록한다. @param _pObserver 등록할 '옵저버 객체' @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
			eOBJECT_RESULT		RegisterObserver(TOBSERVER* _pObserver)	{ CGMSG msg; return RegisterObserver(_pObserver, msg);}
	//! @brief '옵저버 객체'를 등록한다. @param _pObserver 등록할 '옵저버 객체' @param _Msg 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 성공 @return !eOBJECT_RESULT::SUCCESS 실패
	virtual	eOBJECT_RESULT		RegisterObserver(TOBSERVER* _pObserver, CGMSG& _Msg);
	//! @brief 등록된 '옵저버 객체'를 해제한다. @param _pObserver 등록해제할 '옵저버 객체' @return true 성공 @return false 실패
	virtual	bool				UnregisterObserver(TOBSERVER* _pObserver);
	//! @brief 모든 등록된 '옵저버 객체'를 해제한다.
	virtual	void				UnregisterAllObserver();

	//! @brief '옵저버 객체'의 갯수를 얻는다. @return 옵저버 객체 갯수
			int					GetObserverCount() const				{ LOCK(m_containerObserver) { return _GetObserverCount();}}
	//! @brief 들어갈 여유 있는 '옵저버 객체'의 갯수를 얻는다. @return 들어갈 여유 있는 옵저버 객체 갯수
			int					GetObserverRoomCount() const			{ LOCK(m_containerObserver) { return _GetObserverRoomCount();}}
	//! @brief 최대 '옵저버 객체'의 갯수를 얻는다. @return 최대 옵저버 객체 갯수
			int					GetMaxObserverCount() const				{ LOCK(m_containerObserver) { return _GetMaxObserverCount();}}
	//! @brief 최대 '옵저버 객체'의 설정한다. @param _MaxCount 설정할 '최대 옵저버 객체 갯수'
			void				SetMaxObserverCount(int _MaxCount);

	//! @brief 옵저버 객체가 꽉 찼는지를 확인한다. @return true 꽉찼다. false 꽉차지 않았다.
			bool				IsObserverFull() const					{ LOCK(m_containerObserver) { return _IsObserverFull();}}
	//! @brief 옵저버 객체가 하나도 없는지 확인한다. @return true 완전히 비어있다. false 비어있지 않다.
			bool				IsObserverEmpty() const					{ LOCK(m_containerObserver) { return _IsObserverEmpty();}}
	//! @brief 옵저버 객체가 들어갈 여유가 있는가를 확인한다. @return true 최대 옵저버 수만큼 꽉찼다. false 들어갈 여유가 있다.
			bool				IsObserverRoom() const					{ LOCK(m_containerObserver) { return _IsObserverRoom();}}
	//! @brief 옵저버 객체가 하나라도 있는가를 확인한다. @return true 비어있지 않다. false 완전히 비어 있다.
			bool				IsObserverExist() const					{ LOCK(m_containerObserver) { return _IsObserverExist();}}

	//! @brief 옵저버의 락을 건다.
			void				LockObservers() const					{ ICGReferenceable::AddRef(); m_containerObserver.lock();}	// Group List에 Lock걸기.
	//! @brief 옵저버의 언락한다.
			void				UnlockObservers() const					{ m_containerObserver.unlock(); ICGReferenceable::Release();}	// Group List의 Lock풀기.
	//! @brief 옵저버의 락을 얻는다.
								operator LOCKABLE<>&()					{ return m_containerObserver;}	// 연산자 overlading(LOCKU용)

	//! @brief 정방향 반복자 처음 옵저버를 얻는다. @return '처음 옵저버'
			ITERATOR			begin()									{ return m_containerObserver.begin();}
	//! @brief 정방향 반복자 처음 옵저버를 얻는다. @return '처음 옵저버'
			CONST_ITERATOR		begin() const							{ return m_containerObserver.begin();}
	//! @brief 정방향 반복자 끝 옵저버를 얻는다. @return '끝 옵저버'
			ITERATOR			end()									{ return m_containerObserver.end();}
	//! @brief 정방향 반복자 끝 옵저버를 얻는다. @return '끝 옵저버'
			CONST_ITERATOR		end() const								{ return m_containerObserver.end();}

	//! @brief 특정 옵저버를 찾는다. @param _fCondition 찾는 조건 함수 @return 찾은 멤버 데이터
			CGPTR<TOBSERVER>	FindObserver(const std::function<bool (TOBSERVER*)>& _fCondition);
	//! @brief 모든 옵저버에 특정 함수를 실행한다. @param _fExecute 실행하는 함수 @return true 성공 @return false 실패
			bool				ForEachObserver(const std::function<bool (TOBSERVER*)>& _fExecute);


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief 새로운 옵저버가 등록되기 직전 호출되는 함수 @param _pObserver 등록할 '옵저버 객체' @param _Msg 등록시 전달할 메시지 @return eOBJECT_RESULT::SUCCESS 입장 성공 @return !eOBJECT_RESULT::SUCCESS 입장 실패
	virtual	eOBJECT_RESULT		OnObserverRegistering(TOBSERVER* /*_pObserver*/, CGMSG& /*_Msg*/){ return eOBJECT_RESULT::SUCCESS;}
	//! @brief 새로운 멤버가 등록된 후 호출되는 함수 @param _pObserver 등록한 '옵저버 객체' @param _Msg 등록시 전달할 메시지
	virtual	void				OnObserverRegistered(TOBSERVER* /*_pObserver*/, CGMSG& /*_Msg*/) {}

	//! @brief 옵저버가 등록해제되기 직전에 호출되는 함수 @param _pObserver 등록해제할 '옵저버 객체' @return 전달할 값
	virtual	uintptr_t			OnObserverUnregistering(TOBSERVER* /*_pObserver*/) { return 0;}
	//! @brief 옵저버가 등록해제된 후 호출되는 함수 @param _pObserver 등록해제한 '옵저버 객체' @param _Result OnObserverUnregistering()의 리턴 함수
	virtual	void				OnObserverUnregistered(TOBSERVER* /*_pObserver*/, uintptr_t /*_Result*/){}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) 현재 붙어 있는 Peer의 수/최대 Peer수 얻기와 설정하기 함수.
			int					_GetObserverCount() const				{	return static_cast<int>(m_containerObserver.size());}
			int					_GetObserverRoomCount() const			{	return m_countMaxObserver-m_containerObserver.size();}
			int					_GetMaxObserverCount() const			{	return m_countMaxObserver;}
			
	// 2) Peer의 상태를 얻는 함수.(꽉찼는가?, 완전히 비었는가?, 자리가 남았는가?)
			bool				_IsObserverFull() const					{	return m_containerObserver.size()>=m_countMaxObserver;}
			bool				_IsObserverEmpty() const				{	return m_containerObserver.empty();}
			bool				_IsObserverRoom() const					{	return static_cast<int>(m_containerObserver.size())<m_countMaxObserver;}
			bool				_IsObserverExist() const				{	return !m_containerObserver.empty();}
private:
	// 3) ...
			LOCKABLE<TCONTAINER> m_containerObserver;
			int					m_countMaxObserver;
};


template <class TOBSERVER>
eOBJECT_RESULT CList<TOBSERVER>::RegisterObserver(TOBSERVER* _pObserver, CGMSG& _Msg)
{
	// Check) _pObserver가 nullptr이면 안됀다.
	RETURN_IF(_pObserver==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);
	
	LOCK(m_containerObserver)
	{
		// Check) 꽉 찼는가?
		RETURN_IF(IsObserverFull(), eOBJECT_RESULT::MEMBER_FULL);

		// Check) 이미 같은 Observer가 존재하는지 확인한다.
		ITERATOR	iterFind	 = std::find(m_containerObserver.begin(), m_containerObserver.end(), _pObserver);

		// Check) 이미 붙어 있다면 끝낸다.
		RETURN_IF(iterFind != m_containerObserver.end(), eOBJECT_RESULT::ALEADY_EXIST);

		// 1) OnObserverRegistering()함수를 호출한다.
		auto	eResult	 = OnObserverRegistering(_pObserver, _Msg);

		// Check) 입장 조건에 맞지 않는다!
		RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult);

		// 2) 추가한다.
		m_containerObserver.push_back(_pObserver);

		// 3) OnObserverRegistered()함수를 호출한다.
		try
		{
			OnObserverRegistered(_pObserver, _Msg);
		}
		// Exception) Rollback한다.
		catch(const std::exception& e)
		{
			// Log)
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Completeion[OnObserverRegistered] ") _CGFUNCTION);

			// - OnException을 호출한다.
			auto	bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

			// - Observer를 제거한다.
			m_containerObserver.pop_back();

			// Check) 
			RETURN_IF(bExecuted, eOBJECT_RESULT::EXCEPTION);

			// Reraise) 
			throw;
		}
	}

	// Return) 성공이닷!!!
	return	eOBJECT_RESULT::SUCCESS;
}

template <class TOBSERVER>
bool CList<TOBSERVER>::UnregisterObserver(TOBSERVER* _pObserver)
{
	// Check) _pObserver가 nullptr이여서는 안됀다.
	CGASSERT(_pObserver!=nullptr, );
	
	LOCK(m_containerObserver)
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		// 1) 먼저 이미 등록되어 있는지 찾는다.
		ITERATOR	iterFind	 = std::find(m_containerObserver.begin(), m_containerObserver.end(), _pObserver);

		// Check) 찾지 못했으면 끝낸다.
		RETURN_IF(iterFind==m_containerObserver.end(), false);

		// 2) OnObserverUnregistering()함수를 호출한다.
		try
		{
			dwResult	 = OnObserverUnregistering(_pObserver);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGNetObserver : Occure exception in 'OnObserverUnregistering' function on Observer object ") _CGFUNCTION);
		}

		// 2) 제거한다.
		m_containerObserver.erase(iterFind);

		// 3) OnObserverUnregistered()함수를 호출한다.
		try
		{
			OnObserverUnregistered(_pObserver, dwResult);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGNetObserver : Occure exception in 'OnObserverUnregistered' function on Observer object ") _CGFUNCTION);
		}
	}

	// Return) 
	return	true;
}

template <class TOBSERVER>
void CList<TOBSERVER>::UnregisterAllObserver()
{
	LOCK(m_containerObserver)
	{
		for(auto& iter:m_containerObserver)
		{
			// Check) nullptr이면 다음...
			CONTINUE_IF(iter->IsEmpty());

			// 1) Observer를 Unregister한다.
			UnregisterObserver(iter);
		}
	}
}


template <class TOBSERVER>
void CList<TOBSERVER>::SetMaxObserverCount(int _MaxCount)
{
	LOCK(m_containerObserver)
	{
		// 1) 최대 Observer수를 설정한다.
		m_countMaxObserver	 = _MaxCount;
	
		// 2) Reserve한다.(Reserver함수가 있을 경우에만...)
	#if defined(_MSC_VER)
		__if_exists(TCONTAINER::reserve)
		{
			m_containerObserver.reserve((_MaxCount>256) ? 256:_MaxCount);
		}
	#endif
	}
}

template <class TOBSERVER>
CGPTR<TOBSERVER> CList<TOBSERVER>::FindObserver(const std::function<bool (TOBSERVER*)>& _fCondition)
{
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		for(auto& iter:m_containerObserver)
		{
			// 1) Execute함수를 실행한다.
			bool	result	 = _fCondition(iter);

			// Check) 
			RETURN_IF(result==true, iter);
		}
	}

	// Return) 찾지 못했다..
	return	CGPTR<TOBSERVER>();
}

template <class TOBSERVER>
bool CList<TOBSERVER>::ForEachObserver(const std::function<bool (TOBSERVER*)>& _fExecute)
{
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		for(auto& iter:m_containerObserver)
		{
			// 1) Execute함수를 실행한다.
			bool	result	 = _fExecute(*iter);

			// Check) 
			RETURN_IF(result==false, false);
		}
	}

	// Return) 성공...
	return	true;
}


}