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

 @class		CSchedulable
 @brief		ICGScheduable ��ü�� �������ִ� Executor�� �ý��� ���ο����� ���ȴ�.
 @todo		
 @ref		
 @details	\n
 Execute()�Լ��� ��ϵ� ICGSchedulable ��ü�� ������ �ش�.
 �Ϲ������� ICGSchedulable������ �����ð����� 

*///-----------------------------------------------------------------------------
class CSchedulable :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NThread,								//     ICGExeuctor
	public						ICGAttachable<ICGSchedulable>			//     Attachable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	//! @brief '���� ����' ������ �Բ� �����Ѵ�. @param _tickdiff '���� ����'
			CSchedulable();
	//! @brief '��ü �̸�'�� '���� ����' ������ �Բ� �����Ѵ�. @param _strName '��ü �̸�' @param _tickdiff '���� ����'
			CSchedulable(_In_ const _CHAR* _strName);
			CSchedulable(_In_ const _CHAR_SUB* _strName);
	virtual ~CSchedulable();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// Definitions)
			typedef	circular_list<CGPTR<ICGSchedulable>>	CONTAINER;
			class ITERATOR;
public:
	// 1) Destroy
	//!	@brief '������'�� �ݴ´�. @return true ���� @return false ����
	virtual	bool				Stop() override;

	// 2) RegisterSchedulable/UnregisterSchedulable
	//!	@brief '������ ��ü'�� ����Ѵ�. @param _pSchedulable ����� '������ ��ü' 	@return true ���� @return false ����(�̹� ������ ��� �����Ѵ�.)
			bool				RegisterSchedulable(_In_ ICGSchedulable* _pSchedulable)		{ return ProcessAttach(_pSchedulable);}
	//! @brief ��ϵ� '������ ��ü'�� �����Ѵ�. @param _pSchedulable ��������� '������ ��ü' @return @return true ���� @return false ����(�ش� ��ü�� �������� ���� ��� �����Ѵ�.)
			bool				UnregisterSchedulable(_In_ ICGSchedulable* _pSchedulable)	{ return ProcessDetach(_pSchedulable)!=0;}
	//! @brief ��� '������ ��ü'�� ��� ���� �Ѵ�.
			int					UnregisterAllSchedulable();

	// 3) Iterator
	//! @brief	��ϵ� '������ ��ü'�鿡 �����ϱ� ���� �ݺ��ڸ� ��´�. @return !nullptr �ݺ��� @return nullptr ȹ�� ����
			ITERATOR			GetIterator();

	// 4) Schedulable
	//!	@brief ��ϵ� '������ ��ü'�� ������ ��´�. @return ��ϵ� '������ ��ü'�� ��
			size_t				GetSchedulableCount() const;

	//!	@brief ��ϵ� '������ ��ü'�� �ϳ��� ������ Ȯ���Ѵ�. @return true ��� ����. @return false ��� ���� ����.
			bool				IsEmpty() const;
	//!	@brief ��ϵ� '������ ��ü'���� �ϳ��� �ִ��� Ȯ���Ѵ�. @return true ��� ���� ����. @return false ��� ����.
			bool				IsExist() const;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Post�Լ���.
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0) override;

	// 2) Execute�Լ���...
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) override;

	// 3) Attach/Detach
	virtual	bool				ProcessAttach(_In_ ICGSchedulable* _pSchedulable) override;
	virtual	int					ProcessDetach(_In_opt_ ICGSchedulable* _pSchedulable) override;

private:
	// 1) Tick Gap
			LOCKABLE<CONTAINER>	m_listSchedulable;
			CONTAINER::iterator	m_iterNow;
};

class CSchedulable::ITERATOR
{
public:
	ITERATOR() : m_csLock(nullptr) {}
	ITERATOR(const CGD::lockable& cs, const CONTAINER::iterator& _iterBegin, const CONTAINER::iterator& _iterEnd) : m_csLock(cs), m_iter(_iterBegin), m_iterEnd(_iterEnd)	{}

public:
	bool			IsContinue() const	{	return m_iter!=m_iterEnd;}
	bool			IsEnded() const		{	return m_iter==m_iterEnd;}
	bool			MoveNext()			{	if(m_iter==m_iterEnd) return false; ++m_iter; return true;}
				
	void			operator++()		{	++m_iter;}
	ICGSchedulable*	operator->()		{	return *m_iter;}
	ICGSchedulable*	operator*()			{	return *m_iter;}

public:
			CGD::lock_guard			m_csLock;
			CONTAINER::iterator		m_iter;
			CONTAINER::iterator		m_iterEnd;
};


}