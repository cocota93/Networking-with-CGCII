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
namespace CGMessageable
{

//-----------------------------------------------------------------------------
/**

 @class		NBase
 @brief		�޽����� ���� �޴� Ŭ����
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class NBase : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGMessageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NBase() : m_bEnableMessageable(true)						{}
	virtual ~NBase()													{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) ProcessMessage Function
	virtual	int					ProcessMessage(CGMSG& _Msg)				{	if(IsMessageableDisabled()) return 0; return OnMessage(_Msg);}

	// 2) Enable Status
	//! @brief �޽��� ������ Ȱ��ȭ ��Ų��.
			void				EnableMessageable()						{	m_bEnableMessageable=true;}
	//! @brief �޽��� ������ ���� ��Ų��.
			void				DisableMessageable()					{	m_bEnableMessageable=false;}
	//! @brief �޽����� ���� �� �ִ� �����ΰ��� �˻��Ѵ�. @return true ���� �� ����. @return false ���� �� ����.
			bool				IsMessageableEnabled()					{	return m_bEnableMessageable;}
	//! @brief �޽����� ���� �� ���� �����ΰ��� �˻��Ѵ�. @return true ���� �� ����. @return false ���� �� ����.
			bool				IsMessageableDisabled()					{	return !IsMessageableEnabled();}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief �޽����� ���� �޾��� �� ȣ��Ǵ� �Լ� @param _Msg ���޹��� �޽��� @return !0 �޽����� ó����. @return 0 �޽����� ó������ ����.
	virtual	int					OnMessage(CGMSG& _Msg) PURE;


// ****************************************************************************
// Implmentations)
// ----------------------------------------------------------------------------
private:
	// 1) Flag
			bool				m_bEnableMessageable;
};


}