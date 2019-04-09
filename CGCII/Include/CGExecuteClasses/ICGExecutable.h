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

 @class		ICGExecutable
 @brief		������ ó���� �����ϴ� ����(Functor) Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ICGExecutable ��ü�� ICGExecutor�� ���� ����Ǵ� ��ü�̴�.
 ó���ؾ��� ������ ICGExecutable Ŭ������ ProcessExecute(...)�� ������ ��ü�� ������ Executor�� ������ ��û�Ѵ�.

*///-----------------------------------------------------------------------------
class ICGExecutable :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						OVERLAPPED,								// (@) OVERLAPPED structure
	virtual public				ICGObjectIdentifiable,
	virtual public				ICGReferenceable						// (@) Reference count
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	explicit ICGExecutable() : m_countConcurrentExecuting(0), m_countMaxConcurrentExecuting(INT_MAX)	{	hEvent=NULL;}
	explicit ICGExecutable(_In_ size_t p_iMaxConcurrentExecuting) : m_countConcurrentExecuting(0), m_countMaxConcurrentExecuting(p_iMaxConcurrentExecuting)	{	hEvent=NULL;}
	virtual	~ICGExecutable()											{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief	���� ���� ���� ������ ��´�. @return ���� ���� ���� ����
			size_t				GetConcurrentExecutingCount() const		{	return m_countConcurrentExecuting;}
	//! @brief �ִ� ���� ���� ������ �����Ѵ�. @return �ִ� ���� ���� ����
			size_t				GetMaxConcurrentExecutingCount() const	{	return m_countMaxConcurrentExecuting;}
	//! @brief ���ÿ� ���� �ɼ� �ִ� �ִ� ������ �����Ѵ�. @param	�ִ� ���� ���� ����
			void				SetMaxConcurrentExecutingCount(size_t p_iCount){	m_countMaxConcurrentExecuting=p_iCount;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	// 2) ó���Ǿ���� ������ ������ �Լ�
	/**
	@brief	���� �� ������ �����Ѵ�.
	@param	_Return		���� ����� �Ѱ��ش�.
	@param	_Param		���޵� �Ķ����
	@return	0			����
	@return	!0			����
	*/
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) PURE;

public:
			intptr_t			lResult;
			size_t				dwBytesTransferred;
			TICK::time_point	tickTime;

public:
			ATOMIC<size_t>		m_countConcurrentExecuting;
			size_t				m_countMaxConcurrentExecuting;
};
