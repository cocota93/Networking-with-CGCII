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
//-----------------------------------------------------------------------------
//
// CCGQueryPerformance
//
// 1. CCGQueryPerformance��...
//    1) QueryPerformance�� ����Ͽ� ������ �ð��� �����ϱ� ���� ���̴�.
//    2) ���е��� �ſ� ���ٴ� ������ ������ ���ϰ� ���� ���� ���.
//    3) ������� �ð��� ���� �� ����Ѵ�.
//
//
// 2. ����
//    1) ������ ������ �� �Ʒ� �Լ��� ȣ���Ѵ�.
//       CheckTimeStart()

//    2) ������ ������ �� �Ʒ�  �Լ��� ȣ���Ѵ�.
//       CheckTimeEnd()
//
//    3) ���� ������ �ð��� �������� �Ʒ� �Լ��� ȣ�� �Ѵ�. 
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