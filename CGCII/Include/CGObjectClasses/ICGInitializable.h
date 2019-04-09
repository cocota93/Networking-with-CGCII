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

 @class		ICGInitializable
 @brief		�ʱ�ȭ�ϱ�(Initialize) �Լ��� ���� �������̽� Ŭ�����̴�.
 @todo		
 @ref		ICGOpenable, ICGCloseable, ICGDestroyable
 @details	\n
 �ʱ�ȭ�ϱ�(Initialize) �Լ��� ���� �������̽� Ŭ�����̴�.
 ICGDestroyable Ŭ������ ��ӹ޾� �Ҹ��ϱ�(Destroy)�� ������ ���ȴ�.
 
*/
//-----------------------------------------------------------------------------
class ICGInitializable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGDestroyable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGInitializable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief ���� ���� ���� �ʱ�ȭ�� �����Ѵ�. @return true ���� @return false ����
			bool				Initialize() { CGMSG_CONTEXT tempMSG; return Initialize(tempMSG); }

	//! @brief �ʱ�ȭ �Ѵ�. @param _Msg �ʱ�ȭ ���ڸ� ������ �޽��� @return true ���� @return false ����
	virtual	bool				Initialize(CGMSG_CONTEXT& _Msg) PURE;
};
