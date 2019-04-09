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
//    5) Open과 Close는 원하는 만큼 수행할 수 있으며 최종적으로 ProcessQuery()
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

class IQuery : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGServerQuery							// (@) Querier
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			IQuery()			{}
	virtual ~IQuery()			{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Session
			CGPTR<CGServerQuery::DB::Session> GetSession() const		{	return m_pSession;}
			void				SetSession(CGServerQuery::DB::Session* p_pSession){	m_pSession=p_pSession;}
			void				ResetSession()							{	m_pSession.reset();}

	// 2) Transaction Start/Comit/Comit
			_Return_type_success_(return >= 0)
			intptr_t			BeginTransaction(
									_In_ ISOLEVEL _isoLevel = ISOLATIONLEVEL_READCOMMITTED,
									_In_ ULONG _isoFlags=0,
									_In_opt_ ITransactionOptions* _pOtherOptions=nullptr,
									_Out_opt_ ULONG* _pulTransactionLevel=nullptr) const throw();
												
			intptr_t			AbortTransaction(
									_In_opt_ BOID* _pboidReason=nullptr,
									_In_ BOOL _bRetaining=FALSE,
									_In_ BOOL _bAsync=FALSE) const throw();

			intptr_t			CommitTransaction(
									_In_ BOOL _bRetaining=FALSE,
									_In_ uint32_t _grfTC=XACTTC_SYNC,
									_In_ uint32_t _grfRM=0) const throw();

			_Return_type_success_(return >= 0)
			intptr_t			GetTransactionInfo(_Out_ XACTTRANSINFO* pInfo) const throw();


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	// 2)
	virtual	intptr_t			ProcessRequestQuery() PURE;


// ****************************************************************************
// Implementations) 
// ----------------------------------------------------------------------------
public:
	// 1) Session
	//    - Session은 OLE-DB에 반드시 필요하다. 따라서 이것이 없으면 말짱 도로묵이다앗...
	//    - Query에 필요한 핵심으로 DB와 접속이 되어 있는 것을 의미한다.
	CGPTR<CGServerQuery::DB::Session>	m_pSession;

	// 2) OnFree..
	virtual	void				OnFinalRelease() override					{	ResetSession(); m_pRequestor.reset();}

	// 3) 내부적 처리를 위한 함수.
			void				_ProcessNotifyToRequestor();
			void				_ProcessRegenerationSession();
};


}
}
