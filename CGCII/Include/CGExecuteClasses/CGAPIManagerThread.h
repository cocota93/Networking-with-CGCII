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
namespace CGAPI
{
// Definitions) 
class CThread;

//-----------------------------------------------------------------------------
/**

 @class		ManagerThread
 @brief		Thread�� �����ϴ� ���� Ŭ�����̴�.
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
	//! @brief �ı��Ѵ�. @return true ���� @return false ����
	virtual	bool				Destroy() override;

	//! @brief ����� ���ø� �����Ѵ�. @param _tickValue '�Ѱ� ��� �ð�'
			void				StartDeadlockObserving(_In_ TICK::duration _tickValue=TICK::seconds(2));
	//! @brief ����� ���ø� �ߴ��Ѵ�.
			void				StopDeadlockObserving();
	//! @brief ����� �����尡 �����ϴ��� Ȯ���ϰ� ó���Ѵ�.
			void				CheckDeadlock();

	//! @brief ����� '�Ѱ� ��� �ð�'�� ��´�. @return ������ '�Ѱ� ��� �ð�'
			TICK::duration		GetDeadlockThreshold() const			{	return m_tickdiffDeadlockThreshold;}
	//! @brief ����� '�Ѱ� ��� �ð�'�� �����Ѵ�. @param _tick ������ '�Ѱ� ��� �ð�'
			void				SetDeadlockThreshold(_In_ TICK::duration _tick){	m_tickdiffDeadlockThreshold=_tick;}

	//! @brief '����� ���� ����'�� ��´�. @return ������ '����� ���� ����'
			TICK::duration		GetObservingInterval() const			{	return m_tickdifferObserving;}
	//! @brief '����� ���� ����'�� �����Ѵ�. @param _tick ������ '����� ���� ����'
			void				SetObservingInterval(_In_ TICK::duration _tick){	m_tickdifferObserving=_tick;}

	//! @brief ���� ������ ������ ��´�. @return ���� ������ ��
			size_t				GetCount() const;
	//! @brief ���� �� ������ ��ü�� ��´�. @return ���� �� ������ ��ü
			ITERATOR			begin()									{	return m_listThread.begin();}
	//! @brief ���� �� ������ ��ü�� ��´�. @return ���� �� ������ ��ü
			ITERATOR			end()									{	return m_listThread.end();}

	//! @brief �� ��ü�� ��´�.
								operator lockable&()					{	return m_listThread;}

	//! @brief '������ ������ �̱��� ��ü'�� ��´�. @return '�⺻ ������'
	static	CGPTR<ManagerThread> GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '������ ������ �̱��� ��ü'�� �����Ѵ�.
	static	void				SetInstance(_In_ ManagerThread* _pInstance);
	//! @brief '������ ������ �̱��� ��ü'�� �����Ѵ�.
	static	void				ResetInstance();

	//! @brief '�⺻ ������ ��ü'�� ��´�. @return �⺻ ������ ��ü
	static	CGPTR<CThread>		GetDefaultThreadObject()				{	return GetInstance()->m_pThreadDefault;}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
private:
	//! @brief ������ ��ü�� ����Ѵ�. @return true ���� @return false ����
			bool				RegisterThread(_In_ CGAPI::CThread* _pThread);
	//! @brief ������ ��ü�� ��������Ѵ�. @return true ���� @return false ����
			bool				UnregisterThread(_In_ CGAPI::CThread* _pThread);

	//! @brief �����尡 ��ϵ� �� ȣ��Ǵ� �Լ�
	virtual	void				ProcessOnRegister()						{}
	//! @brief �����尡 ��������� �� ȣ��Ǵ� �Լ�
	virtual	void				ProcessOnUnregister()					{}
	//! @brief ������ ó���ϴ� �Լ�
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