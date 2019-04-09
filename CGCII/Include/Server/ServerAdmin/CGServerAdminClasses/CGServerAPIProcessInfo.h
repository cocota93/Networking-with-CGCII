//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// CGNetAPI::CProcessInfo
//
// 1. CGNetAPI::CProcessInfo란!
//    1) Process등 각종 System 정보를 알아보기 위한 class임
//
//
//-----------------------------------------------------------------------------
#include "Pdh.h"

namespace CGNetAPI
{

class CProcessInfo
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CProcessInfo();
	virtual	~CProcessInfo();

// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			BOOL				InitProcessInfo(_In_z_ const _CHAR* p_strProcess);
			BOOL				InitProcessInfo(_In_z_ const _CHAR_SUB* p_strProcess);
			void				CloseProcessInfo();

	static	PDH_STATUS			GetCounter(_In_reads_z_(p_MaxLength) const _CHAR* szPathBuffer, _In_ int p_MaxLength);
	static	PDH_STATUS			GetCounter(_In_reads_z_(p_MaxLength) const _CHAR_SUB* szPathBuffer, _In_ int p_MaxLength);

			void				UpdateCounter();

public:
			int					m_lProcessTime;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			HQUERY				m_hQuery;

			HCOUNTER			m_hCounter_ProcessTime;
};

}


//----------------------------------------------------------------------------
// Libraries Link
//
// * Library용이 아닌 경우에만 LIB file들을 Link한다.
//
//----------------------------------------------------------------------------
#if !defined(_LIB) || defined(_CONSOLE)

#pragma comment (lib, "Pdh.Lib")

#endif