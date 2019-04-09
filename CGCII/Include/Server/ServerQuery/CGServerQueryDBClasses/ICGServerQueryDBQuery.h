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
	//    - Session�� OLE-DB�� �ݵ�� �ʿ��ϴ�. ���� �̰��� ������ ��¯ ���ι��̴پ�...
	//    - Query�� �ʿ��� �ٽ����� DB�� ������ �Ǿ� �ִ� ���� �ǹ��Ѵ�.
	CGPTR<CGServerQuery::DB::Session>	m_pSession;

	// 2) OnFree..
	virtual	void				OnFinalRelease() override					{	ResetSession(); m_pRequestor.reset();}

	// 3) ������ ó���� ���� �Լ�.
			void				_ProcessNotifyToRequestor();
			void				_ProcessRegenerationSession();
};


}
}
