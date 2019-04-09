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

#define	CGEXECUTOR_AUTO		(-1)
#define	CGEXECUTOR_NOTHREAD	0

namespace CGExecutor
{

//-----------------------------------------------------------------------------
/**

 @class		Default
 @brief		내부적으로 자동 생성되는 기본 Executor이다.
 @todo		
 @ref		
 @details	\n
 내부적으로 사용되는 모든 실행처리에 사용되는 싱글턴 Executor이다.
 내부적으로 다중 쓰레드 Executor와 SingleExecutor와 Scheduler를 가지고 있다.
 기본적으로는 자동생성되나 초기화기 필요할 경우 InitInstance()를 호출해 초기화할 수도 있다.
 실행요청은 PostExecute(...)함수로 가능하며 RegisterSchedulable로 Scheudler에 등록할 수도 있다.
 소멸처리도 자동으로 되기 때문에 다른 처리를 해줄 필요도 없다.

*///-----------------------------------------------------------------------------
class Default : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNameable::NString,
	public						NCGObjectState,
	public						NCGInitializable,
	public						ICGReferenceable::NoAct
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			Default();
	virtual ~Default();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Create/Destroy
	//! @brief '기본 실행자'의 싱글턴 객체를 초기화한다. @param _nT 생성할 쓰레드 갯수 CGEXECUTOR_AUTO(-1)이면 코어 갯수에 따라 자동 계산되 생성된다.
	static	void				InitInstance(_In_ int _nT=CGEXECUTOR_AUTO);
	//! @brief '기본 실행자'의 싱글턴 객체를 초기화한다. @param _nT 생성할 쓰레드 갯수 CGEXECUTOR_AUTO(-1)이면 코어 갯수에 따라 자동 계산되 생성된다.
	static	void				InitInstance(CGMSG_CONTEXT& _Msg);
	//! @brief '기본 실행자'를 파괴한다.
	static	void				DestroyInstance();

	// 2) Instance Get/Set/Reset
	//! @brief '기본 실행자'의 싱글턴 객체를 얻는다. @return '기본 실행자'
	static	Default*			GetInstance()							{	if(m_Instance.m_pexecutorDefaultSingly.empty()) InitInstance(); return &m_Instance;}

	//! @brief 쓰레드 갯수를 얻는다. @return 쓰레드 갯수
	static	int					GetThreadCount();
	//!	@brief 프로세스 갯수를 얻는다. @return 프로세스 갯수
	static	int					GetProcessCount();

	// 3) Executor/Scheduler Get
	//! @brief '기본 실행자'를 얻는다. @return '기본 실행자' 포인터
	static	CGPTR<CCompletionPortThread> GetExecutor()					{	if(m_Instance.m_pexecutorDefault.empty()) InitInstance(); return m_Instance.m_pexecutorDefault;}
	//! @brief '기본 스케쥴러'를 얻는다. @return '기본 스케쥴러'
	static	CGPTR<CSchedulable>		GetScheduler()						{	if(m_Instance.m_pexecutorSchedulable.empty()) InitInstance(); return m_Instance.m_pexecutorSchedulable;}
	//! @brief 기본 단일 실행 스케쥴러를 얻는다. @return '기본 단일 실행 스케쥴러'
	static	CGPTR<CSingleExecute>	GetSchedulerSingly()				{	if(m_Instance.m_pexecutorDefaultSingly.empty()) InitInstance(); return m_Instance.m_pexecutorDefaultSingly;}

	//! @brief '실행자'를 얻는다. @return '실행자'
			CGPTR<CCompletionPortThread> Executor()						{	return m_pexecutorDefault;}
	//! @brief '스케쥴러'를 얻는다. @return '스케쥴러'
			CGPTR<CSchedulable>		Scheduler()							{	return m_pexecutorSchedulable;}
	//! @brief '단일 실행 스케쥴러'를 얻는다. @return '단일 실행 스케쥴러'
			CGPTR<CSingleExecute>	SchedulerSingly()					{	return m_pexecutorDefaultSingly;}

	// 4) RunExecutor
	//! @brief '실행자'를 직접 실행시킨다. @details '실행자'를 수동으로 실행시킨다.
	static	void				RunExecutor();

	// 5) Factory Sustainer
	//! @brief '풀 관리자'를 실행시킨다. @return true 성공 @return false 실해
	static	bool				StartFactoryGarbageCollection();
	//! @brief '풀 관리자'를 중지시킨다. @return true 성공 @return false 실해
	static	bool				StopFactoryGarbageCollection();

