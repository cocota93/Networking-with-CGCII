//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Server Query DB Classes                          *
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
// CGServerQuery::DB::CQuery
//
// 1. CGServerQuery::DB::CQuery��!
//    1) ICGServerQuery�� Command�� ��ӹ޾� ���� �⺻ Query��.
//    2) Querier�� Query�� Post�ϰų� Request�ϰ� �Ǹ� Session�� �Ҵ�ް� �ȴ�.
//    3) Session�� �Ҵ�ް� �Ǹ� Query String�� �Ѱ� OpenQuery�Լ��� ȣ�������ν�
//       Query�� ������ �� �ִ�.
//    4) �׸��� Query�� �Ϸ�� �� CloseQuery�� ȣ���Ͽ� Query�� ������ �� �ִ�.
//    5) Start�� Stop�� ���ϴ� ��ŭ ������ �� ������ ���������� ProcessQuery()
//       �Լ��� ����Ǹ� Session�� �ݳ��ǰ� �ȴ�.
//
// 2. Accessor�� ����
//    1) ����� �� �ִ� Accessor�� �⺻������ ũ�� �ΰ����� �ִ�.
//					
//       - CAccessor<TACCESSOR> �⺻ Accessor�� Query�� ���� �� ������� Ŭ����
//         ���� ������ �޵��� �̸� ������ ������ �� ���̴�.
//       - CDynamicAccessor		Query�� ���� �� ����� �ʿ信 ���� ��� ���� 
//		                        �ֵ��� �� ������ ������ Query�� �����ϴ�.
//
// 3. Rowset�� ����
//    1) Query�� ��� 1���� �ϳ��� Row�̴�. �̰��� ó���ϱ� ���� ���� RowSet�̴�.
//       �⺻������ 3������ RowSet�� ����� �� �ִ�.
//      
//       - CNoRowset		Rowset�� ������� �ʴ´�.
//		 - CRowset		Rowset�� ����Ѵ�.
//		 - CMultiRowset	���� ���� Rowset�� ���� �� �ֵ��� �Ѵ�.
//
// 4. CMultipleResults�� ����
//	  1) ������ ����� ������ �����ϴ� ���̴�. ��ü������ ó���Ǵ� ������ ����
//		 �ٸ� ������ ���� Class�� ���û����� �Ʒ��� ����.
//
//		 - CNoMultipleResults	�Ѳ����� ���� ���� ������� ���� �ʴ´�.
//		 - CMultipleResults		�Ѳ����� ���� ���� ������� �޴´�.
//
// 
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DB
{

#define	CGQUERY_RETRY_MAX	4

template<class TACCESSOR=CDynamicAccessor, template <typename T> class TROWSET = CRowset, class TMULTIPLE = CMultipleResults>
class CQuery : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CCommand<TACCESSOR, TROWSET, TMULTIPLE>,// (@) Command
	virtual public				CGServerQuery::DB::IQuery				// (@) Querier
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CQuery();
	virtual ~CQuery();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Create command and set the command text
	template <class TCHAR_QUERY>
			intptr_t			PrepareQuery(_In_z_ const TCHAR_QUERY* _strCommand, _In_ REFGUID _guidCommand = DBGUID_DEFAULT);

	// 2) QUery Open/Close
			template<class TCHAR_QUERY>
			intptr_t			OpenQuery(
									_In_opt_ const TCHAR_QUERY* _strCommand,
									_In_opt_ CDBPropSet* _pProperty=nullptr,
									_In_opt_ DBROWCOUNT* _pRowsAffected=nullptr,
									_In_ REFGUID _guidCommand=DBGUID_DEFAULT,
									_In_ bool _bBind=true,
									_In_ ULONG _ulPropSets=0);

			intptr_t			OpenQuery(
									_In_ int _iCommand,
									_In_opt_ CDBPropSet* _pProperty=nullptr,
									_In_opt_ DBROWCOUNT* _pRowsAffected=nullptr,
									_In_ REFGUID _guidCommand=DBGUID_DEFAULT,
									_In_ bool _bBind=true,
									_In_ ULONG _ulPropSets=0);

			intptr_t			OpenQuery(
									_In_opt_ DBPROPSET* _pPropSet=nullptr,
									_In_opt_ DBROWCOUNT* _pRowsAffected=nullptr,
									_In_ bool _bBind=true,
									_In_ ULONG _ulPropSets=0);
			void				CloseQuery();

	// 3) For DefaultCommand
	__if_not_exists(GetDefaultCommand)
	{
			_STRING				m_stringQuery;

			void				Set(const wchar_t* _strCommand)			{	SetQueryString(_strCommand);}
			void				SetQueryString(const char* _strCommand)	{	wchar_t temp[2048]; MBS_TO_WCS(temp, 2048,_strCommand, 2048); m_stringQuery=temp;}
			void				SetQueryString(const wchar_t* _wstrQuery){	m_stringQuery=_wstrQuery;}
			const _STRING&		GetQueryString() const					{	return m_stringQuery;}
			LPCWSTR				_GetCommandString()						{	return m_stringQuery.c_str(); }
	}
	__if_exists(GetDefaultCommand)
	{
			LPCWSTR				_GetCommandString()						{	wchar_t* temp; GetDefaultCommand((LPCWSTR*)&temp); return temp;}
	};

	// 4) For CDynamicParameterAccessor
	__if_exists(TACCESSOR::BindParameters)
	{
			template<class TTYPE>
			typename std::enable_if<!std::is_pointer<TTYPE>::value, TTYPE>::type
								GetValue(_In_ int nColumn) const				{	return *(TTYPE*)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetValue((DBORDINAL)nColumn);}
			template<class TTYPE>
			typename std::enable_if<!std::is_pointer<TTYPE>::value, TTYPE>::type
								GetValue(_In_z_ const CHAR* _strColumnName) const{	return *(TTYPE*)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetValue(_strColumnName);}
			template<class TTYPE>
			typename std::enable_if<!std::is_pointer<TTYPE>::value, TTYPE>::type
								GetValue(_In_z_ const WCHAR* _wstrColumnName) const{	return *(TTYPE*)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetValue(_wstrColumnName);}

			template<class TTYPE>
			typename std::enable_if<std::is_pointer<TTYPE>::value, TTYPE>::type
								GetValue(_In_ int nColumn) const				{	return (TTYPE)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetValue(nColumn);}
			template<class TTYPE>
			typename std::enable_if<std::is_pointer<TTYPE>::value, TTYPE>::type
								GetValue(_In_z_ const CHAR* _strColumnName) const {	return (TTYPE)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetValue(_strColumnName);}
			template<class TTYPE>
			typename std::enable_if<std::is_pointer<TTYPE>::value, TTYPE>::type
								GetValue(_In_z_ const WCHAR* _wstrColumnName) const{	return (TTYPE)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetValue(_wstrColumnName);}

			// - SetParam
			typedef	char*		CHAR_STR;
			typedef	wchar_t*	WCHAR_STR;

			template<class TTYPE>
			bool				SetParam(_In_ int _iOrdinal, _In_ const TTYPE& _Data, _In_ DBSTATUS _Status=DBSTATUS_S_OK)			{ return CCommand<TACCESSOR, TROWSET, TMULTIPLE>::SetParam(_iOrdinal, &_Data, _Status);}
			template<>
			bool				SetParam<char*>(_In_ int _iOrdinal, _In_ const CHAR_STR& _String, _In_ DBSTATUS _Status)			{ return CCommand<TACCESSOR, TROWSET, TMULTIPLE>::SetParamString(_iOrdinal, _String, _Status);}
			template<>
			bool				SetParam<wchar_t*>(_In_ int _iOrdinal, _In_ const WCHAR_STR& _String, _In_ DBSTATUS _Status)		{ return CCommand<TACCESSOR, TROWSET, TMULTIPLE>::SetParamString(_iOrdinal, _String, _Status); }
			template<>
			bool				SetParam<std::string>(_In_ int _iOrdinal, _In_ const std::string& _String, _In_ DBSTATUS _Status)	{ return CCommand<TACCESSOR, TROWSET, TMULTIPLE>::SetParamString(_iOrdinal, _String.c_str(), _Status); }
			template<>
			bool				SetParam<std::wstring>(_In_ int _iOrdinal, _In_ const std::wstring& _String, _In_ DBSTATUS _Status)	{ return CCommand<TACCESSOR, TROWSET, TMULTIPLE>::SetParamString(_iOrdinal, _String.c_str(), _Status); }

			template<class TTYPE>
			TTYPE				GetParam(_In_ int _iOrdinal)					{	return *(TTYPE*)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetParam(_iOrdinal);}
			template<class TTYPE>
			TTYPE				GetParam(_In_z_ const CHAR* _strColumnName)		{	return *(TTYPE*)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetParam(_strColumnName);}
			template<class TTYPE>
			TTYPE				GetParam(_In_z_ const WCHAR* _wstrColumnName)	{	return *(TTYPE*)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetParam(_wstrColumnName);}

			template<class TTYPE>
			const TTYPE*		GetParamString(_In_ int _iOrdinal)				{	CGASSERT_ERROR(false);}
			template<>
			const CHAR*			GetParamString<CHAR>(_In_ int _iOrdinal)		{	return (CHAR*)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetParam(nParam);}
			template<>
			const WCHAR*		GetParamString<WCHAR>(_In_ int _iOrdinal)		{	return (WCHAR*)CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetParam(nParam);}

			DBORDINAL			GetOrdinal(_In_z_ const CHAR* _strColumnName)	{	DBORDINAL iOrdinal; if(CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetOrdinal(_strColumnName, &iOrdinal)==false) throw CGException::CThrow_InvalidArgument(); return iOrdinal;}
			DBORDINAL			GetOrdinal(_In_z_ const WCHAR* _wstrColumnName)	{	DBORDINAL iOrdinal; if(CCommand<TACCESSOR, TROWSET, TMULTIPLE>::GetOrdinal(_wstrColumnName, &iOrdinal)==false) throw CGException::CThrow_InvalidArgument(); return iOrdinal;}
	}


public:
			typedef	CQuery<TACCESSOR, TROWSET, TMULTIPLE>	TSELF;

			struct RESULT
			{
				RESULT()		{}
				RESULT(TSELF* _Query) : pQuery(_Query)		{}

				TSELF*			pQuery;

				struct ITERATOR
				{
				public:
					ITERATOR()		{}
					ITERATOR(const ITERATOR& _Copy) : pQuery(_Copy.pQuery), hResult(_Copy.hResult) {}
					ITERATOR(TSELF* _Query, intptr_t _hResult) : pQuery(_Query), hResult(_hResult) {}

					CGPTR<TSELF>	pQuery;
					intptr_t		hResult;

					ITERATOR&		operator=(const ITERATOR& _rhs) NOEXCEPT{ pQuery=_rhs.pQuery; hResult=_rhs.hResult;return (*this);}
					TSELF*			operator->() const NOEXCEPT				{ return pQuery;}
					TSELF&			operator*() NOEXCEPT					{ return *pQuery;}
					const TSELF&	operator*()	const NOEXCEPT				{ return *pQuery;}

					bool			operator==(const ITERATOR& _Rhs) const	{ return hResult!=_Rhs.hResult;}
					bool			operator!=(const ITERATOR& _Rhs) const	{ return hResult==_Rhs.hResult;}

					ITERATOR&		operator++()							{ hResult=pQuery->GetNextResult(nullptr); return *this;}
					ITERATOR&		operator++(int)							{ hResult=pQuery->GetNextResult(nullptr); return *this;}
				};

				ITERATOR			begin()									{	return ITERATOR(pQuery, S_OK);}
				ITERATOR			end()									{	return ITERATOR(nullptr, S_OK);}
			};

			RESULT				Result()									{ return RESULT(this);}

			struct ITERATOR
			{
			public:
				ITERATOR()		{}
				ITERATOR(const ITERATOR& _Copy) : pQuery(_Copy.pQuery), hResult(_Copy.hResult) {}
				ITERATOR(TSELF* _Query, intptr_t _hResult) : pQuery(_Query), hResult(_hResult) {}

				TSELF*			pQuery;
				intptr_t		hResult;

				ITERATOR&		operator=(const ITERATOR& _rhs) NOEXCEPT	{ pQuery = _rhs.pQuery; hResult = _rhs.hResult;return (*this); }
				TSELF*			operator->() const NOEXCEPT					{ return pQuery; }
				TSELF&			operator*() NOEXCEPT						{ return *pQuery; }
				const TSELF&	operator*()	const NOEXCEPT					{ return *pQuery; }

				bool			operator==(const ITERATOR& _Rhs) const		{ return hResult!=_Rhs.hResult; }
				bool			operator!=(const ITERATOR& _Rhs) const		{ return hResult==_Rhs.hResult; }

				ITERATOR&		operator++()								{ hResult = pQuery->MoveNext(); return *this; }
				ITERATOR&		operator++(int)								{ hResult = pQuery->MoveNext(); return *this; }
			};

			ITERATOR			begin()										{ return ITERATOR(this, (m_spRowset != nullptr) ? MoveFirst() : E_FAIL); }
			ITERATOR			end()										{ return ITERATOR(nullptr, S_OK); }
	

// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) OnBeginQuery/OnEndQuery	
	virtual	void				OnBeginQuery()								{}
	virtual	void				OnEndQuery(intptr_t /*p_hResult*/)			{}


// ****************************************************************************
// Implementations) 
// ----------------------------------------------------------------------------
protected:
	// 1) Query��û ������ �����ϴ� �Լ�.
	virtual	intptr_t			ProcessRequestQuery();

public:
	// 4) Poolable�� ����ؼ�...
	virtual	void				OnFinalRelease() override					{	CloseQuery(); CGServerQuery::DB::IQuery::OnFinalRelease();}
};

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
CQuery<TACCESSOR, TROWSET, TMULTIPLE>::CQuery()
{
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
CQuery<TACCESSOR, TROWSET, TMULTIPLE>::~CQuery()
{
	// 1) �ݴ´�.
	CloseQuery();
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
template<class TCHAR_QUERY>
intptr_t CQuery<TACCESSOR, TROWSET, TMULTIPLE>::PrepareQuery(_In_z_ const TCHAR_QUERY* _strCommand, _In_ REFGUID _guidCommand)
{
	// Declare)
	intptr_t	hResult;
	int			iRetry	 = CGQUERY_RETRY_MAX;

	// 1) Create Command
	do
	{
		hResult	 = CCommand<TACCESSOR, TROWSET, TMULTIPLE>::Create(*m_pSession, _strCommand, _guidCommand);
	}while(QueryResult(this, m_pSession, hResult, _strCommand) && (--iRetry));

	// Check) 
	ERROR_RETURN_IF(hResult!=S_OK, hResult, TraceErrorRecords(this, m_pSession, hResult, _strCommand));

	// 2) Prepare
	do
	{
		hResult = Prepare();
	} while (QueryResult(this, m_pSession, hResult, _strCommand) && (--iRetry));

	// Check) Prepare�� ���������� ������.
	ERROR_RETURN_IF(hResult != S_OK, hResult, TraceErrorRecords(this, m_pSession, hResult, _strCommand));

	// 3) Parameter�� Bind�Ѵ�.
	__if_exists(TACCESSOR::BindParameters)
	{
		// Declare) 
		void*	pDummy;

		// - Parameter�� Bind�Ѵ�.
		hResult	 = TACCESSOR::BindParameters(&m_hParameterAccessor, m_spCommand, &pDummy, true, true);

		// Check) 
		ERROR_RETURN_IF(hResult!=S_OK, hResult, TraceErrorRecords(this, m_pSession, hResult, _strCommand));
	}

	// Return) 
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
intptr_t CQuery<TACCESSOR, TROWSET, TMULTIPLE>::ProcessRequestQuery()
{
	// 1) Property Set
	CDBPropSet propset(DBPROPSET_ROWSET);

	// 2) PropSet
	__if_exists(GetRowsetProperties)
	{
		__if_exists(HasBookmark)
		{
			if( HasBookmark() )
				propset.AddProperty(DBPROP_IRowsetLocate, true);
		}
		__if_not_exists(CDynamicAccessor)
		{
			GetRowsetProperties(&propset);
		}
	}
	__if_not_exists(GetRowsetProperties)
	{
		__if_exists(HasBookmark)
		{
			if( HasBookmark() )
			{
				propset.AddProperty(DBPROP_IRowsetLocate, true);
			}
		}
	}

	// 3) On Open Query�� �����Ѵ�.
	OnBeginQuery();

	// 4) Session Open�ϱ�...
	intptr_t	hResult	 = OpenQuery<_CHAR>(_GetCommandString(), &propset);

	// 5) OnCloseQuery�Լ��� ȣ���Ѵ�.
	OnEndQuery(hResult);

	// Return)
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
template<class TCHAR_QUERY>
intptr_t CQuery<TACCESSOR, TROWSET, TMULTIPLE>::OpenQuery(_In_opt_ const TCHAR_QUERY* _strCommand, _In_opt_ CDBPropSet* _pPropSet, _In_opt_ DBROWCOUNT* _pRowsAffected, _In_ REFGUID _guidCommand, _In_ bool _bBind, _In_ ULONG _ulPropSets)
{
	// Check) m_pSession�� nullptr�̸� �ȉ´�.
	CGASSERT_ERROR(m_pSession.exist());

	// Check) m_pSession�� nullptr�̸� �ȉ´�.
	RETURN_IF(m_pSession.empty(), E_FAIL);

	// ���) 
	m_pSession->m_pQuerier->Statistics_OnQueryTry();

	// Declare) 
	int			iRetry	 = CGQUERY_RETRY_MAX;
	intptr_t	hResult  =0;

	do
	{
		// 1) Session�� Open�Ѵ�.
		hResult	 = Open(*m_pSession, _strCommand, _pPropSet, _pRowsAffected, _guidCommand, _bBind, _ulPropSets);

	// Check) 
	}while(QueryResult(this, m_pSession, hResult, _strCommand) && (--iRetry));

	// Return) ����� �����Ѵ�.
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
intptr_t CQuery<TACCESSOR, TROWSET, TMULTIPLE>::OpenQuery(_In_ int _iCommand, _In_opt_ CDBPropSet* _pPropSet, _In_opt_ DBROWCOUNT* _pRowsAffected, _In_ REFGUID _guidCommand, _In_ bool _bBind, _In_ ULONG _ulPropSets)
{
	// Check) m_pSession�� nullptr�̸� �ȉ´�.
	CGASSERT_ERROR(m_pSession.exist());

	// Check) m_pSession�� nullptr�̸� �ȉ´�.
	RETURN_IF(m_pSession.empty(), E_FAIL);

	// ���) 
	m_pSession->m_pQuerier->Statistics_OnQueryTry();

	do
	{
		// 1) Session�� Open�Ѵ�.
		hResult	 = Open(*m_pSession, _iCommand, _pPropSet, _pRowsAffected, _guidCommand, _bBind, _ulPropSets);

	// Check) �������� ���� �������� ��� ���� ���ó���� �Ѵ�.
	}while(QueryResult(this, m_pSession, hResult) && (--iRetry));

	// Return) ����� �����Ѵ�.
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
intptr_t CQuery<TACCESSOR, TROWSET, TMULTIPLE>::OpenQuery(_In_opt_ DBPROPSET *_pPropSet, _In_opt_ DBROWCOUNT* _pRowsAffected, _In_ bool _bBind, _In_ ULONG _ulPropSets)
{
	// Check) m_pSession�� nullptr�̸� �ȉ´�.
	CGASSERT_ERROR(m_pSession.exist());

	// Check) m_pSession�� nullptr�̸� �ȉ´�.
	RETURN_IF(m_pSession.empty(), E_FAIL);

	// ���) 
	m_pSession->m_pQuerier->Statistics_OnQueryTry();

	// Declare) 
	intptr_t	hResult;
	int			iRetry	 = CGQUERY_RETRY_MAX;

	do
	{
		// 1) Session�� Open�Ѵ�.
		hResult	 = Open(_pPropSet, _pRowsAffected, _bBind, _ulPropSets);

	// Check) �������� ���� �������� ��� ���� ���ó���� �Ѵ�.
	}while(QueryResult(this, m_pSession, hResult) && (--iRetry));

	// Return) ����� �����Ѵ�.
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
void CQuery<TACCESSOR, TROWSET, TMULTIPLE>::CloseQuery()
{
	// 1) Command�� �ݴ´�.
	ReleaseCommand();

	// 2) �ݴ´�.
	Close();

	// 3) Result�� �ݰ�...
	if (GetMultiplePtr() != NULL)
	{
		GetMultiplePtr()->Release();
		*GetMultiplePtrAddress() = NULL;
	}

	// 4) DynamicAccessor�� ��� Parameter �޸𸮸� �����Ѵ�.
	__if_exists(TACCESSOR::CDynamicParameterAccessor)
	{
		// - ParameterEntry�� ���۸� �Ҵ�����
		SAFE_DELETE_ARRAY(m_pParameterEntry);

		// - ParameterName�� Buffer�� �Ҵ�����
		if (m_ppParamName != NULL)
		{
			CoTaskMemFree(*m_ppParamName);
			SAFE_DELETE(m_ppParamName);
		}

		// - m_pParameterBuffer ���۸� �Ҵ�����
		SAFE_DELETE(m_pParameterBuffer)

		m_nParameterBufferSize	 = 0;
		m_nParams				 = 0;
	};

	// 5) String�� Clear�Ѵ�.
	__if_not_exists(GetDefaultCommand)
	{
		m_stringQuery.clear();
	}
}


}
}

typedef	std::function<intptr_t(HRESULT, QUERY_DYNAMIC*)>	TLAMBDA_QUERY;
