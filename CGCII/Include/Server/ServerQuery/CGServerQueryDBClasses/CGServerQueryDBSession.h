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
// CGServerQuery::DB::Session
//
// 1. CGServerQuery::DB::Session란!
//    1) Session은 하나의 Query를 처리하기 위해 필요한 객체이다.
//    2) 하나의 Session은 동시에 하나의 Query를 수행할 수 있다.
//    3) Query를 수행한 후 Session을 닫으면 다시 Query를 수행할 수 있다.
//    4) Session의 참조가 종료하면 m_pQuerier롤 되돌려 진다.
//    5) m_pQuerier는 Session을 생성한 곳이자 관리자이다.
//    6) m_pDataSource는 ATL::CDataSource를 가진 변수이다.
//
//
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DB
{

class Session : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						ATL::CSession,						//     Session
	virtual public				ICGReferenceable					//     IOCP Completer
{
public:
			CGPTR<DataSource>	m_pDataSource;
			CGPTR<CGServerQuery::DB::CQuerier>	m_pQuerier;
public:
			intptr_t			Reopen(_Inout_opt_cap_(p_ulPropSets) DBPROPSET* p_pPropSet=nullptr, _In_ ULONG p_ulPropSets=0);
public:
	virtual	void				ProcessDispose() override;

};


}
}