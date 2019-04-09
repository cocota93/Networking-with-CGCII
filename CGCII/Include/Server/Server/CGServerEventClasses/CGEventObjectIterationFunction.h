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
// CGEvent::Object::CIterationFunction
//
// 1. CGEvent::Object::CIterationFunction란??
//    1) CGEvent::Object::CIteration와 완전히 동일하지만 각 실행을 
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
class CIterationFunction :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::Object::CIteration
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CIterationFunction() : CGEvent::Object::CIteration(), m_functionIteration(nullptr) {}
			CIterationFunction(const char* _strName) : CGEvent::Object::CIteration(_strName), m_functionIteration(nullptr) {}
			CIterationFunction(const wchar_t* _wstrName) : CGEvent::Object::CIteration(_wstrName), m_functionIteration(nullptr) {}
	virtual	~CIterationFunction()										{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 함수 설정.
			void				SetIterationFunction(_In_ const TFUNCTION& p_function) {	m_functionIteration=p_function;}
			const TFUNCTION& 	GetIterationFunction() const			{	return m_functionIteration;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) Event가 반복적으로 불려지는 함수.
	virtual	eOBJECT_RESULT		ProcessEventIteration(_In_ const TIME::SYSTEM::time_point& _rtime) {	RETURN_IF(m_functionIteration==nullptr, eOBJECT_RESULT::NOT_EXIST); return m_functionIteration(_rtime);}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Function
			TFUNCTION			m_functionIteration;
};


}
}