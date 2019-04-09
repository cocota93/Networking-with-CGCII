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

 @class		NCGObjectState
 @brief		ICGObjectState�� ������ Ŭ����
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class NCGObjectState : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGObjectState
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NCGObjectState() : m_stateObject(eOBJECT_STATE::NONE)			{}
			NCGObjectState(_In_ eOBJECT_STATE _State) : m_stateObject(_State) {}
	virtual	~NCGObjectState()												{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief ���� ��ü ���¸� ��´�. @return true ���� ��ü ����
	virtual	eOBJECT_STATE		GetObjectState() const override				{	return m_stateObject;}
	//! @brief ���� ��ü ���¸� �����Ѵ�. @param _State �����ϰ��� �ϴ� '��ü ����' @return ������ '��ü ����'
	virtual	eOBJECT_STATE		SetObjectState(_In_ eOBJECT_STATE _State) NOEXCEPT  override  	{	eOBJECT_STATE statusPre=m_stateObject.exchange(_State); if(statusPre!=_State) ProcessStateChanged(_State); return statusPre;}
	//! @brief ���� ���°� _StateCompare�� ��� _State�� �����Ѵ�. @param _StateCompare ���� ��ü ���� @ param _State ������ ��ü ���� @return true ���� ���� @return false ���� ����
	virtual	bool				SetObjectStateIf(_In_ eOBJECT_STATE _StateCompare, _In_ eOBJECT_STATE _State) NOEXCEPT override	{	bool bChanged=m_stateObject.compare_exchange_weak(_StateCompare, _State); if(bChanged) ProcessStateChanged(_State); return bChanged;}


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	//! @brief ���°� ����Ǿ��� �� ȣ��ȴ�. @param _State ����� ����
	virtual	void				ProcessStateChanged(_In_ eOBJECT_STATE /*_State*/)	{}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			ATOMIC<eOBJECT_STATE>	m_stateObject;
};
