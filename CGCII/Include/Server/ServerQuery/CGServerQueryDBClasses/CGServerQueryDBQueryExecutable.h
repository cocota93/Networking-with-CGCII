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
// CGServerQuery::DB::CQueryExecutable
//
// 1. CGServerQuery::DB::CQueryExecutable��!
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

template<class TACCESSOR=CDynamicAccessor, template <typename T> class TROWSET=CRowset, class TMULTIPLE=CMultipleResults>
class CQueryExecutable : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CQuery<TACCESSOR, TROWSET, TMULTIPLE>,	// 
	virtual public				CGServerQuery::DB::IQueryExecutable		// QuerierBase
{
// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Query�� ó���� ������ �Լ�.
	virtual	intptr_t			ProcessQueryResult(_In_ intptr_t _Return) PURE;

	// 2) Query�� ó���� ������ �Լ�.
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
intptr_t CQueryExecutable<TACCESSOR, TROWSET, TMULTIPLE>::ProcessExecute(_In_ intptr_t /*_Return*/, _In_ size_t /*_Param*/)
{
	// Declare)
	intptr_t	hResult;

	// 2) Request Query
	hResult	 = ProcessRequestQuery();

	// Check) Query�� ���������� ���⼭ �׳� ������.
	RETURN_IF(FAILED(hResult), S_FALSE);

	try
	{
		// 3) Query Result�� ó���Ѵ�.
		hResult	 = ProcessQueryResult(hResult);
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