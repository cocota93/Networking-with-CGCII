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

 @class		NCGSingleton
 @brief		객체 인스턴스를 하나만 생성하는 클래스
 @todo		
 @ref		
 @details	\n
 GetInstance()함수에 지역 static변수로 Instance변수를 설정하도록 했다.
 사용시점 생성을 위해서 이렇게 제작되었다.
 Thread-Safe한 Singleton을 구현을 위해 InitInstance에서 DCL(Double Check Locking) 형태로 구현되도록 하였다.

*/
//-----------------------------------------------------------------------------
template <class TINSTANCE, class TCREATE=CGPTR<TINSTANCE>>
class NCGSingleton : virtual public ICGReferenceable
{
// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Get Instance
	//! @brief '싱글턴 객체'를 얻는다. 최초 실행 시 '싱글턴 객체'가 초기화한다.
	static	CGPTR<TINSTANCE>	GetInstance();
	//! @brief '싱글턴 객체'를 설정한다. @param _pInstance 설정할 '싱글턴 객체'
	static	void				SetInstance(TINSTANCE* _pInstance);
	//! @brief '싱글턴 객체'를 초기화한다.
	static	void				ResetInstance();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// Static)
	//! @brief '싱글턴 객체'를 초기화한다.
	static	void				InitInstance();

	static	LOCKABLE<>			m_csCreate;
	static	TCREATE				m_pInstance;
};

template <class TINSTANCE, class TCREATE>
LOCKABLE<> NCGSingleton<TINSTANCE, TCREATE>::m_csCreate;

template <class TINSTANCE, class TCREATE>
TCREATE NCGSingleton<TINSTANCE, TCREATE>::m_pInstance;

template <class TINSTANCE, class TCREATE>
inline CGPTR<TINSTANCE>	NCGSingleton<TINSTANCE, TCREATE>::GetInstance()							
{
	// Check) 만약 생성되어 있지 않으면 새로 생성한다.
	if(m_pInstance.empty())
	{
		InitInstance();
	}

	// Return) 얻은 Instance를 리턴한다.
	return m_pInstance;
}

template <class TINSTANCE, class TCREATE>
void NCGSingleton<TINSTANCE, TCREATE>::SetInstance(TINSTANCE* _pInstance)
{
	LOCK(m_csCreate)
	{
		m_pInstance	 = _pInstance;
	}
}

template <class TINSTANCE, class TCREATE>
void NCGSingleton<TINSTANCE, TCREATE>::ResetInstance()
{
	// Declare) 
	NCGSingleton<TINSTANCE, TCREATE>	pinstance;

	// 1) 먼저 복사하고 Default Logger를 Reset한다.
	LOCK(g_csDefaultLogger)
	{
		// 1) 먼저 복사
		pinstance	 = m_pInstance;

		// 2) Instance를 Reset한다.
		m_pInstance.reset();
	}

	// 3) 여기서 Reset한다.(Deadlock을 피하기 위한 조치)
	pinstance.reset();
}

template <class TINSTANCE, class TCREATE>
inline void	NCGSingleton<TINSTANCE, TCREATE>::InitInstance()							
{
	LOCK(m_csCreate)
	{
		// 1) Instance를 얻는다.
		// Check) 이미 생성되어 있으면 그냥 끝낸다.
		RETURN_IF(m_pInstance.exist(),);

		// 2) 신규로 생성한다.
		m_pInstance	 = _CGNEW_RAW<TINSTANCE>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL);
	}
}
