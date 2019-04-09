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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::IO::ConnectableManager
//
// 1. CGNet::IO::ConnectableManager
//    1) Socket�� List�� �����Ͽ� ��� ���ӵ� Socket�� �����ϰų� ��ü���� �޽�����
//       �����ϵ��� �� �� �ִ�.
//    2) �� Connectable Manager�� �Ϲ������� Connective::IAccptor�� IConnective��
//       ������������ �ʿ�� �Ѵ�.
//       Acceptor�� �Բ� ���� ��ӹ޾� Acceptor�� ���� Socket�� Connectable Manager��
//       ����� �����ϴ� ���� �Ϲ����̴�.
//
// 2. Connectable�� �����ϱ� ���� Iterator
//    1) �� Connectable Manager���� �����ϴ� Iterator�� Iterator�� ��� ����
//       ��ü�� Lock�� �ɸ��� �Ǹ� Iterator�� �Ҹ�ɶ����� Lock�� �����Ѵ�.
//       ���� Iterator�� ��� �۾��� ó���� �� �ִ��� ���� Iterator�� �Ҹ���Ѿ�
//       �Ѵ�.
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

	// 3) Send (Send�Լ��� ���� ��츸...)
	virtual bool				Send(_In_ const CCGBuffer& _Buffer) override;

	// 4) Connectable ��
	virtual	int					GetCount() const override;

	// 5) Iterator���
	virtual	CGPTR<CONNECTABLE_ITERATOR>	AllocIterator() override;

	// 6) Iterator���.
			ITERATOR			begin()									{	return m_listConnectable.begin();}
			ITERATOR			end()									{	return m_listConnectable.end();}

	// 7) Lock�� �ɱ� ����...
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
	// 1) ���� Accept���� Socket ����.
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
	// 1) Connectable�� ��´�.
	auto	pConnectable	 = dynamic_cast<TCONNECTABLE*>(_pConnectable);

	// Check) 
	THROW_IF(pConnectable==nullptr, CGException::CThrow_InvalidArgument(_CGTEXT("CGNetSocket: CGNet::IO::Connectable::CList<T>::AddConnectable�� _pConnectable�� nullptr�Դϴ�. ") _CGFUNCTION));

	LOCK(m_listConnectable)
	{
		// 1) Connectable�� Socket List�� �߰��Ѵ�.
		m_listConnectable.push_front(pConnectable);

		// Check) 
		CGASSERT_ERROR(_pConnectable->m_flexible.get<IConnectableManager*>()==nullptr);

		// 2) pConnectableManager�� ������ ���´�.
		_pConnectable->m_flexible.get<IConnectableManager*>()	 = this;

		// 3) Iterator�� ������ ���´�.
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
		// 1) Connectable Manager�� ��´�.
		IConnectableManager*	pConnectableManager	 = _pConnectable->m_flexible.get<IConnectableManager*>();

		// Check) ���� Connectable�� nullptr�̸� �׳� ������!
		RETURN_IF(pConnectableManager==nullptr, false);

		// Check) pConnectableManager�� ����� this�������� �Ѵ�.
		CGASSERT_ERROR(pConnectableManager==this);

		// 2) list���� �����.
		m_listConnectable.erase(_pConnectable->m_flexible.get<ITERATOR>(sizeof(IConnectableManager*)));

		// 3) pConnectableManager�� nullptr�� �����Ѵ�.
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
		// 1) Connect Count�� ������ ���´�.
		int	iSize	 = static_cast<int>(m_listConnectable.size());

		// 2) List�� �� ���δ�.
		m_listConnectable.clear();

		// 3) Reference Count�� ���δ�.
		AddRef(-iSize);
	}
}

template <class TCONNECTABLE>
void CList<TCONNECTABLE>::DisconnectAllConnectable()
{
	LOCK(m_listConnectable)
	{
		// 1) ��� Disconnect�Ѵ�.
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

			// 1) CloseSocket�Ѵ�.
			iter->CloseSocket();
		}
	}
}

template <class TCONNECTABLE>
bool CList<TCONNECTABLE>::Send(_In_ const CCGBuffer& _Buffer)
{
#if defined(_MSC_VER)
	// Case) Send�Լ��� ���� ���...
	__if_exists(TCONNECTABLE::Send)
	{
		LOCK(m_listConnectable)
		{
			for(auto& iter:m_listConnectable)
			{
				// - �����Ѵ�.
				iter->Send(_Buffer);
			}
		}
	}

	// Case) Send�Լ��� ���� ��츸...
	__if_not_exists(TCONNECTABLE::Send)
	{
#endif
		LOCK(m_listConnectable)
		{
			for(auto& iter:m_listConnectable)
			{
				// - Sender�� ��´�.
				auto	pSender	 = dynamic_cast<CGNet::IO::ISender*>(iter.get());

				// Check) 
				CONTINUE_IF(pSender==nullptr);

				// - �����Ѵ�.
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
			// 1) Ȯ���Ѵ�.
			bool	result	 = _fCondition(iter);

			// Check) result�� true�� ������ �� ���� �����Ѵ�.
			RETURN_IF(result==true, *iter);
		}
	}

	// Return) ã�� ������ ���� nullptr�� ���ϵȴ�.
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
			// 1) _fExecute�Լ��� �����Ѵ�.
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
