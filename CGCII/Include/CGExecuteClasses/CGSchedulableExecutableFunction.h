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

 @class		CFunction
 @brief		Ư�� �Լ��� �����ð����� Executor�� �ɾ��ִ� Schedulable Ŭ����
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TEXECUTE=TFUNCTION>
class CFunction :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGSchedulable::NExecutable,
	public						CGExecutable::CFunction<TEXECUTE>
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	//! @brief �⺻ ������.
	explicit CFunction() : NExecutable() { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}
	//! @brief ���� ���� ������ �Բ� �����Ѵ�. @param _tickGap ���� ����
	explicit CFunction(_In_ TICK::duration _tickGap) : NExecutable(_tickGap) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}
	//! @brief ���� �Լ��� ������ �Բ� �����Ѵ�. @param _Function ���� �Լ�
	explicit CFunction(_In_ const TFUNCTION& _Function) : CGSchedulable::NExecutable(), CGExecutable::CFunction<TEXECUTE>(_Function) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}
	//! @brief ���� �Լ��� ���� ���� ������ �Բ� �����Ѵ�. @param _Function ���� �Լ� @param _tickGap ���� ����
	explicit CFunction(_In_ const TFUNCTION& _Function, _In_ TICK::duration _tickGap) : CGSchedulable::NExecutable(_tickGap), CGExecutable::CFunction<TEXECUTE>(_Function) { SetObjectType(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}

	virtual ~CFunction()		{}
};


}
}
