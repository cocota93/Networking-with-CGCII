//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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
// CManagerRegister
//
// 1. CManagerRegister��!
//    1) 
//    2) 
//
//-----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// 1) Transaction ID
//    ��û�� ������ �� ��û���� �ο��Ǵ� ���� ID�� �Ϲ������� �������� ���� ������.
//    �ַ� ������ ��û�� ������ �� ���ȴ�.
// ----------------------------------------------------------------------------
#pragma pack(1)

class TRANSACTION_ID
{
public:
			TRANSACTION_ID() : m_tid(0)											{}
			TRANSACTION_ID(const TRANSACTION_ID& _copy) : m_tid(_copy.m_tid)	{}
	explicit TRANSACTION_ID(uint64_t _tid) : m_tid(_tid)						{}

public:
			void				generate()										{ static ATOMIC<uint64_t> tid(0); uint64_t temp=++tid; if(temp==0) temp=++tid; m_tid=temp;}
			void				reset()											{ m_tid=0;}
			uint64_t			value()	const									{ return m_tid;}

			bool				empty() const									{ return m_tid==0;}
			bool				exist() const									{ return m_tid!=0;}

public:
			TRANSACTION_ID&		operator=(const TRANSACTION_ID& _rhs)			{ m_tid=_rhs.m_tid; return *this;}
			TRANSACTION_ID&		operator=(uint64_t _rhs)						{ m_tid=_rhs; return *this;}

			bool				operator==(const TRANSACTION_ID& _rhs) const	{ return m_tid==_rhs.m_tid;}
			bool				operator!=(const TRANSACTION_ID& _rhs) const	{ return m_tid!=_rhs.m_tid;}
			bool				operator>=(const TRANSACTION_ID& _rhs) const	{ return m_tid>=_rhs.m_tid;}
			bool				operator> (const TRANSACTION_ID& _rhs) const	{ return m_tid> _rhs.m_tid;}
			bool				operator<=(const TRANSACTION_ID& _rhs) const	{ return m_tid<=_rhs.m_tid;}
			bool				operator< (const TRANSACTION_ID& _rhs) const	{ return m_tid< _rhs.m_tid;}

private:
			uint64_t			m_tid;
};


// ----------------------------------------------------------------------------
// 2) Source ID
//    ������ �� �ҽ��� �������ִ� ID
// ----------------------------------------------------------------------------
class SOURCE_ID
{
public:
			SOURCE_ID() : m_sid(0) {}
			SOURCE_ID(const SOURCE_ID& _copy) : m_sid(_copy.m_sid) {}
	explicit SOURCE_ID(uint64_t _sid) : m_sid(_sid) {}

public:
	void				generate() { static ATOMIC<uint64_t> sid(0); uint64_t temp=++sid; if (temp==0) temp=++sid; m_sid=temp; }
	void				reset() { m_sid=0; }
	uint64_t			value()	const { return m_sid; }

	bool				empty() const { return m_sid==0; }
	bool				exist() const { return m_sid!=0; }

public:
	SOURCE_ID&			operator=(const SOURCE_ID& _rhs) { m_sid=_rhs.m_sid; return *this; }
	SOURCE_ID&			operator=(uint64_t _rhs) { m_sid=_rhs; return *this; }

	bool				operator==(const SOURCE_ID& _rhs) const { return m_sid==_rhs.m_sid; }
	bool				operator!=(const SOURCE_ID& _rhs) const { return m_sid!=_rhs.m_sid; }
	bool				operator>=(const SOURCE_ID& _rhs) const { return m_sid>=_rhs.m_sid; }
	bool				operator> (const SOURCE_ID& _rhs) const { return m_sid> _rhs.m_sid; }
	bool				operator<=(const SOURCE_ID& _rhs) const { return m_sid<=_rhs.m_sid; }
	bool				operator< (const SOURCE_ID& _rhs) const { return m_sid< _rhs.m_sid; }

						operator uint64_t() const				{	return m_sid;}

private:
	uint64_t			m_sid;
};


// ----------------------------------------------------------------------------
// 3) REQUEST ID
//    ��û�� ������ �� ���Ǵ� ID
//    ��û ID��
//    
//    1. ��û�� �� ���� ��Ÿ���� SOURCE_ID
//    2. ��û��ȣ�� �ǹ��ϴ� TRANSACTION_ID
//
//    �� �����Ͽ� �����Ѵ�.
//
//    �ٸ� ������ ������ TRANSACTION_ID��  ���޹޾� ����� ��� TRANSACTION_ID
//   ������ ������ ��� TRANSACTION_ID�� �ߺ��� �� �ִ�.
//    ���� ���� ���� TRANSACTION_ID�� ���޹��� Source�� ID�� �����Ͽ� ���� ID�̴�.
//   �Ϲ������� ���� Remote���� ���޹��� Transaction ID�� �����Ͽ� ����� �� ���δ�.
// ----------------------------------------------------------------------------
class REQUEST_ID
{
public:
			REQUEST_ID() : sid(0), tid()									{}
			REQUEST_ID(SOURCE_ID _sid, TRANSACTION_ID _tid) : sid(_sid), tid(_tid) {}
public:
			SOURCE_ID			sid;		// Source ID
			TRANSACTION_ID		tid;		// Transaction ID
public:
			void				reset()											{ sid=0; tid=0; }
			void				generate(SOURCE_ID _sid)						{ sid=_sid; tid.generate();}

