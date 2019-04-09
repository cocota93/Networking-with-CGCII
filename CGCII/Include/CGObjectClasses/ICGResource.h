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

 @class		ICGResource
 @brief		�ڿ� �Ӽ� �������̽� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 �ڿ�(Resource)�� �⺻ �Ӽ��� ������ �������̽� Ŭ������ IObject�� ��ӹ޾Ҵ�.
 �� �������̽��� ��ӹ����� '�ڿ� ������'�� ���� ������ �� �ִ�.
 
*/
//-----------------------------------------------------------------------------
class ICGResource : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						ICGObjectIdentifiable,
	virtual public				ICGMessageable,
	virtual public				ICGNameable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual ~ICGResource()											{}
};
