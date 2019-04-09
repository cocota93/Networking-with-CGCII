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
// ScopedTransaction
//
// 1. CGServerQuery::DB::CQuery��!
//    1) ICGServerQuery�� Command�� ��ӹ޾� ���� �⺻ Query��.
//    2) Querier�� Query�� Post�ϰų� Request�ϰ� �Ǹ� Session�� �Ҵ�ް� �ȴ�.
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

class CScopedTransaction
{
public:
			CScopedTransaction(Session* _pSession) : m_pSession(_pSession)			{	if(_pSession!=nullptr) _pSession->StartTransaction(); }
			CScopedTransaction(IQuery* _pQuery) : m_pSession(_pQuery->GetSession())	{	if(m_pSession!=nullptr) m_pSession->StartTransaction(); }
			~CScopedTransaction()						{	Abort();}

			void			Commit()					{ if(m_pSession.empty()) return; m_pSession->Commit(); m_pSession.reset();}
			void			Abort()						{ if(m_pSession.empty()) return; m_pSession->Abort(); m_pSession.reset();}

protected:
			CGPTR<Session>	m_pSession;
};


}
}

#define BEGIN_TRANSACTION(query)	{ CGServerQuery::DB::CScopedTransaction tempTransaction(query);
#define COMMIT_TRANSACTION			tempTransaction.Commit();
#define ROLLBACK_TRANSACTION		tempTransaction.Abort();
#define END_TRANSACTION				}
#define END_TRANSACTION_WITH_COMMIT	COMMIT_TRANSACTION}
