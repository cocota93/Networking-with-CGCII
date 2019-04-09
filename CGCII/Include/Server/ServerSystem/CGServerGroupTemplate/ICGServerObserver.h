//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                         Socket template Classes                           *
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

 @class		CArray
 @brief		�������� ������ �ֱ� ���� �������̽� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ���� ���´� �׷�� �����ϴ� �ٸ� �׷�� �ٸ��� ��Ÿ������ �������� �ʴ´�.
 �� �������� ���ÿ� ���� ��ü�� �������Ҽ� �ִ�.
       
*///-----------------------------------------------------------------------------
template <class _TOBSERVER>
class ICGServerObservers :
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (I) Reference Counter.
{
// ****************************************************************************
// Declare) Member�� Type
// ----------------------------------------------------------------------------
public:
	typedef	_TOBSERVER			TOBSERVER;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGServerObservers()										{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief '������ ��ü'�� ����Ѵ�. @param _pObserver ����� '������ ��ü' @return eOBJECT_RESULT::SUCCESS ���� @return !eOBJECT_RESULT::SUCCESS ����
	virtual	eOBJECT_RESULT		RegisterObserver(TOBSERVER* _pObserver) PURE;
	//! @brief ��ϵ� '������ ��ü'�� �����Ѵ�. @param _pObserver ��� ������ '������ ��ü' @return true ���� @return false ����
	virtual	bool				UnregisterObserver(TOBSERVER* _pObserver) PURE;
	//! @brief ��� '������ ��ü'�� ��� �����Ѵ�.
	virtual	void				UnregisterAllObserver() PURE;
};
