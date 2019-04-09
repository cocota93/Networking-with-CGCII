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
// CGServerQuery::DB::CQuerier
//
// 1. CGServerQuery::DB::CQuerier��!
//    1) Ole-DB�� ����Ͽ� Query�� �����ϴ� Querier�̴�.
//
// 2. CGServerQuery::DB::CQuerier�� �ٽ�! Function�� ��� ����
//    1) OpenDB		ó�� ����� �� DB�� ���� �Լ��� ó���� �ݵ�� ȣ���Ͽ��� �ϴ�
//	                �Լ�.
//					���⼭ DB���ῡ �ʿ��� �α����� �����ϰ� Session�� �����
//	  2) CloseDB	�α��� �� DB�� �α׾ƿ��ϴ� ���� �ǹ��Ѵ�.
//    3) Query
//		 - PostRequestQuery	�񵿱������� Query�� �����ϴ� �Լ���.
//		 - RequestQuery		���������� Query�� �����ϴ� �Լ��� Query�� �Ϸ�� ��
//							���� �Լ��� �Ϸ���� �ʴ´�.
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
// 3. ���� ����
//    1) RequestQuery�� ����� PostQuery�� ��뿡 �����ؾ� �Ѵ�.
//       RequestQuery�� Session�� ��� ���� ����� ������ �߻��� �� �ֱ� �����̴�.
//       RequestQueyry�� ����Ѵٸ� ���� Session�� �����ϰ� �ٸ� Query��
//       �����ϱ⸦ �����Ѵ�.
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
	// 1) OLE-DB�� DB Session(Connection)
			LOCKABLE<>			m_csQuery;
			circular_list<CGPTR<Session>>	m_stackSession;
			circular_list<QUEUED_QUERY>		m_queueQuery;

			ATOMIC<int>			m_nSessionCreated;

	// 2) Query���� �Լ�.
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
	// Check) Start�� ���°� �ƴ϶�� �ȉ´�.
	RETURN_IF(GetObjectState()!=eOBJECT_STATE::RUNNING, false);

	// Declare) 
	class CTempQuery : public TQUERY, virtual public DB::IQueryExecutable, public NCGPoolable<CTempQuery>
	{
	public:
		std::function<intptr_t(TQUERY*)>		m_fLambda;
		void Set(const std::function<intptr_t(TQUERY*)>& a)	{	m_fLambda=a;}
		virtual	intptr_t ProcessExecute(_In_ intptr_t, _In_ size_t) override { return m_fLambda(this);}
	};

	// 1) �����Ѵ�.
	auto	pquery	 = NEW<CTempQuery>();

	// 2) Lambda�Լ��� �����Ѵ�.
	pquery->m_fLambda	 = _rfLambda;

	// 3) Query�� ��û�Ѵ�.
	return	PostRequestQuery(pquery);
}

template <class TQUERY, class TCHAR_QUERY>
CGPTR<TQUERY> CQuerier::RequestQuery(const TCHAR_QUERY* _strCommand)
{
	// Check) Start�� ���°� �ƴ϶�� �ȉ´�.
	RETURN_IF(GetObjectState()!=eOBJECT_STATE::RUNNING, CGPTR<TQUERY>());

	// 1) Query�� �Ҵ�޴´�.
	auto	pQuery	 = AllocQuery<TQUERY>();

	// Check)
	ERROR_RETURN_IF(pQuery.empty(), CGPTR<TQUERY>(), )

	// Check)
	CGASSERT_ERROR(pQuery->m_pSession.exist());

	// 2) Query�� ��û�Ѵ�.
	auto	intptr_t = pQuery->OpenQuery(_strCommand);

	// Check) Query�� ���������� ����!
	ERROR_RETURN_IF(intptr_t !=S_OK, CGPTR<TQUERY>(), );

	// Return) 
	return	pQuery;
}

template <class TQUERY, class TCHAR_QUERY>
bool CQuerier::PostRequestQuery(const TCHAR_QUERY* _strCommand, const std::function<intptr_t(intptr_t, TQUERY*)>& _rLambda)
{
	// Check) Start�� ���°� �ƴ϶�� �ȉ´�.
	RETURN_IF(GetObjectState()!=eOBJECT_STATE::RUNNING, false);

	// 1) Query ��ü�� �����Ѵ�.
	auto	pQuery	 = NEW<CQueryExecutableLambda<TQUERY>>();

	// 2) Query�� �����Ѵ�.
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