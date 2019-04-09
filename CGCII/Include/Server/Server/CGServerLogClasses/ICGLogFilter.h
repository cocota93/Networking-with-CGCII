//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                            Server Log Classes                             *
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
//-----------------------------------------------------------------------------
/**

@class		ICGLogFilter
@brief		전달달 Log 중 조건에 맞는 Log만 골라내는 Filter 객체 Interface
@todo
@ref
@details	\n

*/
//-----------------------------------------------------------------------------
class ICGLogFilter : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGLogFilter()		{}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	virtual bool				ProcessFiltering(_In_ const CGLOG_RECORD* _pLogRecord) PURE;

};

