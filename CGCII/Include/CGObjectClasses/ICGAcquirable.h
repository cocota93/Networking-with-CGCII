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

 @class		ICGPausable
 @brief		�������/�ٽý��� �Ӽ��� ���� �������̽� Ŭ����
 @todo		
 @ref		ICGInitializable, ICGDestroyable, ICGStartable
 @details	\n
 �������(Pause)/�簳(Continue) �Ӽ��� ������ �ִ� �������̽� Ŭ�����̴�.

*/
//-----------------------------------------------------------------------------
class ICGAcuquirable :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual	~ICGAcuquirable()	{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief �����Ѵ�. @return true ���� @return false ����
	virtual	eOBJECT_RESULT		Acquire() PURE;

	//! @brief �簳�Ѵ�. @return true ���� @return false ����
	virtual	void				Unacquire() PURE;
};
