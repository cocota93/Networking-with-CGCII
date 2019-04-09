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
// CGServerQuery::DB::DataSource
//
// 1. CGServerQuery::DB::DataSource란!
//    1) Session과 CDataSource를 묶어 놓은 CDataSource을 상속받은 Class이다.
//    2) CDataSource에 IReferenceCount만 추가한 것이다.
//
//
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DB
{

class DataSource : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						ATL::CDataSource,
	virtual public				ICGReferenceable
{
};

}
}