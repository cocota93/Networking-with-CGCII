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
// CGServerQuery::DB::CQuerier
//
// 1. CGServerQuery::DB::CQuerier란!
//    1) Ole-DB를 사용하여 Query를 수행하는 Querier이다.
//
// 2. CGServerQuery::DB::CQuerier의 핵심! Function의 기능 설명
//    1) OpenDB		처음 사용할 때 DB를 여는 함수로 처음에 반드시 호출하여야 하는
//	                함수.
//					여기서 DB연결에 필요한 로그인을 수행하고 Session을 만든다
//	  2) CloseDB	로그인 된 DB를 로그아웃하는 것을 의미한다.
//    3) Query
//		 - PostRequestQuery	비동기적으로 Query를 수행하는 함수다.
//		 - RequestQuery		동기적으로 Query를 수행하는 함수로 Query가 완료될 때
//							까지 함수가 완료되지 않는다.
//
// 3. Parameters
//    1) "SessionPerSource"
//	  2) "DataSourceCount"
//    3) "init"
//    4) "provider"
//       "data_source"
//       "user_id"
//       "password"
//       "initial_catalog"
//
//    [CASE MSSQL]
//		"provider"			 = "SQLOLEDB.1"
//		"data_source"		 = "TEST_SERVER"
//		"user_id"			 = "sa"
//		"password"			 = "12341234"
//		"initial_catalog"	 = "Test"
//
//    [CASE MySQL]
//		"provider"			 = "MSDASQL.1"
//		"data_source"		 = "TEST_SERVER"
//		"user_id"			 = "sa"
//		"password"			 = "12341234"
//		"initial_catalog"	 = "Test"
//
// 3. 주의 사항
//    1) RequestQuery를 사용중 PostQuery의 사용에 중의해야 한다.
//       RequestQuery가 Session을 모두 물고 데드락 현상이 발생할 수 있기 때문이다.
//       RequestQueyry를 사용한다면 기존 Session을 해제하고 다른 Query를
//       수행하기를 권장한다.
//
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DB
{

class CQuerier :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGServerQuerier,
	public						CGNameable::NString,
	public						NCGObjectState,
	public						NCGStartable,
	public						NCGInitializable,
	public						NCGDispatchable,
	virtual public				ICGMessageable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CQuerier(const char* _strName);
			CQuerier(const wchar_t* _wstrName=nullptr);
	virtual ~CQuerier();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Start
			bool				Start(CGMSG_CONTEXT& _Msg)				{	return NCGStartable::Start(_Msg);}
			bool				Start(CGExecutor::CCompletionPort* p_pExecutor, const char* _strInitialization, int _nSessionPerSource=32, int p_nDataSource=1);
			bool				Start(CGExecutor::CCompletionPort* p_pExecutor, const wchar_t* p_wstrInitialization, int _nSessionPerSource=32, int p_nDataSource=1);
			bool				Start(_In_opt_z_ const char* _strInitialization, int _nSessionPerSource=32, int p_nDataSource=1);
			bool				Start(_In_opt_z_ const wchar_t* _strInitialization, int _nSessionPerSource=32, int p_nDataSource=1);
			bool				Start(_In_z_ const char* _strProgID, _In_z_ const char* _strDataSource, _In_z_ const char* _strUserName, _In_z_ const char* _strPasswordd,  _In_z_ const char* _strInitialCatalog=nullptr, int _nSessionPerSource=32, int p_nDataSource=1);
			bool				Start(_In_z_ const wchar_t* _strProgID, _In_z_ const wchar_t* _strDataSource, _In_z_ const wchar_t* _strUserName, _In_z_ const wchar_t* _strPassword,  _In_z_ const wchar_t* _strInitialCatalog=nullptr,int _nSessionPerSource=32, int p_nDataSource=1);
			bool				StartFromFileName(_In_z_ const char* _strFileName, int _nSessionPerSource=32, int p_nDataSource=1);
			bool				StartFromFileName(_In_z_ const wchar_t* _strFileName, int _nSessionPerSource=32, int p_nDataSource=1);
			          
			CGPTR<ICGExecutor>	GetExecutor() const						{ return m_pExecutor; }


	// 2) RequestQuery/PostRequestQuery/Cancel
	virtual	bool				RequestQuery(DB::IQuery* _pQuery);
			template <class TCHAR_QUERY>
			CGPTR<DB::CQuery<>>	RequestQuery(const TCHAR_QUERY* _strCommand) { return RequestQuery<DB::CQuery<>, TCHAR_QUERY>(_strCommand);}
			template <class TQUERY, class TCHAR_QUERY>
			CGPTR<TQUERY>		RequestQuery(const TCHAR_QUERY* _strCommand);
	virtual	bool				PostRequestQuery(DB::IQueryExecutable* _pQuery);
			template <class TCHAR_QUERY>
			bool				PostRequestQuery(const TCHAR_QUERY* _strCommand, const std::function<intptr_t(intptr_t, CQueryExecutableLambda<>*)>& _rLambda)	{ return PostRequestQuery<CQueryExecutableLambda<>, TCHAR_QUERY>(_strCommand, _rLambda);}
			template <class TQUERY, class TCHAR_QUERY>
			bool				PostRequestQuery(const TCHAR_QUERY* _strCommand, const std::function<intptr_t(intptr_t, TQUERY*)>& _rLambda);
	virtual	bool				CancelQuery(ICGServerQuery* _pQuery);
			void				CancelAllQueries();

	// 3) AllocQuery/PostAllocQuery
			template <class TQUERY>
			CGPTR<TQUERY>		AllocQuery()							{ auto pQuery=NEW<TQUERY>(); bool b=AllocSession(pQuery); if(b==false) return CGPTR<TQUERY>(); return pQuery;}
			CGPTR<DB::CQuery<>> AllocQuery()							{ return AllocQuery<DB::CQuery<>>();}
			template <class TQUERY>
			bool				PostAllocQuery(const std::function<intptr_t(TQUERY*)>& _rfLambda);
			bool				PostAllocQuery(const std::function<intptr_t(DB::CQuery<>*)>& _rfLambda)	{ return PostAllocQuery<DB::CQuery<>>(_rfLambda);}

	
	// 4) AllocSession/FreeSession
			bool				AllocSession(DB::IQuery* _pQuery);
	virtual	void				FreeSession(DB::Session* p_pSession);

	// 7) NotifyMessage
	virtual	int					NotifyMessage(CGMSG& _Msg) override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Status
	virtual	void				ProcessStart(CGMSG_CONTEXT& _Msg) override;
	virtual	void				ProcessStop() override;
	virtual void				_ProcessDestroy() override;


	// 2) ...
	virtual	bool				ProcessRequestQuery(ICGServerQuery* _pQuery);
	virtual	bool				ProcessPostRequestQuery(ICGServerQueryExecutable* _pQuery);
			circular_list<CGPTR<Session>> ProcessCreateSession(const _CHAR* _strInitialization, int _nSessionPerSource=32, int _nDataSource=1);
			circular_list<CGPTR<Session>> ProcessCreateSessionFromFileName(const _CHAR* _strFileName, int _nSessionPerSource=32, int _nDataSource=1);
			circular_list<CGPTR<Session>> ProcessCreateSessionWithNameUserPassword(_In_z_ const _CHAR* _strProgID, _In_z_ const _CHAR* _strDataSource, _In_z_ const _CHAR* _strUserName, _In_z_ const _CHAR* _strPassword,  _In_z_ const _CHAR* _strInitialCatalog=nullptr, int _nSessionPerSource=32, int p_nDataSource=1);

	virtual	int					ProcessMessage(CGMSG& _Msg) override;

protected:
			struct QUEUED_QUERY
			{
				QUEUED_QUERY(ICGReferenceable* ) : pQuery()	{}

				void (CQuerier::*fExecute)(DB::IQuery*);
				CGPTR<DB::IQuery>	pQuery;
				bool			operator!=(ICGServerQuery* _pQuery) const	{ return pQuery!=_pQuery;}
				bool			operator==(ICGServerQuery* _pQuery) const	{ return pQuery==_pQuery;}
			};

protected:
	// 1) OLE-DB용 DB Session(Connection)
			LOCKABLE<>			m_csQuery;
			circular_list<CGPTR<Session>>	m_stackSession;
			circular_list<QUEUED_QUERY>		m_queueQuery;

			ATOMIC<int>			m_nSessionCreated;

	// 2) Query수행 함수.
			void				Query_Request(DB::IQuery* _pQuery);
			void				Query_Post(DB::IQuery* _pQuery);

	// 3) Executor
			CGPTR<ICGExecutor>	m_pExecutor;
			bool				m_bCreated;

	// Declare) 
			class CExecutableQuery;
			friend class CExecutableQuery;
};

