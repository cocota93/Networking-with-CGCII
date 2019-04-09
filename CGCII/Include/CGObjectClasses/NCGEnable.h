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

@class		NCGEnable
@brief		����/�Ұ��� �Ӽ��� ���� �������̽� Ŭ����
@todo		
@ref		ICGReferenceable
@details	\n

*/
//-----------------------------------------------------------------------------
class NCGEnable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGEnable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NCGEnable(bool _bState=false) : m_bState(_bState)			{}
	virtual	~NCGEnable()	{}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	void				OnEanble(bool _bState)					{}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
protected:
	//! @brief ����/�Ұ��� ������ ���� ó���� �����Ѵ�. @param _bState ������ State @return ���� ���� ����
	virtual	bool				ProcessSetEnable(bool _bState)	{	auto bOld=m_bState.exchange(_bState); if(bOld!=_bState) OnEanble(_bState); return bOld;}

	//! @brief ������ ����/�Ұ��� ������ ������ �����Ѵ�. @return ������ ����/�Ұ��� ��������
	virtual	bool				ProcessGetEnable()				{	return m_bState.load();}

private:
			ATOMIC<bool>		m_bState;
};
