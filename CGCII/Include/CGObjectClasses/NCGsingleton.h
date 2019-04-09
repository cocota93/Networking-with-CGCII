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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		NCGSingleton
 @brief		��ü �ν��Ͻ��� �ϳ��� �����ϴ� Ŭ����
 @todo		
 @ref		
 @details	\n
 GetInstance()�Լ��� ���� static������ Instance������ �����ϵ��� �ߴ�.
 ������ ������ ���ؼ� �̷��� ���۵Ǿ���.
 Thread-Safe�� Singleton�� ������ ���� InitInstance���� DCL(Double Check Locking) ���·� �����ǵ��� �Ͽ���.

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
	//! @brief '�̱��� ��ü'�� ��´�. ���� ���� �� '�̱��� ��ü'�� �ʱ�ȭ�Ѵ�.
	static	CGPTR<TINSTANCE>	GetInstance();
	//! @brief '�̱��� ��ü'�� �����Ѵ�. @param _pInstance ������ '�̱��� ��ü'
	static	void				SetInstance(TINSTANCE* _pInstance);
	//! @brief '�̱��� ��ü'�� �ʱ�ȭ�Ѵ�.
	static	void				ResetInstance();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// Static)
	//! @brief '�̱��� ��ü'�� �ʱ�ȭ�Ѵ�.
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
	// Check) ���� �����Ǿ� ���� ������ ���� �����Ѵ�.
	if(m_pInstance.empty())
	{
		InitInstance();
	}

	// Return) ���� Instance�� �����Ѵ�.
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

	// 1) ���� �����ϰ� Default Logger�� Reset�Ѵ�.
	LOCK(g_csDefaultLogger)
	{
		// 1) ���� ����
		pinstance	 = m_pInstance;

		// 2) Instance�� Reset�Ѵ�.
		m_pInstance.reset();
	}

	// 3) ���⼭ Reset�Ѵ�.(Deadlock�� ���ϱ� ���� ��ġ)
	pinstance.reset();
}

template <class TINSTANCE, class TCREATE>
inline void	NCGSingleton<TINSTANCE, TCREATE>::InitInstance()							
{
	LOCK(m_csCreate)
	{
		// 1) Instance�� ��´�.
		// Check) �̹� �����Ǿ� ������ �׳� ������.
		RETURN_IF(m_pInstance.exist(),);

		// 2) �űԷ� �����Ѵ�.
		m_pInstance	 = _CGNEW_RAW<TINSTANCE>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL);
	}
}
