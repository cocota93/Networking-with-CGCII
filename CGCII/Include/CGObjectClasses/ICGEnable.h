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

 @class		ICGEnable
 @brief		����/�Ұ��� �Ӽ��� ���� �������̽� Ŭ����
 @todo		
 @ref		ICGReferenceable
 @details	\n
 
*/
//-----------------------------------------------------------------------------
class ICGEnable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGEnable()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief �޽��� ó���� ��û�Ѵ�. @param _Msg ó�� ��û�ϴ� �޽��� @return true !0 ó���� @return 0 ó������ ����
			bool				Enable(bool _bState=true)			{	return ProcessSetEnable(_bState);}
			bool				Disable()							{	return ProcessSetEnable(false);}

			bool				IsEnable()							{	return ProcessGetEanble();}
			bool				IsDisable()							{	return !ProcessGetEanble();}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	//! @brief ����/�Ұ��� ������ ���� ó���� �����Ѵ�. @param _bState ������ State @return ���� ��������
	virtual	bool				ProcessSetEnable(bool _bState) PURE;

	//! @brief ������ ����/�Ұ��� ������ ������ �����Ѵ�. @return ������ ����/�Ұ��� ��������
	virtual	bool				ProcessGetEnable() PURE;
};
