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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGServerQuery::DB::CQuery
//
// 1. CGServerQuery::DB::CQuery란!
//    1) ICGServerQuery와 Command를 상속받아 만든 기본 Query다.
//    2) Querier에 Query를 Post하거나 Request하게 되면 Session을 할당받게 된다.
//    3) Session을 할당받게 되면 Query String을 넘겨 OpenQuery함수를 호출함으로써
//       Query를 수행할 수 있다.
//    4) 그리고 Query가 완료된 후 CloseQuery를 호출하여 Query를 종료할 수 있다.
//    5) Start와 Stop은 원하는 만큼 수행할 수 있으며 최종적으로 ProcessQuery()
//       함수가 종료되면 Session도 반납되게 된다.
//
// 2. Accessor의 선택
//    1) 사용할 수 있는 Accessor는 기본적으로 크게 두가지가 있다.
//					
//       - CAccessor<TACCESSOR> 기본 Accessor로 Query의 설정 및 결과값을 클래스
//         내부 변수에 받도록 미리 정의해 놓도록 한 것이다.
//       - CDynamicAccessor		Query의 내용 및 결과를 필요에 따라 얻어 쓸수 
//		                        있도록 한 것으로 간단한 Query에 유용하다.
//
// 3. Rowset의 선택
//    1) Query의 결과 1개가 하나의 Row이다. 이것을 처리하기 위한 것이 RowSet이다.
//       기본적으로 3가지의 RowSet을 사용할 수 있다.
//      
//       - CNoRowset		Rowset을 사용하지 않는다.
//		 - CRowset		Rowset을 사용한다.
//		 - CMultiRowset	여러 개의 Rowset을 가질 수 있도록 한다.
//
// 4. CMultipleResults의 선택
//	  1) 선택한 결과의 갯수를 선정하는 것이다. 자체적으로 처리되는 내용은 없고
//		 다만 선택을 위한 Class로 선택사항은 아래와 같다.
//
//		 - CNoMultipleResults	한꺼번에 여러 개의 결과물을 받지 않는다.
//		 - CMultipleResults		한꺼번에 여러 개의 결과물을 받는다.
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
	// 1) Query요청 절차를 정의하는 함수.
	virtual	intptr_t			ProcessRequestQuery();

