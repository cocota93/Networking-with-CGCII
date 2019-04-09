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
// CGAPI::ManagerPerfornamceQuery
//
// 1. CGAPI::ManagerPerfornamceQuery란!
//    1) Process등 각종 System 정보를 알아보기 위한 class임
//
//
//-----------------------------------------------------------------------------
namespace CGAPI
{

class CPerformanceCounter :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPerformanceCounter();
			CPerformanceCounter(_In_z_ const _CHAR* p_strQuery);
			CPerformanceCounter(_In_z_ const _CHAR_SUB* p_strQuery);
	virtual ~CPerformanceCounter();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Create/Destroy
			bool				Create(_In_z_ const _CHAR* p_strQuery);
			bool				Create(_In_z_ const _CHAR_SUB* p_strQuery);
			void				Destroy();

	// 2) GetValue
			long				GetValueLONG(_In_ uint32_t p_dwFlag=PDH_FMT_1000);
			double				GetValueDOUBLE();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			PDH_HCOUNTER		m_hCounter;
			CGPTR<ManagerPerfornamceQuery>	m_pManager;

	friend	class ManagerPerfornamceQuery;
};


}