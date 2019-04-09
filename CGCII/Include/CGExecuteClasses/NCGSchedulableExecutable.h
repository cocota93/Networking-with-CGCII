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

//-----------------------------------------------------------------------------
/**

 @class		NExecutable
 @brief		�����ð����� Executable�� �ɾ��ִ� Schedulable Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 �����ð����� Executor�� ������ �ɷ����� Schedulable ��ü�̴�.
 ���ణ���� SetExecuteInterval()�Լ��� ������ �� �ִ�
 ������ Executor�� SetExecutor()�Լ��� ������ �� �ִ�.
 ���� Executor�� �����Ǿ��� ���� ������ Default Executor���� ����ȴ�.

*///-----------------------------------------------------------------------------
class NExecutable :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NCGSchedulable,
	virtual public				ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			NExecutable(_In_ TICK::duration _tickdifferExecute=TICK::seconds(1));
	virtual ~NExecutable();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Executor
	//! @brief ������ '������'�� ��´�. @return ������ '������'
			CGPTR<ICGExecutor>	GetExecutor() const						{	return m_pexecutor;}
	//! @brief '������'�� �����Ѵ�. @param _pExecutor ������ '������'
			void				SetExecutor(_In_ ICGExecutor* _pExecutor){	m_pexecutor=_pExecutor;}
	//! @brief ������ '������'�� �����Ѵ�.
			void				ResetExecutor()							{	m_pexecutor.reset();}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) OnRegister/OnUnregister
	virtual	void				ProcessOnRegister() override;
	virtual	void				ProcessOnUnregister() override;

	// 2) Execute�Լ���
	virtual	void				ProcessSchedule() override;
};


}
