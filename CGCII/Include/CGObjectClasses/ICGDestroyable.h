//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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

 @class		ICGDestroyable
 @brief		�Ҹ��ϱ�(Destroy) �Լ��� ���� �������̽� Ŭ����
 @todo		
 @ref		ICGCloseable, ICGInitializable, ICGDestroyable
 @details	\n
 �Ҹ��ϱ�(Destroy) �Լ��� ���� �������̽� Ŭ�����̴�.
 �Ϲ������� ICGInitialzable Ŭ������ Initialize()�� �Բ� ���ȴ�.

*/
//-----------------------------------------------------------------------------
class ICGDestroyable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGDestroyable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief �Ҹ��Ѵ�. @return true ���� @return false ����
	virtual	bool				Destroy() PURE;
};
