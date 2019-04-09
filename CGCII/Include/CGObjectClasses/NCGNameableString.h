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
// 1. CGNameable란?
//     이름을 가지고 있는 
//    의미 한다.
//     일반적으로 Factory는 원하는 종류의 객체를 생산하여 할당하고 일련번호를
//    붙혀 관리한다. 또 다 사용한 객체를 돌려받으면 그 객체를 관리하고 있다가
//    다시 객체의 할당을 원할 때 할당해주는 Pool의 역할도 한다.
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

	//! @brief '객체 이름'설정과 함께 초기화한다.
			NString(_In_opt_z_ const _CHAR* _strName)					{	m_strName[0]=(_CHAR)NULL; if(_strName!=nullptr) ProcessSetName(_strName);}
	//! @brief '객체 이름'과 함께 초기화한다.
			NString(_In_opt_z_ const _CHAR_SUB* _strName)				{	m_strName[0]=(_CHAR)NULL; if(_strName!=nullptr){ _CHAR	strBuffer[1024]; SetName(CONVERT_STRING(_strName, strBuffer));}}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Name을  설정하고 얻는 함수.
	//! @brief '객체 이름'을 설정하는 과정을 정의하는 함수. @param _strName 설정할 '객체 이름'
	virtual	void				ProcessSetName(_In_z_ const _CHAR* _strName) override {	CGSTRCPY_S(m_strName, MAX_NAME_LENGTH, _strName);}
	//! @brief '객체 이름'과 동일한가를 확인하는 함수. @param _strCompare 비교할 '이름' @return true 동일하다. @return false 동일하지 않다.
	virtual	bool				ProcessIsThis(_In_z_ const _CHAR* _strCompare)const override {	return CGSTRCMP_S(m_strName, _strCompare, MAX_NAME_LENGTH)==0;}
	//! @brief '객체 이름'을 얻는 과정을 설정하는 함수. @return 등록된 '객체 이름'
	virtual	const _CHAR*		ProcessGetName() const override			{	return m_strName;}


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
private:
	// 1) String: Name
			_CHAR				m_strName[MAX_NAME_LENGTH];
};


}
