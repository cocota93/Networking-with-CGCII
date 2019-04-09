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

 @class		CFactoryGarbageCollection
 @brief		Ǯ ������ ���� ������ ȣ�����ش�.
 @todo		
 @ref		
 @details	\n
 Factory �Ŵ����� ����(Sustain)�Լ��� ȣ���� Ǯ�� ������ �ݷ��� ó�� ��� ���� ����Ȱ���� ó���Ѵ�.

*///-----------------------------------------------------------------------------
class CFactoryGarbageCollection:
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NCGSchedulable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			CFactoryGarbageCollection();
	virtual ~CFactoryGarbageCollection();


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
			LOCKABLE<CGPTR<CGFactory::Manager>>	m_pmanagerFactory;
};


}
}