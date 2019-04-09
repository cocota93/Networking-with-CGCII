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

namespace CGExecutor
{

//-----------------------------------------------------------------------------
/**

 @class		CSchedulable
 @brief		ICGScheduable 겍체를 실행해주는 Executor로 시스템 내부용으로 사용된다.
 @todo		
 @ref		
 @details	\n
 Execute()함수는 등록된 ICGSchedulable 객체를 실행해 준다.
 일반적으로 ICGSchedulable에서는 일정시간마다 

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
	//! @brief '실행 간격' 설정과 함께 생성한다. @param _tickdiff '실행 간격'
			CSchedulable();
	//! @brief '객체 이름'과 '실행 간격' 설정과 함께 생성한다. @param _strName '객체 이름' @param _tickdiff '실행 간격'
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
	//!	@brief '실행자'를 닫는다. @return true 성공 @return false 실패
	virtual	bool				Stop() override;

	// 2) RegisterSchedulable/UnregisterSchedulable
	//!	@brief '스케쥴 객체'를 등록한다. @param _pSchedulable 등록할 '스케쥴 객체' 	@return true 성공 @return false 실패(이미 존재할 경우 실패한다.)
			bool				RegisterSchedulable(_In_ ICGSchedulable* _pSchedulable)		{ return ProcessAttach(_pSchedulable);}
	//! @brief 등록된 '스케쥴 객체'를 해제한다. @param _pSchedulable 등록해제할 '스케쥴 객체' @return @return true 성공 @return false 실패(해당 객체가 조재하지 않을 경우 실패한다.)
			bool				UnregisterSchedulable(_In_ ICGSchedulable* _pSchedulable)	{ return ProcessDetach(_pSchedulable)!=0;}
	//! @brief 모든 '스케쥴 객체'를 등록 해제 한다.
			int					UnregisterAllSchedulable();

	// 3) Iterator
	//! @brief	등록된 '스케쥴 객체'들에 접근하기 위한 반복자를 얻는다. @return !nullptr 반복자 @return nullptr 획득 실패
			ITERATOR			GetIterator();

	// 4) Schedulable
	//!	@brief 등록된 '스케쥴 객체'의 갯수를 얻는다. @return 등록된 '스케쥴 객체'의 수
			size_t				GetSchedulableCount() const;

	//!	@brief 등록된 '스케쥴 객체'가 하나도 없는지 확인한다. @return true 비어 있음. @return false 비어 있지 않음.
			bool				IsEmpty() const;
	//!	@brief 등록된 '스케쥴 객체'들이 하나라도 있는지 확인한다. @return true 비어 있지 않음. @return false 비어 있음.
			bool				IsExist() const;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Post함수임.
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para=0) override;

	// 2) Execute함수임...
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