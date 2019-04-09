//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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

 @class		ICGReferenceable
 @brief		참조계수 속성의 인터페이스 클래스
 @todo		
 @ref		CGPTR, CGOBJ
 @details	\n
 참조계수 속성을 가지는 인터페이스 클래스로 내부적으로  참조계수를 가지고 있다.
 이 참조계수는 처음 생성될때는 0으로 초기화 되며
 AddReference()함수를 호출하면 참조계수 1이 증가하게 된다.
 Release()함수를 호출하면 참조계수 1이 감소하게 된다.
 또 참조계수가 0이 되면 OnFinalRelease/ProcessDispose함수를 호출해준다.
 OnFinalRelease()함수를 재정의하면 참조계수가 0이 되었을 때 동작을 정의해 줄수 있다.
 이때 참조계수 증감은 쓰레드에 안전하게 동작한다.

 일반적으로 ICGReferenceable는 동적할당된 객체의 자동할당해제를 위해 사용된다.

*/
//-----------------------------------------------------------------------------
class ICGDisposable
{
protected:
	virtual	void				ProcessDispose() PURE;
};

class ICGReferenceable : virtual public ICGDisposable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			ICGReferenceable() : m_Counter(0), m_bDisuse(false) CGNEW_DEBUG_INFO_INITIALIZE {}
			ICGReferenceable(const ICGReferenceable&) : m_Counter(0), m_bDisuse(false) CGNEW_DEBUG_INFO_INITIALIZE {}
	virtual	~ICGReferenceable()											{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
#ifdef _DEBUG
	#define		DEBUG_ON_ADD_REFERENCECOUNT(count)	_Debug_OnAddReferenceCount(count)
	#define		DEBUG_ON_RELEASE_REFERENCECOUNT		_Debug_OnReleaseReferenceCount()
#else
	#define		DEBUG_ON_ADD_REFERENCECOUNT(count)	
	#define		DEBUG_ON_RELEASE_REFERENCECOUNT
#endif

public:
	//! @brief 참조계수를 0으로 설정한다.(OnFinalRelease/ProcessDispose함수는 호출되지 않는다.) 
			void				ResetReferenceCount()					{	m_Counter=0;}
	//! @brief 참조계수를 정해진 값으로 설정한다. @param _Count 변경할 참조계수 값
			void				SetReferenceCount(int _Count)			{	m_Counter=_Count;}

	//! @brief 참조계수를 1 증가시킨다. @return 변공된 참조계수 값
			int					AddRef()								{	DEBUG_ON_ADD_REFERENCECOUNT(1); return ++m_Counter;}
	//! @brief 참조계수를 _Count만큼 증가시킨다.(_Count값이 음수면 안됀다.) @param _Count 증가치 @return 증가시킨 이후 참조계수
			int					AddRef(int _Count)						{	DEBUG_ON_ADD_REFERENCECOUNT(_Count); CGASSERT_ERROR(_Count>=0); return m_Counter+=_Count;}

	//! @brief 참조계수를 1 감소시킨다. 참조계수가 0이 되면 OnFinalRelease/ProcessDispose를 호출한다. @return 감소시킨 후 참조계수
			int					Release()								{	DEBUG_ON_RELEASE_REFERENCECOUNT; int result=--m_Counter; CGASSERT_ERROR(result>=0); if(result==0) { OnFinalRelease(); CGNEW_DEBUG_INFO_RESET(this); ProcessDispose(); } return result;}

	//! @brief 현재 참조계수를 얻는다. @return 현재 참조계수
			int					GetReferenceCount() const				{	return m_Counter;}

	//! @brief 객체를 폐기하도록 설정한다. 풀에서 할당된 객체의 경우 Disuse로 설정되면 풀로 되돌아 가면 재사용하지 않고 바로 소멸시킨다. 
			void				SetAsDisuse()							{	m_bDisuse = true; }
			bool				IsDisuse() const						{	return m_bDisuse;}

	//! @brief 증가연산자: 참조계수를 1 증가시킨다.(AddRef와 동일하다.)
			ICGReferenceable&	operator++()							{	AddRef(); return *this;}
	//! @brief 감소연산자: 참조계수를 1 감소시킨다.(Release()와 동일하다.)
			ICGReferenceable&	operator--()							{	Release(); return *this;}
	//! @brief 더하기 연산자: 참조계수를 rhs만큼 증가시킨다. @param rhs 증가치
			void				operator+=(int rhs)						{	AddRef(rhs);}

	//! @brief 대입연산자
			ICGReferenceable&	operator=(const ICGReferenceable&)		{	return *this;}

	// Definitions) 기본 정의 Class
			class NoAct;
			class Delete;

	// Debug)
			CGNEW_DEBUG_INFO_DECLARE


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Release가 0이 되는 순간 Release를 위해 불려지는 함수.
	virtual	void				OnFinalRelease()						{}

	// Debug) Debug일 때만 호출되는 훅함수이다.
	//        - Reference Count가 어느 시점에서 증가되고 감소하는 지 확인하는 용도로 이 훅함수를 재정의할 수 있다.
	//        - Release에서 이 함수 자체가 호출되지 않는다.
	virtual	void				_Debug_OnAddReferenceCount(int /*_count*/){}
	virtual	void				_Debug_OnReleaseReferenceCount()		{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			ATOMIC<int>			m_Counter;
			bool				m_bDisuse;
};

// Releaser) 
class ICGReferenceable::NoAct : virtual public ICGDisposable
{
public: 
	virtual ~NoAct() 
	{
	}

	virtual void ProcessDispose() override 
	{
	}
};

class ICGReferenceable::Delete : virtual public ICGDisposable
{
public:
	virtual ~Delete() 
	{
	}

	virtual void ProcessDispose() override
	{
		delete this;
	}
};
