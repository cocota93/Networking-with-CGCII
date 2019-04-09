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
//-----------------------------------------------------------------------------
/**

 @class		ICGExecutable
 @brief		실행의 처리를 정의하는 펑터(Functor) 클래스이다.
 @todo		
 @ref		
 @details	\n
 ICGExecutable 객체는 ICGExecutor에 의해 실행되는 객체이다.
 처리해야할 내용을 ICGExecutable 클래스의 ProcessExecute(...)에 정의해 객체를 생성후 Executor에 실행을 요청한다.

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
	//! @brief	현재 동시 실행 갯수를 얻는다. @return 현재 동시 실행 갯수
			size_t				GetConcurrentExecutingCount() const		{	return m_countConcurrentExecuting;}
	//! @brief 최대 동시 실행 갯수를 설정한다. @return 최대 동시 실행 갯수
			size_t				GetMaxConcurrentExecutingCount() const	{	return m_countMaxConcurrentExecuting;}
	//! @brief 동시에 실행 될수 있는 최대 갯수를 설정한다. @param	최대 동시 실행 갯수
			void				SetMaxConcurrentExecutingCount(size_t p_iCount){	m_countMaxConcurrentExecuting=p_iCount;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	// 2) 처리되어야할 내용을 정의한 함수
	/**
	@brief	실행 될 내용을 정의한다.
	@param	_Return		실행 결과를 넘겨준다.
	@param	_Param		전달된 파라메터
	@return	0			성공
	@return	!0			실패
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
