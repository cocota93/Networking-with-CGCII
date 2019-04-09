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

 @class		ICGStartable
 @brief		����/����/�������/�ٽý��� �Ӽ��� ���� �������̽� Ŭ����
 @todo		
 @ref		ICGOpenable, ICGCloseable, ICGInitializable, ICGDestroyable
 @details	\n
 ����(Start)/����(Stop)/����(Pause)/�簳(Continue) �Ӽ��� ������ �ִ� �������̽� Ŭ�����̴�.

*/
//-----------------------------------------------------------------------------
class ICGStartable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual	~ICGStartable()		{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief �����Ѵ�. @param _pMSG ���۽� ������ ���� @return true ���� @return false ����
			bool				Start()									{ CGMSG_CONTEXT tempMSG; return Start(tempMSG);}
	virtual	bool				Start(CGMSG_CONTEXT& _Msg) PURE;

	//! @brief �����Ѵ�. @return true ���� @return false ����
	virtual	bool				Stop() PURE;
};
