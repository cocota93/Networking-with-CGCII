//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / Release 2017.01.03                        *
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
//-----------------------------------------------------------------------------
//
// CGServerQuery::DB::CQuery
//
//-----------------------------------------------------------------------------
class CDynamicParameterAccessorEx : public CDynamicParameterAccessor
{
public:
	HRESULT BindParameters(HACCESSOR* pHAccessor, ICommand* pCommand, void** ppParameterBuffer, bool fBindLength = false, bool fBindStatus = false) throw()
	{
		if (NULL == m_pParameterBuffer)
		{
			return CDynamicParameterAccessor::BindParameters
			(pHAccessor, pCommand, ppParameterBuffer, fBindLength, fBindStatus);
		}
		else
		{
			*ppParameterBuffer = m_pParameterBuffer;
			return S_OK;
		}
	}
};