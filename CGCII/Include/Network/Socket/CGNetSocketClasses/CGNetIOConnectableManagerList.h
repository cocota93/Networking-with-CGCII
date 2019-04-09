//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Network Socket Classes                           *
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
// CGNet::IO::ConnectableManager
//
// 1. CGNet::IO::ConnectableManager
//    1) Socket을 List로 관리하여 모든 접속된 Socket을 열람하거나 전체에게 메시지를
//       전송하도록 할 수 있다.
//    2) 이 Connectable Manager는 일반적으로 Connective::IAccptor나 IConnective의
//       구현과정에서 필요로 한다.
//       Acceptor와 함께 다중 상속받아 Acceptor를 받은 Socket을 Connectable Manager를
//       사용해 관리하는 것이 일반적이다.
//
// 2. Connectable을 열람하기 위한 Iterator
//    1) 이 Connectable Manager에서 제공하는 Iterator는 Iterator를 얻는 순간
//       전체에 Lock이 걸리게 되며 Iterator가 소멸될때까지 Lock을 유지한다.
//       따라서 Iterator를 얻어 작업을 처리한 후 최대한 빨리 Iterator를 소멸시켜야
//       한다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace ConnectableManager
{

template <class TCONNECTABLE=CGNet::IO::IConnectable>
class CList : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				IConnectableManager,					//     Connectable manager
	virtual public				CGNet::IO::ISender						//     Sender
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
		typedef	typename circular_list<CGPTR<TCONNECTABLE>>::iterator	ITERATOR;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CList()														{}
	virtual	~CList()													{	RemoveAllConnectable();}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Connected Socket
	virtual	bool				AddConnectable(_In_ IConnectable* _pConnectable) override;
	virtual	bool				RemoveConnectable(_In_ IConnectable* _pConnectable) override;
			void				RemoveAllConnectable();

	// 2) Disconnect All Accepted Socket
	virtual	void				DisconnectAllConnectable() override;
	virtual	void				CloseAllConnectable(_In_ uint32_t p_dwFlag=0) override;

	// 3) Send (Send함수가 있을 경우만...)
	virtual bool				Send(_In_ const CCGBuffer& _Buffer) override;

	// 4) Connectable 수
	virtual	int					GetCount() const override;

	// 5) Iterator얻기
	virtual	CGPTR<CONNECTABLE_ITERATOR>	AllocIterator() override;

	// 6) Iterator얻기.
			ITERATOR			begin()									{	return m_listConnectable.begin();}
			ITERATOR			end()									{	return m_listConnectable.end();}

	// 7) Lock을 걸기 위해...
								operator CGD::lockable&()				{	return m_listConnectable;}

	// 8) Lambda Executor
	#if _MSC_VER>=_MSC_VER_2010
			CGPTR<TCONNECTABLE>	FindConnectable(_In_ const std::function<bool (TCONNECTABLE*)>& _fCondition);
			bool				ForEachConnectable(_In_ const std::function<bool (TCONNECTABLE*)>& _fExecute);
	#endif


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) 현재 Accept받은 Socket 정보.
			LOCKABLE<circular_list<CGPTR<TCONNECTABLE>>>	m_listConnectable;

			void				ClearConnectableList();

	// Definitions) Connectable Iterator
	class CONNECTABLE_ITERATORList : public CONNECTABLE_ITERATOR
	{
	public:
				CONNECTABLE_ITERATORList(ITERATOR p_IterBegin, ITERATOR p_IterEnd, CGD::lockable* p_csLock) : m_csLock(p_csLock), m_iterNow(p_IterBegin), m_iterBegin(p_IterBegin), m_iterEnd(p_IterEnd) 	{	m_csLock->lock();}
				~CONNECTABLE_ITERATORList()								{	m_csLock->unlock();}

		virtual	void			Reset() override						{	m_iterNow=m_iterBegin;}
		virtual	TCONNECTABLE*	GetPre() override						{	return	(m_iterNow!=m_iterBegin) ? (*m_iterNow--).get() : nullptr;}
		virtual	TCONNECTABLE*	GetNext() override						{	return	(m_iterNow!=m_iterEnd) ? (*m_iterNow++).get() : nullptr;}

	public:
				CGD::lockable*	m_csLock;
				ITERATOR		m_iterNow;
				ITERATOR		m_iterBegin;
				ITERATOR		m_iterEnd;
	};

	friend	CONNECTABLE_ITERATORList;
};


template <class TCONNECTABLE>
bool CList<TCONNECTABLE>::AddConnectable(_In_ IConnectable* _pConnectable)
{
	// 1) Connectable을 얻는다.
	auto	pConnectable	 = dynamic_cast<TCONNECTABLE*>(_pConnectable);

	// Check) 
	THROW_IF(pConnectable==nullptr, CGException::CThrow_InvalidArgument(_CGTEXT("CGNetSocket: CGNet::IO::Connectable::CList<T>::AddConnectable의 _pConnectable이 nullptr입니다. ") _CGFUNCTION));

	LOCK(m_listConnectable)
	{
		// 1) Connectable을 Socket List에 추가한다.
		m_listConnectable.push_front(pConnectable);

		// Check) 
		CGASSERT_ERROR(_pConnectable->m_flexible.get<IConnectableManager*>()==nullptr);

		// 2) pConnectableManager를 설정해 놓는다.
		_pConnectable->m_flexible.get<IConnectableManager*>()	 = this;

		// 3) Iterator를 저장해 놓는다.
	#pragma push_macro("new")
	#undef new
		new (&pConnectable->m_flexible.flexible<16>::get<ITERATOR>(sizeof(IConnectableManager*))) typename circular_list<CGPTR<TCONNECTABLE>>::iterator(m_listConnectable.begin());
	#pragma pop_macro("new")
	}

	// Return) 
	return	true;
}