			bool				empty() const									{ return sid==0; }
			bool				exist() const									{ return sid!=0; }
public:
			REQUEST_ID&			operator= (const REQUEST_ID& _rhs)				{ sid=_rhs.sid; tid=_rhs.tid; return *this; }
			bool				operator==(const REQUEST_ID& _rhs) const		{ return tid==_rhs.tid && sid==_rhs.sid; }
			bool				operator!=(const REQUEST_ID& _rhs) const		{ return tid!=_rhs.tid || sid!=_rhs.sid; }
			bool				operator>=(const REQUEST_ID& _rhs) const		{ return (tid>_rhs.tid) ? true : ((tid<_rhs.tid) ? false : (sid>=_rhs.sid)); }
			bool				operator> (const REQUEST_ID& _rhs) const		{ return (tid>_rhs.tid) ? true : ((tid<_rhs.tid) ? false : (sid> _rhs.sid)); }
			bool				operator<=(const REQUEST_ID& _rhs) const		{ return (tid<_rhs.tid) ? true : ((tid>_rhs.tid) ? false : (sid<=_rhs.sid)); }
			bool				operator< (const REQUEST_ID& _rhs) const		{ return (tid<_rhs.tid) ? true : ((tid>_rhs.tid) ? false : (sid< _rhs.sid)); }
};

#pragma pack()

namespace std 
{

template <>
struct hash<TRANSACTION_ID>
{
	std::size_t operator()(const TRANSACTION_ID& _Key) const
	{
		return	static_cast<size_t>(_Key.value());
	}
};

template <>
struct hash<SOURCE_ID>
{
	std::size_t operator()(const SOURCE_ID& _Key) const
	{
		return	static_cast<size_t>(_Key.value());
	}
};

template <>
struct hash<REQUEST_ID>
{
	std::size_t operator()(const REQUEST_ID& _Key) const
	{
		return	static_cast<size_t>(_Key.tid.value());
	}
};

}



