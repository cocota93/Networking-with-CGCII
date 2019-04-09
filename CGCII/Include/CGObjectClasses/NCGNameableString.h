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

namespace CGNameable
{

//-----------------------------------------------------------------------------
/**

 @class		NString
 @brief		
 @todo		
 @ref		
 @details	\n

*/
//
// ICGNameable
//
// 1. CGNameable��?
//     �̸��� ������ �ִ� 
//    �ǹ� �Ѵ�.
//     �Ϲ������� Factory�� ���ϴ� ������ ��ü�� �����Ͽ� �Ҵ��ϰ� �Ϸù�ȣ��
//    ���� �����Ѵ�. �� �� ����� ��ü�� ���������� �� ��ü�� �����ϰ� �ִٰ�
//    �ٽ� ��ü�� �Ҵ��� ���� �� �Ҵ����ִ� Pool�� ���ҵ� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
class NString : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGNameable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NString()													{	m_strName[0]=(_CHAR)NULL;}
	virtual	~NString()													{}

	//! @brief '��ü �̸�'������ �Բ� �ʱ�ȭ�Ѵ�.
			NString(_In_opt_z_ const _CHAR* _strName)					{	m_strName[0]=(_CHAR)NULL; if(_strName!=nullptr) ProcessSetName(_strName);}
	//! @brief '��ü �̸�'�� �Բ� �ʱ�ȭ�Ѵ�.
			NString(_In_opt_z_ const _CHAR_SUB* _strName)				{	m_strName[0]=(_CHAR)NULL; if(_strName!=nullptr){ _CHAR	strBuffer[1024]; SetName(CONVERT_STRING(_strName, strBuffer));}}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Name��  �����ϰ� ��� �Լ�.
	//! @brief '��ü �̸�'�� �����ϴ� ������ �����ϴ� �Լ�. @param _strName ������ '��ü �̸�'
	virtual	void				ProcessSetName(_In_z_ const _CHAR* _strName) override {	CGSTRCPY_S(m_strName, MAX_NAME_LENGTH, _strName);}
	//! @brief '��ü �̸�'�� �����Ѱ��� Ȯ���ϴ� �Լ�. @param _strCompare ���� '�̸�' @return true �����ϴ�. @return false �������� �ʴ�.
	virtual	bool				ProcessIsThis(_In_z_ const _CHAR* _strCompare)const override {	return CGSTRCMP_S(m_strName, _strCompare, MAX_NAME_LENGTH)==0;}
	//! @brief '��ü �̸�'�� ��� ������ �����ϴ� �Լ�. @return ��ϵ� '��ü �̸�'
	virtual	const _CHAR*		ProcessGetName() const override			{	return m_strName;}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
private:
	// 1) String: Name
			_CHAR				m_strName[MAX_NAME_LENGTH];
};


}
