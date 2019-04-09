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
// CGServerQuery::DB::DataSource
//
// 1. CGServerQuery::DB::DataSource��!
//    1) Session�� CDataSource�� ���� ���� CDataSource�� ��ӹ��� Class�̴�.
//    2) CDataSource�� IReferenceCount�� �߰��� ���̴�.
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