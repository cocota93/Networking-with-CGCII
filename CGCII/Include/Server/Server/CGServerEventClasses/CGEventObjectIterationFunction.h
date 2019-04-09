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
// CGEvent::Object::CIterationFunction
//
// 1. CGEvent::Object::CIterationFunction��??
//    1) CGEvent::Object::CIteration�� ������ ���������� �� ������ 
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
	// 1) �Լ� ����.
			void				SetIterationFunction(_In_ const TFUNCTION& p_function) {	m_functionIteration=p_function;}
			const TFUNCTION& 	GetIterationFunction() const			{	return m_functionIteration;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) Event�� �ݺ������� �ҷ����� �Լ�.
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