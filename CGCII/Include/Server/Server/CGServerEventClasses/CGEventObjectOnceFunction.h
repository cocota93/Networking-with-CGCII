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
// CGEvent::Object::COnce
//
// 1. CGEvent::Object::COnce란??
//    1) 정해진 시간 딱 한번만 수행이 되는 Event Object이다.
//    2) SetEventTime()함수를 사용하여 실행될 시간을 설정할 수 있다.
//
//    주의!!!) 설정되는 시간은 모두 Local TIme이 아니라 System Time므로 주의해야 한다.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

template <class TFUNCTION=EVENT_FUNCTION>
class COnceFunction :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::Object::COnce
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			COnceFunction() : m_functionOnce(nullptr)					{}
			COnceFunction(const char* _strName) : CGEvent::Object::COnce(_strName), m_functionOnce(nullptr) {}
			COnceFunction(const wchar_t* _wstrName) : CGEvent::Object::COnce(_wstrName), m_functionOnce(nullptr) {}
	virtual	~COnceFunction()											{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) 함수 설정.
			void				SetFunction(_In_ const TFUNCTION& p_function){	m_functionOnce=p_function;}
			const TFUNCTION& 	GetFunction() const						{	return m_functionOnce;}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	virtual	eOBJECT_RESULT		ProcessEvent(_In_ const TIME::SYSTEM::time_point& _rtime)	{	RETURN_IF(m_functionOnce==nullptr, eOBJECT_RESULT::NOT_EXIST); return m_functionOnce(_rtime);}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Functions
			TFUNCTION			m_functionOnce;
};


}
}