template <typename TOBJECT, typename TKEY=REQUEST_ID>
class CGManagerRegister : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CGManagerRegister()							{}
	virtual	~CGManagerRegister()						{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Request/Unrequester
			TKEY				Register(TOBJECT* _Object);
			void				Register(TOBJECT* _Object, const TKEY& _idRegister);
			CGPTR<TOBJECT>		Unregister(const TKEY& _Key);
			vector<CGPTR<TOBJECT>> UnregisterAll();

	// 2) Request Count
			size_t				GetRegisteredCount() const;

			CGD::lockable&		GetLockable()		{	return m_mapRegister;}
			operator CGD::lockable&()				{	return m_mapRegister;}
			operator const CGD::lockable&() const	{	return m_mapRegister;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual void				OnRegister(TOBJECT* /*_Object*/, const TKEY& /*_Key*/)		{}
	virtual	void				OnUnregister(TOBJECT* /*_Object*/, const TKEY& /*_Key*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			LOCKABLE<std::unordered_map<TKEY, CGPTR<TOBJECT>>>	m_mapRegister;

public:
			TKEY				_RegisterObject(TOBJECT* _Object);
			void				_RegisterObject(TOBJECT* _Object, const TKEY& _Key);
			CGPTR<TOBJECT>		_UnregisterObject(const TKEY& _Key);
			bool				_UnregisterObjectIf(const TKEY& _Key, TOBJECT* _Object);
			size_t				_GetRegisteredCount() const;
			CGPTR<TOBJECT>		_FindObject(const TKEY& _Key) const;
};

template <typename TOBJECT, typename TKEY>
TKEY CGManagerRegister<TOBJECT, TKEY>::Register(TOBJECT* _Object)
{
	LOCK(m_mapRegister)
	{
		return	_RegisterObject(_Object);
	}
}

template <typename TOBJECT, typename TKEY>
void CGManagerRegister<TOBJECT, TKEY>::Register(TOBJECT* _Object, const TKEY& _idRegister)
{
	LOCK(m_mapRegister)
	{
		_RegisterObject(_Object, _idRegister);
	}
}

template <typename TOBJECT, typename TKEY>
TKEY CGManagerRegister<TOBJECT, TKEY>::_RegisterObject(TOBJECT* _Object)
{
	// Declare) RequestID�� ��´�.
	TKEY	dwRegisterID;

	// 1) Key�� Generate�Ѵ�.
	dwRegisterID.generate();

	// 2) Insert�Ѵ�.
	auto	result	 = m_mapRegister.insert(std::make_pair(dwRegisterID, _Object));

	// Check) �������� ���ߴٸ� Exception�� ������.
	THROW_IF(result.second==false, CGException::CThrow_AleadyExist(_CGTEXT("Fail to insert ") _CGFUNCTION));

	// 3) Hook�Լ� ȣ��
	OnRegister(_Object, dwRegisterID);

	// Return) 
	return	dwRegisterID;
}

template <typename TOBJECT, typename TKEY>
void CGManagerRegister<TOBJECT, TKEY>::_RegisterObject(TOBJECT* _Object, const TKEY& _idRegister)
{
	// Check)
	CGASSERT_ERROR(_idRegister.exist());

	// Check) �������� ���ߴٸ� Exception�� ������.
	THROW_IF(_idRegister.empty(), CGException::CThrow_InvalidArgument(_CGTEXT("Fail to insert ") _CGFUNCTION));

	// 1) Insert�Ѵ�.
	auto	result	 = m_mapRegister.insert(std::make_pair(_idRegister, _Object));

	// Check) �������� ���ߴٸ� Exception�� ������.
	THROW_IF(result.second==false, CGException::CThrow_AleadyExist(_CGTEXT("Fail to insert ") _CGFUNCTION));

	// 2) Hook�Լ� ȣ��
	OnRegister(_Object, _idRegister);
}

template <typename TOBJECT, typename TKEY>
CGPTR<TOBJECT> CGManagerRegister<TOBJECT, TKEY>::Unregister(const TKEY& _Key)
{
	LOCK(m_mapRegister)
	{
		return	_UnregisterObject(_Key);
	}
}

template <typename TOBJECT, typename TKEY>
CGPTR<TOBJECT> CGManagerRegister<TOBJECT, TKEY>::_UnregisterObject(const TKEY& _Key)
{
	// Declare) 
	CGPTR<TOBJECT>	pObject;

	// 1) Account ID�� �ش��ϴ� Request������ ��´�.
	auto	iterFind	 = m_mapRegister.find(_Key);

	// Check) ã�� ���ߴٸ� ������.
	RETURN_IF(iterFind==m_mapRegister.end(), CGPTR<TOBJECT>());

	// 2) ã�� Request�� SocketUser�� ������ ���´�.
	pObject	 = iterFind->second;

	// 2) Hook�Լ� ȣ��
	OnUnregister(pObject, _Key);

	// 3) �����.
	m_mapRegister.erase(iterFind);

	// Return) 
	return	pObject;
}

template <typename TOBJECT, typename TKEY>
bool CGManagerRegister<TOBJECT, TKEY>::_UnregisterObjectIf(const TKEY& _Key, TOBJECT* _Object)
{
	// Declare) 
	CGPTR<TOBJECT>	pObject;

	// 1) Account ID�� �ش��ϴ� Request������ ��´�.
	auto	iterFind	 = m_mapRegister.find(_Key);

	// Check) ã�� ���ߴٸ� ������.
	RETURN_IF(iterFind==m_mapRegister.end(), false);

	// Check) 
	RETURN_IF(_Object!=iterFind->second, false);

	// 2) Hook�Լ� ȣ��
	OnUnregister(iterFind->second, _Key);

	// 3) �����.
	m_mapRegister.erase(iterFind);

	// Return) 
	return	true;
}


template <typename TOBJECT, typename TKEY>
vector<CGPTR<TOBJECT>> CGManagerRegister<TOBJECT, TKEY>::UnregisterAll()
{
	// Declare) 
	vector<CGPTR<TOBJECT>> vectorAll;

	LOCK(m_mapRegister)
	{
		// 1) ���� Reserve
		vectorAll.reserve(m_mapRegister.size());

		// 1) ��� Request�� OnUnregister�� ȣ���Ѵ�.
		for(auto& iter:m_mapRegister)
		{
			// - vectorAll�� �ִ´�
			vectorAll.push_back(iter.second);

			// - Unregister�Ѵ�.
			OnUnregister(iter.second, iter.first);
		}

		// 2) Ŭ�����Ѵ�.
		m_mapRegister.clear();
	}

	// Return)
	return	vectorAll;
}

template <typename TOBJECT, typename TKEY>
size_t CGManagerRegister<TOBJECT, TKEY>::GetRegisteredCount() const
{
	LOCK(m_mapRegister)
	{
		return	_GetRegisteredCount();
	}
}

template <typename TOBJECT, typename TKEY>
size_t CGManagerRegister<TOBJECT, TKEY>::_GetRegisteredCount() const
{
	return	static_cast<int>(m_mapRegister.size());
}

template <typename TOBJECT, typename TKEY>
CGPTR<TOBJECT> CGManagerRegister<TOBJECT, TKEY>::_FindObject(const TKEY& _Key) const
{
	// 1) Account ID�� �ش��ϴ� Request������ ��´�.
	auto	iterFind	 = m_mapRegister.find(_Key);

	// Check) ã�� ���ߴٸ� ������.
	RETURN_IF(iterFind==m_mapRegister.end(), CGPTR<TOBJECT>());

	// Return) ã�� ��ü�� �����Ѵ�.
	return	iterFind->second;
}
