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
// CGServerQuery::DB::Session
//
// 1. CGServerQuery::DB::Session��!
//    1) Session�� �ϳ��� Query�� ó���ϱ� ���� �ʿ��� ��ü�̴�.
//    2) �ϳ��� Session�� ���ÿ� �ϳ��� Query�� ������ �� �ִ�.
//    3) Query�� ������ �� Session�� ������ �ٽ� Query�� ������ �� �ִ�.
//    4) Session�� ������ �����ϸ� m_pQuerier�� �ǵ��� ����.
//    5) m_pQuerier�� Session�� ������ ������ �������̴�.
//    6) m_pDataSource�� ATL::CDataSource�� ���� �����̴�.
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