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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGSchedulable
{

//-----------------------------------------------------------------------------
/**

 @class		NExecutable
 @brief		일정시간마다 Executable을 걸어주는 Schedulable 클래스이다.
 @todo		
 @ref		
 @details	\n
 일정시간마다 Executor에 실행이 걸려지는 Schedulable 객체이다.
 실행간격은 SetExecuteInterval()함수로 설정할 수 있다
 실행할 Executor는 SetExecutor()함수로 설정할 수 있다.
 만약 Executor가 설정되어져 있지 않으면 Default Executor에서 실행된다.

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
	//! @brief 설정된 '실행자'를 얻는다. @return 설정된 '실행자'
			CGPTR<ICGExecutor>	GetExecutor() const						{	return m_pexecutor;}
	//! @brief '실행자'를 설정한다. @param _pExecutor 설정할 '실행자'
			void				SetExecutor(_In_ ICGExecutor* _pExecutor){	m_pexecutor=_pExecutor;}
	//! @brief 설정된 '실행자'를 리셋한다.
			void				ResetExecutor()							{	m_pexecutor.reset();}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) OnRegister/OnUnregister
	virtual	void				ProcessOnRegister() override;
	virtual	void				ProcessOnUnregister() override;

	// 2) Execute함수임
	virtual	void				ProcessSchedule() override;
};


}
