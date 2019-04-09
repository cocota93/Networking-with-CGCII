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

 @class		Manager
 @brief		예외 관리자이다.
 @todo		
 @ref		
 @details	\n
 Access Violation과 같은 SEH에 의해 발생하는 Exception을 관리하는 매니저이다.
 일반적으로 예외가 발생했을 때 덤프를 남기는 역할을 수행한다.
 내부적으로 같은 주소에서 발생하는 예외에 대해서는 중복적으로 Dump를 남기지 않는다.
 SetDumpCountLimit()를 사용해 남기는 최대의 Dump수를 설정할 수 있다.
 (기본값은 DEFAULT_MAX_EXCEPTIONLIMIT:4096개)
 SetDumpType()를 사용하여 남기는 Dump의 내용을 설정할 수 있다.
 (기본값은 DEFAULT_MINIDUMP_TYPE:MINIDUMP_TYPE_MINI)

*///-----------------------------------------------------------------------------
namespace CGExecutor
{

class Manager :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNameable::NString,					// (@) Nameable
	public						NCGDispatchable,
	virtual public				ICGDestroyable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
		typedef	circular_list<ICGExecutor*>::iterator	ITERATOR;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			Manager();
	virtual ~Manager();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Iterator용.
	//! @brief 락 객체를 얻는다.
								operator lockable&()					{	return m_listExcutor;}
	//! @brief 최초 덤프 반복자. @return 첫번째 덤프 반복자
			ITERATOR			begin()									{	return m_listExcutor.begin();}
	//! @brief 마지막 덤프 반복자. @return 마지막 덤프 반복자
			ITERATOR			end()									{	return m_listExcutor.end();}
	//! @brief Executor의 갯수
			size_t				size()									{	return m_listExcutor.size();}


	// 2) Initialize Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '예외 관리자 싱글턴 객체'를 설정한다. @ param _pInstance 설정할 '예외 관리자 싱글턴 객체'
	static	void				SetInstance(Manager* _pInstance);
	//! @brief '예외 관리자 싱글턴 객체'를 리셋한다.
	static	void				ResetInstance();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	//! @brief 쓰레드 객체를 등록한다. @return true 성공 @return false 실패
			bool				RegisterExecutor(_In_ ICGExecutor* _pExecutor);
	//! @brief 쓰레드 객체를 등록해제한다. @return true 성공 @return false 실패
			bool				UnregisterExecutor(_In_ ICGExecutor* _pExecutor);

	//! @brief 쓰레드가 등록될 때 호출되는 함수
	virtual	void				ProcessOnRegister()						{}
	//! @brief 쓰레드가 등록해제될 때 호출되는 함수
	virtual	void				ProcessOnUnregister()					{}
protected:
	// 1) Executor 관련
			LOCKABLE<circular_list<ICGExecutor*>> m_listExcutor;

	// 2) Instance
	static	CGOWN<Manager>		m_pInstance;
	static	LOCKABLE<>			m_csCreate;
	static	void				InitInstance();

public:
	// 3) Destroy
	virtual	bool				Destroy() override;
};


}

