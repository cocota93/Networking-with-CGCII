//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Event Classes                            *
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
// ----------------------------------------------------------------------------
// 1. Event System이란?
//
//    1) 각종 System을 제작하다보면 일정시간마다 실행을 하거나 특정한 시간에 실행
//       해야하는 것들을 설정할 필요가 있다.
//       이때 특정한 시간이나  특정한 시간마다 실행하도록 하는 시스템이 Event 시스템이다.
//
//    2) Event System은 Event Object와 Event Manager로 나뉘어진다.
//       - Event Manager는 등록된 EventObject를 등록하였다가 정해진 시간마다 실행해주는
//         관리자를 의미한다.
//       - Event Object는 Event Manager에 등록되어 동작하는 객체로 필요에 따라
//         다양한 실행형태로 제작되어져 있다. 
//         선언된 Event Object는 아래와 같은 것들이 있다.
//
//         @ CGEvent::Object::COnce
//           예약된 시간에 딱 1회만 실행되는 객체
//
//         @ CGEvent::Object::CStartEnd
//           예약된 시작시간과 종료시간에 각각 정해진 함수를 호출하는 객체
//
//         @ CGEvent::Object::CStartIterationEnd
//           예약된 시작시간에 정해진 함수가 호출되며 이후에 정해진 간격에 따라
//           정해진 함수를 정해진 실행횟수만큼 호출해주는 Event 객체이다.
//           실행횟수만큼 호출된 후 ProcessEventEnd()함수가 호출된다.
//
//         @ CCGEventIteration
//           정해진 시간 간격 마다 정해진 함수를 무한반복적으로 실행해하는
//           Event객체이다.
//
//    3) 각 Event객체들은 특정한 시간에 호출되어지는 virtual함수들이 정의되어 있다.
//       이 virtual함수를 재정의하여 실행하고자하는 내용을 작성하면 된다.
//
//    4) Event객체의 정밀도는 초단위 수준만을 보장하므로 더욱 정밀한 실행이 필요할
//       경우 Executable이나 다른 방법을 사용하기를 권장한다.
//
//    5) Event System에서의 시간은 모두 System Time을 사용하고 있다. System Time은
//       Local Time과 동일하지 않기 때문에 실제 지역 시간과는 다를 수 있으므로 
//       설정을 할때는 반드시 System Time으로 설정할 필요가 있다.
//
//
// 2. 주요함수.
//    1) RegisterEvent()/UnregisterEvent()/UnregisterEventAll()
//       각각 Event 객체를 등록하거나 등록해제하거나 혹은 모든 Event Object를 등록
//       해제하는 함수이다.
//       (*일반적으로 이 함수를 직접쓰지는 않고 IEventObject의 Register(), Unregister()
//         함수를 더 많이 사용한다.)
//
//    2) begin()/end()
//       - Manager에 등록된 모든 Event객체를 얻고자 할 때 사용하는 함수이다.
//       - 이때 주의해야하는 것은 안전한 실행을 위해 반드시 Lock을 건 이후에 
//         begin()함수를 호출하여 Event Object에 접근하라는 것이다.
//
//    3) Delete Done Event Option
//       - 완료가 된 Event Object를 제거할 것인가 그대로 남겨둘 것인가를 설정하는
//         옵션이다.
//       - SetDeleteDoneEvent()함수를 사용해 설정할 수 있다. true로 설정할 경우
//         완료된 Event객체는 List에서 자동으로 제거하게 된다.
//       - 기본 설정치는 true이다.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{

class Manager : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGSchedulable::NExecutable,
	public						CGNameable::NString,
	public						NCGObjectState,
	public						NCGStartable,
	public						NCGInitializable,
	virtual public				NCGDispatchable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
			typedef	std::set<CGPTR<ICGEventObject> >::iterator			ITERATOR;
			typedef	std::set<CGPTR<ICGEventObject> >::const_iterator	CONST_ITERATOR;


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
			ITERATOR			begin()									{	return m_setEvent.begin();}
			ITERATOR			end()									{	return m_setEvent.end();}
			int					GetCount()								{	return (int)m_setEvent.size();}
								operator CGD::lockable&()				{	return m_setEvent;}

	// 2) Add/Remove
			bool				RegisterEvent(_In_ ICGEventObject* _pEvent);
			bool				UnregisterEvent(_In_ ICGEventObject* _pEvent);
			CGPTR<ICGEventObject> UnregisterEvent(_In_ int64_t _idEvent);
			void				UnregisterEventAll();
			CGPTR<ICGEventObject> FindEvent(_In_ int64_t _idEvent);
			
	// 3) Flags
			void				SetDeleteDoneEvent(_In_ bool p_bStatus = true)	{ m_bDeleteDoneEvent = p_bStatus; }
			void				EnableDeleteDoneEvent()					{	m_bDeleteDoneEvent=true;}
			void				DisableDeleteDoneEvent()				{	m_bDeleteDoneEvent=false;}
			bool				IsDeleteDoneEvent() const				{	return m_bDeleteDoneEvent;}

	// 4) Init Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	static	void				SetInstance(_In_ Manager* p_pInstance);
	static	void				ResetInstance();


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
protected:
	//! @brief 초기화되기 전 호출된다.(OnDestroy()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnInitializing(CGMSG_CONTEXT& _Msg);
	//! @brief 초기화될 때 호출된다.(OnDestroying()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnInitialize(CGMSG_CONTEXT& _Msg);

	//! @brief 파괴되기 전 호출된다.(OnInitialize()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnDestroying();
	//! @brief 파괴될 때 호출된다.(OnInitializing()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnDestroy();

	//! @brief 초기화되기 전 호출된다.(OnDestroy()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStarting(CGMSG_CONTEXT& _Msg);
	//! @brief 초기화될 때 호출된다.(OnDestroying()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStart(CGMSG_CONTEXT& _Msg);

	//! @brief 파괴되기 전 호출된다.(OnInitialize()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStopping();
	//! @brief 파괴될 때 호출된다.(OnInitializing()함수와 짝함수다.) @param _Msg 초기화 할때 전달될 메시지
	virtual	void				OnStop();


	virtual	bool				OnRegisterEvent(_In_ ICGEventObject* _pEvent);
	virtual	bool				OnUnregisterEvent(_In_ ICGEventObject* _pEvent);
	virtual	bool				OnCompleteEvent(_In_ ICGEventObject* _pEvent);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Execute함수임...
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;

public:
	// 1) Executor/Notifier
			CGPTR<CGExecutor::CCompletionPort>	m_pExecutor;
			CGPTR<CGExecutor::CSchedulable>		m_pSchedulable;

	// 2) List Event
			LOCKABLE<std::set<CGPTR<ICGEventObject>>>	m_setEvent;

	// 3) flags
			bool				m_bDeleteDoneEvent;

	// 4) Instance
	static	CGOWN<Manager>		m_pInstance;
	static	LOCKABLE<>			m_csCreate;
	static	void				InitInstance();
public:
};


}