template <class TCONNECTABLE>
bool CList<TCONNECTABLE>::RemoveConnectable(_In_ IConnectable* _pConnectable)
{
	LOCK(m_listConnectable)
	{
		// 1) Connectable Manager를 얻는다.
		IConnectableManager*	pConnectableManager	 = _pConnectable->m_flexible.get<IConnectableManager*>();

		// Check) 만약 Connectable이 nullptr이면 그냥 끝낸다!
		RETURN_IF(pConnectableManager==nullptr, false);

		// Check) pConnectableManager는 만드시 this여야지만 한다.
		CGASSERT_ERROR(pConnectableManager==this);

		// 2) list에서 지운다.
		m_listConnectable.erase(_pConnectable->m_flexible.get<ITERATOR>(sizeof(IConnectableManager*)));

		// 3) pConnectableManager를 nullptr로 설정한다.
		_pConnectable->m_flexible.get<IConnectableManager*>()	 = nullptr;
	}

	// Return) 
	return	true;
}

template <class TCONNECTABLE>
void CList<TCONNECTABLE>::RemoveAllConnectable()
{
	ClearConnectableList();
}

template <class TCONNECTABLE>
void CList<TCONNECTABLE>::ClearConnectableList()
{
	LOCK(m_listConnectable)
	{
		// 1) Connect Count를 저장해 놓는다.
		int	iSize	 = static_cast<int>(m_listConnectable.size());

		// 2) List를 싹 줄인다.
		m_listConnectable.clear();

		// 3) Reference Count를 줄인다.
		AddRef(-iSize);
	}
}

template <class TCONNECTABLE>
void CList<TCONNECTABLE>::DisconnectAllConnectable()
{
	LOCK(m_listConnectable)
	{
		// 1) 모두 Disconnect한다.
		for(auto& iter:m_listConnectable)
		{
			iter->Disconnect();
		}
	}
}

template <class TCONNECTABLE>
void CList<TCONNECTABLE>::CloseAllConnectable(_In_ uint32_t p_dwFlag)
{
	auto	qwTick	 = TICK::now();
	
	LOCK(m_listConnectable)
	{
		for(auto& iter:m_listConnectable)
		{
			// Check) 
			if(p_dwFlag)
			{
				if(iter->GetSocketState()== eSOCKET_STATE::CLOSED)
				{
					TICK::duration	tickDiffer	 = qwTick-iter->Statistics_GetTickDisconnect();

					CONTINUE_IF(tickDiffer<TICK::seconds(10));
				}
			}

			// 1) CloseSocket한다.
			iter->CloseSocket();
		}
	}
}

template <class TCONNECTABLE>
bool CList<TCONNECTABLE>::Send(_In_ const CCGBuffer& _Buffer)
{
#if defined(_MSC_VER)
	// Case) Send함수가 있을 경우...
	__if_exists(TCONNECTABLE::Send)
	{
		LOCK(m_listConnectable)
		{
			for(auto& iter:m_listConnectable)
			{
				// - 전송한다.
				iter->Send(_Buffer);
			}
		}
	}

	// Case) Send함수가 없을 경우만...
	__if_not_exists(TCONNECTABLE::Send)
	{
#endif
		LOCK(m_listConnectable)
		{
			for(auto& iter:m_listConnectable)
			{
				// - Sender를 얻는다.
				auto	pSender	 = dynamic_cast<CGNet::IO::ISender*>(iter.get());

				// Check) 
				CONTINUE_IF(pSender==nullptr);

				// - 전송한다.
				pSender->Send(_Buffer);
			}
		}
#if defined(_MSC_VER)
	}
#endif

	// Return) 
	return	true;
}

template <class TCONNECTABLE>
int CList<TCONNECTABLE>::GetCount() const
{
	LOCK(m_listConnectable)
	{
		return	static_cast<int>(m_listConnectable.size());
	}
}


#if _MSC_VER>=_MSC_VER_2010
template <class TCONNECTABLE>
CGPTR<TCONNECTABLE> CList<TCONNECTABLE>::FindConnectable(_In_ const std::function<bool(TCONNECTABLE*)>& _fCondition)
{
	LOCK(m_listConnectable)
	{
		for(auto& iter:m_listConnectable)
		{
			// 1) 확인한다.
			bool	result	 = _fCondition(iter);

			// Check) result가 true가 나오면 그 값을 리턴한다.
			RETURN_IF(result==true, *iter);
		}
	}

	// Return) 찾지 못했을 때는 nullptr이 리턴된다.
	return	CGPTR<TCONNECTABLE>();
}
#endif

#if _MSC_VER>=_MSC_VER_2010
template <class TCONNECTABLE>
bool CList<TCONNECTABLE>::ForEachConnectable(_In_ const std::function<bool(TCONNECTABLE*)>& _fExecute)
{
	LOCK(m_listConnectable)
	{
		for(auto& iter:m_listConnectable)
		{
			// 1) _fExecute함수를 실행한다.
			bool	result	 = _fExecute(iter);

			// Check) 
			RETURN_IF(result==false, false);
		}
	}

	// Return) 
	return	true;
}
#endif

template <class TCONNECTABLE>
CGPTR<typename CList<TCONNECTABLE>::CONNECTABLE_ITERATOR> CList<TCONNECTABLE>::AllocIterator()
{
	return	NEW<CONNECTABLE_ITERATORList>(m_listConnectable.begin(), m_listConnectable.end(), &m_listConnectable);
}


}
}
}
