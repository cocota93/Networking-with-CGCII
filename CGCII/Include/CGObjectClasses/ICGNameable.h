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
//-----------------------------------------------------------------------------
/**

 @class		ICGNameable
 @brief		이름을 가지는 속성 인터페이스 클래스
 @todo		
 @ref		ICGOpenable, ICGCloseable, ICGDestroyable
 @details	\n
 객체는 이름을 설정하거나 설정된 이름을 얻는 속성을 가지려면 이 인터페이스 클래스를 상속받는다.
 SetName(...)함수는 이름을 설정하는 함수이며
 GetName()은 설정된 이름을 얻는 함수이다.

*/
//-----------------------------------------------------------------------------
#define	MAX_NAME_LENGTH		256

class ICGNameable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGNameable()		{}

// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief '비교 이름'과 동일한가를 확인하는 처리를 정의한다. @param _strCompare '비교 이름' @return true 같음 @return false 다름
	virtual	bool				ProcessIsThis(_In_z_ const _CHAR* /*_strCompare*/) const PURE;
	//! @brief '객체 이름'을 얻는 과정을 정의한다. @return true '객체 이름' 포인터
	virtual	const _CHAR*		ProcessGetName() const PURE;
	//! @brief '객체 이름'을 설정하는 과정을 정의한다. @param  _strName 설정할 '객체 이름'
	virtual	void				ProcessSetName(_In_z_ const _CHAR* /*_strName*/) PURE;

public:
	//! @brief '객체 이름'을 설정한다. @param _strName '객체이름'
			void				SetName(_In_z_ const _CHAR* _strName)			{	ProcessSetName(_strName);}
	//! @brief '객체 이름'을 설정한다. @param _strName '객체이름'
			void				SetName(_In_z_ const _CHAR_SUB* _strName)		{	_CHAR strBuffer[1024]; ProcessSetName(CONVERT_STRING(_strName, strBuffer));}

	//! @brief '비교 이름'과 동일한가 확인한다. @param _strCompare '비교 이름' @return true 같음 @return false 다름
			bool				IsThis(_In_z_ const _CHAR* _strCompare) const	{	return ProcessIsThis(_strCompare);}
	//! @brief '비교 이름'과 동일한가 확인한다. @param _strCompare '비교 이름' @return true 같음 @return false 다름
			bool				IsThis(_In_z_ const _CHAR_SUB* _strCompare) const{	_CHAR strBuffer[1024]; return ProcessIsThis(CONVERT_STRING(_strCompare, strBuffer));}

	//! @brief '객체 이름'을 얻는다. @return '객체 이름' 포인터
			const _CHAR*		GetName() const									{	return ProcessGetName();}
	//! @brief '객체 이름'을 얻는다. @param _strName '객체 이름'을 받아올 포인터 @return '객체이름'을 받아올 포인터
			_CHAR*				GetName(_Inout_z_ _CHAR* _strName) const			{	RETURN_IF(_strName==nullptr, nullptr); CGSTRCPY_S(_strName, MAX_NAME_LENGTH, ProcessGetName()); return _strName;}
	//! @brief '객체 이름'을 얻는다. @param _strName '객체 이름'을 받아올 포인터 @return '객체이름'을 받아올 포인터
			_CHAR_SUB*			GetName(_Inout_z_ _CHAR_SUB* _strName) const		{	RETURN_IF(_strName==nullptr, nullptr); return CONVERT_STRING(ProcessGetName(), _strName);}

};

template <class TOBJECT>
const _CHAR* GET_NAME(_In_ TOBJECT* object)
{	
	ICGNameable* p=dynamic_cast<ICGNameable*>(object);
	return (p!=nullptr) ? p->GetName() : _CGTEXT("");
}