	// 6) Exception Observer
	//! @brief '예외 관리자'를 실행시킨다. @return true 성공 @return false 실해
	static	bool				StartExceptionObserving();
	//! @brief '예외 관리자'를 중지시킨다. @return true 성공 @return false 실해
	static	bool				StopExceptionObserving();

	// 7) Post Execute
	//!	@brief '실행 객체'의 실행을 요청한다. @param _pExecutable 실행할 '실행 객체' @return true 성공 @return false 실패
	template <class TEXECUTABLE>
	static	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ const CGPTR<TEXECUTABLE>& _pExecutable)	{	return PostExecute(_pExecutable.get());}
	//! @brief 정해진 시간에 '실행 객체'를 실행 요청한다. @param _tickTime 실행할 시간 @param _pExecutable 실행할 '실행 객체' @return true 성공 @return false 실패
	template <class TEXECUTABLE>
	static	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ const CGPTR<TEXECUTABLE>& _pExecutable) { return PostExecute(_tickTime, _pExecutable.get());}
	//!	@brief '실행 객체'의 실행을 요청한다. @param _pExecutable 실행할 '실행 객체' @return true 성공 @return false 실패
	template <class TEXECUTABLE>
	static	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ TEXECUTABLE* _pExecutable)			{	return GetExecutor()->PostExecute(_pExecutable);}
	//! @brief 정해진 시간에 '실행 객체'를 실행 요청한다. @param _tickTime 실행할 시간 @param _pExecutable 실행할 '실행 객체' @return true 성공 @return false 실패
	template <class TEXECUTABLE>
	static	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ TEXECUTABLE* _pExecutable) {	return GetSchedulerSingly()->PostExecuteAt(_tickTime, _pExecutable);}

	//!	@brief 람다 함수의 실행을 요청한다. @param _pExecutable 실행할 람다함수 @return true 성공 @return false 실패
	template <class TFUNCTION>
	static	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TFUNCTION _fFunction);


	//! @brief 정해진 시간에 람다 함수를 실행 요청한다. @param _tickTime 실행할 시간 @param _pExecutable 실행할 람다함수 @return true 성공 @return false 실패
	template <class TFUNCTION>
	static	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ TFUNCTION _fFunction);
	//! @brief 함수의 실행 요청한다. @param _pExecutable 실행할 함수 @return true 성공 @return false 실패
	template <class TFUNCTION>
	static	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TFUNCTION _fFunction);
	//! @brief 정해진 시간에 함수를 실행 요청한다. @param _tickTime 실행할 시간 @param _pExecutable 실행할 함수 @return true 성공 @return false 실패
	template <class TFUNCTION>
	static	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ TFUNCTION _fFunction);


	//! @brief 멤버 함수의 실행 요청한다. @param _Object 대상 객체 @param _pMemberFunction 실행할 멤버 함수 @return true 성공 @return false 실패
	template <class TOBJECT>
	static	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)());
	//! @brief 멤버 함수의 실행 요청한다. @param _Object 대상 객체 @param _pMemberFunction 실행할 멤버 함수 @return true 성공 @return false 실패
	template <class TOBJECT>
	static	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)());
	//! @brief 정해진 시간에 멤버 함수의 실행을 요청한다. @param _tickTime 실행할 시간 @param _Object 대상 객체 @param _pMemberFunction 실행할 멤버 함수 @return true 성공 @return false 실패
	template <class TOBJECT>
	static	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)());
	//! @brief 정해진 시간에 멤버 함수의 실행을 요청한다. @param _tickTime 실행할 시간 @param _Object 대상 객체 @param _pMemberFunction 실행할 멤버 함수 @return true 성공 @return false 실패
	template <class TOBJECT>
	static	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)());

	// 8) Schedulable 
	//! @brief '스케쥴 객체'를 '기본 스케쥴러'에 등록한다. @param _pSchedulable 등록할 '스케쥴 객체' @return true 성공 @return false 실패
	static	bool				RegisterSchedulable(_In_ ICGSchedulable* _pSchedulable);
	//! @brief 등록된 '스케쥴 객체'를 '기본 스케쥴러'에서 해제한다. @param _pSchedulable 등록해제할 '스케쥴 객체' @return true 성공 @return false 실패
	static	bool				UnregisterSchedulable(_In_ ICGSchedulable* _pSchedulable);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Executor/Scheduler/FactoryGarbageCollection
			CGPTR<CGExecutor::CCompletionPortThread>		m_pexecutorDefault;
			CGPTR<CGExecutor::CSingleExecuteThread>			m_pexecutorDefaultSingly;
			CGPTR<CGExecutor::CSchedulable>					m_pexecutorSchedulable;
			CGPTR<CGSchedulable::System::CFactoryGarbageCollection>	m_pschedulableFactoryGarbageCollection;
			CGPTR<CGSchedulable::System::CExceptionObserver> m_pschedulableExceptionObserver;
			LOCKABLE<>			m_csLock;
			int					m_InitParam;

	// 2) Instance
	static	Default				m_Instance;
	static	LOCKABLE<>			m_csCreate;

	// 3) Create Function
	virtual	void				ProcessInitialize(CGMSG_CONTEXT& _Msg) override;
	virtual	void				ProcessDestroy() override;
};


