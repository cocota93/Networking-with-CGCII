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
//
// CCGQueryPerformance
//
// 1. CCGQueryPerformance은...
//    1) QueryPerformance를 사용하여 정말한 시간을 측정하기 위한 것이다.
//    2) 정밀도가 매우 높다는 장점이 있지만 부하가 비교적 많이 든다.
//    3) 상대적인 시간을 구할 때 사용한다.
//
//
// 2. 사용법
//    1) 측정을 시작할 때 아래 함수를 호출한다.
//       CheckTimeStart()

//    2) 측정을 종료할 때 아래  함수를 호출한다.
//       CheckTimeEnd()
//
//    3) 측정 구간의 시간을 얻으려면 아래 함수를 호추 한다. 
//       GetGapTime()
//
//
//-----------------------------------------------------------------------------
class CCGQueryPerformance
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CCGQueryPerformance()										{	QueryPerformanceFrequency(&m_tickFrequency); ;}
			~CCGQueryPerformance()										{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			float			GetGapTime() const							{	return m_fGapTime;}

			void			CheckTimeStart()							{	QueryPerformanceCounter(&m_timePre);}
			void			CheckTimeEnd()								{	QueryPerformanceCounter(&m_timeNow); m_fGapTime	 = ((float)m_timeNow.QuadPart-(float)m_timePre.QuadPart)/(float)m_tickFrequency.QuadPart*1000.f;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			LARGE_INTEGER	m_tickFrequency;

			LARGE_INTEGER	m_timePre;
			LARGE_INTEGER	m_timeNow;

			float			m_fGapTime;

public:
	static	LARGE_INTEGER	InitQueryFrequency();

};