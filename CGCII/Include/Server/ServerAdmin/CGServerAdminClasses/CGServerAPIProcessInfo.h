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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNetAPI::CProcessInfo
//
// 1. CGNetAPI::CProcessInfo��!
//    1) Process�� ���� System ������ �˾ƺ��� ���� class��
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
// * Library���� �ƴ� ��쿡�� LIB file���� Link�Ѵ�.
//
//----------------------------------------------------------------------------
#if !defined(_LIB) || defined(_CONSOLE)

#pragma comment (lib, "Pdh.Lib")

#endif