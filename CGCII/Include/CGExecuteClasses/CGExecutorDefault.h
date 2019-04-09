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

#define	CGEXECUTOR_AUTO		(-1)
#define	CGEXECUTOR_NOTHREAD	0

namespace CGExecutor
{

//-----------------------------------------------------------------------------
/**

 @class		Default
 @brief		���������� �ڵ� �����Ǵ� �⺻ Executor�̴�.
 @todo		
 @ref		
 @details	\n
 ���������� ���Ǵ� ��� ����ó���� ���Ǵ� �̱��� Executor�̴�.
 ���������� ���� ������ Executor�� SingleExecutor�� Scheduler�� ������ �ִ�.
 �⺻�����δ� �ڵ������ǳ� �ʱ�ȭ�� �ʿ��� ��� InitInstance()�� ȣ���� �ʱ�ȭ�� ���� �ִ�.
 �����û�� PostExecute(...)�Լ��� �����ϸ� RegisterSchedulable�� Scheudler�� ����� ���� �ִ�.
 �Ҹ�ó���� �ڵ����� �Ǳ� ������ �ٸ� ó���� ���� �ʿ䵵 ����.

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
	//! @brief '�⺻ ������'�� �̱��� ��ü�� �ʱ�ȭ�Ѵ�. @param _nT ������ ������ ���� CGEXECUTOR_AUTO(-1)�̸� �ھ� ������ ���� �ڵ� ���� �����ȴ�.
	static	void				InitInstance(_In_ int _nT=CGEXECUTOR_AUTO);
	//! @brief '�⺻ ������'�� �̱��� ��ü�� �ʱ�ȭ�Ѵ�. @param _nT ������ ������ ���� CGEXECUTOR_AUTO(-1)�̸� �ھ� ������ ���� �ڵ� ���� �����ȴ�.
	static	void				InitInstance(CGMSG_CONTEXT& _Msg);
	//! @brief '�⺻ ������'�� �ı��Ѵ�.
	static	void				DestroyInstance();

	// 2) Instance Get/Set/Reset
	//! @brief '�⺻ ������'�� �̱��� ��ü�� ��´�. @return '�⺻ ������'
	static	Default*			GetInstance()							{	if(m_Instance.m_pexecutorDefaultSingly.empty()) InitInstance(); return &m_Instance;}

	//! @brief ������ ������ ��´�. @return ������ ����
	static	int					GetThreadCount();
	//!	@brief ���μ��� ������ ��´�. @return ���μ��� ����
	static	int					GetProcessCount();

	// 3) Executor/Scheduler Get
	//! @brief '�⺻ ������'�� ��´�. @return '�⺻ ������' ������
	static	CGPTR<CCompletionPortThread> GetExecutor()					{	if(m_Instance.m_pexecutorDefault.empty()) InitInstance(); return m_Instance.m_pexecutorDefault;}
	//! @brief '�⺻ �����췯'�� ��´�. @return '�⺻ �����췯'
	static	CGPTR<CSchedulable>		GetScheduler()						{	if(m_Instance.m_pexecutorSchedulable.empty()) InitInstance(); return m_Instance.m_pexecutorSchedulable;}
	//! @brief �⺻ ���� ���� �����췯�� ��´�. @return '�⺻ ���� ���� �����췯'
	static	CGPTR<CSingleExecute>	GetSchedulerSingly()				{	if(m_Instance.m_pexecutorDefaultSingly.empty()) InitInstance(); return m_Instance.m_pexecutorDefaultSingly;}

	//! @brief '������'�� ��´�. @return '������'
			CGPTR<CCompletionPortThread> Executor()						{	return m_pexecutorDefault;}
	//! @brief '�����췯'�� ��´�. @return '�����췯'
			CGPTR<CSchedulable>		Scheduler()							{	return m_pexecutorSchedulable;}
	//! @brief '���� ���� �����췯'�� ��´�. @return '���� ���� �����췯'
			CGPTR<CSingleExecute>	SchedulerSingly()					{	return m_pexecutorDefaultSingly;}

	// 4) RunExecutor
	//! @brief '������'�� ���� �����Ų��. @details '������'�� �������� �����Ų��.
	static	void				RunExecutor();

	// 5) Factory Sustainer
	//! @brief 'Ǯ ������'�� �����Ų��. @return true ���� @return false ����
	static	bool				StartFactoryGarbageCollection();
	//! @brief 'Ǯ ������'�� ������Ų��. @return true ���� @return false ����
	static	bool				StopFactoryGarbageCollection();

	// 6) Exception Observer
	//! @brief '���� ������'�� �����Ų��. @return true ���� @return false ����
	static	bool				StartExceptionObserving();
	//! @brief '���� ������'�� ������Ų��. @return true ���� @return false ����
	static	bool				StopExceptionObserving();

	// 7) Post Execute
	//!	@brief '���� ��ü'�� ������ ��û�Ѵ�. @param _pExecutable ������ '���� ��ü' @return true ���� @return false ����
	template <class TEXECUTABLE>
	static	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ const CGPTR<TEXECUTABLE>& _pExecutable)	{	return PostExecute(_pExecutable.get());}
	//! @brief ������ �ð��� '���� ��ü'�� ���� ��û�Ѵ�. @param _tickTime ������ �ð� @param _pExecutable ������ '���� ��ü' @return true ���� @return false ����
	template <class TEXECUTABLE>
	static	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ const CGPTR<TEXECUTABLE>& _pExecutable) { return PostExecute(_tickTime, _pExecutable.get());}
	//!	@brief '���� ��ü'�� ������ ��û�Ѵ�. @param _pExecutable ������ '���� ��ü' @return true ���� @return false ����
	template <class TEXECUTABLE>
	static	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ TEXECUTABLE* _pExecutable)			{	return GetExecutor()->PostExecute(_pExecutable);}
	//! @brief ������ �ð��� '���� ��ü'�� ���� ��û�Ѵ�. @param _tickTime ������ �ð� @param _pExecutable ������ '���� ��ü' @return true ���� @return false ����
	template <class TEXECUTABLE>
	static	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ TEXECUTABLE* _pExecutable) {	return GetSchedulerSingly()->PostExecuteAt(_tickTime, _pExecutable);}

	//!	@brief ���� �Լ��� ������ ��û�Ѵ�. @param _pExecutable ������ �����Լ� @return true ���� @return false ����
	template <class TFUNCTION>
	static	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TFUNCTION _fFunction);


	//! @brief ������ �ð��� ���� �Լ��� ���� ��û�Ѵ�. @param _tickTime ������ �ð� @param _pExecutable ������ �����Լ� @return true ���� @return false ����
	template <class TFUNCTION>
	static	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ TFUNCTION _fFunction);
	//! @brief �Լ��� ���� ��û�Ѵ�. @param _pExecutable ������ �Լ� @return true ���� @return false ����
	template <class TFUNCTION>
	static	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TFUNCTION _fFunction);
	//! @brief ������ �ð��� �Լ��� ���� ��û�Ѵ�. @param _tickTime ������ �ð� @param _pExecutable ������ �Լ� @return true ���� @return false ����
	template <class TFUNCTION>
	static	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ TFUNCTION _fFunction);


	//! @brief ��� �Լ��� ���� ��û�Ѵ�. @param _Object ��� ��ü @param _pMemberFunction ������ ��� �Լ� @return true ���� @return false ����
	template <class TOBJECT>
	static	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)());
	//! @brief ��� �Լ��� ���� ��û�Ѵ�. @param _Object ��� ��ü @param _pMemberFunction ������ ��� �Լ� @return true ���� @return false ����
	template <class TOBJECT>
	static	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)());
	//! @brief ������ �ð��� ��� �Լ��� ������ ��û�Ѵ�. @param _tickTime ������ �ð� @param _Object ��� ��ü @param _pMemberFunction ������ ��� �Լ� @return true ���� @return false ����
	template <class TOBJECT>
	static	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)());
	//! @brief ������ �ð��� ��� �Լ��� ������ ��û�Ѵ�. @param _tickTime ������ �ð� @param _Object ��� ��ü @param _pMemberFunction ������ ��� �Լ� @return true ���� @return false ����
	template <class TOBJECT>
	static	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ TICK::time_point _tickTime, _In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)());

	// 8) Schedulable 
	//! @brief '������ ��ü'�� '�⺻ �����췯'�� ����Ѵ�. @param _pSchedulable ����� '������ ��ü' @return true ���� @return false ����
	static	bool				RegisterSchedulable(_In_ ICGSchedulable* _pSchedulable);
	//! @brief ��ϵ� '������ ��ü'�� '�⺻ �����췯'���� �����Ѵ�. @param _pSchedulable ��������� '������ ��ü' @return true ���� @return false ����
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
// 1. PostExecute��...
//    lambda�Լ��� �񵿱������� �����ϰ� ���� �� CGExecutable::CFunction�� ����Ͽ�
//    Executor�� �ɾ��־�� �Ѵ�. �̷� ���ŷ����� �����ֱ� ���� �� ������ �̸�
//    ������ ���� �Լ��̴�.
//
//-----------------------------------------------------------------------------
// For Lambda Function) 
template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
Default::PostExecute(_In_ TFUNCTION _fFunction)
{
	// 1) Lambda�� Executable�� �Ҵ�޴´�.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute�Լ��� �����Ѵ�.
	pExecutable->SetFunction(_fFunction);

	// 3) Post�Ѵ�.
	return GetSchedulerSingly()->PostExecute(pExecutable);
}

template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
Default::PostExecute(_In_ TICK::time_point _tickTime, _In_ TFUNCTION _fFunction)
{
	// 1) Lambda�� Executable�� �Ҵ�޴´�.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute�Լ��� �����Ѵ�.
	pExecutable->SetFunction(_fFunction);

	// 3) Post�Ѵ�.
	return GetSchedulerSingly()->PostExecuteAt(_tickTime, pExecutable);
}


// For Function) 
template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
Default::PostExecute(_In_ TFUNCTION _fFunction)
{
	// 1) Lambda�� Executable�� �Ҵ�޴´�.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute�Լ��� �����Ѵ�.
	pExecutable->SetFunction(_fFunction);

	// 3) Post�Ѵ�.
	return GetSchedulerSingly()->PostExecute(pExecutable);
}

template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
Default::PostExecute(_In_ TICK::time_point _tickTime, _In_ TFUNCTION _fFunction)
{
	// 1) Lambda�� Executable�� �Ҵ�޴´�.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute�Լ��� �����Ѵ�.
	pExecutable->SetFunction(_fFunction);

	// 3) Post�Ѵ�.
	return GetSchedulerSingly()->PostExecuteAt(_tickTime, pExecutable);
}


// For Member Function) 
template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
Default::PostExecute(_In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)())
{
	// 1) Member�Լ� Function�� Executable�� �Ҵ�޴´�.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute �Լ��� Object���� �����Ѵ�.
	pExecutable->SetObject(_Object);
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post�Ѵ�.
	return GetExecutor()->PostExecute(pExecutable);
}

template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
Default::PostExecute(_In_ TICK::time_point _tickTime, _In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)())
{
	// 1) Member�Լ� Function�� Executable�� �Ҵ�޴´�.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute �Լ��� Object���� �����Ѵ�.
	pExecutable->SetObject(_Object);
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post�Ѵ�.
	return GetSchedulerSingly()->PostExecuteAt(_tickTime, pExecutable);
}

template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
Default::PostExecute(_In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)())
{
	// 1) Member�Լ� Function�� Executable�� �Ҵ�޴´�.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute �Լ��� Object���� �����Ѵ�.
	pExecutable->SetObject(_Object.get());
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post�Ѵ�.
	return GetExecutor()->PostExecute(pExecutable);
}

template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
Default::PostExecute(_In_ TICK::time_point _tickTime, _In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)())
{
	// 1) Member�Լ� Function�� Executable�� �Ҵ�޴´�.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute �Լ��� Object���� �����Ѵ�.
	pExecutable->SetObject(_Object.get());
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post�Ѵ�.
	return GetSchedulerSingly()->PostExecuteAt(_tickTime, pExecutable);
}


}

#define	POST_EXECUTE			CGExecutor::Default::PostExecute
#define	REGISTER_SCHEDULABLE	CGExecutor::Default::RegisterSchedulable
#define	UNREGISTER_SCHEDULABLE	CGExecutor::Default::UnregisterSchedulable