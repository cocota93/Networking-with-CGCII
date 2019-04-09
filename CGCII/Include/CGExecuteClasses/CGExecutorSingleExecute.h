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

namespace CGExecutor
{

//-----------------------------------------------------------------------------
/**

 @class		CSingleExecute
 @brief		������ �ð��� 1ȸ�� ����Ǵ� Executable�� ó���ϴ� Executor�̴�.
 @todo		
 @ref		
 @details	\n
 ������ �ð��� 1ȸ�� ����ǰ� ����� Executable�� �����Ѵ�.
 ���������δ� �켱����ť(Priority Queue)�� ����ؼ� ��������� ������ �ſ� ���� 
 Executable�� �־ ȿ�������� ó���� �����ϴ�.
 ���� ���� ���� ������ �������� ������ �������� ��� ����� ������ ��� �õ��Ѵ�.
 ���� ������� ���� Executable�� ��� CancelExecutable()�Լ��� ������ �� �ִ�.
 �⺻ �ִ� ť�� ���̴� 8192���� �����Ǿ� �ִ�. (�ʿ�� �ڵ� Ȯ��ȴ�.)

 �� ��ü������ Executable�� ���������� �ʰ� �ٸ� Executor�� ������ ��û�ϱ⸸ �ϹǷ�
 �ݵ�� ���� ���� SetExecutor()�Լ��� �Ͽ��� Executor�� �ݵ�� ������ �־�� �Ѵ�.
 ���� Executor�� �����Ǿ� ���� ������ �ƹ��� ���۵� ���� �ʴ´�.

*///-----------------------------------------------------------------------------
class CSingleExecute : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CSingleExecute(_In_ ICGExecutor* _pExecutor=nullptr);
	virtual ~CSingleExecute();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Stop
	//!	@brief '������'�� �ݴ´�. @return true ���� @return false ����
	virtual	bool				Stop() override;

	// 2) Cancel Execution
	//! @brief ������ '���� ��ü'�� ����Ѵ�. @param	_pExecutable ����� Executable ��ü @return true ���� @return false ����
			bool				CancelExecutable(_In_ ICGExecutable* _pExecutable);
	//!	@brief	��� '���� ��ü'�� ����Ѵ�. 	@details �� �Լ��� �����ϸ� ť�׵� Executable�� 0���� �ȴ�.
			void				CancelAllExecutable();

	// 3) Attribute
	//!	@brief ť�׵� '���� ��ü'�� ������ ��´�. @return ť�׵� '������ ��ü'�� ��
			size_t				GetExecutableCount() const;
	//! @brief ���� ť�׵� '���� ��ü'�� �ϳ��� ������ Ȯ���Ѵ�. @return true ����ִ�. @return	false �����Ѵ�. @details IsExist()�� �ݴ� �Լ��̴�.
			bool				IsEmpty() const							{	return GetExecutableCount()==0;}
	//! @brief ���� ť�׵� '���� ��ü'�� �����ϴ��� Ȯ���Ѵ�. @return	true �����Ѵ�. @return false �������� �ʴ´�.
			bool				IsExist() const							{	return GetExecutableCount()!=0;}

	// 4) Executor
	//! @brief �����Ǿ��� '������'�� ��´�.	@return	������ '������'
			CGPTR<ICGExecutor>	GetExecutor() const						{	return m_pExecutor;}
	//! @brief '���� ��ü'�� ó���� �� '������'�� �����Ѵ�. @param _pExecutor ������ '������;
			void				SetExecutor(_In_ ICGExecutor* _pExecutor){	m_pExecutor=_pExecutor;}
	//! @brief ������ '������'�� �����Ѵ�.(nullptr�� �����Ѵ�)
			void				ResetExecutor()							{	m_pExecutor.reset();}

	// 5) Post�Լ���.
	//!	@brief	������ �ð��� '���� ��ü'�� �����Ѵ�. @param _tickTime ������ �ð�(TICK) @param _pExecutable ������ '���� ��ü' @param _Para ���� �� ������ ���� @return true ���� @return false ����
			bool				PostExecuteAt(_In_ TICK::time_point _tickTime, _In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0);
	//!	@brief	���� �ð��� �������� ������ �ð� ���Ŀ� '���� ��ü'�� �����Ѵ�.	@param _tickDiffer 	������ ���������� �ð���	@param _pExecutable	������ '���� ��ü' @param _Para ���� �� ������ ���� @return true ���� @return false ����
			bool				PostExecuteAfter(_In_ TICK::duration _tickDiffer, _In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// Definitions)
			struct EXECUTION_AT;

	// 1) Executor(�Ϲ������� CGExecutor::Defualt�� Executor)
			CGPTR<ICGExecutor>	m_pExecutor;

	// 2) Executable list
			LOCKABLE<vector<EXECUTION_AT>>	m_priorityqueueExecutable;

	// 3) Executable Push/Pop
			void				PushExecutable(_In_ const EXECUTION_AT& _pExecutable);
			void				PopExecutable();

	//!	@brief	������ ��û�ϴ� ���� ��� ����ȴ�. @param _pExecutable ������ '���� ��ü' @param _Para ����� �ѱ� ���� @return true ���� @return false ����
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0) override;

	// 4) Execute�Լ�.
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) override;

};


}