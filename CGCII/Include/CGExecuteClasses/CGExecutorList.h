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

 @class		CList
 @brief		���� ���� Executor�� ���� Executor ��ü�̴�.
 @todo		
 @ref		
 @details	\n
 Execute()�Լ��� ȣ��Ǹ� ��ϵ� ��� Executor�� Execute()�Լ��� ȣ���� �ش�.

*///-----------------------------------------------------------------------------
template <class TEXECUTOR>
class CList :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutor,
	virtual public				ICGAttachable<TEXECUTOR>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CList();
	virtual ~CList();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// Definitions) 
			typedef	circular_list<CGPTR<TEXECUTOR>>	CONTAINER;
			class ITERATOR;

	//!	@brief �����ڸ� �ݴ´�. @return true ���� @return false ����
	virtual	bool				Stop() override;

	// 2) Attach/Detach
	//! @brief '������'�� ����Ѵ�. @param _pExecutor ����� '������' @return true ��� ���� @return false ��� ����(�Ϲ������� ������ ��ü�� ��ϵǾ� ���� ��� �����Ѵ�.)
			bool				RegisterExecutor(_In_ TEXECUTOR* _pExecutor)	{ return ProcessAttach(_pExecutor);}
	//! @brief ��ϵ� '������'�� �����Ѵ�. @param _pExecutor ��������� '������' @return true ������� ���� @return false ������� ����(�Ϲ������� �ش� ��ü�� ��ϵǾ� ���� ���� ��� �����Ѵ�.)
			bool				UnregisterExecutor(_In_opt_ TEXECUTOR* _pExecutor)	{ return ProcessDetach(_pExecutor);}
	//! @brief ��ϵ� ��� '������'�� �����Ѵ�.
			int					UnregisterAllExecutor();

	// 3) Iterator
	//! @brief	��ϵ� '���� ��ü'�鿡 �����ϱ� ���� �ݺ��ڸ� ��´�. @return !nullptr �ݺ��� @return nullptr ȹ�� ����
			ITERATOR			GetIterator();

	// 4) Attribute
	//!	@brief ��ϵ� '���� ��ü'�� ������ ��´�. @return ��ϵ� '������ ��ü'�� ��
			size_t				GetExecutorCount() const;
	//!	@brief ��ϵ� '������'�� �ϳ��� ������ Ȯ���Ѵ�. @return true ��� ����. @return false ��� ���� ����.
			bool				IsEmpty() const;
	//!	@brief ��ϵ� '������'���� �ϳ��� �ִ��� Ȯ���Ѵ�. @return true ��� ���� ����. @return false ��� ����.
			bool				IsExist() const;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Executor list
			LOCKABLE<CONTAINER>	m_listExecutor;

	// 2) Execute
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) override;

	// 3) Post�Լ���.
	//! @brief '���� ��ü'�� ó���� ��û�Ѵ�. @param _pExecutable '���� ��ü' @param _Para ���� �� ������ ���� @return true ���� @return false ����
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0) override;

	// 4) Attach/Detach
	virtual	bool				ProcessAttach(_In_ TEXECUTOR* _pSchedulable) override;
	virtual	int					ProcessDetach(_In_opt_ TEXECUTOR* _pSchedulable) override;
};


}

#include "CGExecuteclasses/CGExecutorList.inl"