//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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

namespace CGSchedulable
{
namespace Executable
{

//-----------------------------------------------------------------------------
/**

 @class		CFunctionMember
 @brief		Ư�� ��� �Լ��� �����ð����� Executor�� �ɾ��ִ� Schedulable Ŭ����
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TCLASS>
class CFunctionMember :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGSchedulable::NExecutable,
	public						CGExecutable::CFunctionMember<TCLASS>
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
			typedef		void (TCLASS::*PMEMBERFUNCTION)();


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	//! @brief ���� ���� ������ �Բ� �����Ѵ�. @param _tickGap ���� ����
	explicit CFunctionMember(_In_ TICK::duration _tickGap=TICK::seconds(1)) : CGSchedulable::NExecutable(_tickGap) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION_MEMBER);}
	//! @brief ������ ��� �Լ��� ��ü �׸��� ���� ������ �����ϸ� �����Ѵ�. @param _Object '��� ��ü' @param _pMemberFunction '���� �� ��� �Լ�' @param _tickGap '���� ����'
	explicit CFunctionMember(_In_ TCLASS* _Object, _In_ PMEMBERFUNCTION _pMemberFunction, _In_ TICK::duration _tickGap=TICK::seconds(1)) : CGSchedulable::NExecutable(_tickGap), CGExecutable::CFunctionMember<TCLASS>(_Object, _pMemberFunction) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION_MEMBER);}
	virtual ~CFunctionMember()	{}
};


}
}