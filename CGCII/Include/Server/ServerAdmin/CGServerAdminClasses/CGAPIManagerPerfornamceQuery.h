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

class ManagerPerfornamceQuery : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable,
	public						NCGSingleton<ManagerPerfornamceQuery>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ManagerPerfornamceQuery();
	virtual ~ManagerPerfornamceQuery();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			bool				UpdateQuery();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			bool				AddCounter(CPerformanceCounter* p_pCounter, _In_z_ const _CHAR* p_strQuery);
			bool				AddCounter(CPerformanceCounter* p_pCounter, _In_z_ const _CHAR_SUB* p_strQuery);
			bool				RemoveCounter(CPerformanceCounter* p_pCounter);

protected:
			HQUERY				m_hQuery;
			LOCKABLE<>			m_csCounter;

	friend	class CPerformanceCounter;
};


}