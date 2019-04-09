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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
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
 �Ϲ����� ���� Container�� ���� Observer ������.
 Array/Linked-List Container�� Observer�� �����Ѵ�.

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
	//! @brief '������ ��ü'�� ����Ѵ�. @param _pObserver ����� '������ ��ü' @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
			eOBJECT_RESULT		RegisterObserver(TOBSERVER* _pObserver)	{ CGMSG msg; return RegisterObserver(_pObserver, msg);}
	//! @brief '������ ��ü'�� ����Ѵ�. @param _pObserver ����� '������ ��ü' @param _Msg ������ �޽��� @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
	virtual	eOBJECT_RESULT		RegisterObserver(TOBSERVER* _pObserver, CGMSG& _Msg);
	//! @brief ��ϵ� '������ ��ü'�� �����Ѵ�. @param _pObserver ��������� '������ ��ü' @return true ���� @return false ����
	virtual	bool				UnregisterObserver(TOBSERVER* _pObserver);
	//! @brief ��� ��ϵ� '������ ��ü'�� �����Ѵ�.
	virtual	void				UnregisterAllObserver();

	//! @brief '������ ��ü'�� ������ ��´�. @return ������ ��ü ����
			int					GetObserverCount() const				{ LOCK(m_containerObserver) { return _GetObserverCount();}}
	//! @brief �� ���� �ִ� '������ ��ü'�� ������ ��´�. @return �� ���� �ִ� ������ ��ü ����
			int					GetObserverRoomCount() const			{ LOCK(m_containerObserver) { return _GetObserverRoomCount();}}
	//! @brief �ִ� '������ ��ü'�� ������ ��´�. @return �ִ� ������ ��ü ����
			int					GetMaxObserverCount() const				{ LOCK(m_containerObserver) { return _GetMaxObserverCount();}}
	//! @brief �ִ� '������ ��ü'�� �����Ѵ�. @param _MaxCount ������ '�ִ� ������ ��ü ����'
			void				SetMaxObserverCount(int _MaxCount);

	//! @brief ������ ��ü�� �� á������ Ȯ���Ѵ�. @return true ��á��. false ������ �ʾҴ�.
			bool				IsObserverFull() const					{ LOCK(m_containerObserver) { return _IsObserverFull();}}
	//! @brief ������ ��ü�� �ϳ��� ������ Ȯ���Ѵ�. @return true ������ ����ִ�. false ������� �ʴ�.
			bool				IsObserverEmpty() const					{ LOCK(m_containerObserver) { return _IsObserverEmpty();}}
	//! @brief ������ ��ü�� �� ������ �ִ°��� Ȯ���Ѵ�. @return true �ִ� ������ ����ŭ ��á��. false �� ������ �ִ�.
			bool				IsObserverRoom() const					{ LOCK(m_containerObserver) { return _IsObserverRoom();}}
	//! @brief ������ ��ü�� �ϳ��� �ִ°��� Ȯ���Ѵ�. @return true ������� �ʴ�. false ������ ��� �ִ�.
			bool				IsObserverExist() const					{ LOCK(m_containerObserver) { return _IsObserverExist();}}

	//! @brief �������� ���� �Ǵ�.
			void				LockObservers() const					{ ICGReferenceable::AddRef(); m_containerObserver.lock();}	// Group List�� Lock�ɱ�.
	//! @brief �������� ����Ѵ�.
			void				UnlockObservers() const					{ m_containerObserver.unlock(); ICGReferenceable::Release();}	// Group List�� LockǮ��.
	//! @brief �������� ���� ��´�.
								operator LOCKABLE<>&()					{ return m_containerObserver;}	// ������ overlading(LOCKU��)

	//! @brief ������ �ݺ��� ó�� �������� ��´�. @return 'ó�� ������'
			ITERATOR			begin()									{ return m_containerObserver.begin();}
	//! @brief ������ �ݺ��� ó�� �������� ��´�. @return 'ó�� ������'
			CONST_ITERATOR		begin() const							{ return m_containerObserver.begin();}
	//! @brief ������ �ݺ��� �� �������� ��´�. @return '�� ������'
			ITERATOR			end()									{ return m_containerObserver.end();}
	//! @brief ������ �ݺ��� �� �������� ��´�. @return '�� ������'
			CONST_ITERATOR		end() const								{ return m_containerObserver.end();}

	//! @brief Ư�� �������� ã�´�. @param _fCondition ã�� ���� �Լ� @return ã�� ��� ������
			CGPTR<TOBSERVER>	FindObserver(const std::function<bool (TOBSERVER*)>& _fCondition);
	//! @brief ��� �������� Ư�� �Լ��� �����Ѵ�. @param _fExecute �����ϴ� �Լ� @return true ���� @return false ����
			bool				ForEachObserver(const std::function<bool (TOBSERVER*)>& _fExecute);


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief ���ο� �������� ��ϵǱ� ���� ȣ��Ǵ� �Լ� @param _pObserver ����� '������ ��ü' @param _Msg ��Ͻ� ������ �޽��� @return eOBJECT_RESULT::SUCCESS ���� ���� @return !eOBJECT_RESULT::SUCCESS ���� ����
	virtual	eOBJECT_RESULT		OnObserverRegistering(TOBSERVER* /*_pObserver*/, CGMSG& /*_Msg*/){ return eOBJECT_RESULT::SUCCESS;}
	//! @brief ���ο� ����� ��ϵ� �� ȣ��Ǵ� �Լ� @param _pObserver ����� '������ ��ü' @param _Msg ��Ͻ� ������ �޽���
	virtual	void				OnObserverRegistered(TOBSERVER* /*_pObserver*/, CGMSG& /*_Msg*/) {}

	//! @brief �������� ��������Ǳ� ������ ȣ��Ǵ� �Լ� @param _pObserver ��������� '������ ��ü' @return ������ ��
	virtual	uintptr_t			OnObserverUnregistering(TOBSERVER* /*_pObserver*/) { return 0;}
	//! @brief �������� ��������� �� ȣ��Ǵ� �Լ� @param _pObserver ��������� '������ ��ü' @param _Result OnObserverUnregistering()�� ���� �Լ�
	virtual	void				OnObserverUnregistered(TOBSERVER* /*_pObserver*/, uintptr_t /*_Result*/){}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) ���� �پ� �ִ� Peer�� ��/�ִ� Peer�� ���� �����ϱ� �Լ�.
			int					_GetObserverCount() const				{	return static_cast<int>(m_containerObserver.size());}
			int					_GetObserverRoomCount() const			{	return m_countMaxObserver-m_containerObserver.size();}
			int					_GetMaxObserverCount() const			{	return m_countMaxObserver;}
			
	// 2) Peer�� ���¸� ��� �Լ�.(��á�°�?, ������ ����°�?, �ڸ��� ���Ҵ°�?)
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
	// Check) _pObserver�� nullptr�̸� �ȉ´�.
	RETURN_IF(_pObserver==nullptr, eOBJECT_RESULT::INVALID_ARGUMENT);
	
	LOCK(m_containerObserver)
	{
		// Check) �� á�°�?
		RETURN_IF(IsObserverFull(), eOBJECT_RESULT::MEMBER_FULL);

		// Check) �̹� ���� Observer�� �����ϴ��� Ȯ���Ѵ�.
		ITERATOR	iterFind	 = std::find(m_containerObserver.begin(), m_containerObserver.end(), _pObserver);

		// Check) �̹� �پ� �ִٸ� ������.
		RETURN_IF(iterFind != m_containerObserver.end(), eOBJECT_RESULT::ALEADY_EXIST);

		// 1) OnObserverRegistering()�Լ��� ȣ���Ѵ�.
		auto	eResult	 = OnObserverRegistering(_pObserver, _Msg);

		// Check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(eResult!=eOBJECT_RESULT::SUCCESS, eResult);

		// 2) �߰��Ѵ�.
		m_containerObserver.push_back(_pObserver);

		// 3) OnObserverRegistered()�Լ��� ȣ���Ѵ�.
		try
		{
			OnObserverRegistered(_pObserver, _Msg);
		}
		// Exception) Rollback�Ѵ�.
		catch(const std::exception& e)
		{
			// Log)
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Excp) CGServerGroup: Exception Completeion[OnObserverRegistered] ") _CGFUNCTION);

			// - OnException�� ȣ���Ѵ�.
			auto	bExecuted	 = CGException::ExecuteExceptionHandler(this, e, _CGTEXT(__FUNCTION__));

			// - Observer�� �����Ѵ�.
			m_containerObserver.pop_back();

			// Check) 
			RETURN_IF(bExecuted, eOBJECT_RESULT::EXCEPTION);

			// Reraise) 
			throw;
		}
	}

	// Return) �����̴�!!!
	return	eOBJECT_RESULT::SUCCESS;
}

