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
namespace CGAPI
{
// Definitions) 
class CThread;

//-----------------------------------------------------------------------------
/**

 @class		ManagerThread
 @brief		Thread를 관리하는 관리 클래스이다.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
class ManagerThread :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNameable::NString,					// (@) Nameable
	virtual public				NCGDispatchable,						// (@) Dispatchable List
	virtual public				ICGDestroyable,							//     Distroyable
	virtual public				ICGSchedulable							//     Schedulable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
		typedef vector<CGAPI::CThread*>		TCONTAINER;
		typedef	TCONTAINER::iterator		ITERATOR;
		typedef	TCONTAINER::const_iterator	CONST_ITERATOR;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ManagerThread();
	virtual ~ManagerThread();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 파괴한다. @return true 성공 @return false 실패
	virtual	bool				Destroy() override;

	//! @brief 데드락 감시를 시작한다. @param _tickValue '한계 대기 시간'
			void				StartDeadlockObserving(_In_ TICK::duration _tickValue=TICK::seconds(2));
	//! @brief 데드락 감시를 중단한다.
			void				StopDeadlockObserving();
	//! @brief 데드락 쓰레드가 존재하는지 확인하고 처리한다.
			void				CheckDeadlock();

	//! @brief 데드락 '한계 대기 시간'을 얻는다. @return 설정된 '한계 대기 시간'
			TICK::duration		GetDeadlockThreshold() const			{	return m_tickdiffDeadlockThreshold;}
	//! @brief 데드락 '한계 대기 시간'을 설정한다. @param _tick 설정할 '한계 대기 시간'
			void				SetDeadlockThreshold(_In_ TICK::duration _tick){	m_tickdiffDeadlockThreshold=_tick;}

	//! @brief '데드락 감시 간격'을 얻는다. @return 설정된 '데드락 감시 간격'
			TICK::duration		GetObservingInterval() const			{	return m_tickdifferObserving;}
	//! @brief '데드락 감시 간격'을 설정한다. @param _tick 설정할 '데드락 감시 간격'
			void				SetObservingInterval(_In_ TICK::duration _tick){	m_tickdifferObserving=_tick;}

	//! @brief 현재 쓰레드 갯수를 얻는다. @return 현재 쓰레드 수
			size_t				GetCount() const;
	//! @brief 제일 앞 쓰레드 객체를 얻는다. @return 제일 앞 쓰레드 객체
			ITERATOR			begin()									{	return m_listThread.begin();}
	//! @brief 제일 뒤 쓰레드 객체를 얻는다. @return 제일 뒤 쓰레드 객체
			ITERATOR			end()									{	return m_listThread.end();}

	//! @brief 락 객체를 얻는다.
								operator lockable&()					{	return m_listThread;}

	//! @brief '쓰레드 관리자 싱글턴 객체'를 얻는다. @return '기본 실행자'
	static	CGPTR<ManagerThread> GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '쓰레드 관리자 싱글턴 객체'를 설정한다.
	static	void				SetInstance(_In_ ManagerThread* _pInstance);
	//! @brief '쓰레드 관리자 싱글턴 객체'를 리셋한다.
	static	void				ResetInstance();

	//! @brief '기본 쓰레드 객체'를 얻는다. @return 기본 쓰레드 객체
	static	CGPTR<CThread>		GetDefaultThreadObject()				{	return GetInstance()->m_pThreadDefault;}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
private:
	//! @brief 쓰레드 객체를 등록한다. @return true 성공 @return false 실패
			bool				RegisterThread(_In_ CGAPI::CThread* _pThread);
	//! @brief 쓰레드 객체를 등록해제한다. @return true 성공 @return false 실패
			bool				UnregisterThread(_In_ CGAPI::CThread* _pThread);

	//! @brief 쓰레드가 등록될 때 호출되는 함수
	virtual	void				ProcessOnRegister()						{}
	//! @brief 쓰레드가 등록해제될 때 호출되는 함수
	virtual	void				ProcessOnUnregister()					{}
	//! @brief 스케쥴 처리하는 함수
	virtual	void				ProcessSchedule();

private:
	// 1) Pool List.
			LOCKABLE<TCONTAINER> m_listThread;

	// 2) Default Thread Object
			CGPTR<CGAPI::CThread> m_pThreadDefault;

	// 3) Observing
			TICK::time_point	m_tickObservingLast;
			TICK::duration		m_tickdifferObserving;
			TICK::duration		m_tickdiffDeadlockThreshold;
			ATOMIC<int>			m_bObservingDeadlock;

	// 4) Instance
	static	CGOWN<ManagerThread> m_pInstance;
	static	LOCKABLE<>			m_csCreate;
	static	void				InitInstance();

	// Friend) 
	friend	CGAPI::CThread;
};


}