template <class TQUERY>
bool CQuerier::PostAllocQuery(const std::function<intptr_t(TQUERY*)>& _rfLambda)
{
	// Check) Start된 상태가 아니라면 안됀다.
	RETURN_IF(GetObjectState()!=eOBJECT_STATE::RUNNING, false);

	// Declare) 
	class CTempQuery : public TQUERY, virtual public DB::IQueryExecutable, public NCGPoolable<CTempQuery>
	{
	public:
		std::function<intptr_t(TQUERY*)>		m_fLambda;
		void Set(const std::function<intptr_t(TQUERY*)>& a)	{	m_fLambda=a;}
		virtual	intptr_t ProcessExecute(_In_ intptr_t, _In_ size_t) override { return m_fLambda(this);}
	};

	// 1) 생성한다.
	auto	pquery	 = NEW<CTempQuery>();

	// 2) Lambda함수를 설정한다.
	pquery->m_fLambda	 = _rfLambda;

	// 3) Query를 요청한다.
	return	PostRequestQuery(pquery);
}

template <class TQUERY, class TCHAR_QUERY>
CGPTR<TQUERY> CQuerier::RequestQuery(const TCHAR_QUERY* _strCommand)
{
	// Check) Start된 상태가 아니라면 안됀다.
	RETURN_IF(GetObjectState()!=eOBJECT_STATE::RUNNING, CGPTR<TQUERY>());

	// 1) Query를 할당받는다.
	auto	pQuery	 = AllocQuery<TQUERY>();

	// Check)
	ERROR_RETURN_IF(pQuery.empty(), CGPTR<TQUERY>(), )

	// Check)
	CGASSERT_ERROR(pQuery->m_pSession.exist());

	// 2) Query를 요청한다.
	auto	intptr_t = pQuery->OpenQuery(_strCommand);

	// Check) Query에 실패했으면 끝냄!
	ERROR_RETURN_IF(intptr_t !=S_OK, CGPTR<TQUERY>(), );

	// Return) 
	return	pQuery;
}

template <class TQUERY, class TCHAR_QUERY>
bool CQuerier::PostRequestQuery(const TCHAR_QUERY* _strCommand, const std::function<intptr_t(intptr_t, TQUERY*)>& _rLambda)
{
	// Check) Start된 상태가 아니라면 안됀다.
	RETURN_IF(GetObjectState()!=eOBJECT_STATE::RUNNING, false);

	// 1) Query 객체를 생성한다.
	auto	pQuery	 = NEW<CQueryExecutableLambda<TQUERY>>();

	// 2) Query를 설정한다.
	pQuery->SetQueryString(_strCommand);
	pQuery->SetLambda(_rLambda);

	// Declare) 
	bool	bResult;

	// Return) 
	bResult	 = PostRequestQuery(pQuery);

	// Check) 
	RETURN_IF(bResult==false, bResult);

	// Return) 
	return	true;
}


}
}