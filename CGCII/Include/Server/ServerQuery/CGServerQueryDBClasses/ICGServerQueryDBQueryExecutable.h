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
// CGServerQuery::DB::IQueryExecutable
//
// 1. CGServerQuery::DB::IQueryExecutable란!
//    1) 비동기적 Query를 위한 Interface 클래스이다.
// 
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DB
{

class IQueryExecutable : 
	virtual public				CGServerQuery::DB::IQuery,				// (I) QuerierBase
	virtual public				ICGServerQueryExecutable				// (I) Executable
{
public:
	typedef	CGServerQuery::DB::IQuery	IQUERY;

};


}
}