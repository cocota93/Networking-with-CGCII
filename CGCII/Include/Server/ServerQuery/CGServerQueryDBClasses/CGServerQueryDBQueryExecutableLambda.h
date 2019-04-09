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
// CGServerQuery::DB::CQueryExecutableLambda
//
// 1. CGServerQuery::DB::CQueryExecutableLambda��!
//    1) RowSet & NoRowSet &CMultiRowSet�� ����Ͽ� Querier�� �����ϵ��� ����
//       �Ǿ���.
//    2) ProcessGetQueryString()�� �������Ͽ� Query String�� �����Ѵ�.
//    3) Session�� �Ҵ�ް� �Ǹ� Query String�� �Ѱ� OpenQuery�Լ��� ȣ�������ν�
//       Query�� ������ �� �ִ�.
//    4) �׸��� Query�� �Ϸ�� �� CloseQuery�� ȣ���Ͽ� Query�� ������ �� �ִ�.
//    5) Open�� Close�� ���ϴ� ��ŭ ������ �� ������ ���������� ProcessQuery()
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
	// 1) ������ �Լ��� �����ϴ� �Լ�.
			void				SetLambda(_In_ const TQUERYLAMBDA& p)	{	m_lambdaQuery=p;}
			TQUERYLAMBDA		GetLambda() const						{	return m_lambdaQuery;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Lambda function
			TQUERYLAMBDA		m_lambdaQuery;

	// 2) Query�� ó���� ������ �Լ�.
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};

template<class TQUERY>
intptr_t CQueryExecutableLambda<TQUERY>::ProcessExecute(_In_ intptr_t /*_Return*/, _In_ size_t /*_Param*/)
{
	// Declare)
	intptr_t	hResult;

	// 1) Query�� �����Ѵ�.
	hResult	 = ProcessRequestQuery();

	try
	{
		// 2) Request Query
		hResult	 = m_lambdaQuery(hResult, this);

		// Check) Query�� ���������� ���⼭ �׳� ������.
		RETURN_IF(FAILED(hResult), S_FALSE);
	}
	catch(...)
	{
		// - Close Query
		CloseQuery();

		// Reraise)
		throw;
	}

	// 4) Query�� �ݴ´�.
	CloseQuery();

	// Return)
	return	hResult;
}


}
}