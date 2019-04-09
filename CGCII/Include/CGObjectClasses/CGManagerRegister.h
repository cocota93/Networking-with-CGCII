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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CManagerRegister
//
// 1. CManagerRegister란!
//    1) 
//    2) 
//
//-----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// 1) Transaction ID
//    요청을 수행할 때 요청마다 부여되는 고유 ID로 일반적으로 순차적인 값을 가진다.
//    주로 서버간 요청을 수행할 때 사용된다.
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
//    전달해 준 소스를 구분해주는 ID
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
//    요청을 구분할 때 사용되는 ID
//    요청 ID는
//    
//    1. 요청을 한 곳을 나타내는 SOURCE_ID
//    2. 요청번호를 의미하는 TRANSACTION_ID
//
//    로 구분하여 저장한다.
//
//    다른 곳에서 생성된 TRANSACTION_ID를  전달받아 사용할 경우 TRANSACTION_ID
//   만으로 구분할 경우 TRANSACTION_ID가 중복될 수 있다.
//    따라서 전달 받은 TRANSACTION_ID에 전달받은 Source의 ID를 결합하여 만든 ID이다.
//   일반적으로 여러 Remote에서 전달받은 Transaction ID를 구분하여 사용할 때 쓰인다.
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
	// Declare) RequestID을 얻는다.
	TKEY	dwRegisterID;

	// 1) Key를 Generate한다.
	dwRegisterID.generate();

	// 2) Insert한다.
	auto	result	 = m_mapRegister.insert(std::make_pair(dwRegisterID, _Object));

	// Check) 삽입하지 못했다면 Exception을 던진다.
	THROW_IF(result.second==false, CGException::CThrow_AleadyExist(_CGTEXT("Fail to insert ") _CGFUNCTION));

	// 3) Hook함수 호출
	OnRegister(_Object, dwRegisterID);

	// Return) 
	return	dwRegisterID;
}

template <typename TOBJECT, typename TKEY>
void CGManagerRegister<TOBJECT, TKEY>::_RegisterObject(TOBJECT* _Object, const TKEY& _idRegister)
{
	// Check)
	CGASSERT_ERROR(_idRegister.exist());

	// Check) 삽입하지 못했다면 Exception을 던진다.
	THROW_IF(_idRegister.empty(), CGException::CThrow_InvalidArgument(_CGTEXT("Fail to insert ") _CGFUNCTION));

	// 1) Insert한다.
	auto	result	 = m_mapRegister.insert(std::make_pair(_idRegister, _Object));

	// Check) 삽입하지 못했다면 Exception을 던진다.
	THROW_IF(result.second==false, CGException::CThrow_AleadyExist(_CGTEXT("Fail to insert ") _CGFUNCTION));

	// 2) Hook함수 호출
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

	// 1) Account ID에 해당하는 Request정보를 얻는다.
	auto	iterFind	 = m_mapRegister.find(_Key);

	// Check) 찾지 못했다면 끝낸다.
	RETURN_IF(iterFind==m_mapRegister.end(), CGPTR<TOBJECT>());

	// 2) 찾은 Request의 SocketUser를 저장해 놓는다.
	pObject	 = iterFind->second;

	// 2) Hook함수 호출
	OnUnregister(pObject, _Key);

	// 3) 지운다.
	m_mapRegister.erase(iterFind);

	// Return) 
	return	pObject;
}

template <typename TOBJECT, typename TKEY>
bool CGManagerRegister<TOBJECT, TKEY>::_UnregisterObjectIf(const TKEY& _Key, TOBJECT* _Object)
{
	// Declare) 
	CGPTR<TOBJECT>	pObject;

	// 1) Account ID에 해당하는 Request정보를 얻는다.
	auto	iterFind	 = m_mapRegister.find(_Key);

	// Check) 찾지 못했다면 끝낸다.
	RETURN_IF(iterFind==m_mapRegister.end(), false);

	// Check) 
	RETURN_IF(_Object!=iterFind->second, false);

	// 2) Hook함수 호출
	OnUnregister(iterFind->second, _Key);

	// 3) 지운다.
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
		// 1) 먼저 Reserve
		vectorAll.reserve(m_mapRegister.size());

		// 1) 모든 Request의 OnUnregister를 호출한다.
		for(auto& iter:m_mapRegister)
		{
			// - vectorAll에 넣는다
			vectorAll.push_back(iter.second);

			// - Unregister한다.
			OnUnregister(iter.second, iter.first);
		}

		// 2) 클리어한다.
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
	// 1) Account ID에 해당하는 Request정보를 얻는다.
	auto	iterFind	 = m_mapRegister.find(_Key);

	// Check) 찾지 못했다면 끝낸다.
	RETURN_IF(iterFind==m_mapRegister.end(), CGPTR<TOBJECT>());

	// Return) 찾은 객체를 리턴한다.
	return	iterFind->second;
}
