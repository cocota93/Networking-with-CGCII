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

 @class		CListPriority
 @brief		ť�׵� Executable���� �켱����ť �˰����� ����� ���ʷ� �����Ѵ�.
 @todo		
 @ref		
 @details	\n
 �⺻���� ������ ť�׵� Executable ��ü �� ���ǵ� ����ð��� ���� �͵鸸 �������ش�.
 �켱���� ť(Priority queue)�� ����� �Ź� ��� ��ϵ� ��ü�� ��ȸ���� �ʰ� ���� ����Ǿ�� �ϴ� ��ü�� ������ �ش�.

*///-----------------------------------------------------------------------------
class CListPriority :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	//! @brief '������' ������ �Բ� �����Ѵ�. @param _pExecutor '������'
			CListPriority(ICGExecutor* _pExecutor=nullptr);
	virtual ~CListPriority();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//!	@brief �����ڸ� �ݴ´�. @return true ���� @return false ����
	virtual	bool				Stop() override;

	//! @brief '���� ��ü'�� ����Ѵ�. @param _pExecutable ����� '���� ��ü' @return true ���� @return false ���� (�̹� ��ϵ� ��ü�� ��� �߻��Ѵ�.)
			bool				RegisterExecutable(_In_ ICGExecutable* _pExecutable);
	//! @brief ��ϵ� '���� ��ü'�� �����Ѵ�. @param _pExecutable ��� ���� �� '���� ��ü' @return true ���� @return false ���� (�ش� ��ü�� ��ϵ� ���°� �ƴ� ��� �߻��Ѵ�.)
			bool				UnregisterExecutable(_In_ ICGExecutable* _pExecutable);
	//!	@brief ��ϵ� ��� '���� ��ü��' �����Ѵ�.
			void				UnregisterAllExecutor();

	//!	@brief ��ϵ� '���� ��ü'�� ������ ��´�. @return ��ϵ� '������ ��ü'�� ��
			size_t				GetExecutorCount() const;
	//!	@brief ��ϵ� '���� ��ü'�� �ϳ��� ������ Ȯ���Ѵ�. @return true ��� ����. @return false ��� ���� ����.
			bool				IsEmpty() const							{	return GetExecutorCount()==0;}
	//!	@brief ��ϵ� '���� ��ü'���� �ϳ��� �ִ��� Ȯ���Ѵ�. @return true ��� ���� ����. @return false ��� ����.
			bool				IsExist() const							{	return GetExecutorCount()!=0;}
			
	//! @brief ������ '������'�� ��´�. @return ������ '������'
			CGPTR<ICGExecutor>	GetExecutor() const						{	return m_pexecutorDefault;}
	//! @brief '������'�� �����Ѵ�. @param _pExecutor ����� '������'
			void				SetExecutor(_In_ ICGExecutor* _pExecutor){	m_pexecutorDefault=_pExecutor;}
	//! @brief ������ '������'�� �����Ѵ�.
			void				ResetExecutor()							{	m_pexecutorDefault.reset();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Executor list
			LOCKABLE<vector<CGPTR<ICGExecutable>>>	m_priorityqueueExecutable;

	// 2) Executor
			CGPTR<ICGExecutor>	m_pexecutorDefault;

	//!	@brief '���� ��ü'�� ������ ��û�Ѵ�. @param _pExecutor ������ '���� ��ü' @param _Param ���� �� ������ ���� @return true ���� @return false ����
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Param=0) override;

	// 3) Execute�Լ�.
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) override;

			void				HeapDownExecutable();

};


}