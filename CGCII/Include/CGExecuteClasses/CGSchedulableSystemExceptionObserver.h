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
namespace System
{

//-----------------------------------------------------------------------------
/**

 @class		CExceptionObserver
 @brief		Exception �����ڸ� �����ð����� �������ش�.
 @todo		
 @ref		
 @details	\n
 Exception �����ڿ����� �����带 �����ϸ� ����� ���� ���� �߻��ϸ� �������ܸ� ����
 ������� Ǫ�� �ϰ� ���� �۾��� �����Ѵ�.

*///-----------------------------------------------------------------------------
class CExceptionObserver:
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NCGSchedulable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			CExceptionObserver();
	virtual ~CExceptionObserver();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) OnRegister/OnUnregister
	virtual	void				ProcessOnRegister() override;
	virtual	void				ProcessOnUnregister() override;

	// 2) Execute�Լ���...
	virtual	void				ProcessSchedule() override;

	// 3) ...
			LOCKABLE<CGPTR<CGException::Manager>>	m_pmanagerException;
};


}
}