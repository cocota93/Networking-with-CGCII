//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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

 @class		NCGPausable
 @brief		ICGPausable�� ������ Ŭ����
 @todo		
 @ref		
 @details	\n

 */
//-----------------------------------------------------------------------------
class NCGPausable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGPausable,
	virtual	public				ICGObjectState
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief �����Ѵ�. @return true ���� @return false ����
	virtual	bool				Pause() override;
	//! @brief �簳�Ѵ�. @return true ���� @return false ����
	virtual	bool				Continue() override;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//! @brief ��� �ߴܵǱ� �� ȣ��ȴ�.(OnContinue()�Լ��� ¦�Լ���.)
	virtual	void				OnPausing()							{}
	//! @brief ��� �ߴܵ� �� ȣ��ȴ�.(OnContinuing()�Լ��� ¦�Լ���.)
	virtual	void				OnPause()							{}

	//! @brief �ٽ� ���� �Ǳ� ��ȣ��ȴ�.(OnDestroying()�Լ��� ¦�Լ���.)
	virtual	void				OnContinuing()						{}
	//! @brief �ٽý����� �� ȣ��ȴ�.(OnPausing()�Լ��� ¦�Լ���.)
	virtual	void				OnContinue()						{}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
public:
	//! @brief ��� ������ �� ó���ؾ��� ������ �����Ѵ�. @param _Msg ������ ����
	virtual	void				ProcessPause();
	//! @brief ������ ������ �� ó���ؾ��� ������ �����Ѵ�.
	virtual	void				ProcessContinue();
};