template <class TOBSERVER>
bool CList<TOBSERVER>::UnregisterObserver(TOBSERVER* _pObserver)
{
	// Check) _pObserver�� nullptr�̿����� �ȉ´�.
	CGASSERT(_pObserver!=nullptr, );
	
	LOCK(m_containerObserver)
	{
		// Declare) 
		uintptr_t	dwResult	 = 0;

		// 1) ���� �̹� ��ϵǾ� �ִ��� ã�´�.
		ITERATOR	iterFind	 = std::find(m_containerObserver.begin(), m_containerObserver.end(), _pObserver);

		// Check) ã�� �������� ������.
		RETURN_IF(iterFind==m_containerObserver.end(), false);

		// 2) OnObserverUnregistering()�Լ��� ȣ���Ѵ�.
		try
		{
			dwResult	 = OnObserverUnregistering(_pObserver);
		}
		// Exception) 
		catch(const std::exception& e)
		{
			CGLOG_EXCEPTION(DEFAULT_LOGGER, _CGTEXT("(Prgr) CGNetObserver : Occure exception in 'OnObserverUnregistering' function on Observer object ") _CGFUNCTION);
		}

		// 2) �����Ѵ�.
		m_containerObserver.erase(iterFind);

		// 3) OnObserverUnregistered()�Լ��� ȣ���Ѵ�.
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
			// Check) nullptr�̸� ����...
			CONTINUE_IF(iter->IsEmpty());

			// 1) Observer�� Unregister�Ѵ�.
			UnregisterObserver(iter);
		}
	}
}


template <class TOBSERVER>
void CList<TOBSERVER>::SetMaxObserverCount(int _MaxCount)
{
	LOCK(m_containerObserver)
	{
		// 1) �ִ� Observer���� �����Ѵ�.
		m_countMaxObserver	 = _MaxCount;
	
		// 2) Reserve�Ѵ�.(Reserver�Լ��� ���� ��쿡��...)
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
			// 1) Execute�Լ��� �����Ѵ�.
			bool	result	 = _fCondition(iter);

			// Check) 
			RETURN_IF(result==true, iter);
		}
	}

	// Return) ã�� ���ߴ�..
	return	CGPTR<TOBSERVER>();
}

template <class TOBSERVER>
bool CList<TOBSERVER>::ForEachObserver(const std::function<bool (TOBSERVER*)>& _fExecute)
{
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		for(auto& iter:m_containerObserver)
		{
			// 1) Execute�Լ��� �����Ѵ�.
			bool	result	 = _fExecute(*iter);

			// Check) 
			RETURN_IF(result==false, false);
		}
	}

	// Return) ����...
	return	true;
}


}