public:
	// 4) Poolable에 대비해서...
	virtual	void				OnFinalRelease() override					{	CloseQuery(); CGServerQuery::DB::IQuery::OnFinalRelease();}
};

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
CQuery<TACCESSOR, TROWSET, TMULTIPLE>::CQuery()
{
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
CQuery<TACCESSOR, TROWSET, TMULTIPLE>::~CQuery()
{
	// 1) 닫는다.
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

	// Check) Prepare에 실패했으면 끝낸다.
	ERROR_RETURN_IF(hResult != S_OK, hResult, TraceErrorRecords(this, m_pSession, hResult, _strCommand));

	// 3) Parameter를 Bind한다.
	__if_exists(TACCESSOR::BindParameters)
	{
		// Declare) 
		void*	pDummy;

		// - Parameter를 Bind한다.
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

	// 3) On Open Query를 수행한다.
	OnBeginQuery();

	// 4) Session Open하기...
	intptr_t	hResult	 = OpenQuery<_CHAR>(_GetCommandString(), &propset);

	// 5) OnCloseQuery함수를 호출한다.
	OnEndQuery(hResult);

	// Return)
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
template<class TCHAR_QUERY>
intptr_t CQuery<TACCESSOR, TROWSET, TMULTIPLE>::OpenQuery(_In_opt_ const TCHAR_QUERY* _strCommand, _In_opt_ CDBPropSet* _pPropSet, _In_opt_ DBROWCOUNT* _pRowsAffected, _In_ REFGUID _guidCommand, _In_ bool _bBind, _In_ ULONG _ulPropSets)
{
	// Check) m_pSession이 nullptr이면 안됀다.
	CGASSERT_ERROR(m_pSession.exist());

	// Check) m_pSession이 nullptr이면 안됀다.
	RETURN_IF(m_pSession.empty(), E_FAIL);

	// 통계) 
	m_pSession->m_pQuerier->Statistics_OnQueryTry();

	// Declare) 
	int			iRetry	 = CGQUERY_RETRY_MAX;
	intptr_t	hResult  =0;

	do
	{
		// 1) Session을 Open한다.
		hResult	 = Open(*m_pSession, _strCommand, _pPropSet, _pRowsAffected, _guidCommand, _bBind, _ulPropSets);

	// Check) 
	}while(QueryResult(this, m_pSession, hResult, _strCommand) && (--iRetry));

	// Return) 결과를 리턴한다.
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
intptr_t CQuery<TACCESSOR, TROWSET, TMULTIPLE>::OpenQuery(_In_ int _iCommand, _In_opt_ CDBPropSet* _pPropSet, _In_opt_ DBROWCOUNT* _pRowsAffected, _In_ REFGUID _guidCommand, _In_ bool _bBind, _In_ ULONG _ulPropSets)
{
	// Check) m_pSession이 nullptr이면 안됀다.
	CGASSERT_ERROR(m_pSession.exist());

	// Check) m_pSession이 nullptr이면 안됀다.
	RETURN_IF(m_pSession.empty(), E_FAIL);

	// 통계) 
	m_pSession->m_pQuerier->Statistics_OnQueryTry();

	do
	{
		// 1) Session을 Open한다.
		hResult	 = Open(*m_pSession, _iCommand, _pPropSet, _pRowsAffected, _guidCommand, _bBind, _ulPropSets);

	// Check) 성공했을 경우와 실패했을 경우 각각 통계처리를 한다.
	}while(QueryResult(this, m_pSession, hResult) && (--iRetry));

	// Return) 결과를 리턴한다.
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
intptr_t CQuery<TACCESSOR, TROWSET, TMULTIPLE>::OpenQuery(_In_opt_ DBPROPSET *_pPropSet, _In_opt_ DBROWCOUNT* _pRowsAffected, _In_ bool _bBind, _In_ ULONG _ulPropSets)
{
	// Check) m_pSession이 nullptr이면 안됀다.
	CGASSERT_ERROR(m_pSession.exist());

	// Check) m_pSession이 nullptr이면 안됀다.
	RETURN_IF(m_pSession.empty(), E_FAIL);

	// 통계) 
	m_pSession->m_pQuerier->Statistics_OnQueryTry();

	// Declare) 
	intptr_t	hResult;
	int			iRetry	 = CGQUERY_RETRY_MAX;

	do
	{
		// 1) Session을 Open한다.
		hResult	 = Open(_pPropSet, _pRowsAffected, _bBind, _ulPropSets);

	// Check) 성공했을 경우와 실패했을 경우 각각 통계처리를 한다.
	}while(QueryResult(this, m_pSession, hResult) && (--iRetry));

	// Return) 결과를 리턴한다.
	return	hResult;
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
void CQuery<TACCESSOR, TROWSET, TMULTIPLE>::CloseQuery()
{
	// 1) Command를 닫는다.
	ReleaseCommand();

	// 2) 닫는다.
	Close();

	// 3) Result를 닫고...
	if (GetMultiplePtr() != NULL)
	{
		GetMultiplePtr()->Release();
		*GetMultiplePtrAddress() = NULL;
	}

	// 4) DynamicAccessor일 경우 Parameter 메모리를 제거한다.
	__if_exists(TACCESSOR::CDynamicParameterAccessor)
	{
		// - ParameterEntry용 버퍼를 할당해제
		SAFE_DELETE_ARRAY(m_pParameterEntry);

		// - ParameterName용 Buffer를 할당해제
		if (m_ppParamName != NULL)
		{
			CoTaskMemFree(*m_ppParamName);
			SAFE_DELETE(m_ppParamName);
		}

		// - m_pParameterBuffer 버퍼를 할당해제
		SAFE_DELETE(m_pParameterBuffer)

		m_nParameterBufferSize	 = 0;
		m_nParams				 = 0;
	};

	// 5) String을 Clear한다.
	__if_not_exists(GetDefaultCommand)
	{
		m_stringQuery.clear();
	}
}


}
}

typedef	std::function<intptr_t(HRESULT, QUERY_DYNAMIC*)>	TLAMBDA_QUERY;