//-----------------------------------------------------------------------------
//
// PostExecute
//
// 1. PostExecute란...
//    lambda함수를 비동기적으로 실행하고 싶을 때 CGExecutable::CFunction를 사용하여
//    Executor에 걸어주어야 한다. 이런 번거러움을 덜어주기 위해 그 과정을 미리
//    정의해 놓은 함수이다.
//
//-----------------------------------------------------------------------------
// For Lambda Function) 
template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
Default::PostExecute(_In_ TFUNCTION _fFunction)
{
	// 1) Lambda용 Executable을 할당받는다.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute함수를 설정한다.
	pExecutable->SetFunction(_fFunction);

	// 3) Post한다.
	return GetSchedulerSingly()->PostExecute(pExecutable);
}

template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
Default::PostExecute(_In_ TICK::time_point _tickTime, _In_ TFUNCTION _fFunction)
{
	// 1) Lambda용 Executable을 할당받는다.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute함수를 설정한다.
	pExecutable->SetFunction(_fFunction);

	// 3) Post한다.
	return GetSchedulerSingly()->PostExecuteAt(_tickTime, pExecutable);
}


// For Function) 
template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
Default::PostExecute(_In_ TFUNCTION _fFunction)
{
	// 1) Lambda용 Executable을 할당받는다.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute함수를 설정한다.
	pExecutable->SetFunction(_fFunction);

	// 3) Post한다.
	return GetSchedulerSingly()->PostExecute(pExecutable);
}

template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
Default::PostExecute(_In_ TICK::time_point _tickTime, _In_ TFUNCTION _fFunction)
{
	// 1) Lambda용 Executable을 할당받는다.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute함수를 설정한다.
	pExecutable->SetFunction(_fFunction);

	// 3) Post한다.
	return GetSchedulerSingly()->PostExecuteAt(_tickTime, pExecutable);
}


// For Member Function) 
template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
Default::PostExecute(_In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)())
{
	// 1) Member함수 Function용 Executable을 할당받는다.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute 함수와 Object를를 설정한다.
	pExecutable->SetObject(_Object);
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post한다.
	return GetExecutor()->PostExecute(pExecutable);
}

template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
Default::PostExecute(_In_ TICK::time_point _tickTime, _In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)())
{
	// 1) Member함수 Function용 Executable을 할당받는다.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute 함수와 Object를를 설정한다.
	pExecutable->SetObject(_Object);
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post한다.
	return GetSchedulerSingly()->PostExecuteAt(_tickTime, pExecutable);
}

template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
Default::PostExecute(_In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)())
{
	// 1) Member함수 Function용 Executable을 할당받는다.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute 함수와 Object를를 설정한다.
	pExecutable->SetObject(_Object.get());
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post한다.
	return GetExecutor()->PostExecute(pExecutable);
}

template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
Default::PostExecute(_In_ TICK::time_point _tickTime, _In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)())
{
	// 1) Member함수 Function용 Executable을 할당받는다.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute 함수와 Object를를 설정한다.
	pExecutable->SetObject(_Object.get());
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post한다.
	return GetSchedulerSingly()->PostExecuteAt(_tickTime, pExecutable);
}


}

#define	POST_EXECUTE			CGExecutor::Default::PostExecute
#define	REGISTER_SCHEDULABLE	CGExecutor::Default::RegisterSchedulable
#define	UNREGISTER_SCHEDULABLE	CGExecutor::Default::UnregisterSchedulable