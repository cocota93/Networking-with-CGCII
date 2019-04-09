//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Event Classes                            *
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
// ----------------------------------------------------------------------------
//
// CGEvent::Object::CStartEndFunction
//
// 1. CGEvent::Object::CStartEndFunction
//    1) CGEvent::Object::CStartEnd와 완전히 동일하지만 각 실행을 
//       Process~함수의 재정의가 아니라 함수포인터로 함수를 지정하여 그 함수를
//       실행한 객체이다.
//
//    주의!!!) 설정되는 시간은 모두 Local TIme이 아니라 System Time이다.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

template <class TFUNCTION=EVENT_FUNCTION>
class CStartEndFunction :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::Object::CStartEnd
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CStartEndFunction() : CGEvent::Object::CStartEnd(), m_functionStart(nullptr), m_functionEnd(nullptr)	{}
			CStartEndFunction(const char* _strName) : CGEvent::Object::CStartEnd(_strName), m_functionStart(nullptr), m_functionEnd(nullptr) {}
			CStartEndFunction(const wchar_t* _wstrName) : CGEvent::Object::CStartEnd(_wstrName), m_functionStart(nullptr), m_functionEnd(nullptr) {}
	virtual	~CStartEndFunction()										{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 함수 설정.
			void				SetStartFunction(_In_ const TFUNCTION& p_function) {	m_functionStart=p_function;}
			const TFUNCTION& 	GetStartFunction() const				{	return m_functionStart;}

			void				SetEndFunction(_In_ const TFUNCTION& p_function) {	m_functionEnd=p_function;}
			const TFUNCTION& 	GetEndFunction() const					{	return m_functionEnd;}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	// 1) Event를 시작할 때 불려지는 함수.
	virtual	eOBJECT_RESULT		ProcessEventStart(_In_ const TIME::SYSTEM::time_point& _rtime)	{	RETURN_IF(m_functionStart==nullptr, eOBJECT_RESULT::NOT_EXIST); return m_functionStart(_rtime);}

	// 2) Event가 끝날 때 불려지는 함수.
	virtual	eOBJECT_RESULT		ProcessEventEnd(_In_ const TIME::SYSTEM::time_point& _rtime)	{	RETURN_IF(m_functionEnd==nullptr, eOBJECT_RESULT::NOT_EXIST); return m_functionEnd(_rtime);}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Functions
			TFUNCTION			m_functionStart;
			TFUNCTION			m_functionEnd;
};


}
}