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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//----------------------------------------------------------------------------
//
//
//  Query DB Classes
//
//
//----------------------------------------------------------------------------
//#define	CGDYNAMIC_PARAMETER_ACCESSOR					CDynamicParameterAccessorEx
#define	CGDYNAMIC_PARAMETER_ACCESSOR					CDynamicParameterAccessor

#define	QUERY(accessor)									CGServerQuery::DB::CQuery<accessor>
#define	QUERY_EXECUTABLE(accessor)						CGServerQuery::DB::CQueryExecutable<accessor>
#define	QUERY_EXECUTABLE_LAMBDA(accessor)				CGServerQuery::DB::CQueryExecutableLambda<accessor>
#define	QUERY_DYNAMIC									CGServerQuery::DB::CQuery<>
#define QUERY_DYNAMIC_PARAM								CGServerQuery::DB::CQuery<CGDYNAMIC_PARAMETER_ACCESSOR>
#define	QUERY_EXECUTABLE_DYNAMIC						CGServerQuery::DB::CQueryExecutable<>
#define QUERY_EXECUTABLE_DYNAMIC_PARAM					CGServerQuery::DB::CQueryExecutable<CGDYNAMIC_PARAMETER_ACCESSOR>
#define	QUERY_EXECUTABLE_LAMBDA_DYNAMIC					CGServerQuery::DB::CQueryExecutableLambda<>
#define QUERY_EXECUTABLE_LAMBDA_DYNAMIC_PARAM			CGServerQuery::DB::CQueryExecutableLambda<CGDYNAMIC_PARAMETER_ACCESSOR>

struct CGSERVERQUERY_ERROR_INFO
{
	CGPTR<ICGServerQuerier>	pQuerier;
	CGPTR<ICGServerQuery>	pQuery;

	intptr_t				hResult;
	LCID					lcLocale;
	CDBErrorInfo			ErrorInfo;
	const _CHAR*			strQuery;
	ULONG					cRecords;
};
