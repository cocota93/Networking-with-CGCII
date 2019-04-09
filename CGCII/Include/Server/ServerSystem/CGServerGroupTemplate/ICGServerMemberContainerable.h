//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Group Template Classes                           *
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
/**

 @class		ICGServerMemberContainerable
 @brief		�׷��� ����� �Ǳ� ���� �������̽� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE>
class ICGServerMemberContainerable : virtual public ICGReferenceable
{
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief Ư�� ����� ã�´�. @param _fCondition ã�� ���� �Լ� @return ã�� ��� ������
	virtual	CGPTR<_TMEMBERBASE>	FindMember(const std::function<bool(_TMEMBERBASE*)>& _fCondition) PURE;

	//! @brief ��� ����� Ư�� �Լ��� �����Ѵ�. @param _fExecute �����ϴ� �Լ� @return true ���� @return false ����
	virtual	bool				ForEachMember(const std::function<bool(_TMEMBERBASE*)>& _fExecute) PURE;

};
