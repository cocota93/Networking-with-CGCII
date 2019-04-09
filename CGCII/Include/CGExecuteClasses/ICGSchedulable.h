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
//-----------------------------------------------------------------------------
/**

 @class		ICGSchedulable
 @brief		Ư�� �ð��� ������ �����ؾ� �ϴ� ���� �����ϴ� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
class ICGSchedulable :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGObjectIdentifiable,
	virtual public				ICGReferenceable						// (@) Reference count
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGSchedulable()											{}
	virtual	~ICGSchedulable()											{}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	//! @brief ��ϵ� �� ȣ��Ǵ� �Լ�
	virtual	void				ProcessOnRegister() PURE;

	//! @brief ����� ������ �� ȣ��Ǵ� �Լ�
	virtual	void				ProcessOnUnregister() PURE;

	//! @brief ������ ó���� ���� ȣ��Ǵ� �Լ�.
	virtual	void				ProcessSchedule() PURE;

protected:
	// 3) ������ Schedule�� �߰��� 
			CGPTR<ICGExecutor>	m_pexecutor;

};
