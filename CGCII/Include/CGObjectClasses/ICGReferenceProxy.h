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

 @class		ICGReferenceProxy
 @brief		기생하는 참조계수 클래스이다.
 @todo		
 @ref		CGPTR
 @details	\n
 참조계수 속성을 가지는 인터페이스 클래스로 내부적으로  참조계수를 가지고 있다.
 이 참조계수는 처음 생성될때는 0으로 초기화 되며
 AddReference()함수를 호출하면 참조계수 1이 증가하게 된다.
 Release()함수를 호출하면 참조계수 1이 감소하게 된다.
 또 참조계수가 0이 되면 OnFinalRelease()함수를 호출해준다.
 OnFinalRelease()함수를 재정의하면 참조계수가 0이 되었을 때 동작을 정의해 
 줄 수 있다.
 이때 참조계수 증감은 쓰레드에 안전하게 동작한다.

 일반적으로 ICGReferenceable는 동적할당된 객체의 자동할당해제를 위해 사용된다.

*/
//-----------------------------------------------------------------------------
class ICGReferenceProxy
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			ICGReferenceProxy(ICGReferenceable* _pBoss) : m_pBoss(_pBoss) {}
			ICGReferenceProxy(const ICGReferenceProxy& _Copy): m_pBoss(_Copy.m_pBoss) {}
	virtual	~ICGReferenceProxy()										{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief 참조계수를 1 증가시킨다. @return 변공된 참조계수 값
			int					AddRef()								{	return m_pBoss->AddRef();}
	//! @brief 참조계수를 _Count만큼 증가시킨다.(_Count값이 음수면 안됀다.) @param _Count 증가치 @return 증가시킨 이후 참조계수
			int					AddRef(int _Count)						{	return m_pBoss->AddRef(_Count);}

	//! @brief 참조계수를 1 감소시킨다. 참조계수가 0이 되면 OnFinalRelease/ProcessDispose를 호출한다. @return 감소시킨 후 참조계수
			int					Release()								{	return m_pBoss->Release();}

	//! @brief 현재 참조계수를 얻는다. @return 현재 참조계수
			int					GetReferenceCount() const				{	return m_pBoss->GetReferenceCount();}

	//! @brief 객체를 폐기하도록 설정한다. 풀에서 할당된 객체의 경우 Disuse로 설정되면 풀로 되돌아 가면 재사용하지 않고 바로 소멸시킨다. 
			void				SetAsDisuse()							{	m_pBoss->SetAsDisuse();}
			bool				IsDisuse() const						{	return m_pBoss->IsDisuse();}

	//! @brief 증가연산자: 참조계수를 1 증가시킨다.(AddRef와 동일하다.)
			ICGReferenceProxy&	operator++()							{	m_pBoss->AddRef(); return *this;}
	//! @brief 감소연산자: 참조계수를 1 감소시킨다.(Release()와 동일하다.)
			ICGReferenceProxy&	operator--()							{	m_pBoss->Release(); return *this;}
	//! @brief 더하기 연산자: 참조계수를 rhs만큼 증가시킨다. @param rhs 증가치
			void				operator+=(int rhs)						{	m_pBoss->AddRef(rhs);}

	//! @brief 대입연산자
			ICGReferenceProxy&	operator=(const ICGReferenceProxy&)		{	return *this;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			ICGReferenceable*	m_pBoss;
};
