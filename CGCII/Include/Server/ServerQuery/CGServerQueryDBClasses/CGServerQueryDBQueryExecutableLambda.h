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
// CGServerQuery::DB::CQueryExecutableLambda
//
// 1. CGServerQuery::DB::CQueryExecutableLambda란!
//    1) RowSet & NoRowSet &CMultiRowSet을 사용하여 Querier를 제작하도록 설계
//       되었다.
//    2) ProcessGetQueryString()을 재정의하여 Query String을 정의한다.
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

template<class TQUERY=CQuery<CDynamicAccessor, CRowset, CMultipleResults>>
class CQueryExecutableLambda : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						TQUERY,									// Query
	virtual public				CGServerQuery::DB::IQueryExecutable		// QuerierBase
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CQueryExecutableLambda()									{}
	virtual ~CQueryExecutableLambda()									{}


// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:
	typedef	std::function<intptr_t(intptr_t, TQUERY*)>	TQUERYLAMBDA;


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) 실행할 함수를 정의하는 함수.
			void				SetLambda(_In_ const TQUERYLAMBDA& p)	{	m_lambdaQuery=p;}
			TQUERYLAMBDA		GetLambda() const						{	return m_lambdaQuery;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Lambda function
			TQUERYLAMBDA		m_lambdaQuery;

	// 2) Query의 처리를 정의한 함수.
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};

template<class TQUERY>
intptr_t CQueryExecutableLambda<TQUERY>::ProcessExecute(_In_ intptr_t /*_Return*/, _In_ size_t /*_Param*/)
{
	// Declare)
	intptr_t	hResult;

	// 1) Query를 수행한다.
	hResult	 = ProcessRequestQuery();

	try
	{
		// 2) Request Query
		hResult	 = m_lambdaQuery(hResult, this);

		// Check) Query에 실패했으면 여기서 그냥 끝낸다.
		RETURN_IF(FAILED(hResult), S_FALSE);
	}
	catch(...)
	{
		// - Close Query
		CloseQuery();

		// Reraise)
		throw;
	}

	// 4) Query를 닫는다.
	CloseQuery();

	// Return)
	return	hResult;
}


}
}