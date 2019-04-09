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

 @class		ICGMessageable
 @brief		�޽����� ������ �� �ִ� �������̽� Ŭ����
 @todo		
 @ref		ICGOpenable, ICGCloseable, ICGDestroyable
 @details	\n
 �޽����� ���޹��� �� �ִ� �������̽� Ŭ�����̴�. 
 RequestProcessMessage(...)�Լ��� �޽����� ���޹�����
 ProcessMessage(...) �Լ����� ���� ���� �޽����� ���� ó���� �����Ѵ�.

*/
//-----------------------------------------------------------------------------
class ICGMessageable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGMessageable()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief �޽��� ó���� ��û�Ѵ�. @param _Msg ó�� ��û�ϴ� �޽��� @return true !0 ó���� @return 0 ó������ ����
			int					RequestProcessMessage(CGMSG& _Msg)		{	return ProcessMessage(_Msg);}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief �޽��� ó���� �����Ѵ�. @param _Msg ó�� ��û�ϴ� �޽��� @return true !0 ó���� @return 0 ó������ ����
	virtual	int					ProcessMessage(CGMSG& _Msg) PURE;
};
