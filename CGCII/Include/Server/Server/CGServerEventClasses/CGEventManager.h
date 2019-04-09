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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
// 1. Event System�̶�?
//
//    1) ���� System�� �����ϴٺ��� �����ð����� ������ �ϰų� Ư���� �ð��� ����
//       �ؾ��ϴ� �͵��� ������ �ʿ䰡 �ִ�.
//       �̶� Ư���� �ð��̳�  Ư���� �ð����� �����ϵ��� �ϴ� �ý����� Event �ý����̴�.
//
//    2) Event System�� Event Object�� Event Manager�� ����������.
//       - Event Manager�� ��ϵ� EventObject�� ����Ͽ��ٰ� ������ �ð����� �������ִ�
//         �����ڸ� �ǹ��Ѵ�.
//       - Event Object�� Event Manager�� ��ϵǾ� �����ϴ� ��ü�� �ʿ信 ����
//         �پ��� �������·� ���۵Ǿ��� �ִ�. 
//         ����� Event Object�� �Ʒ��� ���� �͵��� �ִ�.
//
//         @ CGEvent::Object::COnce
//           ����� �ð��� �� 1ȸ�� ����Ǵ� ��ü
//
//         @ CGEvent::Object::CStartEnd
//           ����� ���۽ð��� ����ð��� ���� ������ �Լ��� ȣ���ϴ� ��ü
//
//         @ CGEvent::Object::CStartIterationEnd
//           ����� ���۽ð��� ������ �Լ��� ȣ��Ǹ� ���Ŀ� ������ ���ݿ� ����
//           ������ �Լ��� ������ ����Ƚ����ŭ ȣ�����ִ� Event ��ü�̴�.
//           ����Ƚ����ŭ ȣ��� �� ProcessEventEnd()�Լ��� ȣ��ȴ�.
//
//         @ CCGEventIteration
//           ������ �ð� ���� ���� ������ �Լ��� ���ѹݺ������� �������ϴ�
//           Event��ü�̴�.
//
//    3) �� Event��ü���� Ư���� �ð��� ȣ��Ǿ����� virtual�Լ����� ���ǵǾ� �ִ�.
//       �� virtual�Լ��� �������Ͽ� �����ϰ����ϴ� ������ �ۼ��ϸ� �ȴ�.
//
//    4) Event��ü�� ���е��� �ʴ��� ���ظ��� �����ϹǷ� ���� ������ ������ �ʿ���
//       ��� Executable�̳� �ٸ� ����� ����ϱ⸦ �����Ѵ�.
//
//    5) Event System������ �ð��� ��� System Time�� ����ϰ� �ִ�. System Time��
//       Local Time�� �������� �ʱ� ������ ���� ���� �ð����� �ٸ� �� �����Ƿ� 
//       ������ �Ҷ��� �ݵ�� System Time���� ������ �ʿ䰡 �ִ�.
//
//
// 2. �ֿ��Լ�.
//    1) RegisterEvent()/UnregisterEvent()/UnregisterEventAll()
//       ���� Event ��ü�� ����ϰų� ��������ϰų� Ȥ�� ��� Event Object�� ���
//       �����ϴ� �Լ��̴�.
//       (*�Ϲ������� �� �Լ��� ���������� �ʰ� IEventObject�� Register(), Unregister()
//         �Լ��� �� ���� ����Ѵ�.)
//
//    2) begin()/end()
//       - Manager�� ��ϵ� ��� Event��ü�� ����� �� �� ����ϴ� �Լ��̴�.
//       - �̶� �����ؾ��ϴ� ���� ������ ������ ���� �ݵ�� Lock�� �� ���Ŀ� 
//         begin()�Լ��� ȣ���Ͽ� Event Object�� �����϶�� ���̴�.
//
//    3) Delete Done Event Option
//       - �Ϸᰡ �� Event Object�� ������ ���ΰ� �״�� ���ܵ� ���ΰ��� �����ϴ�
//         �ɼ��̴�.
//       - SetDeleteDoneEvent()�Լ��� ����� ������ �� �ִ�. true�� ������ ���
//         �Ϸ�� Event��ü�� List���� �ڵ����� �����ϰ� �ȴ�.
//       - �⺻ ����ġ�� true�̴�.
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
	// 1) Iterator��.
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
	//! @brief �ʱ�ȭ�Ǳ� �� ȣ��ȴ�.(OnDestroy()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnInitializing(CGMSG_CONTEXT& _Msg);
	//! @brief �ʱ�ȭ�� �� ȣ��ȴ�.(OnDestroying()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnInitialize(CGMSG_CONTEXT& _Msg);

	//! @brief �ı��Ǳ� �� ȣ��ȴ�.(OnInitialize()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnDestroying();
	//! @brief �ı��� �� ȣ��ȴ�.(OnInitializing()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnDestroy();

	//! @brief �ʱ�ȭ�Ǳ� �� ȣ��ȴ�.(OnDestroy()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStarting(CGMSG_CONTEXT& _Msg);
	//! @brief �ʱ�ȭ�� �� ȣ��ȴ�.(OnDestroying()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStart(CGMSG_CONTEXT& _Msg);

	//! @brief �ı��Ǳ� �� ȣ��ȴ�.(OnInitialize()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStopping();
	//! @brief �ı��� �� ȣ��ȴ�.(OnInitializing()�Լ��� ¦�Լ���.) @param _Msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				OnStop();


	virtual	bool				OnRegisterEvent(_In_ ICGEventObject* _pEvent);
	virtual	bool				OnUnregisterEvent(_In_ ICGEventObject* _pEvent);
	virtual	bool				OnCompleteEvent(_In_ ICGEventObject* _pEvent);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Execute�Լ���...
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