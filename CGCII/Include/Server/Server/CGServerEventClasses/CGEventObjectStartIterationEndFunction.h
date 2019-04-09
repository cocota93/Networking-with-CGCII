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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// CGEvent::Object::CStartIterationEndFunction
//
// 1. CGEvent::Object::CStartIterationEndFunction��??
//    1) CGEvent::Object::CStartIterationEnd�� ������ ���������� �� ������ 
//       Process~�Լ��� �����ǰ� �ƴ϶� �Լ������ͷ� �Լ��� �����Ͽ� �� �Լ���
//       ������ ��ü�̴�.
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�̴�.
//
// ----------------------------------------------------------------------------
namespace CGEvent
{
namespace Object
{

template <class TFUNCTION=EVENT_FUNCTION>
class CStartIterationEndFunction :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGEvent::Object::CStartIterationEnd
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CStartIterationEndFunction() : CGEvent::Object::CStartIterationEnd(), m_functionStart(nullptr), m_functionEnd(nullptr), m_functionIteration(nullptr)	{}
			CStartIterationEndFunction(const char* _strName) : CGEvent::Object::CStartIterationEnd(_strName), m_functionStart(nullptr), m_functionEnd(nullptr), m_functionIteration(nullptr) {}
			CStartIterationEndFunction(const wchar_t* _wstrName) : CGEvent::Object::CStartIterationEnd(_wstrName), m_functionStart(nullptr), m_functionEnd(nullptr), m_functionIteration(nullptr) {}
	virtual	~CStartIterationEndFunction()								{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) �Լ� ����.
			void				SetStartFunction(_In_ const TFUNCTION& p_function) {	m_functionStart=p_function;}
			const TFUNCTION& 	GetStartFunction() const				{	return m_functionStart;}

			void				SetEndFunction(_In_ const TFUNCTION& p_function) {	m_functionEnd=p_function;}
			const TFUNCTION& 	GetEndFunction() const					{	return m_functionEnd;}

			void				SetIterationFunction(_In_ const TFUNCTION& p_function) {	m_functionIteration=p_function;}
			const TFUNCTION& 	GetIterationFunction() const			{	return m_functionIteration;}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	// 1) Event�� ������ �� �ҷ����� �Լ�.
	virtual	eOBJECT_RESULT		ProcessEventStart(_In_ const TIME::SYSTEM::time_point& _rtime)		{	RETURN_IF(m_functionStart==nullptr, eOBJECT_RESULT::NOT_EXIST); return m_functionStart(_rtime);}

	// 2) Event�� ���� �� �ҷ����� �Լ�.
	virtual	eOBJECT_RESULT		ProcessEventEnd(_In_ const TIME::SYSTEM::time_point& _rtime)		{	RETURN_IF(m_functionEnd==nullptr, eOBJECT_RESULT::NOT_EXIST); return m_functionEnd(_rtime);}

	// 3) Event�� �ݺ������� �ҷ����� �Լ�.
	virtual	eOBJECT_RESULT		ProcessEventIteration(_In_ const TIME::SYSTEM::time_point& _rtime)	{	RETURN_IF(m_functionIteration==nullptr, eOBJECT_RESULT::NOT_EXIST); return m_functionIteration(_rtime);}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Functions
			TFUNCTION			m_functionStart;
			TFUNCTION			m_functionEnd;
			TFUNCTION			m_functionIteration;
};


}
}